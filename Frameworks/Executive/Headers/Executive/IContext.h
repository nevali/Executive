/* DO NOT EDIT: Automatically generated from IContext.idl by idl */

#ifndef IContext_FWD_DEFINED
# define IContext_FWD_DEFINED
typedef struct IContext IContext;
#endif

#ifndef ICONTEXT_H_IDL_
# define ICONTEXT_H_IDL_

/* Executive Microkernel
 * IContext.idl
 *   Represents a scheduling context
 */

/* Copyright 2015-2022 Mo McRoberts.
 *
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
# include <Executive/IRegion.h>
# include <Executive/IRegionHolder.h>

/* IContext version 0.0 */

# ifndef __IContext_INTERFACE_DEFINED__
#  define __IContext_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IContext interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IContext


DECLARE_INTERFACE_(IContext, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IContext */
	STDMETHOD_(bool, swap)(THIS_ IContext *other) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IContext_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IContext_retain(__this) __this->lpVtbl->retain(__this)
#   define IContext_release(__this) __this->lpVtbl->release(__this)
#   define IContext_swap(__this, other) __this->lpVtbl->swap(__this, other)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IContext_INTERFACE_DEFINED__*/


#endif /*!ICONTEXT_H_IDL_*/

#if defined(INITGUID) || !defined(ICONTEXT_H_GUIDS_DEFINED_)
# define ICONTEXT_H_GUIDS_DEFINED_

/* IID_IContext = {5bd135fc-3380-4b6b-9d6c-86da269897bb} */
UUID_DEFINE(IID_IContext, 0x5b, 0xd1, 0x35, 0xfc,  0x33, 0x80, 0x4b, 0x6b, 0x9d, 0x6c, 0x86, 0xda, 0x26, 0x98, 0x97, 0xbb);
#endif /*INITGUID || !ICONTEXT_H_GUIDS_DEFINED_ */

