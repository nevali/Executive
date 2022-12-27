#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* Special handling for /Network directory (DK_NETWORK) */

STATUS
Executive_Directory_Network_populate(IMutableContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

#if FEATURE_DEBUG_NAMESPACE
	EXLOGF((LOG_DEBUG, "Executive::Directory: populating the /Network domain"));
#endif
	ExPhaseShift(PHASE_STARTUP_NETWORK);
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Applications", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Library", &CLSID_Executive_Container, NULL, NULL));
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Users", &CLSID_Executive_Container, NULL, NULL));
	for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
	{
		entry->data.flags |= DEF_MOUNTPOINT|DEF_IMMUTABLE;
	}
#if FEATURE_DEBUG_NAMESPACE
	EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Network domain complete"));
#endif
	return E_SUCCESS;
}
