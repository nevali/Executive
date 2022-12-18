#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Subsystems.h"

#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Subsystems)

/* Executive::Subsystems is a singleton which internally creates and populates
 * a container, passing through calls from its IContainer interface to it
 */

struct Executive_Subsystems
{
	IObject Object;
	IContainer Container;
	struct
	{
		IMutableContainer *container;
	} data;
};


static void Executive_Subsystems_init(Executive_Subsystems *self);

static Executive_Subsystems Executive_subsystems;

EXEC_COMMON_STATIC_IOBJECT(Executive_Subsystems);

static struct IObject_vtable_ Executive_Subsystems_IObject_vtable = {
	Executive_Subsystems_queryInterface,
	Executive_Subsystems_retain,
	Executive_Subsystems_release
};

static STATUS Executive_Subsystems_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_Subsystems_iterator(IContainer *me);

static struct IContainer_vtable_ Executive_Subsystems_IContainer_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Subsystems, IContainer),
	Executive_Subsystems_resolve,
	Executive_Subsystems_iterator
};

STATUS
Executive_Subsystems_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	if(!ExUuidEqual(clsid, &CLSID_Executive_Subsystems))
	{
		return E_NOENT;
	}
	if(!Executive_subsystems.data.container)
	{
		if(!executive.data.allocator)
		{
			return E_NOMEM;
		}
		Executive_Subsystems_init(&Executive_subsystems);
	}
	return IObject_queryInterface((&(Executive_subsystems.Object)), iid, out);
}

static void
Executive_Subsystems_init(Executive_Subsystems *self)
{
	size_t c;
	Executive_Resident_Object *residentObjects;

	self->Object.lpVtbl = &Executive_Subsystems_IObject_vtable;
	self->Object.instptr = self;
	self->Container.lpVtbl = &Executive_Subsystems_IContainer_vtable;
	self->Container.instptr = self;
	ExAssert(E_SUCCESS == Executive_createObject(&CLSID_Executive_Container, &IID_IMutableContainer, (void **) &(self->data.container)));
	/* Add resident subsystems */
	residentObjects = Executive_Resident_objects();
	if(residentObjects)
	{
		for(c = 0; residentObjects[c].name; c++)
		{
			ExAssert(E_SUCCESS == IMutableContainer_add((self->data.container), residentObjects[c].name, residentObjects[c].classid, (void *) residentObjects[c].instance));
		}
	}
}

static STATUS
Executive_Subsystems_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_Subsystems *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Container);
	EXEC_COMMON_SUPPORTS_DEFAULT;
}

static REFCOUNT
Executive_Subsystems_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_Subsystems_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}

/* IContainer */

static STATUS
Executive_Subsystems_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	Executive_Subsystems *self = INTF_TO_CLASS(me);

	return IMutableContainer_resolve((self->data.container), name, entry);
}

static IIterator *
Executive_Subsystems_iterator(IContainer *me)
{
	Executive_Subsystems *self = INTF_TO_CLASS(me);

	return IMutableContainer_iterator((self->data.container));
}

