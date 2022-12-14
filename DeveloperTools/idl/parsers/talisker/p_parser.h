/* Copyright (c) 2008-2018 Mo McRoberts.
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

#ifndef P_PARSER_H_
# define P_PARSER_H_                   1

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <ctype.h>
# include <stdarg.h>
# ifdef HAVE_STDINT_H
#  include <stdint.h>
# endif
# ifdef HAVE_INTTYPES_H
#  include <inttypes.h>
# endif
# ifdef HAVE_UNISTD_H
#  include <unistd.h>
# endif
# ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>
# endif
# include <sys/stat.h>
# include <limits.h>
# include <assert.h>
# include <jansson.h>

# ifndef HAVE_GETOPT
extern int opterr, optind, optopt, optreset;
extern char *optarg;
extern int getopt(int argc, char * const argv[], const char *options);
# endif

# ifndef YYSTYPE
#  define YYSTYPE char *
# endif

# ifndef YYLTYPE
#  define YYLTYPE yyltype
# endif

typedef struct yyltype {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	char *filename;
} yyltype;

struct yyguts_t;

# include "idlparse.h"

typedef char idl_ident_t[64];

# define IDL_IDENT_MAX (sizeof(idl_ident_t) - 1)

typedef struct idl_module_struct idl_module_t;

struct idl_module_struct
{
	int included; /* if this is an imported module */
	void *scanner;
	char *filename; /* final filename, e.g., /Library/Frameworks/COM/Headers/wtypes.idl */
	char *shortname; /* short filename, e.g., COM/wtypes.idl */
	struct idl_emitter_struct *emitter;
	
	json_t *ir; /* Current JSON object pointer */
	json_t *irroot; /* JSON intermediate representation */
	json_t *irstack[32]; /* Current JSON object stack */
	size_t irsp; /* JSON object stack pointer */
	json_t *irtype; /* Current type being parsed */
	json_t *pending; /* Attributes which will be applied to the next-pushed object */
	
	int nodefimports;
};

extern idl_module_t *curmod;
extern const char *progname;
extern int nodefimports;

/* Tokenizer */

extern int idl_keyword_lookup(const char *s);

/* Yacc-based parser */

# define YY_DECL int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, void *yyscanner)
extern YY_DECL;

extern int yylex_init(void **scanner);
extern int yylex_destroy(void *scanner);
extern int yyparse(void *scanner);
extern void yyrestart(FILE *f, void *scanner);
extern char *yyget_text (void *yyscanner);
extern int yyget_lineno (void *yyscanner);


/* IDL parser */

extern int idl_parse(const char *src, int defimp, int useinc);

extern void idl_module_vmsg(idl_module_t *module, YYLTYPE *loc, const char *prefix, const char *fmt, va_list ap);
extern void idl_module_error(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...);
extern void idl_module_errmsg(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...);
extern void idl_module_warning(idl_module_t *module, YYLTYPE *loc, const char *fmt, ...);
extern void idl_module_terminate(void);

/* Parse-module handling */
extern idl_module_t *idl_module_create(const char *filename);
extern int idl_module_add(idl_module_t *module);
extern int idl_module_done(idl_module_t *module);
extern int idl_module_output(void);

extern idl_module_t *idl_module_lookup(const char *pathname);

/* Import paths */

int idl_incpath_reset(void);
int idl_incpath_add_includedir(const char *path);
int idl_incpath_locate(char *buf, size_t buflen, const char *path);

/* JSON IR emitter */

json_t *idl_json_push_as(idl_module_t *module, const char *type, const char *target, YYLTYPE *loc);
json_t *idl_json_push(idl_module_t *module, const char *type, YYLTYPE *loc);
int idl_json_pop(idl_module_t *module);
int idl_json_attr(idl_module_t *module, const char *attr, json_t *value);

json_t *idl_json_push_type(idl_module_t *module);
int idl_json_pop_type(idl_module_t *module);
int idl_json_type_attr(idl_module_t *module, const char *attr, json_t *value);
int idl_json_pointer(idl_module_t *module, const char *ptrtype);

#endif /* !P_PARSER_H_ */
