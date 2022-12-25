/* Executive Microkernel
 * SYSINFO
 *  Report information about the system
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include <Runtime/Runtime.h>

/* XXX what should our native main() be? */

STATUS
mainThread(IThread *self)
{
	UNUSED__(self);

#ifdef EXEC_BUILD_CONFIG
	RtLog(LOG_NOTICE, PRODUCT_FULLNAME " SYSINFO [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	RtLog(LOG_DEBUG, PRODUCT_FULLNAME " SYSINFO [build " PRODUCT_BUILD_ID_STR "]");
#endif
	return E_SUCCESS;
}
