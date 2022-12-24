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

/* XXX this is not thread-safe */
static char logbuf[132];

void
RtDebugFormat(LogLevel level, const char *format, ...)
{
#if EXEC_BUILD_DEBUG
	va_list args;

	va_start(args, format);
	RtLogFormatArgs(level, format, args);
	va_end(args);
#else /*EXEC_BUILD_DEBUG*/
	UNUSED__(level);
	UNUSED__(format);
#endif /*!EXEC_BUILD_DEBUG*/
}

void
RtTraceFormat(const char *format, ...)
{
#if EXEC_BUILD_DEBUG
	va_list args;

	va_start(args, format);
	RtLogFormatArgs(LOG_TRACE, format, args);
	va_end(args);
#else /*EXEC_BUILD_DEBUG*/
	UNUSED__(level);
	UNUSED__(format);
#endif /*!EXEC_BUILD_DEBUG*/
}

void
RtLogFormat(LogLevel level, const char *format, ...)
{
	va_list args;
	
	va_start(args, format);
	RtLogFormatArgs(level, format, args);
	va_end(args);
}

void
RtLogFormatArgs(LogLevel level, const char *format, va_list args)
{
	/* XXX not thread-safe */
	RtStrBufFormatArgs(logbuf, sizeof(logbuf), format, args);
	RtLog(level, logbuf);
}

#if 0
extern int printf(const char *, ...);
#endif

void
RtLog(LogLevel level, const char *string)
{
#if RUNTIME_BUILD_EXEC
	if(executive.data.diagnostics)
	{
		IPlatformDiagnostics_log(executive.data.diagnostics, level, string);
	}
#if 0
	else
	{
		printf("<<< %d  %s >>>\n", level, string);
	}
#endif
#else /*RUNTIME_BUILD_EXEC*/
	UNUSED__(level);

	if(Rt__private__.stderr)
	{
		IWriteChannel_write(Rt__private__.stderr, (const uint8_t *) string, RtStrLen(string));
	}
#endif /*!RUNTIME_BUILD_EXEC*/
}

void
RtPanic(const char *str)
{
#if RUNTIME_BUILD_EXEC
	IPlatform_panic(executive.data.platform, str);
#else
	RtLog(LOG_EMERGENCY, str);
#endif
}
