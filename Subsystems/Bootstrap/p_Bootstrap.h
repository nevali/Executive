#ifndef P_BOOTSTRAP_H_
# define P_BOOTSTRAP_H_

# define INITGUID_EXTERN               1

# include <Executive/Classes.h>

# include <Executive/IObject.h>
# include <Executive/ISubsystem.h>
# include <Executive/INamespace.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Executive/IWriteChannel.h>
# include <Executive/ITasker.h>
# include <Executive/ITask.h>
# include <Executive/IThread.h>
# include <Executive/IContainer.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IExecutable.h>

#define ExUuidEqual(a, b) ((a)->d.d1 == (b)->d.d1 && (a)->d.d2 == (b)->d.d2 && (a)->d.d3 == (b)->d.d3 && (a)->d.d4 == (b)->d.d4)

typedef struct Bootstrap Bootstrap;
typedef union Bootstrap_ResidentTask Bootstrap_ResidentTask;

struct Bootstrap
{
	/* Supported interfaces */
	IObject Object;
	ISubsystem Subsystem;
	IContainer Container;
	/* Instance data */
	struct
	{
		bool running;
		IMutableContainer *container;
		INamespace *root;
		IPlatformDiagnostics *diagnostics;
		IWriteChannel *console;
		ITasker *tasker;
		ITask *sentinel;
	} data;
};

union Bootstrap_ResidentTask
{
	IObject Object;
	IExecutable Executable;
	struct
	{
		const void *vtable;
		Bootstrap *bootstrap;
		ThreadEntrypoint entry;
	} data;
};

extern IObject *bootstrap_IObject;
extern Bootstrap_ResidentTask Bootstrap_startupTask;

void Bootstrap_ResidentTask_init(Bootstrap_ResidentTask *self, Bootstrap *bootstrap, ThreadEntrypoint entry);

void Bootstrap_Startup_mainThread(IThread *self);

void Bootstrap_Sentinel_mainThread(IThread *self);

#endif /*!P_BOOTSTRAP_H_*/
