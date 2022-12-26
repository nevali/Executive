/* Executive Microkernel
 * Despatch Gateway
 */

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

#include "p_Despatch.h"

static void Executive_Despatch_syscall(ExecutiveDespatch *despatch, Executive_Despatch_Context *context, IThread *currentThread);

/* Executive::despatch()
 *   Despatch Gateway -- invoked in response to a trap, interrupt, exception,
 *   timer, or similar, to invoke the correct handler
 */
void
Executive_despatch(ExecutiveDespatch *despatch)
{
	IThread *currentThread;
	Executive_Despatch_Context *despatchContext;

	ExAssert(NULL != despatch);
	EXTRACEF(("Executive::despatch({ .type = %d })", despatch->type));
	currentThread = NULL;
	ITasker_interrupt(executive.data.tasker, 0, (IObject **) (void **) &despatchContext, &currentThread);
	EXLOGF((LOG_DEBUG7, "despatchContext = %p, currentThread = %p", despatchContext, currentThread));
	switch(despatch->type)
	{
		case EDT_SYSCALL:
			Executive_Despatch_syscall(despatch, despatchContext, currentThread);
			break;
		default:
			ExPanic("unhandled despatch type");
	};
	if(currentThread)
	{
		IThread_release(currentThread);
	}
	ITasker_resume(executive.data.tasker, 0);
}

static void
Executive_Despatch_syscall(ExecutiveDespatch *despatch, Executive_Despatch_Context *context, IThread *currentThread)
{
	void *target;
	ExecutiveDespatchHandler handler;
	
	EXTRACEF(("Executive::Despatch::syscall(%lx, %lx, %lx, %lx, %lx, %lx, %lx, %lx)",
		despatch->syscall.arg[0], despatch->syscall.arg[1],
		despatch->syscall.arg[2], despatch->syscall.arg[3],
		despatch->syscall.arg[4], despatch->syscall.arg[5],
		despatch->syscall.arg[6], despatch->syscall.arg[7]));
	target = NULL;
	handler = NULL;
	despatch->syscall.status = E_NOTIMPL;
	if(0 == despatch->syscall.arg[0])
	{
		/* This call is to the IThread interface on the current thread */
		EXLOGF((LOG_DEBUG7, "Executive::Despatch::syscall(): despatching to current thread"));
		target = currentThread;
		handler = Executive_Despatch_Handlers_IThread;
		if(!currentThread)
		{
			EXLOGF((LOG_DEBUG, "no current thread??"));
			despatch->syscall.status = E_BADOBJ;
			return;
		}
	}
	else
	{
		despatch->syscall.arg[0]--;
		if(despatch->syscall.arg[0] >= context->data.ndescriptors || !context->data.descriptors[despatch->syscall.arg[0]].object)
		{
			EXLOGF((LOG_CONDITION, "%%E-INVAL: descriptor %d is not valid", despatch->syscall.arg[0] + 1));
			despatch->syscall.status = E_INVAL;
			return;
		}
/*		EXLOGF((LOG_DEBUG7, "Executive::Despatch::syscall(): despatching to descriptor %d", despatch->syscall.arg[0] + 1)); */
		target = context->data.descriptors[despatch->syscall.arg[0]].object;
		handler = context->data.descriptors[despatch->syscall.arg[0]].handler;
	}
	if(!target)
	{
		despatch->syscall.status = E_BADOBJ;
		EXLOGF((LOG_CONDITION, "%%E-BAD-OBJ: Object descriptor %d is not valid", despatch->syscall.arg[0] + 1));
		return;
	}
	/* if the method ID is 0, 1, or 2, this can be handled by the IObject
	 * handler without any further lookups
	 */
	if(despatch->syscall.arg[1] < 3)
	{
		handler = Executive_Despatch_Handlers_IObject;
	}
	if(!handler)
	{
		/* for now we don't know how to deal with any other objects */
		despatch->syscall.status = E_NOT_IMPL;
		EXLOGF((LOG_CONDITION, "%%E-NOT-IMPL: unable to call method %d, sorry - no handler available", despatch->syscall.arg[1]));
		return;
	}
	handler(despatch, target, context, currentThread);
/* 	EXTRACEF(("Executive::Despatch::syscall(): status = %d", despatch->syscall.status)); */
}
