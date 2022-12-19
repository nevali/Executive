
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_CooperativeTasker.h"

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
