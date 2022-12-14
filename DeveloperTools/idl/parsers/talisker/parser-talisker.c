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

const char *progname = "idlc-parse-talisker";
idl_module_t *curmod;
int nodefimports = 0;

void idl_parser_version(void);
void idl_parser_usage(void);

int
idl_parse(const char *src, int defimp, int useinc)
{
	FILE *f;
	char fpath[PATH_MAX + 1];
	idl_module_t *lastmod;
	void *scanner;
	json_t *self;
	
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
	curmod = idl_module_create(fpath);
	if(!defimp)
	{
		curmod->nodefimports = 1;
	}
	if(lastmod)
	{
		curmod->included = 1;
	}
	self = idl_json_push(curmod, "idlsrc", NULL);
	/* TODO: add timestamps */
	json_object_set_new(self, "@source", json_string(curmod->filename));
	if(curmod->included)
	{
		json_object_set_new(self, "included", json_true());
	}
	else
	{
		json_object_set_new(self, "included", json_false());
	}
	idl_module_add(curmod);
	yylex_init(&scanner);
	curmod->scanner = scanner;
	yyrestart(f, scanner);
	yyparse(scanner);
	fclose(f);
	idl_module_done(curmod);
	curmod = lastmod;
	return 0;
}

int
main(int argc, char **argv)
{
	const char *srcfile, *t;
	int c;
	
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
	while((c = getopt(argc, argv, "M:n:hV")) != -1)
	{
		switch(c)
		{
			case 'M':
				idl_incpath_add_includedir(optarg);
				break;
			case 'n':
				if(0 == strcmp(optarg, "ostdinc"))
				{
					idl_incpath_reset();
				}
				else if(0 == strcmp(optarg, "obuiltin"))
				{
					nodefimports = 1;
				}
				else
				{
					fprintf(stderr, "%s: illegal option -- n%s\n", progname, optarg);
					idl_parser_usage();
					exit(EXIT_FAILURE);
				}
				break;
			case 'h':
				usage();
				exit(EXIT_SUCCESS);
			case 'V':
				idl_parser_version();
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
	curmod = NULL;
	if(-1 == idl_parse(srcfile, 1, 0))
	{
		exit(EXIT_FAILURE);
	}
	idl_module_output();
	return 0;
}
