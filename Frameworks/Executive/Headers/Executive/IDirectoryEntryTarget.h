/* DO NOT EDIT: Automatically generated from IDirectoryEntryTarget.idl by idl */

#ifndef IDirectoryEntryTarget_FWD_DEFINED
# define IDirectoryEntryTarget_FWD_DEFINED
typedef struct IDirectoryEntryTarget IDirectoryEntryTarget;
#endif

#ifndef IDIRECTORYENTRYTARGET_H_IDL_
# define IDIRECTORYENTRYTARGET_H_IDL_

/* Executive Microkernel
 * IDirectoryEntryTarget.idl
 *   Interface implemented by objects created by classes
 *   implementing the MDirectoryEntryTarget metaclass interface
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

/* IDirectoryEntryTarget version 0.0 */

# ifndef __IDirectoryEntryTarget_INTERFACE_DEFINED__
#  define __IDirectoryEntryTarget_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IDirectoryEntryTarget interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IDirectoryEntryTarget


DECLARE_INTERFACE_(IDirectoryEntryTarget, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IDirectoryEntryTarget */
	STDMETHOD_(void, linked)(THIS_ IDirectoryEntry *dirent) PURE;
	STDMETHOD_(void, unlinked)(THIS_ IDirectoryEntry *dirent) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IDirectoryEntryTarget_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IDirectoryEntryTarget_retain(__this) __this->lpVtbl->retain(__this)
#   define IDirectoryEntryTarget_release(__this) __this->lpVtbl->release(__this)
#   define IDirectoryEntryTarget_linked(__this, dirent) __this->lpVtbl->linked(__this, dirent)
#   define IDirectoryEntryTarget_unlinked(__this, dirent) __this->lpVtbl->unlinked(__this, dirent)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IDirectoryEntryTarget_INTERFACE_DEFINED__*/


#endif /*!IDIRECTORYENTRYTARGET_H_IDL_*/

#if defined(INITGUID) || !defined(IDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_)
# define IDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_

/* IID_IDirectoryEntryTarget = {7f01159e-af02-4ab6-9349-6abd0773afcf} */
UUID_DEFINE(IID_IDirectoryEntryTarget, 0x7f, 0x01, 0x15, 0x9e,  0xaf, 0x02, 0x4a, 0xb6, 0x93, 0x49, 0x6a, 0xbd, 0x07, 0x73, 0xaf, 0xcf);
#endif /*INITGUID || !IDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_ */

