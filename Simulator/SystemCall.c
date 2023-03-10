#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <stdarg.h>
#include <string.h>

#include <stdio.h>

#include <Executive/SystemCall.h>
#include <Executive/Internal/Despatch.h>

/* This function is invoked in user space when the simmulated runtime or user
 * program wants to make a system call
 */
int
ExSystemCall(int descriptor, int method, ...)
{
	va_list ap;
	ExecutiveDespatch despatch;

	/* Hand off the call to the Executive's Despatch Gateway, which is responsible
	 * for informing the scheduler that it's currently suspended on the current
	 * processor, and routing the request (amongst other things)
	 *
	 * To do this, assemble an ExecutiveDespatch structure, which captures the
	 * system call arguments as they would be passed in registers (modulo
	 * architecture-specific nuance which would normally be handled by the
	 * real trap code)
	 *
	 */
	memset(&despatch, 0, sizeof(ExecutiveDespatch));
	despatch.syscall.type = EDT_SYSCALL;
	despatch.syscall.arg[0] = descriptor;
	despatch.syscall.arg[1] = method;
	va_start(ap, method);
#if 0
	if(method == -1)
	{
		/* XXX this will work on LP64 and LP32 but not LLP64, etc. */
		despatch.syscall.arg[2] = va_arg(ap, ExecutiveIndirectCall *);
	}
	else
#endif
	{
		despatch.syscall.arg[2] = va_arg(ap, uintptr_t);
		despatch.syscall.arg[3] = va_arg(ap, uintptr_t);
		despatch.syscall.arg[4] = va_arg(ap, uintptr_t);
		despatch.syscall.arg[5] = va_arg(ap, uintptr_t);
		despatch.syscall.arg[6] = va_arg(ap, uintptr_t);
		despatch.syscall.arg[7] = va_arg(ap, uintptr_t);
	}
	va_end(ap);
#if 0
	fprintf(stderr, "Simulator:  ExSystemCall(%d, %04x, %lx, %lx, %lx, %lx, %lx, %lx)\n", descriptor, method,
		despatch.syscall.arg[2], despatch.syscall.arg[3],
		despatch.syscall.arg[4], despatch.syscall.arg[5],
		despatch.syscall.arg[6], despatch.syscall.arg[7]);
#endif
	Executive_despatch(&despatch);
	return despatch.syscall.status;
}
