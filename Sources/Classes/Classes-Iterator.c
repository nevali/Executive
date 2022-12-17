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

/** Executive::Classes::Iterator **/

/* This class implements a basic iterator interface to a set of in-memory
 * objects, in particular the Executive's list of registered classes, making
 * them visible in the Object Directory, and so resolveable by name
 */

#undef INTF_TO_CLASS
#define INTF_TO_CLASS(i)               EXEC_COMMON_INTF_TO(i, Executive_Classes_Iterator)

static void Executive_Classes_Iterator_init(Executive_Classes_Iterator *self);
static void Executive_Classes_Iterator_fini(Executive_Classes_Iterator *self);

static STATUS Executive_Classes_Iterator_queryInterface(IObject *me, REFUUID iid, void **out);

static STATUS Executive_Classes_Iterator_next(IIterator *me);
static IObject *Executive_Classes_Iterator_current(IIterator *me);

static struct IIterator_vtable_ Executive_Classes_Iterator_vtable = {
	EXEC_COMMON_VTABLE_IOBJECT(Executive_Classes_Object, IIterator),
	Executive_Classes_Iterator_next,
	Executive_Classes_Iterator_current
};

/* Allocator */

Executive_Classes_Iterator *
Executive_Classes_Iterator_create(void)
{
	Executive_Classes_Iterator *p;

	EXTRACEF(("Executive::Classes::Iterator::create()"));
	p = ExAlloc(sizeof(Executive_Classes_Iterator));
	if(!p)
	{
		return NULL;
	}
	Executive_Classes_Iterator_init(p);
	return p;
}

/* Constructor */

static void
Executive_Classes_Iterator_init(Executive_Classes_Iterator *self)
{
	EXTRACEF(("Executive::Classes::Iterator::init(%p)", self));
	/* Initialise the parent */
	Executive_Classes_Object_init(&(self->parent));
	/* Install the callbacks */
	self->parent.data.queryInterface = Executive_Classes_Iterator_queryInterface;
	self->parent.data.fini = (void *) Executive_Classes_Iterator_fini;
	/* Set up the IIterator interface */
	self->Iterator.lpVtbl = &Executive_Classes_Iterator_vtable;
	self->Iterator.instptr = self;
	ExAssert(self->parent.data.refCount == 1);
}

/* Destructor */

static void
Executive_Classes_Iterator_fini(Executive_Classes_Iterator *self)
{
	EXTRACEF(("Executive::Classes::Iterator::fini(%p)", self));
	if(self->data.fini)
	{
		self->data.fini(self);
	}
}

/* queryInterface */
static STATUS
Executive_Classes_Iterator_queryInterface(IObject *me, REFUUID iid, void **out)
{
	Executive_Classes_Iterator *self = INTF_TO_CLASS(me);

	EXEC_COMMON_SUPPORTS(Iterator);
	EXEC_COMMON_NOTIMPL;
}

/* IIterator */

static STATUS
Executive_Classes_Iterator_next(IIterator *me)
{
	Executive_Classes_Iterator *self = INTF_TO_CLASS(me);

	EXTRACEF(("Executive::Classes::Iterator::next(%p)", self));
	if(self->data.next)
	{
		return self->data.next(self);
	}
	EXDBGF((LOG_DEBUG, "Executive::Classes::Iterator::current(%p): no next callback provided", self));
	return E_NOTIMPL;
}

static IObject *
Executive_Classes_Iterator_current(IIterator *me)
{
	Executive_Classes_Iterator *self = INTF_TO_CLASS(me);

	EXTRACEF(("Executive::Classes::Iterator::current(%p)", self));
	if(self->data.current)
	{
		return self->data.current(self);
	}
	EXDBGF((LOG_DEBUG, "Executive::Classes::Iterator::current(%p): no current callback provided", self));
	return NULL;
}
