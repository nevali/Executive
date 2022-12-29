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
	*out = NULL;
	if(RtUuidEqual(iid, &IID_IObject))
	{
		*out = Runtime_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IThread))
	{
		*out = IThread_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_INamespace))
	{
		*out = INamespace_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IAddressSpace))
	{
		*out = IAddressSpace_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IRegion))
	{
		*out = IRegion_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IContainer))
	{
		*out = IContainer_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IWriteChannel))
	{
		*out = IWriteChannel_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IIterator))
	{
		*out = IIterator_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_IDirectoryEntry))
	{
		*out = IDirectoryEntry_Client_create(descriptor);
	}
	else if(RtUuidEqual(iid, &IID_ILink))
	{
		*out = ILink_Client_create(descriptor);
	}
	else
	{
		RTLOGF((LOG_WARNING, "Runtime: WARNING: iid:" UUID_PRINTF_FORMAT " is not supported", UUID_PRINTF_ARGS(iid)));
		return E_NOTIMPL;
	}
	if(*out)
	{
		return E_SUCCESS;
	}
	RTLOGF((LOG_ERROR, "Runtime: ERROR: constructor for iid:" UUID_PRINTF_FORMAT " failed"));
	return E_NOTIMPL;
}
