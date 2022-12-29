/* Executive Microkernel
 * Kernel initialisation logic
 *   Obtains the Memory Manager and Boot Environment from the PAL, sets up
 *   an allocator, creates the object directory, creates the tasker, creates
 *   the bootstrap task and initial thread, transfers control to it
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

#include "p_Executive.h"

#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive)

/* Internal Executive state data */
struct Executive executive;

/* IObject */
static STATUS Executive_queryInterface(IObject *me, REFUUID iid, void **out);
static REFCOUNT Executive_retain(IObject *me);
static REFCOUNT Executive_release(IObject *me);

struct IObject_vtable_ Executive_IObject_vtable = {
	Executive_queryInterface,
	Executive_retain,
	Executive_release
};

/* IContainer */
static STATUS Executive_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_iterator(IContainer *me);

struct IContainer_vtable_ Executive_IContainer_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive, IContainer),
	Executive_resolve,
	Executive_iterator
};

/* IDirectoryEntryTarget */
static void Executive_linked(IDirectoryEntryTarget *me, IDirectoryEntry *entry);
static void Executive_unlinked(IDirectoryEntryTarget *me, IDirectoryEntry *entry);

struct IDirectoryEntryTarget_vtable_ Executive_IDirectoryEntryTarget_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive, IDirectoryEntryTarget),
	Executive_linked,
	Executive_unlinked
};

/* Callback registered with Executive::Classes */
STATUS
Executive_MetaClass_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	UNUSED__(clsid);

	return Executive_queryInterface(&(executive.Object), iid, out);
}

/* IObject */

static STATUS
Executive_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive *self = &executive;

	UNUSED__(me);

	EXEC_COMMON_SUPPORTS(Container);
	EXEC_COMMON_SUPPORTS(DirectoryEntryTarget);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}

/* IContainer */

static STATUS
Executive_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	UNUSED__(me);

	if(!executive.data.system)
	{
		Executive_init_sysContainer();
	}
	return IContainer_resolve(executive.data.system, name, entry);
}

static IIterator *
Executive_iterator(IContainer *me)
{
	UNUSED__(me);

	if(!executive.data.system)
	{
		Executive_init_sysContainer();
	}
	return IContainer_iterator(executive.data.system);
}

/* IDirectoryEntryTarget */

static void
Executive_linked(IDirectoryEntryTarget *me, IDirectoryEntry *entry)
{
	UNUSED__(me);

	if(!executive.data.system)
	{
		Executive_init_sysContainer();
	}
	me = NULL;
	if((E_SUCCESS == IMutableContainer_queryInterface(executive.data.system, &IID_IDirectoryEntryTarget, (void **) &me)))
	{
		IDirectoryEntryTarget_linked(me, entry);
		IDirectoryEntryTarget_release(me);
	}
}

static void
Executive_unlinked(IDirectoryEntryTarget *me, IDirectoryEntry *entry)
{
	UNUSED__(me);

	if(!executive.data.system)
	{
		Executive_init_sysContainer();
	}
	me = NULL;
	if((E_SUCCESS == IMutableContainer_queryInterface(executive.data.system, &IID_IDirectoryEntryTarget, (void **) &me)))
	{
		IDirectoryEntryTarget_unlinked(me, entry);
		IDirectoryEntryTarget_release(me);
	}
}


void
Executive_yield(void)
{
	ITasker_yield(executive.data.tasker);
}
