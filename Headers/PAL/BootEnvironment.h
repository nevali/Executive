/* Executive Microkernel
 *   Headers/PAL/BootEnvironment.h
 *   Defines the well-known BootEnvironment metaclass provided by the PAL
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

#ifndef EXECUTIVE_PAL_BOOTENVIRONMENT_H_
# define EXECUTIVE_PAL_BOOTENVIRONMENT_H_ 1

# include <Executive/IBootEnvironment.h>

#endif /*!EXECUTIVE_PAL_BOOTENVIRONMENT_H_*/

#if defined(INITGUID) || !defined(BOOTENVIRONMENT_H_GUIDS_DEFINED_)
# define BOOTENVIRONMENT_H_GUIDS_DEFINED_

/* CLSID_PAL_BootEnvironment = { b3be0a71-e1c9-43e7-9c3f-0e18aba6b880 } */
UUID_DEFINE(CLSID_PAL_BootEnvironment, 0xb3, 0xbe, 0x0a, 0x7a, 0xe1, 0xc9, 0x43, 0xe7, 0x9c, 0x3f, 0x0e, 0x18, 0xab, 0xa6, 0xb8, 0x80);
#endif /*INITGUID||!BOOTENVIRONMENT_H_GUIDS_DEFINED_*/
