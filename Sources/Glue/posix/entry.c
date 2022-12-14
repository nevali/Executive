/* Executive Microkernel
 *   POSIX Glue
 *   Provides a program entry-point for builds hosted on POSIX-like platforms
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

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#if HAVE_DLFCN_H
# include <dlfcn.h>
#endif

#include <Executive/Internal/Entry.h>
#include <PAL/PAL.h>

#ifndef EXEC_POSIX_PAL_DEFAULT
# warning EXEC_POSIX_PAL_DEFAULT is not set, a fallback value will be used
# define EXEC_POSIX_PAL_DEFAULT        "PAL.posix.so"
#endif

static struct ExecutiveEntryParameters params;

const char __glue_ident[] = "@(#) $Glue: posix [ " PACKAGE_STRING " build " PRODUCT_BUILD_ID_STR " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST " ] $";

#ifndef RTLD_LOCAL
# define RTLD_LOCAL                    0
#endif
#ifndef RTLD_FIRST
# define RTLD_FIRST                    0
#endif
#ifndef RTLD_NOW
# define RTLD_NOW                      0
#endif
#ifndef RTLD_NODELETE
# define RTLD_NODELETE                 0
#endif

int
main(int argc, char **argv, char **envp)
{
#if EXEC_BUILD_DYNAMIC
	const char *palName;
	void *palHandle;

	/* If this is a dynamic build of the Executive, targeting a Posix-like
	 * system, it means this module is responsible for locating and loading
	 * an appropriate PAL.
 	 *
	 * If the environment variable EXECUTIVE_PAL is set, then that's assumed to
	 * be the name of a file which can be passed to dlopen(), and will
	 * export a PAL_queryPlatformInterface symbol.
	 * 
	 * If not, we search for a PAL with a default compiled-in name, supplied
	 * by the configuration logic of the Posix PAL itself
	 */
	palName = getenv("EXECUTIVE_PAL");
	if(palName)
	{
		fprintf(stderr, "DEBUG: PAL set to '%s' via the EXECUTIVE_PAL environment variable\n", palName);
	}
	else
	{
		palName = EXEC_POSIX_PAL_DEFAULT;
		fprintf(stderr, "DEBUG: PAL defaulting to '%s'\n", palName);
	}
	palHandle = dlopen(palName, RTLD_LOCAL|RTLD_NOW|RTLD_NODELETE|RTLD_FIRST);
	if(!palHandle)
	{
		fprintf(stderr, "%s: PANIC: unable to load a Platform Adaptation Layer (PAL): %s\n", argv[0], dlerror());
		abort();
	}
	fprintf(stderr, "DEBUG: PAL '%s' opened as handle <%p>\n", palName, palHandle);
	params.PAL_metaClass = dlsym(palHandle, SYMNAME__("PAL", "metaClass", "0.0"));
	if(params.PAL_metaClass)
	{
		fprintf(stderr, "DEBUG: located <%s> at <%p>\n", SYMNAME__("PAL", "metaClass", "0.0"), params.PAL_metaClass);
	}
	else
	{
		fprintf(stderr, "%s: PANIC: unable to locate symbol <%s> in loaded PAL\n", argv[0], SYMNAME__("PAL", "metaClass", "0.0"));
		abort();
	}
#endif
	if(!params.PAL_metaClass && !PAL_metaClass)
	{
		/* Perform this check here because all the Executive can do without a
		 * PAL is silently relinquish control
		 */
		fprintf(stderr, "%s: PANIC: no PAL supplied by the dynamic loader\n", argv[0]);
		abort();
	}
	params.argc = argc;
	params.argv = argv;
	params.environ = envp;
	if(Executive_start == NULL)
	{
		fprintf(stderr, "%s: PANIC: cannot transfer control to the Executive\n", argv[0]);
		abort();
	}
	Executive_start(&params);
	fprintf(stderr, "%s: PANIC: control unexpectedly relinquished by Executive\n", argv[0]);
	abort();
}