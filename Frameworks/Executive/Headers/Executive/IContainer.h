/* DO NOT EDIT: Automatically generated from IContainer.idl by idl */

#ifndef IContainer_FWD_DEFINED
# define IContainer_FWD_DEFINED
typedef struct IContainer IContainer;
#endif

#ifndef ICONTAINER_H_IDL_
# define ICONTAINER_H_IDL_

/* Executive Microkernel
 * IContainer.idl
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
# include <Executive/IDirectoryEntry.h>
# include <Executive/IIterator.h>

/* IContainer version 0.0 */

# ifndef __IContainer_INTERFACE_DEFINED__
#  define __IContainer_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IContainer interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IContainer


DECLARE_INTERFACE_(IContainer, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IContainer */
	STDMETHOD_(STATUS, resolve)(THIS_ const char *name, IDirectoryEntry **entry) PURE;
	STDMETHOD_(IIterator*, iterator)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IContainer_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IContainer_retain(__this) __this->lpVtbl->retain(__this)
#   define IContainer_release(__this) __this->lpVtbl->release(__this)
#   define IContainer_resolve(__this, name, entry) __this->lpVtbl->resolve(__this, name, entry)
#   define IContainer_iterator(__this) __this->lpVtbl->iterator(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IContainer_INTERFACE_DEFINED__*/


#endif /*!ICONTAINER_H_IDL_*/

#if defined(INITGUID) || !defined(ICONTAINER_H_GUIDS_DEFINED_)
# define ICONTAINER_H_GUIDS_DEFINED_

/* IID_IContainer = {46dbd10a-0915-4350-a689-f44ce9db70d2} */
UUID_DEFINE(IID_IContainer, 0x46, 0xdb, 0xd1, 0x0a,  0x09, 0x15, 0x43, 0x50, 0xa6, 0x89, 0xf4, 0x4c, 0xe9, 0xdb, 0x70, 0xd2);
#endif /*INITGUID || !ICONTAINER_H_GUIDS_DEFINED_ */

