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

static STATUS IAddressSpace_Client_regionFromPointer(IAddressSpace *me, void *ptr, IRegion **region);
static int IAddressSpace_Client_pageSize(IAddressSpace *me);
static STATUS IAddressSpace_Client_obtainRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);
static STATUS IAddressSpace_Client_obtainTransientRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region);
static STATUS IAddressSpace_Client_createContext(IAddressSpace *me, IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context);

static struct IAddressSpace_vtable_ IAddressSpace_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IAddressSpace),
	IAddressSpace_Client_regionFromPointer,
	IAddressSpace_Client_pageSize,
	IAddressSpace_Client_obtainRegion,
	IAddressSpace_Client_obtainTransientRegion,
	IAddressSpace_Client_createContext
};

IAddressSpace *
IAddressSpace_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IAddressSpace_Client_vtable;
	return (IAddressSpace *) (void *) client;
}

void
IAddressSpace_Client_init_(IAddressSpace_Client *client, int descriptor)
{
	client->data.refCount = 1;
	client->data.descriptor = descriptor;
	client->data.vtable = &IAddressSpace_Client_vtable;
}

/* 3 = STATUS regionFromPointer([in] void *ptr, [out] IRegion **region); */

static STATUS
IAddressSpace_Client_regionFromPointer(IAddressSpace *me, void *ptr, IRegion **region)
{
	STATUS status;
	int outd;

	outd = -1;
	if(region)
	{
		*region = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IAddressSpace_ID_regionFromPointer, ptr, (region ? &outd : NULL))))
	{
		return status;
	}
	if(region)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, &IID_IRegion, (void **) region)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, 2);
		}
	}
	return status;
}

/* 4 = int pageSize(void); */

static int
IAddressSpace_Client_pageSize(IAddressSpace *me)
{
	STATUS status;
	int out;

	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IAddressSpace_ID_pageSize, &out)))
	{
		return (int) status;
	}
	return out;
}

/* 5 = int obtainRegion([in] size_t count, [in] RegionFlags flags, [in] IRegionHolder *owner, [out] IRegion **region); */

static STATUS
IAddressSpace_Client_obtainRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	STATUS status;
	int outd;

	outd = -1;
	if(region)
	{
		*region = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IAddressSpace_ID_obtainRegion, count, flags, owner, (region ? &outd : NULL))))
	{
		return status;
	}
	if(region)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, &IID_IRegion, (void **) region)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, 2);
		}
	}
	return status;
}

/* 6 = int obtainTransientRegion([in] size_t count, [in] RegionFlags flags, [in] IRegionHolder *owner, [out] IRegion **region); */

static STATUS
IAddressSpace_Client_obtainTransientRegion(IAddressSpace *me, size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region)
{
	STATUS status;
	int outd;

	outd = -1;
	if(region)
	{
		*region = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IAddressSpace_ID_obtainTransientRegion, count, flags, owner, (region ? &outd : NULL))))
	{
		return status;
	}
	if(region)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, &IID_IRegion, (void **) region)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, 2);
		}
	}
	return status;
}

/* 7 = STATUS createContext([in] IThread *thread, [in] void *stackBase, [in] size_t stackSize, [in] ThreadEntrypoint ip, [out] IContext **context); */

static STATUS
IAddressSpace_Client_createContext(IAddressSpace *me, IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context)
{
	UNUSED__(me);
	UNUSED__(thread);
	UNUSED__(stackBase);
	UNUSED__(stackSize);
	UNUSED__(ip);

	if(context)
	{
		*context = NULL;
	}

	return E_NOTIMPL;
}
