/* Copyright (c) 2015-2022 Mo McRoberts.
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
# include "BuildConfiguration.h"
#endif

#include <stdio.h>

#include "p_AddressSpace.h"

#define INTF_TO_CLASS(i)               (PAL_POSIX_Context *)((void *)(i))

static void PAL_POSIX_Context_destroy(PAL_POSIX_Context *self);

/* IObject */

static int PAL_POSIX_Context_queryInterface(IContext *me, REFUUID riid, void **ptr);
static int32_t PAL_POSIX_Context_retain(IContext *me);
static int32_t PAL_POSIX_Context_release(IContext *me);

/* IContext */

static bool PAL_POSIX_Context_swap(IContext *me, IContext *to);

static struct IContext_vtable_ PAL_POSIX_Context_vtable = {
	PAL_POSIX_Context_queryInterface,
	PAL_POSIX_Context_retain,
	PAL_POSIX_Context_release,
	PAL_POSIX_Context_swap
};

/*PRIVATE*/

static void PAL_POSIX_Context_trampoline(int signo);
static void PAL_POSIX_Context_bootstrap(void);
static void PAL_POSIX_Context_start(PAL_POSIX_Context *ctx);

static volatile sig_atomic_t trampoline_sprung;
static volatile jmp_buf trampoline_caller;
static volatile jmp_buf trampoline_jb;
static volatile PAL_POSIX_Context *trampoline_context;

PAL_POSIX_Context *
PAL_POSIX_Context_create(PAL_POSIX_AddressSpace *addressSpace)
{
	PAL_POSIX_Context *ctx;

	if(NULL == (ctx = (PAL_POSIX_Context *) calloc(1, sizeof(PAL_POSIX_Context))))
	{
		return NULL;
	}
	ctx->Context.lpVtbl = &PAL_POSIX_Context_vtable;
	ctx->data.addressSpace = addressSpace;
	ctx->data.refCount = 1;
	return ctx;
}

/* PRIVATE */
static void
PAL_POSIX_Context_destroy(PAL_POSIX_Context *self)
{
	free(self);
}

#define VOLATILE_JMPBUF(x) (*((jmp_buf *) &(x)))

/* PRIVATE */
void
PAL_POSIX_Context_setup(PAL_POSIX_Context *self)
{
    struct sigaction sa;
    struct sigaction osa;
    stack_t ss;
    stack_t oss;
    sigset_t osigs;
    sigset_t sigs;

	/* block SIGUSR1 */
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGUSR1);
	sigprocmask(SIG_BLOCK, &sigs, &osigs);
	/* add our handler for SIGUSR1 */
    sa.sa_handler = PAL_POSIX_Context_trampoline;
    sigemptyset(&(sa.sa_mask));
    sa.sa_flags = SA_ONSTACK;
    if(0 != sigaction(SIGUSR1, &sa, &osa))
	{
        return;
	}
	/* Set up the context stack -- this assumes the stack grows downwards */
	ss.ss_sp    = self->data.stackLow;
    ss.ss_size  = self->data.stackHigh - self->data.stackLow;
    ss.ss_flags = 0;
    if(sigaltstack(&ss, &oss) < 0)
	{
		return;
	}
	/* Trigger the signal handler being invoked, which will store the context
	 * and return
	 */
    trampoline_sprung = false;
    kill(getpid(), SIGUSR1);
    sigfillset(&sigs);
    sigdelset(&sigs, SIGUSR1);
    while(false == trampoline_sprung)
	{
		sigsuspend(&sigs);
	}
	/* Disentagle the stack from the signal-handling machinery (a multi-stage process) */
	/* Get the current signal stack */
    sigaltstack(NULL, &ss);
	/* Set the SS_DISABLE flag on it */
    ss.ss_flags = SS_DISABLE;
    if (sigaltstack(&ss, NULL) < 0)
	{
        return;
	}
	/* Check that SS_DISABLE has been applied */
	sigaltstack(NULL, &ss);
    if (!(ss.ss_flags & SS_DISABLE))
	{
        return;
	}
	/* If there was previously a non-disabled stack, re-enable it  */
    if (!(oss.ss_flags & SS_DISABLE))
	{
        sigaltstack(&oss, NULL);
	}
	/* restore previous signal handling state */
    sigaction(SIGUSR1, &osa, NULL);
    sigprocmask(SIG_SETMASK, &osigs, NULL);
	/* prepare to re-enter the trampoline, now outside of a signal-handling
	 * context, passing state data via globals
	 */
	trampoline_context = self;
	if(0 == setjmp(VOLATILE_JMPBUF(trampoline_caller)))
	{
		longjmp(VOLATILE_JMPBUF(trampoline_jb), 1);
	}
	/* we are done */
	fprintf(stderr, "PAL::POSIX::Context::setup(): context %p created\n", self);
	return;
}

