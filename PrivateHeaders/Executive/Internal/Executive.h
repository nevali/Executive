/* This header is used by the Executive's start-up code (Sources/entrypoint.c)
 * and by the Classes module of the Executive itself
 */

#ifndef EXECUTIVE_INTERNAL_EXECUTIVE_H_
# define EXECUTIVE_INTERNAL_EXECUTIVE_H_ 1

# include <Executive/IPlatform.h>
# include <Executive/IMemoryManager.h>
# include <Executive/IBootEnvironment.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Executive/IMutableContainer.h>
# include <Executive/INamespace.h>
# include <Executive/ITasker.h>
# include <Executive/IThread.h>

typedef struct Executive Executive;

struct ExecutiveEntryParameters;

/* Executive private data */
struct Executive
{
	/* Placeholder for our virtual method table */
	void *vmt;
	struct
	{
		int (*PAL_metaClass)(REFUUID clsid, REFUUID iid, void **out);
		/* A reference to the PAL's Platform object */
		IPlatform *platform;
		/* A reference to the current memory manager */
		IMemoryManager *mm;
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
	} data;
};

extern Executive executive;

STATUS Executive_initialise(struct ExecutiveEntryParameters *params, IPlatform *platform);
STATUS Executive_bootstrap(void);
STATUS Executive_run(void);

#endif /*!EXECUTIVE_INTERNAL_EXECUTIVE_H_*/
