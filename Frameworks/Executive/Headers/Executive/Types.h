/* DO NOT EDIT: Automatically generated from Types.idl by idl */

#ifndef TYPES_H_IDL_
# define TYPES_H_IDL_

/* Executive Microkernel
 * Types.idl
 *   Defines core types used by the Executive
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

#include <Executive/Linkage.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# if __STDC_VERSION__ >= 199901L
#  ifndef __cplusplus
#   include <stdbool.h>
#  endif
#  include <stdalign.h>
#  include <stdnoreturn.h>
# endif /*C99*/
#endif /*__STDC__*/
#if defined(__arm64__) || defined(__aarch64__)
# include <Executive/arm64/Types.h>
#else
# error unsupported or unrecognised host architecture
#endif

/* Types version 0.0 */

# ifndef __Types_INTERFACE_DEFINED__
#  define __Types_INTERFACE_DEFINED__
typedef int32_t REFCOUNT;
#if 0 /*IDL-ONLY*/
typedef void *va_list;
typedef uint32_t size_t;
typedef int32_t ptrdiff_t;
#endif /*IDL-ONLY*/
#  undef INTERFACE
# endif /*!__Types_INTERFACE_DEFINED__*/


#endif /*!TYPES_H_IDL_*/

