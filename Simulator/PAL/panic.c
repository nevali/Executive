#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#include <stdlib.h>

void
PAL_panic(const char *string)
{
	PALLog(LOG_EMERGENCY, string);
	fprintf(stderr, "\n\n\n"
		 "++===================================================================++\n"
		"||      S Y S T E M   P A N I C   D U R I N G   P H A S E   %04x     ||\n"
		"++===================================================================++\n\n"
		"%s\n\n"
		 "++===================================================================++\n"
		"||      S Y S T E M   P A N I C   D U R I N G   P H A S E   %04x     ||\n"
		"++===================================================================++\n\n",
		PAL_POSIX_phase, string, PAL_POSIX_phase);
	abort();
}
