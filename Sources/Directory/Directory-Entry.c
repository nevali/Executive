#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory_Entry *)((i)->instptr)

/** Executive::Directory::Entry **/

/* IObject */
static STATUS Executive_Directory_Entry_queryInterface(IDirectoryEntry *me, REFUUID iid, void **out);
static REFCOUNT Executive_Directory_Entry_retain(IDirectoryEntry *me);
static REFCOUNT Executive_Directory_Entry_release(IDirectoryEntry *me);
/* IDirectoryEntry */
static STATUS Executive_Directory_Entry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out);
static STATUS Executive_Directory_Entry_name(IDirectoryEntry *me, char *buf, size_t bufsize);
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

    ExAssert(NULL != name);
    ExAssert(NULL != clsid);

    EXTRACEF(("Executive::Directory::Entry::create('%s', clsid:" UUID_PRINTF_FORMAT ")", name, UUID_PRINTF_ARGS(clsid)));

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
    p->data.userFlags = 0;
    p->data.name = ExStrDup(name);
    ExUuidCopy(&(p->data.clsid), clsid);
    return p;
}

static STATUS
Executive_Directory_Entry_queryInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    EXTRACEF(("Executive::Directory::Entry::queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(iid)));
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
        if(self->data.delegate)
        {
            IDirectoryEntryTarget_release(self->data.delegate);
        }
        if(self->data.object)
        {
            IObject_release(self->data.object);
        }
        if(self->data.link)
        {
            ILink_release(self->data.link);
        }
        if(self->data.container)
        {
            IObject_release(self->data.container);
        }
        ExFree(self->data.name);
    });
}
static STATUS
Executive_Directory_Entry_queryTargetInterface(IDirectoryEntry *me, REFUUID iid, void **out)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    if(self->data.object)
    {
        return IObject_queryInterface(self->data.object, iid, out);
    }
    return E_NOTIMPL;   
}

static STATUS
Executive_Directory_Entry_name(IDirectoryEntry *me, char *buf, size_t bufsize)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    if(buf)
    {
        return ExStrCopy(buf, bufsize, self->data.name);
    }
    return ExStrLen(self->data.name);
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
    
    return self->data.flags | self->data.userFlags;
}

static STATUS
Executive_Directory_Entry_setFlags(IDirectoryEntry *me, DirectoryEntryFlags flags)
{
    Executive_Directory_Entry *self = INTF_TO_CLASS(me);

    /* These are not valid user flags */
    flags &= ~(DEF_LINK|DEF_VOID|DEF_CONTAINER);
    if(self->data.flags & DEF_IMMUTABLE || self->data.userFlags & DEF_IMMUTABLE)
    {
        EXLOGF((LOG_CONDITION, "%%E-PERM: set flags: operation not permitted (directory entry is marked immutable); flags = %d, new flags = %d", self->data.flags, flags));
        return E_PERM;
    }
    self->data.userFlags = flags;
    return E_SUCCESS;
}
