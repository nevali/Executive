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
 
#if !RUNTIME_BUILD_EXEC

/* During early initialisation we don't have access to an address space from
 * which to obtain regions, which means we don't have an allocator, which
 * means the proxy objects must be statically-allocated
 */

static IAddressSpace_Client IAddressSpace_client;

extern void abort(void);

void
Rt__Initialise()
{
	int task, addressSpace;

	task = -1;
	/* object 0, method 5 = IThread::task() */
	ExSystemCall(0, 5, &IID_ITask, &task, NULL, NULL, NULL, NULL, NULL);
	if(task < 0)
	{
		abort();
		return;
	}
	/* task, method 7 = ITask::addressSpace() */
	addressSpace = -1;
	ExSystemCall(task, 7, &IID_IAddressSpace, &addressSpace, NULL, NULL, NULL, NULL, NULL);
	if(addressSpace < 0)
	{
		abort();
		return;
	}
	IAddressSpace_Client_init_(&IAddressSpace_client, addressSpace);
	Rt__private__.addressSpace = &(IAddressSpace_client.AddressSpace);
	RtAllocator_create(Rt__private__.addressSpace);
	Rt__private__.mainThread = IThread_Client_create(0);
	if(!Rt__private__.mainThread)
	{
		abort();
		return;
	}
	Rt__private__.task = ITask_Client_create(task);
	if(!Rt__private__.task)
	{
		abort();
		return;
	}
	ITask_ns((Rt__private__.task), &IID_INamespace, (void **) &(Rt__private__.ns));
	/* XXX inherited descriptors */
	/* XXX stdin/stdout/stderr */
}

#endif /*!RUNTIME_BUILD_EXEC*/
