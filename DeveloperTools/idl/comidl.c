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

#include "p_comidl.h"

const char *progname = "comidl";
idl_module_t *curmod;

/* Global options */

int nodefimports = 0;
int nodefinc = 0;
idl_mode_t defmode = MODE_UNSPEC;

static void
usage(void)
{
	fprintf(stderr, "Usage: %s [OPTIONS] SOURCE\n"
		"OPTIONS is one or more of:\n"
		"  -H FILE                  Write inteface definition C/C++ header to FILE\n"
		"  -P FILE                  Write proxy to FILE\n"
		"  -S FILE                  Write stub to FILE\n"
		"  -I PATH                  Add PATH to the import search path\n"
		"  -F PATH                  Add PATH to the framework search path\n"
		"  -nostdinc                Reset the import and framework search paths\n"
		"  -nodefimports            Don't perform default imports\n"
		"  -nodefinc                Omit default includes from generated C/C++ headers\n"
		"  -Wp,OPTIONS              Pass OPTIONS to the C preprocessor\n"
		"  -v                       Display version information and exit\n"
		"  -h                       Display this message and exit\n"
		"  -X LANGUAGE              Output for LANGUAGE [default=C]\n"
		"  -M MODE                  Specify default output mode: [default=com]\n"
		"    talisker                 Talisker COM\n"
		"    mscom                    Microsoft COM/ReactOS/WINE\n"
		"    sunrpc                   Sun ONC RPC\n"
		"  Note: specified mode value may be overridden within IDL\n",
		progname);
}

static void
version(void)
{
	fprintf(stderr, "Talisker IDL compiler " PACKAGE " " VERSION "\n");
	fprintf(stderr, "Copyright (c) 2008-2015 Mo McRoberts\n");
	fprintf(stderr, "Copyright (c) 2007 Novell, Inc. All rights reserved.\n");
	fprintf(stderr, "Copyright (c) 1989 Open Software Foundation, Inc.\n");
	fprintf(stderr, "Copyright (c) 1989 Hewlett-Packard Company\n");
	fprintf(stderr, "Copyright (c) 1989 Digital Equipment Corporation\n");
	#ifndef HAVE_GETOPT
		fprintf(stderr, "Copyright (c) 1987, 1993, 1994\nThe Regents of the University of California.  All rights reserved.\n");
	#endif
}

idl_mode_t
idl_mode_parse(const char *modestr)
{
	if(0 == strcmp(modestr, "talisker"))
	{
		return MODE_TALISKER;
	}
	if(0 == strcmp(modestr, "mscom"))
	{
		return MODE_MSCOM;
	}
	if(0 == strcmp(modestr, "sunrpc") || 0 == strcmp(modestr, "oncrpc"))
	{
		return MODE_SUNRPC;
	}
	return MODE_UNSPEC;
}

int
idl_builtin_create(idl_module_t *mod, idl_interface_t *intf, const char *name, idl_builtintype_t type, idl_typemod_t mods)
{
	idl_typedecl_t *typedecl;
	idl_symdef_t *sym;
	
	typedecl = idl_module_typedecl_push(mod);
	typedecl->builtin_type = type;
	typedecl->modifiers = mods;
	sym = idl_module_symdef_create(mod, &(intf->symlist), typedecl);
	sym->type = SYM_TYPEDEF;
	strncpy(sym->ident, name, IDL_IDENT_MAX);
	sym->ident[IDL_IDENT_MAX] = 0;
	idl_module_symdef_add(mod, &(intf->symlist), sym);
	idl_module_typedecl_pop(mod);
	return 0;
}

int
idl_builtin(void)
{
	idl_module_t *mod;
	idl_interface_t *builtins;
	
	mod = idl_module_create("*Built-in*", NULL);
	builtins = idl_intf_create(mod);
	idl_builtin_create(mod, builtins, "bool", TYPE_BOOLEAN, TYPEMOD_NONE);
	idl_builtin_create(mod, builtins, "int8_t", TYPE_INT8, TYPEMOD_SIGNED);
	idl_builtin_create(mod, builtins, "int16_t", TYPE_INT16, TYPEMOD_SIGNED);
	idl_builtin_create(mod, builtins, "int32_t", TYPE_INT32, TYPEMOD_SIGNED);
	idl_builtin_create(mod, builtins, "int64_t", TYPE_INT64, TYPEMOD_SIGNED);
	idl_builtin_create(mod, builtins, "uint8_t", TYPE_INT8, TYPEMOD_UNSIGNED);
	idl_builtin_create(mod, builtins, "uint16_t", TYPE_INT16, TYPEMOD_UNSIGNED);
	idl_builtin_create(mod, builtins, "uint32_t", TYPE_INT32, TYPEMOD_UNSIGNED);
	idl_builtin_create(mod, builtins, "uint64_t", TYPE_INT64, TYPEMOD_UNSIGNED);
	return 0;
}

