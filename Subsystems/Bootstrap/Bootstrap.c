#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

#define INTF_TO_CLASS(i) ((Bootstrap *)(void *)((i)->instptr))

/* IObject */
STATUS Bootstrap_queryInterface(IObject *me, REFUUID iid, void **out);
static REFCOUNT Bootstrap_retain(IObject *me);
static REFCOUNT Bootstrap_release(IObject *me);

static struct IObject_vtable_ Bootstrap_IObject_vtable = {
	Bootstrap_queryInterface,
	Bootstrap_retain,
	Bootstrap_release
};

/* ISubsystem */
static STATUS Bootstrap_start(ISubsystem *me, INamespace *root);
static STATUS Bootstrap_stop(ISubsystem *me, INamespace *root);

static struct ISubsystem_vtable_ Bootstrap_ISubsystem_vtable = {
	(STATUS (*)(ISubsystem *, REFUUID, void **)) &Bootstrap_queryInterface,
	(REFCOUNT (*)(ISubsystem *)) &Bootstrap_retain,
	(REFCOUNT (*)(ISubsystem *)) &Bootstrap_release,
	Bootstrap_start,
	Bootstrap_stop
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

static const char *banner = PRODUCT_FULLNAME " [" HOST_FAMILY "] - " PRODUCT_RELEASE "\n"
	"  " PACKAGE_NAME " version " PACKAGE_VERSION ", build " PRODUCT_BUILD_ID_STR ", built at " PRODUCT_BUILD_DATE " " PRODUCT_BUILD_TIME " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST "\n\n";

/* This code must be written as though it runs exclusively in user-space,
 * using only the interfaces provided to it; undefined references to the UUIDs
 * defined by the Executive are okay, other symbols are not.
 */

#define ExUuidEqual(a, b) ((a)->d.d1 == (b)->d.d1 && (a)->d.d2 == (b)->d.d2 && (a)->d.d3 == (b)->d.d3 && (a)->d.d4 == (b)->d.d4)

static size_t
ExStrLen(const char *str)
{
	size_t c;

	for(c = 0; str[c]; c++)
	{
	}
	return c;
}

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
	if(ExUuidEqual(iid, &IID_ISubsystem))
	{
		bootstrap.Subsystem.lpVtbl = &Bootstrap_ISubsystem_vtable;
		bootstrap.Subsystem.instptr = &bootstrap;
		if(out)
		{
			*out = &(bootstrap.Subsystem);
		}
		return E_SUCCESS;
	}
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
		/* If no console, can we open a write channel on the diagnostics interface and use that? */
		if(E_SUCCESS != INamespace_open(root, "/System/Devices/Diagnostics", NULL, &IID_IWriteChannel, (void **) &(self->data.console)))
		{
			/* No console at all */
			self->data.console = NULL;
		}
	}
	if(self->data.console)
	{
		IWriteChannel_write((self->data.console), (const uint8_t *) banner, ExStrLen(banner));
	}
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

STATUS
Bootstrap_stop(ISubsystem *me, INamespace *root)
{
	UNUSED__(me);
	UNUSED__(root);
	
	/* The Bootstrap subsystem cannot be stopped */
	return E_PERM;
}
