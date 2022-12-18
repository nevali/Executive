/* Executive Microkernel
 * Co-operative Tasker
 *   Implements basic co-operative multitasking, delegating actual context
 *   switching to architecture-specific (but not platform-specific) code
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

/* XXX placeholder */
#include <setjmp.h>

struct Executive_CooperativeTasker
{
	ITasker Tasker;
	IObject Object;
	IContainer Container;
	struct
	{
		REFCOUNT refCount;
		Executive_CooperativeTasker_Task *firstTask;
		Executive_CooperativeTasker_Task *lastTask;
		TASKID nextTaskId;
		long nextThreadId;
		/* XXX per-CPU */
		Executive_CooperativeTasker_Task *currentTask;
		Executive_CooperativeTasker_Thread *currentThread;
	} data;
};

union Executive_CooperativeTasker_Task
{
	ITask Task;
	IObject Object;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		/* Task ID */
		TASKID id;
		/* Task flags */
		TaskFlags flags;
		/* pointer to the Tasker that owns us */
		Executive_CooperativeTasker *tasker;
		/* pointer to the next task in the list */
		Executive_CooperativeTasker_Task *nextTask;
		/* IJob *job */
		/* IAddressSpace *addressSpace; */
		/* IRegionSet *regions; */
		Executive_CooperativeTasker_Thread *mainThread;
	} data;
};

union Executive_CooperativeTasker_Thread
{
	IObject Object;
	IThread Thread;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		/* Thread ID */
		THREADID id;
		ThreadFlags flags;
		/* which task are we part of */
		Executive_CooperativeTasker_Task *task;
		/* pointer to the next thread in the list */
		Executive_CooperativeTasker_Thread *nextThread;
		/* pointer to the thread's stack */
		uint8_t *stackBase;
		size_t stackSize;
		ThreadEntrypoint entrypoint;
		sigjmp_buf env; 
		/* IEvent *eventQueue; */
	} data;
};

/* IObject */
static STATUS Executive_CooperativeTasker_queryInterface(ITasker *me, REFUUID iid, void **out);
static REFCOUNT Executive_CooperativeTasker_retain(ITasker *me);
static REFCOUNT Executive_CooperativeTasker_release(ITasker *me);
/* ITasker */
static void Executive_CooperativeTasker_tick(ITasker *me);
static void Executive_CooperativeTasker_yield(ITasker *me);
static STATUS Executive_CooperativeTasker_createTask(ITasker *me, const struct TaskCreationParameters *params, REFUUID iid, void **out);
/* IContainer */
static STATUS Executive_CooperativeTasker_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_CooperativeTasker_iterator(IContainer *me);

static const struct IObject_vtable_ Executive_CooperativeTasker_IObject_vtable = {
	/* there is no pleasant way to do this */
	(STATUS (*)(IObject *, REFUUID, void **))(void *) &Executive_CooperativeTasker_queryInterface,
	(REFCOUNT (*)(IObject *))(void *) &Executive_CooperativeTasker_retain,
	(REFCOUNT (*)(IObject *))(void *) &Executive_CooperativeTasker_release
};

static const struct ITasker_vtable_ Executive_CooperativeTasker_ITasker_vtable = {
	Executive_CooperativeTasker_queryInterface,
	Executive_CooperativeTasker_retain,
	Executive_CooperativeTasker_release,
	Executive_CooperativeTasker_tick,
	Executive_CooperativeTasker_yield,
	Executive_CooperativeTasker_createTask
};

static const struct IContainer_vtable_ Executive_CooperativeTasker_IContainer_vtable = {
	/* there is no pleasant way to do this */
	(STATUS (*)(IContainer *, REFUUID, void **))(void *) &Executive_CooperativeTasker_queryInterface,
	(REFCOUNT (*)(IContainer *))(void *) &Executive_CooperativeTasker_retain,
	(REFCOUNT (*)(IContainer *))(void *) &Executive_CooperativeTasker_release,
	Executive_CooperativeTasker_resolve,
	Executive_CooperativeTasker_iterator
};

