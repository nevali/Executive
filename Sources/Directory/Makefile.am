## Executive Microkernel
## Object Directory
##  

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

noinst_LTLIBRARIES = libDirectory.Debug.la libDirectory.Free.la libDirectory.Release.la

libDirectory_Release_la_SOURCES = p_Directory.h \
	Directory.c Directory-MObject.c Directory-MDirectoryEntryTarget.c \
	\
	Directory-IObject.c Directory-IContainer.c Directory-IMutableContainer.c \
	Directory-INamespace.c Directory-IDirectoryEntryTarget.c \
	\
	Directory-Entry.c \
	\
	Directory-Iterator.c \
	\
	Directory-Link.c

libDirectory_Release_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${RELEASE_CPPFLAGS}


libDirectory_Free_la_SOURCES = $(libDirectory_Release_la_SOURCES)
libDirectory_Free_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${FREE_CPPFLAGS}

libDirectory_Debug_la_SOURCES = $(libDirectory_Release_la_SOURCES)
libDirectory_Debug_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} ${DEBUG_CPPFLAGS}
