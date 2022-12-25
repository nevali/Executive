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

#include "p_CooperativeTasker.h"

/* XXX placeholder */
#include <setjmp.h>

#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_CooperativeTasker)

/* ITasker */
static void Executive_CooperativeTasker_tick(ITasker *me);
void Executive_CooperativeTasker_yield(ITasker *me);
static STATUS Executive_CooperativeTasker_createTask(ITasker *me, const struct TaskCreationParameters *params, REFUUID iid, void **out);
static void Executive_CooperativeTasker_interrupt(ITasker *me, int processor, IObject **despatchContext, IThread **curThread);
static void Executive_CooperativeTasker_resume(ITasker *me, int processor);

/* PRIVATE */
static volatile Executive_CooperativeTasker_Thread *Executive_CooperativeTasker_nextRunnableThread(Executive_CooperativeTasker *self);

const struct ITasker_vtable_ Executive_CooperativeTasker_ITasker_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_CooperativeTasker, ITasker),
	Executive_CooperativeTasker_tick,
	Executive_CooperativeTasker_yield,
	Executive_CooperativeTasker_createTask,
	Executive_CooperativeTasker_interrupt,
	Executive_CooperativeTasker_resume
};

#if 0
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
#endif

/* Executive::CooperativeTasker::yield()
 * Voluntarily relinquish CPU time
 *
 * yield() is invoked when a thread wishes to voluntarily relinquish its CPU
 * time allocation, for example because it's waiting on some external event to
 * occur
 *
 * if there are no other runnable threads, IPlatform::nap() is invoked, and
 * then control is returned to the caller
 *
 * otherwise, invoke IPlatform::tick() and switch context to the next
 * runnable thread
 *
 * see also tick(), which performs a similar function, but if there are no
 * other runnable threads, invokes IPlatform::tick() and then returns to
 * thew caller
 */
void
Executive_CooperativeTasker_yield(ITasker *me)
{
	volatile Executive_CooperativeTasker *self = INTF_TO_CLASS(me);
	volatile Executive_CooperativeTasker_Thread *thread, *nextThread;

	EXTRACEF(("Executive::CooperativeTasker::yield()"));
	EXLOGF((LOG_DEBUG, "currentThread = %p", self->data.currentThread));
	EXLOGF((LOG_DEBUG, "runnable threads list:-"));
	for(thread = self->data.firstRunnableThread; thread; thread = thread->data.nextRunnable)
	{
		EXLOGF((LOG_DEBUG, " runnable thread: %p => %u:%u", thread, thread->data.task->data.id, thread->data.id));
	}
	/* if there's a current thread, suspend it */
	self->data.previousThread = NULL;
	if(self->data.currentThread)
	{
		if(Executive_CooperativeTasker_Thread_suspend((Executive_CooperativeTasker_Thread *) self->data.currentThread))
		{
			EXTRACEF(("Executive::CooperativeTasker::yield(): resumed (self->data.currentThread = %p)", self->data.currentThread));
			return;
		}
	}
	nextThread = Executive_CooperativeTasker_nextRunnableThread((Executive_CooperativeTasker *) self);
	EXLOGF((LOG_DEBUG, "Executive::CooperativeTasker::yield(): nextThread = %p", nextThread));
	if(!nextThread)
	{
		EXTRACEF(("Executive::CooperativeTasker::yield(): no runnable threads"));
		IPlatform_nap(executive.data.platform);
		return;
	}
	if(nextThread == self->data.previousThread)
	{
		EXTRACEF(("Executive::CooperativeTasker::yield(): no other runnable threads; napping before resumption"));
		IPlatform_nap(executive.data.platform);
	}
	else
	{
		IPlatform_tick(executive.data.platform);
	}
	Executive_CooperativeTasker_Thread_resume((Executive_CooperativeTasker_Thread *) nextThread);
}

static void
Executive_CooperativeTasker_tick(ITasker *me)
{
	UNUSED__(me);

	/* XXX is there no current task, or has the current thread exceeded its
	 * runtime?
	 */
	IPlatform_tick(executive.data.platform);
}

