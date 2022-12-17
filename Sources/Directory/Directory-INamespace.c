#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<INamespace> **/

/* INamespace */
const struct INamespace_vtable_ Executive_Directory_INamespace_vtable = {
	(STATUS (*)(INamespace *, REFUUID, void **))(void *) &Executive_Directory_queryInterface,
	(REFCOUNT (*)(INamespace *))(void *) &Executive_Directory_retain,
	(REFCOUNT (*)(INamespace *))(void *) &Executive_Directory_release,
	(STATUS (*)(INamespace *, const char *, IDirectoryEntry **))(void *) &Executive_Directory_resolve,
	(IIterator *(*)(INamespace *))(void *) &Executive_Directory_iterator,
	Executive_Directory_resolveEntry,
	Executive_Directory_resolveContainer,
	Executive_Directory_open,
	Executive_Directory_INamespace_create,
	Executive_Directory_INamespace_add,
	Executive_Directory_INamespace_createLink,
	Executive_Directory_INamespace_setFlags
};

STATUS
Executive_Directory_resolveEntry(INamespace *me, const char *path, IContainer *scope, IDirectoryEntry **dentry)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	STATUS status;
	IContainer *parent;
	const char *basename;

	UNUSED__(self);

	ExAssert(NULL != dentry);
	ExAssert(NULL != path);
	parent = NULL;
	basename = NULL;
	EXLOGF((LOG_TRACE, "Executive::Directory<INamespace>::resolveEntry('%s')", path));

	/* resolve all but the final path component to a container */
	if(E_SUCCESS != (status = Executive_Directory_resolveContainer(me, path, scope, &parent, &basename)))
	{
		EXLOGF((LOG_DEBUG, "Executive::Directory<INamespace>::resolveEntry(): resolveContainer() failed - %d", status));
		return status;
	}
	/* resolve the remainder within that container */
	EXLOGF((LOG_DEBUG, "Executive::Directory<INamespace>::resolveEntry(): resolving '%s' within parent %p", basename, parent));
	ExAssert(NULL != parent);
	status = IContainer_resolve(parent, basename, dentry);
	IContainer_release(parent);
	return status;
}

/* INamespace::resolveContainer() implements the core path traversal logic
 *
 * its purpose is to return to the caller the container the object at a given
 * path (which may not exist yet), and which may be absolute, or relative to
 * a particular scope
 *
 * any links encountered along the way are followed, up to a maximum limit
 */
