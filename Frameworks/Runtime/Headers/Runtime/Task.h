/* Executive Microkernel
 * Runtime framework
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

#ifndef RUNTIME_TASK_H_
# define RUNTIME_TASK_H_               1

# include <Runtime/IThread.h>

/* Program main routine */
EXTERN_C STATUS mainThread(IThread *self);

#endif /*!RUNTIME_TASK_H_*/
