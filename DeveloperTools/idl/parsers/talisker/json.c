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

const char *
idl_json_filename(idl_module_t *module)
{
	json_t *fn;
	size_t c;
	
	if(!module->irroot)
	{
		return NULL;
	}
	for(c = module->irsp + 1; c > 0; c--)
	{
		fn = json_object_get(module->irstack[c - 1], "@file");
		if(fn)
		{
			return json_string_value(fn);
		}
	}
	return NULL;
}

json_t *
idl_json_push_as(idl_module_t *module, const char *type, const char *target, YYLTYPE *loc)
{
	json_t *self, *parent;
	const char *prevfn;
	static int index;
	
	self = json_object();
	if(type)
	{
		json_object_set_new(self, "@class", json_string(type));
	}
	if(loc)
	{
		json_object_set_new(self, "@line", json_integer(loc->first_line));
		if(loc->filename)
		{
			prevfn = idl_json_filename(module);
			if(!prevfn && module->irroot)
			{
				/* If there isn't a previous filename, and a root module
				 * already exists, update it
				 */
				json_object_set_new(module->irroot, "@file", json_string(loc->filename));
				prevfn = idl_json_filename(module);
			}
			if(!prevfn || strcmp(prevfn, loc->filename))
			{
				json_object_set_new(self, "@file", json_string(loc->filename));
			}
		}
	}
	json_object_set_new(self, "@index", json_integer(index));
	index++;
	if(module->ir)
	{
		if(module->irtype)
		{
			json_object_set_new(module->ir, "@irtype", module->irtype);
			module->irtype = NULL;
		}
		parent = json_object_get(module->ir, target);
		if(!parent || !json_is_array(parent))
		{
			parent = json_array();
			json_object_set_new(module->ir, target, parent);
		}
		json_array_append_new(parent, self);
		module->irsp++;
		module->irstack[module->irsp] = self;
		module->ir = self;
	}
	else
	{
		module->irroot = self;
		module->ir = self;
		module->irstack[0] = self;
		module->irsp = 0;
	}
	if(module->pending)
	{
		json_object_set_new(self, "attrs", module->pending);
		module->pending = NULL;
	}
	/* Note that 'self' is a borrowed reference now */
	return self;
}

json_t *
idl_json_push(idl_module_t *module, const char *type, YYLTYPE *loc)
{
	return idl_json_push_as(module, type, "@", loc);
}


int
idl_json_pop(idl_module_t *module)
{
	if(module->pending)
	{
		json_decref(module->pending);
		module->pending = NULL;
	}
	if(module->irtype)
	{
		idl_json_pop_type(module);
	}
	if(module->irsp)
	{
		module->irsp--;
		module->ir = module->irstack[module->irsp];
	}
	else
	{
		if(module->irroot)
		{
			json_decref(module->irroot);
		}
		module->irroot = NULL;
		module->ir = NULL;
		module->irsp = 0;
	}
	module->irtype = NULL;
	if(module->ir)
	{
		module->irtype = json_object_get(module->ir, "@irtype");
		if(module->irtype)
		{
			json_incref(module->irtype);
			json_object_del(module->ir, "@irtype");
		}
	}
	return 0;
}

int
idl_json_attr(idl_module_t *module, const char *attr, json_t *value)
{
	if(!module->pending)
	{
		module->pending = json_object();
	}
	json_object_set_new(module->pending, attr, value);
	return 0;
}


json_t *
idl_json_push_type(idl_module_t *module)
{
	json_t *self;
	
	self = json_object();
	assert(module->irtype == NULL);
	module->irtype = self;
	json_object_set_new(module->irtype, "@target", json_string("type"));
	return self;
}

int
idl_json_pop_type(idl_module_t *module)
{
	json_t *target, *irtype;
	
	if(!module->irtype)
	{
		return 0;
	}
	irtype = module->irtype;
	target = json_object_get(irtype, "@target");
	module->irtype = NULL;
	if(target)
	{
		json_object_set_new(module->ir, json_string_value(target), irtype);
		json_object_del(irtype, "@target");
	}
	else
	{
		json_decref(irtype);
	}
	return 0;
}

int
idl_json_type_attr(idl_module_t *module, const char *attr, json_t *value)
{
	json_t *attrs;
	
	if(module->irtype)
	{
		if(!(attrs = json_object_get(module->irtype, "attrs")))
		{
			attrs = json_object();
			json_object_set_new(module->irtype, "attrs", attrs);
		}
		json_object_set_new(attrs, attr, value);
	}
	return 0;
}


int
idl_json_pointer(idl_module_t *module, const char *ptrtype)
{
	json_t *list;
	
	if(module->ir)
	{
		if(!(list = json_object_get(module->ir, "pointer")))
		{
			list = json_array();
			json_object_set_new(module->ir, "pointer", list);
		}
		json_array_append_new(list, json_string(ptrtype));
	}
	return 0;
}

