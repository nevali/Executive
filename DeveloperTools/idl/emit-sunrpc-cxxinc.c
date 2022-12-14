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

static int sunrpc_cxxinc_init(idl_module_t *module);
static int sunrpc_cxxinc_done(idl_module_t *module);
static int sunrpc_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf);
static int sunrpc_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf);
static int sunrpc_cxxinc_cppquote(idl_module_t *module, const char *quote);
static int sunrpc_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int sunrpc_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int sunrpc_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef);
static int sunrpc_cxxinc_import(idl_module_t *module, idl_interface_t *intf);

struct idl_emitter_struct idl_sunrpc_cxxinc_emitter = {
	sunrpc_cxxinc_init,
	sunrpc_cxxinc_done,
	sunrpc_cxxinc_intf_prologue,
	sunrpc_cxxinc_intf_epilogue,
	sunrpc_cxxinc_cppquote,
	sunrpc_cxxinc_typedef,
	sunrpc_cxxinc_method,
	sunrpc_cxxinc_const,
	sunrpc_cxxinc_import
};


static int
sunrpc_cxxinc_init(idl_module_t *module)
{
    if(1 != idl_emit_cxxinc_open(module))
	{
		return -1;
	}
	if(0 == module->headerwritten)
	{
		module->headerwritten = 1;
		fprintf(module->hout, "#ifndef _%s_RPCGEN\n", module->hmacro);
		fprintf(module->hout, "# define _%s_RPCGEN\n\n", module->hmacro);
		if(0 == module->nodefinc)
		{
			fprintf(module->hout, "# include <rpc/rpc.h>\n\n");
		}
	}
	return 0;
}

static int
sunrpc_cxxinc_done(idl_module_t *module)
{
	if(module->headerwritten)
	{
		fprintf(module->hout, "\n#endif /*!_%s_RPCGEN*/\n", module->hmacro);
	}
	idl_emit_cxxinc_close(module);
	return 0;
}

static int
sunrpc_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf)
{
	FILE *f;

	f = module->hout;

	fprintf(f, "/* %s (%lu) version %lu */\n", intf->name, intf->id, intf->version);

	return 0;
}

static int
sunrpc_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf)
{
	(void) module;
	(void) intf;
	
	return 0;
}

static int
sunrpc_cxxinc_cppquote(idl_module_t *module, const char *quote)
{
	fprintf(module->hout, "%s\n", quote);
	return 0;
}

static int
sunrpc_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) intf;

	fprintf(module->hout, "typedef ");
	idl_emit_cxx_write_sym(module, module->hout, symdef, NULL);
	fputc(';', module->hout);
	fputc('\n', module->hout);
	return 0;
}

static int
sunrpc_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) intf;

	idl_emit_cxx_write_indent(module, module->hout);
	idl_emit_cxx_write_type(module, module->hout, symdef->decl);
	idl_emit_cxx_write_symdef(module, module->hout, symdef, " %s", "", "void");
	fprintf(module->hout, ";\n");	
	return 0;
}

static int
sunrpc_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef)
{
	fprintf(module->hout, "#  define %s ", symdef->ident);
	idl_emit_cxx_write_expr(module, module->hout, symdef->constval);
	fputc('\n', module->hout);

	return 0;
}

static int
sunrpc_cxxinc_import(idl_module_t *module, idl_interface_t *intf)
{
	if(!intf->cheader)
	{
		return 0;
	}
	fprintf(module->hout, "# include <%s>\n", intf->cheader);
	return 0;
}
