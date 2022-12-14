/* Executive Microkernel
 *   Headers/PAL/Platform.h
 *   Defines the well-known Platform metaclass provided by the PAL
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

#ifndef EXECUTIVE_PAL_PLATFORM_H_
# define EXECUTIVE_PAL_PLATFORM_H_         1

# include <Executive/IPlatform.h>

#endif /*!EXECUTIVE_PAL_PLATFORM_H_*/

#if defined(INITGUID) || !defined(PLATFORM_H_GUIDS_DEFINED_)
# define PLATFORM_H_GUIDS_DEFINED_

/* CLSID_PAL_Platform = {aba13443-50f7-449f-be24-6b7190b4d871} */
UUID_DEFINE(CLSID_PAL_Platform, 0xab, 0xa1, 0x34, 0x43, 0x50, 0xf7, 0x44, 0x9f, 0xbe, 0x24, 0x6b, 0x71, 0x90, 0xb4, 0xd8, 0x71);
#endif /*INITGUID||!PLATFORM_H_GUIDS_DEFINED_*/
