%{
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

/*
 * Copyright (c) 2007, Novell, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Novell, Inc. nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * 
 * (c) Copyright 1989 OPEN SOFTWARE FOUNDATION, INC.
 * (c) Copyright 1989 HEWLETT-PACKARD COMPANY
 * (c) Copyright 1989 DIGITAL EQUIPMENT CORPORATION
 * To anyone who acknowledges that this file is provided "AS IS"
 * without any express or implied warranty:
 *                 permission to use, copy, modify, and distribute this
 * file for any purpose is hereby granted without fee, provided that
 * the above copyright notices and this notice appears in all source
 * code copies, and that none of the names of Open Software
 * Foundation, Inc., Hewlett-Packard Company, or Digital Equipment
 * Corporation be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.  Neither Open Software Foundation, Inc., Hewlett-
 * Packard Company, nor Digital Equipment Corporation makes any
 * representations about the suitability of this software for any
 * purpose.
 * 
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_comidl.h"

static char vertmp[64];

void
yyerror(void *scanner, char *s)
{
	idl_module_error(curmod, yyget_lineno(scanner), "%s", s);
}

%}

/* Options */

%start module
%pure-parser
%lex-param { void *scanner }
%parse-param { void *scanner }
%error-verbose

/* Keywords */
%token ALIGN_KW
%token ARRAY_KW
%token ASTRING_KW

%token BINARYNAME_KW
%token BOOLEAN_KW
%token BROADCAST_KW
%token BYTE_KW

%token CALL_AS_KW
%token CASE_KW
%token CHAR_KW
%token COCLASS_KW
%token CONST_KW
%token COMM_STATUS_KW
%token CONTEXT_HANDLE_KW
%token CPP_QUOTE_KW
%token CSTRING_KW
%token CHEADER_KW

%token DEFAULT_KW
%token DISPINTERFACE_KW
%token DOMSTRING_KW
%token DOUBLE_KW

%token ENDPOINT_KW
%token ENUM_KW
%token EXCEPTIONS_KW

%token FALSE_KW
%token FIRST_IS_KW
%token FLOAT_KW
%token FUNCTION_KW

%token HANDLE_KW
%token HANDLE_T_KW
%token HYPER_KW

%token ID_KW
%token IDEMPOTENT_KW
%token IGNORE_KW
%token IID_IS_KW
%token IMPLICIT_HANDLE_KW
%token IMPORT_KW
%token IN_KW
%token INOUT_KW
%token INT_KW
%token INTERFACE_KW

%token LAST_IS_KW
%token LENGTH_IS_KW
%token LIBRARY_KW
%token LOCAL_KW
%token LONG_KW

%token MAX_IS_KW
%token MAYBE_KW
%token MIN_IS_KW
%token MODE_KW
%token MODULE_KW
%token MUTABLE_KW

%token NULL_KW
%token NATIVE_KW
%token NODEFINC_KW
%token NOSCRIPT_KW
%token NOTXPCOM_KW
%token NSID_KW

%token OCTET_KW
%token OUT_KW
%token OBJECT_KW

%token PIPE_KW
%token PROGRAM_KW
%token POINTER_DEFAULT_KW
%token PTR_KW

%token RANGE_KW
%token REF_KW
%token REFLECT_DELETIONS_KW
%token REMOTE_KW
%token RESTRICT_KW
%token RETVAL_KW

%token SCRIPTABLE_KW
%token SECURE_KW
%token SHAPE_KW
%token SHORT_KW
%token SIGNED_KW
%token SIZE_IS_KW
%token SMALL_KW
%token STRING_KW
%token STRUCT_KW
%token SWITCH_KW
%token SWITCH_IS_KW
%token SWITCH_TYPE_KW

%token TRUE_KW
%token TRANSMIT_AS_KW
%token TYPEDEF_KW

%token UNION_KW
%token UNIQUE_KW
%token UNSIGNED_KW
%token UTF8STRING_KW
%token UUID_KW

%token V1_ARRAY_KW
%token V1_ENUM_KW
%token V1_STRING_KW
%token V1_STRUCT_KW
%token VERSION_KW
%token VOID_KW

%token WCHAR_KW
%token WIRE_MARSHAL_KW
%token WSTRING_KW

/*  Non-keyword tokens      */

%token UUID

/*  Punctuation             */

%token COLON
%token COMMA
%token DOTDOT
%token EQUAL
%token LBRACE
%token LBRACKET
%token LPAREN
%token RBRACE
%token RBRACKET
%token RPAREN
%token SEMI
%token STAR
%token QUESTION
%token BAR
%token BARBAR
%token LANGLE
%token LANGLEANGLE
%token RANGLE
%token RANGLEANGLE
%token AMP
%token AMPAMP
%token LESSEQUAL
%token GREATEREQUAL
%token EQUALEQUAL
%token CARET
%token PLUS
%token MINUS
%token NOT
%token NOTEQUAL
%token SLASH
%token PERCENT
%token TILDE
%token POUND
%token UNKNOWN  /* Something that doesn't fit in any other token class */

%token IDENTIFIER
%token STRING
%token INTEGER_NUMERIC
%token FLOAT_NUMERIC

%%

module:
		blocks
	;
	
blocks:
		block
	|	blocks block
	;
	
block:
		interface
	|	typedef_decl
	|	optional_imports
	|	cpp_quote
	;

interface:
		interface_init interface_start interface_ancestor interface_tail
		{
			idl_intf_done(curmod->curintf);
			idl_module_scope_pop(curmod);
		}
    |   INTERFACE_KW identifier SEMI
	    {
			if(!idl_intf_lookup($1))
			{
				idl_interface_t *p;

				p = idl_intf_stub(curmod, $1);
				p->type = BLOCK_INTERFACE;
			}
		}
	;

interface_start:
		interface_attributes INTERFACE_KW identifier
		{
			
			curmod->curintf->type = BLOCK_INTERFACE;
			/* TODO: name clashes */
			idl_intf_name(curmod->curintf, $3);
			idl_intf_started(curmod->curintf);
		}
	;
	
/* Include some attribute names here, too, as they can be used unambiguously
 * as identifiers.
 */

identifier:
		IDENTIFIER { $$ = $1; }
	|	UUID_KW { $$ = $1; }
	|	MODE_KW { $$ = $1; }
    |   NODEFINC_KW { $$ = $1; }
	|	STRING_KW { $$ = $1; }
	|	LOCAL_KW { $$ = $1; }
	|	OBJECT_KW { $$ = $1; }
	|	IN_KW { $$ = $1; }
	|	OUT_KW { $$ = $1; }
	|	INOUT_KW { $$ = $1; }
    |   ID_KW { $$ = $1; }
    |   PTR_KW { $$ = $1; }
    |   CHEADER_KW { $$ = $1; }
	;

interface_ancestor:
		/* Nothing */
	|	COLON identifier
		{
			if(NULL == (curmod->curintf->ancestor = idl_intf_lookup($2)))
			{
				curmod->curintf->ancestor = idl_intf_stub(curmod, $2);
/*				idl_module_error(curmod, yyget_lineno(scanner), "cannot derive %s from undefined interface %s", curmod->curintf->name, $2); */
			}
		}
	;

interface_init:
		{
			idl_scope_t *scope;

			idl_intf_create(curmod);
			scope = idl_module_scope_push(curmod);
			scope->type = ST_CONTAINER;
		}
	;

interface_tail:
		LBRACE interface_body RBRACE
		{ idl_intf_finished(curmod->curintf); }
	|	error
		{
			$$ = NULL;
			fprintf(stderr, "Parse error (2)\n");
		}
	|	error RBRACE
		{
			$$ = NULL;
			fprintf(stderr, "Parse error (3)\n");
		}
	;


interface_body:
		optional_imports exports extraneous_semi:
	;

/*
 * Interface Attributes
 *
 * Interface attributes are special--there is no cross between interface
 * attributes and other attributes (for instance on fields or types.
 */
interface_attributes:
        attribute_opener interface_attr_list extraneous_comma attribute_closer
		{
		}
    |   attribute_opener error attribute_closer
        {
			fprintf(stderr, "Some error occurred while reading attributes (%s)\n", $2);
        }

    |   /* Nothing */
    ;

interface_attr_list:
        interface_attr
    |   interface_attr_list COMMA interface_attr
    |   /* nothing */
    ;

interface_attr:
        UUID_KW error
        {
			fprintf(stderr, "Parse error (1)\n");
        }
    |   UUID_KW uuid
        {
			idl_intf_uuid(curmod->curintf, $2);
        }
    |   ENDPOINT_KW LPAREN port_list extraneous_comma RPAREN
        {
        }
    |   EXCEPTIONS_KW LPAREN excep_list extraneous_comma RPAREN
        {
        }
    |   VERSION_KW LPAREN version_number RPAREN
        {
			char *dummy;
			
			curmod->curintf->version = strtoul($3, &dummy, 0);
			$$ = $3;
        }
   |   ID_KW LPAREN INTEGER_NUMERIC RPAREN
        {
			char *dummy;
			
			curmod->curintf->id = strtoul($3, &dummy, 0);
			$$ = $3;
        }
    |   LOCAL_KW
        {
			curmod->curintf->local = 1;
			$$ = $1;
        }
	|	OBJECT_KW
		{
			curmod->curintf->object = 1;
		}
    |   POINTER_DEFAULT_KW LPAREN pointer_class RPAREN
        {
			$$ = $3;
        }
	|	MODE_KW LPAREN identifier RPAREN
		{
			idl_module_set_mode(curmod, yyget_lineno(scanner), $3);
		}
    |   NODEFINC_KW
        {
        	curmod->nodefinc = 1;
        }
    |   CHEADER_KW LPAREN STRING RPAREN
	    {
		    idl_intf_set_cheader(curmod->curintf, $3);
		}	   		
    ;

pointer_class:
	        REF_KW {  }
	    |   PTR_KW {  }
	    |   UNIQUE_KW { }
	    ;

version_number:
        INTEGER_NUMERIC
        {
			$$ = $1;
        }
   |    FLOAT_NUMERIC
        {
			unsigned long major_version, minor_version;
			
			sscanf($1,"%lu.%lu",&major_version,&minor_version);
			major_version &= 0xFFFF;
			minor_version &= 0xFFFF;
            sprintf(vertmp, "%lu", (major_version << 16) | minor_version);
			$$ = vertmp;
        }
    ;

port_list:
        port_spec
    |   port_list COMMA port_spec
    ;

excep_list:
        excep_spec
        {
        }
    |   excep_list COMMA excep_spec
        {
        }
    ;

port_spec:
        STRING
        {
        }
    ;

excep_spec:
        identifier
        {
        }
    ;

optional_imports:
        imports
    |   /* Nothing */
        {
        }
    ;

imports:
        import
    |   imports import
        {
        }
    ;

import:
        IMPORT_KW error
        {
        }
    |   IMPORT_KW error SEMI
        {
        }
    |   IMPORT_KW import_files SEMI
        {
			$$ = $2;
        }
    ;

import_files:
        import_file
    |   import_files COMMA import_file
        {
        }
    ;



import_file:
        STRING
        {
			if(-1 == idl_parse($1, NULL, 0, 1))
			{
				idl_module_terminate();
			}
        }
    ;


exports:
		/* Nothing */
	|	export
	|	exports extraneous_semi export
	;

export:
		cpp_quote
	|	typedef_decl
	|	method_decl
	|	const_decl
	|	struct_decl
	|	error
		{
			fprintf(stderr, "Parse error during exports\n");
		}
	;

attribute_opener:
        LBRACKET
        {
        }
    ;

attribute_closer:
        RBRACKET
        {
        }
    ;


extraneous_comma:
		COMMA
	|	/* nothing */
	;

extraneous_semi:
		SEMI
	|	extraneous_semi SEMI
	|	/* nothing */
    ;

typedef_decl:
		TYPEDEF_KW typedef_init type_decl pointer_ident_decl_list SEMI
		{
			idl_module_typedecl_pop(curmod);
/*			idl_intf_write_typedef(curmod->curintf, curmod->curintf->firstsym); */
			curmod->curintf->firstsym = NULL;
		}
	;
	
const_decl:
		CONST_KW const_init const_type simple_declarator EQUAL const_value SEMI
		{
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	;

struct_decl: 
		struct_init LBRACE struct_body RBRACE SEMI
		{
			idl_symdef_t *sym;

			curmod->curtype->has_symlist = 1;
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
			sym = idl_intf_symdef_create(curmod->curintf, curmod->curtype);
			curmod->cursym->type = SYM_STRUCT;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_typedecl_pop(curmod);
			idl_module_scope_pop(curmod);
/*			idl_intf_write_type(curmod->curintf, sym->decl); */
		}
	;

	
const_init:
		symdef_init
		{
			curmod->cursym->type = SYM_CONST;
		}
	;
	
const_type:
		SMALL_KW
		{
			curmod->cursym->const_type = TYPE_INT16;
		}
	|	SHORT_KW
		{
			curmod->cursym->const_type = TYPE_INT16;
		}
	|	LONG_KW
		{
			curmod->cursym->const_type = TYPE_INT32;
		}
	|	INT_KW
		{
			curmod->cursym->const_type = TYPE_INT32;
		}
	;
	
const_value:
		expression
		{
			idl_expr_t *expr = (idl_expr_t *) $1;
			
			if(0 == expr->isconst)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "expression is not constant");
			}
			curmod->cursym->constval = expr;
		}
	
