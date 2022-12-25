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

#ifndef P_CLIENT_H_
# define P_CLIENT_H_                   1

# define INITGUID_EXTERN               1

# include <Runtime/Memory.h>
# include <Runtime/Internal/Client.h>
# include <Runtime/Internal/Classes.h>
# include <Executive/SystemCall.h>

# include <Executive/IWriteChannel.h>
# include <Executive/IContainer.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IDirectoryEntry.h>
# include <Executive/ILink.h>
# include <Executive/IWriteChannel.h>

# define INTF_TO_CLASS(i)               ((Runtime_Client *)(void *)(i))

RUNTIME_DECL_IOBJECT(Runtime_Client);

#define RUNTIME_CLIENT_INIT_IN_DESCRIPTOR(param, desc, invalid) \
	if(param) \
	{ \
		/* XXX we don't know how to do this yet */ \
		invalid; \
	} \
	else \
	{ \
		desc = -1; \
	}
#define RUNTIME_CLIENT_INIT_OUT_DESCRIPTOR(param, desc) \
	if(param) \
	{ \
		*param = NULL; \
	} \
	desc = -1;
#define RUNTIME_CLIENT_HANDLE_OUT_DESCRIPTOR(param, desc, riid, status) \
	if(param) \
	{ \
		if(E_SUCCESS != (status = Runtime_Client_createFor(desc, riid, (void **) param))) \
		{ \
			/* outd<IObject>::release() */ \
			ExSystemCall(desc, IObject_ID_release); \
		} \
	}
#define RUNTIME_CLIENT_HANDLE_IN_DESCRIPTOR(param, desc) /* */

EXTERN_C Runtime_Client *Runtime_Client_create(int descriptor);
EXTERN_C STATUS Runtime_Client_createFor(int descriptor, REFUUID iid, void **out);

EXTERN_C STATUS IContainer_Client_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
EXTERN_C IIterator *IContainer_Client_iterator(IContainer *me);

#endif /*!P_CLIENT_H_*/
