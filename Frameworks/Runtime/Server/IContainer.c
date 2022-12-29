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

#include "p_Server.h"

EXEC_DESPATCH_HANDLER(IContainer)
{
	EXEC_DESPATCH_BEGIN(IContainer)
	{
		/* STATUS resolve([in] const char *name, [out] IDirectoryEntry **entry); */
		EXEC_DESPATCH_HANDLE(IContainer, resolve)
		{
			IDirectoryEntry *r3;
			r3 = NULL;
			if(E_SUCCESS == (despatch->syscall.status = IContainer_resolve(target,
				(const char *) (void *) despatch->syscall.arg[2],
				&r3)))
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, r3, ((REFUUID) &IID_IDirectoryEntry));
			}
			return;
		}
		
		/* IIterator *iterator(void); */
		EXEC_DESPATCH_HANDLE(IContainer, iterator)
		{
			IIterator *r2;
			
			r2 = IContainer_iterator(target);
			if(NULL == r2)
			{
				despatch->syscall.status = E_NOMEM;
				return;
			}
			despatch->syscall.status = E_SUCCESS;
			EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[2], context, r2, ((REFUUID) &IID_IIterator));
			return;
		}
	}
	EXEC_DESPATCH_END(IContainer);
}
