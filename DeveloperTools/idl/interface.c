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

idl_interface_t *
idl_intf_create(idl_module_t *module)
{
	idl_interface_t *p;
	
	if(NULL == (p = (idl_interface_t *) calloc(1, sizeof(idl_interface_t))))
	{
		return NULL;
	}
	p->cursymlist = &(p->symlist);
	idl_module_addintf(module, p);
	if(module->houtname)
	{
		idl_intf_set_cheader(p, module->houtname);
	}
	return p;
}

idl_interface_t *
idl_intf_stub(idl_module_t *module, const char *name)
{
	idl_interface_t *p;
	idl_typedecl_t *typedecl;
	idl_symdef_t *sym;
	
	if(NULL == (p = (idl_interface_t *) calloc(1, sizeof(idl_interface_t))))
	{
		return NULL;
	}
	p->cursymlist = &(p->symlist);
	p->stub = 1;
	idl_module_addintf(module, p);
	idl_intf_name(p, name);
	typedecl = idl_module_typedecl_push(module);
	typedecl->builtin_type = TYPE_INTERFACE;
	sym = idl_module_symdef_create(module, &(p->symlist), typedecl);
	sym->type = SYM_TYPEDEF;
	strcpy(sym->ident, p->name);
	idl_module_symdef_add(module, &(p->symlist), sym);
	idl_module_typedecl_pop(module);
	fprintf(stderr, "added stub '%s'\n", name);
	return p;
}

idl_interface_t *
idl_intf_lookup(const char *name)
{
	return idl_module_lookupintf(name, 1);
}

int
idl_intf_done(idl_interface_t *intf)
{
	return idl_module_doneintf(intf->module, intf);
}

int
idl_intf_resolve(idl_interface_t *intf)
{
	if(intf->resolved)
	{
		return 0;
	}
	if(intf->stub)
	{
		if(intf->target)
		{
			intf->resolved = 1;
			return idl_intf_resolve(intf->target);
		}
		intf->target = idl_module_lookupintf(intf->name, 0);
		if(!intf->target)
		{
			idl_module_errmsg(intf->module, 0, "unable to resolve interface '%s'\n", intf->name);
			return -1;
		}
		intf->resolved = 1;
		return 0;
	}
	if(intf->ancestor && intf->ancestor->stub)
	{
		if(idl_intf_resolve(intf->ancestor))
		{
			return -1;
		}
		intf->ancestor = intf->ancestor->target;
	}
	intf->resolved = 1;
	return 0;
}

