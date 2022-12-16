#ifndef P_MEMORYMANAGER_H_
# define P_MEMORYMANAGER_H_           1

/* File I/O, host memory management */
# include <unistd.h>
/* mmap() */
# include <sys/mman.h>
/* memcmp() */
# include <string.h>
/* calloc(), free() */
# include <stdlib.h>

# include <PAL/PAL.h>

typedef union PAL_POSIX_MemoryManager PAL_POSIX_MemoryManager;
typedef union PAL_POSIX_Region PAL_POSIX_Region;

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

extern void PAL_POSIX_Platform_setMemoryManager(IMemoryManager *mm);

extern void PAL_POSIX_MemoryManager_init(void);
extern int PAL_POSIX_Region_create(PAL_POSIX_MemoryManager *mm, RegionFlags flags, IRegionHolder *owner, void *ptr, size_t size, PAL_POSIX_Region **out);

#endif /*!P_MEMORYMANAGER_H_*/