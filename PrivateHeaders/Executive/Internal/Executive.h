/* This header is used by the Executive's start-up code (Sources/entrypoint.c)
 * and by the Classes module of the Executive itself
 */

#ifndef EXECUTIVE_INTERNAL_EXECUTIVE_H_
# define EXECUTIVE_INTERNAL_EXECUTIVE_H_ 1

# include <Executive/IPlatform.h>
# include <Executive/IAddressSpace.h>
# include <Executive/IBootEnvironment.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Executive/IMutableContainer.h>
# include <Executive/INamespace.h>
# include <Executive/ITasker.h>
# include <Executive/IThread.h>
# include <Executive/IDirectoryEntryTarget.h>

# undef ExPanic
# define ExPanic(str)                  IPlatform_panic(executive.data.platform, str) /*[noreturn]*/
# undef ExAlloc
# define ExAlloc(nbytes)               IAllocator_alloc(executive.data.allocator, nbytes)
# undef ExReAlloc
# define ExReAlloc(ptr, nbytes)        IAllocator_realloc(executive.data.allocator, ptr, nbytes)
# undef ExFree
# define ExFree(ptr)                   IAllocator_free(executive.data.allocator, ptr)
# undef ExYield
# define ExYield()                     ITasker_yield(executive.data.tasker)
# undef ExLog
# define ExLog(level, str)             if(executive.data.diagnostics) { IPlatformDiagnostics_log(executive.data.diagnostics, level, str); }
# undef ExOpen
# define ExOpen(filename, iid, out)    INamespace_open(executive.data.rootNS, filename, NULL, iid, (void **) (out))
# undef ExCreate
# define ExCreate(filename, clsid, iid, out) INamespace_create(executive.data.rootNS, filename, NULL, clsid, iid, (void **) (out))
# undef ExAdd
# define ExAdd(filename, clsid, obj)   INamespace_add(executive.data.rootNS, filename, NULL, clsid, obj)
# undef ExCreateLink
# define ExCreateLink(filename, target, force) INamespace_createLink(executive.data.rootNS, filename, NULL, target, force)
# undef ExSetFlags
# define ExSetFlags(filename, flags)   INamespace_setFlags(executive.data.rootNS, filename, NULL, flags)
# undef ExPhaseShift
# define ExPhaseShift(phase)           IPlatform_phaseTransition(executive.data.platform, phase)

typedef struct Executive Executive;

struct ExecutiveEntryParameters;

/* Executive private data */
struct Executive
{
	IObject Object;
	IContainer Container;
	IDirectoryEntryTarget DirectoryEntryTarget;
	struct
	{
		/* The PAL's metaclass callback, provided by the Glue */
		int (*PAL_metaClass)(REFUUID clsid, REFUUID iid, void **out);
		/* A reference to the PAL's Platform object */
		IPlatform *platform;
		/* A reference to the kernel's address space */
		IAddressSpace *addressSpace;
		/* A reference to our default allocator */
		IAllocator *allocator;
		/* A reference to the boot environment */
		IBootEnvironment *bootEnvironment;
		/* A reference to the PAL's diagnostics interface, if provided */
		IPlatformDiagnostics *diagnostics;
		/* A pointer to the root of the Object Directory */
		IMutableContainer *rootDirectory;
		/* The Object Directory namespace */
		INamespace *rootNS;
		/* A reference to the Tasker */
		ITasker *tasker;
		/* Our bootstrap task */
		ITask *bootstrapTask;
		/* A pointer to our internal System container */
		IMutableContainer *system;
	} data;
};

extern Executive executive;

STATUS Executive_MetaClass_metaClass(REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_init(Executive *self, struct ExecutiveEntryParameters *params, IPlatform *platform);
STATUS Executive_startup(Executive *self);
STATUS Executive_runLoop(Executive *self);

#endif /*!EXECUTIVE_INTERNAL_EXECUTIVE_H_*/
