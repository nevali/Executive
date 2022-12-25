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

#define EXEC_DESPATCH_COPY_FROM_USER(src, dest, nbytes) \
	if(!src) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
#define EXEC_DESPATCH_COPY_TO_USER(dest, src, nbytes) \
	if(!dest) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
#define EXEC_DESPATCH_DESCRIPTOR(ret, ctx, obj, iid) \
	*((int *)(void *)(ret)) = Executive_Despatch_descriptor(ctx, obj, iid);

void
Executive_Despatch_Handlers_IThread(ExecutiveDespatch *despatch, void *object, Executive_Despatch *context, IThread *currentThread)
{
	IThread *target = (IThread *) object;
	UNUSED__(despatch);
	UNUSED__(context);
	UNUSED__(currentThread);

	EXTRACEF(("Executive::Despatch::Handlers::IThread(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
		despatch->syscall.arg[0], despatch->syscall.arg[1],
		despatch->syscall.arg[2], despatch->syscall.arg[3],
		despatch->syscall.arg[4], despatch->syscall.arg[5],
		despatch->syscall.arg[6], despatch->syscall.arg[7]));

	switch(despatch->syscall.arg[1])
	{
		case 0:
			/* queryInterface - handled by Executive::Despatch::Handlers::IObject */
			return;
		case 1:
			/* retain */
			return;
		case 2:
			/* release */
			return;
		case 3:
			/* THREADID id(void);
			 * TREAT AS: STATUS id(THREADID *r2)
			 */
			{
				THREADID r2 = IThread_id(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(THREADID));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 4:
			/* ThreadFlags flags(void);
			 * TREAT AS: STATUS flags(ThreadFlags *r2)
			 */
			{
				ThreadFlags r2 = IThread_flags(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(ThreadFlags));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 5:
			/*	STATUS task([in] REFUUID iid, [out, iid_is(iid)] void **out); */
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
			}
			return;
		case 6:
			/* STATUS job([in] REFUUID iid, [out, iid_is(iid)] void **out); */
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
			}
			return;
		case 7:
			/* STATUS ns([in] REFUUID iid, [out, iid_is(iid)] void **out); */
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
			}
			return;
		case 8:
			/* [local] void yield(void); */
			{
				despatch->syscall.status = E_SUCCESS;
				IThread_yield(currentThread);
			}
			return;
	}
	ExPanic("unhandled IThread method!");
}
