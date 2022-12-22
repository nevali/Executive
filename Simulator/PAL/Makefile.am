## Executive Microkernel
## Simulator infrastructure
##   Builds a version of the Runtime framework that embeds a copy of the
##   Executive with a simulated PAL and supporting infrastructure

AM_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

noinst_LTLIBRARIES = libPAL.la

libPAL_la_SOURCES = p_PAL.h \
	BuildInformation.c panic.c \
	metaClass.c Platform.c PlatformDiagnostics.c \
	BootEnvironment.c \
	p_AddressSpace.h \
	AddressSpace.c Region.c Context.c
