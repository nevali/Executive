#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory *)((i)->instptr)

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
	Executive_Directory_INamespace_setFlags
};

STATUS
Executive_Directory_resolveEntry(INamespace *me, const char *path, IContainer *scope, IDirectoryEntry **dentry)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	STATUS status;
	const char *head, *tail;
	char objname[32];
	IDirectoryEntry *cur;
	IContainer *dscope;

	ExAssert(NULL != dentry);
	ExAssert(NULL != path);

	*dentry = NULL;
	dscope = NULL;
	cur = NULL;	
	if(!scope || path[0] == '/')
	{
		scope = &(self->Container);
	}
	head = path;
	do
	{
		for(; head[0] == '/'; head++);
		if(!head[0])
		{
			break;
		}
		for(tail = head; tail[0] && tail[0] != '/'; tail++);
		if((size_t) (tail - head) >= sizeof(objname))
		{
			EXLOGF((LOG_CONDITION, "path component too long in INamespace::resolvePath()"));
			if(dscope)
			{
				IContainer_release(dscope);
			}		
			return E_NOENT;
		}
		/* copy the path from head .. tail to our buffer, null-terminating it */
		ExStrLCopy(objname, sizeof(objname), head, tail - head);
		/* attempt to resolve the path component within the current scope */
		status = IContainer_resolve(scope, objname, &cur);
		if(dscope)
		{
			/* if the current scope was retained by us, release it */
			IContainer_release(dscope);
		}
		if(status != E_SUCCESS)
		{
			/* if the path component could not be resolved, return failure */
			return status;
		}
		/* was this the last path component? */
		if(!tail[0])
		{
			/* no more path components - resolved successfully */
			*dentry = cur;
			return E_SUCCESS;
		}
		/* attempt to open the entry's target as a container */
		status = IDirectoryEntry_queryTargetInterface(cur, &IID_IContainer, (void **) &dscope);
		if(status != E_SUCCESS)
		{
			/* cannot traverse if it doesn't support IContainer */
			EXLOGF((LOG_DEBUG, "object %s is not a container", objname));
			return E_NOENT;
		}
		/* the scope is now the container interface we just obtained */
		scope = dscope;
		/* continue processing the path at the slash character */
		head = tail;
	}
	while(scope && head[0]);
	/* if we reached this point, there were trailing slashes, or
	 * an empty path was provided; if cur is non-NULL, it means
	 * we successfully resolved the path up until this point, and
	 * were simply expecting another path component to resolve
	 */
	/* if the scope was retained by us, release it*/
	if(dscope)
	{
		IContainer_release(dscope);
	}
	if(cur)
	{
		*dentry = cur;
		return E_SUCCESS;
	}
	EXLOGF((LOG_CONDITION, "%%E-NOENT: empty path provided to INamespace::resolvePath()"));
	return E_NOENT;
}

STATUS
Executive_Directory_resolveContainer(INamespace *me, const char *path, IContainer *scope, IContainer **container, const char **basename)
{
	Executive_Directory *self = INTF_TO_CLASS(me);
	STATUS status;
	const char *head, *tail;
	char objname[32];
	IDirectoryEntry *cur;
	IContainer *dscope;

	ExAssert(NULL != container);
	ExAssert(NULL != path);

	*container = NULL;
	dscope = NULL;
	cur = NULL;	
	if(!scope || path[0] == '/')
	{
		scope = &(self->Container);
	}
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
			break;
		}
		if((size_t) (tail - head) >= sizeof(objname))
		{
			EXLOGF((LOG_CONDITION, "path component too long in INamespace::resolveContainer()"));
			if(dscope)
			{
				IContainer_release(dscope);
			}		
			return E_NOENT;
		}
		/* copy the path from head .. tail to our buffer, null-terminating it */
		ExStrLCopy(objname, sizeof(objname), head, tail - head);
		/* attempt to resolve the path component within the current scope */
		status = IContainer_resolve(scope, objname, &cur);
		if(dscope)
		{
			/* if the current scope was retained by us, release it */
			IContainer_release(dscope);
		}
		if(status != E_SUCCESS)
		{
			/* if the path component could not be resolved, return failure */
			return status;
		}
		/* attempt to open the entry's target as a container */
		status = IDirectoryEntry_queryTargetInterface(cur, &IID_IContainer, (void **) &dscope);
		if(status != E_SUCCESS)
		{
			/* cannot traverse if it doesn't support IContainer */
			EXLOGF((LOG_DEBUG, "object %s is not a container", objname));
			return E_NOENT;
		}
		/* the scope is now the container interface we just obtained */
		scope = dscope;
		/* continue processing the path at the slash character */
		head = tail;
	}
	while(scope && head[0]);
	if(basename)
	{
		*basename = head;
	}
	*container = scope;
	if(!dscope)
	{
		/* we're returning a reference to ourselves */
		self->data.refCount++;
	}
	return E_SUCCESS;
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
	EXLOGF((LOG_DEBUG, "located parent entry for '%s'", path));
	EXLOGF((LOG_DEBUG, "basename is '%s'", basename));
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
	EXLOGF((LOG_DEBUG, "new object created successfully"));
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
	EXLOGF((LOG_DEBUG, "located parent entry for '%s'", path));
	EXLOGF((LOG_DEBUG, "basename is '%s'", basename));
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
	EXLOGF((LOG_DEBUG, "new object created successfully"));
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
