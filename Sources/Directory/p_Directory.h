#ifndef P_DIRECTORY_H_
# define P_DIRECTORY_H_                1

# include <Executive/Internal/Directory.h>
# include <Executive/Internal/Runtime.h>
# include <Executive/Internal/Classes.h>
# include <Executive/Internal/Executive.h>

/** Executive::Directory metaclass */

struct Executive_Directory_MetaClass
{
	/* Standard constructor, also used for IObject */
	MObject Object;
	/* MSCOM-style factory */
	MFactory Factory;
	/* subsidiary directory entry constructor */
	MDirectoryEntryTarget DirectoryEntryTarget;
	/* What kind of objects does this metaclass create? */
	DirectoryKind kind;
};

typedef struct Executive_Directory_MetaClass Executive_Directory_MetaClass;

/* these three methods are used by all of the metaclass interfaces */
STATUS Executive_Directory_MetaClass_queryInterface(IObject *me, REFUUID iid, void **out);
REFCOUNT Executive_Directory_MetaClass_retain(IObject *me);
REFCOUNT Executive_Directory_MetaClass_release(IObject *me);

extern struct MObject_vtable_ Executive_Directory_MObject_vtable;
extern struct MFactory_vtable_ Executive_Directory_MFactory_vtable;
extern struct MDirectoryEntryTarget_vtable_ Executive_Directory_MDirectoryEntryTarget_vtable;

/** Executive::Directory **/

struct Executive_Directory
{
	IDirectoryEntryTarget DirectoryEntryTarget;
	IMutableContainer MutableContainer;
	IContainer Container;
	IObject Object;
	INamespace Namespace;
	struct
	{
		REFCOUNT refCount;
		DirectoryKind kind;
		Executive_Directory_Entry *first, *last;
	} data;
};

/** Executive::Directory::Entry **/

struct Executive_Directory_Entry
{
	IDirectoryEntry DirectoryEntry;
	IObject Object;
	struct
	{
		REFCOUNT refCount;
		Executive_Directory_Entry *next;
		char *name;
		UUID clsid;
		DirectoryEntryFlags flags;
		DirectoryEntryFlags userFlags;
		/* the basic target object */
		IObject *object;
		/* the target delegate interface */
		IDirectoryEntryTarget *delegate;
		/* if flags & DEF_LINK*/
		ILink *link;
		/* if flags & DEF_CONTAINER */
		IContainer *container;
	} data;
};

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               (struct Executive_Directory *)((i)->instptr)

STATUS Executive_Directory_Root_populate(IMutableContainer *me);
STATUS Executive_Directory_System_populate(IMutableContainer *me);
STATUS Executive_Directory_Local_populate(IMutableContainer *me);
STATUS Executive_Directory_Cluster_populate(IMutableContainer *me);
STATUS Executive_Directory_Network_populate(IMutableContainer *me);


#endif /*!P_DIRECTORY_H_*/
