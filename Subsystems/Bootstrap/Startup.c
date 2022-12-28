#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "ProductInformation.h"
#endif

#include "p_Bootstrap.h"

Bootstrap_ResidentTask Bootstrap_startupTask;

void Bootstrap_Startup_mainThread(IThread *self)
{
	INamespace *ns;
	IPlatformDiagnostics *diag;

	IThread_ns(self, &IID_INamespace, (void **) &ns);
	INamespace_open(ns, "/System/Platform/Devices/Diagnostics", NULL, &IID_IPlatformDiagnostics, (void **) &diag);
	IPlatformDiagnostics_log(diag, PROGRESS_LOGLEVEL, PRODUCT_NAME_RELEASE " is starting up...");
	for(;;)
	{
#if FEATURE_TRACE && FEATURE_DEBUG_CONTEXTS
		IPlatformDiagnostics_log(diag, LOG_TRACE, "Bootstrap: Startup: tock");
#endif
		IThread_yield(self);
	}
}
