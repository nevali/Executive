#ifndef P_DIRECTORY_H_
# define P_DIRECTORY_H_                1

# include <Executive/Internal/Directory.h>
# include <Executive/Internal/Runtime.h>
# include <Executive/Internal/Classes.h>

# define EXEC_COMMON_SUPPORTS(basename) \
	if(ExUuidEqual(iid, &IID_I ## basename)) \
	{ \
		if(out) \
		{ \
			I ## basename ##_retain((&(self->basename))); \
			*out = &(self->basename); \
		} \
		return E_SUCCESS; \
	}
# define EXEC_COMMON_SUPPORTS_DEFAULT \
	EXEC_COMMON_SUPPORTS(Object); \
	if(out) \
	{ \
		*out = NULL; \
	} \
	do { \
		UUIDBUF ibuf; \
		ExUuidStr(iid, ibuf); \
		EXLOGF((LOG_CONDITION, "%%E-NOTIMPL: %s(): iid:%s is not supported", __FUNCTION__, ibuf)); \
	} while(0); \
	return E_NOTIMPL;
# define EXEC_COMMON_RETAIN(class) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount++; \
	return self->data.refCount;
# define EXEC_COMMON_RELEASE(class, fini) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount--; \
	if(!self->data.refCount) \
	{ \
		fini; \
		return 0; \
	} \
	return self->data.refCount;

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

#endif /*!P_DIRECTORY_H_*/