STATUS
Executive_Directory_resolveContainer(INamespace *me, const char *path, IContainer *scope, IContainer **container, const char **basename)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	STATUS status;
	size_t linkCount;
	char *buffer, *head, *tail;
	int save;
	IDirectoryEntry *dentry, *linkEntry;
	ILink *link;
	DirectoryEntryFlags flags;
	IContainer *childContainer;

	ExAssert(NULL != container);
	ExAssert(NULL != path);

	EXLOGF((LOG_TRACE, "Executive::Directory<INamespace>::resolveContainer('%s')", path));

	*container = NULL;
	if(basename)
	{
		*basename = NULL;
	}
	dentry = NULL;
	link = NULL;
	linkEntry = NULL;
	linkCount = 0;
	status = E_SUCCESS;
	/* the supplied path is duplicated into a buffer */
	buffer = ExStrDup(path);
	if(NULL == buffer)
	{
		return E_NOMEM;
	}
	/* ensure we have a starting scope */
	if(!scope || buffer[0] == '/')
	{
		scope = &(self->Container);
	}
	head = tail = buffer;
	IContainer_retain(scope);
	while(scope && head[0])
	{
		/* skip any extraneous slashes */
		for(; head[0] == '/'; head++);
		/* if there are no characters remaining, stop processing */
		if(!head[0])
		{
			break;
		}
		/* start at head and continue until a slash or the end of the string
		 * is reached, storing the position in tail, thus head .. tail consists
		 * of a single path component with trailing slash
		 */
		for(tail = head; tail[0] && tail[0] != '/'; tail++);
		/* if there is no trailing slash, perform no further processing - the
		 * purpose of this function is to locate the container of the named
		 * path
		 */
		if(!tail[0])
		{
			break;
		}
		/* save the path separator and terminate the string at tail */
		save = tail[0];
		tail[0] = 0;

		EXLOGF((LOG_DEBUG7, "*** will attempt to resolve path component '%s' to a container", head));

		/* attempt to resolve the path component within the current scope */
		if(E_SUCCESS != (status = IContainer_resolve(scope, head, &dentry))) break;
		flags = IDirectoryEntry_flags(dentry);
		/* attempt to resolve any link chains */
		for(; linkCount < 16 && flags & DEF_LINK; linkCount++)
		{
			/* attempt to read the link */
			status = IDirectoryEntry_queryTargetInterface(dentry, &IID_ILink, (void **) &link);
			if(status != E_SUCCESS)
			{
				/* cannot traverse if it doesn't support ILink */
				EXLOGF((LOG_CONDITION, "%%E-NOT-CONTAINER: Executive::Directory::ResolveContainer(): '%s' does not support ILink", buffer));
				break;
			}
			EXLOGF((LOG_DEBUG7, "attempting to resolve '%s'", ILink_target(link)));
			status = Executive_Directory_resolveEntry(me, ILink_target(link), scope, &linkEntry);
			ILink_release(link);
			if(E_SUCCESS != status)
			{
				EXLOGF((LOG_DEBUG, "resolveEntry() failed %d", status));
				break;
			}
			EXLOGF((LOG_DEBUG7, "have resolved link to a new entry"));
			/* replace the entry and fetch the flags again */
			IDirectoryEntry_release(dentry);
			dentry = linkEntry;
			flags = IDirectoryEntry_flags(dentry);
		}
		/* if flags still assert DEF_LINK, we didn't process all of the links
		 * in the chain
		 */
		if(flags & DEF_LINK)
		{
			EXLOGF((LOG_CONDITION, "%%E-???: %s: too many levels of links (stopped at %d)", linkCount));
			status = E_NOT_CONTAINER;
			break;
		}
		if(E_SUCCESS != status)
		{
			EXLOGF((LOG_DEBUG, "link traversal failed"));
			break;
		}
		if(!(flags & DEF_CONTAINER))
		{
			/* this object must be either a container or a link to a container */
			EXLOGF((LOG_CONDITION, "%%E-NOT-CONTAINER: Executive::Directory::ResolveContainer(): '%s' is not a containerr", buffer));
			status = E_NOT_CONTAINER;
			break;
		}	
		/* attempt to open the entry's target as a container */
		status = IDirectoryEntry_queryTargetInterface(dentry, &IID_IContainer, (void **) &childContainer);
		IDirectoryEntry_release(dentry);
		dentry = NULL;
		if(status != E_SUCCESS)
		{
			EXLOGF((LOG_CONDITION, "%%E-NOT-CONTAINER: Executive::Directory::ResolveContainer(): '%s' does not support IContainer", buffer));
			break;
		}
		ExAssert(NULL != childContainer);
		/* the scope is now the container interface we just obtained */
		IContainer_release(scope);
		scope = childContainer;
		childContainer = NULL;
		/* continue processing the path at the path separator */
		head = tail;
		head[0] = save;
	}
	if(E_SUCCESS == status)
	{
		EXLOGF((LOG_DEBUG7, "%s: successfully resolved to container", buffer));
		if(basename)
		{
			/* skip any leftover slashes */
			for(; head[0] == '/'; head++);
			*basename = path + (head - buffer);
			EXLOGF((LOG_DEBUG7, "buffer = '%s', basename = '%s'", buffer, *basename));
		}
		*container = scope;
	}
	else
	{
		EXLOGF((LOG_DEBUG, "%s: failed to resolve to container %d", buffer, status));
		IContainer_release(scope);
	}
	if(dentry)
	{
		IDirectoryEntry_release(dentry);
	}
	ExFree(buffer);
	return status;
}

/* resolve the given path to a directory entry, then attempt to obtain the
 * specified interface on the target object
 */
STATUS
Executive_Directory_open(INamespace *me, const char *path, IContainer *scope, REFUUID iid, void **out)
{
	STATUS status;
	IDirectoryEntry *dentry;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = Executive_Directory_resolveEntry(me, path, scope, &dentry)))
	{
		return status;
	}
	if(iid)
	{
		status = IDirectoryEntry_queryTargetInterface(dentry, iid, out);
	}
	IDirectoryEntry_release(dentry);
	return status;
}

const char *
Executive_Directory_basename(const char *path)
{
	const char *head, *tail;

	head = path;
	do
	{
		for(; head[0] == '/'; head++);
		if(!head[0])
		{
			break;
		}
		for(tail = head; tail[0] && tail[0] != '/'; tail++);
		if(!tail[0])
		{
			return head;
		}
		head = tail;
	}
	while(head[0]);
	return path;
}

/* resolve the given path to a directory entry, then attempt to obtain
 * the IMutableContainer interface on the target object; if that succeeds,
 * then invoke IMutableComntainer::create() to create a new object with
 * the provided name
 */
