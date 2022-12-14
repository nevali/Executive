#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory *)((i)->instptr)

/** Executive::Directory<IMutableContainer> **/

const struct IMutableContainer_vtable_ Executive_Directory_IMutableContainer_vtable = {
	(STATUS (*)(IMutableContainer *, REFUUID, void **))(void *) &Executive_Directory_queryInterface,
	(REFCOUNT (*)(IMutableContainer *))(void *) &Executive_Directory_retain,
	(REFCOUNT (*)(IMutableContainer *))(void *) &Executive_Directory_release,
	(REFCOUNT (*)(IMutableContainer *, const char *, IDirectoryEntry **))(void *) &Executive_Directory_resolve,
	(IIterator *(*)(IMutableContainer *))(void *) &Executive_Directory_iterator,
	Executive_Directory_IMutableContainer_create,
	Executive_Directory_add
};

STATUS
Executive_Directory_IMutableContainer_create(IMutableContainer *me, const char *name, REFUUID clsid, REFUUID iid, void **out)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *entry;
	IDirectoryEntry *dentry;
	MDirectoryEntryTarget *dtmeta;
	IDirectoryEntryTarget *target;
	IContainer *container;
	STATUS status;
#ifndef NDEBUG
	UUIDBUF cbuf, ibuf;
#endif

#ifndef NDEBUG
	ExUuidStr(clsid, cbuf);
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::Directory::<IMutableContainer>create('%s', clsid:%s, iid:%s)", name, cbuf, ibuf));
#endif
	EXLOGF((LOG_DEBUG7, "Executive::Directory::create(): checking that entry does not already exist"));
	if(E_SUCCESS == Executive_Directory_resolve(&(self->Container), name, &dentry))
	{
		IDirectoryEntry_release(dentry);
		EXLOGF((LOG_CONDITION, "%%E-EXISTS: an object named '%s' already exists within this container", name));
		return E_EXISTS;
	}
	EXLOGF((LOG_DEBUG7, "Executive::Directory::create(): attempting to obtain a suitable metaclass interface for clsid:%s", cbuf));
	if(E_SUCCESS == Executive_metaClass(clsid, &IID_MDirectoryEntryTarget, (void **) &dtmeta))
	{
		EXLOGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>create(): obtained MDirectoryEntryTarget metaclass interface"));
		/* first create the directory entry */
		if(NULL == (entry = Executive_Directory_Entry_create(name, clsid, DEF_NONE)))
		{
			MDirectoryEntryTarget_release(dtmeta);
			return E_NOMEM;
		}
		EXLOGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>create(): entry created"));
		/* next call the createInstance method on the metaclass interface */
		if(E_SUCCESS != (status = MDirectoryEntryTarget_createInstance(dtmeta, &(entry->DirectoryEntry), &target)))
		{
			EXLOGF((LOG_DEBUG, "Executive::Directory::<IMutableContainer>create(): MDirectoryEntryTarget::createInstance() failed with status %d", status));
			MDirectoryEntryTarget_release(dtmeta);
			return status;
		}
		MDirectoryEntryTarget_release(dtmeta);
		/* the entry retains the target interface pointer */
		entry->data.target = target;
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
		if(E_SUCCESS == IObject_queryInterface(target, &IID_IContainer, (void **) &container))
		{
			EXLOGF((LOG_DEBUG6, "target object supports IContainer; setting DEF_CONTAINER"));
			entry->data.flags |= DEF_CONTAINER;
			IContainer_release(container);
		}
		/* tell the target it's been linked */
		IDirectoryEntryTarget_linked(target, &(entry->DirectoryEntry));
		/* if the caller requested an interface on the target, hand over
		 * to QueryInterface to obtain it
		 */
		if(iid)
		{
			EXLOGF((LOG_DEBUG7, "Executive::Directory::<IMutableContainer>create(): handing off control to IDirectoryEntryTarget::queryInterface()"));
			return IDirectoryEntryTarget_queryInterface(target, iid, out);
		}
		return E_SUCCESS;
	}
	/* XXX we should support MFactory */
#ifndef NDEBUG
	EXLOGF((LOG_CONDITION, "%%E-PERM: Executive::Directory::<IMutableContainer>create(): no supported metaclass interfaces available for clsid:%s", cbuf));
#endif
	return E_PERM;
}

STATUS
Executive_Directory_add(IMutableContainer *me, const char *name, REFUUID clsid, IObject *target)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	Executive_Directory_Entry *entry;
	IDirectoryEntry *dentry;
	IContainer *container;
#ifndef NDEBUG
	UUIDBUF cbuf;
#endif

	UNUSED__(self);

#ifndef NDEBUG
	ExUuidStr(clsid, cbuf);
	EXLOGF((LOG_DEBUG2, "Executive::Directory::<IMutableContainer>add('%s', clsid:%s)", name, cbuf));
#endif
	EXLOGF((LOG_DEBUG7, "checking that entry does not already exist"));
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
	EXLOGF((LOG_DEBUG6, "Executive::Directory::<IMutableContainer>add(): entry created"));
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
	if(E_SUCCESS == IObject_queryInterface(target, &IID_IContainer, (void **) &container))
	{
		EXLOGF((LOG_DEBUG6, "target object supports IContainer; setting DEF_CONTAINER"));
		entry->data.flags |= DEF_CONTAINER;
		IContainer_release(container);
	}
	if(E_SUCCESS == IObject_queryInterface(target, &IID_IDirectoryEntryTarget, (void **) &(entry->data.target)))
	{
		EXLOGF((LOG_DEBUG, "target object supports IDirectoryEntryTarget"));
		IDirectoryEntryTarget_linked(entry->data.target, &(entry->DirectoryEntry));
	}
	else
	{
		EXLOGF((LOG_DEBUG, "target object does NOT support IDirectoryEntryTarget, it will not receive notifications"));
		IObject_retain(target);
		entry->data.object = target;
	}
	return E_SUCCESS;
}
