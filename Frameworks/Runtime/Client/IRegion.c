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

#include "p_Client.h"

#if !RUNTIME_BUILD_EXEC

#include <stdio.h>

static void IRegion_Client_init_(IRegion_Client *client, int descriptor);

static REFCOUNT IRegion_Client_retain_noop(IRegion *me);
static REFCOUNT IRegion_Client_release_noop(IRegion *me);

static RegionFlags IRegion_Client_flags(IRegion *me);
static STATUS IRegion_Client_queryOwnerInterface(IRegion *me, REFUUID iid, void **out);
static uint8_t *IRegion_Client_base(IRegion *me);
static size_t IRegion_Client_pages(IRegion *me);
static size_t IRegion_Client_bytes(IRegion *me);

static struct IRegion_vtable_ IRegion_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IRegion),
	IRegion_Client_flags,
	IRegion_Client_queryOwnerInterface,
	IRegion_Client_base,
	IRegion_Client_pages,
	IRegion_Client_bytes
};

/* IRegion is required to bootstrap the allocator, so ensure one is statically allocated */

static IRegion_Client IRegion_Client_initial, *firstRegion;

static struct IRegion_vtable_ IRegion_Client_vtable_static = {
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

	if(!firstRegion)
	{
		IRegion_Client_init_(&IRegion_Client_initial, descriptor);
		firstRegion = &IRegion_Client_initial;
		return &(firstRegion->Region);
	}
	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IRegion_Client_vtable;
	return (IRegion *) (void *) client;
}

static void
IRegion_Client_init_(IRegion_Client *client, int descriptor)
{
	client->data.refCount = 1;
	client->data.descriptor = descriptor;
	client->data.vtable = &IRegion_Client_vtable_static;
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

	if(E_SUCCESS != ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 3, &flags))
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
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 4, iid, (out ? &outd : NULL))))
	{
		return status;
	}
	if(out)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, iid, out)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, 2);
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
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 5, &out);
	fprintf(stderr, "IRegion::base(%p) => %p\n", me, out);
	return out;
}

/* 6 = size_t pages(void); */
static size_t
IRegion_Client_pages(IRegion *me)
{
	size_t out;

	out = (size_t) -1;
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 6, &out);
	return out;
}

/* 7 = size_t bytes(void); */
static size_t
IRegion_Client_bytes(IRegion *me)
{
	size_t out;

	out = (size_t) -1;
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 7, &out);
	return out;
}

#endif /*!RUNTIME_BUILD_EXEC*/

#define INITGUID                       1
#include <Executive/initguid.h>

#if !RUNTIME_BUILD_SIMULATOR
#include <Executive/IRegion.h>
#endif


