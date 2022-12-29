## Executive Microkernel
## UUIDs

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

# Whilst a version of the Runtime is linked into the Executive, and a
# second version into the Simulator, we want to ensure that all of the UUID
# definitions are available in the right places. This means that:
#
# The Executive version of the Runtime includes only those UUIDs that the
# Executive itself depends upon (i.e., those interfaces implemented by it
# and the PAL)
#
# The Simulator version of the Runtime should include all OTHER well-known
# UUIDs
#
# The standard version of the Runtime framework should include the combined
# set of both
#
# Classes and interfaces that don't ever get referenced by UUID aren't
# included

noinst_LTLIBRARIES = libExecRuntimeUUIDs.la libRuntimeUUIDs.la

if BUILD_SIMULATOR

noinst_LTLIBRARIES += libSimRuntimeUUIDs.la

endif

libExecRuntimeUUIDs_la_SOURCES = p_UUIDs.h \
	Classes.c \
	IObject.c IAllocator.c IRegionHolder.c IBootEnvironment.c \
	IDirectoryEntryTarget.c IPlatform.c IPlatformDiagnostics.c \
	ISubsystem.c ITasker.c IAddressSpace.c IContainer.c \
	IDirectoryEntry.c IIterator.c ILink.c IMutableContainer.c \
	INamespace.c ITask.c IThread.c IWriteChannel.c IExecutable.c \
	\
	MObject.c MDirectoryEntryTarget.c MFactory.c
libExecRuntimeUUIDs_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1

libSimRuntimeUUIDs_la_SOURCES = p_UUIDs.h \
	IContext.c IRegion.c
libSimRuntimeUUIDs_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_SIMULATOR=1

libRuntimeUUIDs_la_SOURCES = $(libExecRuntimeUUIDs_la_SOURCES) $(libSimRuntimeUUIDs_la_SOURCES)
libRuntimeUUIDs_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_USER=1
