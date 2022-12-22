#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <Executive/Internal/Executive.h>
#include <Executive/Internal/Entry.h>
#include <Executive/Internal/Resident.h>
#include <Runtime/Runtime.h>
#include <Runtime/Internal/Private.h>
#include <PAL/PAL.h>

static struct ExecutiveEntryParameters params;

const char sim_ident__[] = "@(#) $Simulator: [ " PACKAGE_STRING " build " PRODUCT_BUILD_ID_STR " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST " ] $";

Executive_Resident_Object *
Executive_Resident_objects(void)
{
	return NULL;
}

void
Simulator_mainThread(IThread *self)
{
	UNUSED__(self);

	fprintf(stderr, "Simulator: main thread %p started!\n", self);
	Rt__Initialise(self);
	fprintf(stderr, "Simulator: transferring control to main thread of user program...\n");
	/* XXX should not be "self" here!! */
	mainThread(self);
	fprintf(stderr, "Simulator: main thread ended, exiting\n");
	exit(0);
}

int
main(int argc, char **argv, char **envp)
{
	TaskCreationParameters tcp;

	UNUSED__(argc);
	UNUSED__(argv);
	params.flags = EEF_SIMULATOR|EEF_HAVE_ENVIRON;
	params.environ = envp;
	Executive_start(&params);
	memset(&tcp, 0, sizeof(TaskCreationParameters));
	tcp.mainThread_entrypoint = Simulator_mainThread;
	tcp.name = argv[0];
	tcp.namespace = executive.data.rootNS;
	if(E_SUCCESS != ITasker_createTask(executive.data.tasker, &tcp, NULL, NULL))
	{
		fprintf(stderr, "Simulator: ERROR: failed to create Simulator task\n");
		abort();
	}
	Executive_runLoop(&executive);
	abort();
}
