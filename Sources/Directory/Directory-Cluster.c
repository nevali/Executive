#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* Special handling for /Cluster directory (DK_CLUSTER) */

STATUS
Executive_Directory_Cluster_populate(IMutableContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

	EXLOGF((LOG_DEBUG, "Executive::Directory: populating the /Cluster domain"));
	ExPhaseShift(PHASE_STARTUP_CLUSTER);
	ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Nodes", &CLSID_Executive_Container, NULL, NULL));
	for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
	{
		entry->data.flags |= DEF_IMMUTABLE;
	}
	EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Cluster domain complete"));

	return E_SUCCESS;
}
