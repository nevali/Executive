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

#include "p_parser.h"

static char shortbuf[256], stringbuf[512];
static char *strp;
static YYLTYPE *newloc, locbuf;
static void read_c_comment(struct yyguts_t * yyg, void *scanner);
static void update_location(struct yyguts_t *yyg, YYLTYPE *loc);

#define YY_USER_INIT memset(yylloc, 0, sizeof(YYLTYPE));
#define YY_USER_ACTION update_location(yyg, yylloc);

%}

%option noyywrap
%option yylineno
%option reentrant
%option bison-bridge
%option bison-locations

%x str

delim           [ \t\n\f]
opt_ws          {delim}*
ws              {delim}
letter          [A-Za-z_$]
digit           [0-9]
hex_digit       [0-9A-Fa-f]
id              {letter}({letter}|{digit})*
l_suffix        (l|L)
u_suffix        (u|U)
f_suffix        (u|U)
integer         -?{digit}+(({u_suffix}{l_suffix})|({l_suffix}{u_suffix})|{l_suffix}|{u_suffix})?
c_hex_integer   (0(x|X){hex_digit}*)(({l_suffix}{u_suffix}?)|({u_suffix}{l_suffix}?))?
float           {digit}+\.{digit}+({f_suffix}|{l_suffix})?
octet           {hex_digit}{hex_digit}
octet2          {octet}{octet}
octet_dot       {octet}\.
octet2_dash     {octet2}\-
olduuid         \({opt_ws}{octet2}{octet2}{octet}{octet_dot}{octet_dot}{octet_dot}{octet_dot}{octet_dot}{octet_dot}{octet_dot}{octet_dot}{octet}{opt_ws}\)
uuid            \({opt_ws}{octet2}{octet2_dash}{octet2_dash}{octet2_dash}{octet2_dash}{octet2}{octet2}{octet2}{opt_ws}\)
other           .
preproc         ^#.*$

%%
{ws}            { /* No action, and no return */ }
'\n'            { yycolumn = 1; }
":"             {return(COLON);}
","             {return(COMMA);}
".."            {return(DOTDOT);}
"="             {return(EQUAL);}
\[              {return(LBRACKET);}
"("             {return(LPAREN);}
\]              {return(RBRACKET);}
")"             {return(RPAREN);}
";"             {return(SEMI);}
"*"             {return(STAR);}
"{"             {return(LBRACE);}
"??<"           {return(LBRACE);}
"}"             {return(RBRACE);}
"??>"           {return(RBRACE);}
"?"             {return(QUESTION);}
"|"             {return(BAR);}
"||"            {return(BARBAR);}
"<"             {return(LANGLE);}
"<<"            {return(LANGLEANGLE);}
">"             {return(RANGLE);}
">>"            {return(RANGLEANGLE);}
"&"             {return(AMP);}
"&&"            {return(AMPAMP);}
"<="            {return(LESSEQUAL);}
">="            {return(GREATEREQUAL);}
"=="            {return(EQUALEQUAL);}
"^"             {return(CARET);}
"+"             {return(PLUS);}
"-"             {return(MINUS);}
"!"             {return(NOT);}
"!="            {return(NOTEQUAL);}
"/"             {return(SLASH);}
"%"             {return(PERCENT);}
"~"             {return(TILDE);}

\" {
	strp = stringbuf;
	BEGIN(str);
}

<str>\" {
	BEGIN(INITIAL);
	*strp = 0;
	*yylval = stringbuf;
	return STRING;
}

<str>\\[0-7]{1,3} {
	/* octal escape sequence */
	int result;

	sscanf( yytext + 1, "%o", &result );

	if( result > 0xff)
	{
		idl_module_error(curmod, yylloc, "octal character sequence out of range (%s)", yytext);
	}
	*strp = result;
	strp++;
}

<str>\\[0-9]+ {
	idl_module_error(curmod, yylloc, "invalid escape sequence (%s)", yytext);
}

<str>\\n  *strp++ = '\n';
<str>\\t  *strp++ = '\t';
<str>\\r  *strp++ = '\r';
<str>\\b  *strp++ = '\b';
<str>\\f  *strp++ = '\f';

<str>\\(.|\n)  *strp++ = yytext[1];

<str>[^\\\n\"]+ {
	char *yptr = yytext;

	while ( *yptr )
		*strp++ = *yptr++;
}

"/*" {
	read_c_comment(yyg, yyscanner);
}

