/* DO NOT EDIT: Automatically generated from IAddressSpace.idl by idl */

#ifndef IAddressSpace_FWD_DEFINED
# define IAddressSpace_FWD_DEFINED
typedef struct IAddressSpace IAddressSpace;
#endif

#ifndef IADDRESSSPACE_H_IDL_
# define IADDRESSSPACE_H_IDL_

/* Executive Microkernel
 * IAddressSpace.idl
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
# include <Executive/IContext.h>
# include <Executive/IThread.h>

/* IAddressSpace version 0.0 */

# ifndef __IAddressSpace_INTERFACE_DEFINED__
#  define __IAddressSpace_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IAddressSpace interface is currently considered unstable; source and binary compatibility is not assured.
#endif
typedef enum 
{
	 	ASF_NONE = 0
}  AddressSpaceFeatures;
#  undef INTEFACE
#  define INTERFACE IAddressSpace


DECLARE_INTERFACE_(IAddressSpace, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IAddressSpace */
	STDMETHOD_(STATUS, regionFromPointer)(THIS_ void *ptr, IRegion **region) PURE;
	STDMETHOD_(int, pageSize)(THIS) PURE;
	STDMETHOD_(STATUS, obtainRegion)(THIS_ size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) PURE;
	STDMETHOD_(STATUS, obtainTransientRegion)(THIS_ size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **region) PURE;
	STDMETHOD_(STATUS, createContext)(THIS_ IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **context) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IAddressSpace_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IAddressSpace_retain(__this) __this->lpVtbl->retain(__this)
#   define IAddressSpace_release(__this) __this->lpVtbl->release(__this)
#   define IAddressSpace_regionFromPointer(__this, ptr, region) __this->lpVtbl->regionFromPointer(__this, ptr, region)
#   define IAddressSpace_pageSize(__this) __this->lpVtbl->pageSize(__this)
#   define IAddressSpace_obtainRegion(__this, count, flags, owner, region) __this->lpVtbl->obtainRegion(__this, count, flags, owner, region)
#   define IAddressSpace_obtainTransientRegion(__this, count, flags, owner, region) __this->lpVtbl->obtainTransientRegion(__this, count, flags, owner, region)
#   define IAddressSpace_createContext(__this, thread, stackBase, stackSize, ip, context) __this->lpVtbl->createContext(__this, thread, stackBase, stackSize, ip, context)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IAddressSpace_INTERFACE_DEFINED__*/


#endif /*!IADDRESSSPACE_H_IDL_*/

#if defined(INITGUID) || !defined(IADDRESSSPACE_H_GUIDS_DEFINED_)
# define IADDRESSSPACE_H_GUIDS_DEFINED_

/* IID_IAddressSpace = {f037af3e-a41f-4813-b2dc-69bf96049bf2} */
UUID_DEFINE(IID_IAddressSpace, 0xf0, 0x37, 0xaf, 0x3e,  0xa4, 0x1f, 0x48, 0x13, 0xb2, 0xdc, 0x69, 0xbf, 0x96, 0x04, 0x9b, 0xf2);
#endif /*INITGUID || !IADDRESSSPACE_H_GUIDS_DEFINED_ */

