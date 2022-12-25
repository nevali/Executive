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

/* Emit C/C++ includes in Talisker mode */

static int talisker_cxxinc_init(idl_module_t *module);
static int talisker_cxxinc_done(idl_module_t *module);
static int talisker_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf);
static int talisker_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf);
static int talisker_cxxinc_cppquote(idl_module_t *module, const char *quote);
static int talisker_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int talisker_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int talisker_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef);
static int talisker_cxxinc_import(idl_module_t *module, idl_interface_t *intf);
static void talisker_cxxinc_methods(idl_module_t *module, FILE *f, idl_interface_t *intf);
static int talisker_cxxinc_method_macros(idl_module_t *module, FILE *f, idl_interface_t *curintf, idl_interface_t *intf, int written);
static int talisker_cxxinc_consts(idl_module_t *module, FILE *f, idl_interface_t *container);

struct idl_emitter_struct idl_talisker_cxxinc_emitter = {
	talisker_cxxinc_init,
	talisker_cxxinc_done,
	talisker_cxxinc_intf_prologue,
	talisker_cxxinc_intf_epilogue,
	talisker_cxxinc_cppquote,
	talisker_cxxinc_typedef,
	talisker_cxxinc_method,
	talisker_cxxinc_const,
	talisker_cxxinc_import
};


static int
talisker_cxxinc_init(idl_module_t *module)
{
	size_t c;
	FILE *f;
	
    if(1 != idl_emit_cxxinc_open(module))
	{
		return -1;
	}
	if(!module->headerwritten)
	{
		module->headerwritten = 1;
		f = module->hout;
		for(c = 0; c < module->ninterfaces; c++)
		{
			if(module->interfaces[c]->type == BLOCK_INTERFACE &&
				module->interfaces[c]->object)
			{
				fprintf(f, "#ifndef %s_FWD_DEFINED\n", module->interfaces[c]->name);
				fprintf(f, "# define %s_FWD_DEFINED\n", module->interfaces[c]->name);
				fprintf(f, "typedef struct %s %s;\n", module->interfaces[c]->name, module->interfaces[c]->name);
				fprintf(f, "#endif\n\n");
			}
		}
		fprintf(f, "#ifndef %s_IDL_\n", module->hmacro);
		fprintf(f, "# define %s_IDL_\n\n", module->hmacro);
	}
	return 0;
}

static int
talisker_cxxinc_done(idl_module_t *module)
{
	size_t c;

	fprintf(module->hout, "\n#endif /*!%s_IDL_*/\n\n", module->hmacro);

	if(module->nguids)
	{
		fprintf(module->hout, "#if defined(INITGUID) || !defined(%s_GUIDS_DEFINED_)\n", module->hmacro);
		fprintf(module->hout, "# define %s_GUIDS_DEFINED_\n", module->hmacro);
		for(c = 0; c < module->nguids; c++)
		{
			fprintf(module->hout, "\n/* %s = {%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x} */\n",
					module->guids[c]->name,
					module->guids[c]->data1, module->guids[c]->data2, module->guids[c]->data3,
					module->guids[c]->data4[0], module->guids[c]->data4[1],
					module->guids[c]->data4[2], module->guids[c]->data4[3], module->guids[c]->data4[4],
					module->guids[c]->data4[5], module->guids[c]->data4[6], module->guids[c]->data4[7]);
			fprintf(module->hout, "UUID_DEFINE(%s, 0x%02x, 0x%02x, 0x%02x, 0x%02x,  0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x);\n",
					module->guids[c]->name,
					(module->guids[c]->data1 >> 24) & 0xff,
					(module->guids[c]->data1 >> 16) & 0xff,
					(module->guids[c]->data1 >> 8) & 0xff,
					module->guids[c]->data1 & 0xff,
					(module->guids[c]->data2 >> 8) & 0xff,
					module->guids[c]->data2 & 0xff,
					(module->guids[c]->data3 >> 8) & 0xff,
					module->guids[c]->data3 & 0xff,
					module->guids[c]->data4[0], module->guids[c]->data4[1],
					module->guids[c]->data4[2], module->guids[c]->data4[3], module->guids[c]->data4[4],
					module->guids[c]->data4[5], module->guids[c]->data4[6], module->guids[c]->data4[7]);
		}
		fprintf(module->hout, "#endif /*INITGUID || !%s_GUIDS_DEFINED_ */\n\n", module->hmacro);
	}
	idl_emit_cxxinc_close(module);
	return 0;
}

