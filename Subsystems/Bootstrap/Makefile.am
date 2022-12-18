## Executive Microkernel
## Bootstrap subsystem
##

AM_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

## Build a resident version of the subsystem that will be linked into the
## Executive binary

noinst_LTLIBRARIES = libBootstrap.Resident.la

libBootstrap_Resident_la_SOURCES = p_Bootstrap.h \
	Bootstrap.c Sentinel.c

