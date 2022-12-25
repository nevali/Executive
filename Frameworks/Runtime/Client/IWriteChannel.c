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

static size_t IWriteChannel_Client_send(IWriteChannel *me, const uint8_t *buf, size_t buflen);
static size_t IWriteChannel_Client_write(IWriteChannel *me, const char *str);
static size_t IWriteChannel_Client_writeLn(IWriteChannel *me, const char *str);

static struct IWriteChannel_vtable_ IWriteChannel_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IWriteChannel),
	IWriteChannel_Client_send,
	IWriteChannel_Client_write,
	IWriteChannel_Client_writeLn
};

IWriteChannel *
IWriteChannel_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IWriteChannel_Client_vtable;
	return (IWriteChannel *) (void *) client;
}

static size_t
IWriteChannel_Client_send(IWriteChannel *me, const uint8_t *buf, size_t buflen)
{
	STATUS status;

	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IWriteChannel_ID_send, buf, &buflen)))
	{
		return buflen;
	}
	return 0;
}

static size_t
IWriteChannel_Client_write(IWriteChannel *me, const char *str)
{
	STATUS status;
	size_t buflen;

	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IWriteChannel_ID_write, str, &buflen)))
	{
		return buflen;
	}
	return 0;
}

static size_t
IWriteChannel_Client_writeLn(IWriteChannel *me, const char *str)
{
	STATUS status;
	size_t buflen;

	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IWriteChannel_ID_writeLn, str, &buflen)))
	{
		return buflen;
	}
	return 0;
}

#endif /*!RUNTIME_BUILD_EXEC*/

#define INITGUID                       1
#include <Executive/initguid.h>

#if !RUNTIME_BUILD_SIMULATOR
# include <Executive/IWriteChannel.h>
#endif
