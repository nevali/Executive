/* DO NOT EDIT: Automatically generated from ILink.idl by idl */

#ifndef ILink_FWD_DEFINED
# define ILink_FWD_DEFINED
typedef struct ILink ILink;
#endif

#ifndef ILINK_H_IDL_
# define ILINK_H_IDL_

/* Executive Microkernel
 * ILink.idl
 *   Represents a link to another object
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

/* ILink version 0.0 */

# ifndef __ILink_INTERFACE_DEFINED__
#  define __ILink_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The ILink interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE ILink


DECLARE_INTERFACE_(ILink, IObject)
{
	BEGIN_INTERFACE

#  ifdef __cplusplus
	static const int32_t ILink_ID__MIN_ = 144;
	static const int32_t ILink_ID_target = ILink_ID__MIN_;
	static const int32_t ILink_ID__MAX_ = ILink_ID_target;

#  else /*__cplusplus*/

#  define ILink_ID__MIN_ 144
#  define ILink_ID_target ILink_ID__MIN_
#  define ILink_ID__MAX_ ILink_ID_target
#  endif /*__cplusplus*/

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ILink */
	STDMETHOD_(STATUS, target)(THIS_ char *buf, size_t buflen) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define ILink_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define ILink_retain(__this) __this->lpVtbl->retain(__this)
#   define ILink_release(__this) __this->lpVtbl->release(__this)
#   define ILink_target(__this, buf, buflen) __this->lpVtbl->target(__this, buf, buflen)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__ILink_INTERFACE_DEFINED__*/

#  define ILink_ID__MAX_ ILink_ID_target

#endif /*!ILINK_H_IDL_*/

#if defined(INITGUID) || !defined(ILINK_H_GUIDS_DEFINED_)
# define ILINK_H_GUIDS_DEFINED_

/* IID_ILink = {75d9e760-48ee-4f9a-a01e-d1a38cf2cd96} */
UUID_DEFINE(IID_ILink, 0x75, 0xd9, 0xe7, 0x60,  0x48, 0xee, 0x4f, 0x9a, 0xa0, 0x1e, 0xd1, 0xa3, 0x8c, 0xf2, 0xcd, 0x96);
#endif /*INITGUID || !ILINK_H_GUIDS_DEFINED_ */

