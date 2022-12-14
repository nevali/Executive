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

static idl_module_t **modules;
static size_t nmodules;

void
idl_module_terminate(void)
{
	size_t c;
	
	for(c = 0; c < nmodules; c++)
	{
		if(NULL != modules[c]->hout)
		{
			fclose(modules[c]->hout);
			unlink(modules[c]->houtname);
		}
	}
	exit(EXIT_FAILURE);
}

void
idl_module_vmsg(idl_module_t *module, int line, const char *prefix, const char *fmt, va_list ap)
{
	fprintf(stderr, "%s:%d: %s: ", module->filename, line, prefix);
	vfprintf(stderr, fmt, ap);
	fputc('\n', stderr);
	fflush(stderr);
}

void
idl_module_errmsg(idl_module_t *module, int line, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, line, "error", fmt, ap);
	va_end(ap);
}

void
idl_module_error(idl_module_t *module, int line, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, line, "error", fmt, ap);
	va_end(ap);
	idl_module_terminate();
}

void
idl_module_warning(idl_module_t *module, int line, const char *fmt, ...)
{
	va_list ap;
	
	va_start(ap, fmt);
	idl_module_vmsg(module, line, "warning", fmt, ap);
	va_end(ap);
}

idl_module_t *
idl_module_create(const char *filename, const char *hout)
{
	idl_module_t *p, **q;
	const char *t;
	char *s;
	
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
	if(NULL != hout)
	{
		p->houtname = strdup(hout);
		if(NULL == (t = strrchr(hout, '/')))
		{
			t = hout;
		}
		else
		{
			t++;
		}
		if(NULL == (p->hmacro = (char *) malloc(strlen(t) + 16)))
		{
			free(p);
			return NULL;
		}
		sprintf(p->hmacro, "%s", t);
		s = p->hmacro;
		while(*s)
		{
			if(!isalnum(*s))
			{
				*s = '_';
			}
			else
			{
				*s = toupper(*s);
			}
			s++;
		}
		if(NULL == p->shortname)
		{
			if(NULL == (t = strrchr(filename, '/')))
			{
				t = filename;
			}
			else
			{
				t++;
			}
			p->shortname = strdup(t);
		}
	}
	p->nodefinc = nodefinc;
	p->nodefimports = nodefimports;
	p->cur = &(p->rootscope);
	p->cur->module = p;
	p->cur->line = 1;
	p->cur->type = ST_MODULE;
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

/* Create a new scope, make it current, and return it */
idl_scope_t *
idl_module_scope_push(idl_module_t *module)
{
	idl_scope_t *p;

	p = (idl_scope_t *) calloc(1, sizeof(idl_scope_t));
	p->parent = module->cur;
	p->module = module;
	p->type = module->cur->type;
	if(module->scanner)
	{
		p->line = yyget_lineno(module->scanner);
	}
	if(module->curintf)
	{
		p->container = module->curintf;
	}
	if(module->cursym)
	{
		p->symdef = module->cursym;
	}
	if(module->cur->first)
	{
		module->cur->last->next = p;
	}
	else
	{
		module->cur->first = p;
	}
	module->cur->last = p;
	module->cur = p;
	return p;
}

/* Jump up the scope chain; returns the new current scope */
idl_scope_t *
idl_module_scope_pop(idl_module_t *module)
{
	if(!module->cur->parent)
	{
		return module->cur;
	}
	module->cur = module->cur->parent;
	return module->cur;
}

idl_interface_t *
idl_module_lookupintf(const char *name, int incstubs)
{
	size_t c, d;
	
	for(c = 0; c < nmodules; c++)
	{
		for(d = 0; d < modules[c]->ninterfaces; d++)
		{
			if(modules[c]->interfaces[d]->stub)
			{
				if(!incstubs && !modules[c]->interfaces[d]->target)
				{
					continue;
				}
			}
			if(0 == strcmp(modules[c]->interfaces[d]->name, name))
			{
				if(modules[c]->interfaces[d]->stub &&
					modules[c]->interfaces[d]->target)
				{
					return modules[c]->interfaces[d]->target;
				}
				return modules[c]->interfaces[d];
			}
		}
	}
	return NULL;
}


int
idl_module_done(idl_module_t *module)
{
	idl_emit(module);
	return 0;
}

int
idl_module_addintf(idl_module_t *module, idl_interface_t *intf)
{
	idl_interface_t **q;
	
	if(NULL == (q = realloc(module->interfaces, sizeof(idl_interface_t *) * (module->ninterfaces + 1))))
	{
		return -1;
	}
	q[module->ninterfaces] = intf;
	module->interfaces = q;
	module->ninterfaces++;
	intf->module = module;
	intf->symlist.parent = module->cursymlist;
	module->cursymlist = intf->cursymlist;
	module->curintf = intf;
	return 0;
}

int
idl_module_doneintf(idl_module_t *module, idl_interface_t *intf)
{
	if(module->curintf == intf)
	{
		module->cursymlist = intf->symlist.parent;
		module->curintf = NULL;
	}
	return 0;
}

int
idl_module_addguid(idl_module_t *module, const idl_guid_t *guid)
{
	idl_guid_t const **q;
	
	if(NULL == (q = realloc((void *) (module->guids), sizeof(idl_guid_t *) * (module->nguids + 1))))
	{
		return -1;
	}
	q[module->nguids] = guid;
	module->guids = q;
	module->nguids++;
	return 0;
}

idl_typedecl_t *
idl_module_typedecl_push(idl_module_t *module)
{
	idl_typedecl_t *p;
	
	if(NULL == (p = (idl_typedecl_t *) calloc(1, sizeof(idl_typedecl_t))))
	{
		return NULL;
	}
	module->typestack[module->typestackpos] = module->curtype = p;
	module->typestackpos++;
/*	fprintf(stderr, "Started processing of type [0x%08x] (stackpos = %d)\n", (unsigned int) p, (int) module->typestackpos); */
	return p;
}

idl_typedecl_t *
idl_module_typedecl_pop(idl_module_t *module)
{
	idl_typedecl_t *p;
	
	module->typestackpos--;
	p = module->typestack[module->typestackpos];
/*	fprintf(stderr, "Completed processing of type [0x%08x] = %d (stackpos = %d)\n", (unsigned int) p, (int) p->builtin_type, (int) module->typestackpos); */
	if(0 != module->typestackpos)
	{
		module->curtype = module->typestack[module->typestackpos - 1];
	}
	else
	{
		module->curtype = NULL;
	}
	return p;
}

idl_symdef_t *
idl_module_symdef_create(idl_module_t *module, idl_symlist_t *symlist, /*[optional]*/ idl_typedecl_t *typedecl)
{
	idl_symdef_t *p;

	if(NULL == (p = (idl_symdef_t *) calloc(1, sizeof(idl_symdef_t))))
	{
		return NULL;
	}
	p->decl = typedecl;
	if(-1 == idl_module_symdef_add(module, symlist, p))
	{
		free(p);
		return NULL;
	}
	return p;
}

int
idl_module_symdef_add(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *sym)
{
	idl_symdef_t **q;
	
	if(NULL == (q = (idl_symdef_t **) realloc(symlist->defs, sizeof(idl_symdef_t *) * (symlist->ndefs + 1))))
	{
		return -1;
	}
	q[symlist->ndefs] = sym;
	symlist->defs = q;
	symlist->ndefs++;
	module->cursym = sym;
	sym->type = symlist->symtype;
/*	fprintf(stderr, "Starting processing of symbol [0x%08x]\n", (unsigned int) sym); */
	return 0;
}

int
idl_module_symdef_done(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *sym)
{
	(void) symlist;
	
/*	fprintf(stderr, "Completed processing of symbol %s [0x%08x]\n", sym->ident, (unsigned int) sym); */
	if(module->cursym == sym)
	{
		module->cursym = NULL;
	}
	else
	{
		fprintf(stderr, "WARNING: module->cursym (%s) is not sym (%s) in idl_module_symdef_done\n", module->cursym->ident, sym->ident);
	}
	return 0;
}

int
idl_module_symdef_link(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *symdef)
{
	idl_symdef_t *prev;
	size_t c;

	(void) module;
	
	prev = NULL;
	for(c = 0; c < symlist->ndefs; c++)
	{
		if(symlist->defs[c] == symdef)
		{
			break;
		}
		prev = symlist->defs[c];
	}
	if(NULL != prev)
	{
		prev->nextsym = symdef;
	}
	return 0;
}

idl_symdef_t *
idl_module_symdef_lookup(idl_module_t *module, idl_symlist_t *start, const char *name, int recurse)
{
	size_t c;
	idl_symdef_t *p;
	
	(void) module;
	
	if(NULL != start)
	{
/*		if(recurse)
		{
			fprintf(stderr, "--- Searching for %s ---\n", name);
		} */
		while(start)
		{
			for(c = 0; c < start->ndefs; c++)
			{
				if(0 == strcmp(start->defs[c]->ident, name))
				{
					return start->defs[c];
				}
			}
			start = start->parent;
		}
		if(recurse)
		{
			return idl_module_symdef_lookup(module, NULL, name, 1);
		}
		return NULL;
	}
	if(NULL != module)
	{
		/* We've searched the default scope chain, try the blocks in the current
		 * module.
		 */
		for(c = 0; c < module->ninterfaces; c++)
		{
/*			fprintf(stderr, "Searching %s in %s\n", module->interfaces[c]->name, module->filename); */
			if(NULL != (p = idl_module_symdef_lookup(module, &(module->interfaces[c]->symlist), name, 0)))
			{
				return p;
			}
		}
		if(recurse)
		{
			return idl_module_symdef_lookup(NULL, NULL, name, 1);
		}
		return NULL;
	}
	/* Try all of the blocks in all of the modules */
/*	fprintf(stderr, "nmodules is %u\n", (unsigned) nmodules); */
	for(c = 0; c < nmodules; c++)
	{
/*		fprintf(stderr, "Searching %s\n", modules[c]->filename); */
		if(NULL != (p = idl_module_symdef_lookup(modules[c], NULL, name, 0)))
		{
			return p;
		}
	}
	
	return NULL;
}

int
idl_module_symlist_push(idl_module_t *module, idl_symlist_t *symlist)
{
	symlist->parent = module->cursymlist;
	module->cursymlist = symlist;
	return 0;
}

int
idl_module_symlist_pop(idl_module_t *module, idl_symlist_t *symlist)
{
	if(module->cursymlist == symlist)
	{
		module->cursymlist = symlist->parent;
	}
	return 0;
}

int
idl_module_set_mode(idl_module_t *module, int line, const char *modestr)
{
	idl_mode_t mode;
	
	mode = idl_mode_parse(modestr);
	if(MODE_UNSPEC == mode)
	{
		idl_module_errmsg(module, line, "unrecognised mode attribute value '%s'", modestr);
		idl_module_error(module, line, "applicable values: rpc, com, mscom, dcerpc, sunrpc, xpcom");
	}
	if(MODE_UNSPEC != module->mode && mode != module->mode)
	{
		idl_module_error(module, line, "mode cannot be specified to more than one value in the same module");
	}
	module->mode = mode;
	return 0;
}
