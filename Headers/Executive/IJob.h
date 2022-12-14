/* DO NOT EDIT: Automatically generated from IJob.idl by idl */

#ifndef IJob_FWD_DEFINED
# define IJob_FWD_DEFINED
typedef struct IJob IJob;
#endif

#ifndef IJOB_H_IDL_
# define IJOB_H_IDL_

/* Executive Microkernel
 * IJob.idl
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

/* IJob version 0.0 */

# ifndef __IJob_INTERFACE_DEFINED__
#  define __IJob_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The IJob interface is currently considered unstable; source and binary compatibility is not assured.
#endif
#  undef INTEFACE
#  define INTERFACE IJob


DECLARE_INTERFACE_(IJob, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IJob */

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IJob_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IJob_retain(__this) __this->lpVtbl->retain(__this)
#   define IJob_release(__this) __this->lpVtbl->release(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IJob_INTERFACE_DEFINED__*/


#endif /*!IJOB_H_IDL_*/

#if defined(INITGUID) || !defined(IJOB_H_GUIDS_DEFINED_)
# define IJOB_H_GUIDS_DEFINED_

/* IID_IJob = {516d3f53-7c65-4a8a-8067-4d075977a595} */
UUID_DEFINE(IID_IJob, 0x51, 0x6d, 0x3f, 0x53,  0x7c, 0x65, 0x4a, 0x8a, 0x80, 0x67, 0x4d, 0x07, 0x59, 0x77, 0xa5, 0x95);
#endif /*INITGUID || !IJOB_H_GUIDS_DEFINED_ */

