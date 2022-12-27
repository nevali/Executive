/* Executive Microkernel
 * SLEEP
 *  Do nothing for a (computationally) long time
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include <Runtime/Runtime.h>

#include <Executive/ILink.h>

STATUS
mainThread(IThread *self)
{
	STATUS status;

#ifdef EXEC_BUILD_CONFIG
	RtLog(LOG_NOTICE, PRODUCT_FULLNAME " SLEEP [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	RtLog(LOG_DEBUG, PRODUCT_FULLNAME " SLEEP [build " PRODUCT_BUILD_ID_STR "]");
#endif
	if(E_SUCCESS != (status = IThread_sleepSeconds(self, 60)))
	{
		RtLogFormat(LOG_ERROR, "%s: failed to sleep: %s", RtStatusName(status), RtStatusMessage(status));
		return status;
	}
	return E_SUCCESS;
}
