/* Executive Microkernel
 * SysDump -- Dump the object directory
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <Runtime/Runtime.h>

/* XXX what should our native main() be? */

STATUS
mainThread(IThread *self)
{
	UNUSED__(self);

#ifdef EXEC_BUILD_CONFIG
	RtLog(LOG_NOTICE, PRODUCT_FULLNAME " " PACKAGE_NAME " [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	RtLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " [build " PRODUCT_BUILD_ID_STR "]");
#endif
	return E_SUCCESS;
}
