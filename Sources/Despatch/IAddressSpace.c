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
Executive_Despatch_Handlers_IAddressSpace(ExecutiveDespatch *despatch, void *object, Executive_Despatch *context, IThread *currentThread)
{
	IAddressSpace *target = (IAddressSpace *) object;
	UNUSED__(despatch);
	UNUSED__(context);
	UNUSED__(currentThread);

	EXTRACEF(("Executive::Despatch::Handlers::IAddressSpace(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
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
			/* 3 = STATUS regionFromPointer([in] void *ptr, [out] IRegion **region); */
			{
				IRegion *out;

				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_regionFromPointer(target, (void *) (despatch->syscall.arg[2]), &out)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, out, &IID_IRegion);
				}
			}
			return;
		case 4:
			/* 4 = int pageSize(void); */		
			{
				int r2;

				r2 = IAddressSpace_pageSize(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(int));
				if(r2)
				{
					despatch->syscall.status = E_SUCCESS;
				}
			}
			return;
		case 5:
			/* 5 = STATUS obtainRegion([in] size_t count, [in] RegionFlags flags, [in,local] IRegionHolder *owner, [out] IRegion **region); */
			{
				IRegion *region;

				region = NULL;
				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_obtainRegion(target, despatch->syscall.arg[2], despatch->syscall.arg[3], NULL, &region)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[5], context, region, &IID_IRegion);
				}
			}
			return;
		case 6:
			/* 6 = STATUS obtainTransientRegion([in] size_t count, [in] RegionFlags flags, [in,local] IRegionHolder *owner, [out] IRegion **region); */
			{
				IRegion *region;

				region = NULL;
				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_obtainTransientRegion(target, despatch->syscall.arg[2], despatch->syscall.arg[3], NULL, &region)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[5], context, region, &IID_IRegion);
				}
			}
			return;
	}
	ExPanic("unhandled IAddressSpace method!");
}