static void
PAL_POSIX_Context_trampoline(int signo)
{
	UNUSED__(signo);

	if(0 == setjmp(VOLATILE_JMPBUF(trampoline_jb)))
	{
		/* return from a signal-handling context ASAP*/
		trampoline_sprung = true;
		return;
	}
	fprintf(stderr, "PAL::POSIX::Context::trampoline: resumed after setjmp(), bootstrapping context %p\n", trampoline_context);
	PAL_POSIX_Context_bootstrap();
}

static void
PAL_POSIX_Context_bootstrap(void)
{
	volatile PAL_POSIX_Context *ctx;
	volatile jmp_buf caller;

	/* transfer temporary globals to the stack */
	ctx = trampoline_context;
	trampoline_context = NULL;
	memcpy((void *) caller, (void *) trampoline_caller, sizeof(jmp_buf));
	/* save our real state */
	fprintf(stderr, "PAL::POSIX::Context(%p)::bootstrap: saving initial state\n", ctx);
#if 0
	if(false == PAL_POSIX_Context_suspend((IContext *) &(ctx->Context)))
#endif
	if(0 == setjmp(VOLATILE_JMPBUF(ctx->data.jb)))
	{
		fprintf(stderr, "PAL::POSIX::Context(%p)::bootstrap: jumping back to caller\n", ctx);
		longjmp(VOLATILE_JMPBUF(caller), 1);
	}
	fprintf(stderr, "PAL::POSIX::Context(%p)::bootstrap: starting context\n", ctx);
	PAL_POSIX_Context_start((PAL_POSIX_Context *) ctx);
}

static void
PAL_POSIX_Context_start(PAL_POSIX_Context *ctx)
{
	fprintf(stderr, "PAL::POSIX::Context(%p)::start: calling entrypoint (Thread %p)\n", ctx, ctx->data.thread);
	ctx->data.entry(ctx->data.thread);
	abort();
}

/* IObject */

static int
PAL_POSIX_Context_queryInterface(IContext *me, REFUUID iid, void **out)
{
	PAL_POSIX_Context *self = INTF_TO_CLASS(me);

	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			*out = &(self->Object);
			IContext_retain(me);
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(iid, &IID_IContext, sizeof(UUID)))
	{
		if(out)
		{
			*out = &(self->Context);
			IContext_retain(me);
		}
		return E_SUCCESS;
	}
	/* Unsupported interface*/
	return E_NOENT;
}

static int32_t
PAL_POSIX_Context_retain(IContext *me)
{
	PAL_POSIX_Context *self = INTF_TO_CLASS(me);

	/* XXX atomics */
	self->data.refCount++;

	return self->data.refCount;
}

static int32_t
PAL_POSIX_Context_release(IContext *me)
{
	PAL_POSIX_Context *self = INTF_TO_CLASS(me);

	/* XXX atomics */
	self->data.refCount--;
	if(!self->data.refCount)
	{
		PAL_POSIX_Context_destroy(self);
		return 0;
	}
	return self->data.refCount;
}

static bool
PAL_POSIX_Context_swap(IContext *me, IContext *to)
{
	volatile PAL_POSIX_Context *self;
	volatile PAL_POSIX_Context *other;

	self = INTF_TO_CLASS(me);
	other = INTF_TO_CLASS(to);
	fprintf(stderr, "PAL::POSIX::Context::swap(%p, %p)\n", self, other);
	if(me == to)
	{
		return true;
	}
	if(NULL == to)
	{
		fprintf(stderr, "PAL::POSIX::Context::swap(%p): switching to first context\n", self);
		longjmp(VOLATILE_JMPBUF(self->data.jb), 1);
		abort();
	}
	if(0 == setjmp(VOLATILE_JMPBUF(self->data.jb)))
	{
		fprintf(stderr, "PAL::POSIX::Context::swap(%p) - context suspended\n", self);
		longjmp(VOLATILE_JMPBUF(other->data.jb), 1);
		return false;
	}
	fprintf(stderr, "PAL::POSIX::Context::swap(%p) - context restored\n", self);
	return true;
}
