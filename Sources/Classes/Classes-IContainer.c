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

/* The Classes object represents the list of registered classes
 *
 * It's a singleton, and so its interface pointers can be retrieved directly
 * via Executive::metaClass()
 *
 * It implements the IContainer interface, so that it can be traversed
 *
 * At startup, a directory entry for the Classes object is created at
 * /System/Classes, allowing class name resolution to occur
 */

static STATUS Executive_Classes_queryInterface(IContainer *me, REFUUID iid, void **out);
static REFCOUNT Executive_Classes_retain(IContainer *me);
static REFCOUNT Executive_Classes_release(IContainer *me);
static STATUS Executive_Classes_resolve(IContainer *me, const char *name, IDirectoryEntry **entry);
static IIterator *Executive_Classes_iterator(IContainer *me);

static struct IContainer_vtable_ Executive_Classes_IContainer_vtable = {
	Executive_Classes_queryInterface,
	Executive_Classes_retain,
	Executive_Classes_release,
	Executive_Classes_resolve,
	Executive_Classes_iterator
};

IContainer Executive_Classes_IContainer = { &Executive_Classes_IContainer_vtable, NULL };

static struct {
    const char *name;
    REFUUID clsid;
} Executive_Classes_roots[] = {
    { "Executive", &CLSID_Executive_Container },
    { "PAL", &CLSID_Executive_Container },
    { NULL, NULL }
};
static size_t Executive_Classes_rootCount = 2;

static STATUS Executive_Classes_rootIterator_next(Executive_Classes_Iterator *self);
static IObject *Executive_Classes_rootIterator_current(Executive_Classes_Iterator *self);
static IIterator *Executive_Classes_subDirectoryEntry_iterator(Executive_Classes_DirectoryEntry *self);
static void Executive_Classes_subIterator_fini(Executive_Classes_Iterator *self);
static STATUS Executive_Classes_subIterator_next(Executive_Classes_Iterator *self);
static IObject *Executive_Classes_subIterator_current(Executive_Classes_Iterator *self);

/* Executive::Classes */

static STATUS
Executive_Classes_queryInterface(IContainer *me, REFUUID iid, void **out)
{
	UNUSED__(me);
	if(out)
	{
		*out = NULL;
	}
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_IContainer))
	{
		if(out)
		{
			*out = me;
		}
		return E_SUCCESS;
	}
	return E_NOTIMPL;
}

