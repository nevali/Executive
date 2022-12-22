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

size_t
RtStrLen(const char *str)
{
	size_t c;

	RTASSERT(NULL != str);
	for(c = 0; str[c]; c++)
	{
	}
/*	RTLOGF((LOG_TRACE, "RtStrLen('%s') = %u", str, c)); */
	return c;
}

char *
RtStrDup(const char *str)
{
	RTASSERT(NULL != str);
	return (char *) RtMemDup(str, RtStrLen(str) + 1);
}

const char *
RtStrPos(const char *str, int ch)
{
	RTASSERT(NULL != str);
	for(; *str; str++)
	{
		if(*str == ch)
		{
			return str;
		}
	}
	return NULL;
}

int
RtStrEqual(const char *a, const char *b)
{
	RTASSERT(NULL != a);
	RTASSERT(NULL != b);
	
	for(; *a && *b; ++a, ++b)
	{
		if(*a != *b)
		{
			return 0;
		}
	}
	if(*a != *b)
	{
		return 0;
	}
	return 1;
}

int
RtStrLEqual(const char *a, const char *b, size_t max)
{
	RTASSERT(NULL != a);
	RTASSERT(NULL != b);
	
	for(; *a && *b && max; ++a, ++b)
	{
		max--;
		if(*a != *b)
		{
			return 0;
		}
	}
	if(!max)
	{
		return 1;
	}
	if(*a != *b)
	{
		return 0;
	}
	return 1;
}

size_t
RtStrLCopy(char *dest, size_t size, const char *src, size_t max)
{
	size_t count;

	for(count = 0; size > 1 && max && src; count++)
	{
		*dest = *src;
		dest++;
		src++;
		size--;
		max--;
		dest[0] = 0;
	}
	return count;
}

size_t
RtStrCopy(char *dest, size_t size, const char *src)
{
	size_t count;

	for(count = 0; size > 1 && src; count++)
	{
		*dest = *src;
		dest++;
		src++;
		size--;
		dest[0] = 0;
	}
	return count;
}
