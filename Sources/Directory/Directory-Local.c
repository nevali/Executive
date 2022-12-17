#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* Special handling for /Local directory (DK_LOCAL) */

STATUS
Executive_Directory_Local_populate(IMutableContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

	EXLOGF((LOG_DEBUG, "Executive::Directory: populating the /Local domain"));
/*	ExPhaseShift(PHASE_STARTUP_LOCAL); */

	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Applications", "/System/Volumes/Data/Applications", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Tools", "/System/Volumes/Data/Tools", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Library", "/System/Volumes/Data/Library", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Users", "/System/Volumes/Data/Users", true));
	ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Developer", "/System/Volumes/Data/Developer", true));

	for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
	{
		entry->data.flags |= DEF_SYSTEM|DEF_IMMUTABLE;
	}
	EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Local domain complete"));

	return E_SUCCESS;
}
