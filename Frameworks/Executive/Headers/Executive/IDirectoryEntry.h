/* DO NOT EDIT: Automatically generated from IDirectoryEntry.idl by idl */

#ifndef IDirectoryEntry_FWD_DEFINED
# define IDirectoryEntry_FWD_DEFINED
typedef struct IDirectoryEntry IDirectoryEntry;
#endif

#ifndef IDIRECTORYENTRY_H_IDL_
# define IDIRECTORYENTRY_H_IDL_

/* Executive Microkernel
 * IDirectoryEntry.idl
 *   Represents an entry in the Object Directory
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

/* IDirectoryEntry version 0.0 */

# ifndef __IDirectoryEntry_INTERFACE_DEFINED__
#  define __IDirectoryEntry_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IDirectoryEntry interface is currently considered unstable; source and binary compatibility is not assured.
#endif
typedef enum 
{
	 	DEF_NONE = 0,
	 	DEF_SYSTEM = (1<<0),
	 	DEF_CONTAINER = (1<<1),
	 	DEF_IMMUTABLE = (1<<2),
	 	DEF_HIDDEN = (1<<3),
	 	DEF_LINK = (1<<4),
	 	DEF_VOID = (1<<5),
	 	DEF_MOUNTPOINT = (1<<6)
}  DirectoryEntryFlags;
#  undef INTEFACE
#  define INTERFACE IDirectoryEntry


DECLARE_INTERFACE_(IDirectoryEntry, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IDirectoryEntry */
	STDMETHOD_(STATUS, queryTargetInterface)(THIS_ REFUUID iid, void **out) PURE;
	STDMETHOD_(const char*, name)(THIS) PURE;
	STDMETHOD_(void, classid)(THIS_ UUID *clsid) PURE;
	STDMETHOD_(DirectoryEntryFlags, flags)(THIS) PURE;
	STDMETHOD_(STATUS, setFlags)(THIS_ DirectoryEntryFlags flags) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IDirectoryEntry_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IDirectoryEntry_retain(__this) __this->lpVtbl->retain(__this)
#   define IDirectoryEntry_release(__this) __this->lpVtbl->release(__this)
#   define IDirectoryEntry_queryTargetInterface(__this, iid, out) __this->lpVtbl->queryTargetInterface(__this, iid, out)
#   define IDirectoryEntry_name(__this) __this->lpVtbl->name(__this)
#   define IDirectoryEntry_classid(__this, clsid) __this->lpVtbl->classid(__this, clsid)
#   define IDirectoryEntry_flags(__this) __this->lpVtbl->flags(__this)
#   define IDirectoryEntry_setFlags(__this, flags) __this->lpVtbl->setFlags(__this, flags)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IDirectoryEntry_INTERFACE_DEFINED__*/


#endif /*!IDIRECTORYENTRY_H_IDL_*/

#if defined(INITGUID) || !defined(IDIRECTORYENTRY_H_GUIDS_DEFINED_)
# define IDIRECTORYENTRY_H_GUIDS_DEFINED_

/* IID_IDirectoryEntry = {4a285022-c781-437c-94ef-44254bd51bd3} */
UUID_DEFINE(IID_IDirectoryEntry, 0x4a, 0x28, 0x50, 0x22,  0xc7, 0x81, 0x43, 0x7c, 0x94, 0xef, 0x44, 0x25, 0x4b, 0xd5, 0x1b, 0xd3);
#endif /*INITGUID || !IDIRECTORYENTRY_H_GUIDS_DEFINED_ */

