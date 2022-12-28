## Executive Microkernel
## Co-operative Tasker
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

noinst_LTLIBRARIES = libCooperativeTasker.la

libCooperativeTasker_la_SOURCES = p_CooperativeTasker.h \
	CooperativeTasker.c CooperativeTasker-IObject.c CooperativeTasker-ITasker.c \
	CooperativeTasker-IContainer.c CooperativeTasker-Task.c \
	CooperativeTasker-Thread.c CooperativeTasker-Sentinel.c

libCooperativeTasker_la_CPPFLAGS = @AM_CPPFLAGS@ ${WARNING_CPPFLAGS} -DRUNTIME_BUILD_EXEC=1
