/* This code must be written as though it runs exclusively in user-space,
 * using only the interfaces provided to it; undefined references to the UUIDs
 * defined by the Executive are okay, other symbols are not.
 */

STATUS
Bootstrap_start(ISubsystem *me, INamespace *root)
{
	Bootstrap *self = INTF_TO_CLASS(me);
	STATUS status;
	struct TaskCreationParameters taskInfo;

	/* Are we already running? */
	if(self->data->running)
	{
		return E_SUCCESS;
	}
	/* Retain the namespace */
	INamespace_retain(root);
	self->data.namespace = root;
	/* Obtain the platform diagnostics interface if possible */
	if(E_SUCCESS != INamespace_open(root, "/System/Devices/Diagnostics", &IID_IPlatformDiagnostics, &(self->data.diagnostics)))
	{
		self->data.diagnostics = NULL;
	}
	/* Open the console if possible */
	if(E_SUCCESS != INamespace_open(root, "/System/Devices/Console", &IID_IWriteChannel, &(self->data.console)))
	{
		self->data.console = NULL;
	}
	/* If no console, can we open a write channel on the diagnostics interface and use that? */
	/* Open /System/Jobs's ICoordinator interface */
	/* Create the Bootstrap job */
	/* Release the job coordinator */
	/* Open /System/Tasks's ITasker interface */
	/* Create the Sentinel task */
#if 0
	/* Ask the tasker to create a task in the Executive's address space */
	taskInfo.flags = TF_EXECUTIVE;
	taskInfo.name = "Sentinel";
	taskInfo.job = self->data.job;
	taskInfo.namespace = root;
	taskInfo.mainThread_entrypoint = Bootstrap_Sentinel_mainThread;

	if(E_SUCCESS != (status = ITasker_createTask(tasker, &taskInfo, &IID_ITask, (void **) &self->data.sentinel))
	{
		ITasker_release(tasker);
		return status;
	}
#endif
	/* Release the Tasker*/
	ITasker_release(tasker);
	return E_SUCCESS;
}
