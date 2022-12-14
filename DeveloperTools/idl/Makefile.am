## Copyright 2008-2015 Mo McRoberts.
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

dist_noinst_DATA = LICENSE-2.0 README.md

AM_YFLAGS = -d
BUILT_SOURCES = lexidl.c idlparse.c idlparse.h

noinst_PROGRAMS = idl

idl_CPPFLAGS = @IDL_CPPFLAGS@
idl_SOURCES = p_comidl.h \
	idlparse.y lexidl.l \
	keywords.c  module.c interface.c comidl.c emit.c getopt.c incpath.c \
	expr.c \
	emit-cxx.c \
	emit-talisker-cxxinc.c \
	emit-mscom-cxxinc.c \
	emit-sunrpc-cxxinc.c