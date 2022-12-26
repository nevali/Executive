/* Executive Microkernel
 * IThread despatch
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

EXEC_DESPATCH_HANDLER(IThread)
{
	EXEC_DESPATCH_BEGIN(IThread)
	{
		/* THREADID id(void);
			* TREAT AS: STATUS id(THREADID *r2)
			*/
		EXEC_DESPATCH_HANDLE(IThread, id)
		{
			THREADID r2 = IThread_id(target);
			EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(THREADID));
			despatch->syscall.status = E_SUCCESS;
			return;
		}

		/* ThreadFlags flags(void);
			* TREAT AS: STATUS flags(ThreadFlags *r2)
			*/
		EXEC_DESPATCH_HANDLE(IThread, flags)
		{
			ThreadFlags r2 = IThread_flags(target);
			EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(ThreadFlags));
			despatch->syscall.status = E_SUCCESS;
			return;
		}

		/*	STATUS task([in] REFUUID iid, [out, iid_is(iid)] void **out); */
		EXEC_DESPATCH_HANDLE(IThread, task)
		{
			UUID iid;
			void *outptr;

			EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
			EXTRACEF(("Executive::Despatch::Handlers::IThread::task(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
			despatch->syscall.status = IThread_task(target, &iid, &outptr);
			if(despatch->syscall.status == E_SUCCESS)
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
			}
			return;
		}

		/* STATUS job([in] REFUUID iid, [out, iid_is(iid)] void **out); */
		EXEC_DESPATCH_HANDLE(IThread, job)
		{
			UUID iid;
			void *outptr;

			EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
			EXTRACEF(("Executive::Despatch::Handlers::IThread::job(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
			despatch->syscall.status = IThread_job(target, &iid, &outptr);
			if(despatch->syscall.status == E_SUCCESS)
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
			}
			return;
		}

		/* STATUS ns([in] REFUUID iid, [out, iid_is(iid)] void **out); */
		EXEC_DESPATCH_HANDLE(IThread, ns)
		{
			UUID iid;
			void *outptr;

			EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
			EXTRACEF(("Executive::Despatch::Handlers::IThread::ns(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
			despatch->syscall.status = IThread_ns(target, &iid, &outptr);
			if(despatch->syscall.status == E_SUCCESS)
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
			}
			return;
		}
	
		/* [local] void yield(void); */
		EXEC_DESPATCH_HANDLE(IThread, yield)
		{
			despatch->syscall.status = E_SUCCESS;
			IThread_yield(currentThread);
			return;
		}
	}
	EXEC_DESPATCH_END(IThread);
}
