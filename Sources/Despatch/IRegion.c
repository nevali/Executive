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

void
Executive_Despatch_Handlers_IRegion(ExecutiveDespatch *despatch, void *object, Executive_Despatch *context, IThread *currentThread)
{
	IRegion *target = (IRegion *) object;
	
	UNUSED__(despatch);
	UNUSED__(target);
	UNUSED__(context);
	UNUSED__(currentThread);

	EXTRACEF(("Executive::Despatch::Handlers::IRegion(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
		despatch->syscall.arg[0], despatch->syscall.arg[1],
		despatch->syscall.arg[2], despatch->syscall.arg[3],
		despatch->syscall.arg[4], despatch->syscall.arg[5],
		despatch->syscall.arg[6], despatch->syscall.arg[7]));
	switch(despatch->syscall.arg[1])
	{
			case 0:
			/* 0 = STATUS queryInterface() - handled by Executive::Despatch::Handlers::IObject */
			return;
		case 1:
			/* 1 = REFCOUNT retain() */
			return;
		case 2:
			/* 2 = REFCOUNT release();  */
			return;
		case 3:
			/* 3 = RegionFlags flags(); */
			{
				RegionFlags r2;

				r2 = IRegion_flags(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(RegionFlags));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 4:
			/* 4 =  int queryOwnerInterface([in] REFUUID riid, [out, iid_is(riid)] void **ptr); */
			/* %E-NOT-IMPL - not valid across a syscall boundary */
			return;
		case 5:
			/* 5 = uint8_t *base(void); */
			{
				uint8_t *r2;

				/* XXX check that this is from the same address-space? */
				r2 = IRegion_base(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(uint8_t *));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 6:
			/* 6 = size_t pages(void); */
			{
				size_t r2;

				r2 = IRegion_pages(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(size_t));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
		case 7:
			/* 7 = size_t bytes(void); */
			{
				size_t r2;

				r2 = IRegion_bytes(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(size_t));
				despatch->syscall.status = E_SUCCESS;
			}
			return;
	}
	ExPanic("unhandled IRegion method!");
}
