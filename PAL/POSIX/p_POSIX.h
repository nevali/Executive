/* Executive Microkernel
 * POSIX Platform Adaptation Layer
 *   Private common header
 */

#ifndef P_POSIX_H_
# define P_POSIX_H_

# define INITGUID_EXTERN               1

/* Diagnostics and panic output */
#  include <stdio.h>
/* Errno values */
#  include <errno.h>
/* malloc(), free(), etc. */
#  include <stdlib.h>
/* memcmp() */
#  include <string.h>
/* sleep()  */
#  include <unistd.h>

# include <PAL/PAL.h>

# include <Executive/IWriteChannel.h>
# include <Executive/IContainer.h>
# include <Executive/INamespace.h>

# include <Executive/IMutableContainer.h>
# include <Executive/MFactory.h>

# include <Executive/Classes.h>
# include <Executive/Internal/Classes.h>

typedef struct PAL_POSIX_Platform PAL_POSIX_Platform;
typedef union PAL_POSIX_BootEnvironment PAL_POSIX_BootEnvironment;
typedef struct PAL_POSIX_PlatformDiagnostics PAL_POSIX_PlatformDiagnostics;

extern PAL_POSIX_Platform *PAL_POSIX;

/* This construction is valid for as long as the interfaces are all part of a
 * single-inheritance chain; for interfaces that are divergent, a structure
 * containing a set of distinct interfaces, each with their own backreference,
 * would be required (and traversal logic in method bodies).
 */
struct PAL_POSIX_Platform
{
	IObject Object;
	IPlatform Platform;
	IContainer Container;
	struct
	{
		IAllocator *allocator;
		INamespace *namespace;
		IMutableContainer *platformContainer;
		IMemoryManager *memoryManager;
		IBootEnvironment *BootEnvironment;
		IPlatformDiagnostics *diagnostics;
	} data;
};

union PAL_POSIX_BootEnvironment
{
	IObject Object;
	IBootEnvironment BootEnvironment;
	struct
	{
		void *vtable;
	} data;
};

struct PAL_POSIX_PlatformDiagnostics
{
	IObject Object;
	IPlatformDiagnostics PlatformDiagnostics;
	IWriteChannel WriteChannel;
	struct
	{
		LogLevel level;
	} data;
};

# ifdef __cplusplus
extern "C" {
# endif

void PAL_POSIX_panic(const char *string);
void PAL_POSIX_init(void);
void PAL_POSIX_Platform_init(void);
void PAL_POSIX_Platform_setMemoryManager(IMemoryManager *mm);
void PAL_POSIX_Platform_setDiagnostics(IPlatformDiagnostics *diag);
void PAL_POSIX_MemoryManager_init(void);
void PAL_POSIX_PlatformDiagnostics_init(void);

extern void PAL_POSIX_PlatformDiagnostics_log(IPlatformDiagnostics *me, LogLevel level, const char *str);

extern PHASE PAL_POSIX_phase;

# if EXEC_BUILD_RELEASE
#  define PALLOGF(x)
#  define PALLog(level, str)
#  define PALDebug(str)
#  define PALDebug2(str)
#  define PALDebug3(str)
#  define PALDebug4(str)
#  define PALDebug5(str)
#  define PALDebug6(str)
#  define PALDebug7(str)
#  define PALTrace(str)
#  define PALCondition(str)
# else
extern void PAL_POSIX_PlatformDiagnostics__logf(LogLevel level, const char *str, ...);
#  define PALLOGF(X)                    PAL_POSIX_PlatformDiagnostics__logf X
#  define PALLog(level, str)            PAL_POSIX_PlatformDiagnostics_log(NULL, level, str)
#  define PALDebug(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG, str)
#  define PALDebug2(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG2, str)
#  define PALDebug7(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG7, str)
#  define PALTrace(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_TRACE, str)
#  define PALCondition(str)             PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_CONDITION, str)
# endif

# ifdef __cplusplus
}
# endif

#endif /*!P_POSIX_H_*/