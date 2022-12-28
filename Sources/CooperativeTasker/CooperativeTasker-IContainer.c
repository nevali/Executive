
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#if FEATURE_COOPERATIVE_TASKER

# include "p_CooperativeTasker.h"

# define INTF_TO_CLASS(i)              EXEC_COMMON_INTF_TO(i, Executive_CooperativeTasker)

/* IContainer */
static STATUS Executive_CooperativeTasker_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_CooperativeTasker_iterator(IContainer *me);

const struct IContainer_vtable_ Executive_CooperativeTasker_IContainer_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_CooperativeTasker, IContainer),
	Executive_CooperativeTasker_resolve,
	Executive_CooperativeTasker_iterator
};

/* Executive::CooperativeTasker::<IContainer>resolve() */
static STATUS
Executive_CooperativeTasker_resolve(IContainer *me, const char *name, IDirectoryEntry **out)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	UNUSED__(self);

	UNUSED__(name);
	UNUSED__(out);

	return E_NOTIMPL;
}

static IIterator *
Executive_CooperativeTasker_iterator(IContainer *me)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	UNUSED__(self);

	return NULL;
}

#endif /*FEATURE_COOPERATIVE_TASKER*/