/* IObject */
static STATUS Executive_CooperativeTasker_Task_queryInterface(ITask *me, REFUUID iid, void **out);
static REFCOUNT Executive_CooperativeTasker_Task_retain(ITask *me);
static REFCOUNT Executive_CooperativeTasker_Task_release(ITask *me);
/* ITask */
static TASKID Executive_CooperativeTasker_Task_id(ITask *me);
static TaskFlags Executive_CooperativeTasker_Task_flags(ITask *me);
/* INTERNAL */
static int Executive_CooperativeTasker_Task_runnable(Executive_CooperativeTasker_Task *task);

static const struct ITask_vtable_ Executive_CooperativeTasker_Task_vtable = {
	Executive_CooperativeTasker_Task_queryInterface,
	Executive_CooperativeTasker_Task_retain,
	Executive_CooperativeTasker_Task_release,
	Executive_CooperativeTasker_Task_id,
	Executive_CooperativeTasker_Task_flags
};


/* IObject */
static STATUS Executive_CooperativeTasker_Thread_queryInterface(IThread *me, REFUUID iid, void **out);
static REFCOUNT Executive_CooperativeTasker_Thread_retain(IThread *me);
static REFCOUNT Executive_CooperativeTasker_Thread_release(IThread *me);
/* IThread */
static THREADID Executive_CooperativeTasker_Thread_id(IThread *me);
static ThreadFlags Executive_CooperativeTasker_Thread_flags(IThread *me);
static ITask *Executive_CooperativeTasker_Thread_task(IThread *me);
static void Executive_CooperativeTasker_Thread_yield(IThread *me);

static const struct IThread_vtable_ Executive_CooperativeTasker_Thread_vtable = {
	Executive_CooperativeTasker_Thread_queryInterface,
	Executive_CooperativeTasker_Thread_retain,
	Executive_CooperativeTasker_Thread_release,
	Executive_CooperativeTasker_Thread_id,
	Executive_CooperativeTasker_Thread_flags,
	Executive_CooperativeTasker_Thread_task,
	Executive_CooperativeTasker_Thread_yield
};


/** Executive::CooperativeTasker **/

#define INTF_TO_CLASS(i)               (Executive_CooperativeTasker *)((void *)(i->instptr))

ITasker *
Executive_CooperativeTasker_create(void)
{
	Executive_CooperativeTasker *tasker;

	tasker = ExAlloc(sizeof(Executive_CooperativeTasker));
	if(!tasker)
	{
		return NULL;
	}
	tasker->data.refCount = 1;
	tasker->data.nextThreadId = 1;
	tasker->Object.instptr = tasker;
	tasker->Object.lpVtbl = &Executive_CooperativeTasker_IObject_vtable;
	tasker->Tasker.instptr = tasker;
	tasker->Tasker.lpVtbl = &Executive_CooperativeTasker_ITasker_vtable;
	tasker->Container.instptr = tasker;
	tasker->Container.lpVtbl = &Executive_CooperativeTasker_IContainer_vtable;
	return &(tasker->Tasker);
}


static STATUS
Executive_CooperativeTasker_queryInterface(ITasker *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Tasker);
	EXEC_COMMON_SUPPORTS(Container);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_CooperativeTasker_retain(ITasker *me)
{
	EXEC_COMMON_RETAIN(Executive_CooperativeTasker);
}

static REFCOUNT
Executive_CooperativeTasker_release(ITasker *me)
{
	EXEC_COMMON_RELEASE(Executive_CooperativeTasker, {
		ExPanic("attempt to destroy Tasker (if handover were possible, this line of code would not exist)");
		ExFree(self);
	});
}

