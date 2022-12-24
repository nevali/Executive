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

#include "p_PAL.h"

using namespace PAL::Simulator;

#define VOLATILE_JMPBUF(x) (*((jmp_buf *) &(x)))

static volatile sig_atomic_t trampoline_sprung;
static volatile jmp_buf trampoline_caller;
static volatile jmp_buf trampoline_jb;
static volatile Context *trampoline_context;

static UUID IID_IContextPrivate = UUID_INIT__(0xe2, 0x10, 0xcb, 0x36, 0x12, 0xf7, 0x47, 0xc8, 0xa5, 0x99, 0x22, 0xda, 0x5d, 0xa0, 0xed, 0xb0);

Context::Context(AddressSpace *as):
	refCount_(1),
	addressSpace(as)
{
}

Context::~Context()
{
}

/* PRIVATE */
void
Context::setup(void)
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
    sa.sa_handler = Context::trampoline;
    sigemptyset(&(sa.sa_mask));
    sa.sa_flags = SA_ONSTACK;
    if(0 != sigaction(SIGUSR1, &sa, &osa))
	{
        return;
	}
	/* Set up the context stack -- this assumes the stack grows downwards */
    ss.ss_flags = 0;
	ss.ss_sp = stackBase;
    ss.ss_size = stackSize;
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
	trampoline_context = this;
	if(0 == setjmp(VOLATILE_JMPBUF(trampoline_caller)))
	{
		longjmp(VOLATILE_JMPBUF(trampoline_jb), 1);
	}
	/* we are done */
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context::setup(): context %p created", this);
	return;
}

void
Context::trampoline(int signo)
{
	UNUSED__(signo);

	if(0 == setjmp(VOLATILE_JMPBUF(trampoline_jb)))
	{
		/* return from a signal-handling context ASAP*/
		trampoline_sprung = true;
		return;
	}
	Platform::tracef("PAL::Simulator::Context::trampoline: resumed after setjmp(), bootstrapping context %p", trampoline_context);
	Context::bootstrap();
}

void
Context::bootstrap(void)
{
	volatile Context *ctx;
	volatile jmp_buf caller;

	/* transfer temporary globals to the stack */
	ctx = trampoline_context;
	trampoline_context = NULL;
	memcpy((void *) caller, (void *) trampoline_caller, sizeof(jmp_buf));
	/* save our real state */
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context(%p)::bootstrap: saving initial state", ctx);
	if(0 == setjmp(VOLATILE_JMPBUF(ctx->jb)))
	{
		Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context(%p)::bootstrap: jumping back to caller", ctx);
		longjmp(VOLATILE_JMPBUF(caller), 1);
	}
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context(%p)::bootstrap: starting context", ctx);
	((Context *)ctx)->_start();
}

void
Context::_start()
{
	Platform::tracef("PAL::Simulator::Context(%p)::start: calling entrypoint (Thread %p)", this, thread);
	entry(thread);
	abort();
}

/* IObject */

STATUS
Context::queryInterface(REFUUID iid, void **out)
{
	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(&iid, &IID_IContextPrivate, sizeof(UUID)))
	{
		if(out)
		{
			IContextPrivate *me = static_cast<IContextPrivate *>(this);
			/* XXX NOTE: NO RETAIN -- PRIVATE USE ONLY */
			*out = me;
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(&iid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			IObject *me = static_cast<IObject *>(static_cast<IContextPrivate *>(this));
			me->retain();
			*out = me;
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(&iid, &IID_IContext, sizeof(UUID)))
	{
		if(out)
		{
			IContext *me = static_cast<IContext *>(this);
			me->retain();
			*out = me;
		}
		return E_SUCCESS;
	}
	/* Unsupported interface*/
	return E_NOENT;
}

REFCOUNT
Context::retain(void)
{
	/* XXX atomics */
	refCount_++;

	return refCount_;
}

REFCOUNT
Context::release(void)
{
	refCount_--;
	if(!refCount_)
	{
		delete this;
		return 0;
	}
	return refCount_;
}

bool
Context::swap(IContext *to)
{
	IContextPrivate *priv;
	volatile Context *self;
	volatile Context *other;

	self = this;
	if(NULL == to)
	{
		Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context::swap(%p): switching to first context", self);
		longjmp(VOLATILE_JMPBUF(self->jb), 1);
		abort();
	}
	/* XXX this is very bad */
	if(E_SUCCESS != to->queryInterface(IID_IContextPrivate, (void **) &priv))
	{
		Platform::logf(LOG_DEBUG7, "failed to obtain IContextPrivate!!");
		return true;
	}
	other = priv->self();
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context::swap(%p, %p)\n", self, other);
	if(self == other)
	{
		return true;
	}
	if(0 == setjmp(VOLATILE_JMPBUF(self->jb)))
	{
		Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context::swap(%p) - context suspended\n", self);
		longjmp(VOLATILE_JMPBUF(other->jb), 1);
		return false;
	}
	Platform::logf(LOG_DEBUG7, "PAL::Simulator::Context::swap(%p) - context restored\n", self);
	return true;
}
