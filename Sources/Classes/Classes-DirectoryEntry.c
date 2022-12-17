#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Classes.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Classes_DirectoryEntry)

/** Executive::Classes::DirectoryEntry **/

/* IObject */
EXEC_COMMON_STATIC_IOBJECT(Executive_Classes_DirectoryEntry);
/* IDirectoryEntry */
static STATUS Executive_Classes_DirectoryEntry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out);
static const char *Executive_Classes_DirectoryEntry_name(IDirectoryEntry *me);
static void Executive_Classes_DirectoryEntry_classid(IDirectoryEntry *me, UUID *clsid);
static DirectoryEntryFlags Executive_Classes_DirectoryEntry_flags(IDirectoryEntry *me);
static STATUS Executive_Classes_DirectoryEntry_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags);
/* IContainer */
static STATUS Executive_Classes_DirectoryEntry_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_Classes_DirectoryEntry_iterator(IContainer *me);
/* ILink */
static const char *Executive_Classes_DirectoryEntry_target(ILink *me);

static struct IDirectoryEntry_vtable_ Executive_Classes_DirectoryEntry_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Classes_DirectoryEntry, IDirectoryEntry),
    Executive_Classes_DirectoryEntry_queryTargetInterface,
    Executive_Classes_DirectoryEntry_name,
    Executive_Classes_DirectoryEntry_classid,
    Executive_Classes_DirectoryEntry_flags,
    Executive_Classes_DirectoryEntry_setFlags
};

static struct IContainer_vtable_ Executive_Classes_DirectoryEntry_IContainer_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Classes_DirectoryEntry, IContainer),
    Executive_Classes_DirectoryEntry_resolve,
    Executive_Classes_DirectoryEntry_iterator
};

static struct ILink_vtable_ Executive_Classes_DirectoryEntry_ILink_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Classes_DirectoryEntry, ILink),
    Executive_Classes_DirectoryEntry_target
};

/** Executive::Directory::Entry **/

Executive_Classes_DirectoryEntry *
Executive_Classes_DirectoryEntry_create(const char *name, REFUUID clsid, DirectoryEntryFlags flags)
{
    Executive_Classes_DirectoryEntry *p;

    ExAssert(NULL != name);
    ExAssert(NULL != clsid);

    EXTRACEF(("Executive::Directory::Entry::create('%s', clsid:" UUID_PRINTF_FORMAT ")", name, UUID_PRINTF_ARGS(clsid)));

    if(NULL == (p = ExAlloc(sizeof(Executive_Classes_DirectoryEntry))))
    {
        EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Classes_DirectoryEntry)));
        return NULL;
    }
    p->DirectoryEntry.lpVtbl = &Executive_Classes_DirectoryEntry_vtable;
    p->DirectoryEntry.instptr = p;
    p->Object.lpVtbl = (void *) &Executive_Classes_DirectoryEntry_vtable;
    p->Object.instptr = p;
    p->Container.lpVtbl = &Executive_Classes_DirectoryEntry_IContainer_vtable;
    p->Container.instptr = p;
    p->Link.lpVtbl = &Executive_Classes_DirectoryEntry_ILink_vtable;
    p->Link.instptr = p;
    p->data.refCount = 1;
    p->data.flags = flags;
    p->data.name = ExStrDup(name);
    ExUuidCopy(&(p->data.clsid), clsid);
    return p;
}

/* IObject */

static STATUS
Executive_Classes_DirectoryEntry_queryInterface(IObject *me, REFUUID iid, void **out)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

    EXTRACEF(("Executive::Directory::Entry::queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(iid)));
    EXEC_COMMON_SUPPORTS(DirectoryEntry);
    if(self->data.flags & DEF_CONTAINER)
    {
        EXEC_COMMON_SUPPORTS(Container);
    }
    if(self->data.flags & DEF_LINK)
    {
        EXEC_COMMON_SUPPORTS(Link);
    }
    EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_Classes_DirectoryEntry_retain(IObject *me)
{
    EXEC_COMMON_RETAIN(Executive_Classes_DirectoryEntry);
}

static REFCOUNT
Executive_Classes_DirectoryEntry_release(IObject *me)
{
    EXEC_COMMON_RELEASE(Executive_Classes_DirectoryEntry, {
        ExFree(self->data.name);
        ExFree(self->data.target);
    });
}

/* IDirectoryEntry */

static STATUS
Executive_Classes_DirectoryEntry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

	UNUSED__(iid);

	EXTRACEF(("Executive::Classes::DirectoryEntry::queryTargetInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(iid)));
	if(out)
	{
		*out = NULL;
	}
    /* If a callback was provided, use it */
    if(self->data.queryTargetInterface)
    {
        return self->data.queryTargetInterface(self, iid, out);
    }
    /* We can pose as a container or a link */
    if(self->data.flags & (DEF_CONTAINER|DEF_LINK))
    {
		return IDirectoryEntry_queryInterface(me, iid, out);
    }
    return E_NOTIMPL;
}

static const char *
Executive_Classes_DirectoryEntry_name(IDirectoryEntry *me)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

    return self->data.name;
}

static void
Executive_Classes_DirectoryEntry_classid(IDirectoryEntry *me, UUID *clsid)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

    ExUuidCopy(clsid, &(self->data.clsid));
}

static DirectoryEntryFlags
Executive_Classes_DirectoryEntry_flags(IDirectoryEntry *me)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);
    
    return self->data.flags | DEF_SYSTEM | DEF_IMMUTABLE;
}

static STATUS
Executive_Classes_DirectoryEntry_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags)
{
	UNUSED__(me);
	UNUSED__(flags);

    return E_PERM;
}

STATUS
Executive_Classes_DirectoryEntry_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	UNUSED__(me);

	if(entry)
	{
		*entry = NULL;
	}
	UNUSED__(name);
	UNUSED__(entry);
	return E_NOTIMPL;
}

/* This is invoked to obtain an iterator for the set of classes within a
 * prefix
 */
IIterator *
Executive_Classes_DirectoryEntry_iterator(IContainer *me)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

    if(self->data.iterator)
    {
        return self->data.iterator(self);
    }
    return NULL;
}

/* ILink */

const char *
Executive_Classes_DirectoryEntry_target(ILink *me)
{
    Executive_Classes_DirectoryEntry *self = INTF_TO_CLASS(me);

    if(!(self->data.flags & DEF_LINK))
    {
        return NULL;
    }
    return self->data.target;
}
