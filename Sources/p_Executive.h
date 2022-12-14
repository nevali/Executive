/* Executive Microkernel
 * Sources/Executive/p_ExecutiveServices.h
 *   Common private header used by any C/C++ files comprising the
 *   libExecutiveServices convenience library
 */

/* Copyright (c) 2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/* Prevent multiple inclusions */
#ifndef P_EXECUTIVE_H_
# define P_EXECUTIVE_H_        1

/* */
# define INITGUID_EXTERN       1

# include <stddef.h>

# include <PAL/PAL.h>

# include <Executive/Internal/Executive.h>
# include <Executive/Internal/Entry.h>
# include <Executive/Internal/Runtime.h>

# include <Executive/MFactory.h>

# include <Executive/IAllocator.h>
# include <Executive/IBootEnvironment.h>
# include <Executive/IPlatformDiagnostics.h>

# include <Executive/IIterator.h>

# include <Executive/IContainer.h>
# include <Executive/INamespace.h>
# include <Executive/IMutableContainer.h>
# include <Executive/IDirectoryEntry.h>
# include <Executive/IDirectoryEntryTarget.h>
# include <Executive/ILink.h>

# include <Executive/IWriteChannel.h>

# include <Executive/ITasker.h>
# include <Executive/ITask.h>
# include <Executive/IThread.h>
# include <Executive/IJob.h>
# include <Executive/IEvent.h>

# include <Executive/MDirectoryEntryTarget.h>

# include <Executive/Classes.h>

# define EXEC_THREAD_STACK_SIZE        32768

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

typedef struct Executive Executive;
typedef union Executive_Allocator Executive_Allocator;
typedef union Executive_BootEnvironment Executive_BootEnvironment;
typedef struct Executive_CooperativeTasker Executive_CooperativeTasker;
typedef union Executive_CooperativeTasker_Task Executive_CooperativeTasker_Task;
typedef union Executive_CooperativeTasker_Thread Executive_CooperativeTasker_Thread;

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

# undef ExPanic
# define ExPanic(str)                  IPlatform_panic(executive.data.platform, str) /*[noreturn]*/
# undef ExAlloc
# define ExAlloc(nbytes)               IAllocator_alloc(executive.data.allocator, nbytes)
# undef ExReAlloc
# define ExReAlloc(ptr, nbytes)        IAllocator_realloc(executive.data.allocator, ptr nbytes)
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

# ifdef __cplusplus
extern "C" {
# endif

extern Executive executive;

extern IAllocator *Executive_Allocator_create(IMemoryManager *mm);
extern void *Executive_Allocator_map(Executive_Allocator *me, size_t size, RegionFlags flags);
extern int Executive_Allocator_unmap(Executive_Allocator *me, void *addr, size_t size);

STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_Directory_metaClass(REFUUID clsid, REFUUID iid, void **out);

extern IBootEnvironment *Executive_BootEnvironment_create(void);

extern ITasker *Executive_CooperativeTasker_create(void);

extern void Executive_BootstrapTask_mainThread(IThread *self);

const char *Executive_nameOfClass(REFUUID clsid);

# ifdef __cplusplus
}
# endif

#endif /*!P_EXECUTIVE_H_*/