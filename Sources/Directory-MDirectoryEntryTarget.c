#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

/** Executive::Directory::[Generic] **/

/* IObject */
static STATUS Executive_Directory_Generic_queryInterface(MDirectoryEntryTarget *me, REFUUID iid, void **out);
static REFCOUNT Executive_Directory_Generic_retain(MDirectoryEntryTarget *me);
static REFCOUNT Executive_Directory_Generic_release(MDirectoryEntryTarget *me);
/* MDirectoryEntryTarget */
static STATUS Executive_Directory_Generic_createInstance(MDirectoryEntryTarget *me, DirectoryKind kind, IDirectoryEntry *entry, IDirectoryEntryTarget **out);

static STATUS Executive_Directory_Container_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);
static STATUS Executive_Directory_Root_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);
static STATUS Executive_Directory_System_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);
static STATUS Executive_Directory_Network_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);
static STATUS Executive_Directory_Cluster_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);
static STATUS Executive_Directory_Local_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out);

/** Executive::Directory::[Generic]<MDirectoryEntryTarget> **/
#define DECLARE_METASUBCLASS(name) \
	static struct MDirectoryEntryTarget_vtable_ Executive_Directory_## name ##_MDirectoryEntryTarget_vtable = { \
	Executive_Directory_Generic_queryInterface, \
	Executive_Directory_Generic_retain, \
	Executive_Directory_Generic_release, \
	Executive_Directory_## name ##_createInstance \
}; \
struct MDirectoryEntryTarget Executive_Directory_## name ##_MDirectoryEntryTarget = { &Executive_Directory_## name ##_MDirectoryEntryTarget_vtable, NULL };

DECLARE_METASUBCLASS(Container);
DECLARE_METASUBCLASS(Root);
DECLARE_METASUBCLASS(System);
DECLARE_METASUBCLASS(Network);
DECLARE_METASUBCLASS(Local);
DECLARE_METASUBCLASS(Cluster);

/** Executive::Directory::[Generic]<IObject> **/

static STATUS
Executive_Directory_Generic_queryInterface(MDirectoryEntryTarget *me, REFUUID iid, void **out)
{
#ifndef NDEBUG
	UUIDBUF ibuf;
#endif

#ifndef NDEBUG
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::Directory::Generic::+queryInterface(iid:%s)", ibuf));
#endif
	/* The only metaclass interfaces supported by Executive::Directory::[Generic]
	 * are IObject and MDirectoryEntryTarget
	 */
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_MDirectoryEntryTarget))
	{
		EXLOGF((LOG_DEBUG6, "Executive::Directory::Container::+queryInterface(): metaclass interface is supported"));
		if(out)
		{
			*out = me;
		}
		return E_SUCCESS;
	}
	EXLOGF((LOG_CONDITION, "E-NOTIMPL: iid:%s is not implemented by Executive::Directory::Generic", ibuf));
	return E_NOTIMPL;
}

static REFCOUNT
Executive_Directory_Generic_retain(MDirectoryEntryTarget *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_Directory_Generic_release(MDirectoryEntryTarget *me)
{
	UNUSED__(me);

	return 1;
}

/** Executive::Directory::[Generic]<MDirectoryEntryTarget> **/

static STATUS
Executive_Directory_Generic_createInstance(MDirectoryEntryTarget *me, DirectoryKind kind, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	Executive_Directory *dir;

	/* This class method is invoked when a container wants to create a new
	 * instance of Executive::Directory::System
	 */
	UNUSED__(me);

	ExAssert(NULL != out);

	EXLOGF((LOG_TRACE, "Executive::Directory::[Generic]<MDirectoryEntryTarget>::+createInstance(%d, %s)", kind, (entry ? IDirectoryEntry_name(entry) : "NULL" )));

	*out = NULL;
#ifndef NDEBUG
	if(kind == DK_ROOT)
	{
		ExAssert(NULL == entry);
	}
	else
#endif
	{
		ExAssert(NULL != entry);
		if(NULL == entry)
		{
			EXLOGF((LOG_CONDITION, "%%E-INVAL: Executive::Directory::[Generic]::+createInstance() invoked with entry == NULL"));
			return E_INVAL;
		}
	}
	if(!(dir = ExAlloc(sizeof(Executive_Directory))))
	{
		EXLOGF((LOG_CONDITION, "%%E-NOMEM: ExAlloc(%u) failed", sizeof(Executive_Directory)));
		return E_NOMEM;
	}
	dir->Object.lpVtbl = &Executive_Directory_IObject_vtable;
	dir->Object.instptr = dir;
	dir->Container.lpVtbl = &Executive_Directory_IContainer_vtable;
	dir->Container.instptr = dir;
	dir->MutableContainer.lpVtbl = &Executive_Directory_IMutableContainer_vtable;
	dir->MutableContainer.instptr = dir;
	dir->DirectoryEntryTarget.lpVtbl = &Executive_Directory_IDirectoryEntryTarget_vtable;
	dir->DirectoryEntryTarget.instptr = dir;
	if(kind == DK_ROOT)
	{
		dir->Namespace.lpVtbl = &Executive_Directory_INamespace_vtable;
		dir->Namespace.instptr = dir;
	}
	dir->data.refCount = 1;
	dir->data.kind = kind;
#ifndef NDEBUG
	switch(kind)
	{
		case DK_ROOT:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Root (Object Directory root)"));
			/* it should not be possible to create a new root directory if one
			 * already exists
			 */
			ExAssert(NULL == executive.data.rootDirectory);
			break;
		case DK_DOMAIN:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Domain ('%s')", IDirectoryEntry_name(entry)));
			break;
		case DK_SYSTEM:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::System ('%s')", IDirectoryEntry_name(entry)));
			break;
		case DK_NETWORK:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Network ('%s')",  IDirectoryEntry_name(entry)));
			break;
		case DK_LOCAL:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Local ('%s')",  IDirectoryEntry_name(entry)));
			break;
		case DK_CLUSTER:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Cluster ('%s')",  IDirectoryEntry_name(entry)));
			break;
		case DK_CONTAINER:
			EXLOGF((LOG_DEBUG, "created Executive::Directory::Container ('%s')",  IDirectoryEntry_name(entry)));
			break;
	}
#endif
	*out = &(dir->DirectoryEntryTarget);
	return E_SUCCESS;
}

static STATUS
Executive_Directory_Container_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	return Executive_Directory_Generic_createInstance(me, DK_CONTAINER, entry, out);
}

static STATUS
Executive_Directory_Root_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	ExAssert(NULL == executive.data.rootDirectory);
	return Executive_Directory_Generic_createInstance(me, DK_ROOT, entry, out);
}

static STATUS
Executive_Directory_System_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	return Executive_Directory_Generic_createInstance(me, DK_SYSTEM, entry, out);
}

static STATUS
Executive_Directory_Network_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	return Executive_Directory_Generic_createInstance(me, DK_NETWORK, entry, out);
}

static STATUS
Executive_Directory_Local_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	return Executive_Directory_Generic_createInstance(me, DK_LOCAL, entry, out);
}

static STATUS
Executive_Directory_Cluster_createInstance(MDirectoryEntryTarget *me, IDirectoryEntry *entry, IDirectoryEntryTarget **out)
{
	return Executive_Directory_Generic_createInstance(me, DK_CLUSTER, entry, out);
}

