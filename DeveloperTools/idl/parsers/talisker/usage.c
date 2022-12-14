/* Copyright (c) 2008-2015 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_parser.h"

void
idl_parser_usage(void)
{
	fprintf(stderr, "Usage: %s [OPTIONS] SOURCE\n"
		"OPTIONS is one or more of:\n"
		"  -M PATH                  Add PATH to the import search path\n"
		"  -nostdinc                Reset the import and framework search paths\n"
		"  -nobuiltin               Don't supply any built-in definitions or imports\n"
		"  -V                       Display version information and exit\n"
		"  -h                       Display this message and exit\n",
		progname);
}
