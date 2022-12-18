#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

#define INTF_TO_CLASS(i) ((Bootstrap *)(void *)((i)->instptr))

STATUS Bootstrap_queryInterface(IObject *me, REFUUID iid, void **out);
static REFCOUNT Bootstrap_retain(IObject *me);
static REFCOUNT Bootstrap_release(IObject *me);

static struct IObject_vtable_ Bootstrap_IObject_vtable = {
	Bootstrap_queryInterface,
	Bootstrap_retain,
	Bootstrap_release
};

/* construct a minimal static object to expose Bootstrap::queryInterface */
static Bootstrap bootstrap = {
	{ &Bootstrap_IObject_vtable, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{
		false,
		NULL, NULL, NULL, NULL
	} };
IObject *bootstrap_IObject = &(bootstrap.Object);

/* This code must be written as though it runs exclusively in user-space,
 * using only the interfaces provided to it; undefined references to the UUIDs
 * defined by the Executive are okay, other symbols are not.
 */

#define ExUuidEqual(a, b) ((a)->d.d1 == (b)->d.d1 && (a)->d.d2 == (b)->d.d2 && (a)->d.d3 == (b)->d.d3 && (a)->d.d4 == (b)->d.d4)

/* IObject */

STATUS
Bootstrap_queryInterface(IObject *me, REFUUID iid, void **out)
{
	UNUSED__(me);

	if(out)
	{
		*out = NULL;
	}
	if(ExUuidEqual(iid, &IID_IObject))
	{
		bootstrap.Object.lpVtbl = &Bootstrap_IObject_vtable;
		bootstrap.Object.instptr = &bootstrap;
		if(out)
		{
			*out = &(bootstrap.Object);
		}
		return E_SUCCESS;
	}
#if 0
	if(ExUuidEqual(iid, &IID_ISubsystem))
	{
		if(out)
		{
			*out = &(bootstrap.Subsystem);
		}
		return E_SUCCESS;
	}
#endif
	return E_NOTIMPL;
}

static REFCOUNT
Bootstrap_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}
static REFCOUNT
Bootstrap_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}

/* ISubsystem */

STATUS
Bootstrap_start(ISubsystem *me, INamespace *root)
{
	Bootstrap *self = INTF_TO_CLASS(me);
	STATUS status;
	struct TaskCreationParameters taskInfo;
	ITasker *tasker;

	/* Are we already running? */
	if(self->data.running)
	{
		return E_SUCCESS;
	}
	self->data.running = true;
	/* Retain the namespace */
	INamespace_retain(root);
	self->data.root = root;
	/* Obtain the platform diagnostics interface if possible */
	if(E_SUCCESS != INamespace_open(root, "/System/Devices/Diagnostics", NULL, &IID_IPlatformDiagnostics, (void **) &(self->data.diagnostics)))
	{
		self->data.diagnostics = NULL;
	}
	/* Open the console if possible */
	if(E_SUCCESS != INamespace_open(root, "/System/Devices/Console", NULL, &IID_IWriteChannel, (void **) &(self->data.console)))
	{
		self->data.console = NULL;
	}
	/* If no console, can we open a write channel on the diagnostics interface and use that? */
	/* Open /System/Jobs's ICoordinator interface */
	/* Create the Bootstrap job */
	/* Release the job coordinator */
	/* Open /System/Tasks's ITasker interface */
	if(E_SUCCESS != (status = INamespace_open(root, "/System/Tasks", NULL, &IID_ITasker, (void **) &tasker)))
	{
		/* PANIC */
		return status;
	}
	/* Create the Sentinel task */
	/* Ask the tasker to create a task in the Executive's address space */
	taskInfo.flags = TF_EXECUTIVE;
	taskInfo.name = "Sentinel";
#if 0
	taskInfo.job = self->data.job;
#endif
	taskInfo.namespace = root;
	taskInfo.mainThread_entrypoint = Bootstrap_Sentinel_mainThread;

	if(E_SUCCESS != (status = ITasker_createTask(tasker, &taskInfo, &IID_ITask, (void **) &self->data.sentinel)))
	{
		ITasker_release(tasker);
		return status;
	}
	/* Release the Tasker*/
	ITasker_release(tasker);
	return E_SUCCESS;
}
