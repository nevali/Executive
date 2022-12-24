
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
static void Executive_CooperativeTasker_Thread_destroy(Executive_CooperativeTasker_Thread *self);
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

/*INTERNAL*/
Executive_CooperativeTasker_Thread *
Executive_CooperativeTasker_Thread_create(Executive_CooperativeTasker_Task *task, ThreadEntrypoint entry)
{
	Executive_CooperativeTasker_Thread *thread, *p;

	thread = ExAlloc(sizeof(Executive_CooperativeTasker_Thread));
	if(!thread)
	{
		return NULL;
	}
	thread->data.refCount = 1;
	thread->data.vtable = &Executive_CooperativeTasker_Thread_vtable;
	thread->data.tasker = task->data.tasker;
	thread->data.task = task;
	thread->data.entrypoint = entry;
	thread->data.id = thread->data.tasker->data.nextThreadId;
	thread->data.tasker->data.nextThreadId++;
	thread->data.stackBase = ExAlloc(EXEC_THREAD_STACK_SIZE);
	thread->data.stackSize = EXEC_THREAD_STACK_SIZE;
	if(E_SUCCESS != IAddressSpace_createContext(task->data.addressSpace, &(thread->Thread), thread->data.stackBase, thread->data.stackSize, (ThreadEntrypoint) Executive_CooperativeTasker_Thread__start, &(thread->data.context)))
	{
		EXLOGF((LOG_CONDITION, "Executive::CooperativeTasker::Thread::create(): IAddressSpace::createContext() failed"));
		Executive_CooperativeTasker_Thread_destroy(thread);
		return NULL;
	}
	thread->data.flags = THF_READY;
	if(NULL == task->data.mainThread)
	{
		task->data.mainThread = thread;
	}
	else
	{
		for(p = task->data.mainThread; p->data.nextThread; p = p->data.nextThread)
		{
		}
		p->data.nextThread = thread;
	}
	Executive_CooperativeTasker_Thread_schedule(thread);
	return thread;
}

/*PRIVATE*/
static void
Executive_CooperativeTasker_Thread_destroy(Executive_CooperativeTasker_Thread *self)
{
	if(self->data.context)
	{
		IContext_release(self->data.context);
	}
	ExFree(self->data.stackBase);
	ExFree(self);
}

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
		Executive_CooperativeTasker_Thread_destroy(self);
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
	return ITask_ns((&(self->data.task->Task)), iid, out);
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
	ExAssert(self->data.context);
	EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%p => %u:%u)", self, self->data.task->data.id, self->data.id));	
#if 0
	if(false == IContext_suspend(self->data.context))
#endif
	{
		EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%p => %u:%u): suspended!", self, self->data.task->data.id, self->data.id));	
		self->data.flags &= ~THF_STATUSMASK;
		self->data.flags |= THF_SUSPENDED;
		self->data.tasker->data.previousThread = self;
		self->data.tasker->data.currentThread = NULL;
		self->data.tasker->data.currentTask = NULL;
		return false;
	}
#if 0
	EXTRACEF(("Executive::CooperativeTasker::Thread::suspend(%p => %u:%u): resumed!", self, self->data.task->data.id, self->data.id));	
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_RUNNING;
	self->data.tasker->data.currentThread = self;
	self->data.tasker->data.currentTask = self->data.task;
	return true;
#endif
}

/*INTERNAL*/

void
Executive_CooperativeTasker_Thread_resume(Executive_CooperativeTasker_Thread *me)
{
	volatile Executive_CooperativeTasker_Thread *self = me;

	EXTRACEF(("Executive::CooperativeTasker::Thread<%p>::resume(%u:%u, context = %p)", self, self->data.task->data.id, self->data.id, self->data.context));
	if(self->data.context)
	{
		self->data.flags &= ~THF_STATUSMASK;
		self->data.flags |= THF_RUNNING;
		self->data.tasker->data.currentThread = self;
		self->data.tasker->data.currentTask = self->data.task;
		if(self->data.tasker->data.previousThread)
		{
			EXTRACEF(("WILL SUSPEND old thread %p with context %p", self->data.tasker->data.previousThread, self->data.tasker->data.previousThread->data.context));
			IContext_swap(((IContext *) self->data.tasker->data.previousThread->data.context), self->data.context);
		}
		else
		{
			IContext_swap(((IContext *) self->data.context), NULL);
		}
		EXLOGF((LOG_ALERT, "Executive::CooperativeTasker::Thread<%p>::resume(): now resuming thread...", self));
		return;
	}
	EXLOGF((LOG_ALERT, "Executive::CooperativeTasker::Thread::resume(): thread had no context; unscheduling"));
	Executive_CooperativeTasker_Thread_unschedule((Executive_CooperativeTasker_Thread *) self);
}

static void
Executive_CooperativeTasker_Thread__start(Executive_CooperativeTasker_Thread *self)
{
	EXTRACEF(("Executive::CooperativeTasker::Thread::__start(%u:%u)", self->data.task->data.id, self->data.id));
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_RUNNING;
	self->data.tasker->data.currentThread = self;
	self->data.tasker->data.currentTask = self->data.task;
	self->data.entrypoint(&(self->Thread));
	EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::Thread::__start(%u:%u) - thread terminated", self->data.task->data.id, self->data.id));
	IContext_release(self->data.context);
	self->data.context = NULL;
	self->data.flags &= ~THF_STATUSMASK;
	self->data.flags |= THF_COMPLETED;
	Executive_CooperativeTasker_Thread_unschedule(self);
	for(;;)
	{
		IThread_yield((&(self->Thread)));
		EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::Thread::__start(%u:%u) - we should not have reached this point", self->data.task->data.id, self->data.id));
	}
}

void
Executive_CooperativeTasker_Thread_unschedule(Executive_CooperativeTasker_Thread *self)
{
	volatile Executive_CooperativeTasker *tasker = self->data.tasker;
	volatile Executive_CooperativeTasker_Thread *thread;

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
	volatile Executive_CooperativeTasker *tasker = self->data.tasker;

	EXTRACEF(("Executive::CooperativeTasker::Thread::schedule(%u:%u)", self->data.task->data.id, self->data.id));

	self->data.nextRunnable = tasker->data.firstRunnableThread;
	tasker->data.firstRunnableThread = self;
}