/* Executive::CooperativeTasker::<IContainer>resolve() */
static STATUS
Executive_CooperativeTasker_resolve(IContainer *me, const char *name, IDirectoryEntry **out)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	UNUSED__(self);

	UNUSED__(name);
	UNUSED__(out);

	return E_NOTIMPL;
}

static IIterator *
Executive_CooperativeTasker_iterator(IContainer *me)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	UNUSED__(self);

	return NULL;
}



/* Executive::CooperativeTasker::<ITasker>yield()
 *
 * Yield to the Tasker
 *
 * This method is invoked to switch control to the next task in turn; if
 * there aren't any (on the current processor), ask the PAL to perform a
 * power-friendly sleep via PAL::nap()
 *
 * This method may be invoked by the Executive where currentTask == NULL
 * to pass control to the Tasker and allow scheduling to begin; the task
 * of the next runnable thread will become the current task
 *
 */

static void trampoline(Executive_CooperativeTasker_Task *task)
{
	/* XXX use maacros to update flags */
	/* XXX if thread isn't THF_READY bail */
	task->data.mainThread->data.flags = THF_RUNNING;
	sigsetjmp(task->data.mainThread->data.env, 0);
	if(task->data.mainThread->data.flags & THF_RUNNING)
	{
		EXLOGF((LOG_DEBUG, "trampoline(): transferring control to entrypoint of thread %u", task->data.mainThread->data.id));
		task->data.mainThread->data.entrypoint(&task->data.mainThread->Thread);
		task->data.mainThread->data.flags = THF_COMPLETED;
		EXLOGF((LOG_DEBUG, "trampoline(): thread %u has finished", task->data.mainThread->data.id));
		sigsetjmp(task->data.mainThread->data.env, 0);
	}
	else
	{
		EXLOGF((LOG_DEBUG, "trampoline(): thread %u is a zombie", task->data.mainThread->data.id));
	}
}

static void
Executive_CooperativeTasker_yield(ITasker *me)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);
	Executive_CooperativeTasker_Task *task;
	int l;

	ExTrace("Executive::CooperativeTasker::yield()");
/* XXX placeholders */
#define TASK_CONTEXT_SAVE (self->data.currentTask ? sigsetjmp(self->data.currentTask->data.mainThread->data.env, 0) : 0)
#define TASK_IS_RUNNABLE(task) (task && Executive_CooperativeTasker_Task_runnable(task))
#define TASK_CONTEXT_RESTORE(newTask) self->data.currentTask = newTask; \
	if((!((newTask)->data.mainThread->data.flags & THF_RUNNING))) \
	{ \
		trampoline(newTask); \
		return; \
	} \
	else \
	{ \
		siglongjmp(self->data.currentTask->data.mainThread->data.env, 1); \
	}

	if(0 == TASK_CONTEXT_SAVE)
	{
		ExTrace("saved context");
		/* loop through the list of tasks to find the next runnable task
		 *
		 * this is an purposefully minimal and simplistic implementation
		 */
		task = self->data.currentTask;
		l = 0;
		do
		{
			/* if there's a current task */
			if(NULL != task && NULL != task->data.nextTask)
			{
				task = task->data.nextTask;
			}
			else
			{
				task = self->data.firstTask;
				if(l)
				{
					/* prevent looping forever if there's no current task
					 * and no other tasks are runnable yet 
					 */
					break;
				}
				l = 1;
			}
			if(!task)
			{
				ExTrace("no available tasks at all");
				break;
			}
		}
		while(!TASK_IS_RUNNABLE(task));
		if(task == self->data.currentTask)
		{
			task = NULL;
		}
		if(!task || !TASK_IS_RUNNABLE(task))
		{
			ExTrace("Executive::CooperativeScheduler::yield(): no [other] runnable tasks");
			/* no runnable tasks */
			IPlatform_nap(executive.data.platform);
			return;
		}
		/* Switch to the new task */
		ExTrace("will now switch to new task");
		TASK_CONTEXT_RESTORE(task);
	}
	/* This is now the context of the new task */
	ExTrace("Executive::CooperativeScheduler::yield(): resuming");
}

