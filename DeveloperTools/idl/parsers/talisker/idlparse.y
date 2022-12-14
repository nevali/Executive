%{
/* Copyright (c) 2008-2018 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *	  http://www.apache.org/licenses/LICENSE-2.0
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
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Novell, Inc. nor the names of its contributors
 *	may be used to endorse or promote products derived from this software
 *	without specific prior written permission.
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
 *				 permission to use, copy, modify, and distribute this
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

#include "p_parser.h"


static char vertmp[64];

void
yyerror(YYLTYPE *loc, void *scanner, char *s)
{
	(void) scanner;
	
	idl_module_error(curmod, loc, "%s", s);
}

%}

/* Options */

%start root
%pure-parser
%lex-param { void *scanner }
%parse-param { void *scanner }
%error-verbose
%locations

/* Keywords */

%token ALIGN_KW
%token ARRAY_KW
%token ASTRING_KW

%token BINARYNAME_KW
%token BOOLEAN_KW
%token BOOL_KW
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

/*  Non-keyword tokens	  */

%token UUID

/*  Punctuation			 */

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

/* The starting node for the parser */
	
root:
		/* Empty */
		{
				idl_module_warning(curmod, &yylloc, "IDL source contains no statements");
		}
	|	root_statements
		;
	
root_statements:
		root_statement
	|	root_statements root_statement
	;

root_statement:
		import
	|	quote
	|	declaration
	|	definition
	;

/* Declarations */

declaration:
		const_decl SEMI
		interface_decl SEMI
		coclass_decl SEMI
	;

/* Definitions */

definition:
		interface
	|	coclass
	;

/* COMMON: General identifiers */

identifier:
		IDENTIFIER { $$ = $1; }
	|	UUID_KW { $$ = $1; }
	|	MODE_KW { $$ = $1; }
	|	STRING_KW { $$ = $1; }
	|	LOCAL_KW { $$ = $1; }
	|	OBJECT_KW { $$ = $1; }
	|	IN_KW { $$ = $1; }
	|	OUT_KW { $$ = $1; }
	|	INOUT_KW { $$ = $1; }
	|	ID_KW { $$ = $1; }
	|	PTR_KW { $$ = $1; }
	|	CHEADER_KW { $$ = $1; }
	;

/* As 'identifier', above, but set the current node's identifier to whatever
 * was specified
 */
set_identifier:
		identifier
		{
			json_object_set_new(curmod->ir, "identifier", json_string($1));
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

extraneous_comma:
		COMMA
	|	/* nothing */
	;

extraneous_semi:
		SEMI
	|	extraneous_semi SEMI
	|	/* nothing */
	;


pointer_class:
		REF_KW { $$ = $1; }
	|	PTR_KW { $$ = $1; }
	|	UNIQUE_KW { $$ = $1; }
	;

version_number:
		INTEGER_NUMERIC
		{
			$$ = $1;
		}
	|	FLOAT_NUMERIC
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
	|	port_list COMMA port_spec
	;

excep_list:
		excep_spec
		{
		}
	|	excep_list COMMA excep_spec
		{
		}
	;

port_spec:
		STRING
		{
			json_t *list;
			
			if(!(list = json_object_get(curmod->ir, "ports")))
			{
				list = json_array();
				json_object_set_new(curmod->ir, "ports", list);
			}
			json_array_append_new(list, json_string($1));
		}
	;

excep_spec:
		identifier
		{
			json_t *list;
			
			if(!(list = json_object_get(curmod->ir, "exceptions")))
			{
				list = json_array();
				json_object_set_new(curmod->ir, "exceptions", list);
			}
			json_array_append_new(list, json_string($1));
		}
	;

/* quotation syntax:
 *
 * cpp_quote( "text" ) ;
 */

quote:
	cpp_quote

cpp_quote:
	CPP_QUOTE_KW LPAREN STRING RPAREN extraneous_semi
	{
		json_t *self;

		self = idl_json_push(curmod, "quote", &yylloc);
		json_object_del(self, "attrs");
		json_object_del(self, "@");
		json_object_set_new(self, "lang", json_string("cpp"));
		json_object_set_new(self, "text", json_string($3));
		idl_json_pop(curmod);
	}
;


/* import keyword:
 *
 * import "filename" [, "filename" [, ... ]] ;
 */

import:
	IMPORT_KW import_files SEMI
	{
		$$ = $2;
	}
;

import_files:
		import_file
	|	import_files COMMA import_file
		{
		}
	;

import_file:
		STRING
		{
			json_t *self;
		
			self = idl_json_push(curmod, "import", &yylloc);
			json_object_del(self, "@");
			json_object_del(self, "attrs");
			json_object_set_new(self, "filename", json_string($1));
			idl_json_pop(curmod);
		
			if(-1 == idl_parse($1, 0, 1))
			{
				idl_module_terminate();
			}
		}
	;

/* const keyword:
 *
 * const TYPE IDENT = EXPR ;
 */

const_decl:
		const_begin type_decl set_identifier EQUAL const_value
		{
			idl_json_pop(curmod);
		}
	;

const_begin:
		CONST_KW
		{
			idl_json_push(curmod, "const", &yylloc);
		}
	;

const_value:
		expression
		{
			json_t *args;
		
			/* Move the contents of the '@' array to 'value' */
			args = json_object_get(curmod->ir, "@");
			if(args && json_is_array(args) && json_array_size(args))
			{
				json_object_set(curmod->ir, "value", json_array_get(args, 0));
			}
			json_object_del(curmod->ir, "@");
		}

/* interface keyword
 *
 * interface IDENT [ : ANCESTORS... ] [ = ID ] ;
 * ATTRIBUTES interface IDENT [ : ANCESTORS... ] { STATEMENTS } [ = ID ]
 */

interface_decl:
		interface_begin possible_id
		{
			json_object_set_new(curmod->ir, "stub", json_true());
			idl_json_pop(curmod);
		}
	;

interface:
		attributes interface_begin container_ident_ancestor LBRACE container_statements RBRACE possible_id extraneous_semi
		{
			idl_json_pop(curmod);
		}
	;

interface_begin:
		INTERFACE_KW
		{
			idl_json_push(curmod, "interface", &yylloc);
		}
	;

/* coclass keyword - identical syntax to interface */

coclass_decl:
		coclass_begin possible_id
		{
			json_object_set_new(curmod->ir, "stub", json_true());
			idl_json_pop(curmod);
		}
	;

coclass:
		attributes coclass_begin container_ident_ancestor LBRACE container_statements RBRACE possible_id extraneous_semi
		{
			idl_json_pop(curmod);
		}
	;

coclass_begin:
		COCLASS_KW
		{
			idl_json_push(curmod, "coclass", &yylloc);
		}
	;

container_ident_ancestor:
		set_identifier COLON container_ancestors
	|	set_identifier

container_ancestors:
		container_ancestors COMMA container_ancestor
	|	container_ancestor
	;

container_ancestor:
		identifier
		{
			json_t *list;
			
			if(!(list = json_object_get(curmod->ir, "ancestors")))
			{
				list = json_array();
				json_object_set_new(curmod->ir, "ancestors", list);
			}
			json_array_append_new(list, json_string($1));
		}

container_statements:
		/* Nothing */
	|	container_statement
	|	container_statements extraneous_semi container_statement
	;

container_statement:
		cpp_quote
	|	import
	|	typedef_decl
	|	method_decl SEMI
	|	const_decl SEMI
	|	struct_decl
	;

/* COMMON: postfix numeric ID specification */

postfix_id:
		EQUAL INTEGER_NUMERIC
		{
			char *dummy = NULL;
	
			idl_json_attr(curmod, "id", json_integer(strtoul($2, &dummy, 0)));
		}
	;

possible_id:
		/* Nothing */
	|	postfix_id
	;

/* COMMON: typedefs */
	
typedef_decl:
		TYPEDEF_KW typedef_push type_decl pointer_ident_decl_list SEMI
		{
			idl_json_pop(curmod);
		}
	;

typedef_push:
		{
			idl_json_push(curmod, "typedef", &yylloc);
		}
	;

/* COMMON: method declarations */
	
method_decl:
		method_push attributes type_decl set_identifier LPAREN possible_arg_list RPAREN possible_id
		{
			idl_json_pop(curmod);
		}
	;

method_push:
		{
			idl_json_push(curmod, "method", &yylloc);
		}
	;

/* COMMON: struct declarations */

struct_decl:
		struct_push identifier LBRACE struct_body RBRACE SEMI
		{
			idl_json_pop(curmod);
		}
	|	union_push identifier LBRACE struct_body RBRACE SEMI
		{
			idl_json_pop(curmod);
		}
	;	

struct_push:
		STRUCT_KW
		{
			idl_json_push(curmod, "struct", &yylloc);
		}
	;

union_push:
		UNION_KW
		{
			idl_json_push(curmod, "union", &yylloc);
		}
	;

struct_body:
		struct_body struct_union_member extraneous_semi
	|	struct_union_member extraneous_semi
	;

struct_union_member:
		type_decl pointer_ident_decl_list SEMI
		{
		}
	;

/* COMMON: enum declarations */

enum_body:
		enum_body COMMA enum_member
	|	enum_member
	;

enum_member:
		enum_member_push set_identifier EQUAL const_value
		{
			idl_json_pop(curmod);
		}
	|	enum_member_push set_identifier
		{
			idl_json_pop(curmod);
		}
	;

enum_member_push:
		{
			idl_json_push(curmod, "const", &yylloc);
		}

/* COMMON: Type declarations (e.g., return value and parameter specifications ) */

/* All of these productions operate on curmod->irtype, not curmod->ir */

type_decl:
		type_push type_attributes type_modifiers type
		{
			idl_json_pop_type(curmod);
		}
	;

type_push:
		{
			idl_json_push_type(curmod);
		}
	;

type_modifiers:
		type_modifier
	|	type_modifiers type_modifier
	|	/* Nothing */
	;

type_modifier:
		CONST_KW
		{
			json_object_set_new(curmod->irtype, "const", json_true());
		}
	|	UNSIGNED_KW
		{
			json_object_set_new(curmod->irtype, "unsigned", json_true());
		}
	|	SIGNED_KW
		{
			json_object_set_new(curmod->irtype, "signed", json_true());
		}
	;

type:
		VOID_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("void"));
		}
	|	CHAR_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int8"));
		}
	|	INT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int32"));
		}
	|	LONG_KW INT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int32"));
		}
	|	LONG_KW LONG_KW INT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int64"));
		}
	|	SHORT_KW INT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int16"));
		}
	|	SHORT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int16"));
		}
	|	LONG_KW LONG_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int64"));
		}
	|	LONG_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int32"));
		}
	|	FLOAT_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("float"));
		}
	|	DOUBLE_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("double"));
		}
	|	SMALL_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int16"));
		}
	|	BOOLEAN_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("boolean"));
		}
	|	BOOL_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("boolean"));
		}
	|	HYPER_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int64"));
		}
	|	BYTE_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int8"));
			json_object_set_new(curmod->irtype, "unsigned", json_true());
		}
	|	OCTET_KW
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("int8"));
			json_object_set_new(curmod->irtype, "unsigned", json_true());
		}
	|	STRUCT_KW LBRACE struct_body RBRACE
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("struct"));
		}
	|	STRUCT_KW identifier LBRACE struct_body RBRACE
		{
			/* In-line declaration */
			json_object_set_new(curmod->irtype, "intrinsic", json_string("struct"));
			json_object_set_new(curmod->irtype, "struct", json_string($2));
		}
	|	STRUCT_KW identifier
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("struct"));
			json_object_set_new(curmod->irtype, "struct", json_string($2));
		}
	|	ENUM_KW LBRACE enum_body RBRACE
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("enum"));
		}
	|	ENUM_KW identifier LBRACE enum_body RBRACE
		{
			/* In-line declaration */
			json_object_set_new(curmod->irtype, "intrinsic", json_string("enum"));
			json_object_set_new(curmod->irtype, "enum", json_string($2));
		}
	|	ENUM_KW identifier
		{
			json_object_set_new(curmod->irtype, "intrinsic", json_string("enum"));
			json_object_set_new(curmod->irtype, "enum", json_string($2));
		}
	|	identifier
		{
			json_object_set_new(curmod->irtype, "typedef", json_string($1));
		}
	;

