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

EXTERN_C STATUS IContainer_Client_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
EXTERN_C IIterator *IContainer_Client_iterator(IContainer *me);

static struct IContainer_vtable_ IContainer_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IContainer),
	IContainer_Client_resolve,
	IContainer_Client_iterator
};

IContainer *
IContainer_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IContainer_Client_vtable;
	return (IContainer *) (void *) client;
}

STATUS 
IContainer_Client_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	STATUS status;
	int outd;

	outd = -1;
	if(entry)
	{
		*entry = NULL;
	}
	if(E_SUCCESS != (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IContainer_ID_resolve, name, (entry ? &outd : NULL))))
	{
		return status;
	}
	if(entry)
	{
		if(E_SUCCESS != (status = Runtime_Client_createFor(outd, &IID_IDirectoryEntry, (void **) entry)))
		{
			/* outd<IObject>::release() */
			ExSystemCall(outd, IObject_ID_release);
		}
	}
	return status;
}

EXTERN_C IIterator *IContainer_Client_iterator(IContainer *me)
{
	int outd;
	void *outptr;

	outd = -1;
	outptr = NULL;
	if(E_SUCCESS == ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IContainer_ID_iterator, &outd))
	{
		return NULL;
	}
	if(E_SUCCESS != Runtime_Client_createFor(outd, &IID_IIterator, &outptr))
	{
		/* outd<IObject>::release() */
		ExSystemCall(outd, IObject_ID_release);
		return NULL;
	}
	return (IIterator *) outptr;
}

#endif /*!#if !RUNTIME_BUILD_EXEC*/

#if !RUNTIME_BUILD_SIMULATOR
#define INITGUID                       1
#include <Executive/initguid.h>

# include <Executive/IContainer.h>
#endif

