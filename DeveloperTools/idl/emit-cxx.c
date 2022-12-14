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

/* Utilities for emitting C/C++ */

int
idl_emit_cxxinc_open(idl_module_t *module)
{
	if(module->hout)
	{
		return 1;
	}
	if(NULL != module->houtname)
	{
		if(NULL == (module->hout = fopen(module->houtname, "w")))
		{
			fprintf(stderr, "%s: %s: %s\n", progname, module->houtname, strerror(errno));
			exit(EXIT_FAILURE);
		}
		fprintf(module->hout, "/* DO NOT EDIT: Automatically generated from %s by %s */\n\n", module->shortname, progname);
		return 1;
	}
	return 0;
}

void
idl_emit_cxxinc_close(idl_module_t *module)
{
	if(NULL != module->hout)
	{
		fclose(module->hout);
		module->hout = NULL;
	}
}

void
idl_emit_cxx_write_expr(idl_module_t *module, FILE *f, const idl_expr_t *expr)
{
	if(EXPR_CONST == expr->type)
	{
		fprintf(f, "%ld", (long) expr->constval);
		return;
	}
	if(EXPR_SYM == expr->type)
	{
		fprintf(f, "%s", expr->symdef->ident);
	}
	if(EXPR_BRACKET == expr->type)
	{
		fputc('(', f);
	}
	if(NULL != expr->left)
	{
		idl_emit_cxx_write_expr(module, f, expr->left);
	}
	switch(expr->type)
	{
		case EXPR_ADD: fputc('+', f); break;
		case EXPR_SUB: fputc('-', f); break;
		case EXPR_MUL: fputc('*', f); break;
		case EXPR_DIV: fputc('/', f); break;
		case EXPR_MOD: fputc('%', f); break;
		case EXPR_AND: fputc('&', f); fputc('&', f); break;
		case EXPR_BITAND: fputc('&', f); break;
		case EXPR_OR: fputc('|', f); fputc('|', f); break;
		case EXPR_BITOR: fputc('|', f); break;
		case EXPR_XOR: fputc('^', f); break;
		case EXPR_EQUALS: fputc('=', f); fputc('=', f); break;
		case EXPR_NOTEQUALS: fputc('!', f); fputc('=', f); break;
		case EXPR_LESSEQUALS: fputc('<', f); fputc('=', f); break;
		case EXPR_GTEQUALS: fputc('>', f); break;
		case EXPR_LESS: fputc('<', f); break;
		case EXPR_GT: fputc('>', f); break;
		case EXPR_BITNOT: fputc('~', f); break;
		case EXPR_NOT: fputc('!', f); break;
		case EXPR_LSHIFT: fputc('<', f); fputc('<', f); break;
		case EXPR_RSHIFT: fputc('>', f); fputc('>', f); break;
		case EXPR_IFELSE: fputc('?', f); break;
		case EXPR_BRACKET:
		case EXPR_UNSPEC:
		case EXPR_CONST:
		case EXPR_SYM:
			/* nothing */
			break;
	}
	if(NULL != expr->right)
	{
		idl_emit_cxx_write_expr(module, f, expr->right);
	}
	
	if(EXPR_BRACKET == expr->type)
	{
		fputc(')', f);
	}
}

void
idl_emit_cxx_builtin_type(FILE *f, idl_builtintype_t type, idl_typemod_t modifiers)
{
	if(type == TYPE_CHAR ||
		type == TYPE_INT ||
		type == TYPE_LONG ||
		type == TYPE_LONGLONG)
	{
		if(modifiers & TYPEMOD_UNSIGNED)
		{
			fprintf(f, "unsigned ");
		}
		else if(modifiers & TYPEMOD_SIGNED)
		{
			fprintf(f, "signed ");
		}
	}
	switch(type)
	{
		case TYPE_VOID:
			fprintf(f, "void");
			break;
		case TYPE_CHAR:
			fprintf(f, "char");
			break;
		case TYPE_INT:
			fprintf(f, "int");
			break;
		case TYPE_LONG:
			fprintf(f, "long");
			break;
		case TYPE_LONGLONG:
			fprintf(f, "long long");
			break;
		case TYPE_SHORT:
			fprintf(f, "short");
			break;
		case TYPE_FLOAT:
			fprintf(f, "float");
			break;
		case TYPE_DOUBLE:
			fprintf(f, "double");
			break;
		case TYPE_BOOLEAN:
			fprintf(f, "bool");
			break;
		case TYPE_INT8:
			if(modifiers & TYPEMOD_UNSIGNED)
			{
				fprintf(f, "uint8_t");
			}
			else
			{
				fprintf(f, "int8_t");
			}
			break;
		case TYPE_INT16:
			if(modifiers & TYPEMOD_UNSIGNED)
			{
				fprintf(f, "uint16_t");
			}
			else
			{
				fprintf(f, "int16_t");
			}
			break;
		case TYPE_INT32:
			if(modifiers & TYPEMOD_UNSIGNED)
			{
				fprintf(f, "uint32_t");
			}
			else
			{
				fprintf(f, "int32_t");
			}
			break;
		case TYPE_INT64:
			if(modifiers & TYPEMOD_UNSIGNED)
			{
				fprintf(f, "uint64_t");
			}
			else
			{
				fprintf(f, "int64_t");
			}
			break;
		default:
			break;
	}
}