/* COMMON: parameter declarations */

possible_arg_list:
		arg_list
		{
			json_t *args;
			
			/* Move the contents of the '@' array to 'args' */
			args = json_object_get(curmod->ir, "@");
			if(args)
			{
				json_object_set(curmod->ir, "args", args);
			}
			json_object_del(curmod->ir, "@");
		}
	|	VOID_KW
	|	/* nothing */
	;

arg_list:
		arg_list COMMA arg_decl
	|	arg_decl
	;

arg_decl:
		arg_push type_decl pointer_ident_decl
		{
			const char *key;
			json_t *args, *decl, *value;

			if((decl = json_object_get(curmod->ir, "type")))
			{
				if((args = json_object_get(decl, "attrs")))
				{
					json_object_set(curmod->ir, "attrs", args);
					json_object_del(decl, "attrs");
				}
			}
			if((args = json_object_get(curmod->ir, "@")))
			{
				if((decl = json_array_get(args, 0)))
				{
					json_object_foreach(decl, key, value)
					{
						if(key[0] != '@')
						{
							json_object_set(curmod->ir, key, value);
						}
					}
				}
				json_object_del(curmod->ir, "@");
			}
			json_object_del(curmod->ir, "@class");
			json_object_del(curmod->ir, "@index");
			idl_json_pop(curmod);
		}
	;
	
