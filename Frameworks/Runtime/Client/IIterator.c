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

EXTERN_C STATUS IIterator_Client_next(IIterator *me);
EXTERN_C IObject *IIterator_Client_current(IIterator *me);

static struct IIterator_vtable_ IIterator_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IIterator),
	IIterator_Client_next,
	IIterator_Client_current
};

IIterator *
IIterator_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IIterator_Client_vtable;
	return (IIterator *) (void *) client;
}

STATUS 
IIterator_Client_next(IIterator *me)
{
	return ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IIterator_ID_next);
}

IObject *
IIterator_Client_current(IIterator *me)
{
	STATUS status;
	int outd;
	void *outptr;

	outd = -1;
	outptr = NULL;
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IIterator_ID_current, &outd)))
	{
		return NULL;
	}
	if(E_SUCCESS != (status = Runtime_Client_createFor(outd, &IID_IObject, &outptr)) || !outptr)
	{
		/* outd<IObject>::release() */
		ExSystemCall(outd, IObject_ID_release);
		return NULL;
	}
	return (IObject *) outptr;
}
