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

/* This is a template C/C++ header emitter; it is not actually built as
 * part of comidl
 */

static int TEMPLATE_cxxinc_init(idl_module_t *module);
static int TEMPLATE_cxxinc_done(idl_module_t *module);
static int TEMPLATE_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf);
static int TEMPLATE_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf);
static int TEMPLATE_cxxinc_cppquote(idl_module_t *module, const char *quote);
static int TEMPLATE_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int TEMPLATE_cxxinc_type(idl_module_t *module, idl_interface_t *intf, idl_typedecl_t *decl);
static int TEMPLATE_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
static int TEMPLATE_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef);

struct idl_emitter_struct idl_TEMPLATE_cxxinc_emitter = {
	TEMPLATE_cxxinc_init,
	TEMPLATE_cxxinc_done,
	TEMPLATE_cxxinc_intf_prologue,
	TEMPLATE_cxxinc_intf_epilogue,
	TEMPLATE_cxxinc_cppquote,
	TEMPLATE_cxxinc_typedef,
	TEMPLATE_cxxinc_type,
	TEMPLATE_cxxinc_method,
	TEMPLATE_cxxinc_const
};


static int
TEMPLATE_cxxinc_init(idl_module_t *module)
{
    if(1 != idl_emit_cxxinc_open(module))
	{
		return -1;
	}
	if(0 == module->headerwritten)
	{
		module->headerwritten = 1;
		/* write file header */
	}
	return 0;
}

static int
TEMPLATE_cxxinc_done(idl_module_t *module)
{
	if(module->headerwritten)
	{
		/* write file footer */
	}
	idl_emit_cxxinc_close(module);
	return 0;
}

static int
TEMPLATE_cxxinc_intf_prologue(idl_module_t *module, idl_interface_t *intf)
{
	(void) module;
	(void) intf;

	return 0;
}

static int
TEMPLATE_cxxinc_intf_epilogue(idl_module_t *module, idl_interface_t *intf)
{
	(void) module;
	(void) intf;
	
	return 0;
}

static int
TEMPLATE_cxxinc_cppquote(idl_module_t *module, const char *quote)
{
	(void) module;
	(void) quote;

	return 0;
}

static int
TEMPLATE_cxxinc_typedef(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) module;
	(void) intf;
	(void) symdef;

	return 0;
}

static int
TEMPLATE_cxxinc_type(idl_module_t *module, idl_interface_t *intf, idl_typedecl_t *decl)
{
	(void) module;
	(void) intf;
	(void) decl;

	return 0;
}

static int
TEMPLATE_cxxinc_method(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef)
{
	(void) module;
	(void) intf;
	(void) symdef;

	return 0;
}

static int
TEMPLATE_cxxinc_const(idl_module_t *module, idl_symdef_t *symdef)
{
	(void) module;
	(void) symdef;

	return 0;
}
