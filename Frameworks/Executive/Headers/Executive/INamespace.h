/* DO NOT EDIT: Automatically generated from INamespace.idl by idl */

#ifndef INamespace_FWD_DEFINED
# define INamespace_FWD_DEFINED
typedef struct INamespace INamespace;
#endif

#ifndef INAMESPACE_H_IDL_
# define INAMESPACE_H_IDL_

/* Executive Microkernel
 * INamespace.idl
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

/* INamespace version 0.0 */

# ifndef __INamespace_INTERFACE_DEFINED__
#  define __INamespace_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The INamespace interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE INamespace


DECLARE_INTERFACE_(INamespace, IContainer)
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

	/* INamespace */
	STDMETHOD_(STATUS, resolveEntry)(THIS_ const char *path, IContainer *scope, IDirectoryEntry **dentry) PURE;
	STDMETHOD_(STATUS, resolveContainer)(THIS_ const char *path, IContainer *scope, IContainer **container, const char **basename) PURE;
	STDMETHOD_(STATUS, open)(THIS_ const char *path, IContainer *scope, REFUUID iid, void **container) PURE;
	STDMETHOD_(STATUS, create)(THIS_ const char *name, IContainer *scope, REFUUID clsid, REFUUID iid, void **container) PURE;
	STDMETHOD_(STATUS, add)(THIS_ const char *name, IContainer *scope, REFUUID clsid, IObject *target) PURE;
	STDMETHOD_(STATUS, createLink)(THIS_ const char *name, IContainer *scope, const char *target, bool force) PURE;
	STDMETHOD_(STATUS, setFlags)(THIS_ const char *name, IContainer *scope, DirectoryEntryFlags flags) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define INamespace_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define INamespace_retain(__this) __this->lpVtbl->retain(__this)
#   define INamespace_release(__this) __this->lpVtbl->release(__this)
#   define INamespace_resolve(__this, name, entry) __this->lpVtbl->resolve(__this, name, entry)
#   define INamespace_iterator(__this) __this->lpVtbl->iterator(__this)
#   define INamespace_resolveEntry(__this, path, scope, dentry) __this->lpVtbl->resolveEntry(__this, path, scope, dentry)
#   define INamespace_resolveContainer(__this, path, scope, container, basename) __this->lpVtbl->resolveContainer(__this, path, scope, container, basename)
#   define INamespace_open(__this, path, scope, iid, container) __this->lpVtbl->open(__this, path, scope, iid, container)
#   define INamespace_create(__this, name, scope, clsid, iid, container) __this->lpVtbl->create(__this, name, scope, clsid, iid, container)
#   define INamespace_add(__this, name, scope, clsid, target) __this->lpVtbl->add(__this, name, scope, clsid, target)
#   define INamespace_createLink(__this, name, scope, target, force) __this->lpVtbl->createLink(__this, name, scope, target, force)
#   define INamespace_setFlags(__this, name, scope, flags) __this->lpVtbl->setFlags(__this, name, scope, flags)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__INamespace_INTERFACE_DEFINED__*/


#endif /*!INAMESPACE_H_IDL_*/

#if defined(INITGUID) || !defined(INAMESPACE_H_GUIDS_DEFINED_)
# define INAMESPACE_H_GUIDS_DEFINED_

/* IID_INamespace = {444137ec-a886-480e-9ac9-5f5688ed71f9} */
UUID_DEFINE(IID_INamespace, 0x44, 0x41, 0x37, 0xec,  0xa8, 0x86, 0x48, 0x0e, 0x9a, 0xc9, 0x5f, 0x56, 0x88, 0xed, 0x71, 0xf9);
#endif /*INITGUID || !INAMESPACE_H_GUIDS_DEFINED_ */

