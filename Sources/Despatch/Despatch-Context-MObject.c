/* Executive Microkernel
 * Despatch Gateway
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Despatch.h"

/* MObject metaclass interface for Executive::Despatch::Context objects
 * (of which there is one per task, held by the Tasker)
 */
EXEC_COMMON_STATIC_IOBJECT(Executive_Despatch_Context_MObject);
static STATUS Executive_Despatch_Context_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out);

static struct MObject_vtable_ Executive_Despatch_Context_MObject_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Despatch_Context_MObject, MObject),
	Executive_Despatch_Context_MObject_create
};

/* The static Executive::Despatch::Context metaclass instance */
/*EXTERN_C*/ MObject Executive_Despatch_Context_MObject = { &Executive_Despatch_Context_MObject_vtable, NULL };

/* Executive::Despatch::Context<+IObject> */
static STATUS
Executive_Despatch_Context_MObject_queryInterface(IObject *me, REFUUID iid, void **out)
{
	if(RtUuidEqual(iid, &IID_IObject) || RtUuidEqual(iid, &IID_MObject))
	{
		if(out)
		{
			*out = me;
		}
		return E_SUCCESS;
	}
	if(out)
	{
		*out = NULL;
	}
	return E_NOENT;
}

static REFCOUNT
Executive_Despatch_Context_MObject_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_Despatch_Context_MObject_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}

/* Executive::Despatch::Context<+MObject> */

/* Create a new despatch context and return it */
static STATUS
Executive_Despatch_Context_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out)
{
	Executive_Despatch_Context *despatch;

	UNUSED__(me);
	
	ExAssert(out != NULL);
	*out = NULL;
	if(!RtUuidEqual(iid, &IID_IObject))
	{
		return E_NOTIMPL;
	}
	despatch = IAllocator_alloc(allocator, sizeof(Executive_Despatch_Context));
	if(!despatch)
	{
		return E_NOMEM;
	}
	despatch->Object.lpVtbl = &Executive_Despatch_Context_IObject_vtable;
	despatch->data.refCount = 1;
	despatch->data.allocator = allocator;
	*out = despatch;
	return E_SUCCESS;
}

