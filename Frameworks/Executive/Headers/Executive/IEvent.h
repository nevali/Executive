/* DO NOT EDIT: Automatically generated from IEvent.idl by idl */

#ifndef IEvent_FWD_DEFINED
# define IEvent_FWD_DEFINED
typedef struct IEvent IEvent;
#endif

#ifndef IEVENT_H_IDL_
# define IEVENT_H_IDL_

/* Executive Microkernel
 * IEvent.idl
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

/* IEvent version 0.0 */

# ifndef __IEvent_INTERFACE_DEFINED__
#  define __IEvent_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IEvent interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IEvent


DECLARE_INTERFACE_(IEvent, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IEvent */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IEvent_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IEvent_retain(__this) __this->lpVtbl->retain(__this)
#   define IEvent_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IEvent_INTERFACE_DEFINED__*/


#endif /*!IEVENT_H_IDL_*/

#if defined(INITGUID) || !defined(IEVENT_H_GUIDS_DEFINED_)
# define IEVENT_H_GUIDS_DEFINED_

/* IID_IEvent = {0998ed4b-8885-4781-813d-7671215e0208} */
UUID_DEFINE(IID_IEvent, 0x09, 0x98, 0xed, 0x4b,  0x88, 0x85, 0x47, 0x81, 0x81, 0x3d, 0x76, 0x71, 0x21, 0x5e, 0x02, 0x08);
#endif /*INITGUID || !IEVENT_H_GUIDS_DEFINED_ */

