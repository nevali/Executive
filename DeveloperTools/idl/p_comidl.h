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

#ifndef P_COMIDL_H_
# define P_COMIDL_H_                   1

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

# ifndef HAVE_GETOPT
extern int opterr, optind, optopt, optreset;
extern char *optarg;
extern int getopt(int argc, char * const argv[], const char *options);
# endif

# ifndef YYSTYPE
#  define YYSTYPE char *
# endif

# include "idlparse.h"

typedef char idl_ident_t[64];

# define IDL_IDENT_MAX (sizeof(idl_ident_t) - 1)

typedef struct idl_module_struct idl_module_t;
typedef struct idl_scope_struct idl_scope_t;
typedef struct idl_interface_struct idl_interface_t;
typedef struct idl_symlist_struct idl_symlist_t;
typedef struct idl_symdef_struct idl_symdef_t;
typedef struct idl_typedecl_struct idl_typedecl_t;
typedef struct idl_expr_struct idl_expr_t;

typedef struct idl_guid_struct idl_guid_t;

typedef enum
{
	MODE_UNSPEC = 0,
	MODE_RPC,
	MODE_COM,
	MODE_MSCOM,
	MODE_DCERPC,
	MODE_SUNRPC,
	MODE_XPCOM,
	MODE_TALISKER
} idl_mode_t;

typedef enum
{
	BLOCK_UNSPEC = 0,
	BLOCK_INTERFACE,
	BLOCK_MODULE,
	BLOCK_COCLASS,
	BLOCK_LIBRARY,
	BLOCK_DISPINTERFACE
} idl_containertype_t;

typedef enum
{
	ST_MODULE,
	ST_CONTAINER,
	ST_SYMDEF,
	ST_QUOTE,
	ST_IMPORT
} idl_scopetype_t;

typedef enum
{
	PTRCLASS_UNIQUE,
	PTRCLASS_REF,
	PTRCLASS_PTR
} idl_ptrclass_t;

typedef enum
{
	TYPE_NONE,
	TYPE_VOID,
	TYPE_CHAR,
	TYPE_SHORT,
	TYPE_INT,
	TYPE_LONG,
	TYPE_LONGLONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_BOOLEAN,
	TYPE_STRUCT,
	TYPE_UNION,
	TYPE_ENUM,
	TYPE_INTERFACE,
	TYPE_DEF,
	TYPE_INT8,
	TYPE_INT16,
	TYPE_INT32,
	TYPE_INT64
} idl_builtintype_t;

typedef enum
{
	TYPEMOD_NONE = 0,
	TYPEMOD_SIGNED = (1<<0),
	TYPEMOD_UNSIGNED = (1<<1),
	TYPEMOD_CONST = (1<<2)
} idl_typemod_t;

typedef enum
{
	DECL_POINTER,
	DECL_CONST,
	DECL_RESTRICT,
	DECL_LBRACKET,
	DECL_RBRACKET,
	DECL_IDENT
} idl_declarator_t;

typedef enum
{
	SYM_UNSPEC = 0,
	SYM_TYPEDEF,
	SYM_METHOD,
	SYM_PARAM,
	SYM_MEMBER,
	SYM_CONST,
	SYM_ENUM,
	SYM_STRUCT
} idl_symtype_t;

typedef enum
{
	EXPR_UNSPEC = 0,
	EXPR_CONST,
	EXPR_SYM,
	EXPR_ADD,
	EXPR_SUB,
	EXPR_DIV,
	EXPR_MUL,
	EXPR_MOD,
	EXPR_AND,
	EXPR_BITAND,
	EXPR_OR,
	EXPR_BITOR,
	EXPR_XOR,
	EXPR_EQUALS,
	EXPR_NOTEQUALS,
	EXPR_LESSEQUALS,
	EXPR_GTEQUALS,
	EXPR_LESS,
	EXPR_GT,
	EXPR_BRACKET,
	EXPR_BITNOT,
	EXPR_NOT,
	EXPR_IFELSE,
	EXPR_LSHIFT,
	EXPR_RSHIFT
} idl_exprtype_t;

struct idl_guid_struct
{
	char name[IDL_IDENT_MAX + 16];
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t data4[8];
};

struct idl_symlist_struct
{
	idl_symtype_t symtype;
	idl_symlist_t *parent;
	idl_symdef_t **defs;
	size_t ndefs;
};

struct idl_scope_struct
{
	idl_scope_t *parent;
	idl_scope_t *first, *last;
	idl_scope_t *next;
	idl_scopetype_t type;
	idl_module_t *module;
	int line;
	idl_interface_t *container;
	idl_symdef_t *symdef;
	char *text;
};

