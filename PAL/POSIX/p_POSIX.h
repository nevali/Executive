/* Executive Microkernel
 * POSIX Platform Adaptation Layer
 *   Private common header
 */

#ifndef P_POSIX_H_
# define P_POSIX_H_

# define INITGUID_EXTERN               1

/* Diagnostics and panic output */
#  include <stdio.h>
/* File I/O, host memory management */
#  include <unistd.h>
/* Errno values */
#  include <errno.h>
/* malloc(), free(), etc. */
#  include <stdlib.h>
/* mmap() */
#  include <sys/mman.h>
/* memcmp() */
#  include <string.h>

# include <Executive/Errors.h>
# include <PAL/PAL.h>

typedef union PAL_POSIX_Platform PAL_POSIX_Platform;
typedef union PAL_POSIX_MemoryManager PAL_POSIX_MemoryManager;
typedef union PAL_POSIX_Region PAL_POSIX_Region;
typedef union PAL_POSIX_BootEnvironment PAL_POSIX_BootEnvironment;
typedef union PAL_POSIX_PlatformDiagnostics PAL_POSIX_PlatformDiagnostics;

/* These are well-known metaclasses retrievable via PAL$metaClass() */
extern PAL_POSIX_Platform PAL_POSIX_platform;
extern PAL_POSIX_MemoryManager PAL_POSIX_memoryManager;
extern PAL_POSIX_BootEnvironment PAL_POSIX_bootEnvironment;
extern PAL_POSIX_PlatformDiagnostics PAL_POSIX_diagnostics;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain; for interfaces that are divergent, a structure
 * containing a set of distinct interfaces, each with their own backreference,
 * would be required (and traversal logic in method bodies).
 */
union PAL_POSIX_Platform
{
	IPlatform Platform;
	IObject Object;
	struct
	{
		void *vtable;
		IAllocator *allocator;
	} data;	
};

union PAL_POSIX_MemoryManager
{
	IMemoryManager MemoryManager;
	IObject Object;
	struct
	{
		void *vtable;
		int pagesize;
	} data;
};

union PAL_POSIX_Region
{
	IRegion Region;
	IObject Object;
	struct
	{
		void *vtable;
		uint32_t refcount;
		PAL_POSIX_MemoryManager *mm;
		IRegionHolder *holder;
		RegionFlags flags;
		uint8_t *base;
		size_t count;
	} data;
};

union PAL_POSIX_BootEnvironment
{
	IBootEnvironment BootEnvironment;
	IObject Object;
	struct
	{
		void *vtable;
	} data;
};

union PAL_POSIX_PlatformDiagnostics
{
	IPlatformDiagnostics PlatformDiagnostics;
	IObject Object;
	struct
	{
		void *vtable;
	} data;
};

# ifdef __cplusplus
extern "C" {
# endif

extern void PAL_POSIX_panic(const char *string);
extern void PAL_POSIX_init(void);
extern void PAL_POSIX_Platform_init();
extern void PAL_POSIX_MemoryManager_init();
extern void PAL_POSIX_PlatformDiagnostics_init();
extern void PAL_POSIX_PlatformDiagnostics_log(IPlatformDiagnostics *me, LogLevel level, const char *str);
extern int PAL_POSIX_Region_create(PAL_POSIX_MemoryManager *mm, RegionFlags flags, IRegionHolder *owner, void *ptr, size_t size, PAL_POSIX_Region **out);

# define PALLog(level, str)            PAL_POSIX_PlatformDiagnostics_log(NULL, level, str)
# define PALDebug(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG, str)
# define PALDebug2(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG2, str)

# ifdef __cplusplus
}
# endif

#endif /*!P_POSIX_H_*/