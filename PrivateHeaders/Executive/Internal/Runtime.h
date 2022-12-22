#ifndef EXECUTIVE_INTERNAL_RUNTIME_H_
# define EXECUTIVE_INTERNAL_RUNTIME_H_ 1

# include <Executive/UUID.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Runtime/Runtime.h>

# include <Executive/IAllocator.h>
# include <Executive/IAddressSpace.h>

extern IAllocator *RtAllocator_create(IAddressSpace *addressSpace);

# define ExPanic(str)                  Executive_panic(str)
# define ExAlloc(nbytes)               RtMemAlloc(nbytes)
# define ExReAlloc(ptr, nbytes)        RtMemReAlloc(ptr, nbytes)
# define ExFree(ptr)                   RtMemFree(ptr)
# define ExYield()                     Executive_yield()
# define ExLog(level, str)             RtLog(level, str)

# define STR__(x)                      STR2__(x)
# define STR2__(x)                     #x
# define ExNotice(str)				   RtLog(LOG_NOTICE, str)
# define ExCondition(str)              RtLog(LOG_CONDITION, str)

# define ExUuidEqual(a, b)             RtUuidEqual(a, b)
# define ExUuidStr(uu, buf)            RtUuidStr(uu, buf)
# define ExUuidCopy(dest, src)         RtUuidCopy(dest, src)

# define ExStrDup(str)                 RtStrDup(str)
# define ExStrLen(str)                 RtStrLen(str)
# define ExStrCopy(dest, dsize, src)   RtStrCopy(dest, dsize, src)
# define ExStrLCopy(dest, dsize, src, srclen)   RtStrLCopy(dest, dsize, src, srclen)
# define ExStrEqual(a, b)              RtStrEqual(a, b)
# define ExStrLEqual(a, b, max)        RtStrLEqual(a, b, max)

# define ExMemDup(base, len)           RtMemDup(base, len)
# define ExMemCopy(dest, src, len)     RtMemCopy(dest, src, len)

# define ExStatusName(s)               RtStatusName(s)
# define ExStatusMsg(s)                RtStatusMessage(s)
# define ExLogCondition(s, context)    RtLogFormat(LOG_CONDITION, "%s: %s: %s", ExStatusName(s), context, ExStatusMsg(s))

# define ExMetaClass(clsid, iid, out)  Executive_metaClass(clsid, iid, (void **) (out))

# ifdef NDEBUG
/* these are no-ops in free and release builds*/
#  define EXTRACEF(P)
#  define EXDBGF(P)
#  define ExDebug(str)
#  define ExTrace(str)
# else
#  define EXTRACEF(P)                  RtTraceFormat P
#  define EXDBGF(P)                    RtDebugFormat P
#  define ExDebug(str)				   RtLog(LOG_DEBUG, str)
#  define ExTrace(str)				   RtLog(LOG_TRACE, str)
# endif


# if EXEC_BUILD_RELEASE
/* these are no-ops only in release builds */
#  define EXLOGF(P)
/* not actually a no-op to allow for the expression to have side-effets*/
#  define ExAssert__(cond, file, line) (void) (cond)
# else
#  define EXLOGF(P)                    RtLogFormat P
#  define ExAssert__(cond, file, line)  if(!(cond)) { ExAssertPanic__(#cond, file, line); }
#  define ExAssertPanic__(cond, file, line) ExPanic("ASSERTION FAILED: " cond " at " file ":" line)
# endif
#  define ExAssert(cond)               ExAssert__(cond, __FILE__, STR__(__LINE__))

EXTERN_C STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);

EXTERN_C void Executive_panic(const char *str);
EXTERN_C void Executive_yield(void);

#endif /*EXECUTIVE_INTERNAL_RUNTIME_H_*/