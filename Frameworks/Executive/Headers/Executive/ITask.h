/* DO NOT EDIT: Automatically generated from ITask.idl by idl */

#ifndef ITask_FWD_DEFINED
# define ITask_FWD_DEFINED
typedef struct ITask ITask;
#endif

#ifndef ITASK_H_IDL_
# define ITASK_H_IDL_

/* Executive Microkernel
 * Task.idl
 *   Defines a Task
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
# include <Executive/IJob.h>

/* ITask version 0.0 */

# ifndef __ITask_INTERFACE_DEFINED__
#  define __ITask_INTERFACE_DEFINED__
#ifndef W_NO_UNSTABLE_INTERFACES
# warning The ITask interface is currently considered unstable; source and binary compatibility is not assured.
#endif
typedef int32_t TASKID;
typedef enum 
{
	 	TF_TYPEMASK = 7,
	 	TF_DEFAULT = 0,
	 	TF_EXECUTIVE = 1,
	 	TF_STATUSMASK = (31<<3),
	 	TF_NEW = 0,
	 	TF_READY = (1<<3),
	 	TF_RUNNING = (2<<3),
	 	TF_SUSPENDED = (3<<3),
	 	TF_COMPLETED = (4<<3),
	 	TF_TERMINATED = (5<<3)
}  TaskFlags;
#  undef INTEFACE
#  define INTERFACE ITask


DECLARE_INTERFACE_(ITask, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ITask */
	STDMETHOD_(TASKID, id)(THIS) PURE;
	STDMETHOD_(TaskFlags, flags)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define ITask_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define ITask_retain(__this) __this->lpVtbl->retain(__this)
#   define ITask_release(__this) __this->lpVtbl->release(__this)
#   define ITask_id(__this) __this->lpVtbl->id(__this)
#   define ITask_flags(__this) __this->lpVtbl->flags(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__ITask_INTERFACE_DEFINED__*/


#endif /*!ITASK_H_IDL_*/

#if defined(INITGUID) || !defined(ITASK_H_GUIDS_DEFINED_)
# define ITASK_H_GUIDS_DEFINED_

/* IID_ITask = {2b78de24-0c9e-43bc-977d-5d38f4985b86} */
UUID_DEFINE(IID_ITask, 0x2b, 0x78, 0xde, 0x24,  0x0c, 0x9e, 0x43, 0xbc, 0x97, 0x7d, 0x5d, 0x38, 0xf4, 0x98, 0x5b, 0x86);
#endif /*INITGUID || !ITASK_H_GUIDS_DEFINED_ */

