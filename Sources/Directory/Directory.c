#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Directory.h"

/* This implementation is reasonably complex because we use the same code to
 * implement a family of related COM classes which are internally identical
 * except for the construction process
 *
 * Both the instances and the metaclasses support a number of different
 * interfaces.
 *
 * However, because the metaclasses are COM classes, albeit singletons, we
 * can create multiple metaclass instances, all using the same sets of
 * vtables, specifying a different "container kind" value for each, so that
 * the actual construction methods know what sort of container to create.
 *
 * Rather than construct all of these by hand, they are prepared by a one-time
 * initialisation method that is invoked by the only function called directly by
 * code outside of the class family, Executive_Directory_metaClass, which is
 * listed as a callback in Classes.c
 */

/** Executive::Directory **/

/* Map class UUIDs to metaclass instances */

struct MetaclassMap
{
	REFUUID classid;
	DirectoryKind kind;
	Executive_Directory_MetaClass *metaClass;
};

static Executive_Directory_MetaClass Executive_Directory_MetaClass_Container;
static Executive_Directory_MetaClass Executive_Directory_MetaClass_Root;
static Executive_Directory_MetaClass Executive_Directory_MetaClass_System;
static Executive_Directory_MetaClass Executive_Directory_MetaClass_Local;
static Executive_Directory_MetaClass Executive_Directory_MetaClass_Cluster;
static Executive_Directory_MetaClass Executive_Directory_MetaClass_Network;

static struct MetaclassMap Executive_Diretory_metaClass_map[] =
{
	{ &CLSID_Executive_Container, DK_CONTAINER, &Executive_Directory_MetaClass_Container },
	{ &CLSID_Executive_Root, DK_ROOT, &Executive_Directory_MetaClass_Root },
	{ &CLSID_Executive_System, DK_SYSTEM, &Executive_Directory_MetaClass_System },
	{ &CLSID_Executive_Local, DK_LOCAL, &Executive_Directory_MetaClass_Local },
	{ &CLSID_Executive_Cluster, DK_CLUSTER, &Executive_Directory_MetaClass_Cluster },
	{ &CLSID_Executive_Network, DK_NETWORK, &Executive_Directory_MetaClass_Network },
	{ NULL, 0, NULL }
};
static int Executive_Directory_metaClass_init;

/* Retrieve metaclass interfaces for any of the family of classes implemented
 * by this module
 */
STATUS
Executive_Directory_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	size_t c;
	Executive_Directory_MetaClass *mc;
#ifndef NDEBUG
	UUIDBUF cbuf, ibuf;
#endif

#ifndef NDEBUG
	ExUuidStr(clsid, cbuf);
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::Directory::metaClass(clsid:%s, iid:%s)", cbuf, ibuf));
#endif
	if(!Executive_Directory_metaClass_init)
	{
		Executive_Directory_metaClass_init = 1;
		EXLOGF((LOG_DEBUG, "Executive::Directory::metaClass(): initialising now"));
		for(c = 0; Executive_Diretory_metaClass_map[c].classid; c++)
		{
			mc = Executive_Diretory_metaClass_map[c].metaClass;
			mc->Object.lpVtbl = &Executive_Directory_MObject_vtable;
			mc->Object.instptr = mc;
/*			mc->Factory.lpVtbl = &Executive_Directory_MFactory_vtable;
			mc->Factory.instptr = mc; */
			mc->DirectoryEntryTarget.lpVtbl = &Executive_Directory_MDirectoryEntryTarget_vtable;
			mc->DirectoryEntryTarget.instptr = mc;
			mc->kind = Executive_Diretory_metaClass_map[c].kind;
		}
	}
	if(out)
	{
		*out = NULL;
	}
	for(c = 0; Executive_Diretory_metaClass_map[c].classid; c++)
	{
		if(ExUuidEqual(clsid, Executive_Diretory_metaClass_map[c].classid))
		{
			return MObject_queryInterface((&(Executive_Diretory_metaClass_map[c].metaClass->Object)), iid, out);
		}
	}
#ifndef NDEBUG
	EXLOGF((LOG_CONDITION, "%%E-NOENT: Executive::Directory::metaClass(): clsid:%s is not supported by this implementation", cbuf));
#endif
	return E_NOENT;
}

STATUS
Executive_Directory_MetaClass_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_Directory_MetaClass *self = (Executive_Directory_MetaClass *) me->instptr;

	EXTRACEF(("Executive::Directory::+queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(iid)));
	/* The only metaclass interfaces supported by Executive::Directory::[Generic]
	 * are IObject and MObject
	 */
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_MObject))
	{
		EXLOGF((LOG_DEBUG7, "Executive::Directory::Container::+queryInterface(): returning MObject"));
		if(out)
		{
			*out = &(self->Object);
		}
		return E_SUCCESS;
	}
/*	if(ExUuidEqual(iid, &IID_MFactory))
	{
		EXLOGF((LOG_DEBUG7, "Executive::Directory::Container::+queryInterface(): returning MFactory"));
		if(out)
		{
			*out = &(self->Factory);
		}
		return E_SUCCESS;
	} */
	if(ExUuidEqual(iid, &IID_MDirectoryEntryTarget))
	{
		EXLOGF((LOG_DEBUG7, "Executive::Directory::Container::+queryInterface(): returning MDirectoryEntryTarget"));
		if(out)
		{
			*out = &(self->DirectoryEntryTarget);
		}
		return E_SUCCESS;
	}
	EXLOGF((LOG_CONDITION, "E-NOTIMPL: metaclass interface iid:" UUID_PRINTF_FORMAT " is not implemented by Executive::Directory", UUID_PRINTF_ARGS(iid)));
	return E_NOTIMPL;
}

/* no reference counting is needed */
REFCOUNT
Executive_Directory_MetaClass_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}

REFCOUNT
Executive_Directory_MetaClass_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}
