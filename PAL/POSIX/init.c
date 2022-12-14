#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

static int init_once;

void
PAL_POSIX_init(void)
{
	if(init_once)
	{
		return;
	}
	PALLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - POSIX Platform Adaptation Layer [build " PRODUCT_BUILD_ID_STR "]");
	init_once = 1;
	PAL_POSIX_Platform_init();
	PAL_POSIX_MemoryManager_init();
	PAL_POSIX_PlatformDiagnostics_init();
}
