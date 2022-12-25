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

#ifndef RUNTIME_MEMORY_H_
# define RUNTIME_MEMORY_H_             1

# include <Runtime/Linkage.h>
# include <Runtime/Types.h>

/* allocate a block of memory with the default allocator */
EXTERN_C void *RtMemAlloc(size_t nbytes) RUNTIME_LINKAGE__(RtMemAlloc);
/* resize a block previously allocated with RtMemAlloc() */
EXTERN_C void *RtMemReAlloc(void *ptr, size_t nbytes) RUNTIME_LINKAGE__(RtMemReAlloc);
/* release a block originally allocated via RtMemAlloc() */
EXTERN_C void RtMemFree(void *ptr) RUNTIME_LINKAGE__(RtMemFree);
/* allocate a new block of nbytes via RtMemAlloc() and copy src into it */
EXTERN_C void *RtMemDup(const void *src, size_t nbytes) RUNTIME_LINKAGE__(RtMemDup);
/* copy nbytes bytes from src to dest, returning dest */
/* XXX should use builtin memcpy if available */
EXTERN_C void *RtMemCopy(void *restrict dest, const void *restrict src, size_t nbytes) RUNTIME_LINKAGE__(RtMemCopy);
/* set all bytes in buffer to value, returning buffer */
/* XXX should use builtin memset if available */
EXTERN_C void *RtMemSet(void *buffer, int value, size_t nbytes) RUNTIME_LINKAGE__(RtMemSet);

#endif /*!RUNTIME_MEMORY_H_*/
