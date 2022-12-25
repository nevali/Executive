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

#ifndef P_DESPATCH_H_
# define P_DESPATCH_H_

# include <Executive/MObject.h>

# include <Executive/Internal/Runtime.h>
# include <Executive/Internal/Classes.h>
# include <Executive/Internal/Executive.h>
# include <Executive/Internal/Despatch.h>

#define EXEC_DESPATCH_HANDLER(name) \
	void Executive_Despatch_Handlers_ ## name (ExecutiveDespatch *despatch, void *target, Executive_Despatch *context, IThread *currentThread)

#define EXEC_DESPATCH_COPY_FROM_USER(src, dest, nbytes) \
	if(!src) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
#define EXEC_DESPATCH_COPY_TO_USER(dest, src, nbytes) \
	if(!dest) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
#define EXEC_DESPATCH_DESCRIPTOR(ret, ctx, obj, iid) \
	if((ret)) \
	{ \
		*((int *)(void *)(ret)) = Executive_Despatch_descriptor(ctx, obj, iid); \
	} \
	else \
	{ \
		IObject_release(((IObject *)(void *)(obj))); \
	}
#define EXEC_DESPATCH_OBJECT(object_, context_, descriptor_, type_) \
	if((descriptor_) > (context_)->data.ndescriptors) \
	{ \
		despatch->syscall.status = E_BADOBJ; \
		return; \
	} \
	(object_) = (type_ *) ((context_)->data.descriptors[(descriptor_) - 1].object);

typedef union Executive_Despatch Executive_Despatch;
typedef struct Executive_Despatch_Descriptor Executive_Despatch_Descriptor;
typedef void (*ExecutiveDespatchHandler)(ExecutiveDespatch *despatch, void *target, Executive_Despatch *context, IThread *currentThread);

struct Executive_Despatch_Descriptor
{
	IObject *object;
	ExecutiveDespatchHandler handler;
};

union Executive_Despatch
{
	IObject Object;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		IAllocator *allocator;
		Executive_Despatch_Descriptor *descriptors;
		size_t ndescriptors;
	} data;
};

EXTERN_C EXEC_DESPATCH_HANDLER(IObject);
EXTERN_C EXEC_DESPATCH_HANDLER(IThread);
EXTERN_C EXEC_DESPATCH_HANDLER(ITask);
EXTERN_C EXEC_DESPATCH_HANDLER(IAddressSpace);
EXTERN_C EXEC_DESPATCH_HANDLER(INamespace);
EXTERN_C EXEC_DESPATCH_HANDLER(IRegion);

EXTERN_C int Executive_Despatch_descriptor(Executive_Despatch *context, void *object, REFUUID iid);

#endif /*!P_DESPATCH_H_*/
