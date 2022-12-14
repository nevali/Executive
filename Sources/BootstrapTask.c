#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

extern void Executive_Directory_dump(IContainer *me);

void
Executive_StartupTask_mainThread(IThread *self)
{
	UNUSED__(self);

	for(;;)
	{
		ExTrace("Executive::StartupTask::mainThread(): Pong");
		ExYield();
	}
}

void
Executive_BootstrapTask_mainThread(IThread *self)
{
	struct TaskCreationParameters taskInfo;
	IWriteChannel *diag;

	UNUSED__(self);

	EXLOGF((LOG_TRACE, "Executive::BootstrapTask::mainThread() started"));
	diag = NULL;
	if(E_SUCCESS == ExOpen("/System/Diagnostics", &IID_IWriteChannel, &diag))
	{
		const char *message = "========================================================================\n"
			" Executive -- Bootstrap Task -- Diagnostic Interface\n"
			"========================================================================\n";
		EXLOGF((LOG_DEBUG7, "successfully opened diagnostic channel"));
		IWriteChannel_write(diag, (const uint8_t *) message, ExStrLen(message));
	}
	else
	{
		EXLOGF((LOG_DEBUG7, "unable to open diagnostic channel"));
	}
	/* Ask the PAL for its device manager */
	/* Add the device manager as /System/Nodes/localhost/Devices */
	/* Add /System/Devices as link to /System/Nodes/localhost/Devices */
	/* Locate a console */
//	ExAssert(E_SUCCESS == ExOpen("/System/Devices/Console", &IID_IReadWriteChannel, &console));

	/* Print boot messages */
	/* Start secondary processors */
	/* Mount the system volume */
	/* Spawn the first child task */
	taskInfo.flags = TF_EXECUTIVE;
	taskInfo.name = "Startup";
	taskInfo.mainThread_entrypoint = Executive_StartupTask_mainThread;
	ITasker_createTask(executive.data.tasker, &taskInfo, &IID_ITask, NULL);

	Executive_Directory_dump((IContainer *) (void *) executive.data.rootNS);

	if(diag)
	{
		IWriteChannel_release(diag);
	}

	/* Yield to the scheduler forever */
	for(;;)
	{
		ExTrace("Executive::BootstrapTask::mainThread(): Ping");
		ExYield();
	}
}
