#ifndef P_CLASSES_H_
# define P_CLASSES_H_                  1

# include <Executive/Internal/Directory.h>
# include <Executive/Internal/Runtime.h>
# include <Executive/Internal/Classes.h>
# include <Executive/Internal/Executive.h>
# include <PAL/PAL.h>

typedef struct Executive_Classes_Object Executive_Classes_Object;
typedef struct Executive_Classes_Iterator Executive_Classes_Iterator;
typedef struct Executive_Classes_DirectoryEntry Executive_Classes_DirectoryEntry;

typedef STATUS (*MetaClassCallback)(REFUUID clsid, REFUUID iid, void **out);

struct MetaClassEntry
{
	const char *className;
	REFUUID clsid;
	const char *displayName;
	MetaClassCallback fn;
	void /*IObject*/ *factory;
};

/* Executive::Classes::Object */
struct Executive_Classes_Object
{
	IObject Object;
	struct
	{
		REFCOUNT refCount;
		void (*fini)(Executive_Classes_Object *self);
		STATUS (*queryInterface)(IObject *me, REFUUID iid, void **out);
	} data;
};

/* Executive::Classes::Iterator */
struct Executive_Classes_Iterator
{
	Executive_Classes_Object parent;
	IIterator Iterator;
	struct
	{
		/* For implementations to update */
		void *userData;
		size_t index;
		/* Callbacks for implementations to use */
		void (*fini)(Executive_Classes_Iterator *self);
		STATUS (*next)(Executive_Classes_Iterator *self);
		IObject *(*current)(Executive_Classes_Iterator *self);
	} data;
};

/* Executive::Classes::DirectoryEntry */

struct Executive_Classes_DirectoryEntry
{
	IDirectoryEntry DirectoryEntry;
	IContainer Container;
	ILink Link;
	IObject Object;
	struct
	{
		REFCOUNT refCount;
		char *name;
		UUID clsid;
		DirectoryEntryFlags flags;
		char *target;
		/* IDirectoryEntry */
		STATUS (*queryTargetInterface)(Executive_Classes_DirectoryEntry *me, REFUUID iid, void **out);
		/* IContainer */
		IIterator *(*iterator)(Executive_Classes_DirectoryEntry *me);
	} data;
};

/* XXX rename */
extern struct MetaClassEntry metaClass_entries[];

extern IContainer Executive_Classes_IContainer;
extern MFactory Executive_Allocator_MFactory;

void Executive_Classes_Object_init(Executive_Classes_Object *self);
EXEC_COMMON_DECL_IOBJECT(Executive_Classes_Object);

extern Executive_Classes_Iterator *Executive_Classes_Iterator_create(void);
extern Executive_Classes_DirectoryEntry *Executive_Classes_DirectoryEntry_create(const char *name, REFUUID clsid, DirectoryEntryFlags flags);

#endif /*!P_CLASSES_H_*/