void
idl_emit_cxx_write_type(idl_module_t *module, FILE *f, idl_typedecl_t *decl)
{
	size_t c;
	
	(void) module;
	
	if(NULL == decl || TYPE_NONE == decl->builtin_type)
	{
		return;
	}
	if(decl->modifiers & TYPEMOD_CONST)
	{
		fprintf(f, "const ");
	}
	switch(decl->builtin_type)
	{
	case TYPE_STRUCT:
		fprintf(f, "struct %s", decl->tag);
		break;
	case TYPE_UNION:
		fprintf(f, "union %s", decl->tag);
		break;
	case TYPE_ENUM:
		fprintf(f, "enum %s", decl->tag);
		break;
	case TYPE_INTERFACE:
		fprintf(f, "cominterface %s", decl->tag);
		break;
	case TYPE_DEF:
		fprintf(f, "%s", decl->user_type->ident);
		break;
	default:
		idl_emit_cxx_builtin_type(f, decl->builtin_type, decl->modifiers);
	}
	if(decl->has_symlist)
	{
		fputc('\n', f);
		idl_emit_cxx_write_indent(module, f);
		fputc('{', f);
		fputc('\n', f);
		module->houtdepth++;
		for(c = 0; c < decl->symlist.ndefs; )
		{
			idl_emit_cxx_write_indent(module, f);
			c += idl_emit_cxx_write_sym(module, f, decl->symlist.defs[c], NULL);
			if(TYPE_ENUM == decl->builtin_type)
			{
				if(c < decl->symlist.ndefs)
				{
					fputc(',', f);
				}
			}
			else
			{
				fputc(';', f);
			}
			fputc('\n', f);
		}
		module->houtdepth--;
		idl_emit_cxx_write_indent(module, f);
		fputc('}', f);
		fputc(' ', f);
	}
}

void
idl_emit_cxx_write_symdef(idl_module_t *module, FILE *f, idl_symdef_t *symdef, const char *fmt, const char *paramprefix, const char *voidstr)
{
	size_t c;

	(void) module;
	
	if(NULL == paramprefix)
	{
		paramprefix = "";
	}
	if(NULL == voidstr)
	{
		voidstr = "void";
	}
	if(SYM_ENUM == symdef->type)
	{
		/* enum values are handled slightly differently */
		idl_emit_cxx_write_indent(module, f);
		if(symdef->noval)
		{
			fprintf(f, "%s", symdef->ident);
		}
		else
		{
			fprintf(f, "%s = ", symdef->ident);
			idl_emit_cxx_write_expr(module, f, symdef->constval);
		}
		return;
	}
	for(c = 0; c < symdef->ndeclarator; c++)
	{
		switch(symdef->declarator[c])
		{
			case DECL_POINTER:
				fputc('*', f);
				if(symdef->declarator[c + 1] == DECL_CONST ||
					symdef->declarator[c + 1] == DECL_RESTRICT)
				{
					fputc(' ', f);
				}
				break;
			case DECL_CONST:
				fprintf(f, "const ");
				break;
			case DECL_RESTRICT:
				fprintf(f, "restrict ");
				break;
			case DECL_LBRACKET:
				fputc('(', f);
				break;
			case DECL_RBRACKET:
				fputc(')', f);
				break;
			case DECL_IDENT:
				fprintf(f, fmt, symdef->ident);
				break;
		}
	}
	if(1 == symdef->is_fp || SYM_METHOD == symdef->type)
	{
		if(0 == symdef->fp_params.ndefs)
		{
			fprintf(f, "(%s)", voidstr);
		}
		else
		{
			fprintf(f, "(%s", paramprefix);
			for(c = 0; c < symdef->fp_params.ndefs; c++)
			{
				/* We never chain in a list of function parameters */
				symdef->fp_params.defs[c]->nextsym = NULL;
				idl_emit_cxx_write_sym(module, f, symdef->fp_params.defs[c], NULL);
				if(c < symdef->fp_params.ndefs - 1)
				{
					fputc(',', f);
					fputc(' ', f);
				}
			}
			fputc(')', f);
		}
	}
	if(symdef->is_array)
	{
		fputc('[', f);
		if(symdef->array_len > 0)
		{
			fprintf(f, "%d", (int) symdef->array_len);
		}
		else
		{
			fputc('1', f);
		}
		fputc(']', f);
	}
}

int
idl_emit_cxx_write_sym(idl_module_t *module, FILE *f, idl_symdef_t *symdef, const char *fmt)
{
	idl_symdef_t *p;
	int c;
	
	if(NULL == fmt)
	{
		fmt = "%s";
	}
	c = 0;
	idl_emit_cxx_write_type(module, f, symdef->decl);
	fputc(' ', f);
	for(p = symdef; p; p = p->nextsym)
	{
		if(p != symdef)
		{
			fputc(',', module->hout);
			fputc(' ', module->hout);
		}
		idl_emit_cxx_write_symdef(module, module->hout, p, fmt, NULL, NULL);
		c++;
	}
	return c;
}

void
idl_emit_cxx_write_indent(idl_module_t *module, FILE *f)
{
	size_t c, depth;
   
	if(f == module->hout)
	{
		depth = module->houtdepth;
	}
	else
	{
		return;
	}
	for(c = 0; c < depth; c++)
	{
		fputc('\t', f);
	}
}

