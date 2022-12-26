#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* for CLSID_PAL_xxx */
#include <PAL/PAL.h>

/** Executive::Directory<IDirectoryEntryTarget> **/

const struct IDirectoryEntryTarget_vtable_ Executive_Directory_IDirectoryEntryTarget_vtable = {
	(STATUS (*)(IDirectoryEntryTarget *, REFUUID, void **))(void *) &Executive_Directory_queryInterface,
	(REFCOUNT (*)(IDirectoryEntryTarget *))(void *) &Executive_Directory_retain,
	(REFCOUNT (*)(IDirectoryEntryTarget *))(void *) &Executive_Directory_release,
	Executive_Directory_linked,
	Executive_Directory_unlinked
};

void
Executive_Directory_linked(IDirectoryEntryTarget *me, IDirectoryEntry *entry)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

	UNUSED__(entry);

/*	EXLOGF((LOG_TRACE, "Executive::Directory::<IDirectoryEntryTarget>linked('%s')", (entry ? IDirectoryEntry_name(entry) : "(NULL)"))); */
	switch(self->data.kind)
	{
	case DK_ROOT:
		{
			ExAssert(E_SUCCESS == Executive_Directory_Root_populate(&(self->MutableContainer)));
		}
		break;
	case DK_SYSTEM:
		{
			ExAssert(E_SUCCESS == Executive_Directory_System_populate(&(self->MutableContainer)));
		}
		break;
	case DK_LOCAL:
		{
			ExAssert(E_SUCCESS == Executive_Directory_Local_populate(&(self->MutableContainer)));
		}
		break;
	case DK_CLUSTER:
		{
			ExAssert(E_SUCCESS == Executive_Directory_Cluster_populate(&(self->MutableContainer)));
		}
		break;
	case DK_NETWORK:
		{
			ExAssert(E_SUCCESS == Executive_Directory_Network_populate(&(self->MutableContainer)));
		}
		break;
	default:
		return;
	}
}

void
Executive_Directory_unlinked(IDirectoryEntryTarget *me, IDirectoryEntry *entry)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

	UNUSED__(self);
	UNUSED__(entry);

/*	EXLOGF((LOG_TRACE, "Executive::Directory::<IDirectoryEntryTarget>unlinked(): %s", IDirectoryEntry_name(entry))); */
}
