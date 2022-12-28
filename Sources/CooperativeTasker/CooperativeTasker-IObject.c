
#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#if FEATURE_COOPERATIVE_TASKER

# include "p_CooperativeTasker.h"

# define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_CooperativeTasker)

/* IObject */

const struct IObject_vtable_ Executive_CooperativeTasker_IObject_vtable = {
	Executive_CooperativeTasker_queryInterface,
	Executive_CooperativeTasker_retain,
	Executive_CooperativeTasker_release
};

/* IObject */

STATUS
Executive_CooperativeTasker_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_CooperativeTasker *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Tasker);
	EXEC_COMMON_SUPPORTS(Container);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

REFCOUNT
Executive_CooperativeTasker_retain(IObject *me)
{
	EXEC_COMMON_RETAIN(Executive_CooperativeTasker);
}

REFCOUNT
Executive_CooperativeTasker_release(IObject *me)
{
	EXEC_COMMON_RELEASE(Executive_CooperativeTasker, {
		ExPanic("attempt to destroy Tasker (if handover were possible, this line of code would not exist)");
		ExFree(self);
	});
}

#endif /*FEATURE_COOPERATIVE_TASKER*/
