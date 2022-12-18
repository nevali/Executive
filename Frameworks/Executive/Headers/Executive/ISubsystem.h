/* DO NOT EDIT: Automatically generated from ISubsystem.idl by idl */

#ifndef ISubsystem_FWD_DEFINED
# define ISubsystem_FWD_DEFINED
typedef struct ISubsystem ISubsystem;
#endif

#ifndef ISUBSYSTEM_H_IDL_
# define ISUBSYSTEM_H_IDL_

/* Executive Microkernel
 * ISubsystem.idl
 *   Defines the interface provided by subsystems
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

/* ISubsystem version 0.0 */

# ifndef __ISubsystem_INTERFACE_DEFINED__
#  define __ISubsystem_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The ISubsystem interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE ISubsystem


DECLARE_INTERFACE_(ISubsystem, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ISubsystem */
	STDMETHOD_(STATUS, start)(THIS_ INamespace *root) PURE;
	STDMETHOD_(STATUS, stop)(THIS_ INamespace *root) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define ISubsystem_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define ISubsystem_retain(__this) __this->lpVtbl->retain(__this)
#   define ISubsystem_release(__this) __this->lpVtbl->release(__this)
#   define ISubsystem_start(__this, root) __this->lpVtbl->start(__this, root)
#   define ISubsystem_stop(__this, root) __this->lpVtbl->stop(__this, root)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__ISubsystem_INTERFACE_DEFINED__*/


#endif /*!ISUBSYSTEM_H_IDL_*/

#if defined(INITGUID) || !defined(ISUBSYSTEM_H_GUIDS_DEFINED_)
# define ISUBSYSTEM_H_GUIDS_DEFINED_

/* IID_ISubsystem = {742c829a-5a7e-4cc2-a7f1-cace01237120} */
UUID_DEFINE(IID_ISubsystem, 0x74, 0x2c, 0x82, 0x9a,  0x5a, 0x7e, 0x4c, 0xc2, 0xa7, 0xf1, 0xca, 0xce, 0x01, 0x23, 0x71, 0x20);
#endif /*INITGUID || !ISUBSYSTEM_H_GUIDS_DEFINED_ */

