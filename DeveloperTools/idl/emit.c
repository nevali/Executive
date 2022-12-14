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

static int idl_emit_begin(idl_module_t *module);
static int idl_emit_scope(idl_module_t *module, idl_scope_t *scope);

extern struct idl_emitter_struct idl_mscom_cxxinc_emitter;
extern struct idl_emitter_struct idl_sunrpc_cxxinc_emitter;
extern struct idl_emitter_struct idl_talisker_cxxinc_emitter;

/* Begin emitting output: returns -1 on error, 0 if output is suppressed,
 * 1 to proceed.
 */
static int
idl_emit_begin(idl_module_t *module)
{
	if(module->emitter)
	{
		return 1;
	}
	if(module->included)
	{
		return 0;
	}
	if(MODE_UNSPEC == module->mode)
	{
		module->mode = defmode;
	}
	switch(module->mode)
	{
	case MODE_TALISKER:
		module->emitter = &idl_talisker_cxxinc_emitter;
		break;
	case MODE_MSCOM:
		module->emitter = &idl_mscom_cxxinc_emitter;
		break;
	case MODE_SUNRPC:
		module->emitter = &idl_sunrpc_cxxinc_emitter;
		break;
	default:
		fprintf(stderr, "%s: unsupported mode\n", module->shortname);
		return -1;
	}
	if(module->emitter->init(module))
	{
		fprintf(stderr, "%s: failed to initialise emitter\n", module->shortname);
		return -1;
	}
	return 1;
}

int
idl_emit(idl_module_t *module)
{
	int r;

	if((r = idl_emit_begin(module)) != 1)
	{
		return r;
	}
	if(idl_emit_scope(module, &(module->rootscope)))
	{
		return -1;
	}
	return module->emitter->done(module);	
}

/* Emit the contents of a scope */
static int
idl_emit_scope(idl_module_t *module, idl_scope_t *scope)
{
	idl_scope_t *p;
	idl_interface_t *prevcontainer;

	switch(scope->type)
	{
	case ST_MODULE:
		break;
	case ST_QUOTE:
		return module->emitter->emit_cppquote(module, scope->text);
	case ST_CONTAINER:
		prevcontainer = module->curintf;
		module->curintf = scope->container;
		if(module->emitter->intf_prologue(module, scope->container))
		{
			module->curintf = prevcontainer;
			return -1;
		}
		break;
	case ST_SYMDEF:
		switch(scope->symdef->type)
		{
		case SYM_TYPEDEF:
			return module->emitter->emit_typedef(module, scope->container, scope->symdef);
		case SYM_METHOD:
			return module->emitter->emit_method(module, scope->container, scope->symdef);
		case SYM_CONST:
			return module->emitter->emit_const(module, scope->symdef);
		case SYM_UNSPEC:
		case SYM_PARAM:
		case SYM_MEMBER:
		case SYM_ENUM:
		case SYM_STRUCT:
			return 0;
		}
	case ST_IMPORT:
		return module->emitter->emit_import(module, scope->container);
	}

	/* Iterate child scopes */
	for(p = scope->first; p; p = p->next)
	{
		if(idl_emit_scope(module, p))
		{
			return -1;
		}
	}

	switch(scope->type)
	{
	case ST_MODULE:
		break;
	case ST_CONTAINER:
		if(module->emitter->intf_epilogue(module, scope->container))
		{
			module->curintf = prevcontainer;
			return -1;
		}
		module->curintf = prevcontainer;
		break;
	case ST_SYMDEF:
		break;
	case ST_QUOTE:
		break;
	case ST_IMPORT:
		break;
	}
	return 0;
}
