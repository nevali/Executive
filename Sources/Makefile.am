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

SUBDIRS = Executive Runtime Allocator Classes Directory CooperativeTasker \
	Coordinator Despatch Subsystems .

sbin_PROGRAMS =
noinst_LTLIBRARIES = libEntrypoint.la libExecutiveServices.la
noinst_PROGRAMS = Executive.lo
CLEANFILES =
EXTRA_DIST = entrypoint.c

ENTRYPOINT = entrypoint.c

libEntrypoint_la_SOURCES = entrypoint.c
libEntrypointServices_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}

## the ExecutiveServices convenience library contains most of the logic
## of the microkernel itself -- it and the Glue constitute the Executive
## itself (but requires a PAL to function)

libExecutiveServices_la_SOURCES = p_Executive.h \
	BootEnvironment.c UUIDs.c
libExecutiveServices_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}
libExecutiveServices_la_LIBADD = \
	Executive/libExecutive.la \
	Runtime/libRuntime.la \
	Classes/libClasses.la \
	Directory/libDirectory.la \
	CooperativeTasker/libCooperativeTasker.la \
	Subsystems/libSubsystems.la \
	Allocator/libAllocator.la

## Compile the core of the Executive (i.e., the entrypoint and the Executive
## Services convenience library) into a single combined object

Executive_lo_SOURCES =
Executive_lo_LDADD = libEntrypoint.la libExecutiveServices.la
Executive_lo_LDFLAGS = -r
Executive_lo_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(LD) $(Executive_lo_LDFLAGS) -o $@
