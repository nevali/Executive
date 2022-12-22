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

/* In userspace, access to facilities such as the address space (from which
 * an allocator can obtain transient regions) is accomplished by calling
 * IThread::addressSpace() at startup and storing the result in a private
 * data area that other parts of the Runtime framework can access. In
 * kernel-space, the interfaces are accessed in the Executive's private
 * data area instead, and this file isn't used
 */

 RuntimePrivateData Rt__private__ = {
	NULL, NULL, NULL, NULL, NULL, NULL
 };
 