static int
talisker_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf)
{
	FILE *f;
	unsigned major, minor;

	f = module->hout;
	major = (unsigned int) (intf->version >> 16);
	minor = (unsigned int) (intf->version & 0xFFFF);
	fprintf(f, "\n/* %s version %u.%u */\n\n", intf->name, major, minor);
	fprintf(f, "# ifndef __%s_INTERFACE_DEFINED__\n", intf->name);
	fprintf(f, "#  define __%s_INTERFACE_DEFINED__\n", intf->name);
	return 0;
}

static int
talisker_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf)
{
	FILE *f;

	f = module->hout;

	if(intf->object)
	{
		fprintf(f, "#  undef INTEFACE\n");
		fprintf(f, "#  define INTERFACE %s\n\n", intf->name);
		fputc('\n', f);
		idl_emit_cxx_write_indent(module, f);
		if(NULL == intf->ancestor)
		{
			fprintf(f, "DECLARE_INTERFACE(%s)\n", intf->name);
		}
		else
		{
			fprintf(f, "DECLARE_INTERFACE_(%s, %s)\n", intf->name, intf->ancestor->name);
		}
		fprintf(f, "{\n");
		module->houtdepth++;
		idl_emit_cxx_write_indent(module, f);
		fprintf(f, "BEGIN_INTERFACE\n\n");
		talisker_cxxinc_consts(module, f, intf);
		talisker_cxxinc_methods(module, f, intf);
		fputc('\n', f);
		idl_emit_cxx_write_indent(module, f);
		fprintf(f, "END_INTERFACE\n");
		module->houtdepth--;
		fprintf(f, "};\n\n");
		talisker_cxxinc_method_macros(module, f, intf, intf, 0);
	}
	fprintf(f, "#  undef INTERFACE\n");
	fprintf(f, "# endif /*!__%s_INTERFACE_DEFINED__*/\n\n", intf->name);
	return 0;
}

static int
talisker_cxxinc_cppquote(idl_module_t *module, const char *quote)
{
	fprintf(module->hout, "%s\n", quote);
	return 0;
}

static int
talisker_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) intf;

	fprintf(module->hout, "typedef ");
	idl_emit_cxx_write_sym(module, module->hout, symdef, NULL);
	fputc(';', module->hout);
	fputc('\n', module->hout);
	return 0;
}

static int
talisker_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	if(intf->object)
	{
		/* Object interfaces are written by the interface epilogue callback */
		return 0;
	}
	idl_emit_cxx_write_indent(module, module->hout);
	idl_emit_cxx_write_type(module, module->hout, symdef->decl);
	idl_emit_cxx_write_symdef(module, module->hout, symdef, " %s", "", "void");
	fprintf(module->hout, ";\n");
	return 0;
}

static int
talisker_cxxinc_consts(idl_module_t *module, FILE *f, idl_interface_t *container)
{
	size_t c;
	int started;
	idl_symdef_t *sym;

	started = 0;

	for(c = 0; c < container->symlist.ndefs; c++)
	{
		sym = container->symlist.defs[c];
		if(sym->type == SYM_CONST)
		{
			if(!started)
			{
				fprintf(f, "#  ifdef __cplusplus\n");
				started = 1;
			}
			idl_emit_cxx_write_indent(module, f);
			fputs("static const ", f);
			idl_emit_cxx_builtin_type(f, sym->const_type, 0);
			putc(' ', f);
			fputs(sym->ident, f);
			fputs(" = ", f);
			idl_emit_cxx_write_expr(module, f, sym->constval);
			putc(';', f);
			putc('\n', f);
		}
	}
	if(started)
	{
		fputs("\n#  else /*__cplusplus*/\n\n", f);
		for(c = 0; c < container->symlist.ndefs; c++)
		{
			sym = container->symlist.defs[c];
			if(sym->type == SYM_CONST)
			{
				fprintf(f, "#  define %s ", sym->ident);
				idl_emit_cxx_write_expr(module, f, sym->constval);
				fputc('\n', f);
			}
		}
		fputs("#  endif /*__cplusplus*/\n\n", f);
	}
	return 0;
}