method_decl:
		method_attributes type_decl method_init LPAREN fp_args_init possible_arg_list RPAREN SEMI
		{
			idl_symdef_t *fn;

			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
			fn = curmod->cursymlist->defs[curmod->cursymlist->ndefs - 1];
			curmod->cur->symdef = fn;
			idl_module_scope_pop(curmod);
/*			idl_intf_write_method(curmod->curintf, fn); */
		}
	;
	
method_attributes:
		attribute_opener method_attr_list extraneous_comma attribute_closer
	|	/* Nothing */
	;

method_attr_list:
        method_attr
    |   method_attr_list COMMA method_attr
    |   /* nothing */
    ;

method_attr:
	|	CALL_AS_KW LPAREN identifier RPAREN
        {
			/* Don't emit a vtable entry for this method; clients will
			 * use (identifier) instead.
			 */
        }
	|	LOCAL_KW
        {
			/* No stubs will be generated for this method */
        }
    |   ID_KW LPAREN INTEGER_NUMERIC RPAREN
        {
			/* Set the numeric RPC identifier for this method */
        }
	;
	
	
method_init:
		methodspec_begin declarator 
		{
/*			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_IDENT;
			curmod->cursym->ndeclarator++;
			strncpy(curmod->cursym->ident, $1, IDL_IDENT_MAX);
			curmod->cursym->ident[IDL_IDENT_MAX] = 0; */
			/* Inherit attributes from the interface */
		}
	;

