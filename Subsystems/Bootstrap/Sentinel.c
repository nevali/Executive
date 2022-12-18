#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

void
Bootstrap_Sentinel_mainThread(IThread *self)
{
	for(;;)
	{
		IThread_yield(self);
	}
}
