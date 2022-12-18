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

/* Each registered class may either have a callback function, whose signature
 * matches that of Executive::metaClass(), or an interface pointer on the
 * metaclass itself, whose queryInterface() method will subsequently
 * invoked
 *
 * Only some registered classes provide any metaclass interfaces
 */

struct MetaClassEntry metaClass_entries[] = {
	{ "Executive", &CLSID_Executive_System, "System Domain", Executive_MetaClass_metaClass, NULL },
	{ "Executive::Classes", &CLSID_Executive_Classes, "Classes", NULL, &Executive_Classes_IContainer },
	{ "PAL::Platform", &CLSID_PAL_Platform, "Platform", NULL, NULL },
	{ "PAL::PlatformDiagnostics", &CLSID_PAL_PlatformDiagnostics, "Platform Diagnostics", NULL, NULL },
	/* XXX the Executive's implementation should be retrievable here */
	{ "PAL::BootEnvironment", &CLSID_PAL_BootEnvironment, "Boot Environment", NULL, NULL },
	/* XXX missing PAL::MemoryManager */
	{ "Executive::Container", &CLSID_Executive_Container, "Container", Executive_Directory_metaClass, NULL },
	{ "Executive::Link", &CLSID_Executive_Link, "Link", NULL, NULL },
	{ "Executive::Allocator", &CLSID_Executive_Allocator, "Memory Allocator", NULL, &Executive_Allocator_MFactory },
	{ "Executive::Root", &CLSID_Executive_Root, "Object Directory", Executive_Directory_metaClass, NULL },
	{ "Executive::Local", &CLSID_Executive_Local, "Local Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Cluster", &CLSID_Executive_Cluster, "Cluster Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Network", &CLSID_Executive_Network, "Network Domain", Executive_Directory_metaClass, NULL },
	{ "Executive::Node", &CLSID_Executive_Node, "Node", NULL, NULL },
	{ "Executive::Tasker", &CLSID_Executive_Tasker, "Tasker", NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL }
};

/* request a metaclass interface from the class identified by the specified clsid
 *
 * broadly equivalent to Co/DllGetClassObject()
 */
STATUS
Executive_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	size_t n;
	STATUS status;

	ExAssert(NULL != clsid);
	ExAssert(NULL != iid);
	if(E_SUCCESS == executive.data.PAL_metaClass(clsid, iid, out))
	{
		return E_SUCCESS;
	}
	EXTRACEF(("Executive::metaClass(clsid:" UUID_PRINTF_FORMAT ", iid:" UUID_PRINTF_FORMAT ")",
		UUID_PRINTF_ARGS(clsid),
		UUID_PRINTF_ARGS(iid)));
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
				EXDBGF((LOG_DEBUG6, "Executive::metaClass(): invoking callback for clsid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid)));
				return metaClass_entries[n].fn(clsid, iid, out);
			}
			if(metaClass_entries[n].factory)
			{
				EXDBGF((LOG_DEBUG6, "Executive::metaClass(): providing factory for clsid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid)));
				return MFactory_queryInterface(((IObject *) metaClass_entries[n].factory), iid, out);
			}
			status = E_NOTIMPL;
			EXLOGF((LOG_CONDITION, "%s: Executive::metaClass(): clsid:" UUID_PRINTF_FORMAT " does not provide a callback or factory", ExStatusName(status), UUID_PRINTF_ARGS(clsid)));
			return E_NOTIMPL;
		}
	}
	status = E_NOTIMPL;
	EXLOGF((LOG_CONDITION, "%s: Executive::metaClass(): clsid:" UUID_PRINTF_FORMAT " is not registered", ExStatusName(status), UUID_PRINTF_ARGS(clsid)));
	return E_NOENT;
}

/* create an instance using MObject or MFactory */
STATUS
Executive_createObject(REFUUID clsid, REFUUID iid, void **out)
{
	STATUS status;
	MObject *constructor;
	MFactory *factory;

	EXTRACEF(("Executive::createObject(clsid:" UUID_PRINTF_FORMAT ", iid:" UUID_PRINTF_FORMAT ")",
		UUID_PRINTF_ARGS(clsid), UUID_PRINTF_ARGS(iid)));
	if(E_SUCCESS == (status = Executive_metaClass(clsid, &IID_MObject, (void **) &constructor)))
	{
		EXLOGF((LOG_DEBUG7, "Executive::createObject: using MObject metaclass interface"));
		status = MObject_create(constructor, executive.data.allocator, iid, out);
		EXLOGF((LOG_DEBUG7, "Executive::createObject(): MObject::create() -> %s", ExStatusName(status)));
		MObject_release(constructor);
		return status;
	}
	if(E_SUCCESS == (status = Executive_metaClass(clsid, &IID_MFactory, (void **) &factory)))
	{
		EXLOGF((LOG_DEBUG7, "Executive::createObject: using MFactory metaclass interface"));
		status = MFactory_createInstance(factory, NULL, iid, out);
		EXLOGF((LOG_DEBUG7, "Executive::createObject(): MFactory::createInstance() -> %s:", ExStatusName(status)));
		MFactory_release(factory);
		return status;
	}
	status = E_NOENT;
	EXLOGF((LOG_CONDITION, "%s: unable to obtain a suitable metaclass interface with which to create an instance of the requested class", ExStatusName(status)));
	return status;
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

	EXTRACEF(("Executive::createObjectByName('%s', iid:" UUID_PRINTF_FORMAT ")", name, UUID_PRINTF_ARGS(iid)));
	status = Executive_classIdForName(name, &clsid);
	if(E_SUCCESS != status)
	{
		ExLogCondition(status, name);
		return status;
	}
	return Executive_createObject(&clsid, iid, out);
}
