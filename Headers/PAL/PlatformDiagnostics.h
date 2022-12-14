/* Executive Microkernel
 *   Headers/PAL/PlaformDiagnostics.h
 *   Defines the well-known PlatformDiagnostics metaclass provided by the PAL
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

#ifndef EXECUTIVE_PAL_PLATFORMDIAGNOSTICS_H_
# define EXECUTIVE_PAL_PLATFORMDIAGNOSTICS_H_ 1

# include <Executive/IPlatformDiagnostics.h>

#endif /*!EXECUTIVE_PAL_PLATFORMDIAGNOSTICS_H_*/

#if defined(INITGUID) || !defined(PLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_)
# define PLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_

/* CLSID_PAL_PlatformDiagnostics = {d3 b7 b5 17-9dac-4eca-8012-cf ec b5 76 e5 69} */
UUID_DEFINE(CLSID_PAL_PlatformDiagnostics, 0xd3, 0xb7, 0xb5, 0x17, 0x9d, 0xac, 0x4a, 0xca, 0x80, 0x12, 0xcf, 0xec, 0xb5, 0x76, 0xe5, 0x69);
#endif /*INITGUID||!PLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_*/
