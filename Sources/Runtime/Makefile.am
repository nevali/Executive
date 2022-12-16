## Executive Microkernel
##   Runtime support

DIST_SUBDIRS = snprintf arm64

noinst_LTLIBRARIES = libRuntime.la libRuntimeThirdParty.la

libRuntime_la_SOURCES = \
	p_Runtime.h \
	UUID.c Strings.c Memory.c Debug.c Diagnostics.c
libRuntimeThirdParty_la_SOURCES = \
	p_Runtime.h \
	snprintf/snprintf.c

libRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}
libRuntime_la_LIBADD = libRuntimeThirdParty.la
