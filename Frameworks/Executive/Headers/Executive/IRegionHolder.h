/* DO NOT EDIT: Automatically generated from IRegionHolder.idl by idl */

#ifndef IRegionHolder_FWD_DEFINED
# define IRegionHolder_FWD_DEFINED
typedef struct IRegionHolder IRegionHolder;
#endif

#ifndef IREGIONHOLDER_H_IDL_
# define IREGIONHOLDER_H_IDL_

/* Executive Microkernel
 * IRegionHolder.idl
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

/* IRegionHolder version 0.0 */

# ifndef __IRegionHolder_INTERFACE_DEFINED__
#  define __IRegionHolder_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IRegionHolder interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IRegionHolder


DECLARE_INTERFACE_(IRegionHolder, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IRegionHolder */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IRegionHolder_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IRegionHolder_retain(__this) __this->lpVtbl->retain(__this)
#   define IRegionHolder_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IRegionHolder_INTERFACE_DEFINED__*/


#endif /*!IREGIONHOLDER_H_IDL_*/

#if defined(INITGUID) || !defined(IREGIONHOLDER_H_GUIDS_DEFINED_)
# define IREGIONHOLDER_H_GUIDS_DEFINED_

/* IID_IRegionHolder = {d21b6d73-7803-4fa4-ba93-d73498d2d655} */
UUID_DEFINE(IID_IRegionHolder, 0xd2, 0x1b, 0x6d, 0x73,  0x78, 0x03, 0x4f, 0xa4, 0xba, 0x93, 0xd7, 0x34, 0x98, 0xd2, 0xd6, 0x55);
#endif /*INITGUID || !IREGIONHOLDER_H_GUIDS_DEFINED_ */

