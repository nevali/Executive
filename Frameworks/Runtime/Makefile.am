## Executive Microkernel
## Runtime Framework
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

#SUBDIRS = IDL Headers ThirdParty Client .
SUBDIRS = Headers ThirdParty Client .

lib_LTLIBRARIES = libRuntime.la


noinst_LTLIBRARIES = libExecRuntime.la

# XXX -Wl,-nostdlib ?

## The ExecRuntime library contains the subset of the Runtime framework useable
## within the Executive

libExecRuntime_la_SOURCES = Memory.c Allocator.c Strings.c UUID.c Status.c Log.c
libExecRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1
libExecRuntime_la_LIBADD = ThirdParty/libRuntimeThirdParty.la Client/libRuntimeClientExec.la

libRuntime_la_SOURCES = $(libExecRuntime_la_SOURCES) Private.c
libRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_USER=1
libRuntime_la_LIBADD = ThirdParty/libRuntimeThirdParty.la Client/libRuntimeClient.la ../Executive/libExecutive.la
libRuntime_la_LDFLAGS = -no-undefined -avoid-version -rpath $(libdir)
