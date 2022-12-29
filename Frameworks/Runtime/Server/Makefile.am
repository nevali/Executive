## Executive Microkernel
## Server stubs
##   The files in this directory implement the server-side (that is, in-kernel)
##   stubs that are invoked when a system call occurs. They are responsible for
##   unmarshalling the parameters and performing the actual method calls, and
##   then marshalling any return values back to user-space.

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

noinst_LTLIBRARIES = libExecRuntimeServer.la

libExecRuntimeServer_la_SOURCES = p_Server.h \
	IObject.c IThread.c ITask.c INamespace.c IAddressSpace.c \
	IRegion.c IWriteChannel.c IIterator.c IContainer.c IDirectoryEntry.c \
	ILink.c

libExecRuntimeServer_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1
