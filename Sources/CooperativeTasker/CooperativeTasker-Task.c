
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_CooperativeTasker.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (Executive_CooperativeTasker_Task *)((void *)(i))

/* IObject */
static STATUS Executive_CooperativeTasker_Task_queryInterface(ITask *me, REFUUID iid, void **out);
static REFCOUNT Executive_CooperativeTasker_Task_retain(ITask *me);
static REFCOUNT Executive_CooperativeTasker_Task_release(ITask *me);
/* ITask */
static TASKID Executive_CooperativeTasker_Task_id(ITask *me);
static TaskFlags Executive_CooperativeTasker_Task_flags(ITask *me);
static STATUS Executive_CooperativeTasker_Task_namespace(ITask *me, REFUUID iid, void **out);
static STATUS Executive_CooperativeTasker_Task_job(ITask *me, REFUUID iid, void **out);
static STATUS Executive_CooperativeTasker_Task_addressSpace(ITask *me, REFUUID iid, void **out);

/* INTERNAL */
int Executive_CooperativeTasker_Task_runnable(Executive_CooperativeTasker_Task *task);

const struct ITask_vtable_ Executive_CooperativeTasker_Task_vtable = {
	Executive_CooperativeTasker_Task_queryInterface,
	Executive_CooperativeTasker_Task_retain,
	Executive_CooperativeTasker_Task_release,
	Executive_CooperativeTasker_Task_id,
	Executive_CooperativeTasker_Task_flags,
	Executive_CooperativeTasker_Task_namespace,
	Executive_CooperativeTasker_Task_job,
	Executive_CooperativeTasker_Task_addressSpace
};

/** Executive::CooperativeTasker::Task **/

static STATUS
Executive_CooperativeTasker_Task_queryInterface(ITask *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Task);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_CooperativeTasker_Task_retain(ITask *me)
{
	EXEC_COMMON_RETAIN(Executive_CooperativeTasker_Task);
}

static REFCOUNT
Executive_CooperativeTasker_Task_release(ITask *me)
{
	EXEC_COMMON_RELEASE(Executive_CooperativeTasker_Task, {
		ExFree(self);
	});
}

static TASKID
Executive_CooperativeTasker_Task_id(ITask *me)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);

	return self->data.id;
}

static TaskFlags
Executive_CooperativeTasker_Task_flags(ITask *me)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);

	return self->data.flags;
}

static STATUS
Executive_CooperativeTasker_Task_namespace(ITask *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);
	if(self->data.ns)
	{
		return INamespace_queryInterface(self->data.ns, iid, out);
	}
	if(out)
	{
		*out = NULL;
	}
	return E_NOENT;
}

static STATUS
Executive_CooperativeTasker_Task_job(ITask *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);
	if(self->data.job)
	{
		return IJob_queryInterface(self->data.job, iid, out);
	}
	if(out)
	{
		*out = NULL;
	}
	return E_NOENT;
}

static STATUS
Executive_CooperativeTasker_Task_addressSpace(ITask *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Task *self = INTF_TO_CLASS(me);

	return IAddressSpace_queryInterface(self->data.addressSpace, iid, out);
}

/* INTERNAL: Executive::CooperativeTasker::Task::runnable()
 *
 * Examine a candidate task, and if it's runnable, return 1,
 * otherwise 0
 */
int
Executive_CooperativeTasker_Task_runnable(Executive_CooperativeTasker_Task *task)
{
	TaskFlags status = task->data.flags & TF_STATUSMASK;

	switch(status)
	{
		case TF_NEW:
			return 0;
		case TF_READY:
			break;
		case TF_RUNNING:
			break;
		case TF_SUSPENDED:
			return 0;
		case TF_COMPLETED:
			return 0;
		case TF_TERMINATED:
			return 0;
		default:
			ExTrace("warning: task is an unknown state!");
			return 0;
	}
	/* Task is runnable, does it have a runnable thread? */
	if(NULL == task->data.mainThread)
	{
		return 0;
	}
	/* XXX assume yes */
	return 1;
}

#undef INTF_TO_CLASS
