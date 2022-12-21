#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <Executive/Linkage.h>

#undef EXEC_LINKAGE__
#define EXEC_LINKAGE__(name, version) SYM__("EXECUTIVE", name, version) WEAK_IMPORT__ WEAK_STUB__

#include <Executive/Internal/Entry.h>
#include <Executive/SystemCall.h>

void
Executive_start(struct ExecutiveEntryParameters *params)
{
	UNUSED__(params);
}

int
ExSystemCall(int od, int method, ...)
{
	UNUSED__(od);
	UNUSED__(method);

	return E_NOTIMPL;
}