static volatile Executive_CooperativeTasker_Thread *
Executive_CooperativeTasker_nextRunnableThread(Executive_CooperativeTasker *self)
{
	volatile Executive_CooperativeTasker_Thread *thread;

	/* Find the next runnable thread, starting with the previous thread's
	 * next runnable thread pointer (if it has one)
	 */
	 if(self->data.previousThread)
	 {
		if(NULL != (thread = self->data.previousThread->data.nextRunnable))
		{
			EXLOGF((LOG_DEBUG, "previously-running thread had a next-runnable pointer, using that"));
			/* XXX assert that it is in fact runnable */
			return thread;
		}
		EXLOGF((LOG_DEBUG, "there WAS a previous thread, but it was the end of the chain"));
	}
	/* Otherwise, start at the beginning of the list */
	EXLOGF((LOG_DEBUG, "next runnable thread is first runnable thread"));
	return (Executive_CooperativeTasker_Thread *) self->data.firstRunnableThread;
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
	Executive_CooperativeTasker_Task *task, *p;
	STATUS status;

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
	if(E_SUCCESS != (status = Executive_createObject(&CLSID_Executive_DespatchContext, &IID_IObject, (void **) &(task->data.despatchContext))))
	{
		EXLOGF((LOG_CONDITION, "??? failed to create despatch context for new task!"));
		ExFree(task);
		return status;
	}
	task->data.vtable = &Executive_CooperativeTasker_Task_vtable;
	task->data.refCount = 1;
	task->data.tasker = self;
	task->data.id = self->data.nextTaskId;
	self->data.nextTaskId++;
	if(NULL == params->namespace)
	{
		/* XXX inherit from parent task */
		task->data.ns = executive.data.rootNS;
	}
	else
	{
		task->data.ns = params->namespace;
	}
	INamespace_retain(task->data.ns);
	if(NULL == params->addressSpace)
	{
		/* XXX inherit from parent task */
		task->data.addressSpace = executive.data.addressSpace;
	}
	else
	{
		task->data.addressSpace = params->addressSpace;
	}
	IAddressSpace_retain(task->data.addressSpace);
	/* Apply task flags */
	/* XXX sanitise flags */
	task->data.flags = params->flags;
	/* Add the task to the list of tasks */
	if(self->data.firstTask)
	{
		for(p = self->data.firstTask; p->data.nextTask; p = p->data.nextTask)
		{
		}
		p->data.nextTask = task;
	}
	else
	{
		self->data.firstTask = task;
	}
	/* Are we ready to create a main thread? */
	if(params->mainThread_entrypoint)
	{
		EXTRACEF(("Executive::CooperativeTasker::createTask(): entrypoint provided"));
		Executive_CooperativeTasker_Thread_create(task, params->mainThread_entrypoint);
		if(!task->data.mainThread)
		{
			/* ew */
			task->data.refCount = 1;
			ITask_release((&(task->Task)));
			EXLOGF((LOG_CONDITION, "Executive::CooperativeTasker::createTask(): failed to create main thread"));
			return E_NOMEM;
		}
		task->data.flags |= TF_READY;
		EXTRACEF(("Executive::CooperativeTasker::createTask(): new task state is READY"));
	}
	if(out)
	{
		IObject_queryInterface((&(task->Object)), iid, out);
	}
	return task->data.id;
}

static void
Executive_CooperativeTasker_interrupt(ITasker *me, int processor, IObject **despatchContext, IThread **curThread)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	UNUSED__(processor);

	EXTRACEF(("Executive::CooperativeTasker::interrupt(%d)", processor));
	if(despatchContext)
	{
		*despatchContext = NULL;
		if(self->data.currentTask)
		{
			*despatchContext = self->data.currentTask->data.despatchContext;
		}
	}
	if(curThread)
	{
		*curThread = (IThread *) &(self->data.currentThread->Thread);
		if(*curThread)
		{
			IThread_retain((*curThread));
		}
	}
	if(self->data.currentThread)
	{
		/* XXX set THF_TRAP*/
	}
}

static void
Executive_CooperativeTasker_resume(ITasker *me, int processor)
{
	UNUSED__(processor);

	EXTRACEF(("Executive::CooperativeTasker::resume(%d)", processor));
	Executive_CooperativeTasker_tick(me);
}

