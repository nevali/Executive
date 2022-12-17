/* Executive Microkernel
 * Class and metaclass handling
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

#include "p_Classes.h"

/* Generic MFactory implementation */
static STATUS Executive_MFactory_queryInterface(MFactory *me, REFUUID iid, void **out);
static REFCOUNT Executive_MFactory_retain(MFactory *me);
static REFCOUNT Executive_MFactory_release(MFactory *me);
static STATUS Executive_MFactory_lock(MFactory *me, bool dolock);

extern STATUS Executive_Allocator_MFactory_createInstance(MFactory *me, IObject *outer, REFUUID iid, void **out);

static struct MFactory_vtable_ Executive_Allocator_MFactory_vtable = {
	Executive_MFactory_queryInterface,
	Executive_MFactory_retain,
	Executive_MFactory_release,
	Executive_Allocator_MFactory_createInstance,
	Executive_MFactory_lock
};

MFactory Executive_Allocator_MFactory = { &Executive_Allocator_MFactory_vtable, NULL };

/* Generic MFactory */

static STATUS
Executive_MFactory_queryInterface(MFactory *me, REFUUID iid, void **out)
{
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_MFactory))
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
	return E_NOTIMPL;
}

static REFCOUNT Executive_MFactory_retain(MFactory *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT Executive_MFactory_release(MFactory *me)
{
	UNUSED__(me);
	
	return 1;
}

static STATUS Executive_MFactory_lock(MFactory *me, bool dolock)
{
	UNUSED__(me);
	UNUSED__(dolock);

	return E_SUCCESS;
}
