#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/** Executive::Directory<MObject> **/

static STATUS Executive_Directory_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out);

struct MObject_vtable_ Executive_Directory_MObject_vtable = {
	(STATUS (*)(MObject *, REFUUID, void **)) &Executive_Directory_MetaClass_queryInterface,
	(REFCOUNT (*)(MObject *)) &Executive_Directory_MetaClass_retain,
	(REFCOUNT (*)(MObject *)) &Executive_Directory_MetaClass_release,
	Executive_Directory_MObject_create,
};

static STATUS
Executive_Directory_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out)
{
	Executive_Directory_MetaClass *self = (Executive_Directory_MetaClass *) me->instptr;
	Executive_Directory *dir;
	STATUS status;

	UNUSED__(me);

	ExAssert(NULL != out);

	EXLOGF((LOG_TRACE, "Executive::Directory<MObject>::+create()"));

	*out = NULL;
	if(!(dir = IAllocator_alloc(allocator, sizeof(Executive_Directory))))
	{
		EXLOGF((LOG_CONDITION, "%%E-NOMEM: IAllocator::alloc(%u) failed", sizeof(Executive_Directory)));
		return E_NOMEM;
	}
	dir->Object.lpVtbl = &Executive_Directory_IObject_vtable;
	dir->Object.instptr = dir;
	dir->Container.lpVtbl = &Executive_Directory_IContainer_vtable;
	dir->Container.instptr = dir;
	dir->MutableContainer.lpVtbl = &Executive_Directory_IMutableContainer_vtable;
	dir->MutableContainer.instptr = dir;
	if(self->kind == DK_ROOT)
	{
		dir->Namespace.lpVtbl = &Executive_Directory_INamespace_vtable;
		dir->Namespace.instptr = dir;
	}
	dir->data.refCount = 1;
	dir->data.kind = self->kind;
	status = IObject_queryInterface((&(dir->Object)), iid, out);
	if(status == E_SUCCESS)
	{
		/* queryInterface will have incremented the refcount */
		dir->data.refCount--;
	}
	else
	{
		IAllocator_free(allocator, dir);
		*out = NULL;
	}
	return status;
}
