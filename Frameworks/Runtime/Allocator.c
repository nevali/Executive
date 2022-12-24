/* Executive Microkernel
 * Runtime Framework
 *   This framework provides low-level user-space APIs to applications, via
 *   the Executive's system call mechanism
 */

/* Copyright 2015-2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Runtime.h"

/* There is no fundamental difference between a kernel- and a user-space
 * memory allocator, save for the underlying mechanism employed to obtain
 * regions of memory. To that end, the Runtime framework (in both Executive
 * and user-space variants) incorporates the same standard allocator, which
 * is currently Doug Lea's malloc()
 *
 * In both build variants, the allocator uses IAddressSpace::obtainTransientRegion()
 * via intermediate functions defined in this file, the only difference is
 * how that IAddressSpace interface pointer is obtained
 */

#include "ThirdParty/dlmalloc/malloc.h"

#define INTF_TO_CLASS(i)               (RtAllocator *)((void *)(i))

/* Provide a malloc-style memory allocator, primarily for use within the
 * Executive's own address space
 */
union RtAllocator {
	struct {
		const struct IAllocator_vtable_ *vtable;
	} vtable;
	IAllocator Allocator;
	/* XXX this will be a problem if IRegionHolder becomes a delegate with methods!! */
	IRegionHolder RegionHolder;
	IObject Object;
	struct {
		const void *vtable;
		int32_t refCount;
		/* the addres space we obtain regions from */
		IAddressSpace *addressSpace;
		/* the page size used by the Memory Manager */
		size_t pageSize;
		/* the dlmalloc context */
		mspace msp;
		/* a pointer to the next allocator in the chain (if there is one) */
		RtAllocator *next;
		/* a reference to the first region allocated to us by the Memory
		 * Manager */
		IRegion *firstRegion;
		/* our region list */
		size_t regionsSize;
		size_t regionsCount;
		IRegion **regions;
	} data;
};

/* IObject */

static STATUS RtAllocator_queryInterface(IAllocator *me, REFUUID iid, void **out);
static int32_t RtAllocator_retain(IAllocator *me);
static int32_t RtAllocator_release(IAllocator *me);

/* IRegionHolder */

/* IAllocator */

static void *RtAllocator_alloc(IAllocator *me, size_t nbytes);
static void *RtAllocator_realloc(IAllocator *me, void *ptr, size_t nbytes);
static void RtAllocator_free(IAllocator *me, void *ptr);
static size_t RtAllocator_size(IAllocator *me, void *ptr);
static int RtAllocator_didAlloc(IAllocator *me, void *ptr);
static void RtAllocator_compact(IAllocator *me);

static const struct IAllocator_vtable_ RtAllocator_vtable = {
	RtAllocator_queryInterface,
	RtAllocator_retain,
	RtAllocator_release,
	RtAllocator_alloc,
	RtAllocator_realloc,
	RtAllocator_free,
	RtAllocator_size,
	RtAllocator_didAlloc,
	RtAllocator_compact
};

static RtAllocator systemAllocator = { { &RtAllocator_vtable }};

void *
RtMemAlloc(size_t nbytes)
{
	if(!systemAllocator.data.refCount)
	{
		RTPANIC("attempt to use RtMemAlloc() before system allocator is available");
		return NULL;
	}
	return RtAllocator_alloc(&(systemAllocator.Allocator), nbytes);
}

STATUS
RtAllocator_MFactory_createInstance(MFactory *me, IObject *outer, REFUUID iid, void **out)
{
	UNUSED__(me);
	UNUSED__(outer);
	UNUSED__(iid);
	UNUSED__(out);

	return E_NOTIMPL;
}

IAllocator *
RtAllocator_create(IAddressSpace *addressSpace)
{
	RtAllocator *alloc, *p;

	RTASSERT(NULL != addressSpace);
	/* XXX atomic! */
	if(systemAllocator.data.refCount)
	{
		/* Use the system allocator to allocate a new RtAllocator
		 * structure
		 */
		RTLOGF((LOG_DEBUG7, "RtAllocator::create(): initialising secondary allocator"));
		alloc = (RtAllocator *)	mspace_calloc(systemAllocator.data.msp, 1, sizeof(RtAllocator));
		if(!alloc)
		{
			return NULL;
		}
		/* Add the new allocator to the chain */
		for(p = &systemAllocator; p->data.next; p = p->data.next);
		p->data.next = alloc;
	}
	else
	{
		/* The first Allocator we create becomes the system allocator, and
		 * is subsequently used to allocate the data structures used by other
		 * allocators
		 */
		RTLOGF((LOG_DEBUG7, "RtAllocator::create(): initialising system allocator"));
		alloc = &systemAllocator;
		RtMemSet(alloc, 0, sizeof(RtAllocator));
	}
	RTLOGF((LOG_DEBUG7, "RtAllocator::create(): alloc = %p", alloc));
	IAddressSpace_retain(addressSpace);
	alloc->vtable.vtable = &RtAllocator_vtable;
	alloc->data.refCount = 1;
	alloc->data.addressSpace = addressSpace;
	alloc->data.pageSize = IAddressSpace_pageSize(addressSpace);
	RTLOGF((LOG_DEBUG7, "creating mspace"));
	alloc->data.msp = create_mspace_MemoryManager(alloc, 0, 0);
	RTASSERT(NULL != alloc->data.msp);
	/* create the region list */
	RTLOGF((LOG_DEBUG7, "creating regions list"));
	alloc->data.regionsCount = 0;
	alloc->data.regionsSize = 2;
	alloc->data.regions = (IRegion **) mspace_calloc(alloc->data.msp, (alloc->data.regionsSize), sizeof(IRegion *));
	RTASSERT(NULL != alloc->data.regions);
	/* that allocation operation will have triggered the mapping of the first region */
	RTASSERT(NULL != alloc->data.firstRegion);
	alloc->data.regions[0] = alloc->data.firstRegion;
	alloc->data.regionsCount = 1;
	RTLOGF((LOG_DEBUG7, "returning IAllocator interface pointer %p", &(alloc->Allocator)));
	return &(alloc->Allocator);
}

