#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

# define INITGUID_EXTERN       1

#include <Executive/Internal/Allocator.h>
#include <Executive/Internal/Runtime.h>
#include <Executive/MFactory.h>

#include "dlmalloc/malloc.h"

#define INTF_TO_CLASS(i)               (Executive_Allocator *)((void *)(i))

/* Provide a malloc-style memory allocator, primarily for use within the
 * Executive's own address space
 */
union Executive_Allocator {
	struct {
		const struct IAllocator_vtable_ *vtable;
	} vtable;
	IAllocator Allocator;
	IRegionHolder RegionHolder;
	IObject Object;
	struct {
		const void *vtable;
		int32_t refCount;
		/* the Memory Manager used to obtain regions */
		IMemoryManager *mm;
		/* the page size used by the Memory Manager */
		size_t pageSize;
		/* the dlmalloc context */
		mspace msp;
		/* a pointer to the next allocator in the chain (if there is one) */
		Executive_Allocator *next;
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

static STATUS Executive_Allocator_queryInterface(IAllocator *me, REFUUID iid, void **out);
static int32_t Executive_Allocator_retain(IAllocator *me);
static int32_t Executive_Allocator_release(IAllocator *me);

/* IRegionHolder */

/* IAllocator */

static void *Executive_Allocator_alloc(IAllocator *me, size_t nbytes);
static void *Executive_Allocator_realloc(IAllocator *me, void *ptr, size_t nbytes);
static void Executive_Allocator_free(IAllocator *me, void *ptr);
static size_t Executive_Allocator_size(IAllocator *me, void *ptr);
static int Executive_Allocator_didAlloc(IAllocator *me, void *ptr);
static void Executive_Allocator_compact(IAllocator *me);

static const struct IAllocator_vtable_ Executive_Allocator_vtable = {
	Executive_Allocator_queryInterface,
	Executive_Allocator_retain,
	Executive_Allocator_release,
	Executive_Allocator_alloc,
	Executive_Allocator_realloc,
	Executive_Allocator_free,
	Executive_Allocator_size,
	Executive_Allocator_didAlloc,
	Executive_Allocator_compact
};

static Executive_Allocator systemAllocator = { { &Executive_Allocator_vtable }};

extern STATUS
Executive_Allocator_MFactory_createInstance(MFactory *me, IObject *outer, REFUUID iid, void **out)
{
	UNUSED__(me);
	UNUSED__(outer);
	UNUSED__(iid);
	UNUSED__(out);

	return E_NOTIMPL;
}

IAllocator *
Executive_Allocator_create(IMemoryManager *mm)
{
	Executive_Allocator *alloc, *p;

	if(systemAllocator.data.refCount)
	{
		/* Use the system allocator to allocate a new Executive_Allocator
		 * structure
		 */
		alloc = (Executive_Allocator *)	ExAlloc(sizeof(Executive_Allocator));
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
		alloc = &systemAllocator;
	}
	IMemoryManager_retain(mm);
	alloc->data.refCount = 1;
	alloc->data.mm = mm;
	alloc->data.pageSize = IMemoryManager_pageSize(mm);
	alloc->data.msp = create_mspace_MemoryManager(alloc, 0, 0);
	ExAssert(NULL != alloc->data.msp);
	/* create the region list */
	alloc->data.regionsCount = 0;
	alloc->data.regionsSize = 2;
	alloc->data.regions = (IRegion **) mspace_calloc(alloc->data.msp, (alloc->data.regionsSize), sizeof(IRegion *));
	ExAssert(NULL != alloc->data.regions);
	/* that allocation operation will have triggered the mapping of the first region */
	ExAssert(NULL != alloc->data.firstRegion);
	alloc->data.regions[0] = alloc->data.firstRegion;
	alloc->data.regionsCount = 1;
	return &(alloc->Allocator);
}

/* INTERNAL: obtain a region and return it to dlmalloc
 *
 * NOTE: until this function has successfully returned, no dynamic memory
 *       management is available - it's called by create_mspace() when the
 *       first allocator is being created (by Executive_Allocator_create(),
 *       above), and then subsequently when any allocator needs to obtain
 *       pages of transient memory.
 */
void *
Executive_Allocator_map(Executive_Allocator *self, size_t size, RegionFlags flags)
{
	size_t pages;
	IRegion *region;

//	fprintf(stderr, "DEBUG: %s: request for %lu bytes (flags %d)\n", __FUNCTION__, (unsigned long) size, flags);
	if(!self->data.mm)
	{
		PAL_panic("Executive::Allocator::map(): attempt to obtain mapping when no Memory Manager is available");
	}
	/* ASSERT(0 == size % self->data.pageSize); */
	if(size % self->data.pageSize)
	{
		PAL_panic("Executive::Alloctor::map(): ASSERTION FAILED: size % self->data.pageSize is nonzero; request is not page-aligned");
	}
	pages = size / self->data.pageSize;
//	fprintf(stderr, "DEBUG: %s: request is for %lu pages\n", __FUNCTION__, pages);
	if(IMemoryManager_obtainTransientRegion(self->data.mm, pages, flags, &(systemAllocator.RegionHolder), &region) != E_SUCCESS)
	{
		PAL_panic("Executive::Allocator::map(): IMemoryManager::obtainTransientRegion() failed (out of memory?)");
	}
	if(!self->data.firstRegion)
	{
		self->data.firstRegion = region;
//		fprintf(stderr, "DEBUG: %s: obtained first region (%llu bytes) from Memory Manager\n", __FUNCTION__, (unsigned long long) size);
		return IRegion_base(region);
	}
//	PAL_panic("Executive::Allocator::map(): second region obtained but that isn't handled yet");
	EXLOGF((LOG_WARNING, "WARNING: Executive::Allocator::map(): second region obtained but that isn't handled yet"));
	return IRegion_base(region);
}

int
Executive_Allocator_unmap(Executive_Allocator *self, void *addr, size_t size)
{
	UNUSED__(self);
	UNUSED__(addr);
	UNUSED__(size);
	ExNotice("Executive::Allocator::unmap(): not yet implemented");
//	fprintf(stderr, "DEBUG: %s: releasing %lu bytes at 0x%llx\n", __FUNCTION__, size, (unsigned long long) addr);
	return E_NOTIMPL;
}

/* IObject */

static STATUS
Executive_Allocator_queryInterface(IAllocator *me, REFUUID iid, void **out)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);

