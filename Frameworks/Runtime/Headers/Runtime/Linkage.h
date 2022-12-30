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

#ifndef RUNTIME_LINKAGE_H_
# define RUNTIME_LINKAGE_H_            1

# include <Executive/Linkage.h>

# ifndef RUNTIME_LINKAGE__
#  if RUNTIME_BUILD_EXEC
#   define RUNTIME_LINKAGE__(name) SYM__("EXECUTIVE", name, "0.0") WEAK_IMPORT__
#   define RUNTIME_PRIVATE__(name) SYM__("__executive__PRIVATE__", name, "PRIVATE") WEAK_IMPORT__
#  else
#   define RUNTIME_LINKAGE__(name) SYM__("RUNTIME", name, "0.0") WEAK_IMPORT__
#   define RUNTIME_PRIVATE__(name) SYM__("__runtime__PRIVATE__", name, "PRIVATE") WEAK_IMPORT__
#  endif
# endif

#endif /*!RUNTIME_LINKAGE_H_*/
