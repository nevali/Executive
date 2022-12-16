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
	PALLOGF((LOG_DEBUG, "initialising PAL metaclasses"));
	PAL_POSIX_Platform_init();
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX = %p, <IObject> = %p", &(PAL_POSIX_platform), &(PAL_POSIX_platform.Object)));
	PAL_POSIX_MemoryManager_init();
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX::memoryManager<IMemoryManager> = %p", PAL_POSIX_platform.data.memoryManager));
	PAL_POSIX_PlatformDiagnostics_init();
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX::diagnostics<IPlatformDiagnostics> = %p", PAL_POSIX_platform.data.diagnostics));
	PALDebug7("PAL::POSIX::init(): early initialisation complete");
}
