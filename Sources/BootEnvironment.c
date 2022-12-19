/* Executive Microkernel
 * Sources/Executive/bootenv.c
 *   Implements a basic boot environment class if the PAL doesn't provide one
 */

/* Copyright (c) 2022 Mo McRoberts.
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

#include "p_Executive.h"

union Executive_BootEnvironment
{
	IBootEnvironment BootEnvironment;
	IObject Object;
	struct
	{
		void *vtable;
		REFCOUNT refCount;
	} data;
};

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (union Executive_BootEnvironment *)((i))

static STATUS Executive_BootEnvironment_queryInterface(IBootEnvironment *me, REFUUID iid, void **out);
static REFCOUNT Executive_BootEnvironment_retain(IBootEnvironment *me);
static REFCOUNT Executive_BootEnvironment_release(IBootEnvironment *me);

static struct IBootEnvironment_vtable_ Executive_BootEnvironment_vtable = {
	Executive_BootEnvironment_queryInterface,
	Executive_BootEnvironment_retain,
	Executive_BootEnvironment_release
};

/* The PAL didn't provide a Boot Environment object, so synthesise a workable
 * fallback version
 */
 /* XXX should be via MObject */
IBootEnvironment *
Executive_BootEnvironment_create(void)
{
	Executive_BootEnvironment *env;
	
	env = ExAlloc(sizeof(Executive_BootEnvironment));
	if(!env)
	{
		return NULL;
	}
	env->BootEnvironment.lpVtbl = &Executive_BootEnvironment_vtable;
	env->data.refCount = 1;
	return &(env->BootEnvironment);
}

static STATUS Executive_BootEnvironment_queryInterface(IBootEnvironment *me, REFUUID iid, void **out)
{
	Executive_BootEnvironment *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(BootEnvironment);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_BootEnvironment_retain(IBootEnvironment *me)
{
	EXEC_COMMON_RETAIN(Executive_BootEnvironment);
}

static REFCOUNT Executive_BootEnvironment_release(IBootEnvironment *me)
{
	EXEC_COMMON_RELEASE(Executive_BootEnvironment, {});
}