arg_push:
		{
			idl_json_push(curmod, "arg", &yylloc);
		}
	;
	
/* COMMON: declarators */

/* When 'declarator' is reached, curmod->irtype is already populated for us */

declarator:
		pointer_decl direct_declarator
	|	direct_declarator
	;

decl_push:
		{
			idl_json_push(curmod, "decl", &yylloc);
		}
	;

/* Either a function pointer or a simple declarator */

direct_declarator:
		LPAREN declarator RPAREN
		{
			json_object_set_new(curmod->ir, "funcptr", json_true());
		}
	|	set_identifier
	;

/* One or more declarations in a comma-separated list */
pointer_ident_decl_list:
		pointer_ident_decl_list COMMA pointer_ident_decl
	|	pointer_ident_decl
	;

/* A single declaration which may be a pointer (i.e., a function parameter) */
pointer_ident_decl:
		decl_push declarator LPAREN possible_arg_list RPAREN possible_array
		{
			idl_json_pop(curmod);
		}
	|	decl_push declarator possible_array
		{
			idl_json_pop(curmod);
		}
	;

possible_array:
		LBRACKET STAR RBRACKET
		{
			json_object_set_new(curmod->ir, "array", json_true());
			json_object_set_new(curmod->ir, "size", json_integer(-2));
		}
	|	LBRACKET RBRACKET
		{
			json_object_set_new(curmod->ir, "array", json_true());
			json_object_set_new(curmod->ir, "size", json_integer(-1));
		}
	|	LBRACKET INTEGER_NUMERIC RBRACKET
		{
			json_object_set_new(curmod->ir, "array", json_true());
			json_object_set_new(curmod->ir, "size", json_integer(atoi($2)));
		}
	|	/* not an array */
	;

