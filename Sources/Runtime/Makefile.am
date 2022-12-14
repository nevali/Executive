## Executive Microkernel
##   Runtime support

DIST_SUBDIRS = snprintf arm64

noinst_LTLIBRARIES = libRuntime.Release.la libRuntime.Free.la libRuntime.Debug.la libRuntimeThirdParty.la

libRuntime_Release_la_SOURCES = \
	p_Runtime.h \
	UUID.c Strings.c Memory.c Debug.c
libRuntime_Release_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${RELEASE_CPPFLAGS}
libRuntime_Release_la_LIBADD = libRuntimeThirdParty.la

libRuntime_Free_la_SOURCES = $(libRuntime_Release_la_SOURCES)
libRuntime_Free_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${FREE_CPPFLAGS}
libRuntime_Free_la_LIBADD = libRuntimeThirdParty.la

libRuntime_Debug_la_SOURCES = $(libRuntime_Release_la_SOURCES)
libRuntime_Debug_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${DEBUG_CPPFLAGS}
libRuntime_Debug_la_LIBADD = libRuntimeThirdParty.la

libRuntimeThirdParty_la_SOURCES = \
	p_Runtime.h \
	dlmalloc/malloc.h dlmalloc/malloc.c \
	snprintf/snprintf.c
