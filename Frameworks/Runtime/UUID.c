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

bool
RtUuidEqual(REFUUID a, REFUUID b)
{
	RTASSERT(a != NULL);
	RTASSERT(b != NULL);

	if(a->d.d1 != b->d.d1 ||
		a->d.d2 != b->d.d2 ||
		a->d.d3 != b->d.d3 ||
		a->d.d4 != b->d.d4)
	{
		return false;
	}
	return true;
}

size_t
RtUuidStr(REFUUID uuid, UUIDBUF buf)
{
	if(!uuid)
	{
		return RtStrCopy(buf, sizeof(UUIDBUF), "<NULL>");
	}
	return RtStrBufFormat(buf, sizeof(UUIDBUF), "{ %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x }",
		uuid->uuid.time_low, uuid->uuid.time_mid, uuid->uuid.time_hi_and_version,
		uuid->uuid.clock_seq_hi_and_reserved, uuid->uuid.clock_seq_low,
		uuid->uuid.node[0], uuid->uuid.node[1], uuid->uuid.node[2],
		uuid->uuid.node[3], uuid->uuid.node[4], uuid->uuid.node[5]);
}

void
RtUuidCopy(UUID *restrict dest, REFUUID restrict src)
{
	RtMemCopy(dest, src, sizeof(UUID));
}
