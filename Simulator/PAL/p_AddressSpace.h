#ifndef P_ADDRESSSPACE_H_
# define P_ADDRESSSPACE_H_             1

/* File I/O, host memory management */
# include <unistd.h>
/* mmap() */
# include <sys/mman.h>
/* memcmp() */
# include <string.h>
/* calloc(), free() */
# include <stdlib.h>
/* sigsetjmp, etc. */
# include <setjmp.h>
# include <signal.h>

# include <PAL/PAL.h>

# if !defined(SA_ONSTACK) && defined(SV_ONSTACK)
#  define SA_ONSTACK                   SV_ONSTACK
# endif
# if !defined(SS_DISABLE) && defined(SA_DISABLE)
#  define SS_DISABLE                   SA_DISABLE
# endif

typedef union PAL_POSIX_AddressSpace PAL_POSIX_AddressSpace;
typedef union PAL_POSIX_Region PAL_POSIX_Region;
typedef union PAL_POSIX_Context PAL_POSIX_Context;

union PAL_POSIX_AddressSpace
{
	IAddressSpace AddressSpace;
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
		PAL_POSIX_AddressSpace *mm;
		IRegionHolder *holder;
		RegionFlags flags;
		uint8_t *base;
		size_t count;
	} data;
};

union PAL_POSIX_Context
{
	IContext Context;
	IObject Object;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		PAL_POSIX_AddressSpace *addressSpace;
		IThread *thread;
		ThreadEntrypoint entry;
		char *stackLow;
		char *stackHigh;
		jmp_buf jb;
	} data;
};

# ifdef NDEBUG
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
extern void PAL_POSIX_PlatformDiagnostics_log(IPlatformDiagnostics *me, LogLevel level, const char *str);
extern void PAL_POSIX_PlatformDiagnostics__logf(LogLevel level, const char *str, ...);
#  define PALLOGF(X)                    PAL_POSIX_PlatformDiagnostics__logf X
#  define PALLog(level, str)            PAL_POSIX_PlatformDiagnostics_log(NULL, level, str)
#  define PALDebug(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG, str)
#  define PALDebug2(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG2, str)
#  define PALDebug7(str)                PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_DEBUG7, str)
#  define PALTrace(str)                 PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_TRACE, str)
#  define PALCondition(str)             PAL_POSIX_PlatformDiagnostics_log(NULL, LOG_CONDITION, str)
# endif

extern void PAL_POSIX_Platform_setAddressSpace(IAddressSpace *mm);

extern void PAL_POSIX_AddressSpace_init(void);
extern int PAL_POSIX_Region_create(PAL_POSIX_AddressSpace *mm, RegionFlags flags, IRegionHolder *owner, void *ptr, size_t size, PAL_POSIX_Region **out);

extern PAL_POSIX_Context *PAL_POSIX_Context_create(PAL_POSIX_AddressSpace *addressSpace);
extern void PAL_POSIX_Context_setup(PAL_POSIX_Context *self);

#endif /*!P_ADDRESSSPACE_H_*/