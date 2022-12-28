#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#if FEATURE_COOPERATIVE_TASKER

#include "p_CooperativeTasker.h"

#if FEATURE_BOOTPROGRESS
# define LOGLEVEL LOG_INFO
#else
# define LOGLEVEL LOG_DEBUG
#endif

void
Executive_CooperativeTasker_Sentinel_mainThread(IThread *self)
{
	ExLog(LOGLEVEL, "Sentinel task is now operational.");
	for(;;)
	{
#if FEATURE_TRACE && FEATURE_DEBUG_CONTEXTS
		ExLog(LOG_TRACE, "Sentinel: tick");
#endif
		IPlatform_nap(executive.data.platform);
		IThread_yield(self);
	}
}

#endif /*FEATURE_COOPERATIVE_TASKER*/
