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

STATUS
RtOpenAs(const char *path, REFUUID iid, void **out)
{
#if RUNTIME_BUILD_EXEC
	if(!executive.data.rootNS)
	{
		return E_NOTIMPL;
	}
	return INamespace_open(executive.data.rootNS, path, NULL, iid, out);
#else
	if(!Rt__private__.ns)
	{
		return E_NOTIMPL;
	}
	return INamespace_open(Rt__private__.ns, path, NULL, iid, out);
#endif
}