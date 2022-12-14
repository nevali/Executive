
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

#define INTF_TO_CLASS(i)               (PAL_POSIX_Region *)((void *)(i))

static void PAL_POSIX_Region_destroy(PAL_POSIX_Region *me);

/* IObject */

static int PAL_POSIX_Region_queryInterface(IRegion *self, REFUUID riid, void **ptr);
static int32_t PAL_POSIX_Region_retain(IRegion *self);
static int32_t PAL_POSIX_Region_release(IRegion *self);

/* IRegion */

static RegionFlags PAL_POSIX_Region_flags(IRegion *self);
static int PAL_POSIX_Region_queryOwnerInterface(IRegion *self, REFUUID riid, void **ptr);
static uint8_t *PAL_POSIX_Region_base(IRegion *self);
static size_t PAL_POSIX_Region_pages(IRegion *self);
static size_t PAL_POSIX_Region_size(IRegion *self);

static struct IRegion_vtable_ PAL_POSIX_Region_vtable = {
	PAL_POSIX_Region_queryInterface,
	PAL_POSIX_Region_retain,
	PAL_POSIX_Region_release,
	PAL_POSIX_Region_flags,
	PAL_POSIX_Region_queryOwnerInterface,
	PAL_POSIX_Region_base,
	PAL_POSIX_Region_pages,
	PAL_POSIX_Region_size
};

/* Internal to the memory manager:
 *   PAL_POSIX_Region_create() is used by the implementation of the hosted
 *   memory manager's obtainRegion() and obtainTransientRegion() methods to
 *   allocate and initialise a new instance (supporting IRegion) which
 *   represents and encapsulates an owned region within the memory map.
 * 
 *   Because this memory manager is hosted, we can safely use malloc()
 *   and friends to provide heap for our Region instances; a freestanding
 *   version would have to find somewhere to allocate the structures from
 *   itself (e.g., preallocating a page at initialisation-time and storing
 *   aligned structures within in, or even just linking with a small malloc()
 *   implementation for internal use)
 */
int
PAL_POSIX_Region_create(PAL_POSIX_MemoryManager *mm, RegionFlags flags, IRegionHolder *owner, void *ptr, size_t count, PAL_POSIX_Region **region)
{
	PAL_POSIX_Region *p;

	p = (PAL_POSIX_Region *) calloc(1, sizeof(PAL_POSIX_Region));
	if(!p)
	{
		return -E_NOMEM;
	}
	p->Region.lpVtbl = &PAL_POSIX_Region_vtable;
	p->data.mm = mm;
	p->data.flags = flags;
	p->data.refcount = 1;
	/* The holder MUST exist for longer than the lifespan of the region */
	p->data.holder = owner;
	p->data.base = (uint8_t *) ptr;
	p->data.count = count;
	if(owner)
	{
		owner->lpVtbl->retain(owner);
	}
	*region = p;
	return 0;
}

static void
PAL_POSIX_Region_destroy(PAL_POSIX_Region *me)
{
	if(me->data.base)
	{
		munmap(me->data.base, me->data.count * me->data.mm->data.pagesize);
	}
	free(me);
}

/* IObject */

static int
PAL_POSIX_Region_queryInterface(IRegion *self, REFUUID iid, void **out)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)))
	{
		IRegion_retain(self);
		if(out)
		{
			*out = &(me->Object);
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(iid, &IID_IRegion, sizeof(UUID)))
	{
		IRegion_retain(self);
		if(out)
		{
			*out = &(me->Region);
		}
		return E_SUCCESS;
	}
	/* Unsupported interface*/
	return E_NOENT;
}

static int32_t
PAL_POSIX_Region_retain(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	/* XXX atomics */
	me->data.refcount++;

	return me->data.refcount;
}

static int32_t
PAL_POSIX_Region_release(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	/* XXX atomics */
	me->data.refcount--;
	if(!me->data.refcount)
	{
		PAL_POSIX_Region_destroy(me);
		return 0;
	}
	return me->data.refcount;
}


/* IRegion */

static RegionFlags
PAL_POSIX_Region_flags(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	return me->data.flags;
}

static int
PAL_POSIX_Region_queryOwnerInterface(IRegion *self, REFUUID iid, void **out)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	return IRegionHolder_queryInterface(me->data.holder, iid, out);
}

static uint8_t *
PAL_POSIX_Region_base(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	return me->data.base;
}

static size_t
PAL_POSIX_Region_pages(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	return me->data.count;
}

static size_t
PAL_POSIX_Region_size(IRegion *self)
{
	PAL_POSIX_Region *me = INTF_TO_CLASS(self);

	return me->data.count * me->data.mm->data.pagesize;
}
