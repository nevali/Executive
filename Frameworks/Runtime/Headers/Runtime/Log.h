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

#ifndef RUNTIME_LOG_H_
# define RUNTIME_LOG_H_                1

# include <Executive/IPlatformDiagnostics.h>

EXTERN_C void RtDebugFormat(LogLevel level, const char *format, ...) RUNTIME_LINKAGE__(RtDebugFormat);

EXTERN_C void RtTraceFormat(const char *format, ...) RUNTIME_LINKAGE__(RtTraceFormat);

EXTERN_C void RtLogFormat(LogLevel level, const char *format, ...) RUNTIME_LINKAGE__(RtLogFormat);
EXTERN_C void RtLogFormatArgs(LogLevel level, const char *format, va_list args) RUNTIME_LINKAGE__(RtLogFormatArgs);

EXTERN_C void RtLog(LogLevel level, const char *string) RUNTIME_LINKAGE__(RtLlog);

#endif /*!RUNTIME_LOG_H_*/
