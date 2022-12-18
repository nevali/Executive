/* Executive Microkernel
 * Runtime support
 */

#ifndef P_RUNTIME_H_
# define P_RUNTIME_H_                  1

# define INITGUID_EXTERN       1

# include <Executive/UUID.h>
# include <Executive/Internal/Runtime.h>

# ifdef __cplusplus
extern "C" {
# endif

int rpl_vsnprintf(char *, size_t, const char *, va_list);
int rpl_snprintf(char *, size_t, const char *, ...);
int rpl_vasprintf(char **, const char *, va_list);
int rpl_asprintf(char **, const char *, ...);

# ifdef __cplusplus
}
# endif

#endif /*!P_RUNTIME_H_*/