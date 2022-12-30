/* DO NOT EDIT: Automatically generated from IIterator.idl by idl */

#ifndef IIterator_FWD_DEFINED
# define IIterator_FWD_DEFINED
typedef struct IIterator IIterator;
#endif

#ifndef IITERATOR_H_IDL_
# define IITERATOR_H_IDL_

/* Executive Microkernel
 * IIterator.idl
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

/* IIterator version 0.0 */

# ifndef __IIterator_INTERFACE_DEFINED__
#  define __IIterator_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IIterator interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IIterator


DECLARE_INTERFACE_(IIterator, IObject)
{
	BEGIN_INTERFACE

#  ifdef __cplusplus
	static const int32_t IIterator_ID__MIN_ = 128;
	static const int32_t IIterator_ID_next = IIterator_ID__MIN_;
	static const int32_t IIterator_ID_current = IIterator_ID_next+1;
	static const int32_t IITerator_ID__MAX_ = IIterator_ID_current;

#  else /*__cplusplus*/

#  define IIterator_ID__MIN_ 128
#  define IIterator_ID_next IIterator_ID__MIN_
#  define IIterator_ID_current IIterator_ID_next+1
#  define IITerator_ID__MAX_ IIterator_ID_current
#  endif /*__cplusplus*/

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IIterator */
	STDMETHOD_(STATUS, next)(THIS) PURE;
	STDMETHOD_(IObject*, current)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IIterator_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IIterator_retain(__this) __this->lpVtbl->retain(__this)
#   define IIterator_release(__this) __this->lpVtbl->release(__this)
#   define IIterator_next(__this) __this->lpVtbl->next(__this)
#   define IIterator_current(__this) __this->lpVtbl->current(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IIterator_INTERFACE_DEFINED__*/

#  define IIterator_ID_current IIterator_ID_next+1
#  define IITerator_ID__MAX_ IIterator_ID_current

#endif /*!IITERATOR_H_IDL_*/

#if defined(INITGUID) || !defined(IITERATOR_H_GUIDS_DEFINED_)
# define IITERATOR_H_GUIDS_DEFINED_

/* IID_IIterator = {14f0549d-3645-4396-a37c-3158290b77be} */
UUID_DEFINE(IID_IIterator, 0x14, 0xf0, 0x54, 0x9d,  0x36, 0x45, 0x43, 0x96, 0xa3, 0x7c, 0x31, 0x58, 0x29, 0x0b, 0x77, 0xbe);
#endif /*INITGUID || !IITERATOR_H_GUIDS_DEFINED_ */

