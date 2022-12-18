#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

Bootstrap_ResidentTask Bootstrap_startupTask;

void Bootstrap_Startup_mainThread(IThread *self)
{
	UNUSED__(self);
}

