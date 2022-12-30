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

noinst_LTLIBRARIES = libExecutiveUUIDs.la

libExecutiveUUIDs_la_SOURCES = p_UUIDs.h \
	Classes.c \
	IObject.c IAllocator.c IRegionHolder.c IBootEnvironment.c \
	IDirectoryEntryTarget.c IPlatform.c IPlatformDiagnostics.c \
	ISubsystem.c ITasker.c IAddressSpace.c IContainer.c \
	IDirectoryEntry.c IIterator.c ILink.c IMutableContainer.c \
	INamespace.c ITask.c IThread.c IWriteChannel.c IExecutable.c \
	\
	MObject.c MDirectoryEntryTarget.c MFactory.c
libExecutiveUUIDs_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS}
