## Executive Microkernel
## Sources/Glue/posix/Makefile.am
##   Provides an entry-point compiled into hosted builds for Posix-like systems

EXTRA_DIST = config.ac

noinst_LTLIBRARIES =

GLUESRC = entry.c

include $(top_srcdir)/Makefiles/Glue.mk

noinst_PROGRAMS = GlueTest

GlueTest_SOURCES = entry.c test-stubs.c
GlueTest_CPPFLAGS = ${AM_CPPFLAGS} -DEXEC_BUILD_DYNAMIC=1