struct idl_module_struct
{
	int included; /* if this is an imported module */
	void *scanner;
	char *filename; /* final filename, e.g., /Library/Frameworks/COM/Headers/wtypes.idl */
	char *shortname; /* short filename, e.g., COM/wtypes.idl */
	char *houtname; /* header output filename, e.g., wtypes.h */
	FILE *hout;
	char *hmacro; /* e.g., COMIDL_WTYPES_H_ */
	size_t houtdepth; /* indenting level */
	idl_mode_t mode; /* output mode */
	idl_guid_t const **guids; /* GUIDs defined by this module */
	size_t nguids;
	idl_scope_t rootscope;
	idl_scope_t *cur;
	idl_interface_t **interfaces; /* interfaces defined by this module */
	size_t ninterfaces;
	idl_interface_t *curintf;
	idl_symlist_t *cursymlist;
	idl_typedecl_t *typestack[32];
	size_t typestackpos;
	idl_typedecl_t *curtype;
	idl_symdef_t *cursym;
	int nodefinc;
	int nodefimports;
	int headerwritten;
	struct idl_emitter_struct *emitter;
};

struct idl_interface_struct
{
	idl_module_t *module;
	idl_containertype_t type;
	idl_guid_t uuid;
	unsigned long version;
	unsigned long id;
	int local;
	int object;
	idl_ptrclass_t pointer_default;
	idl_ident_t name;
	idl_interface_t *ancestor;
	idl_symlist_t symlist;
	idl_symlist_t *cursymlist;
	idl_symdef_t *firstsym;
	int stub, resolved;
	idl_interface_t *target;
	char *cheader;
};

struct idl_symdef_struct
{
	idl_symtype_t type;
	/* Attributes */
	int local;
	/* Type  */
	idl_builtintype_t const_type;
	idl_typedecl_t *decl;
	/* Declarator */
	size_t ndeclarator;
	idl_declarator_t declarator[16];
	/* Identifier */
	idl_ident_t ident;
	/* Implied attributes */
	/* For methods and function pointers, the parameter lists */
	int is_fp;
	idl_symlist_t fp_params;
	/* Array attributes */
	int is_array;
	ssize_t array_len;
	/* For constants, the constant value. Constants may only be 'small' or 'long' */
	idl_expr_t *constval;
	int noval; /* Enums with no explicit value */
	/* For chained symbols, the next symbol in the chain */
	idl_symdef_t *nextsym;
};

struct idl_typedecl_struct
{
	/* Attributes */
	idl_builtintype_t builtin_type;
	idl_symdef_t *user_type;
	/* Modifiers */
	idl_typemod_t modifiers;
	/* Tag for enums, structs, unions */
	idl_ident_t tag;
	/* Symbol list for enums, structs and unions */
	int has_symlist;
	idl_symlist_t symlist;
};

struct idl_expr_struct
{
	idl_exprtype_t type;
	int isconst;
	long constval;
	const idl_expr_t *left, *right, *alt;
	idl_symdef_t *symdef;
};