{preproc} {
	char *start, *end, *filename;
	int line;
	
	filename = NULL;
	line = -1;
	start = yytext + 1;
	if(isspace(*start))
	{
		start++;
	}
	if(isdigit(*start))
	{
		/* Process linemarkers from the CPP:
		 * # linenum "filename" flags
		 */
		end = start;
		while(isdigit(*end))
		{
			end++;
		}
		if(*end && !isspace(*end))
		{
			idl_module_error(curmod, yylloc, "invalid linemarker: %s", yytext);
		}
		if(*end)
		{
			*end = 0;
			end++;
			while(isspace(*end))
			{
				end++;
			}
		}
		line = atoi(start);
		start = end;
		if(*start)
		{
			if(*start != '"')
			{
				idl_module_error(curmod, yylloc, "invalid linemarker: %s", yytext);
			}
			start++;
			end = start;
			while(*end && *end != '"')
			{
				if(*end == '\\')
				{
					end++;
					if(!*end)
					{
						break;
					}
				}
				end++;
			}
			if(*end != '"')
			{
				idl_module_error(curmod, yylloc, "invalid linemarker: %s", yytext);
			}
			*end = 0;
			filename = start;
		}
		if(newloc)
		{
			free(newloc->filename);
		}
		memset(&locbuf, 0, sizeof(locbuf));
		newloc = &locbuf;
		newloc->first_line = newloc->last_line = line;
		newloc->first_column = newloc->last_column = 1;
		if(filename)
		{
			newloc->filename = strdup(filename);
		}
	}
	else if(isalpha(*start))
	{
		end = start;
		while(isalnum(*end) || *end == '_' || *end == '$')
		{
			end++;
		}
		if(*end)
		{
			if(!isspace(*end))
			{
				idl_module_error(curmod, yylloc, "invalid preprocessor directive: %s", yytext);
			}
			if(!strcmp(start, "ident") || !strcmp(start, "pragma"))
			{
				idl_module_warning(curmod, yylloc, "ignoring unsupported #%s preprocessor directive", start);
			}
			else
			{
				idl_module_error(curmod, yylloc, "invalid preprocessor directive: %s", yytext);
			}
		}
	}
	else
	{
		idl_module_error(curmod, yylloc, "invalid preprocessor directive: %s", yytext);
	}
}

{uuid} {
	strncpy(shortbuf, yytext, sizeof(shortbuf));
	shortbuf[sizeof(shortbuf)-1] = 0;
	*yylval = shortbuf;
	return(UUID);
}

{id} {
	strncpy(shortbuf, yytext, sizeof(shortbuf));
	shortbuf[sizeof(shortbuf)-1] = 0;
	*yylval = shortbuf;
	return idl_keyword_lookup(yytext);
}

{c_hex_integer} {
	strncpy(shortbuf, yytext, sizeof(shortbuf));
	shortbuf[sizeof(shortbuf)-1] = 0;
	*yylval = shortbuf;
	return INTEGER_NUMERIC;
}

{integer} {
	strncpy(shortbuf, yytext, sizeof(shortbuf));
	shortbuf[sizeof(shortbuf)-1] = 0;
	*yylval = shortbuf;
	return INTEGER_NUMERIC;
}

{float} {
	strncpy(shortbuf, yytext, sizeof(shortbuf));
	shortbuf[sizeof(shortbuf)-1] = 0;
	*yylval = shortbuf;
	return FLOAT_NUMERIC;
}

{other} {
	idl_module_error(curmod, yylloc, "parse error near '%s'", yytext);
}

%%

static void
commenteof(struct yyguts_t * yyg, void *yyscanner)
{
	(void) yyg;
	
	idl_module_error(curmod, yylloc, "Unexpected end of file while parsing C-style comment");
}

static void
read_c_comment(struct yyguts_t * yyg, void *yyscanner)
{
	register int c;

	/* While not EOF look for end of comment */
	while ((c = input(yyscanner)))
	{
		if (c == '*')
		{
			if ((c = input(yyscanner)) == '/')
			{
				break;
			}
			else
			{
				unput(c);
			}
		}
	}
	/* Didn't find end comment before EOF, issue error */
	if (c == 0)
	{
		commenteof(yyg, yyscanner);
	}
}

static void
update_location(struct yyguts_t *yyg, YYLTYPE *loc)
{
	if(newloc)
	{
		free(loc->filename);
		*loc = *newloc;
		newloc = NULL;
		yylineno = loc->first_line - 1;
		yycolumn = loc->first_column;
	}
	else
	{
		loc->first_line = yylloc->last_line = yylineno;
		loc->first_column = yycolumn;
	}
	loc->last_column = yycolumn + yyleng - 1;
	yycolumn += yyleng;
}