static int
talisker_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef)
{
	if(module->curintf && module->curintf->object)
	{
		return 0;
	}
	fprintf(module->hout, "#  define %s ", symdef->ident);
	idl_emit_cxx_write_expr(module, module->hout, symdef->constval);
	fputc('\n', module->hout);
	return 0;
}

static int
talisker_cxxinc_import(idl_module_t *module, idl_interface_t *intf)
{
	if(!intf->cheader)
	{
		return 0;
	}
	fprintf(module->hout, "# include <%s>\n", intf->cheader);
	return 0;
}

static void
talisker_cxxinc_methods(idl_module_t *module, FILE *f, idl_interface_t *intf)
{
	size_t c;
	int stdmethod;

	if(NULL != intf->ancestor)
	{
		fprintf(f, "# if !defined(__cplusplus)\n");
		talisker_cxxinc_methods(module, f, intf->ancestor);
		fprintf(f, "# endif /*!__cplusplus*/\n\n");
	}
	idl_emit_cxx_write_indent(module, f);
	fprintf(f, "/* %s */\n", intf->name);
	for(c = 0; c < intf->symlist.ndefs; c++)
	{
		if(1 == idl_intf_method_inherited(intf, intf->symlist.defs[c]->ident))
		{
			continue;
		}
		if(SYM_METHOD == intf->symlist.defs[c]->type)
		{
			stdmethod = 0;
			if(NULL != intf->symlist.defs[c]->decl &&
			   NULL != intf->symlist.defs[c]->decl->user_type &&
			   0 == strcmp(intf->symlist.defs[c]->decl->user_type->ident, "HRESULT"))
			{
				stdmethod = 1;
			}
			idl_emit_cxx_write_indent(module, f);
			if(stdmethod)
			{
				idl_emit_cxx_write_symdef(module, module->hout, intf->symlist.defs[c], "STDMETHOD(%s)", "THIS_ ", "THIS");
				fprintf(f, " PURE;\n");
			}
			else
			{
				fprintf(f, "STDMETHOD_(");
				idl_emit_cxx_write_type(module, f, intf->symlist.defs[c]->decl);
				idl_emit_cxx_write_symdef(module, module->hout, intf->symlist.defs[c], ", %s)", "THIS_ ", "THIS");
				fprintf(f, " PURE;\n");
			}
		}
	}
}

static int
talisker_cxxinc_method_macros(idl_module_t *module, FILE *f, idl_interface_t *curintf, idl_interface_t *intf, int written)
{
	size_t c, d;

	if(NULL != intf->ancestor)
	{
		written += talisker_cxxinc_method_macros(module, f, curintf, intf->ancestor, written);
	}
	for(c = 0; c < intf->symlist.ndefs; c++)
	{
		if(SYM_METHOD == intf->symlist.defs[c]->type)
		{
			if(1 == idl_intf_method_inherited(intf, intf->symlist.defs[c]->ident))
			{
				continue;
			}
			if(0 == written)
			{
				fprintf(f, "#  if !defined(__cplusplus)\n");
				written = 1;
			}
			fprintf(f, "#   define %s_%s(__this", curintf->name, intf->symlist.defs[c]->ident);
			for(d = 0; d < intf->symlist.defs[c]->fp_params.ndefs; d++)
			{
				fprintf(f, ", %s", intf->symlist.defs[c]->fp_params.defs[d]->ident);
			}
			fprintf(f, ") __this->lpVtbl->%s(__this", intf->symlist.defs[c]->ident);
			for(d = 0; d < intf->symlist.defs[c]->fp_params.ndefs; d++)
			{
				fprintf(f, ", %s", intf->symlist.defs[c]->fp_params.defs[d]->ident);
			}
			fputc(')', f);
			fputc('\n', f);
		}
	}
	if(0 != written && curintf == intf)
	{
		fprintf(f, "#  endif /*!__cplusplus*/\n");
	}
	return written;
}
