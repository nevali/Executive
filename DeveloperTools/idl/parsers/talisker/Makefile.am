## Copyright 2008-2018 Mo McRoberts.
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

AM_YFLAGS = -d
BUILT_SOURCES = lexidl.c idlparse.c idlparse.h
CLEANFILES = $(BUILT_SOURCES)

bin_PROGRAMS = idlc-parser-talisker

idlc_parser_talisker_CPPFLAGS = @AM_CPPFLAGS@ @IDL_CPPFLAGS@

idlc_parser_talisker_SOURCES = p_parser.h \
	idlparse.y lexidl.l \
	parser-talisker.c args.c usage.c version.c \
	keywords.c module.c incpath.c json.c \
	../../getopt.c