	if(ExUuidEqual(iid, &IID_IObject))
	{
		IAllocator_retain(me);
		if(out)
		{
			*out = &(self->Object);
		}
		return E_SUCCESS;
	}
	if(ExUuidEqual(iid, &IID_IRegionHolder))
	{
		IAllocator_retain(me);
		if(out)
		{
			*out = &(self->RegionHolder);
		}
		return E_SUCCESS;
	}
	if(ExUuidEqual(iid, &IID_IAllocator))
	{
		IAllocator_retain(me);
		if(out)
		{
			*out = &(self->Allocator);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static int32_t
Executive_Allocator_retain(IAllocator *me)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);

	return self->data.refCount;
}

static int32_t
Executive_Allocator_release(IAllocator *me)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);

	return self->data.refCount;
}

/* IAllocator */

#include <string.h>

static void *
Executive_Allocator_alloc(IAllocator *me, size_t nbytes)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);
	void *ptr;

	ptr = mspace_calloc(self->data.msp, 1, nbytes);
	if(ptr)
	{
		memset(ptr, 0, nbytes);
	}
	return ptr;
}

static void *
Executive_Allocator_realloc(IAllocator *me, void *ptr, size_t nbytes)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);

	return mspace_realloc(self->data.msp, ptr, nbytes);
}

static void
Executive_Allocator_free(IAllocator *me, void *ptr)
{
	Executive_Allocator *self = INTF_TO_CLASS(me);

	mspace_free(self->data.msp, ptr);
}

static size_t
Executive_Allocator_size(IAllocator *me, void *ptr)
{
	UNUSED__(me);
	UNUSED__(ptr);

	return (size_t) -1;
}

static int
Executive_Allocator_didAlloc(IAllocator *me, void *ptr)
{
	UNUSED__(me);
	UNUSED__(ptr);

	return -1;
}

static void
Executive_Allocator_compact(IAllocator *me)
{
	UNUSED__(me);
}
