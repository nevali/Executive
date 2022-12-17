#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<IMutableContainer> **/

const struct IMutableContainer_vtable_ Executive_Directory_IMutableContainer_vtable = {
	(STATUS (*)(IMutableContainer *, REFUUID, void **))(void *) &Executive_Directory_queryInterface,
	(REFCOUNT (*)(IMutableContainer *))(void *) &Executive_Directory_retain,
	(REFCOUNT (*)(IMutableContainer *))(void *) &Executive_Directory_release,
	(REFCOUNT (*)(IMutableContainer *, const char *, IDirectoryEntry **))(void *) &Executive_Directory_resolve,
	(IIterator *(*)(IMutableContainer *))(void *) &Executive_Directory_iterator,
	Executive_Directory_IMutableContainer_create,
	Executive_Directory_add,
	Executive_Directory_createLink
};

static void Executive_Directory_addEntry(Executive_Directory *self, Executive_Directory_Entry *entry);
static void Executive_Directory_Entry_populateObject(Executive_Directory_Entry *self, IObject *object, IDirectoryEntryTarget *delegate);

STATUS
Executive_Directory_IMutableContainer_create(IMutableContainer *me, const char *name, REFUUID clsid, REFUUID iid, void **out)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *entry;
	IDirectoryEntry *dentry;
	MDirectoryEntryTarget *dtmeta;
	IDirectoryEntryTarget *target;
	STATUS status;

	ExAssert(NULL != clsid);
#ifndef NDEBUG
	if(iid)
	{
		EXTRACEF(("Executive::Directory::<IMutableContainer>create('%s', clsid:" UUID_PRINTF_FORMAT ", iid:" UUID_PRINTF_FORMAT ")", name, UUID_PRINTF_ARGS(clsid), UUID_PRINTF_ARGS(iid)));
	}
	else
	{
		EXTRACEF(("Executive::Directory::<IMutableContainer>create('%s', clsid:" UUID_PRINTF_FORMAT ")", name, UUID_PRINTF_ARGS(clsid)));
	}
