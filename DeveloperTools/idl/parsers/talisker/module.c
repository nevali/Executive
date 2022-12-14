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

static idl_module_t **modules;
static size_t nmodules;
static json_t *root;

int
idl_module_output(void)
{
	json_dumpf(root, stdout, JSON_INDENT(4)|JSON_SORT_KEYS);
	fputc('\n', stdout);
	return 0;
}

int
idl_module_add(idl_module_t *module)
{
	json_t *list;
	
	if(!module->ir)
	{
		return 0;
	}
	list = json_object_get(root, "@");
	json_array_append_new(list, module->irstack[0]);
	return 0;
}

void
idl_module_terminate(void)
{
	exit(EXIT_FAILURE);
}

void
idl_module_vmsg(idl_module_t *module, YYLTYPE *loc, const char *prefix, const char *fmt, va_list ap)
{
	if(loc)
	{
		fprintf(stderr, "%s:%d:%d: %s: ", (loc->filename ? loc->filename : module->filename), loc->first_line,  loc->first_column, prefix);
	}
	else
	{
		fprintf(stderr, "%s: %s: ", module->filename, prefix);
	}
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	fflush(stderr);
}

void
idl_module_errmsg(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, loc, "error", fmt, ap);
	va_end(ap);
}

void
idl_module_error(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, loc, "error", fmt, ap);
	va_end(ap);
	idl_module_terminate();
}

void
idl_module_warning(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, loc, "warning", fmt, ap);
	va_end(ap);
}

idl_module_t *
idl_module_create(const char *filename)
{
	idl_module_t *p, **q;
	
	if(!root)
	{
		root = json_object();
		json_object_set_new(root, "@type", json_string("idl"));
		json_object_set_new(root, "@",  json_array());
	}
	if(NULL == (p = (idl_module_t *) calloc(1, sizeof(idl_module_t))))
	{
		return NULL;
	}
	if(NULL == (q = (idl_module_t **) realloc(modules, sizeof(idl_module_t *) * (nmodules + 1))))
	{
		return NULL;
	}
	modules = q;
	p->filename = strdup(filename);
	p->nodefimports = nodefimports;
	modules[nmodules] = p;
	nmodules++;
	return p;
}

idl_module_t *
idl_module_lookup(const char *pathname)
{
	size_t c;
	
	for(c = 0; c < nmodules; c++)
	{
		if(0 == strcmp(modules[c]->filename, pathname))
		{
			return modules[c];
		}
	}
	return NULL;
}

int
idl_module_done(idl_module_t *module)
{
	(void) module;
	
	return 0;
}
