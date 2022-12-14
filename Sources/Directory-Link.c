#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

struct Executive_Directory_Link
{
	ILink Link;
	IObject Object;
	struct
	{
		REFCOUNT refCount;
	} data;
};

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory_Link *)((i)->instptr)

/** Executive::Directory::Link **/

/* IObject */
static STATUS Executive_Directory_Link_queryInterface(ILink *me, REFUUID iid, void **out);
static REFCOUNT Executive_Directory_Link_retain(ILink *me);
static REFCOUNT Executive_Directory_Link_release(ILink *me);
/* ILink */

static struct ILink_vtable_ Executive_Directory_Link_vtable = {
    Executive_Directory_Link_queryInterface,
    Executive_Directory_Link_retain,
    Executive_Directory_Link_release,
};

/** Executive::Directory::Link **/

Executive_Directory_Link *
Executive_Directory_Link_create()
{
    Executive_Directory_Link *p;

    EXLOGF((LOG_TRACE, "Executive::Directory::Link::create()"));

    if(NULL == (p = ExAlloc(sizeof(Executive_Directory_Link))))
    {
        EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Directory_Link)));
        return NULL;
    }
    p->Link.lpVtbl = &Executive_Directory_Link_vtable;
    p->Link.instptr = p;
    p->Object.lpVtbl = (void *) &Executive_Directory_Link_vtable;
    p->Object.instptr = p;
    p->data.refCount = 1;
    return p;
}

static STATUS
Executive_Directory_Link_queryInterface(ILink *me, REFUUID iid, void **out)
{
    Executive_Directory_Link *self = INTF_TO_CLASS(me);

    EXEC_COMMON_SUPPORTS(Link);
    EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_Directory_Link_retain(ILink *me)
{
    EXEC_COMMON_RETAIN(Executive_Directory_Link);
}

static REFCOUNT
Executive_Directory_Link_release(ILink *me)
{
    EXEC_COMMON_RELEASE(Executive_Directory_Link, {});
}
