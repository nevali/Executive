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

#if !RUNTIME_BUILD_EXEC

static STATUS IDirectoryEntry_Client_queryTargetInterface(IDirectoryEntry *self, REFUUID iid, void **out);
static const char *IDirectoryEntry_Client_name(IDirectoryEntry *self);
static void IDirectoryEntry_Client_classid(IDirectoryEntry *self, UUID *classid);
static DirectoryEntryFlags IDirectoryEntry_Client_flags(IDirectoryEntry *self);
static STATUS IDirectoryEntry_Client_setFlags(IDirectoryEntry *self, DirectoryEntryFlags flags);

static struct IDirectoryEntry_vtable_ IDirectoryEntry_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, IDirectoryEntry),
	IDirectoryEntry_Client_queryTargetInterface,
	IDirectoryEntry_Client_name,
	IDirectoryEntry_Client_classid,
	IDirectoryEntry_Client_flags,
	IDirectoryEntry_Client_setFlags
};

/* IDirectoryEntry */

IDirectoryEntry *
IDirectoryEntry_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &IDirectoryEntry_Client_vtable;
	return (IDirectoryEntry *) (void *) client;
}

static STATUS 
IDirectoryEntry_Client_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
	int outd = -1;
	STATUS status;

	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IDirectoryEntry_ID_queryTargetInterface,
		iid, (out ? &outd : NULL))))
	{
		RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(out, outd, iid, status);
	}
	return status;
}

static const char *
IDirectoryEntry_Client_name(IDirectoryEntry *me)
{
	UNUSED__(me);

	return "(no names yet)";
}

static void
IDirectoryEntry_Client_classid(IDirectoryEntry *me, UUID *out)
{
	(void) ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IDirectoryEntry_ID_classid, out);
}

static DirectoryEntryFlags
IDirectoryEntry_Client_flags(IDirectoryEntry *me)
{
	DirectoryEntryFlags flags;

	if(E_SUCCESS != ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IDirectoryEntry_ID_flags, &flags))
	{
		flags = DEF_INVALID;
	}
	return flags;
}

static STATUS
IDirectoryEntry_Client_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags)
{
	return ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, IDirectoryEntry_ID_setFlags, flags);
}

#endif /*!RUNTIME_BUILD_EXEC*/

#if !RUNTIME_BUILD_SIMULATOR
#define INITGUID                       1
#include <Executive/initguid.h>

# include <Executive/IDirectoryEntry.h>
#endif
