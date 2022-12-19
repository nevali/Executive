
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
static STATUS Executive_CooperativeTasker_Thread_task(IThread *me, REFUUID iid, void **out);
static STATUS Executive_CooperativeTasker_Thread_job(IThread *me, REFUUID iid, void **out);
static STATUS Executive_CooperativeTasker_Thread_namespace(IThread *me, REFUUID iid, void **out);
static void Executive_CooperativeTasker_Thread_yield(IThread *me);

/*PRIVATE*/
static void Executive_CooperativeTasker_Thread_spawn(Executive_CooperativeTasker_Thread *self);
static void Executive_CooperativeTasker_Thread__start(Executive_CooperativeTasker_Thread *self);

const struct IThread_vtable_ Executive_CooperativeTasker_Thread_vtable = {
	Executive_CooperativeTasker_Thread_queryInterface,
	Executive_CooperativeTasker_Thread_retain,
	Executive_CooperativeTasker_Thread_release,
	Executive_CooperativeTasker_Thread_id,
	Executive_CooperativeTasker_Thread_flags,
	Executive_CooperativeTasker_Thread_task,
	Executive_CooperativeTasker_Thread_job,
	Executive_CooperativeTasker_Thread_namespace,
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

static STATUS
Executive_CooperativeTasker_Thread_task(IThread *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	return ITask_queryInterface((&(self->data.task->Task)), iid, out);
}

static STATUS
Executive_CooperativeTasker_Thread_job(IThread *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	return ITask_job((&(self->data.task->Task)), iid, out);
}

static STATUS
Executive_CooperativeTasker_Thread_namespace(IThread *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	return ITask_namespace((&(self->data.task->Task)), iid, out);
}

static void
Executive_CooperativeTasker_Thread_yield(IThread *me)
{
	Executive_CooperativeTasker_Thread *self = INTF_TO_CLASS(me);

	ExAssert(self->data.task);
	ExAssert(self->data.task->data.tasker);

	Executive_CooperativeTasker_yield(&(self->data.task->data.tasker->Tasker));
}

/*INTERNAL*/

bool
Executive_CooperativeTasker_Thread_suspend(Executive_CooperativeTasker_Thread *self)
{
	ExAssert(self == self->data.tasker->data.currentThread);
	EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%u:%u)", self->data.task->data.id, self->data.id));
	if(sigsetjmp(self->data.env, 1))
	{
		EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%u:%u) resuming where we left off...", self->data.task->data.id, self->data.id));
		return true;
	}
	EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%u:%u): thread suspended", self->data.task->data.id, self->data.id));
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_SUSPENDED;
	self->data.tasker->data.previousThread = self;
	self->data.tasker->data.currentThread = NULL;
	self->data.tasker->data.currentTask = NULL;
	return false;
}

void
Executive_CooperativeTasker_Thread_resume(Executive_CooperativeTasker_Thread *self)
{
	ThreadFlags status;

	EXTRACEF(("Executive::CooperativeTasker::Thread::resume(%u:%u)", self->data.task->data.id, self->data.id));
	status = self->data.flags & THF_STATUSMASK;
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_RUNNING;
	self->data.tasker->data.currentThread = self;
	self->data.tasker->data.currentTask = self->data.task;
	if(status == THF_READY)
	{
		EXTRACEF(("- thread state was THF_READY (now THF_RUNNING)"));
		/* actually start the thread */
		Executive_CooperativeTasker_Thread_spawn(self);
		EXLOGF((LOG_ALERT, "Executive::CooperativeTasker::Thread::resume(): this should never be reached"));
	}
	else if(status == THF_SUSPENDED)
	{
		EXTRACEF(("- thread state was THF_SUSPENDED (now THF_RUNNING)"));
		siglongjmp(self->data.env, 1);
	}
	else
	{
		EXLOGF((LOG_DEBUG, "Thread::resume(): thread %u:%u state was neither THF_READY nor THF_SUSPENDED", self->data.task->data.id, self->data.id));
		return;
	}
}

static void
Executive_CooperativeTasker_Thread_spawn(Executive_CooperativeTasker_Thread *self)
{
	size_t stack;

	EXTRACEF(("Executive::CooperativeTasker::Thread::spawn(%u:%u)", self->data.task->data.id, self->data.id));
	/* save an initial context */
	if(sigsetjmp(self->data.env, 1))
	{
		/* executing within the thread's context */
		Executive_CooperativeTasker_Thread__start(self);
	}
	/* assuming stack grows down */
	stack = (size_t) (void *) self->data.stackBase + self->data.stackSize;
#if defined(__arm64__) || defined(__ARM_ARCH_7K__)
	/* r21 - r29 = 9 * 2 = 0 .. 17 */
	/* sp        = 1 * 2 = 18 .. 19 */
	self->data.env[18] = stack >> 32;
	self->data.env[19] = stack;
#else
# error don't know how to create a context on whatever CPU this is
#endif
	siglongjmp(self->data.env, 1);
}

static void
Executive_CooperativeTasker_Thread__start(Executive_CooperativeTasker_Thread *self)
{
	EXTRACEF(("Executive::CooperativeTasker::Thread::__start(%u:%u)", self->data.task->data.id, self->data.id));
	self->data.entrypoint(&(self->Thread));
	EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::Thread::__start(%u:%u) - thread terminated", self->data.task->data.id, self->data.id));
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_COMPLETED;
	Executive_CooperativeTasker_Thread_unschedule(self);
	IThread_yield((&(self->Thread)));
	EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::Thread::__start(%u:%u) - we should not have reached this point", self->data.task->data.id, self->data.id));
}

void
Executive_CooperativeTasker_Thread_unschedule(Executive_CooperativeTasker_Thread *self)
{
	Executive_CooperativeTasker *tasker = self->data.tasker;
	Executive_CooperativeTasker_Thread *thread;

	EXTRACEF(("Executive::CooperativeTasker::Thread::unschedule(%u:%u)", self->data.task->data.id, self->data.id));
	/* ensure that this thread does not appear in the tasker's runnable threads list */
	if(tasker->data.firstRunnableThread == self)
	{
		EXLOGF((LOG_DEBUG7, "removing thread from head of runnable threads list"));
		tasker->data.firstRunnableThread = self->data.nextRunnable;
	}
	else if(tasker->data.firstRunnableThread)
	{
		for(thread = tasker->data.firstRunnableThread; thread->data.nextRunnable; thread = thread->data.nextRunnable)
		{
			if(thread->data.nextRunnable == self)
			{
				EXLOGF((LOG_DEBUG7, "removing thread from middle of runnable threads list"));
				thread->data.nextRunnable = self->data.nextRunnable;
			}
		}
	}
	else
	{
		EXLOGF((LOG_DEBUG7, "Tasker has no runnable threads"));
	}
	self->data.nextRunnable = NULL;
	if(tasker->data.previousThread == self)
	{
		tasker->data.previousThread = NULL;
	}
	if(tasker->data.currentThread == self)
	{
		tasker->data.currentThread = NULL;
		tasker->data.currentTask = NULL;
	}
}

void
Executive_CooperativeTasker_Thread_schedule(Executive_CooperativeTasker_Thread *self)
{
	Executive_CooperativeTasker *tasker = self->data.tasker;

	EXTRACEF(("Executive::CooperativeTasker::Thread::schedule(%u:%u)", self->data.task->data.id, self->data.id));

	self->data.nextRunnable = tasker->data.firstRunnableThread;
	tasker->data.firstRunnableThread = self;
}
