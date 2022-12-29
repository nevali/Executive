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

struct IObject_vtable_ Runtime_Client_IObject_vtable = {
	Runtime_Client_queryInterface,
	Runtime_Client_release,
	Runtime_Client_retain
};

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
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IObject_ID_queryInterface, iid, &outd)))
	{
		return status;
	}
	if(E_SUCCESS != (status = Runtime_Client_createFor(outd, iid, out)))
	{
		/* outd<IObject>::release() */
		ExSystemCall(outd, IObject_ID_release);
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
		ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IObject_ID_release);
		RtMemFree(me);
	});
}
