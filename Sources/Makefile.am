## Executive Microkernel
##  Sources/Makefile.am
##  Build the Executive

## Copyright 2015-2022 Mo McRoberts.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##      http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.

SUBDIRS = Glue Runtime Allocator Classes Directory .

sbin_PROGRAMS =
noinst_LTLIBRARIES = libExecutiveServices.la
CLEANFILES =
EXTRA_DIST = entrypoint.c

ENTRYPOINT = entrypoint.c

## the ExecutiveServices convenience library contains most of the logic
## of the microkernel itself -- it and the Glue constitute the Executive
## itself (but requires a PAL to function)

libExecutiveServices_la_SOURCES = p_Executive.h \
	Executive.c BootEnvironment.c \
	CooperativeTasker.c Descriptor.c BootstrapTask.c \
	UUIDs.c
libExecutiveServices_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}
libExecutiveServices_la_LIBADD = Runtime/libRuntime.la Classes/libClasses.la Directory/libDirectory.la Allocator/libAllocator.la

$(top_builddir)/Sources/libExecutiveServices.la: libExecutiveServices.la

# The Executive and PAL can be built in a number of different ways, depending
# upon the target platform/bootloader/host operating system (as appropriate)
# capabilities:
#
#  Dynamic      Dynamic linking/loading is available; the Executive can search
#               for an appropriate PAL using the services provided to it
#
#  Modular      The bootloader or host operating system arranges for the
#               Executive and the correct PAL to be loaded, which doesn't need
#               to specified in advance
#
#  Targeted     The Executive and a specific PAL are either statically or
#               dynamically linked together at build time
#
#  Monolith     The Executive, a specific PAL, and other executables are
#               linked together at build time

include $(top_srcdir)/Makefiles/Executive.Dynamic.mk
include $(top_srcdir)/Makefiles/Executive.Modular.mk

# Monolith builds are performed by the Makefile at the root, after everything else
# has been built
