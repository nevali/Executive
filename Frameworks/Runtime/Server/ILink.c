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

EXEC_DESPATCH_HANDLER(ILink)
{
	EXEC_DESPATCH_BEGIN(ILink)
	{
		/* STATUS target(void); */
		EXEC_DESPATCH_HANDLE(ILink, target)
		{
			char *r2;
			EXEC_DESPATCH_XFER_OUT_FROM_USER(despatch->syscall.arg[2], r2, despatch->syscall.arg[3]);
			despatch->syscall.status = ILink_target(target, r2, despatch->syscall.arg[3]);
			EXEC_DESPATCH_XFER_OUT_TO_USER(despatch->syscall.arg[2], r2, despatch->syscall.arg[3]);
			return;
		}
	}
	EXEC_DESPATCH_END(ILink);
}
