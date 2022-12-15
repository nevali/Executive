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

SUBDIRS = DeveloperTools IDL Headers PrivateHeaders Stubs Sources PAL Subsystems .

EXTRA_DIST = README.md LICENSE-2.0 Dockerfile docker-bake.hcl

## If targeted or monolith build were requested, do so here, after everything
## else has been built

sbin_PROGRAMS =
CLEANFILES =

ENTRYPOINT = Sources/entrypoint.c

include $(top_srcdir)/Makefiles/Executive.Monolith.mk
include $(top_srcdir)/Makefiles/Executive.Targeted.mk
