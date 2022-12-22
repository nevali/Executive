/* Executive Microkernel
 * Runtime Framework
 *   This framework provides low-level user-space APIs to applications, via
 *   the Executive's system call mechanism
 */

/* Copyright 2015-2022 Mo McRoberts.
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

#include "p_Runtime.h"

void *
RtMemDup(const void *src, size_t nbytes)
{
	void *p;

	RTASSERT(NULL != src);
	if(NULL == (p = RtMemAlloc(nbytes)))
	{
		RTLOGF((LOG_CONDITION, "%%E-NOMEM: RtMemDup(): RtMemAlloc(%u) failed", nbytes));
		return NULL;
	}
	return RtMemCopy(p, src, nbytes);
}

void *
RtMemCopy(void *restrict dest, const void *restrict src, size_t nbytes)
{
	size_t si;
	const uint8_t *sp = (const uint8_t *) src;
	uint8_t *dp = (uint8_t *) dest;

	RTASSERT(NULL != src);
	RTASSERT(NULL != dest);
	for(si = 0; si < nbytes; si++)
	{
		dp[si] = sp[si];
	}
	return dest;
}

void *
RtMemSet(void *buffer, int value, size_t nbytes)
{
	uint8_t *bufptr;

	RTASSERT(NULL != buffer);

	for(bufptr = (uint8_t *) buffer; nbytes; bufptr++)
	{
		*bufptr = (uint8_t) value;
		nbytes--;
	}
	return buffer;
}