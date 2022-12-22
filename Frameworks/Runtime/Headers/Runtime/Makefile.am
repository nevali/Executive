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

Runtimedir = $(includedir)/Headers

idlgenerated = 

Runtime_HEADERS = Runtime.h Strings.h Memory.h UUID.h \
	Log.h Status.h Task.h \
	IObject.h IAllocator.h IRegionHolder.h IThread.h \
	$(idlgenerated)

if WITH_IDL

CLEANFILES = $(idlgenerated)

%.h: $(top_srcdir)/Frameworks/Runtime/IDL/Runtime/%.idl
	$(IDL)  -I$(top_srcdir)/Frameworks/Runtime/IDL -I$(top_srcdir)/Frameworks/Executive/IDL  -H $@ $<

endif
