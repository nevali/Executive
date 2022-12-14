/* DO NOT EDIT: Automatically generated from IMutableContainer.idl by idl */

#ifndef IMutableContainer_FWD_DEFINED
# define IMutableContainer_FWD_DEFINED
typedef struct IMutableContainer IMutableContainer;
#endif

#ifndef IMUTABLECONTAINER_H_IDL_
# define IMUTABLECONTAINER_H_IDL_

/* Executive Microkernel
 * IMutableContainer.idl
 *
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
# include <Executive/IContainer.h>

/* IMutableContainer version 0.0 */

# ifndef __IMutableContainer_INTERFACE_DEFINED__
#  define __IMutableContainer_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IMutableContainer interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IMutableContainer


DECLARE_INTERFACE_(IMutableContainer, IContainer)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IContainer */
	STDMETHOD_(STATUS, resolve)(THIS_ const char *name, IDirectoryEntry **entry) PURE;
	STDMETHOD_(IIterator*, iterator)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IMutableContainer */
	STDMETHOD_(STATUS, create)(THIS_ const char *name, REFUUID clsid, REFUUID iid, void **out) PURE;
	STDMETHOD_(STATUS, add)(THIS_ const char *name, REFUUID clsid, IObject *target) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IMutableContainer_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IMutableContainer_retain(__this) __this->lpVtbl->retain(__this)
#   define IMutableContainer_release(__this) __this->lpVtbl->release(__this)
#   define IMutableContainer_resolve(__this, name, entry) __this->lpVtbl->resolve(__this, name, entry)
#   define IMutableContainer_iterator(__this) __this->lpVtbl->iterator(__this)
#   define IMutableContainer_create(__this, name, clsid, iid, out) __this->lpVtbl->create(__this, name, clsid, iid, out)
#   define IMutableContainer_add(__this, name, clsid, target) __this->lpVtbl->add(__this, name, clsid, target)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IMutableContainer_INTERFACE_DEFINED__*/


#endif /*!IMUTABLECONTAINER_H_IDL_*/

#if defined(INITGUID) || !defined(IMUTABLECONTAINER_H_GUIDS_DEFINED_)
# define IMUTABLECONTAINER_H_GUIDS_DEFINED_

/* IID_IMutableContainer = {bf8f706d-24ed-4646-b8d7-954239ec71e9} */
UUID_DEFINE(IID_IMutableContainer, 0xbf, 0x8f, 0x70, 0x6d,  0x24, 0xed, 0x46, 0x46, 0xb8, 0xd7, 0x95, 0x42, 0x39, 0xec, 0x71, 0xe9);
#endif /*INITGUID || !IMUTABLECONTAINER_H_GUIDS_DEFINED_ */