int
idl_intf_started(idl_interface_t *intf)
{
	uint8_t nulldata[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int hasuuid, needuuid;
	idl_typedecl_t *typedecl;
	idl_symdef_t *sym;
	
	if(intf->type == BLOCK_INTERFACE)
	{
		if(intf->object)
		{
			needuuid = 1;
		}
		else if(0 == intf->local)
		{
			needuuid = -1;
		}
	}
	else if(intf->type == BLOCK_COCLASS)
	{
		needuuid = 1;
	}
	if(!intf->uuid.data1 && !intf->uuid.data2 && !intf->uuid.data3 &&
		0 == memcmp(nulldata, intf->uuid.data4, 8))
	{
		hasuuid = 0;
	}
	else
	{
		hasuuid = 1;
	}
	if(1 == needuuid)
	{
		if(0 == hasuuid)
		{
			idl_module_error(intf->module, yyget_lineno(intf->module->scanner), "The uuid() attribute is required for the definition of %s", intf->name);
		}
	}
	else if(0 == needuuid)
	{
		if(1 == hasuuid)
		{
			idl_module_warning(intf->module, yyget_lineno(intf->module->scanner), "The uuid() attribute should not be specified for the definition of %s", intf->name);
		}
	}
	if(0 != hasuuid)
	{
		idl_module_addguid(intf->module, &(intf->uuid));
	}
	typedecl = idl_module_typedecl_push(intf->module);
	typedecl->builtin_type = TYPE_INTERFACE;
	sym = idl_module_symdef_create(intf->module, &(intf->symlist), typedecl);
	sym->type = SYM_TYPEDEF;
	strcpy(sym->ident, intf->name);
	idl_module_symdef_add(intf->module, &(intf->symlist), sym);
	idl_module_typedecl_pop(intf->module);
	return 0;
}

int
idl_intf_finished(idl_interface_t *intf)
{
	(void) intf;

	return 0;
}

int
idl_intf_uuid(idl_interface_t *intf, const char *uuid)
{
	unsigned int tmp1, tmp2, tmp3, tmp4[8];
	size_t c;
	
	sscanf(uuid, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		&(tmp1), &(tmp2), &(tmp3),
		&(tmp4[0]), &(tmp4[1]),
		&(tmp4[2]), &(tmp4[3]), &(tmp4[4]), 
		&(tmp4[5]), &(tmp4[6]), &(tmp4[7]));
	intf->uuid.data1 = tmp1;
	intf->uuid.data2 = tmp2;
	intf->uuid.data3 = tmp3;
	for(c = 0; c < 8; c++)
	{
		intf->uuid.data4[c] = tmp4[c];
	}
	return 0;
}

int
idl_intf_name(idl_interface_t *intf, const char *name)
{
	strncpy(intf->name, name, IDL_IDENT_MAX);
	intf->name[IDL_IDENT_MAX] = 0;
	switch(intf->type)
	{
		case BLOCK_INTERFACE:
			strcpy(intf->uuid.name, "IID_");
			break;
		case BLOCK_COCLASS:
			strcpy(intf->uuid.name, "CLSID_");
			break;
		default:
			strcpy(intf->uuid.name, "GUID_");
			break;
	}
	strcat(intf->uuid.name, intf->name);
	return 0;
}

int
idl_intf_set_cheader(idl_interface_t *intf, const char *header)
{
	char *p;

	p = strdup(header);
	if(!p)
	{
		abort();
	}
	free(intf->cheader);
	intf->cheader = p;

	return 0;
}

idl_symdef_t *
idl_intf_symdef_create(idl_interface_t *intf, idl_typedecl_t *typedecl)
{
	return idl_module_symdef_create(intf->module, intf->cursymlist, typedecl);
}

int
idl_intf_symdef_done(idl_interface_t *intf, idl_symdef_t *symdef)
{
	return idl_module_symdef_done(intf->module, intf->cursymlist, symdef);
}

int
idl_intf_symdef_link(idl_interface_t *intf, idl_symdef_t *symdef)
{
	return idl_module_symdef_link(intf->module, intf->cursymlist, symdef);
}

idl_symdef_t *
idl_intf_symdef_lookup(idl_interface_t *intf, const char *name)
{
	return idl_module_symdef_lookup(intf->module, intf->cursymlist, name, 1);
}

int
idl_intf_symlist_push(idl_interface_t *intf, idl_symlist_t *symlist)
{
	idl_module_symlist_push(intf->module, symlist);
	intf->cursymlist = intf->module->cursymlist;
	return 0;
}

int
idl_intf_symlist_pop(idl_interface_t *intf, idl_symlist_t *symlist)
{
	idl_module_symlist_pop(intf->module, symlist);
	intf->cursymlist = intf->module->cursymlist;
	return 0;
}

int
idl_intf_method_exists(idl_interface_t *intf, const char *methodname)
{
	size_t c;
	
	for(c = 0; c < intf->symlist.ndefs; c++)
	{
		if(SYM_METHOD == intf->symlist.defs[c]->type)
		{
			if(0 == strcmp(intf->symlist.defs[c]->ident, methodname))
			{
				return 1;
			}
		}
	}
	return 0;
}

int
idl_intf_method_exists_recurse(idl_interface_t *intf, const char *methodname)
{
	if(1 == idl_intf_method_exists(intf, methodname))
	{
		return 1;
	}
	if(NULL == intf->ancestor)
	{
		return 0;
	}
	return idl_intf_method_exists_recurse(intf->ancestor, methodname);
}

int
idl_intf_method_inherited(idl_interface_t *intf, const char *methodname)
{
	if(NULL == intf->ancestor)
	{
		return 0;
	}
	if(1 == idl_intf_method_exists_recurse(intf->ancestor, methodname))
	{
		return 1;
	}
	return 0;
}
