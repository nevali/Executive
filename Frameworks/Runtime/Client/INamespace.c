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

static STATUS INamespace_Client_resolveEntry(INamespace *me, const char *path, IContainer *scope, IDirectoryEntry **dentry);
static STATUS INamespace_Client_resolveContainer(INamespace *me, const char *path, IContainer *scope, IContainer **container, const char **basename);
static STATUS INamespace_Client_open(INamespace *me, const char *path, IContainer *scope, REFUUID iid, void **out);
static STATUS INamespace_Client_createCall(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, REFUUID iid, void **out);
static STATUS INamespace_Client_add(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, IObject *target);
static STATUS INamespace_Client_createLink(INamespace *me, const char *path, IContainer *scope, const char *target, bool force);
static STATUS INamespace_Client_setFlags(INamespace *me, const char *path, IContainer *scope, DirectoryEntryFlags flags);

static struct INamespace_vtable_ INamespace_Client_vtable = {
	RUNTIME_VTABLE_IOBJECT(Runtime_Client, INamespace),
	(STATUS (*)(INamespace *, const char *, IDirectoryEntry **)) &IContainer_Client_resolve,
	(IIterator *(*)(INamespace *)) &IContainer_Client_iterator,
	INamespace_Client_resolveEntry,
	INamespace_Client_resolveContainer,
	INamespace_Client_open,
	INamespace_Client_createCall,
	INamespace_Client_add,
	INamespace_Client_createLink,
	INamespace_Client_setFlags
};

INamespace *
INamespace_Client_create(int descriptor)
{
	Runtime_Client *client;

	if(!(client = Runtime_Client_create(descriptor)))
	{
		return NULL;
	}
	client->data.vtable = &INamespace_Client_vtable;
	return (INamespace *) (void *) client;
}

static STATUS
INamespace_Client_resolveEntry(INamespace *me, const char *path, IContainer *scope, IDirectoryEntry **dentry)
{
	int scope_d, dentry_d;
	STATUS status;

	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { return E_INVAL; });
	RUNTIME_CLIENT_INIT_OUT_DESCRIPTOR(dentry, dentry_d);
	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_resolveEntry, path, scope_d, &dentry_d)))
	{
		RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(dentry, dentry_d, &IID_IDirectoryEntry, status);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;
}

static STATUS
INamespace_Client_resolveContainer(INamespace *me, const char *path, IContainer *scope, IContainer **container, const char **basename)
{
	int scope_d, container_d;
	STATUS status;

	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { return E_INVAL; });
	RUNTIME_CLIENT_INIT_OUT_DESCRIPTOR(container, container_d);
	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_resolveContainer, path, scope_d, &container_d, basename)))
	{
		RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(container, container_d, &IID_IContainer, status);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;
}

static STATUS INamespace_Client_open(INamespace *me, const char *path, IContainer *scope, REFUUID iid, void **out)
{
	int scope_d, out_d;
	STATUS status;

	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { return E_INVAL; });
	RUNTIME_CLIENT_INIT_OUT_DESCRIPTOR(out, out_d);
	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_open, path, scope_d, iid, &out_d)))
	{
		RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(out, out_d, iid, status);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;
}

static STATUS
INamespace_Client_createCall(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, REFUUID iid, void **out)
{
	int scope_d, out_d;
	STATUS status;

	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { return E_INVAL; });
	RUNTIME_CLIENT_INIT_OUT_DESCRIPTOR(out, out_d);
	if(E_SUCCESS == (status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_create, path, scope_d, clsid, iid, &out_d)))
	{
		RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(out, out_d, iid, status);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;

}

static STATUS
INamespace_Client_add(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, IObject *target)
{
	int scope_d, target_d;
	STATUS status;

	status = E_SUCCESS;
	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { status = E_INVAL; });
	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(target, target_d, { status = E_INVAL; });
	if(E_SUCCESS == status)
	{
		status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_add, path, scope_d, clsid, target_d);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(target, target_d);
	return status;
}

static STATUS
INamespace_Client_createLink(INamespace *me, const char *path, IContainer *scope, const char *target, bool force)
{
	int scope_d;
	STATUS status;

	status = E_SUCCESS;
	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { status = E_INVAL; });
	if(E_SUCCESS == status)
	{
		status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_createLink, path, scope_d, target, force);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;

}

static STATUS
INamespace_Client_setFlags(INamespace *me, const char *path, IContainer *scope, DirectoryEntryFlags flags)
{
	int scope_d;
	STATUS status;

	status = E_SUCCESS;
	RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(scope, scope_d, { status = E_INVAL; });
	if(E_SUCCESS == status)
	{
		status = ExSystemCall(INTF_TO_CLASS(me)->data.descriptor, INamespace_ID_setFlags, path, scope_d, flags);
	}
	RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(scope, scope_d);
	return status;

}
