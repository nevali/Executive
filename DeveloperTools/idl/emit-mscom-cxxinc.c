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

/* Emit C/C++ includes in MSCOM mode */

static int mscom_cxxinc_init(idl_module_t *module);
static int mscom_cxxinc_done(idl_module_t *module);
static int mscom_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf);
static int mscom_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf);
static int mscom_cxxinc_cppquote(idl_module_t *module, const char *quote);
static int mscom_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int mscom_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int mscom_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef);
static int mscom_cxxinc_import(idl_module_t *module, idl_interface_t *intf);
static void mscom_cxxinc_methods(idl_module_t *module, FILE *f, idl_interface_t *intf);
static int mscom_cxxinc_method_macros(idl_module_t *module, FILE *f, idl_interface_t *curintf, idl_interface_t *intf, int written);

struct idl_emitter_struct idl_mscom_cxxinc_emitter = {
	mscom_cxxinc_init,
	mscom_cxxinc_done,
	mscom_cxxinc_intf_prologue,
	mscom_cxxinc_intf_epilogue,
	mscom_cxxinc_cppquote,
	mscom_cxxinc_typedef,
	mscom_cxxinc_method,
	mscom_cxxinc_const,
	mscom_cxxinc_import
};


static int
mscom_cxxinc_init(idl_module_t *module)
{
	size_t c;
	FILE *f;
	
    if(1 != idl_emit_cxxinc_open(module))
	{
		return -1;
	}
	if(0 == module->headerwritten)
	{
		module->headerwritten = 1;
		f = module->hout;
		if(!module->nodefinc)
		{
			fprintf(f, "#ifndef __REQUIRED_RPCNDR_H_VERSION__\n"
					"# define __REQUIRED_RPCNDR_H_VERSION__ 500\n"
					"#endif\n"
					"\n"
					"#ifndef __REQUIRED_RPCSAL_H_VERSION__\n"
					"# define __REQUIRED_RPCSAL_H_VERSION__ 100\n"
					"#endif\n"
					"\n"
					"#include <rpc.h>\n"
					"#include <rpcndr.h>\n"
					"\n"
					"#ifndef COM_NO_WINDOWS_H\n"
					"#include <windows.h>\n"
					"#include <ole2.h>\n"
					"#endif\n"
					"\n");
		}
		fprintf(f, "#ifndef __%s__\n", module->hmacro);
		fprintf(f, "# define __%s__\n\n", module->hmacro);
		for(c = 0; c < module->ninterfaces; c++)
		{
			if(module->interfaces[c]->type == BLOCK_INTERFACE &&
				module->interfaces[c]->object)
			{
				fprintf(f, "# ifndef __%s_FWD_DEFINED__\n", module->interfaces[c]->name);
				fprintf(f, "#  define __%s_FWD_DEFINED__\n", module->interfaces[c]->name);
				fprintf(f, "typedef struct %s %s;\n", module->interfaces[c]->name, module->interfaces[c]->name);
				fprintf(f, "# endif\n\n");
			}
		}
	}
	return 0;
}

static int
mscom_cxxinc_done(idl_module_t *module)
{
	size_t c;

	if(module->headerwritten)
	{
		fprintf(module->hout, "\n#endif /*!__%s__*/\n", module->hmacro);
		for(c = 0; c < module->nguids; c++)
		{
			fprintf(module->hout, "\n/* %s = {%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x} */\n",
					module->guids[c]->name,
					module->guids[c]->data1, module->guids[c]->data2, module->guids[c]->data3,
					module->guids[c]->data4[0], module->guids[c]->data4[1],
					module->guids[c]->data4[2], module->guids[c]->data4[3], module->guids[c]->data4[4],
					module->guids[c]->data4[5], module->guids[c]->data4[6], module->guids[c]->data4[7]);
			fprintf(module->hout, "DEFINE_GUID(%s, 0x%08X, 0x%04X, 0x%04X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X);\n",
					module->guids[c]->name,
					module->guids[c]->data1, module->guids[c]->data2, module->guids[c]->data3,
					module->guids[c]->data4[0], module->guids[c]->data4[1],
					module->guids[c]->data4[2], module->guids[c]->data4[3], module->guids[c]->data4[4],
					module->guids[c]->data4[5], module->guids[c]->data4[6], module->guids[c]->data4[7]);
		}
	}
	idl_emit_cxxinc_close(module);
	return 0;
}

