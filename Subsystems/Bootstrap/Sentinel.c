#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

extern void Executive_Directory_dump(IContainer *me);

extern void abort(void);

void
Executive_Sentinel_mainThread(IThread *self)
{
	UNUSED__(self);

	for(;;)
	{
		ExTrace("Bootstrap::Sentinel::mainThread(): Ping");
		ExYield();
	}
}
