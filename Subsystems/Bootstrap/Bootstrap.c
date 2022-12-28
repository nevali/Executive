#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include "p_Bootstrap.h"

#define INTF_TO_CLASS(i) ((Bootstrap *)(void *)((i)->instptr))

static void Bootstrap_init(Bootstrap *self);
static void Bootstrap_init_container(Bootstrap *self);

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

/* IContainer */
static STATUS Bootstrap_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Bootstrap_iterator(IContainer *me);

static struct IContainer_vtable_ Bootstrap_IContainer_vtable = {
		(STATUS (*)(IContainer *, REFUUID, void **)) &Bootstrap_queryInterface,
	(REFCOUNT (*)(IContainer *)) &Bootstrap_retain,
	(REFCOUNT (*)(IContainer *)) &Bootstrap_release,
	Bootstrap_resolve,
	Bootstrap_iterator
};

/* construct a minimal static object to expose Bootstrap::queryInterface */
static Bootstrap bootstrap = {
	{ &Bootstrap_IObject_vtable, NULL },
	{ NULL, NULL },
	{ NULL, NULL },
	{
		false,
		NULL, NULL, NULL, NULL, NULL, NULL
	} };
IObject *bootstrap_IObject = &(bootstrap.Object);

static const char *banner = "\n" PRODUCT_FULLNAME " [" HOST_FAMILY "] - " PRODUCT_RELEASE "\n"
	"  " PACKAGE_NAME " version " PACKAGE_VERSION "-" EXEC_BUILD_CONFIG ", build " PRODUCT_BUILD_ID_STR ", built at " PRODUCT_BUILD_DATE " " PRODUCT_BUILD_TIME " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST "\n\n";

/* This code must be written as though it runs exclusively in user-space,
 * using only the interfaces provided to it; undefined references to the UUIDs
 * defined by the Executive are okay, other symbols are not.
 */

#define ExLog(level, str)  if(self->data.diagnostics) IPlatformDiagnostics_log((self->data.diagnostics), level, str)

/* Constructor */

static void
Bootstrap_init(Bootstrap *self)
{
	self->Object.lpVtbl = &Bootstrap_IObject_vtable;
	self->Object.instptr = &bootstrap;
	self->Subsystem.lpVtbl = &Bootstrap_ISubsystem_vtable;
	self->Subsystem.instptr = &bootstrap;
	self->Container.lpVtbl = &Bootstrap_IContainer_vtable;
	self->Container.instptr = &bootstrap;
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
	if(!bootstrap.Subsystem.lpVtbl)
	{
		Bootstrap_init(&bootstrap);
	}
	if(ExUuidEqual(iid, &IID_IObject))
	{
		if(out)
		{
			*out = &(bootstrap.Object);
		}
		return E_SUCCESS;
	}
	if(ExUuidEqual(iid, &IID_ISubsystem))
	{
		if(out)
		{
			*out = &(bootstrap.Subsystem);
		}
		return E_SUCCESS;
	}
	if(ExUuidEqual(iid, &IID_IContainer))
	{
		if(out)
		{
			*out = &(bootstrap.Container);
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
	IExecutable *exec;
	const char *args[4];
	TASKID tid;

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
	/* Create our internal container */
	if(!self->data.container)
	{
		Bootstrap_init_container(self);
	}
	ExLog(PROGRESS_LOGLEVEL, "Opening system console device...");
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
		ExLog(PROGRESS_LOGLEVEL, "Console device opened.");
		IWriteChannel_writeLn((self->data.console), banner);
	}
	else
	{
		ExLog(LOG_NOTICE, "No console device is available, startup messages will only be sent via diagnostic channels");
	}

	/* Open /System/Jobs's ICoordinator interface */
	/* Create the Bootstrap job */
	/* Release the job coordinator */
	/* Open /System/Tasks's ITasker interface */
	if(E_SUCCESS != (status = INamespace_open(root, "/System/Tasks", NULL, &IID_ITasker, (void **) &(self->data.tasker))))
	{
		/* PANIC */
		ExLog(LOG_CRIT, "Bootstrap: unable to open /System/Tasks<ITasker>");
		return status;
	}
	/* Now create the Startup task */
	/* XXX we should be able to use ExSpawn() ? */
	if(E_SUCCESS != (status = INamespace_open(root, "/System/Subsystems/Bootstrap/Startup", NULL, &IID_IExecutable, (void **) &exec)))
	{
		/* PANIC */
		ExLog(LOG_CRIT, "Bootstrap: unable to open /System/Subsystems/Bootstrap/Startup<IExecutable>");
		return status;
	}
	args[0] = "Startup";
	/* Pass any kernel arguments to it */
	args[1] = "--";
	args[2] = NULL;
	/* Provide the console as stdin, stdout, and stderr */

	tid = IExecutable_spawn(exec, args, NULL, NULL);
	IExecutable_release(exec);
	UNUSED__(tid);
	if(tid < 0)
	{
		ExLog(LOG_CRIT, "Bootstrap: unable to spawn /System/Subsystems/Bootstrap/Startup");
		return (STATUS) tid;
	}
	ExLog(PROGRESS_LOGLEVEL, "Startup task created successfully.");
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

/* IContainer */

static STATUS
Bootstrap_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	Bootstrap *self = INTF_TO_CLASS(me);

	if(self->data.container)
	{
		return IMutableContainer_resolve((self->data.container), name, entry);
	}
	return E_NOTIMPL;
}

static IIterator *
Bootstrap_iterator(IContainer *me)
{
	Bootstrap *self = INTF_TO_CLASS(me);

	if(self->data.container)
	{
		return IMutableContainer_iterator((self->data.container));
	}
	return NULL;
}

/* PRIVATE */
static void
Bootstrap_init_container(Bootstrap *self)
{
	STATUS status;

	if(E_SUCCESS != (status = INamespace_create((self->data.root), NULL, NULL, &CLSID_Executive_Container, &IID_IMutableContainer, (void **) &(self->data.container))))
	{
		/* PANIC */
		ExLog(LOG_CRIT, "Bootstrap: unable to create Executive::Container");
		return;
	}
	ExLog(PROGRESS_LOGLEVEL, "Initialising Bootstrap subsystem objects...");
	Bootstrap_ResidentTask_init(&Bootstrap_startupTask, self, Bootstrap_Startup_mainThread);
	IMutableContainer_add((self->data.container), "Startup", &CLSID_Executive_Executable, (void *) &Bootstrap_startupTask);
	ExLog(PROGRESS_LOGLEVEL, "Bootstrap subsystem objects initialised.");
}
