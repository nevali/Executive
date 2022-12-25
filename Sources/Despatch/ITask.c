/* Executive Microkernel
 * ITask despatch
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

void
Executive_Despatch_Handlers_ITask(ExecutiveDespatch *despatch, void *object, Executive_Despatch *context, IThread *currentThread)
{
	ITask *target = (ITask *) object;
	UNUSED__(despatch);
	UNUSED__(context);
	UNUSED__(currentThread);

	EXTRACEF(("Executive::Despatch::Handlers::ITask(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
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
			/* TASKID id(void);
			 * TREAT AS: STATUS id(TASKID *r2)
			 */
			{
				TASKID r2 = ITask_id(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(TASKID));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 4:
			/* TaskFlags flags(void);
			 * TREAT AS: STATUS flags(TaskFlags *r2)
			 */
			{
				TaskFlags r2 = ITask_flags(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(TaskFlags));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 5:
			/* STATUS ns([in] REFUUID iid, [out, iid_is(iid)] void **out); */
			{
				UUID iid;
				void *outptr;

				EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
				EXTRACEF(("Executive::Despatch::Handlers::ITask::ns(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
				despatch->syscall.status = ITask_ns(target, &iid, &outptr);
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
				EXTRACEF(("Executive::Despatch::Handlers::ITask::job(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
				despatch->syscall.status = ITask_job(target, &iid, &outptr);
				if(despatch->syscall.status == E_SUCCESS)
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
				}
			}
			return;
		case 7:
			/* STATUS addressSpace([in] REFUUID iid, [out, iid_is(iid)] void **out); */
			{
				UUID iid;
				void *outptr;

				EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &iid, sizeof(UUID));
				EXTRACEF(("Executive::Despatch::Handlers::ITask::addressSpace(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(&iid)));
				despatch->syscall.status = ITask_addressSpace(target, &iid, &outptr);
				if(despatch->syscall.status == E_SUCCESS)
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, outptr, &iid);
				}
			}
			return;
	}
	ExPanic("unhandled ITask method!");
}