methodspec_begin:
		{
			idl_scope_t *scope;
			
			curmod->cursymlist->symtype = SYM_METHOD;
			idl_intf_symdef_create(curmod->curintf, curmod->curtype);
			curmod->cursym->local = curmod->curintf->local;
			scope = idl_module_scope_push(curmod);
			scope->type = ST_SYMDEF;
		}

typedef_init:
		{
			curmod->cursymlist->symtype = SYM_TYPEDEF;
		}
	;
	
/* A single declaration (i.e., a function parameter) */
pointer_ident_decl:
		symdef_init declarator LPAREN fp_args_init possible_arg_list RPAREN possible_array
		{
			fprintf(stderr, "finished %s\n", curmod->cursym->ident);
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	symdef_init declarator possible_array
		{
			if(0 != curmod->cursym->is_fp)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "Symbol '%s' was declared as a function pointer but no arguments have been specified", curmod->cursym->ident);
			}
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	;
	
/* One or more declarations in a comma-separated list */
pointer_ident_decl_list:
		symdef_init declarator LPAREN fp_args_init_first possible_arg_list RPAREN possible_array
		{
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	symdef_init declarator possible_array
		{
			if(0 != curmod->cursym->is_fp)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "[symdef_init declarator] Symbol '%s' was declared as a function pointer but no arguments have been specified", curmod->cursym->ident);
			}
			curmod->curintf->firstsym = curmod->cursym;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	|	pointer_ident_decl_list COMMA symdef_init declarator LPAREN fp_args_init_link possible_arg_list RPAREN possible_array
		{
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	pointer_ident_decl_list COMMA symdef_init declarator possible_array
		{
			if(0 != curmod->cursym->is_fp)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "Symbol '%s' was declared as a function pointer but no arguments have been specified", curmod->cursym->ident);
			}
			idl_intf_symdef_link(curmod->curintf, curmod->cursym);
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	|	error
		{
			fprintf(stderr, "Parse error on line %d while parsing pointer_ident_decl_list\n", yyget_lineno(scanner));
		}
	;
	
