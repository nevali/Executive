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

static TASKID ITask_Client_id(ITask *me);
static TaskFlags ITask_Client_flags(ITask *me);
static STATUS ITask_Client_job(ITask *me, REFUUID iid, void **out);
static STATUS ITask_Client_ns(ITask *me, REFUUID iid, void **out);
static STATUS ITask_Client_addressSpace(ITask *me, REFUUID iid, void **out);

static struct ITask_vtable_ ITask_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, ITask),
	ITask_Client_id,
	ITask_Client_flags,
	ITask_Client_ns,
	ITask_Client_job,
	ITask_Client_addressSpace
};

ITask *
ITask_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &ITask_Client_vtable;
	return (ITask *) (void *) client;
}

/* 3 = TASKID id(void); */

static TASKID
ITask_Client_id(ITask *me)
{
	TASKID id;
	STATUS status;

	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 3, &id)))
	{
		return (TASKID) status;
	}
	return id;
}

/* 4 = TaskFlags flags(void); */

static TaskFlags
ITask_Client_flags(ITask *me)
{
	TaskFlags id;
	STATUS status;

	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, 3, &id)))
	{
		return (TaskFlags) 0;
	}
	return id;
}

/* 5 = STATUS ns([in] REFUUID iid, [out, iid_is(iid)] void **out); */

static STATUS
ITask_Client_ns(ITask *me, REFUUID iid, void **out)
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
ITask_Client_job(ITask *me, REFUUID iid, void **out)
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

/* 7 = STATUS addressSpace([in] REFUUID iid, [out, iid_is(iid)] void **out); */

static STATUS
ITask_Client_addressSpace(ITask *me, REFUUID iid, void **out)
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

#endif /*!RUNTIME_BUILD_EXEC*/

#define INITGUID                       1
#include <Executive/initguid.h>

#if !RUNTIME_BUILD_SIMULATOR
# include <Executive/ITask.h>
#endif

