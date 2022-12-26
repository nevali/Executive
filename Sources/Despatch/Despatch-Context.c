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

struct Executive_Despatch_Context_Handler
{
	REFUUID iid;
	ExecutiveDespatchHandler handler;
};

#define DECLARE_HANDLER(name) \
	{ &IID_ ## name, Executive_Despatch_Handlers_ ## name }

static struct Executive_Despatch_Context_Handler handlers[] = {

	/* These handlers also need to be declared via
	 *   EXTERN_C EXEC_DESPATCH_HANDLER(name); 
	 * in p_Despatch.h
	 */
	DECLARE_HANDLER(IObject),
	DECLARE_HANDLER(IThread),
	DECLARE_HANDLER(ITask),
	DECLARE_HANDLER(INamespace),
	DECLARE_HANDLER(IAddressSpace),
	DECLARE_HANDLER(IRegion),
	DECLARE_HANDLER(IWriteChannel),
	DECLARE_HANDLER(IIterator),
	DECLARE_HANDLER(IContainer),
	DECLARE_HANDLER(IDirectoryEntry),

	{ NULL, NULL }
};

static ExecutiveDespatchHandler Executive_Despatch_Context_handler(Executive_Despatch_Context *context, REFUUID iid);

/*INTERNAL*/

/* Obtain a descriptor from a despatch context for the supplied interface 
 *
 * !!! we assume that the object has been retained on the descriptor's behalf
 * !!! if the descriptor already exists, we release the additional reference
 */
int
Executive_Despatch_Context_descriptor(Executive_Despatch_Context *context, void *object, REFUUID iid)
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
			EXLOGF((LOG_DEBUG6, "Executive::Despatch::descriptor(): object already exists at slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
			return n + 1;
		}
	}
	/* there not being a handler is not necessarily fatal - it's not a problem
	 * until a non-IObject method is invoked, which may never happen
	 */
	handler = Executive_Despatch_Context_handler(context, iid);
	/* is there a free slot? */
	for(n = 0; (size_t) n < context->data.ndescriptors; n++)
	{
		if(NULL == context->data.descriptors[n].object)
		{
			context->data.descriptors[n].object = object;
			context->data.descriptors[n].handler = handler;
			EXLOGF((LOG_DEBUG6, "Executive::Despatch::descriptor(): using empty slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
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
	EXLOGF((LOG_DEBUG6, "Executive::Despatch::descriptor(): created new slot #%d for iid:" UUID_PRINTF_FORMAT, n + 1, UUID_PRINTF_ARGS(iid)));
	return n + 1;
}

static ExecutiveDespatchHandler
Executive_Despatch_Context_handler(Executive_Despatch_Context *context, REFUUID iid)
{
	size_t c;

	UNUSED__(context);

	for(c = 0; handlers[c].iid; c++)
	{
		if(RtUuidEqual(iid, handlers[c].iid))
		{
			return handlers[c].handler;
		}
	}
	EXLOGF((LOG_DEBUG, "Executive::Despatch::handler(): no handler available for iid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(iid)));
	return NULL;
}
