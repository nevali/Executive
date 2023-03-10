/* Executive Microkernel
 * PrivateHeaders/Executive/Internal/Runtime.h
 *   Defines the internal runtime APIs available to the executive. These are
 *   mapped to the subset of RtXXX() APIs that are included in the Executive's
 *   Mini-Runtime
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
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

#ifndef EXECUTIVE_INTERNAL_RUNTIME_H_
# define EXECUTIVE_INTERNAL_RUNTIME_H_ 1

# ifndef RUNTIME_BUILD_EXEC
#  define RUNTIME_BUILD_EXEC           1
# endif

# include <Executive/UUID.h>
# include <Executive/IPlatformDiagnostics.h>
# include <Runtime/Runtime.h>

# include <Executive/IAllocator.h>
# include <Executive/IAddressSpace.h>

/* This needs to be a better-defined interface */
EXTERN_C IAllocator *RtAllocator_create(IAddressSpace *addressSpace) RUNTIME_PRIVATE__(RtAllocator_create);

# define ExPanic(str)                  Executive_panic(str)
# define ExAlloc(nbytes)               RtMemAlloc(nbytes)
# define ExReAlloc(ptr, nbytes)        RtMemReAlloc(ptr, nbytes)
# define ExFree(ptr)                   RtMemFree(ptr)
# define ExYield()                     RtYield()
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
#  if FEATURE_TRACE
#   define EXTRACEF(P)                  RtTraceFormat P
#   define ExTrace(str)                 RtLog(LOG_TRACE, str)
#  else
#   define EXTRACEF(P)                 /* FEATURE_TRACE disabled EXTRACEF() */
#   define ExTrace(str)                /* FEATURE_TRACE disabled ExTrace() */
#  endif
#  define EXDBGF(P)                    RtDebugFormat P
#  define ExDebug(str)				   RtLog(LOG_DEBUG, str)
# endif


# if EXEC_BUILD_RELEASE
/* these are no-ops only in release builds */
#  define EXLOGF(P)
/* not actually a no-op to allow for the expression to have side-effets*/
#  define ExAssert__(cond, file, line) (void) (cond)
# else
#  define EXLOGF(P)                    RtLogFormat P
#  define ExAssert__(cond, file, line)  if(!(cond)) { ExAssertPanic__(#cond, file, line); }
#  define ExAssertPanic__(cond, file, line) RtPanic("ASSERTION FAILED: " cond " at " file ":" line)
# endif
#  define ExAssert(cond)               ExAssert__(cond, __FILE__, STR__(__LINE__))

/* This does not belong here */
EXTERN_C STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);

#endif /*EXECUTIVE_INTERNAL_RUNTIME_H_*/