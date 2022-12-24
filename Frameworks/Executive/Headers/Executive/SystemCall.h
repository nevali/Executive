/* Executive Microkernel
 * System call interface
 *   Defines the API that user-mode tasks use to call into the Executive
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

#ifndef EXECUTIVE_SYSTEMCALL_H_
# define EXECUTIVE_SYSTEMCALL_H_       1

#include <Executive/Linkage.h>
#include <Executive/Types.h>
#include <Executive/Errors.h>

EXTERN_C STATUS ExSystemCall(int descriptor, int method, ...) EXEC_LINKAGE__(__syscall, "0.0");

#endif /*!EXECUTIVE_SYSTEMCALL_H_*/
