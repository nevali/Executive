/* Executive Microkernel
 * IDirectoryEntry despatch
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

EXEC_DESPATCH_HANDLER(IDirectoryEntry)
{
	EXEC_DESPATCH_BEGIN(IDirectoryEntry)
	{
		/* STATUS queryTargetInterface([in] REFUUID iid, [out,iid_is(iid)] void **out); */
		EXEC_DESPATCH_HANDLE(IDirectoryEntry, queryTargetInterface)
		{
			UUID r2;
			void *r3;

			r3 = NULL;
			EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[2], &r2, sizeof(UUID));
			if(E_SUCCESS == (despatch->syscall.status = IDirectoryEntry_queryTargetInterface(target, &r2, (despatch->syscall.arg[3] ? &r3 : NULL))))
			{
				EXEC_DESPATCH_DESCRIPTOR(despatch->syscall.arg[3], context, r3, &r2);
			}
			return;
		}
		/* [local] STATUS name(char *buf, size_t buflen); */
		EXEC_DESPATCH_HANDLE(IDirectoryEntry, name)
		{
			char *r2;

			EXEC_DESPATCH_XFER_OUT_FROM_USER(despatch->syscall.arg[2], r2, despatch->syscall.arg[3]);
			despatch->syscall.status = IDirectoryEntry_name(target, r2, despatch->syscall.arg[3]);
			EXEC_DESPATCH_XFER_OUT_TO_USER(despatch->syscall.arg[2], r2, despatch->syscall.arg[3]);
			return;
		}
		/* void classid([out] UUID *clsid); */
		EXEC_DESPATCH_HANDLE(IDirectoryEntry, classid)
		{
			UUID r2;

			IDirectoryEntry_classid(target, &r2);
			despatch->syscall.status = E_SUCCESS;
			EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(UUID));
			return;
		}
		/* DirectoryEntryFlags flags(void); */
		EXEC_DESPATCH_HANDLE(IDirectoryEntry, flags)
		{
			DirectoryEntryFlags r2;

			r2 = IDirectoryEntry_flags(target);
			if(r2 == DEF_INVALID)
			{
				despatch->syscall.status = E_PERM;
			}
			else
			{
				despatch->syscall.status = E_SUCCESS;
			}
			EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[2], &r2, sizeof(DirectoryEntryFlags));
			return;
		}
		/* STATUS setFlags(DirectoryEntryFlags flags); */
		EXEC_DESPATCH_HANDLE(IDirectoryEntry, setFlags)
		{
			despatch->syscall.status = IDirectoryEntry_setFlags(target, (DirectoryEntryFlags) despatch->syscall.arg[2]);
			return;
		}
	}
	EXEC_DESPATCH_END(IDirectoryEntry)
}