declarator:
		pointer_decl direct_declarator
	|	direct_declarator
	|	error
		{
			fprintf(stderr, "Error in declarator\n");
		}
	;

simple_declarator:
		identifier
		{
			strncpy(curmod->cursym->ident, $1, IDL_IDENT_MAX);
			curmod->cursym->ident[IDL_IDENT_MAX] = 0;
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_IDENT;
			curmod->cursym->ndeclarator++;
		}
	;
	
direct_declarator:
		LPAREN fnpointer_init declarator RPAREN
		{
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_RBRACKET;
			curmod->cursym->ndeclarator++;
		}
	|	simple_declarator
	|	error
		{
			fprintf(stderr, "Error in direct_declarator\n");
		}
	;
	
possible_array:
		LBRACKET STAR RBRACKET
		{
			curmod->cursym->is_array = 1;
			curmod->cursym->array_len = -2;
		}
	|	LBRACKET RBRACKET
		{
			curmod->cursym->is_array = 1;
			curmod->cursym->array_len = -1;
		}
	|	LBRACKET INTEGER_NUMERIC RBRACKET
		{
			curmod->cursym->is_array = 1;
			curmod->cursym->array_len = atoi($2);
		}
	|	/* nothing */
	;

fnpointer_init:
		{
			curmod->cursym->is_fp = 1;
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_LBRACKET;
			curmod->cursym->ndeclarator++;
		}
	;

