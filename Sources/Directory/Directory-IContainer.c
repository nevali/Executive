#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<IContainer> **/

const struct IContainer_vtable_ Executive_Directory_IContainer_vtable = {
	(STATUS (*)(IContainer *, REFUUID, void **))(void *) &Executive_Directory_queryInterface,
	(REFCOUNT (*)(IContainer *))(void *) &Executive_Directory_retain,
	(REFCOUNT (*)(IContainer *))(void *) &Executive_Directory_release,
	Executive_Directory_resolve,
	Executive_Directory_iterator
};

STATUS
Executive_Directory_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *iterator;

	ExAssert(NULL != name);
	ExAssert(NULL != entry);
	*entry = NULL;
	
	EXTRACEF(("Executive::Directory::<IContainer>resolve('%s')", name));
	for(iterator = self->data.first; iterator; iterator = iterator->data.next)
	{
		if(ExStrEqual(iterator->data.name, name))
		{
#if FEATURE_DEBUG_NAMESPACE
			EXLOGF((LOG_DEBUG7, "Executive::Directory::resolve(): entry located"));
#endif
			IDirectoryEntry_retain((&(iterator->DirectoryEntry)));
			*entry = &(iterator->DirectoryEntry);
			return E_SUCCESS;
		}
	}
#if FEATURE_DEBUG_NAMESPACE
	EXLOGF((LOG_CONDITION, "%%E-NOENT: object '%s' could not be found", name));
#endif
	return E_NOENT;
}

IIterator *
Executive_Directory_iterator(IContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	return (IIterator *)(void *) Executive_Directory_Iterator_create(self->data.first);
}
