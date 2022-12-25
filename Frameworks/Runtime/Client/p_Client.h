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

# include <Runtime/Internal/Client.h>
# include <Runtime/Internal/Classes.h>
# include <Executive/SystemCall.h>

typedef union Runtime_Client Runtime_Client;

union Runtime_Client
{
	IObject Object;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		int descriptor;
	} data;
};

RUNTIME_DECL_IOBJECT(Runtime_Client);

EXTERN_C Runtime_Client *Runtime_Client_create(int descriptor);
EXTERN_C STATUS Runtime_Client_createFor(int descriptor, REFUUID iid, void **out);

#endif /*!P_CLIENT_H_*/
