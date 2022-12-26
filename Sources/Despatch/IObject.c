/* Executive Microkernel
 * IObject despatch
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

EXEC_DESPATCH_HANDLER(IObject)
{
	EXEC_DESPATCH_BEGIN(IObject)
	{
		/* STATUS queryInterface([in] REFUUID iid, [out, iid_is(iid)] void **out); */
		EXEC_DESPATCH_HANDLE(IObject, queryInterface)
		{
			UUID iid;
			void *outptr;

			EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
			EXTRACEF(("Executive::Despatch::Handlers::IObject::queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
			despatch->syscall.status = IObject_queryInterface(target, &iid, &outptr);
			if(despatch->syscall.status == E_SUCCESS)
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
			}
			return;
		}
		/* STATUS retain(void); */
		EXEC_DESPATCH_HANDLE(IObject, retain)
		{
			/* this call is not valid */
			despatch->syscall.status = E_NOTIMPL;
			return;
		}
		/* STATUS release(void); */
		EXEC_DESPATCH_HANDLE(IObject, release)
		{
			size_t n;
			EXTRACEF(("Executive::Despatch::Handlers::IObject::release(%p)", target));
			for(n = 0; n < context->data.ndescriptors; n++)
			{
				if(context->data.descriptors[n].object == object)
				{
					EXLOGF((LOG_DEBUG7, "Executive::Despatch::Handlers::IObject::release(): closing descriptor %u", n + 1));
					context->data.descriptors[n].object = NULL;
					context->data.descriptors[n].handler = NULL;
					break;
				}
			}
			IObject_release(target);
			despatch->syscall.status = E_SUCCESS;
			return;
		}
	}
	EXEC_DESPATCH_END(IObject);
}
