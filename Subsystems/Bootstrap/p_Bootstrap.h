#ifndef P_BOOTSTRAP_H_
# define P_BOOTSTRAP_H_

# define INITGUID_EXTERN               1

# include <Executive/IObject.h>
# include <Executive/ISubsystem.h>
# include <Executive/INamespace.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Executive/IWriteChannel.h>
# include <Executive/ITasker.h>
# include <Executive/ITask.h>
# include <Executive/IThread.h>
# include <Executive/IContainer.h>

typedef struct Bootstrap Bootstrap;

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
		INamespace *root;
		IPlatformDiagnostics *diagnostics;
		IWriteChannel *console;
		ITask *sentinel;
	} data;
};

extern IObject *bootstrap_IObject;

void Bootstrap_Sentinel_mainThread(IThread *self);

#endif /*!P_BOOTSTRAP_H_*/