struct idl_emitter_struct
{
	int (*init)(idl_module_t *module);
	int (*done)(idl_module_t *module);
	int (*intf_prologue)(idl_module_t *module, idl_interface_t *intf);
	int (*intf_epilogue)(idl_module_t *module, idl_interface_t *intf);
	int (*emit_cppquote)(idl_module_t *module, const char *quote);
	int (*emit_typedef)(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
	int (*emit_method)(idl_module_t *module, idl_interface_t *intf, idl_symdef_t *symdef);
	int (*emit_const)(idl_module_t *module, idl_symdef_t *symdef);
	int (*emit_import)(idl_module_t *module, idl_interface_t *intf);
};

extern idl_module_t *curmod;
extern const char *progname;
extern int nostdinc;
extern int nodefimports;
extern int nodefinc;
extern idl_mode_t defmode;

# define YY_DECL int yylex(YYSTYPE *yylval_param, void *yyscanner)
extern YY_DECL;

extern int yylex_init(void **scanner);
extern int yylex_destroy(void *scanner);
extern int yyparse(void *scanner);
extern void yyrestart(FILE *f, void *scanner);
extern char *yyget_text (void *yyscanner);
extern int yyget_lineno (void *yyscanner);

extern idl_mode_t idl_mode_parse(const char *modestr);
extern int idl_parse(const char *src, const char *hout, int defimp, int useinc);

extern int idl_keyword_lookup(const char *s);

extern void idl_module_vmsg(idl_module_t *module, int line, const char *prefix, const char *fmt, va_list ap);
extern void idl_module_error(idl_module_t *module, int line, const char *fmt, ...);
extern void idl_module_errmsg(idl_module_t *module, int line, const char *fmt, ...);
extern void idl_module_warning(idl_module_t *module, int line, const char *fmt, ...);
extern void idl_module_terminate(void);

extern idl_module_t *idl_module_create(const char *filename, const char *hout);
extern int idl_module_done(idl_module_t *module);

extern idl_scope_t *idl_module_scope_push(idl_module_t *module);
extern idl_scope_t *idl_module_scope_pop(idl_module_t *module);

extern idl_module_t *idl_module_lookup(const char *pathname);
extern idl_interface_t *idl_module_lookupintf(const char *name, int incstubs);
extern int idl_module_addintf(idl_module_t *module, idl_interface_t *intf);
extern int idl_module_doneintf(idl_module_t *module, idl_interface_t *intf);
extern int idl_module_addguid(idl_module_t *module, const idl_guid_t *guid);
extern idl_typedecl_t *idl_module_typedecl_push(idl_module_t *module);
extern idl_typedecl_t *idl_module_typedecl_pop(idl_module_t *module);
extern idl_symdef_t *idl_module_symdef_create(idl_module_t *module, idl_symlist_t *symlist, idl_typedecl_t *typedecl);
extern int idl_module_symdef_add(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *sym);
extern int idl_module_symdef_done(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *sym);
extern int idl_module_symdef_link(idl_module_t *module, idl_symlist_t *symlist, idl_symdef_t *symdef);
extern idl_symdef_t *idl_module_symdef_lookup(idl_module_t *module, idl_symlist_t *start, const char *name, int recurse);
extern int idl_module_symlist_push(idl_module_t *module, idl_symlist_t *symlist);
extern int idl_module_symlist_pop(idl_module_t *module, idl_symlist_t *symlist);
extern int idl_module_set_mode(idl_module_t *module, int line, const char *mode);

extern idl_interface_t *idl_intf_create(idl_module_t *module);
extern idl_interface_t *idl_intf_stub(idl_module_t *module, const char *name);
extern int idl_intf_done(idl_interface_t *intf);
extern int idl_intf_uuid(idl_interface_t *intf, const char *uuid);
extern int idl_intf_name(idl_interface_t *intf, const char *name);
extern int idl_intf_set_cheader(idl_interface_t *intf, const char *header);
extern int idl_intf_started(idl_interface_t *intf);
extern int idl_intf_finished(idl_interface_t *intf);
extern idl_interface_t *idl_intf_lookup(const char *name);
extern int idl_intf_resolve(idl_interface_t *intf);
extern idl_symdef_t *idl_intf_symdef_create(idl_interface_t *intf, idl_typedecl_t *typedecl);
extern int idl_intf_symdef_done(idl_interface_t *intf, idl_symdef_t *symdef);
extern int idl_intf_symdef_link(idl_interface_t *intf, idl_symdef_t *symdef);
extern idl_symdef_t *idl_intf_symdef_lookup(idl_interface_t *intf, const char *name);
extern int idl_intf_symlist_push(idl_interface_t *intf, idl_symlist_t *symlist);
extern int idl_intf_symlist_pop(idl_interface_t *intf, idl_symlist_t *symlist);
extern int idl_intf_method_exists(idl_interface_t *intf, const char *methodname);
extern int idl_intf_method_exists_recurse(idl_interface_t *intf, const char *methodname);
extern int idl_intf_method_inherited(idl_interface_t *intf, const char *methodname);

extern int idl_emit(idl_module_t *module);

/* C/C++ emitting helpers */
extern int idl_emit_cxxinc_open(idl_module_t *module);
extern void idl_emit_cxxinc_close(idl_module_t *module);
extern void idl_emit_cxx_write_expr(idl_module_t *module, FILE *f, const idl_expr_t *expr);
extern void idl_emit_cxx_write_type(idl_module_t *module, FILE *f, idl_typedecl_t *decl);
extern void idl_emit_cxx_write_symdef(idl_module_t *module, FILE *f, idl_symdef_t *symdef, const char *fmt, const char *paramprefix, const char *voidstr);
extern int idl_emit_cxx_write_sym(idl_module_t *module, FILE *f, idl_symdef_t *symdef, const char *fmt);
extern void idl_emit_cxx_write_indent(idl_module_t *module, FILE *f);
extern void idl_emit_cxx_builtin_type(FILE *f, idl_builtintype_t type, idl_typemod_t modifiers);

extern int idl_incpath_reset(void);
extern int idl_incpath_add_includedir(const char *path);
extern int idl_incpath_add_frameworkdir(const char *path);
extern int idl_incpath_locate(char *buf, size_t buflen, const char *path);

extern idl_expr_t *idl_expr_create(void);
extern idl_expr_t *idl_expr_create_intconst(long value);
extern idl_expr_t *idl_expr_create_pair(const idl_expr_t *left, idl_exprtype_t op, const idl_expr_t *right);
extern idl_expr_t *idl_expr_create_bracket(const idl_expr_t *expr);
extern idl_expr_t *idl_expr_create_prefix(idl_exprtype_t op, const idl_expr_t *expr);
extern idl_expr_t *idl_expr_create_sym(idl_interface_t *curintf, const char *sym);

#endif /* !P_COMIDL_H_ */
