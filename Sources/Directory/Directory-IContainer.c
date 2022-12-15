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

	EXLOGF((LOG_TRACE, "Executive::Directory::<IContainer>resolve('%s')", name));
	for(iterator = self->data.first; iterator; iterator = iterator->data.next)
	{
		if(ExStrEqual(iterator->data.name, name))
		{
			EXLOGF((LOG_DEBUG7, "Executive::Directory::resolve(): entry located"));
			IDirectoryEntry_retain((&(iterator->DirectoryEntry)));
			*entry = &(iterator->DirectoryEntry);
			return E_SUCCESS;
		}
	}
	EXLOGF((LOG_CONDITION, "%%E-NOENT: object '%s' could not be found", name));
	return E_NOENT;
}

IIterator *
Executive_Directory_iterator(IContainer *me)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	return (IIterator *)(void *) Executive_Directory_Iterator_create(self->data.first);
}


static void
dumpDir(IContainer *self, const char *name, int depth)
{
	size_t c;
	char space[80], flagsbuf[16];
	UUID clsid;
	UUIDBUF cbuf;
	const char *cname;
	DirectoryEntryFlags flags;
	IIterator *iterator;
	IDirectoryEntry *dirent;
	IContainer *container;
	ILink *link;

	UNUSED__(name);
	
	for(c = 0; c < sizeof(space)-1 && c < (size_t) depth; c++)
	{
		space[c] = '-';
	}
	space[c] = 0;
	if(c > 1)
	{
		space[c - 1] = ' ';
	}
	iterator = IContainer_iterator(self);
	if(!iterator)
	{
		EXLOGF((LOG_DEBUG7, "dumpDir(): WARNING: container '%s' does not provide an iterator", name));
		return;
	}
	while(NULL != (dirent = (IDirectoryEntry *) (void *) IIterator_current(iterator)))
	{
		/* XXX we should QI */		
		IDirectoryEntry_classid(dirent, &clsid);
		ExUuidStr(&clsid, cbuf);
		cname = Executive_nameOfClass(&clsid);
		if(!cname)
		{
			cname = cbuf;
		}
		flags = IDirectoryEntry_flags(dirent);
		flagsbuf[0] = (flags & DEF_IMMUTABLE ? '!' : '-');
		flagsbuf[1] = (flags & DEF_SYSTEM ? 's' : '-');
		flagsbuf[2] = (flags & DEF_HIDDEN ? 'h' : '-');
		if(flags & DEF_VOID)
		{
			flagsbuf[3] = '?';
		}
		else if(flags & DEF_LINK)
		{
			flagsbuf[3] = '@';
		}
		else if(flags & DEF_MOUNTPOINT)
		{
			flagsbuf[3] = '#';
		}
		else if(flags & DEF_CONTAINER)
		{
			flagsbuf[3] = '+';
		}
		else
		{
			flagsbuf[3] = '-';
		}
		flagsbuf[4] = 0;
		if((flags & DEF_LINK) && E_SUCCESS == IDirectoryEntry_queryTargetInterface(dirent, &IID_ILink, (void **) &link))
		{
			EXLOGF((LOG_NOTICE, "%42s %s  %s%s -> %s", cname, flagsbuf, space, IDirectoryEntry_name(dirent), ILink_target(link)));
			ILink_release(link);
		}
		else
		{
			EXLOGF((LOG_NOTICE, "%42s %s  %s%s", cname, flagsbuf, space, IDirectoryEntry_name(dirent)));
		}
		if((flags & DEF_CONTAINER) && E_SUCCESS == IDirectoryEntry_queryTargetInterface(dirent, &IID_IContainer, (void **) &container))
		{
			dumpDir(container, IDirectoryEntry_name(dirent), depth + 2);
			IContainer_release(container);
		}
		IDirectoryEntry_release(dirent);
		if(E_SUCCESS != IIterator_next(iterator))
		{
			break;
		}
	}
	IIterator_release(iterator);
}

void
Executive_Directory_dump(IContainer *me)
{
	dumpDir(me, "/", 0);
}
