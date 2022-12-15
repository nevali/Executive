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

#include "p_Executive.h"

typedef STATUS (*MetaClassCallback)(REFUUID clsid, REFUUID iid, void **out);

struct MetaClassEntry
{
	const char *className;
	REFUUID clsid;
	const char *displayName;
	MetaClassCallback fn;
	MFactory *factory;
};

static STATUS Executive_MFactory_queryInterface(MFactory *me, REFUUID iid, void **out);
static REFCOUNT Executive_MFactory_retain(MFactory *me);
static REFCOUNT Executive_MFactory_release(MFactory *me);
static STATUS Executive_MFactory_lock(MFactory *me, bool dolock);

extern STATUS Executive_Allocator_MFactory_createInstance(MFactory *me, IObject *outer, REFUUID iid, void **out);

static struct MFactory_vtable_ Executive_Allocator_MFactory_vtable = {
	Executive_MFactory_queryInterface,
	Executive_MFactory_retain,
	Executive_MFactory_release,
	Executive_Allocator_MFactory_createInstance,
	Executive_MFactory_lock
};

static struct MFactory Executive_Allocator_MFactory = { &Executive_Allocator_MFactory_vtable, NULL };

static struct MetaClassEntry metaClass_entries[] = {
	{ "PAL::Platform", &CLSID_PAL_Platform, "Platform", NULL, NULL },
	{ "PAL::PlatformDiagnostics", &CLSID_PAL_PlatformDiagnostics, "Platform Diagnostics", NULL, NULL },
	{ "PAL::BootEnvironment", &CLSID_PAL_BootEnvironment, "Boot Environment", NULL, NULL },
	{ "Executive::Container", &CLSID_Executive_Container, "Container", Executive_Directory_metaClass, NULL },
	{ "Executive::Link", &CLSID_Executive_Link, "Link", NULL, NULL },
	{ "Executive::Allocator", &CLSID_Executive_Allocator, "Memory Allocator", NULL, &Executive_Allocator_MFactory },
	{ "Executive::Root", &CLSID_Executive_Root, "Object Directory", Executive_Directory_metaClass, NULL },
	{ "Executive::System", &CLSID_Executive_System, "System Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Local", &CLSID_Executive_Local, "Local Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Cluster", &CLSID_Executive_Cluster, "Cluster Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Network", &CLSID_Executive_Network, "Network Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Node", &CLSID_Executive_Node, "Node", NULL, NULL },
	{ "Executive::Tasker", &CLSID_Executive_Tasker, "Tasker", NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL }
};

/* create an instance using MObject or MFactory */
STATUS
Executive_createObject(REFUUID clsid, REFUUID iid, void **out)
{
	STATUS status;
	MObject *constructor;
	MFactory *factory;
#ifndef NDEBUG
	UUIDBUF cbuf, ibuf;

	ExUuidStr(clsid, cbuf);
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::createObject(clsid:%s, iid:%s", cbuf, ibuf));
#endif
	if(E_SUCCESS == (status = Executive_metaClass(clsid, &IID_MObject, (void **) &constructor)))
	{
		status = MObject_create(constructor, executive.data.allocator, iid, out);
		EXLOGF((LOG_DEBUG7, "Executive::createObject(): MObject::create() -> %d", status));
		MObject_release(constructor);
		return status;
	}
	if(E_SUCCESS == (status = Executive_metaClass(clsid, &IID_MFactory, (void **) &factory)))
	{
		status = MFactory_createInstance(factory, NULL, iid, out);
		EXLOGF((LOG_DEBUG7, "Executive::createObject(): MFactory::createInstance() -> %d", status));
		MFactory_release(factory);
		return status;
	}
	EXLOGF((LOG_CONDITION, "%%E-NOENT: unable to obtain a suitable metaclass interface with which to create an instance of the requested class"));
	return E_NOENT;
}

/* request an interface from the metaclass identified by the specified class
 * UUID
 *
 * broadly equivalent to Co/DllGetClassObject()
 */
STATUS
Executive_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
#ifndef NDEBUG
	UUIDBUF cbuf, ibuf;
#endif
	size_t n;

	ExAssert(NULL != clsid);
	ExAssert(NULL != iid);
	if(E_SUCCESS == executive.data.PAL_metaClass(clsid, iid, out))
	{
		return E_SUCCESS;
	}
#ifndef NDEBUG
	ExUuidStr(clsid, cbuf);
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::metaClass(clsid:%s, iid:%s)", cbuf, ibuf));
#endif
	if(out)
	{
		*out = NULL;
	}
	for(n = 0; metaClass_entries[n].className; n++)
	{
		if(ExUuidEqual(clsid, metaClass_entries[n].clsid))
		{
			if(metaClass_entries[n].fn)
			{
				EXLOGF((LOG_DEBUG6, "Executive::metaClass(): invoking callback for clsid:%s", cbuf));
				return metaClass_entries[n].fn(clsid, iid, out);
			}
			if(metaClass_entries[n].factory)
			{
				EXLOGF((LOG_DEBUG6, "Executive::metaClass(): providing factory for clsid:%s", cbuf));
				return MFactory_queryInterface(metaClass_entries[n].factory, iid, out);
			}
			EXLOGF((LOG_CONDITION, "Executive::metaClass(): clsid:%s does not provide a callback or a factory", cbuf));
			return E_NOTIMPL;
		}
	}
	EXLOGF((LOG_CONDITION, "%%E-NOENT: Executive::metaClass(): clsid:%s is not registered", cbuf));
	return E_NOENT;
}

const char *
Executive_nameOfClass(REFUUID clsid)
{
	size_t n;

	for(n = 0; metaClass_entries[n].className; n++)
	{
		if(ExUuidEqual(clsid, metaClass_entries[n].clsid))
		{
			return metaClass_entries[n].className;
		}
	}
	return NULL;
}

STATUS
Executive_classIdForName(const char *name, UUID *clsid)
{
	ExAssert(NULL != name);
	ExAssert(NULL != clsid);

	size_t n;

	for(n = 0; metaClass_entries[n].className; n++)
	{
		if(ExStrEqual(name, metaClass_entries[n].className))
		{
			*clsid = *(metaClass_entries[n].clsid);
			return E_SUCCESS;
		}
	}
	return E_NOENT;
}

STATUS
Executive_createObjectByName(const char *name, REFUUID iid, void **out)
{
	STATUS status;
	UUID clsid;
#ifndef NDEBUG
	UUIDBUF ibuf;

	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::createObjectByName('%s', iid:%s", name, ibuf));
#endif
	status = Executive_classIdForName(name, &clsid);
	if(E_SUCCESS != status)
	{
		EXLOGF((LOG_DEBUG, "classIdForName() failed %d", status));
		return status;
	}
	return Executive_createObject(&clsid, iid, out);
}

static STATUS
Executive_MFactory_queryInterface(MFactory *me, REFUUID iid, void **out)
{
	if(ExUuidEqual(iid, &IID_IObject) || ExUuidEqual(iid, &IID_MFactory))
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
	return E_NOTIMPL;
}

static REFCOUNT Executive_MFactory_retain(MFactory *me)
{
	UNUSED__(me);

	return 2;
}

static REFCOUNT Executive_MFactory_release(MFactory *me)
{
	UNUSED__(me);
	
	return 1;
}

static STATUS Executive_MFactory_lock(MFactory *me, bool dolock)
{
	UNUSED__(me);
	UNUSED__(dolock);

	return E_SUCCESS;
}
