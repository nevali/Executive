/* Executive Microkernel
 * IAddressSpace despatch
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

EXEC_DESPATCH_HANDLER(IAddressSpace)
{
	EXEC_DESPATCH_BEGIN(IAddressSpace)
	{
			/* 3 = STATUS regionFromPointer([in] void *ptr, [out] IRegion **region); */
		EXEC_DESPATCH_HANDLE(IAddressSpace, regionFromPointer)
			{
				IRegion *out;

				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_regionFromPointer(target, (void *) (despatch->syscall.arg[2]), &out)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, out, &IID_IRegion);
				}
				return;
			}
			/* 4 = int pageSize(void); */		
		EXEC_DESPATCH_HANDLE(IAddressSpace, pageSize)
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
			/* 5 = STATUS obtainRegion([in] size_t count, [in] RegionFlags flags, [in,local] IRegionHolder *owner, [out] IRegion **region); */
		EXEC_DESPATCH_HANDLE(IAddressSpace, obtainRegion)
			{
				IRegion *region;

				region = NULL;
				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_obtainRegion(target, despatch->syscall.arg[2], despatch->syscall.arg[3], NULL, &region)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[5], context, region, &IID_IRegion);
				}
			}
			return;
			/* STATUS obtainTransientRegion([in] size_t count, [in] RegionFlags flags, [in,local] IRegionHolder *owner, [out] IRegion **region); */
		EXEC_DESPATCH_HANDLE(IAddressSpace, obtainTransientRegion)
			{
				IRegion *region;

				region = NULL;
				if(E_SUCCESS == (despatch->syscall.status = IAddressSpace_obtainTransientRegion(target, despatch->syscall.arg[2], despatch->syscall.arg[3], NULL, &region)))
				{
					EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[5], context, region, &IID_IRegion);
				}
			}
			return;
		EXEC_DESPATCH_HANDLE(IAddressSpace, createContext)
		{
			despatch->syscall.status = E_PERM;
			return;
		}
	}
	EXEC_DESPATCH_END(IAddressSpace);
}