pointer_decl:
		pointer_decl_token
	|	pointer_decl_token pointer_decl
	;

pointer_decl_token:
		STAR
		{
			idl_json_pointer(curmod, "*");
		}
	|	CONST_KW
		{
			idl_json_pointer(curmod, "const");
		}
	|	RESTRICT_KW
		{
			idl_json_pointer(curmod, "restrict");
		}
	;

/* COMMON: expressions */

expression:
		expr_value
		{
		}
	|	expr_push prefix_expression
		{
			idl_json_pop(curmod);
		}
	|	expr_push postfix_expression
		{
			idl_json_pop(curmod);
		}
	|	expr_push cond_expression
		{
			idl_json_pop(curmod);
		}
	|	expr_push LPAREN expression RPAREN
		{
			idl_json_pop(curmod);
		}
	;

expr_push:
		{
			idl_json_push(curmod, "expr", &yylloc);
		}
	;

expr_pop:
		{
			idl_json_pop(curmod);
		}
	;

/* Expression leaves - identifiers and constant values */

expr_value:
		identifier
		{
			json_t *self;
			
			self = idl_json_push(curmod, "ref", &yylloc);
			json_object_set_new(self, "identifier", json_string($1));
			idl_json_pop(curmod);
		}
	|	INTEGER_NUMERIC
		{
			json_t *self;
			char *dummy = NULL;
			
			self = idl_json_push(curmod, "value", &yylloc);
			json_object_set_new(self, "intrinsic", json_string("int32"));
			json_object_set_new(self, "int", json_integer(strtol($1, &dummy, 0)));
			idl_json_pop(curmod);
		}
	|	FLOAT_NUMERIC
		{
			json_t *self;
			char *dummy = NULL;
			
			self = idl_json_push(curmod, "value", &yylloc);
			json_object_set_new(self, "intrinsic", json_string("float"));
			json_object_set_new(self, "float", json_real(strtold($1, &dummy)));
			idl_json_pop(curmod);
		}
	;

