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

noinst_LTLIBRARIES = libRuntimeClient.la

libRuntimeClient_la_SOURCES = p_Client.h \
	Client.c \
	IObject.c INamespace.c ITask.c IThread.c IAddressSpace.c IContext.c \
	IRegion.c IWriteChannel.c IContainer.c IMutableContainer.c \
	IDirectoryEntry.c ILink.c IIterator.c
libRuntimeClient_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_USER=1
