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

static THREADID IThread_Client_id(IThread *me);
static ThreadFlags IThread_Client_flags(IThread *me);
static STATUS IThread_Client_task(IThread *me, REFUUID iid, void **out);
static STATUS IThread_Client_job(IThread *me, REFUUID iid, void **out);
static STATUS IThread_Client_ns(IThread *me, REFUUID iid, void **out);
static void IThread_Client_yield(IThread *me);

static struct IThread_vtable_ IThread_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IThread),
	IThread_Client_id,
	IThread_Client_flags,
	IThread_Client_task,
	IThread_Client_job,
	IThread_Client_ns,
	IThread_Client_yield
};

IThread *
IThread_Client_create(int descriptor)
{
	Runtime_Client *client;

	client = Runtime_Client_create(descriptor);
	client->data.vtable = &IThread_Client_vtable;
	return (IThread *) (void *) client;
}

/* 3 = THREADID id(void); */
static THREADID
IThread_Client_id(IThread *me)
{
	THREADID id;

	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 3, &id);
	return id;
}

/* 4 = ThreadFlags flags(void); */
static ThreadFlags
IThread_Client_flags(IThread *me)
{
	ThreadFlags flags;

	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 4, &flags);
	return flags;
}

/* 5 = STATUS task([in] REFUUID iid, [out, iid_is(iid)] void **out); */
static STATUS
IThread_Client_task(IThread *me, REFUUID iid, void **out)
{
	int outd;
	STATUS status;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 5, iid, &outd)))
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

/* 6 = STATUS job([in] REFUUID iid, [out, iid_is(iid)] void **out); */
static STATUS
IThread_Client_job(IThread *me, REFUUID iid, void **out)
{
	int outd;
	STATUS status;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 6, iid, &outd)))
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

/* 7 = STATUS ns([in] REFUUID iid, [out, iid_is(iid)] void **out); */
static STATUS
IThread_Client_ns(IThread *me, REFUUID iid, void **out)
{
	int outd;
	STATUS status;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 7, iid, &outd)))
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

/* 8 = [local] void yield(void); */
static void
IThread_Client_yield(IThread *me)
{
	ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 8);
}

#endif /*!RUNTIME_BUILD_EXEC*/

#define INITGUID                       1
#include <Executive/initguid.h>

#if !RUNTIME_BUILD_SIMULATOR
# include <Runtime/IThread.h>
#endif

