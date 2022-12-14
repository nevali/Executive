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

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_MemoryManager *)((void *)(i))

/* IObject */

static int PAL_POSIX_MemoryManager_queryInterface(IMemoryManager *self, REFUUID riid, void **ptr);
static int32_t PAL_POSIX_MemoryManager_retain(IMemoryManager *self);
static int32_t PAL_POSIX_MemoryManager_release(IMemoryManager *self);

/* IMemoryManager */

static int PAL_POSIX_MemoryManager_regionForPtr(IMemoryManager *self, void *ptr, IRegion **out);
static int PAL_POSIX_MemoryManager_pageSize(IMemoryManager *self);
static int PAL_POSIX_MemoryManager_obtainRegion(IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);
static int PAL_POSIX_MemoryManager_obtainTransientRegion(IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);

static struct IMemoryManager_vtable_ PAL_POSIX_MemoryManager_vtable = {
	PAL_POSIX_MemoryManager_queryInterface,
	PAL_POSIX_MemoryManager_retain,
	PAL_POSIX_MemoryManager_release,
	PAL_POSIX_MemoryManager_regionForPtr,
	PAL_POSIX_MemoryManager_pageSize,
	PAL_POSIX_MemoryManager_obtainRegion,
	PAL_POSIX_MemoryManager_obtainTransientRegion
};

PAL_POSIX_MemoryManager PAL_POSIX_memoryManager;

/* INTERNAL: perform one-time initialisation */
void
PAL_POSIX_MemoryManager_init(void)
{
	memset(&PAL_POSIX_memoryManager, 0, sizeof(PAL_POSIX_memoryManager));
	PAL_POSIX_memoryManager.MemoryManager.lpVtbl = &PAL_POSIX_MemoryManager_vtable;
#if defined(HAVE_SYSCONF) && defined(_SC_PAGESIZE)
	PAL_POSIX_memoryManager.data.pagesize = sysconf(_SC_PAGESIZE);
#elif defined(HAVE_GETPAGESIZE)
	PAL_POSIX_memoryManager.data.pagesize = getpagesize();
#else
# warning PAL_POSIX_MemoryManager: no available API to determine default page size
	PAL_POSIX_memoryManager.data.pagesize = 4096; /* Default to 4KB pages without other info */
#endif
}

static int
PAL_POSIX_MemoryManager_queryInterface(IMemoryManager *self, REFUUID riid, void **ptr)
{
	PAL_POSIX_MemoryManager *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, &IID_IObject, sizeof(UUID)))
	{
		if(*ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(me->Object);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IMemoryManager, sizeof(UUID)))
	{
		if(*ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(me->MemoryManager);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static int32_t
PAL_POSIX_MemoryManager_retain(IMemoryManager *self)
{
	UNUSED__(self);
	
	/* PAL_POSIX_MemoryManager is a singleton */
	return 2;
}

static int32_t
PAL_POSIX_MemoryManager_release(IMemoryManager *self)
{
	UNUSED__(self);

	/* PAL_POSIX_MemoryManager is a singleton */
	return 1;
}

static int
PAL_POSIX_MemoryManager_regionForPtr(IMemoryManager *self, void *ptr, IRegion **out)
{
	PAL_POSIX_MemoryManager *me = INTF_TO_CLASS(self);

	UNUSED__(ptr);
	UNUSED__(me);

	if(out)
	{
		*out = NULL;
	}

	return E_NOTIMPL;
}

static int
PAL_POSIX_MemoryManager_pageSize(IMemoryManager *self)
{
	PAL_POSIX_MemoryManager *me = INTF_TO_CLASS(self);

	return me->data.pagesize;
}

static int
PAL_POSIX_MemoryManager_obtainRegion(IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	if(flags & RF_TRANSIENT)
	{
		return PAL_POSIX_MemoryManager_obtainTransientRegion(self, count, flags, owner, region);
	}
	/* PAL_POSIX_MemoryManager cannot currently handle non-transient mappings */
	return E_NOMEM;
}

static int
PAL_POSIX_MemoryManager_obtainTransientRegion(IMemoryManager *self, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	PAL_POSIX_MemoryManager *me = INTF_TO_CLASS(self);
	PAL_POSIX_Region *rgn;
	void *ptr;
	size_t size;
	int mapflags, mapprot, r;
	
	/* This is a transient region by definition*/
	flags |= RF_TRANSIENT;
	if(flags & RF_DMA)
	{
		/* PAL_POSIX_MemoryManager cannot currently provide DMA-supporting regions */
		return -E_NOMEM;
	}	
	size = count * (me->data.pagesize);
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
//	fprintf(stderr, "DEBUG: PAL::POSIX::MemoryManager: transient region of %llu pages (%llu bytes) => %p\n", (unsigned long long) count, (unsigned long long) size, ptr);
	if(!ptr)
	{
		return -E_NOMEM;
	}
	if((r = PAL_POSIX_Region_create(me, flags, owner, ptr, count, &rgn)) != E_SUCCESS)
	{
		munmap(ptr, size);
		return r;
	}
	/* XXX TODO: add to linked list of regions */
	*region = &(rgn->Region);
	return E_SUCCESS;
}
