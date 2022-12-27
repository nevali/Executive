#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Bootstrap.h"

Bootstrap_ResidentTask Bootstrap_sentintelTask;

void
Bootstrap_Sentinel_mainThread(IThread *self)
{
	INamespace *ns;
	IPlatformDiagnostics *diag;

	IThread_ns(self, &IID_INamespace, (void **) &ns);
	INamespace_open(ns, "/System/Platform/Devices/Diagnostics", NULL, &IID_IPlatformDiagnostics, (void **) &diag);
	IPlatformDiagnostics_log(diag, LOG_INFO, "Bootstrap: Sentinel: first CPU started");
	for(;;)
	{
#if FEATURE_TRACE
		IPlatformDiagnostics_log(diag, LOG_TRACE, "Bootstrap: Sentinel: tick");
#endif
		IThread_yield(self);
	}
}
