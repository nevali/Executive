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
# include <Executive/IWriteChannel.h>
# include <Executive/ILink.h>

#define EXEC_DESPATCH_HANDLER(name) \
	void Executive_Despatch_Handlers_ ## name (ExecutiveDespatch *despatch, void *object, Executive_Despatch_Context *context, IThread *currentThread)

#define EXEC_DESPATCH_BEGIN(name) \
	name *target = (name *) object; \
	int method = despatch->syscall.arg[1]; \
	UNUSED__(despatch); \
	UNUSED__(context); \
	UNUSED__(currentThread); \
	UNUSED__(target); \
	UNUSED__(method); \
	EXTRACEF(("Executive::Despatch::Handlers::" #name "(%p, %04x, %lx, %lx, %lx, %lx, %lx, %lx)", \
		object, despatch->syscall.arg[1], \
		despatch->syscall.arg[2], despatch->syscall.arg[3], \
		despatch->syscall.arg[4], despatch->syscall.arg[5], \
		despatch->syscall.arg[6], despatch->syscall.arg[7])); \
	switch(method)

#define EXEC_DESPATCH_END(name) \
	ExPanic("unsupported call to Executive::Despatch::Handlers::" #name);

#define EXEC_DESPATCH_HANDLE(name, method) \
	case name ## _ID_ ## method: \
		EXTRACEF(("Executive::Despatch::Handlers::" #name "(%p)::" #method "(%lx, %lx, %lx, %lx, %lx, %lx)", \
		object, \
		despatch->syscall.arg[2], despatch->syscall.arg[3], \
		despatch->syscall.arg[4], despatch->syscall.arg[5], \
		despatch->syscall.arg[6], despatch->syscall.arg[7]));

/* Copy nbytes from userspace src to kernelspace dest */
#define EXEC_DESPATCH_COPY_FROM_USER(src, dest, nbytes) \
	if(!src) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
/* Copy nybtes from kernelspace src to userspace dest */
#define EXEC_DESPATCH_COPY_TO_USER(dest, src, nbytes) \
	if(!dest) \
	{ \
		/* Trigger an exception */ \
		despatch->syscall.status = E_INVAL; \
		return; \
	} \
	ExMemCopy((void *) (dest), (void *) (src), (nbytes))
/* Map userspace region from src + nybtes corresponding to an [out] parameter to pointer ptr */
# define EXEC_DESPATCH_XFER_OUT_FROM_USER(src, ptr, nbytes) \
	ptr = (void *) (src);
/* Undo previous buffer mapping */
# define EXEC_DESPATCH_XFER_OUT_TO_USER(src, ptr, nbytes)

/* create a descriptor for interface type iid provided by obj and store the
 * result in 'ret', which is assumed to be castable to an int * pointer into
 * userspace (just call Executive_Despatch_Context_descriptor if you want the
 * descriptor on its own)
 */
#define EXEC_DESPATCH_DESCRIPTOR(ret, ctx, obj, iid) \
	if((ret)) \
	{ \
		*((int *)(void *)(ret)) = Executive_Despatch_Context_descriptor(ctx, obj, iid); \
	} \
	else \
	{ \
		IObject_release(((IObject *)(void *)(obj))); \
	}
/* locate the object identified by the descriptor of interface type IType,
 * and if it can't be found, fail with an error
 */
#define EXEC_DESPATCH_OBJECT(object_, context_, descriptor_, type_) \
	if((descriptor_) > (context_)->data.ndescriptors) \
	{ \
		despatch->syscall.status = E_BADOBJ; \
		return; \
	} \
	if((descriptor_) = 0) \
	{ \
		/* not currently valid, only "real" descriptors */ \
		despatch->syscall.status = E_BADOBJ; \
		return; \
	} \
	(object_) = (type_ *) ((context_)->data.descriptors[(descriptor_) - 1].object);

typedef union Executive_Despatch_Context Executive_Despatch_Context;
typedef struct Executive_Despatch_Descriptor Executive_Despatch_Descriptor;
typedef void (*ExecutiveDespatchHandler)(ExecutiveDespatch *despatch, void *target, Executive_Despatch_Context *context, IThread *currentThread);

struct Executive_Despatch_Descriptor
{
	IObject *object;
	ExecutiveDespatchHandler handler;
};

union Executive_Despatch_Context
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
EXTERN_C EXEC_DESPATCH_HANDLER(IContainer);
EXTERN_C EXEC_DESPATCH_HANDLER(INamespace);
EXTERN_C EXEC_DESPATCH_HANDLER(IRegion);
EXTERN_C EXEC_DESPATCH_HANDLER(IWriteChannel);
EXTERN_C EXEC_DESPATCH_HANDLER(IIterator);
EXTERN_C EXEC_DESPATCH_HANDLER(IDirectoryEntry);
EXTERN_C EXEC_DESPATCH_HANDLER(ILink);

EXTERN_C int Executive_Despatch_Context_descriptor(Executive_Despatch_Context *context, void *object, REFUUID iid);

EXTERN_C struct IObject_vtable_ Executive_Despatch_Context_IObject_vtable;

#endif /*!P_DESPATCH_H_*/
