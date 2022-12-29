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

#include "p_Server.h"

EXEC_DESPATCH_HANDLER(IRegion)
{
	EXEC_DESPATCH_BEGIN(IRegion)
	{
		/* 3 = RegionFlags flags(); */
		EXEC_DESPATCH_HANDLE(IRegion, flags)
			{
				RegionFlags r2;

				r2 = IRegion_flags(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(RegionFlags));
				despatch->syscall.status = E_SUCCESS;
				return;
			}
		/* 4 =  int queryOwnerInterface([in] REFUUID riid, [out, iid_is(riid)] void **ptr); */
		EXEC_DESPATCH_HANDLE(IRegion, queryOwnerInterface)
			/* %E-NOT-IMPL - not valid across a syscall boundary */
			return;
		/* 5 = uint8_t *base(void); */
		EXEC_DESPATCH_HANDLE(IRegion, base)
			{
				uint8_t *r2;

				/* XXX check that this is from the same address-space? */
				r2 = IRegion_base(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(uint8_t *));
				despatch->syscall.status = E_SUCCESS;
				return;
			}
		/* size_t pages(void); */
		EXEC_DESPATCH_HANDLE(IRegion, pages)
			{
				size_t r2;

				r2 = IRegion_pages(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(size_t));
				despatch->syscall.status = E_SUCCESS;
				return;
			}
		/* size_t bytes(void); */
		EXEC_DESPATCH_HANDLE(IRegion, bytes)
			{
				size_t r2;

				r2 = IRegion_bytes(target);
				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(size_t));
				despatch->syscall.status = E_SUCCESS;
				return;
			}
	}
	EXEC_DESPATCH_END(IRegion);
}
