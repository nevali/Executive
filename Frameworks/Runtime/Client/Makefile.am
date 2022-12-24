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

noinst_LTLIBRARIES = libExecRuntimeClient.la libRuntimeClient.la

if BUILD_SIMULATOR

noinst_LTLIBRARIES += libSimRuntimeClient.la

endif

libExecRuntimeClient_la_SOURCES = p_Client.h \
	IObject.c IAllocator.c IRegionHolder.c
libExecRuntimeClient_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1

libRuntimeClient_la_SOURCES = $(libExecRuntimeClient_la_SOURCES) \
	INamespace.c ITask.c IThread.c IAddressSpace.c IContext.c
libRuntimeClient_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_USER=1

libSimRuntimeClient_la_SOURCES = $(libRuntimeClient_la_SOURCES)
libSimRuntimeClient_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_SIMULATOR=1