static void
Executive_CooperativeTasker_tick(ITasker *me)
{
	/* XXX is there no current task, or has the current thread exceeded its
	 * runtime?
	 */
	Executive_CooperativeTasker_yield(me);
}

/* Executive::CooperativeTasker::<ITasker>createTask()
 *
 * Create a new task using the supplied task creation parameters structure,
 * returning the interface specified by iid in out
 *
 * A failure to return a requested interface on the new task does not cause
 * the task to be destroyed, because it is automatically added to the Tasker's
 * list of tasks
 */
static TASKID
Executive_CooperativeTasker_createTask(ITasker *me, const struct TaskCreationParameters *params, REFUUID iid, void **out)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);
	Executive_CooperativeTasker_Task *task;

	/* Validate parameters */
	ExAssert(params != NULL);
	EXTRACEF(("Executive::CooperativeTasker::createTask({ .name = '%s' })", params->name));
	if(out)
	{
		/* If the task was created successfully, the caller must test out to
		 * check that queryInterface was successful
		 */
		*out = NULL;
	}
	/* Create the task itself */
	task = ExAlloc(sizeof(Executive_CooperativeTasker_Task));
	if(!task)
	{
		EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::createTask(): ExAlloc(%u) failed", sizeof(Executive_CooperativeTasker_Task)));
		return E_NOMEM;
	}
	task->data.vtable = &Executive_CooperativeTasker_Task_vtable;
	/* Assign the task an ID */
	task->data.tasker = self;
	task->data.id = self->data.nextTaskId;
	self->data.nextTaskId++;
	/* Apply task flags */
	/* XXX sanitise flags */
	task->data.flags = params->flags;
	/* Add the task to the list of tasks */
	if(self->data.lastTask)
	{
		self->data.lastTask->data.nextTask = task;
	}
	else
	{
		self->data.firstTask = task;
	}
	self->data.lastTask = task;
	/* Are we ready to create a main thread? */
	if(params->mainThread_entrypoint)
	{
		EXTRACEF(("Executive::CooperativeTasker::createTask(): entrypoint provided"));
		task->data.mainThread = ExAlloc(sizeof(Executive_CooperativeTasker_Thread));
		if(!task->data.mainThread)
		{
			ITask_release((&(task->Task)));
			return E_NOMEM;
		}
		task->data.mainThread->data.vtable = &Executive_CooperativeTasker_Thread_vtable;
		task->data.mainThread->data.id = self->data.nextThreadId;
		self->data.nextThreadId++;
		task->data.mainThread->data.task = task;
		task->data.mainThread->data.entrypoint = params->mainThread_entrypoint;
		task->data.mainThread->data.stackBase = ExAlloc(EXEC_THREAD_STACK_SIZE);
		task->data.mainThread->data.stackSize = EXEC_THREAD_STACK_SIZE;
		task->data.mainThread->data.flags = THF_READY;
		task->data.flags |= TF_READY;
		EXTRACEF(("Executive::CooperativeTasker::createTask(): new task state is READY"));
	}
	if(out)
	{
		IObject_queryInterface((&(task->Object)), iid, out);
	}
	return task->data.id;
}

#undef INTF_TO_CLASS

/** Executive::CooperativeTasker::Task **/

#define INTF_TO_CLASS(i)               (Executive_CooperativeTasker_Task *)((void *)(i))

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

/* INTERNAL: Executive::CooperativeTasker::Task::runnable()
 *
 * Examine a candidate task, and if it's runnable, return 1,
 * otherwise 0
 */
static int
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
		case TF_WAITING:
			/* check whatever it is we are waiting for? */
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

/** Executive::CooperativeTasker::Thread **/

#define INTF_TO_CLASS(i)               (Executive_CooperativeTasker_Thread *)((void *)(i))

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