/* DO NOT EDIT: Automatically generated from Errors.idl by idl */

#ifndef ERRORS_H_IDL_
# define ERRORS_H_IDL_

/* Executive Microkernel
 * Errors.idl
 *   Defines error codes used by the Executive
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

# include <Executive/Types.h>

/* Errors version 0.0 */

# ifndef __Errors_INTERFACE_DEFINED__
#  define __Errors_INTERFACE_DEFINED__
typedef int STATUS;
#  define E_SUCCESS 0
#  define E_BADOBJ -6
#  define E_NOTIMPL -7
#  define E_INVAL -8
#  define E_PERM -1
#  define E_ACCESS -2
#  define E_NOENT -5
#  define E_EXISTS -9
#  define E_EOF -10
#  define E_NOT_CONTAINER -11
#  define E_NOTDIR E_NOT_CONTAINER
#  define E_NOMEM -3
#  define E_IO -4
#  define E_USER -1024
#  define E_MAX -4095
#  undef INTERFACE
# endif /*!__Errors_INTERFACE_DEFINED__*/


#endif /*!ERRORS_H_IDL_*/

