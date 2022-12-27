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
STATUS
PAL_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	if(!PAL_POSIX)
	{
		PAL_POSIX_Platform_init();
		if(!PAL_POSIX)
		{
			abort();
		}
	}
#if FEATURE_TRACE
/*	fprintf(stderr, "PAL::metaClass(" UUID_PRINTF_FORMAT ")\n", UUID_PRINTF_ARGS(clsid)); */
	PALLOGF((LOG_TRACE, "PAL::POSIX::metaClass(): clsid:" UUID_PRINTF_FORMAT " iid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid), UUID_PRINTF_ARGS(iid)));
#endif
	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(clsid, &CLSID_PAL_Platform, sizeof(UUID)))
	{
		return IObject_queryInterface((&(PAL_POSIX->Object)), iid, out);
	}
	if(0 == memcmp(clsid, &CLSID_PAL_MemoryManager, sizeof(UUID)))
	{
		if(PAL_POSIX->data.addressSpace)
		{
			return IAddressSpace_queryInterface(PAL_POSIX->data.addressSpace, iid, out);
		}
		PALLOGF((LOG_CONDITION, "%%E-NOT-AVAIL: the address space object is not available"));
	}
	if(0 == memcmp(clsid, &CLSID_PAL_PlatformDiagnostics, sizeof(UUID)))
	{
#if FEATURE_PAL_DIAGNOSTICS
		if(PAL_POSIX->data.diagnostics)
		{
			return IPlatformDiagnostics_queryInterface(PAL_POSIX->data.diagnostics, iid, out);
		}
#endif /*FEATURE_PAL_DIAGNOSTICS*/
		PALLOGF((LOG_CONDITION, "%%E-NOT-AVAIL: the platform diagnostics object is not available"));
	}
#if 0
	if(0 == memcmp(clsid, &CLSID_PAL_Console, sizeof(UUID)))
	{
#if FEATURE_CONSOLE
		if(PAL_POSIX->data.console)
		{
			return IObject_queryInterface((&(PAL_POSIX->data.Console->Object)), iid, out);
		}
#endif /*FEATURE_CONSOLE*/
		PALLOGF((LOG_CONDITION, "%%E-NOT-AVAIL: the console object is not available"));
	}
#endif
	/* Class unsupported */
#if FEATURE_DEBUG_CLASSES
	PALLOGF((LOG_CONDITION, "%%E-NOENT: PAL::POSIX::metaClass(): unsupported clsid:" UUID_PRINTF_FORMAT " requested via PAL$metaClass()",
		UUID_PRINTF_ARGS(clsid)));
#endif
	return E_NOENT;
}
