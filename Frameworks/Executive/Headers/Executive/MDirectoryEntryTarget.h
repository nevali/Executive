/* DO NOT EDIT: Automatically generated from MDirectoryEntryTarget.idl by idl */

#ifndef MDirectoryEntryTarget_FWD_DEFINED
# define MDirectoryEntryTarget_FWD_DEFINED
typedef struct MDirectoryEntryTarget MDirectoryEntryTarget;
#endif

#ifndef MDIRECTORYENTRYTARGET_H_IDL_
# define MDIRECTORYENTRYTARGET_H_IDL_

/* Executive Microkernel
 * MDirectoryEntryTarget.idl
 *   Metaclass interface used in the creation of directory entries
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
# include <Executive/IDirectoryEntryTarget.h>

/* MDirectoryEntryTarget version 0.0 */

# ifndef __MDirectoryEntryTarget_INTERFACE_DEFINED__
#  define __MDirectoryEntryTarget_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The MDirectoryEntryTarget interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE MDirectoryEntryTarget


DECLARE_INTERFACE_(MDirectoryEntryTarget, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* MDirectoryEntryTarget */
	STDMETHOD_(STATUS, createInstance)(THIS_ IDirectoryEntry *dirEntry, IDirectoryEntryTarget **out) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define MDirectoryEntryTarget_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define MDirectoryEntryTarget_retain(__this) __this->lpVtbl->retain(__this)
#   define MDirectoryEntryTarget_release(__this) __this->lpVtbl->release(__this)
#   define MDirectoryEntryTarget_createInstance(__this, dirEntry, out) __this->lpVtbl->createInstance(__this, dirEntry, out)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__MDirectoryEntryTarget_INTERFACE_DEFINED__*/


#endif /*!MDIRECTORYENTRYTARGET_H_IDL_*/

#if defined(INITGUID) || !defined(MDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_)
# define MDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_

/* IID_MDirectoryEntryTarget = {2c71beb1-3296-4fc5-b9fb-7aac6654be36} */
UUID_DEFINE(IID_MDirectoryEntryTarget, 0x2c, 0x71, 0xbe, 0xb1,  0x32, 0x96, 0x4f, 0xc5, 0xb9, 0xfb, 0x7a, 0xac, 0x66, 0x54, 0xbe, 0x36);
#endif /*INITGUID || !MDIRECTORYENTRYTARGET_H_GUIDS_DEFINED_ */