#endif
	EXDBGF((LOG_DEBUG7, "Executive::Directory::create(): checking that entry does not already exist"));
	if(E_SUCCESS == Executive_Directory_resolve(&(self->Container), name, &dentry))
	{
		IDirectoryEntry_release(dentry);
		EXLOGF((LOG_CONDITION, "%%E-EXISTS: an object named '%s' already exists within this container", name));
		return E_EXISTS;
	}
	EXDBGF((LOG_DEBUG7, "Executive::Directory::create(): attempting to obtain a suitable metaclass interface for clsid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid)));
	if(E_SUCCESS == Executive_metaClass(clsid, &IID_MDirectoryEntryTarget, (void **) &dtmeta))
	{
		EXDBGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>create(): obtained MDirectoryEntryTarget metaclass interface"));
		/* first create the directory entry */
		if(NULL == (entry = Executive_Directory_Entry_create(name, clsid, DEF_NONE)))
		{
			MDirectoryEntryTarget_release(dtmeta);
			return E_NOMEM;
		}
		EXDBGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>create(): entry created"));
		/* next call the createInstance method on the metaclass interface */
		if(E_SUCCESS != (status = MDirectoryEntryTarget_createInstance(dtmeta, &(entry->DirectoryEntry), &target)))
		{
			EXDBGF((LOG_DEBUG, "Executive::Directory::<IMutableContainer>create(): MDirectoryEntryTarget::createInstance() failed with status %d", status));
			MDirectoryEntryTarget_release(dtmeta);
			return status;
		}
		MDirectoryEntryTarget_release(dtmeta);
		/* add the entry to our list */
		Executive_Directory_addEntry(self, entry);
		Executive_Directory_Entry_populateObject(entry, (IObject *) (void *) target, target);
		/* tell the target it's been linked */
		IDirectoryEntryTarget_linked(target, &(entry->DirectoryEntry));
		/* if the caller requested an interface on the target, hand over
		 * to QueryInterface to obtain it
		 */
		if(iid)
		{
			EXDBGF((LOG_DEBUG7, "Executive::Directory::<IMutableContainer>create(): handing off control to IDirectoryEntryTarget::queryInterface()"));
			return IDirectoryEntryTarget_queryInterface(target, iid, out);
		}
		return E_SUCCESS;
	}
	/* XXX we should support MFactory */
	EXLOGF((LOG_CONDITION, "%%E-PERM: Executive::Directory::<IMutableContainer>create(): no supported metaclass interfaces available for clsid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid)));
	return E_PERM;
}

STATUS
Executive_Directory_add(IMutableContainer *me, const char *name, REFUUID clsid, IObject *target)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *entry;
	IDirectoryEntry *dentry;

	UNUSED__(self);

	EXTRACEF(("Executive::Directory::<IMutableContainer>add('%s', clsid:" UUID_PRINTF_FORMAT ")", name, clsid));
	EXDBGF((LOG_DEBUG7, "checking that entry does not already exist"));
	if(E_SUCCESS == Executive_Directory_resolve(&(self->Container), name, &dentry))
	{
		IDirectoryEntry_release(dentry);
		EXLOGF((LOG_CONDITION, "%%E-EXISTS: an object named '%s' already exists within this container", name));
		return E_EXISTS;
	}
	if(NULL == (entry = Executive_Directory_Entry_create(name, clsid, DEF_NONE)))
	{
		return E_NOMEM;
	}
	EXDBGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>add(): entry created"));
	IObject_retain(target);
	Executive_Directory_addEntry(self, entry);
	Executive_Directory_Entry_populateObject(entry, target, NULL);
	if(entry->data.delegate)
	{
		IDirectoryEntryTarget_linked(entry->data.delegate, &(entry->DirectoryEntry));
	}
	return E_SUCCESS;
}

STATUS Executive_Directory_createLink(IMutableContainer *me, const char *name, const char *target, bool force)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *entry;
	IDirectoryEntry *dentry;
	Executive_Directory_Link *link;

	EXDBGF((LOG_DEBUG7, "checking that entry does not already exist"));
	if(E_SUCCESS == Executive_Directory_resolve(&(self->Container), name, &dentry))
	{
		IDirectoryEntry_release(dentry);
		EXLOGF((LOG_CONDITION, "%%E-EXISTS: an object named '%s' already exists within this container", name));
		return E_EXISTS;
	}
	if(NULL == (entry = Executive_Directory_Entry_create(name, &CLSID_Executive_Link, DEF_LINK)))
	{
		return E_NOMEM;
	}
	EXDBGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>add(): entry created"));
	link = Executive_Directory_Link_create(target);
	Executive_Directory_addEntry(self, entry);
	Executive_Directory_Entry_populateObject(entry, (void *)(IObject *) link, NULL);
		if(entry->data.delegate)
	{
		IDirectoryEntryTarget_linked(entry->data.delegate, &(entry->DirectoryEntry));
	}

	UNUSED__(target);
	UNUSED__(force);

	return E_SUCCESS;
}


static void
Executive_Directory_Entry_populateObject(Executive_Directory_Entry *self, IObject *object, IDirectoryEntryTarget *delegate)
{
	/* we assume we are already retaining the object */
	self->data.object = object;
	/* First, determine what kind of an object it is */
	if(E_SUCCESS == IObject_queryInterface(object, &IID_ILink, (void **) &(self->data.link)))
	{
		EXDBGF((LOG_DEBUG6, "target object supports ILink; setting DEF_LINK"));
		self->data.flags |= DEF_LINK;
	}
	else if(E_SUCCESS == IObject_queryInterface(object, &IID_IContainer, (void **) &(self->data.container)))
	{
		EXDBGF((LOG_DEBUG6, "target object supports IContainer; setting DEF_CONTAINER"));
		self->data.flags |= DEF_CONTAINER;
	}
	if(delegate)
	{
		IDirectoryEntryTarget_retain(delegate);
		self->data.delegate = delegate;
	}
	else
	{
		EXDBGF((LOG_DEBUG, "checking if target supports the delegate interface"));
		if(E_SUCCESS == IObject_queryInterface(object, &IID_IDirectoryEntryTarget, (void **) &(self->data.delegate)))
		{
			EXDBGF((LOG_DEBUG, "target object supports IDirectoryEntryTarget"));
		}
		else
		{
			EXDBGF((LOG_DEBUG, "target object does NOT support IDirectoryEntryTarget, it will not receive notifications"));
		}
	}
}

/* add a new entry to our list, making it visible */
static void
Executive_Directory_addEntry(Executive_Directory *self, Executive_Directory_Entry *entry)
{
	/* add the entry to our list */
	if(self->data.first)
	{
		self->data.last->data.next = entry;
	}
	else
	{
		self->data.first = entry;
	}
	self->data.last = entry;
}