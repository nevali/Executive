/* DO NOT EDIT: Automatically generated from IExecutable.idl by idl */

#ifndef IExecutable_FWD_DEFINED
# define IExecutable_FWD_DEFINED
typedef struct IExecutable IExecutable;
#endif

#ifndef IEXECUTABLE_H_IDL_
# define IEXECUTABLE_H_IDL_

/* Executive Microkernel
 * IExecutable.idl
 *
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
# include <Executive/IObject.h>
# include <Executive/ITask.h>

/* IExecutable version 0.0 */

# ifndef __IExecutable_INTERFACE_DEFINED__
#  define __IExecutable_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IExecutable interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IExecutable


DECLARE_INTERFACE_(IExecutable, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IExecutable */
	STDMETHOD_(TASKID, spawn)(THIS_ const char **args, REFUUID iid, void **out) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IExecutable_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IExecutable_retain(__this) __this->lpVtbl->retain(__this)
#   define IExecutable_release(__this) __this->lpVtbl->release(__this)
#   define IExecutable_spawn(__this, args, iid, out) __this->lpVtbl->spawn(__this, args, iid, out)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IExecutable_INTERFACE_DEFINED__*/


#endif /*!IEXECUTABLE_H_IDL_*/

#if defined(INITGUID) || !defined(IEXECUTABLE_H_GUIDS_DEFINED_)
# define IEXECUTABLE_H_GUIDS_DEFINED_

/* IID_IExecutable = {5f3ad3fa-3b06-4a03-9bef-3fab9763ce83} */
UUID_DEFINE(IID_IExecutable, 0x5f, 0x3a, 0xd3, 0xfa,  0x3b, 0x06, 0x4a, 0x03, 0x9b, 0xef, 0x3f, 0xab, 0x97, 0x63, 0xce, 0x83);
#endif /*INITGUID || !IEXECUTABLE_H_GUIDS_DEFINED_ */

