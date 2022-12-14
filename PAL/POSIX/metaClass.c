#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

/* PAL_metaClass() is invoked by the Executive at the earliest possible
 * point in the execution flow, in order to obtain this PAL's implementation
 * of the Platform object.
 *
 * PAL_metaClass() can also be invoked at other times, to obtain other
 * well-known singleton objects
 * 
 * COM doesn't support class methods (or "static" methods) on interfaces,
 * and there's no mechanism to invoke a method without supplying an interface
 * pointer (which implementation of that interface should be invoked?)
 * 
 * COM does have the concept of "class objects", which encapsulate sets of
 * static (i.e., "instanceless") methods into standard COM instances, and this
 * is how the factory pattern is implemented (with different class object
 * interfaces, such as IClassFactory, IClassFactory2, etc., in Microsoft COM,
 * used to provide for different construction patterns)
 */
int
PAL_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	/* Perform any one-time initialisation that might be required */
	PAL_POSIX_init();
	if(0 == memcmp(clsid, &CLSID_PAL_Platform, sizeof(UUID)))
	{
		if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)) ||
			0 == memcmp(iid, &IID_IPlatform, sizeof(UUID)))
		{
			PALDebug2("PAL::POSIX::metaClass(): Executive requesting a supported interface from CLSID_PAL_Platform");
			if(out)
			{
				*out = &PAL_POSIX_platform;
			}
			return E_SUCCESS;
		}
		/* Interface unsupported */
		PALDebug("PAL::POSIX::metaClass(): unsupported interface requested from CLSID_PAL_Platform");
		return E_NOENT;
	}
	if(0 == memcmp(clsid, &CLSID_PAL_MemoryManager, sizeof(UUID)))
	{
		if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)) ||
			0 == memcmp(iid, &IID_IMemoryManager, sizeof(UUID)))
		{
			PALDebug2("PAL::POSIX::metaClass(): Executive requesting a supported interface from CLSID_PAL_MemoryManager");
			if(out)
			{
				*out = &PAL_POSIX_memoryManager;
			}
			return E_SUCCESS;
		}
		/* Interface unsupported */
		PALDebug("PAL::POSIX::metaClass(): unsupported interface requested from CLSID_PAL_MemoryManager");
		return E_NOENT;
	}
	if(0 == memcmp(clsid, &CLSID_PAL_PlatformDiagnostics, sizeof(UUID)))
	{
		if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)) ||
			0 == memcmp(iid, &IID_IPlatformDiagnostics, sizeof(UUID)))
		{
			PALDebug2("PAL::POSIX::metaClass(): Executive requesting a supported interface from CLSID_PAL_PlatformDiagnostics");
			if(out)
			{
				*out = &PAL_POSIX_diagnostics;
			}
			return E_SUCCESS;
		}
		/* Interface unsupported */
		PALDebug("PAL::POSIX::metaClass(): unsupported interface requested from CLSID_PAL_MemoryManager");
		return E_NOENT;
	}
	/* Class unsupported */
	PALDebug("PAL::POSIX::metaClass(): unsupported class requested via PAL$metaClass()");
	return E_NOENT;
}
