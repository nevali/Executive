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

/* Internal Executive state data */
struct Executive executive;

STATUS
Executive_initialise(struct ExecutiveEntryParameters *params, IPlatform *platform)
{
	MDirectoryEntryTarget *meta;
	IDirectoryEntryTarget *target;

	IPlatform_phaseDidChange(platform, PHASE_STARTUP_EXECINIT);
	executive.data.PAL_metaClass = params->PAL_metaClass;
	executive.data.platform = platform;
	
	ExPhaseShift(PHASE_STARTUP_MM);
	/* Initialise a memory manager first, before we need to allocate any
	 * heap
	 */
	ExAssert(E_SUCCESS == ExMetaClass(&CLSID_PAL_MemoryManager, &IID_IMemoryManager, &(executive.data.mm)));
	ExAssert(NULL != executive.data.mm);
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
	ExPhaseShift(PHASE_STARTUP_DIAG);
	ExAssert(E_SUCCESS == Executive_metaClass(&CLSID_PAL_PlatformDiagnostics, &IID_IPlatformDiagnostics, (void *) &(executive.data.diagnostics)));

	ExNotice(PRODUCT_FULLNAME " " PACKAGE_NAME " [" HOST_FAMILY "] - " PRODUCT_RELEASE);
	ExNotice("  version " PACKAGE_VERSION ", build " PRODUCT_BUILD_ID_STR ", built at " PRODUCT_BUILD_DATE " " PRODUCT_BUILD_TIME " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST);

	/* Request the MDirectoryEntryTarget metaclass interface from Executive::Directory::Root */
	ExPhaseShift(PHASE_STARTUP_ROOT);
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
	/* Release the temporary resources */
	IDirectoryEntryTarget_release(target);
	MDirectoryEntryTarget_release(meta);
	
	EXLOGF((LOG_DEBUG, "Executive::Directory: populating the root directory"));
	/* Create the System domain */
	ExPhaseShift(PHASE_STARTUP_SYSTEM);
	ExAssert(E_SUCCESS == ExCreate("/System", &CLSID_Executive_System, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/System", DEF_SYSTEM|DEF_IMMUTABLE));

	ExAssert(E_SUCCESS == ExAdd("/System/Platform", &CLSID_PAL_Platform, (IObject *) (void *) (executive.data.platform)));
	ExAssert(E_SUCCESS == ExSetFlags("/System/Platform", DEF_SYSTEM|DEF_IMMUTABLE|DEF_HIDDEN));	
	if(executive.data.diagnostics)
	{
		ExAssert(E_SUCCESS == ExAdd("/System/Diagnostics", &CLSID_PAL_PlatformDiagnostics, (IObject *) (void *) (executive.data.diagnostics)));
		ExAssert(E_SUCCESS == ExSetFlags("/System/Diagnostics", DEF_SYSTEM|DEF_IMMUTABLE|DEF_HIDDEN));	
	}
	ExAssert(E_SUCCESS == ExCreate("/System/Volumes/Boot", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/System/Volumes/Boot", DEF_SYSTEM|DEF_MOUNTPOINT|DEF_IMMUTABLE));
	ExAssert(E_SUCCESS == ExCreate("/System/Volumes/System", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/System/Volumes/System", DEF_SYSTEM|DEF_MOUNTPOINT|DEF_IMMUTABLE));
	ExAssert(E_SUCCESS == ExCreate("/System/Volumes/Data", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/System/Volumes/Data", DEF_SYSTEM|DEF_MOUNTPOINT|DEF_IMMUTABLE));
	if(executive.data.bootEnvironment)
	{
		ExAssert(E_SUCCESS == ExAdd("/System/Boot/Environment", &CLSID_PAL_BootEnvironment, (IObject *) (void *) executive.data.bootEnvironment));
		ExAssert(E_SUCCESS == ExSetFlags("/System/Boot/Environment", DEF_SYSTEM|DEF_IMMUTABLE));
	}
	ExPhaseShift(PHASE_STARTUP_CLASSES);
	{
		IContainer *container;

		/* Executive::Classes is a singleton which provides an IContainer
		 * interface, which can be retrieved directly via ExMetaClass()
		 */
		ExAssert(E_SUCCESS == ExMetaClass(&CLSID_Executive_Classes, &IID_IContainer, &container));
		ExAssert(E_SUCCESS == ExAdd("/System/Classes", &CLSID_Executive_Classes, (void *) container));
		ExAssert(E_SUCCESS == ExSetFlags("/System/Classes", DEF_SYSTEM|DEF_IMMUTABLE|DEF_HIDDEN));
		IContainer_release(container);
	}

	ExPhaseShift(PHASE_STARTUP_USERS);
	ExAssert(E_SUCCESS == ExCreate("/Users", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/Users", DEF_IMMUTABLE));
	ExPhaseShift(PHASE_STARTUP_VOLUMES);
	ExAssert(E_SUCCESS == ExCreate("/Volumes", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/Volumes", DEF_IMMUTABLE));

	ExPhaseShift(PHASE_STARTUP_LOCAL);
	ExAssert(E_SUCCESS == ExCreate("/Local", &CLSID_Executive_Local, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/Local", DEF_IMMUTABLE));
	ExPhaseShift(PHASE_STARTUP_CLUSTER);
	ExAssert(E_SUCCESS == ExCreate("/Cluster", &CLSID_Executive_Cluster, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/Cluster", DEF_IMMUTABLE));
	ExPhaseShift(PHASE_STARTUP_NETWORK);
	ExAssert(E_SUCCESS == ExCreate("/Network", &CLSID_Executive_Network, NULL, NULL));
	ExAssert(E_SUCCESS == ExSetFlags("/Network", DEF_IMMUTABLE));

	/* Create an instance of the built-in co-operative tasker */
	ExPhaseShift(PHASE_STARTUP_TASKER);
	/* XXX this should be via a metaclass interface */
	executive.data.tasker = Executive_CooperativeTasker_create();
	ExAssert(NULL != executive.data.tasker);
	ExAssert(E_SUCCESS == ExAdd("/System/Tasks", &CLSID_Executive_Tasker, (IObject *) (void *) executive.data.tasker));
	ExSetFlags("/System/Tasks", DEF_SYSTEM);

	EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the object directory completed"));
	return E_SUCCESS;
}

STATUS
Executive_bootstrap(void)
{
	struct TaskCreationParameters taskInfo;

	/* Ask the tasker to create a task in the Executive's address space */
	ExPhaseShift(PHASE_STARTUP_EXECTASK);
	taskInfo.flags = TF_EXECUTIVE;
	taskInfo.name = "System";
	taskInfo.mainThread_entrypoint = Executive_BootstrapTask_mainThread;
	ExAssert(E_SUCCESS == ITasker_createTask(executive.data.tasker, &taskInfo, &IID_ITask, (void **) &executive.data.bootstrapTask));
	ExAssert(NULL != executive.data.bootstrapTask);

	return E_SUCCESS;
}

STATUS
Executive_run(void)
{
	ExPhaseShift(PHASE_RUNNING);
	for(;;)
	{
		ITasker_yield(executive.data.tasker);
	}
}

void
Executive_panic(const char *str)
{
	IPlatform_panic(executive.data.platform, str);
}

void
Executive_log(int level, const char *str)
{
	if(executive.data.diagnostics)
	{
		 IPlatformDiagnostics_log(executive.data.diagnostics, level, str);
	}
}

void *
Executive_alloc(size_t nbytes)
{
	return IAllocator_alloc(executive.data.allocator, nbytes);
}
void *
Executive_realloc(void *ptr, size_t nbytes)
{
	return IAllocator_realloc(executive.data.allocator, ptr, nbytes);
}

void
Executive_free(void *ptr)
{
	IAllocator_free(executive.data.allocator, ptr);
}

void
Executive_yield(void)
{
	ITasker_yield(executive.data.tasker);
}