fp_args_init:
		{
			idl_symdef_t *fp;
			
			fp = curmod->cursym;
			if(0 == curmod->cursym->is_fp && SYM_METHOD != curmod->cursym->type)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "Cannot declare arguments for non-function-pointer symbol '%s'", curmod->cursym->ident);
			}
			fp->fp_params.symtype = SYM_PARAM;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_intf_symlist_push(curmod->curintf, &(fp->fp_params));
			idl_module_scope_pop(curmod);
		}
	;

fp_args_init_first:
		{
			idl_symdef_t *fp;
			
			fp = curmod->cursym;
			if(0 == curmod->cursym->is_fp)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "Cannot declare arguments for non-function-pointer symbol '%s'", curmod->cursym->ident);
			}
			curmod->curintf->firstsym = curmod->cursym;
			fp->fp_params.symtype = SYM_PARAM;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_intf_symlist_push(curmod->curintf, &(fp->fp_params));
			idl_module_scope_pop(curmod);
		}
	;
	
fp_args_init_link:
		{
			idl_symdef_t *fp;
			
			fp = curmod->cursym;
			if(0 == curmod->cursym->is_fp)
			{
				idl_module_error(curmod, yyget_lineno(scanner), "Cannot declare arguments for non-function-pointer symbol '%s'", curmod->cursym->ident);
			}
			fp->fp_params.symtype = SYM_PARAM;
			idl_intf_symdef_link(curmod->curintf, curmod->cursym);
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_intf_symlist_push(curmod->curintf, &(fp->fp_params));
			idl_module_scope_pop(curmod);
		}
	;

