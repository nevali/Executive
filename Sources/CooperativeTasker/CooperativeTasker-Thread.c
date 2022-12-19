
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_CooperativeTasker.h"

/** Executive::CooperativeTasker::Thread **/

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (Executive_CooperativeTasker_Thread *)((void *)(i))

/* IObject */
static STATUS Executive_CooperativeTasker_Thread_queryInterface(IThread *me, REFUUID iid, void **out);
static REFCOUNT Executive_CooperativeTasker_Thread_retain(IThread *me);
static REFCOUNT Executive_CooperativeTasker_Thread_release(IThread *me);
/* IThread */
static THREADID Executive_CooperativeTasker_Thread_id(IThread *me);
static ThreadFlags Executive_CooperativeTasker_Thread_flags(IThread *me);
static ITask *Executive_CooperativeTasker_Thread_task(IThread *me);
static void Executive_CooperativeTasker_Thread_yield(IThread *me);

const struct IThread_vtable_ Executive_CooperativeTasker_Thread_vtable = {
	Executive_CooperativeTasker_Thread_queryInterface,
	Executive_CooperativeTasker_Thread_retain,
	Executive_CooperativeTasker_Thread_release,
	Executive_CooperativeTasker_Thread_id,
	Executive_CooperativeTasker_Thread_flags,
	Executive_CooperativeTasker_Thread_task,
	Executive_CooperativeTasker_Thread_yield
};

static STATUS
Executive_CooperativeTasker_Thread_queryInterface(IThread *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Thread);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_CooperativeTasker_Thread_retain(IThread *me)
{
	EXEC_COMMON_RETAIN(Executive_CooperativeTasker_Thread);
}

static REFCOUNT
Executive_CooperativeTasker_Thread_release(IThread *me)
{
	EXEC_COMMON_RELEASE(Executive_CooperativeTasker_Thread, {
		ExFree(self);
	});
}

static THREADID
Executive_CooperativeTasker_Thread_id(IThread *me)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	return self->data.id;
}

static ThreadFlags
Executive_CooperativeTasker_Thread_flags(IThread *me)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	return self->data.flags;
}

static ITask *
Executive_CooperativeTasker_Thread_task(IThread *me)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	ITask_retain((&(self->data.task->Task)));
	return &(self->data.task->Task);
}

static void
Executive_CooperativeTasker_Thread_yield(IThread *me)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	ExAssert(self->data.task->data.tasker);

	Executive_CooperativeTasker_yield(&(self->data.task->data.tasker->Tasker));
}
