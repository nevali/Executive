#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <Executive/Internal/Entry.h>
#include <Executive/Internal/Resident.h>
#include <PAL/PAL.h>

static struct ExecutiveEntryParameters params;

const char sim_ident__[] = "@(#) $Simulator: [ " PACKAGE_STRING " build " PRODUCT_BUILD_ID_STR " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST " ] $";

Executive_Resident_Object *
Executive_Resident_objects(void)
{
	return NULL;
}


int
main(int argc, char **argv, char **envp)
{
	params.flags = EEF_SIMULATOR|EEF_HAVE_ARGS|EEF_HAVE_ENVIRON;
	params.argc = argc;
	params.argv = argv;
	params.environ = envp;
	Executive_start(&params);
	fprintf(stderr, "%s: PANIC: control unexpectedly relinquished by Executive\n", argv[0]);
	abort();
}
