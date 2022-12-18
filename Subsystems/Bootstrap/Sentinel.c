#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

void
Bootstrap_Sentinel_mainThread(IThread *self)
{
	UNUSED__(self);

#if 0
	for(;;)
	{
		ExTrace("Bootstrap::Sentinel::mainThread(): Ping");
		ExYield();
	}
#endif
}
