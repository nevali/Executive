## Executive Microkernel
## Public headers
##   Defines the APIs to the Executive

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

## Most of the headers are generated from IDL source

idlgenerated = Types.h Errors.h UUID.h \
	IObject.h IAllocator.h MObject.h MFactory.h \
	IIterator.h \
	IPlatform.h IBootEnvironment.h IAddressSpace.h \
	IRegion.h IRegionHolder.h IPlatformDiagnostics.h \
	MDirectoryEntryTarget.h \
	IContainer.h INamespace.h IMutableContainer.h IDirectoryEntry.h \
	IDirectoryEntryTarget.h ILink.h \
	IWriteChannel.h \
	ITasker.h ITask.h IThread.h IJob.h IEvent.h IExecutable.h IContext.h \
	ISubsystem.h

Executivedir = $(includedir)/Executive

dist_Executive_HEADERS = $(idlgenerated) Linkage.h SystemCall.h initguid.h

if WITH_IDL

CLEANFILES = $(idlgenerated)

%.h: $(top_srcdir)/Frameworks/Executive/IDL/Executive/%.idl
	$(IDL) -I$(top_srcdir)/Frameworks/Executive/IDL -H $@ $<

endif