pointer_decl:
		pointer_decl_token
	|	pointer_decl_token pointer_decl
	;

pointer_decl_token:
		STAR
		{
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_POINTER;
			curmod->cursym->ndeclarator++;
			$$ = $1;
		}
	|	CONST_KW
		{
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_CONST;
			curmod->cursym->ndeclarator++;
			$$ = $1;
		}
	|	RESTRICT_KW
		{
			curmod->cursym->declarator[curmod->cursym->ndeclarator] = DECL_RESTRICT;
			curmod->cursym->ndeclarator++;
			$$ = $1;
		}
	;

type_decl: typedecl_init type_attributes type_modifiers type
	;

typedecl_init:
		{
			idl_module_typedecl_push(curmod);
		}

symdef_init:
		{
			idl_scope_t *scope;

			idl_intf_symdef_create(curmod->curintf, curmod->curtype);
			scope = idl_module_scope_push(curmod);
			scope->type = ST_SYMDEF;
		}
	;

type_attributes:
		attribute_opener type_attr_list extraneous_comma attribute_closer
	|	/* Nothing */
	;
	
type_attr_list:
        type_attr
    |   type_attr_list COMMA type_attr
    |   /* nothing */
    ;

type_attr:
		STRING_KW
	|	WIRE_MARSHAL_KW LPAREN identifier RPAREN
	|	SIZE_IS_KW LPAREN expression RPAREN
	|	RANGE_KW LPAREN expression COMMA expression RPAREN
	|	PTR_KW
	|	UNIQUE_KW
	|	REF_KW
	|	IID_IS_KW LPAREN identifier RPAREN
	|	IN_KW
	|	OUT_KW
	|	INOUT_KW
	|	V1_STRUCT_KW
	;

type_modifiers:
		type_modifier
	|	type_modifiers type_modifier
	|	/* Nothing */
	;

type_modifier:
		CONST_KW
		{
			curmod->curtype->modifiers |= TYPEMOD_CONST;
		}
	|	UNSIGNED_KW
		{
			curmod->curtype->modifiers |= TYPEMOD_UNSIGNED;
		}
	|	SIGNED_KW
		{
			curmod->curtype->modifiers |= TYPEMOD_SIGNED;
		}
	;

