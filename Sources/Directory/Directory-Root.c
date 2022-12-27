#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* Special handling for the root of the object directory (DK_ROOT) */

STATUS
Executive_Directory_Root_populate(IMutableContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	IMutableContainer *mutableContainer;

#if FEATURE_DEBUG_NAMESPACE
	EXLOGF((LOG_DEBUG, "Executive::Directory: creating the root directory objects"));
#endif
/*	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "System", &CLSID_Executive_System, NULL, NULL)); */
	ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "System", &CLSID_Executive_System, &(executive.Object)));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Users", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Volumes", &CLSID_Executive_Container, &IID_IMutableContainer, (void **) &mutableContainer));
	ExAssert(E_SUCCESS == IMutableContainer_createLink(mutableContainer, "System", "/System/Volumes/System", true));
	IMutableContainer_release(mutableContainer);
	
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Local", &CLSID_Executive_Local, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Cluster", &CLSID_Executive_Cluster, NULL, NULL));
	for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
	{
		entry->data.flags |= DEF_SYSTEM|DEF_IMMUTABLE;
	}
	return E_SUCCESS;
}
