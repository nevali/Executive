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

void
Executive_Despatch_Handlers_INamespace(ExecutiveDespatch *despatch, void *object, Executive_Despatch *context, IThread *currentThread)
{
	INamespace *target = (INamespace *) object;

	UNUSED__(despatch);
	UNUSED__(object);
	UNUSED__(context);
	UNUSED__(currentThread);

	EXTRACEF(("Executive::Despatch::Handlers::INamespace(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
		despatch->syscall.arg[0], despatch->syscall.arg[1],
		despatch->syscall.arg[2], despatch->syscall.arg[3],
		despatch->syscall.arg[4], despatch->syscall.arg[5],
		despatch->syscall.arg[6], despatch->syscall.arg[7]));
	switch(despatch->syscall.arg[1])
	{
		case IObject_ID_queryInterface:
			/* 0 = STATUS queryInterface() - handled by Executive::Despatch::Handlers::IObject */
			return;
		case IObject_ID_retain:
			/* 1 = REFCOUNT retain() */
			return;
		case IObject_ID_release:
			/* 2 = REFCOUNT release();  */
			return;
		case IContainer_ID_resolve:
			/* XXX */
			return;
		case IContainer_ID_iterator:
			/* XXX */
			return;
		case INamespace_ID_resolveEntry:
			return;
		case INamespace_ID_resolveContainer:
			return;
			/* STATUS open([in] const char *path, [in] IContainer *scope, REFUUID iid, [out, iid_is(iid)] void **target); */
		case INamespace_ID_open:
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
			}
			return;
		case INamespace_ID_create:
			break;
	}
	ExPanic("unhandled INamespace method!");
}
