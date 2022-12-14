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
	init_once = 1;
#ifdef EXEC_BUILD_CONFIG
	PALLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - POSIX Platform Adaptation Layer [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	PALLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - POSIX Platform Adaptation Layer [build " PRODUCT_BUILD_ID_STR "]");
#endif
	PAL_POSIX_Platform_init();
	PAL_POSIX_MemoryManager_init();
	PAL_POSIX_PlatformDiagnostics_init();
}
