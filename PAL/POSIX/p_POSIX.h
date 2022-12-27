/* Executive Microkernel
 * POSIX Platform Adaptation Layer
 *   Private common header
 */

#ifndef P_POSIX_H_
# define P_POSIX_H_

# define INITGUID_EXTERN               1

/* Diagnostics and panic output */
# include <stdio.h>
/* Errno values */
# include <errno.h>
/* malloc(), free(), etc. */
# include <stdlib.h>
/* memcmp() */
# include <string.h>
/* sleep()  */
# include <unistd.h>
/* sigaction() */
# include <signal.h>
/* nanosleep() */
# include <time.h>

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
#if FEATURE_PAL_DIAGNOSTICS
typedef struct PAL_POSIX_PlatformDiagnostics PAL_POSIX_PlatformDiagnostics;
#endif
#if FEATURE_CONSOLE
typedef struct PAL_POSIX_Console PAL_POSIX_Console;
#endif

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
		INamespace *rootNS;
		IMutableContainer *platformContainer;
		IAddressSpace *addressSpace;
		IBootEnvironment *BootEnvironment;
#if FEATURE_PAL_DIAGNOSTICS
		IPlatformDiagnostics *diagnostics;
#endif
#if FEATURE_CONSOLE
		PAL_POSIX_Console *console;
		LogLevel logLevel;
#endif
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

#if FEATURE_PAL_DIAGNOSTICS
struct PAL_POSIX_PlatformDiagnostics
{
	IObject Object;
	IPlatformDiagnostics PlatformDiagnostics;
	IWriteChannel WriteChannel;
};
#endif /*FEATURE_PAL_DIAGNOSTICS*/

#if FEATURE_CONSOLE
struct PAL_POSIX_Console
{
	IObject Object;
	IWriteChannel WriteChannel;
	struct
	{
		bool started;
	} data;
};
#endif /*FEATURE_CONSOLE*/

# ifdef __cplusplus
extern "C" {
# endif

void PAL_POSIX_panic(const char *string);
void PAL_POSIX_init(void);
void PAL_POSIX_Platform_init(void);
void PAL_POSIX_Platform_setAddressSpace(IAddressSpace *mm);
void PAL_POSIX_AddressSpace_init(void);

# if FEATURE_PAL_DIAGNOSTICS
void PAL_POSIX_PlatformDiagnostics_init(void);
extern void PAL_POSIX_PlatformDiagnostics_log(IPlatformDiagnostics *me, LogLevel level, const char *str);
void PAL_POSIX_Platform_setDiagnostics(IPlatformDiagnostics *diag);
# endif /*FEATURE_PAL_DIAGNOSTICS*/

# if FEATURE_CONSOLE
void PAL_POSIX_Console_init(void);
void PAL_POSIX_Platform_setConsole(PAL_POSIX_Console *console);
size_t PAL_POSIX_Console_send(IWriteChannel *self, const uint8_t *buf, size_t nbytes);
size_t PAL_POSIX_Console_logf(PAL_POSIX_Console *self, LogLevel level, const char *format, ...);
size_t PAL_POSIX_Console_vlogf(PAL_POSIX_Console *self, LogLevel level, const char *format, va_list args);
# endif /*FEATURE_CONSOLE*/

extern PHASE PAL_POSIX_phase;

# if EXEC_BUILD_RELEASE || !FEATURE_PAL_DIAGNOSTICS
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
# else /*EXEC_BUILD_RELEASE || !FEATURE_PAL_DIAGNOSTICS*/
extern void PAL_POSIX_PlatformDiagnostics__logf(LogLevel level, const char *str, ...);
#  define PALLOGF(X)                    PAL_POSIX_PlatformDiagnostics__logf X
#  define PALLog(level, str)            PAL_POSIX_PlatformDiagnostics_log(NULL, level, str)
#  define PALDebug(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG, str)
#  define PALDebug2(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG2, str)
#  define PALDebug7(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG7, str)
#  if FEATURE_TRACE
#   define PALTrace(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_TRACE, str)
#  else
#   define PALTrace(str)                /* FEATURE_TRACE disabled PALTrace() */
#  endif
#  define PALCondition(str)             PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_CONDITION, str)
# endif /*!EXEC_BUILD_RELEASE && FEATURE_PAL_DIAGNOSTICS*/

# ifdef __cplusplus
}
# endif

#endif /*!P_POSIX_H_*/