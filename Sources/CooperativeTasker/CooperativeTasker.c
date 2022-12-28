
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_CooperativeTasker.h"

#if FEATURE_COOPERATIVE_TASKER

ITasker *
Executive_CooperativeTasker_create(void)
{
	Executive_CooperativeTasker *tasker;
	STATUS status;
	struct TaskCreationParameters taskInfo;

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
	/* Once the Executive yields control to the Tasker, it never returns except
	 * in the event a catastrophic failure, and so we need a (lowest-priority)
	 * thread that is always runnable and simply invokes IPlatform::nap() and
	 * ITasker::yield() in an infinite loop. This is task 0, the Sentinel
	 * task.
	 */
 	/* Create the Sentinel task */
	ExLog(LOGLEVEL, "Creating the Sentinel task...");
	RtMemSet(&taskInfo, 0, sizeof(taskInfo));
	taskInfo.flags = TF_EXECUTIVE /* | TF_SENTINEL | TF_CRITICAL */;
	/* taskInfo.priority = TP_LOWEST; */
	taskInfo.name = "Sentinel";
	taskInfo.addressSpace = NULL; 
	taskInfo.namespace = executive.data.rootNS;;
	taskInfo.mainThread_entrypoint = Executive_CooperativeTasker_Sentinel_mainThread;

	if(E_SUCCESS != (status = ITasker_createTask((&(tasker->Tasker)), &taskInfo, NULL, NULL)))
	{
		EXLOGF((LOG_CRIT, "%s: unable to open to create Sentinel task: %s", ExStatusName(status), ExStatusMsg(status)));
		ExFree(tasker);
		return NULL;;
	}
	return &(tasker->Tasker);
}

#endif /*FEATURE_COOPERATIVE_TASKER*/
