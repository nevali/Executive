/* DO NOT EDIT: Automatically generated from IDespatchContext.idl by idl */

#ifndef IDespatchContext_FWD_DEFINED
# define IDespatchContext_FWD_DEFINED
typedef struct IDespatchContext IDespatchContext;
#endif

#ifndef IDESPATCHCONTEXT_H_IDL_
# define IDESPATCHCONTEXT_H_IDL_

/* Executive Microkernel
 * IDespatchContext.idl
 *   Represents a task's despatch context
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

/* IDespatchContext version 0.0 */

# ifndef __IDespatchContext_INTERFACE_DEFINED__
#  define __IDespatchContext_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IDespatchContext interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IDespatchContext


DECLARE_INTERFACE_(IDespatchContext, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IDespatchContext */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IDespatchContext_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IDespatchContext_retain(__this) __this->lpVtbl->retain(__this)
#   define IDespatchContext_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IDespatchContext_INTERFACE_DEFINED__*/


#endif /*!IDESPATCHCONTEXT_H_IDL_*/

#if defined(INITGUID) || !defined(IDESPATCHCONTEXT_H_GUIDS_DEFINED_)
# define IDESPATCHCONTEXT_H_GUIDS_DEFINED_

/* IID_IDespatchContext = {75d9e760-48ee-4f9a-a01e-d1a38cf2cd96} */
UUID_DEFINE(IID_IDespatchContext, 0x75, 0xd9, 0xe7, 0x60,  0x48, 0xee, 0x4f, 0x9a, 0xa0, 0x1e, 0xd1, 0xa3, 0x8c, 0xf2, 0xcd, 0x96);
#endif /*INITGUID || !IDESPATCHCONTEXT_H_GUIDS_DEFINED_ */

