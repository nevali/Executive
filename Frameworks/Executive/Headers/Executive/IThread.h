/* DO NOT EDIT: Automatically generated from IThread.idl by idl */

#ifndef IThread_FWD_DEFINED
# define IThread_FWD_DEFINED
typedef struct IThread IThread;
#endif

#ifndef ITHREAD_H_IDL_
# define ITHREAD_H_IDL_

/* Executive Microkernel
 * IThread.idl
 *   Defines a Thread
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

/* IThread version 0.0 */

# ifndef __IThread_INTERFACE_DEFINED__
#  define __IThread_INTERFACE_DEFINED__
typedef int32_t THREADID;
typedef void (*ThreadEntrypoint)(IThread *self);
typedef enum 
{
	 	THF_TYPEMASK = 7,
	 	THF_DEFAULT = 0,
	 	THF_EXECUTIVE = 1,
	 	THF_STATUSMASK = (31<<3),
	 	THF_NEW = 0,
	 	THF_READY = (1<<3),
	 	THF_RUNNING = (2<<3),
	 	THF_TRAP = (3<<3),
	 	THF_SUSPENDED = (4<<3),
	 	THF_WAITING = (5<<3),
	 	THF_COMPLETED = (6<<3),
	 	THF_TERMINATED = (7<<3)
}  ThreadFlags;
#  undef INTEFACE
#  define INTERFACE IThread


DECLARE_INTERFACE_(IThread, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IThread */
	STDMETHOD_(THREADID, id)(THIS) PURE;
	STDMETHOD_(ThreadFlags, flags)(THIS) PURE;
	STDMETHOD_(STATUS, task)(THIS_ REFUUID iid, void **out) PURE;
	STDMETHOD_(STATUS, job)(THIS_ REFUUID iid, void **out) PURE;
	STDMETHOD_(STATUS, namespace)(THIS_ REFUUID iid, void **out) PURE;
	STDMETHOD_(void, yield)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IThread_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IThread_retain(__this) __this->lpVtbl->retain(__this)
#   define IThread_release(__this) __this->lpVtbl->release(__this)
#   define IThread_id(__this) __this->lpVtbl->id(__this)
#   define IThread_flags(__this) __this->lpVtbl->flags(__this)
#   define IThread_task(__this, iid, out) __this->lpVtbl->task(__this, iid, out)
#   define IThread_job(__this, iid, out) __this->lpVtbl->job(__this, iid, out)
#   define IThread_namespace(__this, iid, out) __this->lpVtbl->namespace(__this, iid, out)
#   define IThread_yield(__this) __this->lpVtbl->yield(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IThread_INTERFACE_DEFINED__*/


#endif /*!ITHREAD_H_IDL_*/

#if defined(INITGUID) || !defined(ITHREAD_H_GUIDS_DEFINED_)
# define ITHREAD_H_GUIDS_DEFINED_

/* IID_IThread = {fa016ec8-40e1-4e48-92dd-0698687bc83c} */
UUID_DEFINE(IID_IThread, 0xfa, 0x01, 0x6e, 0xc8,  0x40, 0xe1, 0x4e, 0x48, 0x92, 0xdd, 0x06, 0x98, 0x68, 0x7b, 0xc8, 0x3c);
#endif /*INITGUID || !ITHREAD_H_GUIDS_DEFINED_ */

