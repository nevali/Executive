#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<MDirectoryEntryTarget> **/

static STATUS Executive_Directory_MDirectoryEntryTarget_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);

struct MDirectoryEntryTarget_vtable_ Executive_Directory_MDirectoryEntryTarget_vtable = {
	(STATUS (*)(MDirectoryEntryTarget *, REFUUID, void **)) &Executive_Directory_MetaClass_queryInterface,
	(REFCOUNT (*)(MDirectoryEntryTarget *)) &Executive_Directory_MetaClass_retain,
	(REFCOUNT (*)(MDirectoryEntryTarget *)) &Executive_Directory_MetaClass_release,
	Executive_Directory_MDirectoryEntryTarget_createInstance,
};

static STATUS
Executive_Directory_MDirectoryEntryTarget_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	Executive_Directory_MetaClass *self = (Executive_Directory_MetaClass *) me->instptr;
	Executive_Directory *dir;

	/* This class method is invoked when a container wants to create a new
	 * instance of Executive::Directory::System
	 */
	ExAssert(NULL != out);

/*	EXLOGF((LOG_TRACE, "Executive::Directory::[Generic]<MDirectoryEntryTarget>::+createInstance(%d, %s)", self->kind, (entry ? IDirectoryEntry_name(entry) : "NULL" ))); */

	*out = NULL;
	if(self->kind == DK_ROOT)
	{
		ExAssert(NULL == entry);
		if(NULL != entry)
		{
			return E_INVAL;
		}
	}
	else
	{
		ExAssert(NULL != entry);
		if(NULL == entry)
		{
/*			EXLOGF((LOG_CONDITION, "%%E-INVAL: Executive::Directory::[Generic]::+createInstance() invoked with entry == NULL and self->kind = %d", self->kind)); */
			return E_INVAL;
		}
	}
	if(!(dir = ExAlloc(sizeof(Executive_Directory))))
	{
		EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Directory)));
		return E_NOMEM;
	}
	dir->Object.lpVtbl = &Executive_Directory_IObject_vtable;
	dir->Object.instptr = dir;
	dir->Container.lpVtbl = &Executive_Directory_IContainer_vtable;
	dir->Container.instptr = dir;
	dir->MutableContainer.lpVtbl = &Executive_Directory_IMutableContainer_vtable;
	dir->MutableContainer.instptr = dir;
	dir->DirectoryEntryTarget.lpVtbl = &Executive_Directory_IDirectoryEntryTarget_vtable;
	dir->DirectoryEntryTarget.instptr = dir;
	if(self->kind == DK_ROOT)
	{
		dir->Namespace.lpVtbl = &Executive_Directory_INamespace_vtable;
		dir->Namespace.instptr = dir;
	}
	dir->data.refCount = 1;
	dir->data.kind = self->kind;
#ifndef NDEBUG
	switch(self->kind)
	{
		case DK_ROOT:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Root (Object Directory root)"));
			/* it should not be possible to create a new root directory if one
			 * already exists
			 */
			/* ExAssert(NULL == executive.data.rootDirectory); */
			break;
		case DK_DOMAIN:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::Domain ('%s')", IDirectoryEntry_name(entry))); */
			break;
		case DK_SYSTEM:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::System ('%s')", IDirectoryEntry_name(entry))); */
			break;
		case DK_NETWORK:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::Network ('%s')",  IDirectoryEntry_name(entry))); */
			break;
		case DK_LOCAL:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::Local ('%s')",  IDirectoryEntry_name(entry))); */
			break;
		case DK_CLUSTER:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::Cluster ('%s')",  IDirectoryEntry_name(entry))); */
			break;
		case DK_CONTAINER:
/*			EXLOGF((LOG_DEBUG, "created Executive::Directory::Container ('%s')",  IDirectoryEntry_name(entry))); */
			break;
	}
#endif
	*out = &(dir->DirectoryEntryTarget);
	return E_SUCCESS;
}
