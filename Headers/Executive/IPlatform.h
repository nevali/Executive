/* DO NOT EDIT: Automatically generated from IPlatform.idl by idl */

#ifndef IPlatform_FWD_DEFINED
# define IPlatform_FWD_DEFINED
typedef struct IPlatform IPlatform;
#endif

#ifndef IPLATFORM_H_IDL_
# define IPLATFORM_H_IDL_

/* Executive Microkernel
 * IPlatform.idl
 *   Defines the Platform interface provided by the PAL to the Executive
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
# include <Executive/IAllocator.h>
# include <Executive/IPlatformDiagnostics.h>

/* IPlatform version 0.0 */

# ifndef __IPlatform_INTERFACE_DEFINED__
#  define __IPlatform_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IPlatform interface is currently considered unstable; source and binary compatibility are not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IPlatform


DECLARE_INTERFACE_(IPlatform, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IPlatform */
	STDMETHOD_(void, panic)(THIS_ const char *string) PURE;
	STDMETHOD_(void, setDefaultAllocator)(THIS_ IAllocator *allocator) PURE;
	STDMETHOD_(void, nap)(THIS) PURE;
	STDMETHOD_(void, phaseDidChange)(THIS_ PHASE newPhase) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IPlatform_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IPlatform_retain(__this) __this->lpVtbl->retain(__this)
#   define IPlatform_release(__this) __this->lpVtbl->release(__this)
#   define IPlatform_panic(__this, string) __this->lpVtbl->panic(__this, string)
#   define IPlatform_setDefaultAllocator(__this, allocator) __this->lpVtbl->setDefaultAllocator(__this, allocator)
#   define IPlatform_nap(__this) __this->lpVtbl->nap(__this)
#   define IPlatform_phaseDidChange(__this, newPhase) __this->lpVtbl->phaseDidChange(__this, newPhase)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IPlatform_INTERFACE_DEFINED__*/


#endif /*!IPLATFORM_H_IDL_*/

#if defined(INITGUID) || !defined(IPLATFORM_H_GUIDS_DEFINED_)
# define IPLATFORM_H_GUIDS_DEFINED_

/* IID_IPlatform = {d02b2658-e5c1-4fce-9ea7-ae39996602c6} */
UUID_DEFINE(IID_IPlatform, 0xd0, 0x2b, 0x26, 0x58,  0xe5, 0xc1, 0x4f, 0xce, 0x9e, 0xa7, 0xae, 0x39, 0x99, 0x66, 0x02, 0xc6);
#endif /*INITGUID || !IPLATFORM_H_GUIDS_DEFINED_ */

