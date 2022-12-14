/* DO NOT EDIT: Automatically generated from ITasker.idl by idl */

#ifndef ITasker_FWD_DEFINED
# define ITasker_FWD_DEFINED
typedef struct ITasker ITasker;
#endif

#ifndef ITASKER_H_IDL_
# define ITASKER_H_IDL_

/* Executive Microkernel
 * ITasker.idl
 *   Defines the Tasker (scheduler) interface
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
# include <Executive/ITask.h>
# include <Executive/IThread.h>

/* ITasker version 0.0 */

# ifndef __ITasker_INTERFACE_DEFINED__
#  define __ITasker_INTERFACE_DEFINED__
typedef struct TaskCreationParameters
{
	const char *name;
	TaskFlags flags;
	ThreadEntrypoint mainThread_entrypoint;
}  TaskCreationParameters;
#  undef INTEFACE
#  define INTERFACE ITasker


DECLARE_INTERFACE_(ITasker, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* ITasker */
	STDMETHOD_(void, tick)(THIS) PURE;
	STDMETHOD_(void, yield)(THIS) PURE;
	STDMETHOD_(TASKID, createTask)(THIS_ const struct TaskCreationParameters *params, REFUUID iid, void **task) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define ITasker_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define ITasker_retain(__this) __this->lpVtbl->retain(__this)
#   define ITasker_release(__this) __this->lpVtbl->release(__this)
#   define ITasker_tick(__this) __this->lpVtbl->tick(__this)
#   define ITasker_yield(__this) __this->lpVtbl->yield(__this)
#   define ITasker_createTask(__this, params, iid, task) __this->lpVtbl->createTask(__this, params, iid, task)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__ITasker_INTERFACE_DEFINED__*/


#endif /*!ITASKER_H_IDL_*/

#if defined(INITGUID) || !defined(ITASKER_H_GUIDS_DEFINED_)
# define ITASKER_H_GUIDS_DEFINED_

/* IID_ITasker = {ae9562b8-ee29-4641-bd4a-b89c4ab9affc} */
UUID_DEFINE(IID_ITasker, 0xae, 0x95, 0x62, 0xb8,  0xee, 0x29, 0x46, 0x41, 0xbd, 0x4a, 0xb8, 0x9c, 0x4a, 0xb9, 0xaf, 0xfc);
#endif /*INITGUID || !ITASKER_H_GUIDS_DEFINED_ */

