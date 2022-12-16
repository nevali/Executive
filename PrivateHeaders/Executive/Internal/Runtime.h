#ifndef EXECUTIVE_INTERNAL_RUNTIME_H_
# define EXECUTIVE_INTERNAL_RUNTIME_H_ 1

# include <Executive/UUID.h>
# include <Executive/IPlatformDiagnostics.h>

typedef char UUIDBUF[42];

# define ExPanic(str)                  Executive_panic(str)
# define ExAlloc(nbytes)               Executive_alloc(nbytes)
# define ExReAlloc(ptr, nbytes)        Executive_realloc(ptr, nbytes)
# define ExFree(ptr)                   Executive_free(ptr)
# define ExYield()                     Executive_yield()
# define ExLog(level, str)             Executive_log(level, str)

# define STR__(x)                      STR2__(x)
# define STR2__(x)                     #x
# define ExNotice(str)				   ExLog(LOG_NOTICE, str)
# define ExCondition(str)              ExLog(LOG_CONDITION, str)

# define ExUuidEqual(a, b)             Executive_Uuid_equal(a, b)
# define ExUuidStr(uu, buf)            Executive_Uuid_string(uu, buf)
# define ExUuidCopy(dest, src)         Executive_Uuid_copy(dest, src)

# define ExStrDup(str)                 Executive_String_duplicate(str)
# define ExStrLen(str)                 Executive_String_length(str)
# define ExStrCopy(dest, dsize, src)   Executive_String_copy(dest, dsize, src)
# define ExStrLCopy(dest, dsize, src, srclen)   Executive_String_lcopy(dest, dsize, src, srclen)
# define ExStrEqual(a, b)              Executive_String_equal(a, b)

# define ExMemDup(base, len)           Executive_Memory_duplicate(base, len)
# define ExMemCopy(dest, src, len)     Executive_Memory_copy(dest, src, len)

# define ExStatusName(s)               Executive_Status_name(s)
# define ExStatusMsg(s)                Executive_Status_defaultMessage(s)
# define ExLogF                        Executive_LogFormat
# define ExLogCondition(s, context)    ExLogF(LOG_CONDITION, "%s: %s: %s", ExStatusName(s), context, ExStatusMsg(s))

# define ExMetaClass(clsid, iid, out)  Executive_metaClass(clsid, iid, (void **) (out))

# ifdef NDEBUG
/* these are no-ops in free and release builds*/
#  define EXTRACEF(P)
#  define EXDBGF(P)
#  define ExDebug(str)
#  define ExTrace(str)
# else
#  define EXTRACEF(P)                  Executive_TraceFormat
#  define EXDBGF(P)                    Executive_DebugFormat
#  define ExDebug(str)				   ExLog(LOG_DEBUG, str)
#  define ExTrace(str)				   ExLog(LOG_TRACE, str)
# endif


# if EXEC_BUILD_RELEASE
/* these are no-ops only in release builds */
#  define EXLOGF(P)
/* not actually a no-op to allow for the expression to have side-effets*/
#  define ExAssert__(cond, file, line) (void) (cond)
# else
#  define EXLOGF(P)                    Executive_LogFormat P
#  define ExAssert__(cond, file, line)  if(!(cond)) { ExAssertPanic__(#cond, file, line); }
#  define ExAssertPanic__(cond, file, line) ExPanic("ASSERTION FAILED: " cond " at " file ":" line)
# endif
#  define ExAssert(cond)               ExAssert__(cond, __FILE__, STR__(__LINE__))

# ifdef __cplusplus
extern "C" {
# endif

STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);

void Executive_panic(const char *str);
void Executive_log(int level, const char *str);
void *Executive_alloc(size_t nbytes);
void *Executive_realloc(void *ptr, size_t nbytes);
void Executive_free(void *ptr);
void Executive_yield(void);

int Executive_Uuid_equal(REFUUID a, REFUUID b);
size_t Executive_Uuid_string(REFUUID uuid, UUIDBUF buf);
void Executive_Uuid_copy(UUID *dest, REFUUID src);

void Executive_LogFormat(LogLevel level, const char *format, ...);
void Executive_DebugFormat(LogLevel level, const char *format, ...);
void Executive_TraceFormat(const char *format, ...);

size_t Executive_String_length(const char *str);
char *Executive_String_duplicate(const char *str);
const char *Executive_String_pos(const char *str, int ch);
size_t Executive_String_copy(char *dest, size_t dsize, const char *src);
size_t Executive_String_lcopy(char *dest, size_t dsize, const char *src, size_t srclen);
int Executive_String_equal(const char *a, const char *b);

void *Executive_Memory_duplicate(const void *src, size_t length);
void Executive_Memory_copy(void *dest, const void *src, size_t nbytes);

const char *Executive_Status_name(STATUS s);
const char *Executive_Status_defaultMessage(STATUS s);

# ifdef __cplusplus
}
# endif

#endif /*EXECUTIVE_INTERNAL_RUNTIME_H_*/