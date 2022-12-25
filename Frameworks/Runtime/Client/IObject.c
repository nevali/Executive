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

static struct IObject_vtable_ Runtime_Client_IObject_vtable = {
	Runtime_Client_queryInterface,
	Runtime_Client_release,
	Runtime_Client_retain
};

Runtime_Client *
Runtime_Client_create(int descriptor)
{
	Runtime_Client *p;

	if(NULL == (p = RtMemAlloc(sizeof(Runtime_Client))))
	{
		return NULL;
	}
	p->data.vtable = &Runtime_Client_IObject_vtable;
	p->data.refCount = 1;
	p->data.descriptor = descriptor;
	return p;
}

STATUS
Runtime_Client_createFor(int descriptor, REFUUID iid, void **out)
{
	/* XXX check if descriptor is already in our object table, if so,
	 * just retain the existing object
	 */
	if(RtUuidEqual(iid, &IID_IObject))
	{
		*out = Runtime_Client_create(descriptor);
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_IThread))
	{
		*out = IThread_Client_create(descriptor);
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_INamespace))
	{
		*out = INamespace_Client_create(descriptor);
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_IAddressSpace))
	{
		*out = IAddressSpace_Client_create(descriptor);
		return E_SUCCESS;
	}
	if(RtUuidEqual(iid, &IID_IRegion))
	{
		*out = IRegion_Client_create(descriptor);
		return E_SUCCESS;
	}
	/* XXX */
	*out = NULL;
	return E_NOTIMPL;
}

/* 0 = [local] STATUS queryInterface([in] REFUUID iid, [out, iid_is(iid) void **out]) */
STATUS
Runtime_Client_queryInterface(IObject *me, REFUUID iid, void **out)
{
	int outd;
	STATUS status;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 0, iid, &outd)))
	{
		return status;
	}
	if(E_SUCCESS != (status = Runtime_Client_createFor(outd, iid, out)))
	{
		/* outd<IObject>::release() */
		ExSystemCall(outd, 2);
	}
	return status;
}

/* 1 = [local] retain(); */
REFCOUNT
Runtime_Client_retain(IObject *me)
{
	RUNTIME_RETAIN(Runtime_Client);
}

/* 2 = [local] release(); */
REFCOUNT
Runtime_Client_release(IObject *me)
{
	RUNTIME_RELEASE(Runtime_Client, {
		ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 2);
		RtMemFree(me);
	});
}

#endif /*!RUNTIME_BUILD_EXEC*/

#define INITGUID                       1
#include <Executive/initguid.h>

#if !RUNTIME_BUILD_SIMULATOR
# include <Runtime/IObject.h>
#endif
