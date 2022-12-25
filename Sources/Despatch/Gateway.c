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

/* MObject metaclass interface for Executive::Despatch */
EXEC_COMMON_STATIC_IOBJECT(Executive_Despatch_MObject);
static STATUS Executive_Despatch_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out);

static struct MObject_vtable_ Executive_Despatch_MObject_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Despatch_MObject, MObject),
	Executive_Despatch_MObject_create
};
/*EXTERN_C*/ MObject Executive_Despatch_MObject = { &Executive_Despatch_MObject_vtable, NULL };

/* IObject for Executive::Despatch instances */
EXEC_COMMON_STATIC_IOBJECT(Executive_Despatch);
static struct IObject_vtable_ Executive_Despatch_IObject_vtable = {
	Executive_Despatch_queryInterface,
	Executive_Despatch_retain,
	Executive_Despatch_release
};

static void Executive_Despatch_syscall(ExecutiveDespatch *despatch, Executive_Despatch *context, IThread *currentThread);

/* +IObject */
static STATUS
Executive_Despatch_MObject_queryInterface(IObject *me, REFUUID iid, void **out)
{
	if(RtUuidEqual(iid, &IID_IObject) || RtUuidEqual(iid, &IID_MObject))
	{
		if(out)
		{
			*out = me;
		}
		return E_SUCCESS;
	}
	if(out)
	{
		*out = NULL;
	}
	return E_NOENT;
}

static REFCOUNT
Executive_Despatch_MObject_retain(IObject *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_Despatch_MObject_release(IObject *me)
{
	UNUSED__(me);

	return 1;
}

/* Create a new despatch context and return it */
static STATUS
Executive_Despatch_MObject_create(MObject *me, IAllocator *allocator, REFUUID iid, void **out)
{
	Executive_Despatch *despatch;

	UNUSED__(me);
	
	ExAssert(out != NULL);
	*out = NULL;
	if(!RtUuidEqual(iid, &IID_IObject))
	{
		return E_NOTIMPL;
	}
	despatch = IAllocator_alloc(allocator, sizeof(Executive_Despatch));
	if(!despatch)
	{
		return E_NOMEM;
	}
	despatch->Object.lpVtbl = &Executive_Despatch_IObject_vtable;
	despatch->data.refCount = 1;
	despatch->data.allocator = allocator;
	*out = despatch;
	return E_SUCCESS;
}

#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Despatch)

/* IObject */
static STATUS
Executive_Despatch_queryInterface(IObject *me, REFUUID iid, void **out)
{
	if(RtUuidEqual(iid, &IID_IObject) || RtUuidEqual(iid, &IID_MObject))
	{
		if(out)
		{
			*out = me;
		}
		return E_SUCCESS;
	}
	if(out)
	{
		*out = NULL;
	}
	return E_NOENT;
}

static REFCOUNT
Executive_Despatch_retain(IObject *me)
{
	EXEC_COMMON_RETAIN(Executive_Despatch);
}

static REFCOUNT
Executive_Despatch_release(IObject *me)
{
	IAllocator *alloc;

	EXEC_COMMON_RELEASE(Executive_Despatch, {
		alloc = self->data.allocator;
		IAllocator_free(alloc, self);
		IAllocator_release(alloc);
	});
}


void
Executive_despatch(ExecutiveDespatch *despatch)
{
	IThread *currentThread;
	Executive_Despatch *despatchContext;

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
Executive_Despatch_syscall(ExecutiveDespatch *despatch, Executive_Despatch *context, IThread *currentThread)
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
		EXLOGF((LOG_DEBUG, "Executive::Despatch::syscall(): despatching to current thread"));
		target = currentThread;
		handler = Executive_Despatch_Handlers_IThread;
		if(!currentThread)
		{
			EXLOGF((LOG_DEBUG, "no current thread?"));
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
		EXLOGF((LOG_DEBUG, "Executive::Despatch::syscall(): despatching to descriptor %d", despatch->syscall.arg[0] + 1));
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
		EXLOGF((LOG_CONDITION, "%%E-NOT-IMPL: unable to call method %d, sorry", despatch->syscall.arg[1]));
		return;
	}
	handler(despatch, target, context, currentThread);
	EXTRACEF(("status = %d", despatch->syscall.status));
}

ExecutiveDespatchHandler
Executive_Despatch_handler(Executive_Despatch *context, REFUUID iid)
{
	UNUSED__(context);

	if(RtUuidEqual(iid, &IID_IObject))
	{
		return Executive_Despatch_Handlers_IObject;
	}
	if(RtUuidEqual(iid, &IID_IThread))
	{
		return Executive_Despatch_Handlers_IThread;
	}
	if(RtUuidEqual(iid, &IID_ITask))
	{
		return Executive_Despatch_Handlers_ITask;
	}
	if(RtUuidEqual(iid, &IID_INamespace))
	{
		return Executive_Despatch_Handlers_INamespace;
	}
	if(RtUuidEqual(iid, &IID_IAddressSpace))
	{
		return Executive_Despatch_Handlers_IAddressSpace;
	}
	if(RtUuidEqual(iid, &IID_IRegion))
	{
		return Executive_Despatch_Handlers_IRegion;
	}
	return NULL;
}

int
Executive_Despatch_descriptor(Executive_Despatch *context, void *object, REFUUID iid)
{
	int n;
	ExecutiveDespatchHandler handler;
	Executive_Despatch_Descriptor *p;

	ExAssert(NULL != context);
	ExAssert(NULL != object);
	ExAssert(NULL != iid);

	/* does the object already exist in the context? */
	for(n = 0; (size_t) n < context->data.ndescriptors; n++)
	{
		if(context->data.descriptors[n].object == object)
		{
			/* release the reference we've been given, as we only
			 * keep one copy per task
			 */
			IObject_release(((IObject *) object));
			EXLOGF((LOG_DEBUG, "Executive::Despatch::descriptor(): object already exists at slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
			return n + 1;
		}
	}
	handler = Executive_Despatch_handler(context, iid);
	/* is there a free slot? */
	for(n = 0; (size_t) n < context->data.ndescriptors; n++)
	{
		if(NULL == context->data.descriptors[n].object)
		{
			context->data.descriptors[n].object = object;
			context->data.descriptors[n].handler = handler;
			EXLOGF((LOG_DEBUG, "Executive::Despatch::descriptor(): using empty slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
			return n + 1;
		}
	}
	p = (Executive_Despatch_Descriptor *) RtMemReAlloc(context->data.descriptors, (context->data.ndescriptors + 8) * sizeof(Executive_Despatch_Descriptor));
	if(!p)
	{
		return E_NOMEM;
	}
	RtMemSet((void *) &(p[context->data.ndescriptors]), 0, 8 * sizeof(Executive_Despatch_Descriptor));
	context->data.descriptors = p;
	context->data.ndescriptors += 8;
	p[n].object = object;
	p[n].handler = handler;
	EXLOGF((LOG_DEBUG, "Executive::Despatch::descriptor(): created new slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
	return n + 1;

}