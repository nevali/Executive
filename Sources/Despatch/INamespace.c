/* Executive Microkernel
 * INamespace despatch
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#include "p_Despatch.h"

EXEC_DESPATCH_HANDLER(INamespace)
{
	EXEC_DESPATCH_BEGIN(INamespace)
	{
		/* IContainer */
		EXEC_DESPATCH_HANDLE(IContainer, resolve)
		EXEC_DESPATCH_HANDLE(IContainer, iterator)
			return Executive_Despatch_Handlers_IContainer(despatch, object, context, currentThread);
		
		EXEC_DESPATCH_HANDLE(INamespace, resolveEntry)
			break;
		EXEC_DESPATCH_HANDLE(INamespace, resolveContainer)
			break;
		/* STATUS open([in] const char *path, [in] IContainer *scope, REFUUID iid, [out, iid_is(iid)] void **target); */
		EXEC_DESPATCH_HANDLE(INamespace, open)
		{
			IContainer *r3;
			void *r5;

			r3 = NULL;
			r5 = NULL;
			if(E_SUCCESS == (despatch->syscall.status = INamespace_open(target,
				(const char *) (void *) despatch->syscall.arg[2],
				r3,
				(REFUUID) (void *) despatch->syscall.arg[4],
				&r5)))
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[5], context, r5, ((REFUUID) (void *) despatch->syscall.arg[4]));
			}
			return;
		}
		EXEC_DESPATCH_HANDLE(INamespace, create)
			break;
		EXEC_DESPATCH_HANDLE(INamespace, add)
			break;
		EXEC_DESPATCH_HANDLE(INamespace, createLink)
			break;
		EXEC_DESPATCH_HANDLE(INamespace, setFlags)
			break;
	}
	EXEC_DESPATCH_END(INamespace);
}