static REFCOUNT
Executive_Classes_retain(IContainer *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT
Executive_Classes_release(IContainer *me)
{
	UNUSED__(me);

	return 1;
}

STATUS
Executive_Classes_resolve(IContainer *me, const char *name, IDirectoryEntry **entry)
{
	UNUSED__(me);

	if(entry)
	{
		*entry = NULL;
	}
	UNUSED__(name);
	UNUSED__(entry);
	/* if name begins with "classid:", the remainder should be parsed as a UUID, and
	 * a directory entry synthesised pointing at the corresponding metaclass's
	 * IObject interface (if it exists)
	 *
	 * this means that querying for a metaclass interface on the target of any link to
	 * /System/Classes/classid:... is directly equivalent to querying for that same
	 * interface via ExMetaClass() - the only difference is the path resolution
	 *
	 * if that class supports one of the standard constructor metaclass
	 * interfaces, then the standard namespace implementation can construct a
	 * new instance of that class on demand, i.e., wrapping "create an object
	 * named X of class Y" into a straightforward operation, where both X and Y
	 * are (in effect) filesystem paths
	 */
	return E_NOTIMPL;
}

IIterator *
Executive_Classes_iterator(IContainer *me)
{
	Executive_Classes_Iterator *iterator;

	UNUSED__(me);

	EXTRACEF(("Executive::Classes::iterator()"));
	/* Create an iterator that will be used to iterate through the available
	 * namespaces (i.e., "Executive", "PAL")
	 */
	if(NULL == (iterator = Executive_Classes_Iterator_create()))
	{
		ExLogCondition(E_NOMEM, "Executive::Classes::Iterator::create()");
		return NULL;
	}
	iterator->data.next = Executive_Classes_rootIterator_next;
	iterator->data.current = Executive_Classes_rootIterator_current;
	return &(iterator->Iterator);
}

static STATUS
Executive_Classes_rootIterator_next(Executive_Classes_Iterator *self)
{
	EXTRACEF(("Executive::Classes::rootIterator_next(index = %u)", self->data.index));
	if(self->data.index >= Executive_Classes_rootCount)
	{
		return E_EOF;
	}
	self->data.index++;
	return E_SUCCESS;
}

/* Create a directory entry on the fly for the current position in the roots list */
static IObject *
Executive_Classes_rootIterator_current(Executive_Classes_Iterator *self)
{
	Executive_Classes_DirectoryEntry *entry;

	EXTRACEF(("Executive::Classes::rootIterator_current(index = %u)", self->data.index));
	if(self->data.index >= Executive_Classes_rootCount)
	{
		return NULL;
	}
	if(NULL == (entry = Executive_Classes_DirectoryEntry_create(Executive_Classes_roots[self->data.index].name,
		Executive_Classes_roots[self->data.index].clsid, DEF_CONTAINER)))
	{
		return NULL;
	}
	entry->data.iterator = Executive_Classes_subDirectoryEntry_iterator;
	return &(entry->Object);
}

static IIterator *
Executive_Classes_subDirectoryEntry_iterator(Executive_Classes_DirectoryEntry *self)
{
	Executive_Classes_Iterator *iterator;

	EXTRACEF(("Executive::Classes::subDirectoryEntry_iterator(%p)", self));

	if(NULL == (iterator = Executive_Classes_Iterator_create()))
	{
		ExLogCondition(E_NOMEM, "Executive::Classes::Iterator::create()");
		return NULL;
	}
	/* Ensure this directory entry exists for at least as long as the iterator */
	self->data.refCount++;
	iterator->data.userData = self;
	iterator->data.fini = Executive_Classes_subIterator_fini;
	iterator->data.next = Executive_Classes_subIterator_next;
	iterator->data.current = Executive_Classes_subIterator_current;
	return &(iterator->Iterator);

	return NULL;
}

static void
Executive_Classes_subIterator_fini(Executive_Classes_Iterator *self)
{
	EXTRACEF(("Executive::Classes::subIterator_fini(%p)", self));
	IDirectoryEntry_release((&((Executive_Classes_DirectoryEntry *) self->data.userData)->DirectoryEntry));
}

static STATUS
Executive_Classes_subIterator_next(Executive_Classes_Iterator *self)
{
	Executive_Classes_DirectoryEntry *parentEntry = (Executive_Classes_DirectoryEntry *) (self->data.userData);
	size_t l;

	EXTRACEF(("Executive::Classes::subIterator_next(%p)", self));
	ExAssert(NULL != parentEntry);
	EXDBGF((LOG_DEBUG7, "subIterator: name='%s'", parentEntry->data.name));

	if(!metaClass_entries[self->data.index].className)
	{
		return E_EOF;
	}
	/* skip over entries which don't match our parent entry's name */
	l = ExStrLen(parentEntry->data.name);
	for(self->data.index++; metaClass_entries[self->data.index].className; self->data.index++)
	{
		if(ExStrLEqual(metaClass_entries[self->data.index].className, parentEntry->data.name, l) && 
			metaClass_entries[self->data.index].className[l] == ':' &&
			metaClass_entries[self->data.index].className[l + 1] == ':')
		{
			return E_SUCCESS;
		}
	}
	/* we reached the end with no matches */
	return E_EOF;
}

static IObject *
Executive_Classes_subIterator_current(Executive_Classes_Iterator *self)
{
	Executive_Classes_DirectoryEntry *parentEntry = (Executive_Classes_DirectoryEntry *) (self->data.userData);
	size_t l;

	EXTRACEF(("Executive::Classes::subIterator_current(%p)", self));
	
	if(!metaClass_entries[self->data.index].className)
	{
		return NULL;
	}
	for(l = ExStrLen(parentEntry->data.name); metaClass_entries[self->data.index].className; self->data.index++)
	{
		EXDBGF((LOG_DEBUG7, "checking if '%s' matches", metaClass_entries[self->data.index].className));
		if(ExStrLEqual(metaClass_entries[self->data.index].className, parentEntry->data.name, l) && 
			metaClass_entries[self->data.index].className[l] == ':' &&
			metaClass_entries[self->data.index].className[l + 1] == ':')
		{
			Executive_Classes_DirectoryEntry *entry;
			char buffer[sizeof(UUIDBUF) + 16];

			/* Create a directory entry for this class on the fly */
			EXDBGF((LOG_DEBUG7, "found match!"));
			entry = Executive_Classes_DirectoryEntry_create(metaClass_entries[self->data.index].className + l + 2, &CLSID_Executive_Link, DEF_LINK);
			/* XXX this is extremely fragile */
			ExUuidStr(metaClass_entries[self->data.index].clsid, buffer + 6);
			buffer[0] = 'c';
			buffer[1] = 'l';
			buffer[2] = 'a';
			buffer[3] = 's';
			buffer[4] = 's';
			buffer[5] = 'i';
			buffer[6] = 'd';
			buffer[7] = ':';
			buffer[8 + 36] = 0;
			entry->data.target = ExStrDup(buffer);
			return &(entry->Object);
		}
	}
	EXDBGF((LOG_DEBUG7, "no more matching entries for this iterator"));
	return NULL;
}