int
idl_parse(const char *src, const char *hout, int defimp, int useinc)
{
	FILE *f;
	char fpath[PATH_MAX + 1], *t;
	idl_module_t *lastmod;
	void *scanner;
	idl_scope_t *scope;
	size_t c;

	if(0 == useinc || src[0] == '/')
	{
		if(strlen(src) > PATH_MAX)
		{
			fprintf(stderr, "%s: %s: path too long\n", progname, src);
			return -1;
		}
		strcpy(fpath, src);
	}
	else
	{
		if(-1 == idl_incpath_locate(fpath, sizeof(fpath), src))
		{
			fprintf(stderr, "%s: %s: %s\n", progname, src, strerror(ENOENT));
			return -1;
		}
	}
	if(NULL == (f = fopen(fpath, "rb")))
	{
		fprintf(stderr, "%s: %s: %s\n", progname, fpath, strerror(errno));
		return -1;
	}
	if(NULL != idl_module_lookup(fpath))
	{
		/*	fprintf(stderr, "%s has already been imported\n", fpath); */
		return 0;
	}
	lastmod = curmod;
	curmod = idl_module_create(fpath, hout);
	if(!defimp)
	{
		curmod->nodefimports = 1;
	}
	if(!hout)
	{
		t = strrchr(fpath, '/');
		if(t)
		{
			t++;
		}
		else
		{
			t = fpath;
		}
		curmod->included = 1;
		curmod->houtname = (char *) malloc(strlen(t) + 3);
		strcpy(curmod->houtname, t);
		t = strrchr(curmod->houtname, '.');
		if(t && !strcmp(t, ".idl"))
		{
			t[1] = 'h';
			t[2] = 0;
		}
		else
		{
			strcat(curmod->houtname, ".h");
		}
	}
	yylex_init(&scanner);
	curmod->scanner = scanner;
	yyrestart(f, scanner);
	yyparse(scanner);
	fclose(f);
	if(lastmod && !lastmod->included)
	{
		for(c = 0; c < curmod->ninterfaces; c++)
		{
			if(!curmod->interfaces[c]->stub)
			{
				scope = idl_module_scope_push(lastmod);
				scope->type = ST_IMPORT;
				scope->container = curmod->interfaces[c];
				idl_module_scope_pop(lastmod);
			}
		}
	}
	idl_module_done(curmod);
	curmod->included = 0;
	curmod->emitter = NULL;
	curmod->scanner = NULL;
	curmod = lastmod;
	return 0;
}

int
main(int argc, char **argv)
{
	const char *srcfile, *intfheader, *t;
	char *ih, *s;
	int defaults, c;
	idl_mode_t mode;
	
	if(NULL != argv[0])
	{
		progname = argv[0];
		if(NULL != (t = strrchr(progname, '/')))
		{
			t++;
			progname = t;
		}
	}
	argv[0] = (char *) progname;
	srcfile = NULL;
	intfheader = NULL;
	defaults = 1;
	while((c = getopt(argc, argv, "H:P:S:I:F:n:W:X:M:hv")) != -1)
	{
		switch(c)
		{
			case 'H':
				intfheader = optarg;
				defaults = 0;
				break;
			case 'I':
				idl_incpath_add_includedir(optarg);
				break;
			case 'F':
				idl_incpath_add_frameworkdir(optarg);
				break;
			case 'n':
				if(0 == strcmp(optarg, "ostdinc"))
				{
					idl_incpath_reset();
				}
				else if(0 == strcmp(optarg, "odefimports"))
				{
					nodefimports = 1;
				}
				else if(0 == strcmp(optarg, "odefinc"))
				{
					nodefinc = 1;
				}
				else
				{
					fprintf(stderr, "%s: illegal option -- n%s\n", progname, optarg);
					usage();
					exit(EXIT_FAILURE);
				}
				break;
			case 'M':
				if(MODE_UNSPEC == (mode = idl_mode_parse(optarg)))
				{
					fprintf(stderr, "%s: invalid mode -- %s\n", progname, optarg);
					usage();
					exit(EXIT_FAILURE);
				}
				if(defmode != MODE_UNSPEC && defmode != mode)
				{
					fprintf(stderr, "%s: output mode cannot be specified more than once\n", progname);
					exit(EXIT_FAILURE);
				}
				defmode = mode;
				break;
			case 'h':
				usage();
				exit(EXIT_SUCCESS);
			case 'v':
				version();
				exit(EXIT_SUCCESS);
			default:
				usage();
				exit(EXIT_FAILURE);
		}
	}
	argv += optind;
	argc -= optind;
	if(argc != 1)
	{
		usage();
		exit(EXIT_FAILURE);
	}
	srcfile = argv[0];
	ih = NULL;
	if(defaults)
	{
		if(NULL == (t = strrchr(srcfile, '/')))
		{
			t = srcfile;
		}
		else
		{
			t++;
		}
		ih = (char *) malloc(strlen(t + 8));
		strcpy(ih, t);
		if(strlen(ih) > 4)
		{
			s = strchr(ih, 0);
			s -= 4;
			if(0 == strcasecmp(s, ".idl"))
			{
				s[0] = '.';
				s[1] = 'h';
				s[2] = 0;
			}
			else
			{
				strcat(ih, ".h");
			}
		}
		else
		{
			strcat(ih, ".h");
		}
		intfheader = ih;
	}
	if(MODE_UNSPEC == defmode)
	{
		defmode = MODE_TALISKER;
	}
/*	idl_incpath_addincludedir("/usr/include");
	idl_incpath_addframeworkdir("/System/Library/Frameworks");
	idl_incpath_addframeworkdir("/Library/Frameworks"); */
	curmod = NULL;
	idl_builtin();
	if(-1 == idl_parse(srcfile, intfheader, 1, 0))
	{
		exit(EXIT_FAILURE);
	}
	free(ih);
	return 0;
}
