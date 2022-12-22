## Executive Microkernel
## Top-level Makefile

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

ACLOCAL_AMFLAGS = -I M4

SUBDIRS = DeveloperTools Frameworks PrivateHeaders Sources Simulator Glue PAL Subsystems .

EXTRA_DIST = README.md LICENSE-2.0 Dockerfile docker-bake.hcl

## If targeted or monolith build were requested, do so here, after everything
## else has been built

sbin_PROGRAMS =
CLEANFILES =

ENTRYPOINT = Sources/entrypoint.c

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
include $(top_srcdir)/Makefiles/Executive.Monolith.mk
include $(top_srcdir)/Makefiles/Executive.Targeted.mk
