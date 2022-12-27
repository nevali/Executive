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
# include "BuildInformation.h"
# include "ProductInformation.h"
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
	
	IPlatform_phaseTransition(platform, PHASE_STARTUP_EXECINIT);
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
#if FEATURE_BOOTPROGRESS
	ExLog(LOG_INFO, PACKAGE_NAME " subsystems initialised");
#endif
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
	/* This should be a call to IPlatform for the initial address space */
	ExAssert(E_SUCCESS == ExMetaClass(&CLSID_PAL_MemoryManager, &IID_IAddressSpace, &(executive.data.addressSpace)));
	ExAssert(NULL != executive.data.addressSpace);
}

/*PRIVATE*/
static void
Executive_init_allocator(void)
{
	/* Create an instance of the Executive's built-in allocator, which will
	 * obtain transient regions from the kernel address sspace
	 */

	ExPhaseShift(PHASE_STARTUP_ALLOCATOR);
	executive.data.allocator = RtAllocator_create(executive.data.addressSpace);
	if(!executive.data.allocator)
	{
		ExPanic("failed to create an allocator using the PAL's memory manager!\n");
	}
	/* Inform the Platform of the new allocator's availability */
	IPlatform_allocatorActivated(executive.data.platform, executive.data.allocator);
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
	if(E_SUCCESS != Executive_metaClass(&CLSID_PAL_PlatformDiagnostics, &IID_IPlatformDiagnostics, (void *) &(executive.data.diagnostics)))
	{
		executive.data.diagnostics = NULL;
		return;
	}

	ExLog(LOG_INFO, PRODUCT_NAME " (" PRODUCT_RELEASE " for " HOST_FAMILY ") is starting");
	ExLog(LOG_INFO, "Diagnostic channel activated");
#if FEATURE_BOOTPROGRESS
	ExLog(LOG_INFO, "");
	ExLog(LOG_INFO, "System initialisation is in progress...");
#endif
#if FEATURE_SELF_TESTS && !NDEBUG
	ExLog(LOG_NOTICE, "A test of the diagnostic logging system is commencing.");
	ExLog(LOG_INFO, "");
	ExLog(LOG_EMERGENCY, "This is a test message at the EMERGENCY level");
	ExLog(LOG_ALERT, "This is a test message at the ALERT level");
	ExLog(LOG_CRITICAL, "This is a test message at the CRITICAL level");
	ExLog(LOG_ERROR, "This is a test message at the ERROR level");
	ExLog(LOG_WARNING, "This is a test message at the WARNING level");
	ExLog(LOG_NOTICE, "This is a test message at the NOTICE level");
	ExLog(LOG_INFO, "This is a test message at the INFO level");
	ExLog(LOG_CONDITION, "This is a test message at the CONDITION level");
	ExLog(LOG_DEBUG, "This is a test message at the DEBUG-1 level");
	ExLog(LOG_DEBUG2, "This is a test message at the DEBUG-2 level");
	ExLog(LOG_DEBUG3, "This is a test message at the DEBUG-3 level");
	ExLog(LOG_DEBUG4, "This is a test message at the DEBUG-4 level");
	ExLog(LOG_DEBUG5, "This is a test message at the DEBUG-5 level");
	ExLog(LOG_DEBUG6, "This is a test message at the DEBUG-6 level");
	ExLog(LOG_DEBUG7, "This is a test message at the DEBUG-7 level");
	ExLog(LOG_TRACE, "This is a test message at the TRACE level");
	ExLog(LOG_INFO, "");
	ExLog(LOG_NOTICE, "Diagnostic logging self-test concluded. Normal logging resuming.");
#endif /*FEATURE_SELF_TESTS && !NDEBUG*/
}

/*PRIVATE*/
static void
Executive_init_directory(void)
{
	MDirectoryEntryTarget *meta;
	IDirectoryEntryTarget *target;

	/* Request the MDirectoryEntryTarget metaclass interface from Executive::Directory::Root */
	ExPhaseShift(PHASE_STARTUP_ROOT);	
	EXTRACEF(("Executive::init_directory(): populating the root directory"));
#if FEATURE_BOOTPROGRESS
	ExLog(LOG_INFO, "Populating initial object directory...");
#endif
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
	/* Inform the Platform object that there's a namespace */
	IPlatform_namespaceActivated(executive.data.platform, executive.data.rootNS);

	if(!executive.data.system)
	{
		/* if nothing triggered the creation of the internal /System container,
		 * do so now */
		Executive_init_sysContainer();
	}
#if FEATURE_DEBUG_NAMESPACE
	EXLOGF((LOG_DEBUG, "Executive::init_directory(): initial population of the object directory completed"));
#endif
}

/*PRIVATE*/
static void
Executive_init_tasker(void)
{
	/* Create an instance of the built-in co-operative tasker */
	ExPhaseShift(PHASE_STARTUP_TASKER);
#if FEATURE_BOOTPROGRESS
	ExLog(LOG_INFO, "Starting the Tasker...");
#endif
	/* XXX this should be via a metaclass interface */
	executive.data.tasker = Executive_CooperativeTasker_create();
	if(NULL == executive.data.tasker)
	{
		EXLOGF((LOG_NOTICE, "no Tasker is available, starting in single-tasking mode"));
		return;
	}
	ExAssert(NULL != executive.data.tasker);
	ExAssert(E_SUCCESS == IMutableContainer_add(executive.data.system, "Tasks", &CLSID_Executive_Tasker,  (void *) executive.data.tasker));
	ExSetFlags("/System/Tasks", DEF_SYSTEM);
}
