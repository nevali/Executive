#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#include <stdlib.h>

void
PAL_panic(const char *string)
{
	PALLog(LOG_EMERGENCY, string);
	abort();
}
