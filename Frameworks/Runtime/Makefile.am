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

SUBDIRS = Headers ThirdParty Client Server UUIDs .

lib_LTLIBRARIES = libRuntime.la


noinst_LTLIBRARIES = libExecRuntime.la

if BUILD_SIMULATOR

noinst_LTLIBRARIES += libSimRuntime.la

endif

# XXX -Wl,-nostdlib ?

## The ExecRuntime library contains the subset of the Runtime framework useable
## within the Executive

libExecRuntime_la_SOURCES = Memory.c Allocator.c Strings.c UUID.c Status.c Log.c Namespace.c Task.c
libExecRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1
libExecRuntime_la_LIBADD = \
	ThirdParty/libExecRuntimeThirdParty.la \
	Server/libExecRuntimeServer.la \
	../Executive/UUIDs/libExecutiveUUIDs.la
libExecRuntime_la_LDFLAGS = -export-symbols-regex '^_?(EXECUTIVE__|IID_|CLSID_)'

## The standard runtime

libRuntime_la_SOURCES = $(libExecRuntime_la_SOURCES) Private.c
libRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_USER=1
libRuntime_la_LIBADD = \
	ThirdParty/libRuntimeThirdParty.la \
	Client/libRuntimeClient.la \
	UUIDs/libRuntimeUUIDs.la \
	../Executive/libExecutive.la
libRuntime_la_LDFLAGS = -no-undefined -avoid-version -rpath $(libdir) -export-symbols-regex '^_?(RUNTIME__|IID_|CLSID_)'

## The Simulator variant replaces the Executive system call mechanism with a
## simulated implementation, primarily to aid in low-level development and
## testing

libSimRuntime_la_SOURCES = $(libRuntime_la_SOURCES)
libSimRuntime_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_SIMULATOR=1
libSimRuntime_la_LIBADD = \
	ThirdParty/libSimRuntimeThirdParty.la \
	Client/libRuntimeClient.la \
	UUIDs/libRuntimeUUIDs.la
libSimRuntime_la_LDFLAGS = -export-symbols-regex '^_?(SIMULATOR__|IID_|CLSID_)'
