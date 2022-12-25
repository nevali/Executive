## Executive Microkernel
## Simulator infrastructure
##   Builds a version of the Runtime framework that embeds a copy of the
##   Executive with a simulated PAL and supporting infrastructure

AM_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

DIST_SUBDIRS = PAL

lib_LTLIBRARIES =

if BUILD_SIMULATOR

SUBDIRS = PAL .

lib_LTLIBRARIES += libRuntime.Simulator.la

endif

libRuntime_Simulator_la_SOURCES = p_Simulator.h \
	Startup.c SystemCall.c ../Sources/entrypoint.c
libRuntime_Simulator_la_LIBADD = \
	$(top_builddir)/Frameworks/Runtime/libSimRuntime.la \
	$(top_builddir)/Sources/libExecutiveServices.la \
	PAL/libPAL.la
libRuntime_Simulator_la_LDFLAGS = -avoid-version