static int
mscom_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf)
{
	FILE *f;
	unsigned major, minor;

	f = module->hout;
	major = (unsigned int) (intf->version >> 16);
	minor = (unsigned int) (intf->version & 0xFFFF);
	fprintf(f, "\n/* %s version %u.%u */\n\n", intf->name, major, minor);
	fprintf(f, "# ifndef __%s_INTERFACE_DEFINED__\n", intf->name);
	fprintf(f, "#  define __%s_INTERFACE_DEFINED__\n", intf->name);
	fprintf(f, "#  define INTERFACE %s\n\n", intf->name);
	return 0;
}

static int
mscom_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf)
{
	FILE *f;

	f = module->hout;

	if(intf->object)
	{
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
		mscom_cxxinc_methods(module, f, intf);
		fputc('\n', f);
		idl_emit_cxx_write_indent(module, f);
		fprintf(f, "END_INTERFACE\n");
		module->houtdepth--;
		fprintf(f, "};\n\n");
		mscom_cxxinc_method_macros(module, f, intf, intf, 0);
	}
	fprintf(f, "#  undef INTERFACE\n");
	fprintf(f, "# endif /*!__%s_INTERFACE_DEFINED__*/\n\n", intf->name);
	return 0;
}

static int
mscom_cxxinc_cppquote(idl_module_t *module, const char *quote)
{
	fprintf(module->hout, "%s\n", quote);
	return 0;
}

static int
mscom_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) intf;

	fprintf(module->hout, "typedef ");
	idl_emit_cxx_write_sym(module, module->hout, symdef, NULL);
	fputc(';', module->hout);
	fputc('\n', module->hout);
	return 0;
}

static int
mscom_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
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
mscom_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef)
{
	fprintf(module->hout, "#  define %s ", symdef->ident);
	idl_emit_cxx_write_expr(module, module->hout, symdef->constval);
	fputc('\n', module->hout);
	return 0;
}

static int
mscom_cxxinc_import(idl_module_t *module, idl_interface_t *intf)
{
	if(!intf->cheader)
	{
		return 0;
	}
	fprintf(module->hout, "# include <%s>\n", intf->cheader);
	return 0;
}

static void
mscom_cxxinc_methods(idl_module_t *module, FILE *f, idl_interface_t *intf)
{
	size_t c;
	int stdmethod;

	if(NULL != intf->ancestor)
	{
		fprintf(f, "# if !defined(__cplusplus) || defined(CINTERFACE)\n");
		mscom_cxxinc_methods(module, f, intf->ancestor);
		fprintf(f, "# endif /*!__cplusplus || CINTERFACE*/\n\n");
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
mscom_cxxinc_method_macros(idl_module_t *module, FILE *f, idl_interface_t *curintf, idl_interface_t *intf, int written)
{
	size_t c, d;

	if(NULL != intf->ancestor)
	{
		written += mscom_cxxinc_method_macros(module, f, curintf, intf->ancestor, written);
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
				fprintf(f, "#  if defined(COBJMACROS)\n");
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
		fprintf(f, "#  endif /*COBJMACROS*/\n");
	}
	return written;
}


#if 0

static void
idl_emit_cxxinc_write_header(idl_module_t *module)
{

	if(0 == nodefinc && 0 == module->nodefinc)
	{
		if(MODE_RPC == module->mode)
		{
			fprintf(module->hout, "\n# include \"DCE-RPC/idlbase.h\"\n");
			if(0 == nodefimports && 0 == module->nodefimports)
			{
				/* This corresponds to the default import of nbase.idl */
				fprintf(module->hout, "# include \"DCE-RPC/nbase.h\"\n");
			}
		}
		else if(MODE_COM == module->mode)
		{
			fprintf(module->hout, "\n# include \"COM/COM.h\"\n");
		}
		else if(MODE_MSCOM == module->mode)
		{
		}
		else if(MODE_DCERPC == module->mode)
		{
			fprintf(module->hout, "\n# include <nbase.h>\n");
		}
		else if(MODE_SUNRPC == module->mode)
		{
			fprintf(module->hout, "\n# include <rpc/rpc.h>\n");
		}
		else if(MODE_XPCOM == module->mode)
		{
			fprintf(module->hout, "\n# ifndef NS_NO_VTABLE\n");
			fprintf(module->hout, "#  define NS_NO_VTABLE\n");
			fprintf(module->hout, "# endif\n");
		}
	}
	fputc('\n', module->hout);
}

static void
idl_emit_cxxinc_write_footer(idl_module_t *module)
{
}

#endif
