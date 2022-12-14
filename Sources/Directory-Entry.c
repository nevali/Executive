#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory_Entry *)((i)->instptr)

/** Executive::Directory::Entry **/

/* IObject */
static STATUS Executive_Directory_Entry_queryInterface(IDirectoryEntry *me, REFUUID iid, void **out);
static REFCOUNT Executive_Directory_Entry_retain(IDirectoryEntry *me);
static REFCOUNT Executive_Directory_Entry_release(IDirectoryEntry *me);
/* IDirectoryEntry */
static STATUS Executive_Directory_Entry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out);
static const char *Executive_Directory_Entry_name(IDirectoryEntry *me);
static void Executive_Directory_Entry_classid(IDirectoryEntry *me, UUID *clsid);
static DirectoryEntryFlags Executive_Directory_Entry_flags(IDirectoryEntry *me);
static STATUS Executive_Directory_Entry_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags);

static struct IDirectoryEntry_vtable_ Executive_Directory_Entry_vtable = {
    Executive_Directory_Entry_queryInterface,
    Executive_Directory_Entry_retain,
    Executive_Directory_Entry_release,
    Executive_Directory_Entry_queryTargetInterface,
    Executive_Directory_Entry_name,
    Executive_Directory_Entry_classid,
    Executive_Directory_Entry_flags,
    Executive_Directory_Entry_setFlags
};

/** Executive::Directory::Entry **/

Executive_Directory_Entry *
Executive_Directory_Entry_create(const char *name, REFUUID clsid, DirectoryEntryFlags flags)
{
    Executive_Directory_Entry *p;
#ifndef NDEBUG
    UUIDBUF cbuf;
    ExUuidStr(clsid, cbuf);
#endif

    ExAssert(NULL != name);
    ExAssert(NULL != clsid);

    EXLOGF((LOG_TRACE, "Executive::Directory::Entry::create('%s', clsid:%s)", name, cbuf));

    if(NULL == (p = ExAlloc(sizeof(Executive_Directory_Entry))))
    {
        EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Directory_Entry)));
        return NULL;
    }
    p->DirectoryEntry.lpVtbl = &Executive_Directory_Entry_vtable;
    p->DirectoryEntry.instptr = p;
    p->Object.lpVtbl = (void *) &Executive_Directory_Entry_vtable;
    p->Object.instptr = p;
    p->data.refCount = 1;
    p->data.flags = flags;
    p->data.name = ExStrDup(name);
    ExUuidCopy(&(p->data.clsid), clsid);
    return p;
}

static STATUS
Executive_Directory_Entry_queryInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    EXEC_COMMON_SUPPORTS(DirectoryEntry);
    EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_Directory_Entry_retain(IDirectoryEntry *me)
{
    EXEC_COMMON_RETAIN(Executive_Directory_Entry);
}

static REFCOUNT
Executive_Directory_Entry_release(IDirectoryEntry *me)
{
    EXEC_COMMON_RELEASE(Executive_Directory_Entry, {
        if(self->data.target)
        {
            IDirectoryEntryTarget_release(self->data.target);
        }
        if(self->data.object)
        {
            IObject_release(self->data.object);
        }
        ExFree(self->data.name);
    });
}
static STATUS
Executive_Directory_Entry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    if(self->data.target)
    {
        return IDirectoryEntryTarget_queryInterface(self->data.target, iid, out);
    }
    if(self->data.object)
    {
        return IObject_queryInterface(self->data.object, iid, out);
    }
    return E_NOTIMPL;   
}

static const char *
Executive_Directory_Entry_name(IDirectoryEntry *me)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    return self->data.name;
}

static void
Executive_Directory_Entry_classid(IDirectoryEntry *me, UUID *clsid)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    ExUuidCopy(clsid, &(self->data.clsid));
}

static DirectoryEntryFlags
Executive_Directory_Entry_flags(IDirectoryEntry *me)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);
    
    return self->data.flags;
}

static STATUS
Executive_Directory_Entry_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    if(self->data.flags & DEF_IMMUTABLE)
    {
        EXLOGF((LOG_CONDITION, "%%E-PERM: set flags: operation not permitted (directory entry is marked immutable); flags = %d, new flags = %d", self->data.flags, flags));
        return E_PERM;
    }
    self->data.flags = flags;
    return E_SUCCESS;
}
