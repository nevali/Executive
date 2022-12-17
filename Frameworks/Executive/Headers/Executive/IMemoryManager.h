/* DO NOT EDIT: Automatically generated from IMemoryManager.idl by idl */

#ifndef IMemoryManager_FWD_DEFINED
# define IMemoryManager_FWD_DEFINED
typedef struct IMemoryManager IMemoryManager;
#endif

#ifndef IMEMORYMANAGER_H_IDL_
# define IMEMORYMANAGER_H_IDL_

/* Executive Microkernel
 * IMemoryManager.idl
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
# include <Executive/IObject.h>
# include <Executive/IRegion.h>
# include <Executive/IRegionHolder.h>

/* IMemoryManager version 0.0 */

# ifndef __IMemoryManager_INTERFACE_DEFINED__
#  define __IMemoryManager_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IMemoryManager interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IMemoryManager


DECLARE_INTERFACE_(IMemoryManager, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IMemoryManager */
	STDMETHOD_(int, regionFromPointer)(THIS_ void *ptr, IRegion **region) PURE;
	STDMETHOD_(int, pageSize)(THIS) PURE;
	STDMETHOD_(int, obtainRegion)(THIS_ size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) PURE;
	STDMETHOD_(int, obtainTransientRegion)(THIS_ size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IMemoryManager_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IMemoryManager_retain(__this) __this->lpVtbl->retain(__this)
#   define IMemoryManager_release(__this) __this->lpVtbl->release(__this)
#   define IMemoryManager_regionFromPointer(__this, ptr, region) __this->lpVtbl->regionFromPointer(__this, ptr, region)
#   define IMemoryManager_pageSize(__this) __this->lpVtbl->pageSize(__this)
#   define IMemoryManager_obtainRegion(__this, count, flags, owner, region) __this->lpVtbl->obtainRegion(__this, count, flags, owner, region)
#   define IMemoryManager_obtainTransientRegion(__this, count, flags, owner, region) __this->lpVtbl->obtainTransientRegion(__this, count, flags, owner, region)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IMemoryManager_INTERFACE_DEFINED__*/


#endif /*!IMEMORYMANAGER_H_IDL_*/

#if defined(INITGUID) || !defined(IMEMORYMANAGER_H_GUIDS_DEFINED_)
# define IMEMORYMANAGER_H_GUIDS_DEFINED_

/* IID_IMemoryManager = {f037af3e-a41f-4813-b2dc-69bf96049bf2} */
UUID_DEFINE(IID_IMemoryManager, 0xf0, 0x37, 0xaf, 0x3e,  0xa4, 0x1f, 0x48, 0x13, 0xb2, 0xdc, 0x69, 0xbf, 0x96, 0x04, 0x9b, 0xf2);
#endif /*INITGUID || !IMEMORYMANAGER_H_GUIDS_DEFINED_ */

