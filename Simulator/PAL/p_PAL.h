/* Executive Microkernel
 * Simulator Platform Adaptation Layer (PAL)
 */

#ifndef P_PAL_H_
# define P_PAL_H_                      1

# define INITGUID_EXTERN               1

/* Diagnostics and panic output */
#  include <cstdio>
/* Errno values */
#  include <cerrno>
/* malloc(), free(), etc. */
#  include <cstdlib>
/* memcmp() */
#  include <cstring>
/* sleep()  */
#  include <unistd.h>
#  include <cstdarg>
/* sigsetjmp, etc. */
# include <setjmp.h>
/* sigaction(), etc. */
# include <signal.h>
/* mmap() */
# include <sys/mman.h>

# include <PAL/PAL.h>

# include <Executive/IWriteChannel.h>
# include <Executive/IContainer.h>
# include <Executive/INamespace.h>

# include <Executive/IMutableContainer.h>
# include <Executive/MFactory.h>

# include <Executive/Classes.h>
# include <Executive/Internal/Classes.h>

# include <Simulator/Internal/Platform.h>
# include <Simulator/Internal/AddressSpace.h>
# include <Simulator/Internal/Region.h>
# include <Simulator/Internal/Context.h>

#endif /*!P_PAL_H_*/