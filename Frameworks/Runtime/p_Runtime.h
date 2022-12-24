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

#ifndef P_RUNTIME_H_
# define P_RUNTIME_H_                  1

# define INITGUID_EXTERN               1

# include <Runtime/Runtime.h>
# include <Executive/SystemCall.h>
# include <Executive/IAllocator.h>
# include <Executive/IThread.h>
# include <Executive/ITask.h>
# include <Executive/INamespace.h>
# include <Executive/IAddressSpace.h>
# include <Executive/IWriteChannel.h>
# include <Executive/MFactory.h>
# include <Runtime/Internal/Private.h>
# include <Runtime/Internal/Client.h>

# if RUNTIME_BUILD_EXEC
#  include <Executive/Internal/Executive.h>
# endif /*RUNTIME_BUILD_EXEC*/

typedef union RtAllocator RtAllocator;

# define RTLOGF(P)                    RtLogFormat P
# define RTPANIC(P)                   RtPanic(P)

# define STR__(x)                      STR2__(x)
# define STR2__(x)                     #x

# ifdef NDEBUG
#  define RtAssert__(cond, file, line)  if(!(cond)) { RtAssertPanic__(#cond, file, line); }
# else
#  define RtAssert__(cond, file, line)  do { (void) (cond); } while(0)
# endif
# define RtAssertPanic__(cond, file, line) RTPANIC("ASSERTION FAILED: " cond " at " file ":" line)
# define RTASSERT(cond)               RtAssert__(cond, __FILE__, STR__(__LINE__))

/*INTERNAL*/
EXTERN_C void *Rt_AllocatorMap(RtAllocator *self, size_t size, RegionFlags flags) RUNTIME_PRIVATE__(AllocatorMap);
EXTERN_C STATUS Rt_AllocatorUnmap(RtAllocator *self, void *addr, size_t size) RUNTIME_PRIVATE__(AllocatorUnmap);
EXTERN_C STATUS RtAllocator_MFactory_createInstance(MFactory *me, IObject *outer, REFUUID iid, void **out) RUNTIME_PRIVATE__(RtAllocator_MFactory_createInstance);
EXTERN_C IAllocator *RtAllocator_create(IAddressSpace *addressSpace) RUNTIME_PRIVATE__(RtAllocator_create);

#endif /*!P_RUNTIME_H_*/
