/* Executive Microkernel
 * Despatch Context
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

/* Executive::Despatch::Context<IObject> */
EXEC_COMMON_STATIC_IOBJECT(Executive_Despatch_Context);
struct IObject_vtable_ Executive_Despatch_Context_IObject_vtable = {
	Executive_Despatch_Context_queryInterface,
	Executive_Despatch_Context_retain,
	Executive_Despatch_Context_release
};

#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Despatch_Context)

/* IObject */
static STATUS
Executive_Despatch_Context_queryInterface(IObject *me, REFUUID iid, void **out)
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
Executive_Despatch_Context_retain(IObject *me)
{
	EXEC_COMMON_RETAIN(Executive_Despatch_Context);
}

static REFCOUNT
Executive_Despatch_Context_release(IObject *me)
{
	IAllocator *alloc;

	EXEC_COMMON_RELEASE(Executive_Despatch_Context, {
		alloc = self->data.allocator;
		IAllocator_free(alloc, self);
		IAllocator_release(alloc);
	});
}
