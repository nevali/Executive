#ifndef P_COOPERATIVETASKER_H_
# define P_COOPERATIVETASKER_H_        1

# define INITGUID_EXTERN               1

# include <Executive/ITasker.h>
# include <Executive/ITask.h>
# include <Executive/Internal/Classes.h>
# include <Executive/Internal/Executive.h>

# define EXEC_THREAD_STACK_SIZE        32768

/* XXX XXX XXX TEMPORARY */
# include <setjmp.h>

typedef struct Executive_CooperativeTasker Executive_CooperativeTasker;
typedef union Executive_CooperativeTasker_Task Executive_CooperativeTasker_Task;
typedef union Executive_CooperativeTasker_Thread Executive_CooperativeTasker_Thread;

struct Executive_CooperativeTasker
{
	ITasker Tasker;
	IObject Object;
	IContainer Container;
	struct
	{
		REFCOUNT refCount;
		Executive_CooperativeTasker_Task *firstTask;
		TASKID nextTaskId;
		long nextThreadId;
		/* XXX per-CPU */
		Executive_CooperativeTasker_Task *currentTask;
		Executive_CooperativeTasker_Thread *previousThread;
		Executive_CooperativeTasker_Thread *currentThread;
		Executive_CooperativeTasker_Thread *firstRunnableThread;
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
		/* the object namespace this task uses */
		INamespace *ns;
		IJob *job;
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
		Executive_CooperativeTasker *tasker;
		/* which task are we part of */
		Executive_CooperativeTasker_Task *task;
		/* pointer to the next thread in the task's list */
		Executive_CooperativeTasker_Thread *nextThread;
		/* pointer to the next runnable thread in the global list */
		Executive_CooperativeTasker_Thread *nextRunnable;
		/* pointer to the thread's stack */
		uint8_t *stackBase;
		size_t stackSize;
		ThreadEntrypoint entrypoint;
		/* XXX */
		sigjmp_buf env; 
		/* IEvent *eventQueue; */
	} data;
};

extern const struct IObject_vtable_ Executive_CooperativeTasker_IObject_vtable;
extern const struct ITasker_vtable_ Executive_CooperativeTasker_ITasker_vtable;
extern const struct IContainer_vtable_ Executive_CooperativeTasker_IContainer_vtable;
extern const struct ITask_vtable_ Executive_CooperativeTasker_Task_vtable;
extern const struct IThread_vtable_ Executive_CooperativeTasker_Thread_vtable;

/* XXX Metaclass interface */
/* XXX PrivateHeaders/Executive/Internal/CooperativeTasker.h */
extern ITasker *Executive_CooperativeTasker_create(void);

STATUS Executive_CooperativeTasker_queryInterface(IObject *me, REFUUID iid, void **out);
REFCOUNT Executive_CooperativeTasker_retain(IObject *me);
REFCOUNT Executive_CooperativeTasker_release(IObject *me);

void Executive_CooperativeTasker_yield(ITasker *me);

bool Executive_CooperativeTasker_Thread_suspend(Executive_CooperativeTasker_Thread *self);
void Executive_CooperativeTasker_Thread_resume(Executive_CooperativeTasker_Thread *self);
void Executive_CooperativeTasker_Thread_schedule(Executive_CooperativeTasker_Thread *self);
void Executive_CooperativeTasker_Thread_unschedule(Executive_CooperativeTasker_Thread *self);

#endif /*!P_COOPERATIVETASKER_H_*/