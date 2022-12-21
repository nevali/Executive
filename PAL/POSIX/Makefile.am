## Executive Microkernel
## POSIX Platform Adaptation Layer
##   Provides platform-specific services to the Executive when running within
##   a POSIX-like operating environment

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

PALNAME = POSIX
PALSRC = p_POSIX.h \
	BuildInformation.c init.c panic.c \
	metaClass.c Platform.c PlatformDiagnostics.c \
	BootEnvironment.c \
	p_AddressSpace.h \
	AddressSpace.c Region.c Context.c

PAL_MOD_EXT = ${EXEC_POSIX_PAL_EXT}
PAL_MOD_ldflags= -shared -module -avoid-version -shrext ${PAL_MOD_EXT} -rpath ${libdir}

include $(top_srcdir)/Makefiles/PAL.mk
