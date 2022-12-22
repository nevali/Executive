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

#ifndef RUNTIME_STRINGS_H_
# define RUNTIME_STRINGS_H_            1

# include <Runtime/Linkage.h>
# include <Runtime/Types.h>

EXTERN_C size_t RtStrLen(const char *str) RUNTIME_LINKAGE__(RtStrLen);
EXTERN_C const char *RtStrPos(const char *str, int ch) RUNTIME_LINKAGE__(RtStrPos);
EXTERN_C size_t RtStrCopy(char *dest, size_t dsize, const char *src) RUNTIME_LINKAGE__(RtStrCopy);
EXTERN_C size_t RtStrLCopy(char *dest, size_t dsize, const char *src, size_t srclen) RUNTIME_LINKAGE__(RtStrLCopy);
EXTERN_C int RtStrEqual(const char *a, const char *b) RUNTIME_LINKAGE__(RtStrEqual);
EXTERN_C int RtStrLEqual(const char *a, const char *b, size_t max) RUNTIME_LINKAGE__(RtStrLEqual);
EXTERN_C char *RtStrDup(const char *str) RUNTIME_LINKAGE__(RtStrDup);
EXTERN_C char *RtStrLDup(const char *str, size_t max) RUNTIME_LINKAGE__(RtStrLDup);
EXTERN_C int RtStrFormat(char **out, const char *format, ...) RUNTIME_LINKAGE__(RtStrFormat);
EXTERN_C int RtStrFormatArgs(char **out, const char *format, va_list args) RUNTIME_LINKAGE__(RtStrFormatArgs);
EXTERN_C int RtStrBufFormat(char *restrict buf, size_t bufsize, const char *restrict format, ...) RUNTIME_LINKAGE__(RtStrBufFormat);
EXTERN_C int RtStrBufFormatArgs(char *restrict buf, size_t bufsize, const char *restrict format, va_list args) RUNTIME_LINKAGE__(RtStrBufFormatArgs);

#endif /*!RUNTIME_STRINGS_H_*/
