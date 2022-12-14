/* DO NOT EDIT: Automatically generated from IBootEnvironment.idl by idl */

#ifndef IBootEnvironment_FWD_DEFINED
# define IBootEnvironment_FWD_DEFINED
typedef struct IBootEnvironment IBootEnvironment;
#endif

#ifndef IBOOTENVIRONMENT_H_IDL_
# define IBOOTENVIRONMENT_H_IDL_

/* Executive Microkernel
 * IBootEnvironment.idl
 *   Defines the Boot Environment interface
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

/* IBootEnvironment version 0.0 */

# ifndef __IBootEnvironment_INTERFACE_DEFINED__
#  define __IBootEnvironment_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IBootEnvironment interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IBootEnvironment


DECLARE_INTERFACE_(IBootEnvironment, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IBootEnvironment */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IBootEnvironment_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IBootEnvironment_retain(__this) __this->lpVtbl->retain(__this)
#   define IBootEnvironment_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IBootEnvironment_INTERFACE_DEFINED__*/


#endif /*!IBOOTENVIRONMENT_H_IDL_*/

#if defined(INITGUID) || !defined(IBOOTENVIRONMENT_H_GUIDS_DEFINED_)
# define IBOOTENVIRONMENT_H_GUIDS_DEFINED_

/* IID_IBootEnvironment = {f12bc7d1-e414-4075-84bd-d5712291f283} */
UUID_DEFINE(IID_IBootEnvironment, 0xf1, 0x2b, 0xc7, 0xd1,  0xe4, 0x14, 0x40, 0x75, 0x84, 0xbd, 0xd5, 0x71, 0x22, 0x91, 0xf2, 0x83);
#endif /*INITGUID || !IBOOTENVIRONMENT_H_GUIDS_DEFINED_ */

