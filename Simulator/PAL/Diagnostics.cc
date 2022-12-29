#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_PAL.h"

using namespace PAL::Simulator;

EXTERN_C void
__cxa_pure_virtual(void)
{
	fprintf(stderr, "PAL::Simulator::Diagnostics:: C++ pure virtual method invoked\n");
	abort();
}

/* Constructor */
Diagnostics::Diagnostics():
#if EXEC_BUILD_RELEASE
	level_(LOG_INFO)
#elif EXEC_BUILD_DEBUG
	level_(LOG_DEBUG2)
#else
	level_(LOG_CONDITION)
#endif
{
#if FEATURE_PAL_DIAGNOSTICS
	setEnvironmentLogLevel();
#endif
}

/*PRIVATE*/
void
Diagnostics::setEnvironmentLogLevel(void)
{
	const char *level;
	size_t c;
	const struct { const char *name; LogLevel level; } levels[] = {
		{ "emerg", LOG_EMERGENCY },
		{ "emergency", LOG_EMERGENCY },
		{ "alert", LOG_ALERT },
		{ "crit", LOG_CRITICAL },
		{ "critical", LOG_CRITICAL },
		{ "info", LOG_INFO },
		{ "condition", LOG_CONDITION },
		{ "cond", LOG_CONDITION },
		{ "debug", LOG_DEBUG },
		{ "debug2", LOG_DEBUG2 },
		{ "debug6", LOG_DEBUG6 },
		{ "debug7", LOG_DEBUG7 },
		{ "trace", LOG_TRACE },
		{ NULL, LOG_INFO }
	};
	if(NULL != (level = getenv("SIMULATOR_LOGLEVEL")))
	{
		Platform::logf(LOG_DEBUG, "PAL::Simulator::Diagnostics: SIMULATOR_LOGLEVEL='%s'", level);
		for(c = 0; levels[c].name; c++)
		{
			if(!strcasecmp(levels[c].name, level))
			{
				level_ = levels[c].level;
				Platform::logf(LOG_INFO, "Diagnostic level set to '%s' (%d) via SIMULATOR_LOGLEVEL environment variable", level, levels[c].level);
				return;
			}
		}
		Platform::logf(LOG_WARNING, "Simulator: WARNING: unknown log level '%s'", level);
	}
}

/*PRIVATE*/
const char *
Diagnostics::logPrefix(LogLevel level)
{
	switch(level)
	{
		case LOG_EMERG:     return "\033[97;101mEMERGENCY\033[0m: \033[39;1m";
		case LOG_ALERT:     return "\033[91mALERT\033[0m:     \033[39;1;97m";
		case LOG_CRITICAL:  return "CRITICAL:  \033[39;1m";
		case LOG_ERROR:     return "ERROR:     \033[39;1m";
		case LOG_WARNING:   return "WARNING:   \033[39;1m";
		case LOG_NOTICE:    return "Note:      \033[39;1m";
		case LOG_INFO:      return "           ";
		/* all the below log levels are below zero and so for debugging purposes only */
		case LOG_CONDITION: return "\033[90m[Condition]";
		case LOG_DEBUG:     return "\033[90m(Debug:1)  ";
		case LOG_DEBUG2:    return "\033[90m(Debug:2)  ";
		case LOG_DEBUG3:    return "\033[90m(Debug:3)  ";
		case LOG_DEBUG4:    return "\033[90m(Debug:4)  ";
		case LOG_DEBUG5:    return "\033[90m(Debug:5)  ";
		case LOG_DEBUG6:    return "\033[90m(Debug:6)  ";
		case LOG_DEBUG7:    return "\033[90m(Debug:7)  ";
		case LOG_TRACE:     return "\033[90m[Trace]    ";
	}
	return NULL;
}

/*INTERNAL*/
void
Diagnostics::vlogf(LogLevel level, const char *str, va_list args)
{
#if FEATURE_PAL_DIAGNOSTICS
	const char *prefix;

	if(level >= level_)
	{
		prefix = logPrefix(level);
		if(prefix)
		{
			fprintf(stderr, "%s ", prefix);
		}
		else
		{
			fprintf(stderr, "<%d> ", level);
		}
		vfprintf(stderr, str, args);
		fputs("\033[0m\n", stderr);
	}
#else
	UNUSED__(level);
	UNUSED__(str);
	UNUSED__(args);
#endif
}

/*INTERNAL*/
void
Diagnostics::panic(PHASE phase, const char *str)
{
	fprintf(stderr, "\n\n\n"
		"++===================================================================++\n"
		"||\033[97;101m      S Y S T E M   P A N I C   D U R I N G   P H A S E   %04x     \033[0m||\n"
		"++===================================================================++\n\n"
		"%s\n\n"
		 "++===================================================================++\n"
		"||\033[97;101m      S Y S T E M   P A N I C   D U R I N G   P H A S E   %04x     \033[0m||\n"
		"++===================================================================++\n\n",
		phase, str, phase);
	abort();
}

STATUS
Diagnostics::queryInterface(REFUUID riid, void **ptr)
{
	Platform::tracef("PAL::Simulator::Diagnostics::queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(riid));
	if(!memcmp(&riid, &IID_IObject, sizeof(UUID)))
	{
		if(ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = static_cast<IObject *>(static_cast<IPlatformDiagnostics *>(this));
		}
		return E_SUCCESS;
	}
	if(!memcmp(&riid, &IID_IPlatformDiagnostics, sizeof(UUID)))
	{
		if(ptr)
		{
			*ptr = static_cast<IPlatformDiagnostics *>(this);
		}
		return E_SUCCESS;
	}
	if(!memcmp(&riid, &IID_IWriteChannel, sizeof(UUID)))
	{
		if(ptr)
		{
			*ptr = static_cast<IWriteChannel *>(this);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

/* IPlatformDiagnostics */

void
Diagnostics::log(LogLevel level, const char *str)
{
#if FEATURE_PAL_DIAGNOSTICS
	const char *prefix;

	if(level >=level_)
	{
		prefix = logPrefix(level);
		if(prefix)
		{
			fprintf(stderr, "%s %s\033[0m\n", prefix, str);
		}
		else
		{
			fprintf(stderr, "<%d> %s\033[0m\n", level, str);
		}
	}
#else
	UNUSED__(level);
	UNUSED__(str);
#endif
}

/* IWriteChannel */

size_t
Diagnostics::send(const uint8_t *buf, size_t nbytes)
{
	fprintf(stderr, "\033[0;33m");
	fwrite((void *) buf, nbytes, 1, stderr);
	fprintf(stderr, "\033[0m");
	return nbytes;
}

size_t
Diagnostics::write(const char *str)
{
	fprintf(stderr, "\033[0;33m%s\033[0m", str);
	return strlen(str);
}

size_t
Diagnostics::writeLn(const char *str)
{
	fprintf(stderr, "\033[0;33m%s\033[0m\n", str);
	return strlen(str);
}