/* INTERNAL: obtain a region and return it to dlmalloc
 *
 * NOTE: until this function has successfully returned, no dynamic memory
 *       management is available - it's called by create_mspace() when the
 *       first allocator is being created (by RtAllocator_create(),
 *       above), and then subsequently when any allocator needs to obtain
 *       pages of transient memory.
 */
void *
Rt_AllocatorMap(RtAllocator *self, size_t size, RegionFlags flags)
{
	size_t pages;
	IRegion *region;
	
	RTLOGF((LOG_DEBUG7, "DEBUG: %s: request for %lu bytes (flags %d)", __FUNCTION__, (unsigned long) size, flags));
	RTASSERT(NULL != self->data.addressSpace);
	/* ASSERT(0 == size % self->data.pageSize); */
	if(size % self->data.pageSize)
	{
		RTPANIC("Executive::Allocator::map(): ASSERTION FAILED: size % self->data.pageSize is nonzero; request is not page-aligned");
	}
	pages = size / self->data.pageSize;
	RTLOGF((LOG_DEBUG7, "DEBUG: %s: request is for %lu pages", __FUNCTION__, pages));
	if(IAddressSpace_obtainTransientRegion(self->data.addressSpace, pages, flags, &(systemAllocator.RegionHolder), &region) != E_SUCCESS)
	{
		RTPANIC("Executive::Allocator::map(): IAddressSpace::obtainTransientRegion() failed (out of memory?)");
	}
	if(!self->data.firstRegion)
	{
		self->data.firstRegion = region;
		RTLOGF((LOG_DEBUG7, "DEBUG: %s: obtained first region (%llu bytes) from the address space", __FUNCTION__, (unsigned long long) size));
		return IRegion_base(region);
	}
	RTLOGF((LOG_WARNING, "WARNING: Executive::Allocator::map(): second region obtained but that isn't handled yet"));
	return IRegion_base(region);
}

/*INTERNAL*/
STATUS
Rt_AllocatorUnmap(RtAllocator *self, void *addr, size_t size)
{
	UNUSED__(self);
	UNUSED__(addr);
	UNUSED__(size);
	RTLOGF((LOG_NOTICE, "RtAllocator::unmap(): not yet implemented"));
//	fprintf(stderr, "DEBUG: %s: releasing %lu bytes at 0x%llx\n", __FUNCTION__, size, (unsigned long long) addr);
	return E_NOTIMPL;
}

/* IObject */

static STATUS
RtAllocator_queryInterface(IAllocator *me, REFUUID iid, void **out)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	if(RtUuidEqual(iid, &IID_IObject))
	{
		if(out)
		{
			IAllocator_retain(me);
			*out = &(self->Object);
		}
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_IRegionHolder))
	{
		if(out)
		{
			IAllocator_retain(me);
			*out = &(self->RegionHolder);
		}
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_IAllocator))
	{
		if(out)
		{
			IAllocator_retain(me);
			*out = &(self->Allocator);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static REFCOUNT
RtAllocator_retain(IAllocator *me)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	return self->data.refCount;
}

static REFCOUNT
RtAllocator_release(IAllocator *me)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	return self->data.refCount;
}

/* IAllocator */

static void *
RtAllocator_alloc(IAllocator *me, size_t nbytes)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	return mspace_calloc(self->data.msp, 1, nbytes);
}

static void *
RtAllocator_realloc(IAllocator *me, void *ptr, size_t nbytes)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	return mspace_realloc(self->data.msp, ptr, nbytes);
}

static void
RtAllocator_free(IAllocator *me, void *ptr)
{
	RtAllocator *self = INTF_TO_CLASS(me);

	mspace_free(self->data.msp, ptr);
}

static size_t
RtAllocator_size(IAllocator *me, void *ptr)
{
	UNUSED__(me);
	UNUSED__(ptr);

	return (size_t) -1;
}

static int
RtAllocator_didAlloc(IAllocator *me, void *ptr)
{
	UNUSED__(me);
	UNUSED__(ptr);

	return -1;
}

static void
RtAllocator_compact(IAllocator *me)
{
	UNUSED__(me);
}
