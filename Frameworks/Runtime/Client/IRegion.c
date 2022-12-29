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

#include "p_Client.h"

static void IRegion_Client_init_(IRegion_Client *client, int descriptor);

static REFCOUNT IRegion_Client_retain_noop(IRegion *me);
static REFCOUNT IRegion_Client_release_noop(IRegion *me);

static RegionFlags IRegion_Client_flags(IRegion *me);
static STATUS IRegion_Client_queryOwnerInterface(IRegion *me, REFUUID iid, void **out);
static uint8_t *IRegion_Client_base(IRegion *me);
static size_t IRegion_Client_pages(IRegion *me);
static size_t IRegion_Client_bytes(IRegion *me);

/* Because IRegion is used as part of the interface between the memory manager
 * (via the AddressSpace), we can't use the allocator to obtain memory for
 * client structures unless and until we know it has room to do so
 *
 * therefore we allocate structures in blocks of four, and allocate the next
 * block as soon as the first structure has been filled, to give ourselves
 * plenty of headroom (this allows for the case where attempting to allocate
 * the next block triggers a request for a new region)
 */

#define REGION_BLOCK_SIZE              4

struct RegionBlock
{
	struct RegionBlock *next;
	IRegion_Client client[REGION_BLOCK_SIZE];
};

static struct RegionBlock regionAnchors, *lastRegionBlock;

static struct IRegion_vtable_ IRegion_Client_vtable = {
	(STATUS (*)(IRegion *, REFUUID, void **)) &Runtime_Client_queryInterface,
	IRegion_Client_retain_noop,
	IRegion_Client_release_noop,
	IRegion_Client_flags,
	IRegion_Client_queryOwnerInterface,
	IRegion_Client_base,
	IRegion_Client_pages,
	IRegion_Client_bytes
};

IRegion *
IRegion_Client_create(int descriptor)
{
	Runtime_Client *client;
	size_t c;
	client = NULL;

	RTTRACEF(("IRegion::Client::create(%d)", descriptor));
	if(NULL == lastRegionBlock)
	{
		/* Obtaining a region for the very first time */
		lastRegionBlock = &regionAnchors;
		client = &(regionAnchors.client[0]);
	}
	else
	{
		for(c = 0; c < REGION_BLOCK_SIZE; c++)
		{
			if(0 == lastRegionBlock->client[c].data.descriptor)
			{
				client = &(regionAnchors.client[c]);
				break;
			}
		}
	}
	if(!client)
	{
		/* this should not happen, in theory */
		return NULL;
	}
	IRegion_Client_init_(client, descriptor);
	return (IRegion *) (void *) client;
}

/* INTERNAL: called by the allocator after allocation has completed, to trigger
 * the creation of an additional region block if needed */
void
IRegion_Client_update_(void)
{
	RTTRACEF(("IRegion::Client::update_()"));
}

static void
IRegion_Client_init_(IRegion_Client *client, int descriptor)
{
	client->data.refCount = 1;
	client->data.descriptor = descriptor;
	client->data.vtable = &IRegion_Client_vtable;
}

/* 1 = REFCOUNT retain(void); */
static REFCOUNT
IRegion_Client_retain_noop(IRegion *me)
{
	UNUSED__(me);

	return 2;
}

/* 2 = REFCOUNT release(void); */
static REFCOUNT
IRegion_Client_release_noop(IRegion *me)
{
	UNUSED__(me);

	return 1;
}

/* 3 = RegionFlags flags(void); */

static RegionFlags
IRegion_Client_flags(IRegion *me)
{
	RegionFlags flags;

	if(E_SUCCESS != ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IRegion_ID_flags, &flags))
	{
		return 0;
	}
	return flags;
}

/* 4 = int queryOwnerInteface([in] REFUUID iid, [out, iid_is(iid)] void **out); */

static STATUS
IRegion_Client_queryOwnerInterface(IRegion *me, REFUUID iid, void **out)
{
	STATUS status;
	int outd;

	outd = -1;
	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IRegion_ID_queryOwnerInterface, iid, (out ? &outd : NULL))))
	{
		return status;
	}
	if(out)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, iid, out)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, IObject_ID_release, NULL, NULL, NULL, NULL, NULL, NULL);
		}
	}
	return status;
}

/* 5 = uint8_t *base(void); */
static uint8_t *
IRegion_Client_base(IRegion *me)
{
	uint8_t *out;

	out = NULL;
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IRegion_ID_base, &out);
	RTLOGF((LOG_DEBUG7, "IRegion::base(%p) => %p\n", me, out));
	return out;
}

/* 6 = size_t pages(void); */
static size_t
IRegion_Client_pages(IRegion *me)
{
	size_t out;

	out = (size_t) -1;
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IRegion_ID_pages, &out);
	return out;
}

/* 7 = size_t bytes(void); */
static size_t
IRegion_Client_bytes(IRegion *me)
{
	size_t out;

	out = (size_t) -1;
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IRegion_ID_bytes, &out);
	return out;
}
