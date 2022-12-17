/* This header is intended to be included more than once */

#ifndef UUID_INIT__
/* the byte sequence is expected to be in network byte order (i.e., the order
 * as a UUID is generally displayed)
 */
# define UUID_INIT__(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
	{ { ((d0) << 24) | ((d1) << 16) | ((d2) << 8) | (d3), \
	((d4) << 8) | (d5), \
	((d6) << 8) | (d7), \
	d8, \
	d9, \
	{ d10, d11, d12, d13, d14, d15 }\
	} }
#endif /*!UUID_INIT__*/

#undef UUID_DEFINE
#undef DEFINE_GUID

#if defined(INITGUID)

/* if INITGUID is defined, declare an external-linkage const literal */
# ifdef __cplusplus
#  define UUID_DEFINE(name, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
extern "C" const UUID name = UUID_INIT__(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15)
# else
#  define UUID_DEFINE(name, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
const UUID name = UUID_INIT__(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15)
# endif

#elif !defined(INITGUID_EXTERN) && defined(__GNUC__)

/* if INITGUID is not defined and we're using GCC or Clang, declare as static-
 * linkage const literal instead (set INITGUID_EXTERN to override this) */

# define UUID_DEFINE(name, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
static const UUID name __attribute__((unused)) = UUID_INIT__(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15)

 #else

 /* otherwise, declare it as an extern */

# ifdef __cplusplus
#  define UUID_DEFINE(name, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) extern "C" const UUID name;
# else
#  define UUID_DEFINE(name, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) extern const UUID name;
# endif

#endif /*INITGUID*/
