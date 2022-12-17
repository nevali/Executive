#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

#include <Executive/Internal/Executive.h>
#include <PAL/Platform.h>
#include <PAL/BootEnvironment.h>

/* Special handling for /System directory (DK_SYSTEM) */

STATUS
Executive_Directory_System_populate(IMutableContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	IContainer *container;
	IMutableContainer *mutableContainer;

	EXLOGF((LOG_DEBUG, "Executive::Directory: populating the /System domain"));
/*	ExPhaseShift(PHASE_STARTUP_SYSTEM); */

	ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "Allocator", &CLSID_Executive_Allocator, (void *) (executive.data.allocator)));
	self->data.last->data.flags |= DEF_HIDDEN;

	ExAssert(E_SUCCESS == ExMetaClass(&CLSID_Executive_Classes, &IID_IContainer, &container));
	ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "Classes", &CLSID_Executive_Classes, (void *) container));
	self->data.last->data.flags |= DEF_HIDDEN;
	IContainer_release(container);

	ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "Platform", &CLSID_PAL_Platform, (void *) (executive.data.platform)));
	self->data.last->data.flags |= DEF_HIDDEN;

	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Subsystems", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Boot", &CLSID_Executive_Container, &IID_IMutableContainer, (void **) &mutableContainer));
	self->data.last->data.flags |= DEF_HIDDEN;
	/* XXX we should add via ExMetaClass() and do away with executive.data.bootEnvironment altogether */
	if(executive.data.bootEnvironment)
	{
		ExAssert(E_SUCCESS == IMutableContainer_add(mutableContainer, "Environment", &CLSID_PAL_BootEnvironment, (void *) executive.data.bootEnvironment));
	}
	IMutableContainer_release(mutableContainer);

	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Nodes", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Volumes", &CLSID_Executive_Container, &IID_IMutableContainer, (void **) &mutableContainer));
	
	ExAssert(E_SUCCESS == IMutableContainer_create(mutableContainer, "Boot", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create(mutableContainer, "System", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create(mutableContainer, "Data", &CLSID_Executive_Container, NULL, NULL));
	IMutableContainer_release(mutableContainer);

	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Devices", "Platform/Devices", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Applications", "Volumes/System/Applications", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Library", "Volumes/System/Library", true));

	for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
	{
		entry->data.flags |= DEF_SYSTEM|DEF_IMMUTABLE;
	}
	EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /System domain complete"));

	return E_SUCCESS;
}
