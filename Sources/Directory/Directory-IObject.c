#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<IObject> **/

const struct IObject_vtable_ Executive_Directory_IObject_vtable = {
	Executive_Directory_queryInterface,
	Executive_Directory_retain,
	Executive_Directory_release
};

STATUS
Executive_Directory_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_Directory *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(MutableContainer);
	EXEC_COMMON_SUPPORTS(Container);
	EXEC_COMMON_SUPPORTS(DirectoryEntryTarget);
	if(self->data.kind == DK_ROOT)
	{
		EXEC_COMMON_SUPPORTS(Namespace);
	}
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

REFCOUNT
Executive_Directory_retain(IObject *me)
{
	EXEC_COMMON_RETAIN(Executive_Directory);
}

REFCOUNT
Executive_Directory_release(IObject *me)
{
	EXEC_COMMON_RELEASE(Executive_Directory, {
		if(self->data.kind == DK_ROOT)
		{
//			IMutableContainer_release(self->data.root.system);
//			IMutableContainer_release(self->data.root.local);
//			IMutableContainer_release(self->data.root.network);
		}
		ExFree(self);
	});
}
