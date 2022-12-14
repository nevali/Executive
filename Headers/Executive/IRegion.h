/* DO NOT EDIT: Automatically generated from IRegion.idl by idl */

#ifndef IRegion_FWD_DEFINED
# define IRegion_FWD_DEFINED
typedef struct IRegion IRegion;
#endif

#ifndef IREGION_H_IDL_
# define IREGION_H_IDL_

/* Executive Microkernel
 * IRegion.idl
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

/* IRegion version 0.0 */

# ifndef __IRegion_INTERFACE_DEFINED__
#  define __IRegion_INTERFACE_DEFINED__
typedef enum 
{
	 	RF_MASK_TYPE = 255,
	 	RF_NORMAL = 0,
	 	RF_TRANSIENT = (1<<0),
	 	RF_DMA = (1<<1),
	 	RF_NOT_BANKED = (1<<2),
	 	RF_PURGEABLE = (1<<3),
	 	RF_STACK = (1<<4),
	 	RF_MASK_OPTIONS = 3840,
	 	RF_NO_WAIT = 256,
	 	RF_UNINITIALIZED = 512,
	 	RF_MASK_PROT = 61440,
	 	RF_NONE = 0,
	 	RF_READ = 4096,
	 	RF_WRITE = 8192,
	 	RF_EXEC = 16384,
	 	RF_MASK_HINTS = 983040,
	 	RF_MASK_LEVEL = 15728640,
	 	RF_LVL_0 = 0,
	 	RF_LVL_1 = (1<<40),
	 	RF_LVL_2 = (2<<40)
}  RegionFlags;
#  undef INTEFACE
#  define INTERFACE IRegion


DECLARE_INTERFACE_(IRegion, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IRegion */
	STDMETHOD_(RegionFlags, flags)(THIS) PURE;
	STDMETHOD_(int, queryOwnerInterface)(THIS_ REFUUID riid, void **ptr) PURE;
	STDMETHOD_(uint8_t*, base)(THIS) PURE;
	STDMETHOD_(size_t, pages)(THIS) PURE;
	STDMETHOD_(size_t, bytes)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IRegion_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IRegion_retain(__this) __this->lpVtbl->retain(__this)
#   define IRegion_release(__this) __this->lpVtbl->release(__this)
#   define IRegion_flags(__this) __this->lpVtbl->flags(__this)
#   define IRegion_queryOwnerInterface(__this, riid, ptr) __this->lpVtbl->queryOwnerInterface(__this, riid, ptr)
#   define IRegion_base(__this) __this->lpVtbl->base(__this)
#   define IRegion_pages(__this) __this->lpVtbl->pages(__this)
#   define IRegion_bytes(__this) __this->lpVtbl->bytes(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IRegion_INTERFACE_DEFINED__*/


#endif /*!IREGION_H_IDL_*/

#if defined(INITGUID) || !defined(IREGION_H_GUIDS_DEFINED_)
# define IREGION_H_GUIDS_DEFINED_

/* IID_IRegion = {e739ecdb-06ec-40c9-95f7-99c22a0c4a7b} */
UUID_DEFINE(IID_IRegion, 0xe7, 0x39, 0xec, 0xdb,  0x06, 0xec, 0x40, 0xc9, 0x95, 0xf7, 0x99, 0xc2, 0x2a, 0x0c, 0x4a, 0x7b);
#endif /*INITGUID || !IREGION_H_GUIDS_DEFINED_ */

