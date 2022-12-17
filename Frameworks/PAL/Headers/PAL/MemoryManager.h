/* Executive Microkernel
 *   Headers/PAL/MemoryManager.h
 *   Defines the well-known MemoryManager metaclass provided by the PAL
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#ifndef EXECUTIVE_PAL_MEMORYMANAGER_H_
# define EXECUTIVE_PAL_MEMORYMANAGER_H_ 1

# include <Executive/IMemoryManager.h>

#endif /*!EXECUTIVE_PAL_MEMORYMANAGER_H_*/

#if defined(INITGUID) || !defined(MEMORYMANAGER_H_GUIDS_DEFINED_)
# define MEMORYMANAGER_H_GUIDS_DEFINED_

/* CLSID_PAL_MemoryManager = {2f 26 86 22-3a 49-49 d8-aa 23-6e fb 1a d0 99 89} */
UUID_DEFINE(CLSID_PAL_MemoryManager, 0x2f, 0x26, 0x86, 0x22, 0x3a, 0x49, 0x49, 0xd8, 0xaa, 0x23, 0x6e, 0xfb, 0x1a, 0xd0, 0x99, 0x89);
#endif /*INITGUID||!MEMORYMANAGER_H_GUIDS_DEFINED_*/
