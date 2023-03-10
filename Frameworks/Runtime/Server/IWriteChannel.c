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

EXEC_DESPATCH_HANDLER(IWriteChannel)
{
	EXEC_DESPATCH_BEGIN(IWriteChannel)
	{
		case IWriteChannel_ID_send:
			/* 3 = size_t send(const uint8_t *buf, size_t buflen); */
			{
				size_t r3;

				EXEC_DESPATCH_COPY_FROM_USER(despatch->syscall.arg[3], &r3, sizeof(size_t));
				
				/* XXX */
				r3 = IWriteChannel_send(target, (uint8_t *) (void *) despatch->syscall.arg[2], r3);

				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[3], &r3, sizeof(size_t));
				if((STATUS) r3 < E_SUCCESS)
				{
					despatch->syscall.status = (STATUS) r3;
				}
				else
				{
					despatch->syscall.status = E_SUCCESS;
				}
			}
			return;
		case IWriteChannel_ID_write:
			/* 3 = size_t write(const const char *str); */
			{
				size_t r3;

				/* XXX */
				r3 = IWriteChannel_write(target, (const char *) (void *) despatch->syscall.arg[2]);

				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[3], &r3, sizeof(size_t));
				if((STATUS) r3 < E_SUCCESS)
				{
					despatch->syscall.status = (STATUS) r3;
				}
				else
				{
					despatch->syscall.status = E_SUCCESS;
				}
			}
			return;
		case IWriteChannel_ID_writeLn:
			/* 3 = size_t writeLn(const const char *str); */
			{
				size_t r3;

				/* XXX */
				r3 = IWriteChannel_writeLn(target, (const char *) (void *) despatch->syscall.arg[2]);

				EXEC_DESPATCH_COPY_TO_USER(despatch->syscall.arg[3], &r3, sizeof(size_t));
				if((STATUS) r3 < E_SUCCESS)
				{
					despatch->syscall.status = (STATUS) r3;
				}
				else
				{
					despatch->syscall.status = E_SUCCESS;
				}
			}
			return;
	}
	EXEC_DESPATCH_END(IWriteChannel);
}
