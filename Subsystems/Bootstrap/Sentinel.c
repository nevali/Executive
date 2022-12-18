#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

Bootstrap_ResidentTask Bootstrap_sentintelTask;

void
Bootstrap_Sentinel_mainThread(IThread *self)
{
	for(;;)
	{
		IThread_yield(self);
	}
}
