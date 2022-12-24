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

#include "p_PAL.h"

using namespace PAL::Simulator;

/* Constructor */

AddressSpace::AddressSpace(void)
{
	Platform::tracef("PAL::Simulator::AddressSpace()");
#if defined(HAVE_SYSCONF) && defined(_SC_PAGESIZE)
	pageSize_ = sysconf(_SC_PAGESIZE);
#elif defined(HAVE_GETPAGESIZE)
	pageSize_ = getpagesize();
#else
# warning PAL::Simulator::AddressSpace: no available API to determine default page size
	pageSize_ = 4096; /* Default to 4KB pages without other info */
#endif
	Platform::logf(LOG_DEBUG, "PAL::Simulator::AddressSpace: page size is %u", pageSize_);
}

/* IObject */
STATUS
AddressSpace::queryInterface(REFUUID riid, void **out)
{
	if(!memcmp(&riid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			/* no retain() because this class is a singleton */
			*out = static_cast<IObject *>(this);
		}
		return E_SUCCESS;
	}
	if(!memcmp(&riid, &IID_IAddressSpace, sizeof(UUID)))
	{
		if(out)
		{
			*out = static_cast<IAddressSpace *>(this);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

int
AddressSpace::obtainTransientRegion(size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	Region *rgn;
	void *ptr;
	size_t size;
	int mapflags, mapprot;
	
	/* This is a transient region by definition*/
	flags = (RegionFlags) (flags | RF_TRANSIENT);
	if(flags & RF_DMA)
	{
		/* PAL_POSIX_AddressSpace cannot currently provide DMA-supporting regions */
		return -E_NOMEM;
	}	
	size = count * pageSize_;
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
	ptr = ::mmap(NULL, size, mapprot, mapflags, -1, 0);
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::AddressSpace: transient region of %llu pages (%llu bytes) => %p", (unsigned long long) count, (unsigned long long) size, ptr);
	if(!ptr)
	{
		return -E_NOMEM;
	}
	rgn = new Region(this, flags, owner, ptr, count);
	/* XXX TODO: add to linked list of regions */
	*region = static_cast<IRegion *>(rgn);
	return E_SUCCESS;
}

STATUS
AddressSpace::createContext(IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context)
{
	Context *ctx;

	*context = NULL;
	ctx = new Context(this);
	if(!ctx)
	{
		return E_NOMEM;
	}
	ctx->thread = thread;
	ctx->stackBase = (uint8_t *) stackBase;
	ctx->stackSize = stackSize;
	ctx->entry = ip;
	ctx->setup();
	*context = static_cast<IContext *>(ctx);
	return E_SUCCESS;
}
