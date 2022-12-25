/* Executive Microkernel
 * Headers/Executive/Linkage.h
 *   Macros to control symbol naming and calling conventions
 */

#ifndef EXECUTIVE_LINKAGE_H_
# define EXECUTIVE_LINKAGE_H_          1


# ifndef __stdcall
#  ifndef _WIN32
#   define __stdcall
#  endif
# endif

# ifdef __cplusplus
#  define restrict
# endif

/* Define Microsoft IDL-compatible macros because that allows the use of any
 * of the several available IDL compiler implementations which generate headers
 * using them (including Microsoft's own, if building on Windows)
 */
# if defined(__cplusplus)
#  define EXTERN_C extern "C"
#  define DECLARE_INTERFACE(name) \
	struct name
#  define DECLARE_INTERFACE_(name, parent) \
	struct name: public parent
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS
#  define THIS_
#  define PURE = 0
#  define STDMETHOD_(type, name) \
	virtual type __stdcall name
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# else /*__cplusplus*/
#  define EXTERN_C extern
#  define DECLARE_INTERFACE(name) \
	typedef struct name name; \
	struct name { \
		const struct name##_vtable_ *lpVtbl; \
		const void *instptr; \
	}; \
	struct name##_vtable_
#  define DECLARE_INTERFACE_(name, parent) \
	DECLARE_INTERFACE(name)
#  define BEGIN_INTERFACE
#  define END_INTERFACE
#  define THIS \
	struct INTERFACE *self
#  define THIS_ \
	struct INTERFACE *self,
#  define PURE
#  define STDMETHOD_(type, name) \
	type __stdcall (*name)
#  define STDMETHOD(name) \
	STDMETHOD(int, name)
# endif /*__cplusplus*/

# define UNUSED__(x)                   (void) (x)

# undef HAS_SYMBOL__
# undef HAS_LEADING_UNDERSCORE__
# undef HAS_WEAK_ALIAS__
# undef HAS_WEAK_IMPORT__
# undef HAS_WEAK_STUB__

# if defined(__GNUC__)
/* <https://gcc.gnu.org/onlinedocs/gcc-12.2.0/gcc/Asm-Labels.html#Asm-Labels> */
#  define HAS_SYMBOL__                  1
#  define HAS_LEADING_UNDERSCORE__      1
#  if defined(__APPLE__) || defined(__MSDOS__) || defined(_WIN32)
#   define SYMBOL__(name)               __asm__("_" name)
#  else
#   define SYMBOL__(name)               __asm__(name)
#  endif
# endif

# if defined(__APPLE__)
#  if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#   define HAS_WEAK_IMPORT__           1
#   define WEAK_IMPORT__               __attribute__((weak_import))
#  endif
# endif

# if defined(__GNUC__) && (defined(__APPLE__) || defined(__ELF__))
#  define HAS_WEAK_STUB__              1
#  define WEAK_STUB__                  __attribute__((weak))
# endif /* __GNUC__&&(__APPLE__||__ELF__)*/

# ifndef  SYMBOL__
#  define SYMBOL__(name)               /* not implemented */
# endif

# ifndef WEAK_ALIAS__
#  define WEAK_ALIAS__(name)           /* not implemented */
# endif

# ifndef WEAK_IMPORT__
#  define WEAK_IMPORT__                /* not implemented */
# endif

# ifndef WEAK_STUB__
#  define WEAK_STUB__                  /* not implemented */
# endif

# ifndef SYMNAME__
#  define SYMNAME__(module, symname, version) module "__" symname
# endif

# ifndef SYM__
#  define SYM__(module, symbol, version) SYMBOL__(SYMNAME__(module, #symbol, version))
# endif

# ifndef EXEC_LINKAGE__
#  define EXEC_LINKAGE__(name, version) SYM__("EXECUTIVE", name, version) WEAK_IMPORT__
# endif

#endif /*!EXECUTIVE_LINKAGE_H_*/
