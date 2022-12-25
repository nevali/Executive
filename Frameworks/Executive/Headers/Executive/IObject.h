/* DO NOT EDIT: Automatically generated from IObject.idl by idl */

#ifndef IObject_FWD_DEFINED
# define IObject_FWD_DEFINED
typedef struct IObject IObject;
#endif

#ifndef IOBJECT_H_IDL_
# define IOBJECT_H_IDL_

/* Executive Microkernel
 * IObject.idl
 *   Defines COM's root polymorphic interface interface
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
# include <Executive/Types.h>
# include <Executive/UUID.h>
# include <Executive/Errors.h>

/* IObject version 0.0 */

# ifndef __IObject_INTERFACE_DEFINED__
#  define __IObject_INTERFACE_DEFINED__
typedef int DESPATCHID;
#  undef INTEFACE
#  define INTERFACE IObject


DECLARE_INTERFACE(IObject)
{
	BEGIN_INTERFACE

#  ifdef __cplusplus
	static const int32_t IObject_ID_queryInterface = 0;
	static const int32_t IObject_ID_retain = 1;
	static const int32_t IObject_ID_release = 2;

#  else /*__cplusplus*/

#  define IObject_ID_queryInterface 0
#  define IObject_ID_retain 1
#  define IObject_ID_release 2
#  endif /*__cplusplus*/

	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IObject_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IObject_retain(__this) __this->lpVtbl->retain(__this)
#   define IObject_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IObject_INTERFACE_DEFINED__*/

#  define IObject_ID_retain 1
#  define IObject_ID_release 2

#endif /*!IOBJECT_H_IDL_*/

#if defined(INITGUID) || !defined(IOBJECT_H_GUIDS_DEFINED_)
# define IOBJECT_H_GUIDS_DEFINED_

/* IID_IObject = {00000000-0000-0000-c000-000000000046} */
UUID_DEFINE(IID_IObject, 0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
#endif /*INITGUID || !IOBJECT_H_GUIDS_DEFINED_ */