type:
		CHAR_KW
		{
			curmod->curtype->builtin_type = TYPE_CHAR;
		}
	|	INT_KW
		{
			curmod->curtype->builtin_type = TYPE_INT;
		}
	|	VOID_KW
		{
			curmod->curtype->builtin_type = TYPE_VOID;
		}
	|	LONG_KW INT_KW
		{
			curmod->curtype->builtin_type = TYPE_INT32;
		}
	|	LONG_KW LONG_KW INT_KW
		{
			curmod->curtype->builtin_type = TYPE_LONGLONG;
		}
	|	SHORT_KW INT_KW
		{
			curmod->curtype->builtin_type = TYPE_SHORT;
		}
	|	SHORT_KW
		{
			curmod->curtype->builtin_type = TYPE_INT16;
		}
	|	LONG_KW LONG_KW
		{
			curmod->curtype->builtin_type = TYPE_LONGLONG;
		}
	|	LONG_KW
		{
			curmod->curtype->builtin_type = TYPE_INT32;
		}
	|	FLOAT_KW
		{
			curmod->curtype->builtin_type = TYPE_FLOAT;
		}
	|	DOUBLE_KW
		{
			curmod->curtype->builtin_type = TYPE_DOUBLE;
		}
	|	SMALL_KW
		{
			curmod->curtype->builtin_type = TYPE_INT16;
		}
	|	BOOLEAN_KW
		{
			curmod->curtype->builtin_type = TYPE_BOOLEAN;
		}
	|	byte
		{
			curmod->curtype->builtin_type = TYPE_INT8;
			if(0 != (curmod->curtype->modifiers & (TYPEMOD_SIGNED|TYPEMOD_UNSIGNED)))
			{
				idl_module_warning(curmod, yyget_lineno(scanner), "'%s' types are always unsigned\n", $1);
			}
			curmod->curtype->modifiers &= ~TYPEMOD_SIGNED;
			curmod->curtype->modifiers |= TYPEMOD_UNSIGNED;
		}
	|	HYPER_KW
		{
			curmod->curtype->builtin_type = TYPE_INT64;
		}
	|	struct LBRACE struct_body RBRACE
		{
			curmod->curtype->has_symlist = 1;
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	struct
		{
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	enum LBRACE enum_body RBRACE
		{
			curmod->curtype->has_symlist = 1;
			idl_intf_symlist_pop(curmod->curintf, curmod->cursymlist);
		}
	|	identifier
		{
			curmod->curtype->builtin_type = TYPE_DEF;
			if(NULL == (curmod->curtype->user_type = idl_intf_symdef_lookup(curmod->curintf, $1)))
			{
				idl_module_error(curmod, yyget_lineno(scanner), "undeclared typedef '%s'", $1);
			}
		}
	|	error
		{
			idl_module_error(curmod, yyget_lineno(scanner), "expected: identifier; found '%s'", $1);
		}
	;

byte:
		OCTET_KW
		{
			$$ = $1;
		}
	|	BYTE_KW
		{
			$$ = $1;
		}
	;

struct_init:
		STRUCT_KW symdef_init identifier
		{
			idl_module_typedecl_push(curmod);
			strncpy(curmod->curtype->tag, $3, IDL_IDENT_MAX);
			curmod->curtype->tag[IDL_IDENT_MAX] = 0;
			curmod->curtype->builtin_type = TYPE_STRUCT;
			curmod->curtype->symlist.symtype = SYM_MEMBER;
			idl_intf_symlist_push(curmod->curintf, &(curmod->curtype->symlist));
		}
	;
	
struct:
		STRUCT_KW
		{
			curmod->curtype->builtin_type = TYPE_STRUCT;
			curmod->curtype->symlist.symtype = SYM_MEMBER;
			idl_intf_symlist_push(curmod->curintf, &(curmod->curtype->symlist));
		}
	|	STRUCT_KW identifier
		{
			strncpy(curmod->curtype->tag, $2, IDL_IDENT_MAX);
			curmod->curtype->tag[IDL_IDENT_MAX] = 0;
			curmod->curtype->builtin_type = TYPE_STRUCT;
			curmod->curtype->symlist.symtype = SYM_MEMBER;
			idl_intf_symlist_push(curmod->curintf, &(curmod->curtype->symlist));
		}
	;

enum:
		ENUM_KW
		{
			curmod->curtype->builtin_type = TYPE_ENUM;
			curmod->curtype->symlist.symtype = SYM_ENUM;
			idl_intf_symlist_push(curmod->curintf, &(curmod->curtype->symlist));
		}
	|	ENUM_KW identifier
		{
			strncpy(curmod->curtype->tag, $2, IDL_IDENT_MAX);
			curmod->curtype->tag[IDL_IDENT_MAX] = 0;
			curmod->curtype->builtin_type = TYPE_ENUM;
			curmod->curtype->symlist.symtype = SYM_ENUM;
			idl_intf_symlist_push(curmod->curintf, &(curmod->curtype->symlist));
		}
	;
	
possible_arg_list:
		arg_list
	|	VOID_KW
	|	/* nothing */
	;

arg_list:
		arg_list COMMA arg_decl
	|	arg_decl
	;
	

arg_decl:
		type_decl pointer_ident_decl
		{
			idl_module_typedecl_pop(curmod);
			curmod->curintf->firstsym = NULL;
		}
	;
	
struct_body:
		struct_body struct_union_member extraneous_semi
	|	struct_union_member extraneous_semi
	;

struct_union_member:
		type_decl pointer_ident_decl_list SEMI
		{
			idl_module_typedecl_pop(curmod);
			curmod->curintf->firstsym = NULL;
		}
	;

enum_body:
		enum_body COMMA enum_member
	|	enum_member
	;
	
enum_member:
		symdef_init simple_declarator EQUAL expression
		{
			curmod->cursym->decl = NULL;
			curmod->cursym->constval = (idl_expr_t *) $4;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	|	symdef_init simple_declarator
		{
			curmod->cursym->decl = NULL;
			curmod->cursym->noval = 1;
			idl_intf_symdef_done(curmod->curintf, curmod->cursym);
			idl_module_scope_pop(curmod);
		}
	;
	
cpp_quote:
		CPP_QUOTE_KW LPAREN STRING RPAREN extraneous_semi
		{
			idl_scope_t *scope;

			scope = idl_module_scope_push(curmod);
			scope->type = ST_QUOTE;
			scope->text = strdup($3);
			idl_module_scope_pop(curmod);
		}
	;

uuid:
		UUID
		{
			const char *s;
			
			s = yyval;
			if('(' == *s)
			{
				s++;
			}
			while(*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')
			{
				s++;
			}
			memmove(yylval, s, 36);
			yylval[36] = 0;
		}
	;

/* XXX FIXME:
 *     The rules of precedence aren't adhered to in any sane way here. This
 *     isn't a problem for header generation, but will be for stubs.
 */
expression:
		expr_value
		{
			$$ = $1;
		}
	|	prefix_expression
		{
			$$ = $1;
		}
	|	postfix_expression
		{
			$$ = $1;
		}
	|	expression QUESTION expression COLON expression
	|	LPAREN expression RPAREN
		{
			$$ = (char *) idl_expr_create_bracket((const idl_expr_t *) $2);
		}
	;

expr_value:
		identifier
		{
			$$ = (char *) idl_expr_create_sym(curmod->curintf, $1);
		}
	|	INTEGER_NUMERIC
		{
			char *dummy;
		
			$$ = (char *) idl_expr_create_intconst(strtol($1, &dummy, 0));
		}
	|	FLOAT_NUMERIC
	;

prefix_expression:
		NOT expression
		{
			$$ = (char *) idl_expr_create_prefix(EXPR_NOT, (const idl_expr_t *) $1);
		}
	|	TILDE expression
		{
			$$ = (char *) idl_expr_create_prefix(EXPR_BITNOT, (const idl_expr_t *) $1);
		}
	;

postfix_expression:
		expression PLUS expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_ADD, (const idl_expr_t *) $3);
		}
	|	expression MINUS expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_SUB, (const idl_expr_t *) $3);
		}
	|	expression SLASH expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_DIV, (const idl_expr_t *) $3);
		}
	|	expression STAR expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_MUL, (const idl_expr_t *) $3);
		}
	|	expression PERCENT expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_MOD, (const idl_expr_t *) $3);
		}
	|	expression CARET expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_XOR, (const idl_expr_t *) $3);
		}
	|	expression LANGLEANGLE expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_LSHIFT, (const idl_expr_t *) $3);
		}
	|	expression RANGLEANGLE expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_RSHIFT, (const idl_expr_t *) $3);
		}
	|	expression AMP expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_BITAND, (const idl_expr_t *) $3);
		}
	|	expression AMPAMP expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_AND, (const idl_expr_t *) $3);
		}
	|	expression BAR expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_BITOR, (const idl_expr_t *) $3);
		}
	|	expression BARBAR expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_OR, (const idl_expr_t *) $3);
		}
	|	expression NOTEQUAL expression
		{
			$$ = (char *) idl_expr_create_pair((const idl_expr_t *) $1, EXPR_NOTEQUALS, (const idl_expr_t *) $3);
		}
	;