STATUS
Executive_Directory_INamespace_create(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, REFUUID iid, void **out)
{
	STATUS status;
	IContainer *container;
	IMutableContainer *mutable;
	const char *basename;

	if(out)
	{
		*out = NULL;
	}
	if(E_SUCCESS != (status = Executive_Directory_resolveContainer(me, path, scope, &container, &basename)))
	{
		return status;
	}
	EXLOGF((LOG_DEBUG7, "located parent entry for '%s'", path));
	EXLOGF((LOG_DEBUG7, "basename is '%s'", basename));
	if(E_SUCCESS != (status = IContainer_queryInterface(container, &IID_IMutableContainer, (void **) &mutable)))
	{
		EXLOGF((LOG_DEBUG, "IDirectoryEntry::queryTargetInterface() failed %d", status));
		IContainer_release(container);
		return status;
	}
	IContainer_release(container);
	if(E_SUCCESS != (status = IMutableContainer_create(mutable, basename, clsid, iid, out)))
	{
		EXLOGF((LOG_DEBUG, "IMutableContainer::create() failed %d", status));
		IMutableContainer_release(mutable);
		return status;
	}
	IMutableContainer_release(mutable);
	EXLOGF((LOG_DEBUG3, "new object created successfully"));
	return status;
}

STATUS
Executive_Directory_INamespace_add(INamespace *me, const char *path, IContainer *scope, REFUUID clsid, IObject *target)
{
	STATUS status;
	IContainer *container;
	IMutableContainer *mutable;
	const char *basename;

	ExAssert(clsid != NULL);
	ExAssert(target != NULL);
	if(E_SUCCESS != (status = Executive_Directory_resolveContainer(me, path, scope, &container, &basename)))
	{
		return status;
	}
	EXLOGF((LOG_DEBUG7, "located parent entry for '%s'", path));
	EXLOGF((LOG_DEBUG7, "basename is '%s'", basename));
	if(E_SUCCESS != (status = IContainer_queryInterface(container, &IID_IMutableContainer, (void **) &mutable)))
	{
		EXLOGF((LOG_DEBUG, "IDirectoryEntry::queryTargetInterface() failed %d", status));
		IContainer_release(container);
		return status;
	}
	IContainer_release(container);
	if(E_SUCCESS != (status = IMutableContainer_add(mutable, basename, clsid, target)))
	{
		EXLOGF((LOG_DEBUG, "IMutableContainer::add() failed %d", status));
		IMutableContainer_release(mutable);
		return status;
	}
	IMutableContainer_release(mutable);
	EXLOGF((LOG_DEBUG2, "new object created successfully"));
	return status;
}

STATUS
Executive_Directory_INamespace_createLink(INamespace *me, const char *path, IContainer *scope, const char *target, bool force)
{
	STATUS status;
	IContainer *container;
	IMutableContainer *mutable;
	const char *basename;

	ExAssert(target != NULL);
	if(E_SUCCESS != (status = Executive_Directory_resolveContainer(me, path, scope, &container, &basename)))
	{
		return status;
	}
	EXLOGF((LOG_DEBUG7, "located parent entry for '%s'", path));
	EXLOGF((LOG_DEBUG7, "basename is '%s'", basename));
	if(E_SUCCESS != (status = IContainer_queryInterface(container, &IID_IMutableContainer, (void **) &mutable)))
	{
		EXLOGF((LOG_DEBUG, "IDirectoryEntry::queryTargetInterface() failed %d", status));
		IContainer_release(container);
		return status;
	}
	IContainer_release(container);
	if(E_SUCCESS != (status = IMutableContainer_createLink(mutable, basename, target, force)))
	{
		EXLOGF((LOG_DEBUG, "IMutableContainer::createLink() failed %d", status));
		IMutableContainer_release(mutable);
		return status;
	}
	IMutableContainer_release(mutable);
	EXLOGF((LOG_DEBUG2, "new link created successfully"));
	return status;
}


STATUS
Executive_Directory_INamespace_setFlags(INamespace *me, const char *path, IContainer *scope, DirectoryEntryFlags flags)
{
	STATUS status;
	IDirectoryEntry *dentry;

	if(E_SUCCESS != (status = Executive_Directory_resolveEntry(me, path, scope, &dentry)))
	{
		return status;
	}
	status = IDirectoryEntry_setFlags(dentry, flags);
	IDirectoryEntry_release(dentry);
	if(status != E_SUCCESS)
	{
		EXLOGF((LOG_CONDITION, "%%E-%d: IDirectoryEntry::setFlags() failed for '%s'", status, path));
	}
	return status;
}
