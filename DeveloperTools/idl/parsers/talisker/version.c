/* Talisker IDL compiler
 */

/* Copyright (c) 2008-2018 Mo McRoberts.
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
idl_parser_version(void)
{
	fprintf(stderr, "Talisker IDL compiler %s\n", VERSION);
	fprintf(stderr, "Copyright (c) 2008-2018 Mo McRoberts\n");
	fprintf(stderr, "Copyright (c) 2007 Novell, Inc. All rights reserved.\n");
	fprintf(stderr, "Copyright (c) 1989 Open Software Foundation, Inc.\n");
	fprintf(stderr, "Copyright (c) 1989 Hewlett-Packard Company\n");
	fprintf(stderr, "Copyright (c) 1989 Digital Equipment Corporation\n");
	#ifndef HAVE_GETOPT
		fprintf(stderr, "Copyright (c) 1987, 1993, 1994\nThe Regents of the University of California.  All rights reserved.\n");
	#endif
}
