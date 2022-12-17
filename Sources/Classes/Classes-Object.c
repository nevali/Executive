/* Executive Microkernel
 * Class and metaclass handling
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

#include "p_Classes.h"

/** Executive::Classes::Object **/

/* This class implements a basic reference-counted object with no special
 * capabilities except for a destructor callback
 *
 * Descendents should place an Executive_Classes_Object structure at the start
 * of their instance structure, and arrange for Executive_Classes_Object to be
 * called at the correct time to perform initialisation. They should also
 * then set object->data.fini to their own destructor
 */

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Classes_Object)

EXEC_COMMON_DECL_IOBJECT(Executive_Classes_Object);
static void Executive_Classes_Object_fini(Executive_Classes_Object *self);

static struct IObject_vtable_ Executive_Classes_Object_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Classes_Object, IObject)
};

void
Executive_Classes_Object_init(Executive_Classes_Object *self)
{
	EXTRACEF(("Executive::Classes::Object::init(%p)", self));
	
	self->Object.lpVtbl = &Executive_Classes_Object_vtable;
	self->Object.instptr = self;
	self->data.refCount = 1;
	self->data.fini = NULL;
	self->data.queryInterface = NULL;
}

static void
Executive_Classes_Object_fini(Executive_Classes_Object *self)
{
	UNUSED__(self);

	EXTRACEF(("Executive::Classes::Object::fini(%p)", self));
}

STATUS
Executive_Classes_Object_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_Classes_Object *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Object);
	if(self->data.queryInterface)
	{
		return self->data.queryInterface(me, iid, out);
	}
	EXEC_COMMON_NOTIMPL;
}

REFCOUNT
Executive_Classes_Object_retain(IObject *me)
{
	EXTRACEF(("Executive::Classes::Object::retain(refCount = %u)", INTF_TO_CLASS(me)->data.refCount));
	EXEC_COMMON_RETAIN(Executive_Classes_Object);
}

REFCOUNT
Executive_Classes_Object_release(IObject *me)
{
	ExAssert(INTF_TO_CLASS(me)->data.refCount > 0);
	EXTRACEF(("Executive::Classes::Object::release(refCount = %u)", INTF_TO_CLASS(me)->data.refCount));
	EXEC_COMMON_RELEASE(Executive_Classes_Object, {
		EXDBGF((LOG_DEBUG7, "Executive::Classes::Object::release(): destroying %p", me));
		if(self->data.fini)
		{
			self->data.fini(self);
		}
		Executive_Classes_Object_fini(self);
	});
}

