## Executive Microkernel
## System Framework
##   This framework provides low-level user-space APIs to applications, via
##   the Executive's system call mechanism

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

DIST_SUBDIRS = c99-snprintf dlmalloc

SUBDIRS =

noinst_LTLIBRARIES = libRuntimeThirdParty.la

libRuntimeThirdParty_la_SOURCES = config.h \
	c99-snprintf/snprintf.c \
	dlmalloc/malloc.h dlmalloc/malloc.c

# XXX GCC/clang-only
libRuntimeThirdParty_la_CPPFLAGS = @AM_CPPFLAGS@ -Wno-empty-body
