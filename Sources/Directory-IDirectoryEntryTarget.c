#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory *)((i)->instptr)

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

	EXLOGF((LOG_TRACE, "Executive::Directory::<IDirectoryEntryTarget>linked('%s')", IDirectoryEntry_name(entry)));
	switch(self->data.kind)
	{
	case DK_SYSTEM:
		EXLOGF((LOG_DEBUG, "Executive::Directory: populating the /System domain"));
		ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "Platform", &CLSID_PAL_Platform, (IObject *) (void *) (executive.data.platform)));
		self->data.last->data.flags |= DEF_HIDDEN;
		if(executive.data.diagnostics)
		{
			ExAssert(E_SUCCESS == IMutableContainer_add((&(self->MutableContainer)), "Diagnostics", &CLSID_PAL_PlatformDiagnostics, (IObject *) (void *) (executive.data.diagnostics)));
			self->data.last->data.flags |= DEF_HIDDEN;
		}
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Nodes", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Volumes", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Boot", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Subsystems", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Devices", "Platform/Devices", true));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Applications", "Volumes/System/Applications", true));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Library", "Volumes/System/Library", true));
		for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
		{
			entry->data.flags |= DEF_SYSTEM|DEF_IMMUTABLE;
		}
		EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /System domain complete"));
		break;
	case DK_CLUSTER:
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Nodes", &CLSID_Executive_Container, NULL, NULL));
		for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
		{
			entry->data.flags |= DEF_IMMUTABLE;
		}
		EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Cluster domain complete"));
		break;
	case DK_LOCAL:
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Applications", "/System/Volumes/Data/Applications", true));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Library", "/System/Volumes/Data/Library", true));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Users", "/System/Volumes/Data/Users", true));
		ExAssert(E_SUCCESS == IMutableContainer_createLink((&(self->MutableContainer)), "Developer", "/System/Volumes/Data/Developer", true));
		for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
		{
			entry->data.flags |= DEF_IMMUTABLE;
		}
		EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Local domain complete"));
		break;
	case DK_NETWORK:
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Applications", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Library", &CLSID_Executive_Container, NULL, NULL));
		ExAssert(E_SUCCESS == IMutableContainer_create((&(self->MutableContainer)), "Users", &CLSID_Executive_Container, NULL, NULL));
		for(Executive_Directory_Entry *entry = self->data.first; entry; entry = entry->data.next)
		{
			entry->data.flags |= DEF_MOUNTPOINT|DEF_IMMUTABLE;
		}
		EXLOGF((LOG_DEBUG, "Executive::Directory: initial population of the /Network domain complete"));
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

	EXLOGF((LOG_TRACE, "Executive::Directory::<IDirectoryEntryTarget>unlinked(): %s", IDirectoryEntry_name(entry)));
}
