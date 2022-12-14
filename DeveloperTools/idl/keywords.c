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

struct idl_keyword_struct
{
	const char *kw;
	int token;
};

static struct idl_keyword_struct keywords[] = 
{
	{ "align", ALIGN_KW },
	{ "array", ARRAY_KW }, /* XPCOM */
	{ "astring", ASTRING_KW }, /* XPCOM */
	
	{ "binaryname", BINARYNAME_KW }, /* XPCOM */
	{ "boolean", BOOLEAN_KW },
	{ "broadcast", BROADCAST_KW },
	{ "byte", BYTE_KW },
	
	{ "call_as", CALL_AS_KW },
	{ "case", CASE_KW },
	{ "char", CHAR_KW },
	{ "cheader", CHEADER_KW }, /* Talisker */
	{ "coclass", COCLASS_KW },
	{ "const", CONST_KW },
	{ "comm_status", COMM_STATUS_KW },
	{ "context_handle", CONTEXT_HANDLE_KW },
	{ "cpp_quote", CPP_QUOTE_KW }, /* MSRPC */
	{ "cstring", CSTRING_KW }, /* XPCOM */
	
	{ "default", DEFAULT_KW },
	{ "dispinterface", DISPINTERFACE_KW },
	{ "domstring", DOMSTRING_KW }, /* XPCOM */
	{ "double", DOUBLE_KW },
	
	{ "endpoint", ENDPOINT_KW },
	{ "enum", ENUM_KW },
	{ "exceptions", EXCEPTIONS_KW },
	
	{ "FALSE", FALSE_KW },
	{ "first_is", FIRST_IS_KW },
	{ "float", FLOAT_KW },
	{ "function", FUNCTION_KW }, /* XPCOM */
	
	{ "handle", HANDLE_KW },
	{ "handle_t", HANDLE_T_KW },
	{ "hyper", HYPER_KW },
	
	{ "id", ID_KW },
	{ "idempotent", IDEMPOTENT_KW },
	{ "ignore", IGNORE_KW },
	{ "iid_is", IID_IS_KW },
	{ "implicit_handle", IMPLICIT_HANDLE_KW },
	{ "import", IMPORT_KW },
	{ "in", IN_KW },
	{ "inout", INOUT_KW }, /* XPCOM, CORBA */
	{ "int", INT_KW },
	{ "interface", INTERFACE_KW },
	
	{ "last_is", LAST_IS_KW },
	{ "length_is", LENGTH_IS_KW },
	{ "library", LIBRARY_KW }, /* MSRPC */
	{ "local", LOCAL_KW },
	{ "long", LONG_KW },
	
	{ "max_is",  MAX_IS_KW },
	{ "maybe", MAYBE_KW },
	{ "min_is", MIN_IS_KW },
	{ "mode", MODE_KW}, /* libcom */
	{ "module", MODULE_KW }, /* MSRPC */
	{ "mutable", MUTABLE_KW }, /* MSRPC */
	
	{ "NULL", NULL_KW },
	{ "native", NATIVE_KW }, /* XPCOM */
	{ "nodefinc", NODEFINC_KW }, /* comidl */
	{ "noscript", NOSCRIPT_KW }, /* XPCOM */
	{ "notxpcom", NOTXPCOM_KW }, /* XPCOM */
	{ "nsid", NSID_KW }, /* XPCOM */
	
	{ "object", OBJECT_KW }, /* MSRPC, XPCOM */
	{ "octet", OCTET_KW }, /* XPCOM */
	{ "out", OUT_KW },
	
	{ "pipe", PIPE_KW },
	{ "pointer_default", POINTER_DEFAULT_KW },
	{ "program", PROGRAM_KW }, /* ONC RPC */
	{ "ptr", PTR_KW },

	{ "range", RANGE_KW },
	{ "ref", REF_KW },
	{ "reflect_deletions", REFLECT_DELETIONS_KW },
	{ "remote", REMOTE_KW },
	{ "restrict", RESTRICT_KW },
	{ "retval", RETVAL_KW }, /* XPCOM */
	
	{ "scriptable", SCRIPTABLE_KW }, /* XPCOM */
	{ "secure", SECURE_KW },
	{ "shape", SHAPE_KW },
	{ "short", SHORT_KW },
	{ "signed", SIGNED_KW },
	{ "size_is", SIZE_IS_KW },
	{ "small", SMALL_KW },
	{ "string", STRING_KW },
	{ "struct", STRUCT_KW },
	{ "switch", SWITCH_KW },
	{ "switch_is", SWITCH_IS_KW },
	{ "switch_type", SWITCH_TYPE_KW },

	{ "TRUE", TRUE_KW },
	{ "transmit_as", TRANSMIT_AS_KW },
	{ "typedef", TYPEDEF_KW },
	
	{ "union", UNION_KW },
	{ "unique", UNIQUE_KW },
	{ "unsigned", UNSIGNED_KW },
	{ "utf8string", UTF8STRING_KW }, /* XPCOM */
	{ "uuid", UUID_KW },
	
	{ "v1_array", V1_ARRAY_KW },
	{ "v1_enum", V1_ENUM_KW },
	{ "v1_string", V1_STRING_KW },
	{ "v1_struct", V1_STRUCT_KW },
	{ "version", VERSION_KW },
	{ "void", VOID_KW },
	
	{ "wchar", WCHAR_KW }, /* XPCOM */
	{ "wire_marshal", WCHAR_KW }, /* MSRPC */
	{ "wstring", WSTRING_KW }, /* XPCOM */
	
	{ NULL, -1 }
};

int
idl_keyword_lookup(const char *s)
{
	size_t c;
	int r;
	
	for(c = 0; NULL != keywords[c].kw && (r = strcmp(keywords[c].kw, s)); c++)
	{
		if(r > 0)
		{
			break;
		}
	}
	if(0 == r)
	{
		return keywords[c].token;
	}
	return IDENTIFIER;
}
