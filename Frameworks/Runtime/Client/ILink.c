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

static STATUS ILink_Client_target(ILink *me, char *buf, size_t bufsize);

static struct ILink_vtable_ ILink_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, ILink),
	ILink_Client_target
};

ILink *
ILink_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &ILink_Client_vtable;
	return (ILink *) (void *) client;
}

STATUS 
ILink_Client_target(ILink *me, char *buf, size_t bufsize)
{
	return ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, ILink_ID_target, buf, bufsize);
}
