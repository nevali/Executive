/* Executive Microkernel
 *  Headers/PAL/PAL.h
 *  Defines the interface between the Executive and the PAL */

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

#ifndef PAL_PAL_H_
# define PAL_PAL_H_          1

# include <Executive/IPlatform.h>
# include <PAL/Platform.h>
# include <PAL/MemoryManager.h>
# include <PAL/BootEnvironment.h>
# include <PAL/PlatformDiagnostics.h>

# ifndef PAL_LINKAGE__
#  define PAL_LINKAGE__(sym, version)  WEAK_IMPORT__ SYM__("PAL", sym, version)
# endif

/* Obtain an interface pointer to the metaclass for the well-known clsid */
extern int PAL_metaClass(REFUUID clsid, REFUUID iid, void **out) PAL_LINKAGE__(metaClass, "0.0");
/* Immediately halt the system */
extern void PAL_panic(const char *string) PAL_LINKAGE__(__panic, "0.0");

#endif /*!PAL_PAL_H_*/
