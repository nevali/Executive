/* Executive Microkernel
 * POSIX Platform Adaptation Layer - Memory Manager
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#include "p_AddressSpace.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_AddressSpace *)((void *)(i))

/* IObject */

static int PAL_POSIX_AddressSpace_queryInterface(IAddressSpace *me, REFUUID riid, void **ptr);
static int32_t PAL_POSIX_AddressSpace_retain(IAddressSpace *me);
static int32_t PAL_POSIX_AddressSpace_release(IAddressSpace *me);

/* XXX should be MAddressSpace - there can only be one */

/* IAddressSpace */

static int PAL_POSIX_AddressSpace_regionForPtr(IAddressSpace *me, void *ptr, IRegion **out);
static int PAL_POSIX_AddressSpace_pageSize(IAddressSpace *me);
static int PAL_POSIX_AddressSpace_obtainRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);
static int PAL_POSIX_AddressSpace_obtainTransientRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);
static STATUS PAL_POSIX_AddressSpace_createContext(IAddressSpace *me, IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context);

static struct IAddressSpace_vtable_ PAL_POSIX_AddressSpace_vtable = {
	PAL_POSIX_AddressSpace_queryInterface,
	PAL_POSIX_AddressSpace_retain,
	PAL_POSIX_AddressSpace_release,
	PAL_POSIX_AddressSpace_regionForPtr,
	PAL_POSIX_AddressSpace_pageSize,
	PAL_POSIX_AddressSpace_obtainRegion,
	PAL_POSIX_AddressSpace_obtainTransientRegion,
	PAL_POSIX_AddressSpace_createContext
};

static PAL_POSIX_AddressSpace PAL_POSIX_memoryManager = { { &PAL_POSIX_AddressSpace_vtable, NULL } };

/* INTERNAL: perform one-time initialisation */
void
PAL_POSIX_AddressSpace_init(void)
{
	PALLOGF((LOG_TRACE, "PAL::POSIX::AddressSpace(%p)::init()", &PAL_POSIX_memoryManager));
#if defined(HAVE_SYSCONF) && defined(_SC_PAGESIZE)
	PAL_POSIX_memoryManager.data.pagesize = sysconf(_SC_PAGESIZE);
#elif defined(HAVE_GETPAGESIZE)
	PAL_POSIX_memoryManager.data.pagesize = getpagesize();
#else
# warning PAL_POSIX_AddressSpace: no available API to determine default page size
	PAL_POSIX_memoryManager.data.pagesize = 4096; /* Default to 4KB pages without other info */
#endif
	PALLOGF((LOG_DEBUG, "PAL::POSIX::AddressSpace: page size is %u", PAL_POSIX_memoryManager.data.pagesize));
	PAL_POSIX_Platform_setAddressSpace(&(PAL_POSIX_memoryManager.AddressSpace));
}

static int
PAL_POSIX_AddressSpace_queryInterface(IAddressSpace *me, REFUUID riid, void **ptr)
{
	PAL_POSIX_AddressSpace *self = INTF_TO_CLASS(me);
	
	if(!memcmp(riid, &IID_IObject, sizeof(UUID)))
	{
		if(ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(self->Object);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IAddressSpace, sizeof(UUID)))
	{
		if(ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(self->AddressSpace);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static int32_t
PAL_POSIX_AddressSpace_retain(IAddressSpace *me)
{
	UNUSED__(me);
	
	/* PAL_POSIX_AddressSpace is a singleton */
	return 2;
}

static int32_t
PAL_POSIX_AddressSpace_release(IAddressSpace *me)
{
	UNUSED__(me);

	/* PAL_POSIX_AddressSpace is a singleton */
	return 1;
}

static int
PAL_POSIX_AddressSpace_regionForPtr(IAddressSpace *me, void *ptr, IRegion **out)
{
	PAL_POSIX_AddressSpace *self = INTF_TO_CLASS(me);

	UNUSED__(ptr);
	UNUSED__(self);

	if(out)
	{
		*out = NULL;
	}

	return E_NOTIMPL;
}

static int
PAL_POSIX_AddressSpace_pageSize(IAddressSpace *me)
{
	PAL_POSIX_AddressSpace *self = INTF_TO_CLASS(me);

	return self->data.pagesize;
}

static int
PAL_POSIX_AddressSpace_obtainRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	if(flags & RF_TRANSIENT)
	{
		return PAL_POSIX_AddressSpace_obtainTransientRegion(me, count, flags, owner, region);
	}
	/* PAL_POSIX_AddressSpace cannot currently handle non-transient mappings */
	return E_NOMEM;
}

static int
PAL_POSIX_AddressSpace_obtainTransientRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	PAL_POSIX_AddressSpace *self = INTF_TO_CLASS(me);
	PAL_POSIX_Region *rgn;
	void *ptr;
	size_t size;
	int mapflags, mapprot, r;
	
	/* This is a transient region by definition*/
	flags |= RF_TRANSIENT;
	if(flags & RF_DMA)
	{
		/* PAL_POSIX_AddressSpace cannot currently provide DMA-supporting regions */
		return -E_NOMEM;
	}	
	size = count * (self->data.pagesize);
	mapprot = PROT_NONE;
	/* XXX MAP_ANON is not mandated by POSIX.1, this will need to be
	 * feature-tested
	 */
	mapflags = MAP_ANON | MAP_PRIVATE;
	if(flags & RF_READ)
	{
		mapprot |= PROT_READ;
	}
	if(flags & RF_WRITE)
	{
		mapprot |= PROT_WRITE;
	}
	if(flags & RF_EXEC)
	{
		mapprot |= PROT_EXEC;
	}
	ptr = mmap(NULL, size, mapprot, mapflags, -1, 0);
//	fprintf(stderr, "DEBUG: PAL::POSIX::AddressSpace: transient region of %llu pages (%llu bytes) => %p\n", (unsigned long long) count, (unsigned long long) size, ptr);
	if(!ptr)
	{
		return -E_NOMEM;
	}
	if((r = PAL_POSIX_Region_create(self, flags, owner, ptr, count, &rgn)) != E_SUCCESS)
	{
		munmap(ptr, size);
		return r;
	}
	/* XXX TODO: add to linked list of regions */
	*region = &(rgn->Region);
	return E_SUCCESS;
}

static STATUS
PAL_POSIX_AddressSpace_createContext(IAddressSpace *me, IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context)
{
	PAL_POSIX_AddressSpace *self = INTF_TO_CLASS(me);
	PAL_POSIX_Context *ctx;

	UNUSED__(thread);
	UNUSED__(stackBase);
	UNUSED__(stackSize);
	UNUSED__(ip);

	*context = NULL;
	ctx = PAL_POSIX_Context_create(self);
	if(!ctx)
	{
		return E_NOMEM;
	}
	ctx->data.thread = thread;
	ctx->data.stackLow = stackBase;
	ctx->data.stackHigh = stackBase + stackSize;
	ctx->data.entry = ip;
	PAL_POSIX_Context_setup(ctx);
	*context = &(ctx->Context);
	return E_SUCCESS;
}
