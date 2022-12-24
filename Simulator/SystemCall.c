#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <stdio.h>

#include <Executive/SystemCall.h>

int
ExSystemCall(int descriptor, int method, ...)
{
	fprintf(stderr, "Simulator: ExSystemCall(%d, %d, ...)\n", descriptor, method);

	return E_NOTIMPL;
}