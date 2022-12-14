#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (union Executive_Directory_Iterator *)(void *)(i)

/** Executive::Directory::Iterator **/

union Executive_Directory_Iterator
{
	IObject Object;
	IIterator Iterator;
	struct
	{
		const struct IIterator_vtable_ *vtable;
		REFCOUNT refCount;
		Executive_Directory_Entry *dirent;
	} data;
};

/* IObject */
static STATUS Executive_Directory_Iterator_queryInterface(IIterator *me, REFUUID iid, void **out);
static REFCOUNT Executive_Directory_Iterator_retain(IIterator *me);
static REFCOUNT Executive_Directory_Iterator_release(IIterator *me);
/* IIterator */
static STATUS Executive_Directory_Iterator_next(IIterator *me);
static IObject *Executive_Directory_Iterator_current(IIterator *me);

static const struct IIterator_vtable_ Executive_Directory_Iterator_vtable = {
	Executive_Directory_Iterator_queryInterface,
	Executive_Directory_Iterator_retain,
	Executive_Directory_Iterator_release,
	Executive_Directory_Iterator_next,
	Executive_Directory_Iterator_current
};

/** Executive::Directory::Iterator **/

Executive_Directory_Iterator *
Executive_Directory_Iterator_create(Executive_Directory_Entry *dirent)
{
	Executive_Directory_Iterator *p;

/* dirent may be NULL to indicate an empty list */
/* ExAssert(NULL != dirent); */

/*	EXLOGF((LOG_TRACE, "Executive::Directory::Iterator::create()")); */

	if(NULL == (p = ExAlloc(sizeof(Executive_Directory_Iterator))))
	{
		EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Directory_Iterator)));
		return NULL;
	}
	p->data.vtable = &Executive_Directory_Iterator_vtable;
	p->data.refCount = 1;
	/* XXX this is currently WEAK */
	p->data.dirent = dirent;
	return p;
}

static STATUS
Executive_Directory_Iterator_queryInterface(IIterator *me, REFUUID iid, void **out)
{
	Executive_Directory_Iterator *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Iterator);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_Directory_Iterator_retain(IIterator *me)
{
	EXEC_COMMON_RETAIN(Executive_Directory_Iterator);
}

static REFCOUNT
Executive_Directory_Iterator_release(IIterator *me)
{
	EXEC_COMMON_RELEASE(Executive_Directory_Iterator, {
/*		EXLOGF((LOG_TRACE, "Executive::Directory::Iterator::release(): freeing iterator"));  */
	});
}

static STATUS
Executive_Directory_Iterator_next(IIterator *me)
{
	Executive_Directory_Iterator *self = INTF_TO_CLASS(me);

	if(!self->data.dirent)
	{
		return E_EOF;
	}
	self->data.dirent = self->data.dirent->data.next;
	if(!self->data.dirent)
	{
		return E_EOF;
	}
	return E_SUCCESS;
}

static IObject *
Executive_Directory_Iterator_current(IIterator *me)
{
	Executive_Directory_Iterator *self = INTF_TO_CLASS(me);

	if(!self->data.dirent)
	{
		return NULL;
	}
	IObject_retain((&(self->data.dirent->Object)));
	return &(self->data.dirent->Object);
}
