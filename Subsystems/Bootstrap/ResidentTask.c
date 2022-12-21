#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

static STATUS Bootstrap_ResidentTask_queryInterface(IExecutable *me, REFUUID iid, void **out);
static REFCOUNT Bootstrap_ResidentTask_retain(IExecutable *me);
static REFCOUNT Bootstrap_ResidentTask_release(IExecutable *me);
static STATUS Bootstrap_ResidentTask_spawn(IExecutable *me, const char **args, REFUUID iid, void **out);

static struct IExecutable_vtable_ Bootstrap_ResidentTask_IExecutable_vtable = {
	Bootstrap_ResidentTask_queryInterface,
	Bootstrap_ResidentTask_retain,
	Bootstrap_ResidentTask_release,
	Bootstrap_ResidentTask_spawn
};

void
Bootstrap_ResidentTask_init(Bootstrap_ResidentTask *self, Bootstrap *bootstrap, ThreadEntrypoint entry)
{
	self->Executable.lpVtbl = &Bootstrap_ResidentTask_IExecutable_vtable;
	self->data.bootstrap = bootstrap;
	self->data.entry = entry;
}

static STATUS
Bootstrap_ResidentTask_queryInterface(IExecutable *me, REFUUID iid, void **out)
{
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_IExecutable))
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

static REFCOUNT
Bootstrap_ResidentTask_retain(IExecutable *me)
{
	UNUSED__(me);
	
	return 2;
}

static REFCOUNT
Bootstrap_ResidentTask_release(IExecutable *me)
{
	UNUSED__(me);
	
	return 1;
}

static STATUS
Bootstrap_ResidentTask_spawn(IExecutable *me, const char **args, REFUUID iid, void **out)
{
	Bootstrap_ResidentTask *self = (Bootstrap_ResidentTask *)(void *) me;
	struct TaskCreationParameters taskInfo;

/*	IPlatformDiagnostics_log((self->data.bootstrap->data.diagnostics), LOG_DEBUG, "Bootstrap::ResidentTask::spawn()"); */
	taskInfo.flags = TF_EXECUTIVE;
	if(args[0])
	{
		taskInfo.name = args[0];
	}
	else
	{
		taskInfo.name = "(no name)";
	}
	taskInfo.addressSpace = NULL;
/*	IPlatformDiagnostics_log((self->data.bootstrap->data.diagnostics), LOG_DEBUG, taskInfo.name); */
#if 0
	taskInfo.job = self->data.job;
#endif
	taskInfo.namespace = self->data.bootstrap->data.root;
	taskInfo.mainThread_entrypoint = self->data.entry;

	return ITasker_createTask((self->data.bootstrap->data.tasker), &taskInfo, iid, out);
}