prefix_expression:
		NOT expr_push expression expr_pop
		{
			json_object_set_new(curmod->ir, "op", json_string("not"));
		}
	|	TILDE expr_push expression expr_pop
		{
			json_object_set_new(curmod->ir, "op", json_string("inverse"));
		}
	;

postfix_expression:
		expr_push expression expr_pop PLUS expr_push expression expr_pop
		{
			json_object_set_new(curmod->ir, "op", json_string("add"));
		}
	|	expression MINUS expression
		{
			json_object_set_new(curmod->ir, "op", json_string("sub"));
		}
	|	expression SLASH expression
		{
			json_object_set_new(curmod->ir, "op", json_string("div"));
		}
	|	expression STAR expression
		{
			json_object_set_new(curmod->ir, "op", json_string("mul"));
		}
	|	expression PERCENT expression
		{
			json_object_set_new(curmod->ir, "op", json_string("mod"));
		}
	|	expression CARET expression
		{
			json_object_set_new(curmod->ir, "op", json_string("compl"));
		}
	|	expression LANGLEANGLE expression
		{
			json_object_set_new(curmod->ir, "op", json_string("lshr"));
		}
	|	expression RANGLEANGLE expression
		{
			json_object_set_new(curmod->ir, "op", json_string("rshr"));
		}
	|	expression AMP expression
		{
			json_object_set_new(curmod->ir, "op", json_string("bitand"));
		}
	|	expression AMPAMP expression
		{
			json_object_set_new(curmod->ir, "op", json_string("and"));
		}
	|	expression BAR expression
		{
			json_object_set_new(curmod->ir, "op", json_string("bitor"));
		}
	|	expression BARBAR expression
		{
			json_object_set_new(curmod->ir, "op", json_string("or"));
		}
	|	expression NOTEQUAL expression
		{
			json_object_set_new(curmod->ir, "op", json_string("neq"));
		}
	;

