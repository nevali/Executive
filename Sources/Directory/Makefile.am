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

noinst_LTLIBRARIES = libDirectory.la

libDirectory_la_SOURCES = p_Directory.h \
	Directory.c Directory-MObject.c Directory-MDirectoryEntryTarget.c \
	\
	Directory-IObject.c Directory-IContainer.c Directory-IMutableContainer.c \
	Directory-INamespace.c Directory-IDirectoryEntryTarget.c \
	\
	Directory-Entry.c \
	\
	Directory-Iterator.c \
	\
	Directory-Link.c \
	\
	Directory-Root.c Directory-System.c Directory-Local.c Directory-Cluster.c \
	Directory-Network.c

libDirectory_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1
