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

const struct ITasker_vtable_ Executive_CooperativeTasker_ITasker_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_CooperativeTasker, ITasker),
	Executive_CooperativeTasker_tick,
	Executive_CooperativeTasker_yield,
	Executive_CooperativeTasker_createTask
};

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

void
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
