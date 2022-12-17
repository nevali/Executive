#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#if !EXEC_BUILD_RELEASE

#include "p_Runtime.h"
#include "../p_Executive.h"

extern int rpl_vsnprintf(char *str, size_t size, const char *format, va_list args);

static char logbuf[1024];

void
Executive_LogFormat(LogLevel level, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	rpl_vsnprintf(logbuf, sizeof(logbuf), format, args);
	if(executive.data.diagnostics)
	{
		IPlatformDiagnostics_log(executive.data.diagnostics, level, logbuf);
	}
}

#endif /*!EXEC_BUILD_RELEASE*/

#ifndef NDEBUG

void
Executive_DebugFormat(LogLevel level, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	rpl_vsnprintf(logbuf, sizeof(logbuf), format, args);
	if(executive.data.diagnostics)
	{
		IPlatformDiagnostics_log(executive.data.diagnostics, level, logbuf);
	}
}

void
Executive_TraceFormat(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	rpl_vsnprintf(logbuf, sizeof(logbuf), format, args);
	if(executive.data.diagnostics)
	{
		IPlatformDiagnostics_log(executive.data.diagnostics, LOG_TRACE, logbuf);
	}
}

#endif /*!NDEBUG*/
