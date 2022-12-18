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

static void Executive_init_memoryManager(void);
static void Executive_init_allocator(void);
static void Executive_init_bootEnvironment(void);
static void Executive_init_diagnostics(void);
static void Executive_init_directory(void);
static void Executive_init_tasker(void);

/* Constructor */

STATUS
Executive_init(Executive *self, struct ExecutiveEntryParameters *params, IPlatform *platform)
{
	UNUSED__(self);
	
	IPlatform_phaseDidChange(platform, PHASE_STARTUP_EXECINIT);
	executive.Object.lpVtbl = &Executive_IObject_vtable;
	executive.Object.instptr = &executive;
	executive.Container.lpVtbl = &Executive_IContainer_vtable;
	executive.Container.instptr = &executive;
	executive.DirectoryEntryTarget.lpVtbl = &Executive_IDirectoryEntryTarget_vtable;
	executive.DirectoryEntryTarget.instptr = &executive;
	executive.data.PAL_metaClass = params->PAL_metaClass;
	executive.data.platform = platform;
	
	Executive_init_memoryManager();
	Executive_init_allocator();
	Executive_init_bootEnvironment();
	Executive_init_diagnostics();
	Executive_init_directory();
	Executive_init_tasker();
	return E_SUCCESS;
}

/*PRIVATE*/
void
Executive_init_sysContainer(void)
{
	MObject *meta;
	
	/* Ask Executive::Directory for this metaclass directly */
	ExAssert(E_SUCCESS == Executive_Directory_metaClass(&CLSID_Executive_System, &IID_MObject, (void **) &meta));
	ExAssert(E_SUCCESS == MObject_create(meta, executive.data.allocator, &IID_IMutableContainer, (void **) &(executive.data.system)));
	MObject_release(meta);

}

/*PRIVATE*/
static void
Executive_init_memoryManager(void)
{
	ExPhaseShift(PHASE_STARTUP_MM);
	/* Initialise a memory manager first, before we need to allocate any
	 * heap
	 */
	ExAssert(E_SUCCESS == ExMetaClass(&CLSID_PAL_MemoryManager, &IID_IMemoryManager, &(executive.data.mm)));
	ExAssert(NULL != executive.data.mm);
}

/*PRIVATE*/
static void
Executive_init_allocator(void)
{
	/* Create an instance of the Executive's built-in allocator, which will
	 * obtain transient regions from the PAL's memory manager
	 */

	ExPhaseShift(PHASE_STARTUP_ALLOCATOR);
	executive.data.allocator = Executive_Allocator_create(executive.data.mm);
	if(!executive.data.allocator)
	{
		ExPanic("failed to create an allocator using the PAL's memory manager!\n");
	}
	/* Inform the Platform of the new allocator's availability */
	IPlatform_setDefaultAllocator(executive.data.platform, executive.data.allocator);
}

/*PRIVATE*/
static void
Executive_init_bootEnvironment(void)
{
	/* Obtain the PAL's boot environment, if it has one */
	ExPhaseShift(PHASE_STARTUP_BOOTENV);
	if(E_SUCCESS != Executive_metaClass(&CLSID_PAL_BootEnvironment, &IID_IBootEnvironment, (void *) &(executive.data.bootEnvironment)))
	{
		/* XXX this should happen via Executive_metaClass() */
		executive.data.bootEnvironment = Executive_BootEnvironment_create();
	}
	ExAssert(NULL != executive.data.bootEnvironment);
	/* Optionally obtain a diagnostics instance; this can fail without
	 * incident (in this event the ExNotice() calls that follow become
	 * no-ops)
	 */
}

/*PRIVATE*/
static void
Executive_init_diagnostics(void)
{
	ExPhaseShift(PHASE_STARTUP_DIAG);
	ExAssert(E_SUCCESS == Executive_metaClass(&CLSID_PAL_PlatformDiagnostics, &IID_IPlatformDiagnostics, (void *) &(executive.data.diagnostics)));

	ExNotice(PRODUCT_FULLNAME " " PACKAGE_NAME " [" HOST_FAMILY "] - " PRODUCT_RELEASE);
	ExNotice("  version " PACKAGE_VERSION ", build " PRODUCT_BUILD_ID_STR ", built at " PRODUCT_BUILD_DATE " " PRODUCT_BUILD_TIME " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST);

}

/*PRIVATE*/
static void
Executive_init_directory(void)
{
	MDirectoryEntryTarget *meta;
	IDirectoryEntryTarget *target;

	/* Request the MDirectoryEntryTarget metaclass interface from Executive::Directory::Root */
	ExPhaseShift(PHASE_STARTUP_ROOT);
	EXLOGF((LOG_DEBUG, "Executive::init_directory(): populating the root directory"));
	ExAssert(E_SUCCESS == Executive_metaClass(&CLSID_Executive_Root, &IID_MDirectoryEntryTarget, (void **) &meta));
	/* invoke the constructor on the metaclass interface, MDirectoryEntryTarget::createInstance()
	 * to create the root instance itself
	 * note that passing a NULL IDirectoryEntry is only valid when creating the
	 * root
	 */
	ExAssert(E_SUCCESS == MDirectoryEntryTarget_createInstance(meta, NULL, &target));
	/* Obtain the IMutableContainer interface */
	ExAssert(E_SUCCESS == IDirectoryEntryTarget_queryInterface(target, &IID_IMutableContainer, (void **) &(executive.data.rootDirectory)));
	/* Obtain the INamespace interface */
	ExAssert(E_SUCCESS == IMutableContainer_queryInterface(executive.data.rootDirectory, &IID_INamespace, (void **) &(executive.data.rootNS)));
	/* Confirm everything is intact*/
	ExAssert(NULL != executive.data.rootDirectory);
	ExAssert(NULL != executive.data.rootNS);
	/* Inform the root directory that it's been "linked" (albeit to nowhere) */
	IDirectoryEntryTarget_linked(target, NULL);
	/* Release the temporary resources */
	IDirectoryEntryTarget_release(target);
	MDirectoryEntryTarget_release(meta);

	if(!executive.data.system)
	{
		/* if nothing triggered the creation of the internal /System container,
		 * do so now */
		Executive_init_sysContainer();
	}
	EXLOGF((LOG_DEBUG, "Executive::init_directory(): initial population of the object directory completed"));
#ifdef EXEC_BUILD_DEBUG
	EXLOGF((LOG_NOTICE, "Executive::init_directory(): dump of object directory follows:-"));
	Executive_Directory_dump((IContainer *) (void *) executive.data.rootNS);
#endif
}

/*PRIVATE*/
static void
Executive_init_tasker(void)
{
	/* Create an instance of the built-in co-operative tasker */
	ExPhaseShift(PHASE_STARTUP_TASKER);
	/* XXX this should be via a metaclass interface */
	executive.data.tasker = Executive_CooperativeTasker_create();
	ExAssert(NULL != executive.data.tasker);
	ExAssert(E_SUCCESS == IMutableContainer_add(executive.data.system, "Tasks", &CLSID_Executive_Tasker,  (void *) executive.data.tasker));
	ExSetFlags("/System/Tasks", DEF_SYSTEM);
}