cond_expression:
		expr_push expression expr_pop QUESTION expr_push expression expr_pop COLON expr_push expression expr_pop
		{
			json_object_set_new(curmod->ir, "op", json_string("cond"));
		}

/* COMMON: Common attributes */

attributes:
		LBRACKET attribute_list RBRACKET
	|	/* Nothing */
	;

attribute_list:
	|	attribute_list COMMA attribute
	|	attribute
	;

attribute:
		UUID_KW uuid
		{
			idl_json_attr(curmod, "uuid", json_string($2));
		}
	|	ENDPOINT_KW LPAREN port_list extraneous_comma RPAREN
		{
		}
	|	EXCEPTIONS_KW LPAREN excep_list extraneous_comma RPAREN
		{
		}
	|	VERSION_KW LPAREN version_number RPAREN
		{
			char *dummy = NULL;
			
			idl_json_attr(curmod, "version", json_integer(strtoul($3, &dummy, 0)));
		}
	|	ID_KW LPAREN INTEGER_NUMERIC RPAREN
		{
			char *dummy = NULL;
			
			idl_json_attr(curmod, "id", json_integer(strtoul($3, &dummy, 0)));
		}
	|	LOCAL_KW
		{
			idl_json_attr(curmod, "local", json_true());
		}
	|	OBJECT_KW
		{
			idl_json_attr(curmod, "object", json_true());
		}
	|	POINTER_DEFAULT_KW LPAREN pointer_class RPAREN
		{
			idl_json_attr(curmod, "pointer_class", json_string($3));
		}
	|	CHEADER_KW LPAREN STRING RPAREN
		{
			idl_json_attr(curmod, "cheader", json_string($3));
		}
	|	CALL_AS_KW LPAREN identifier RPAREN
		{
			/* Don't emit a vtable entry for this method; clients will
			 * use (identifier) instead.
			 */
			idl_json_attr(curmod, "call_as", json_string($3));
		}
	;

/* COMMON: Type/parameter attributes */

type_attributes:
		LBRACKET type_attr_list extraneous_comma RBRACKET
	|	/* Nothing */
	;

type_attr_list:
		type_attr
	|	type_attr_list COMMA type_attr
	|	/* nothing */
	;

type_attr:
		STRING_KW
		{
			idl_json_type_attr(curmod, "string", json_true());
		}
	|	WIRE_MARSHAL_KW LPAREN identifier RPAREN
		{
			idl_json_type_attr(curmod, "wire_marshal", json_string($3));
		}
	|	SIZE_IS_KW LPAREN expression RPAREN
		{
			idl_json_type_attr(curmod, "size_is", json_string($3));
		}
	|	RANGE_KW LPAREN expression COMMA expression RPAREN
		{
			/* XXX */
			idl_json_type_attr(curmod, "range", json_array());
		}
	|	PTR_KW
		{
			idl_json_type_attr(curmod, "ptr", json_true());
		}
	|	UNIQUE_KW
		{
			idl_json_type_attr(curmod, "unique", json_true());
		}
	|	REF_KW
		{
			idl_json_type_attr(curmod, "ref", json_true());
		}		
	|	IID_IS_KW LPAREN identifier RPAREN
		{
			idl_json_type_attr(curmod, "iid", json_string($3));
		}
	|	IN_KW
		{
			idl_json_type_attr(curmod, "in", json_true());
		}
	|	OUT_KW
		{
			idl_json_type_attr(curmod, "out", json_true());
		}
	|	INOUT_KW
		{
			idl_json_type_attr(curmod, "in", json_true());
			idl_json_type_attr(curmod, "out", json_true());
		}
	|	V1_STRUCT_KW
		{
			idl_json_type_attr(curmod, "v1_struct", json_true());
		}
	;
