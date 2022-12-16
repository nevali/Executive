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
	PALLOGF((LOG_TRACE, "PAL::POSIX::metaClass(): clsid:" UUID_PRINTF_FORMAT " iid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid), UUID_PRINTF_ARGS(iid)));
	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(clsid, &CLSID_PAL_Platform, sizeof(UUID)))
	{
		return IObject_queryInterface((&(PAL_POSIX_platform.Object)), iid, out);
	}
	if(0 == memcmp(clsid, &CLSID_PAL_MemoryManager, sizeof(UUID)))
	{
		if(PAL_POSIX_platform.data.memoryManager)
		{
			return IMemoryManager_queryInterface(PAL_POSIX_platform.data.memoryManager, iid, out);
		}
		PALLOGF((LOG_CONDITION, "%%E-NOT-AVAIL: the memory manager object is not available"));
	}
	if(0 == memcmp(clsid, &CLSID_PAL_PlatformDiagnostics, sizeof(UUID)))
	{
		if(PAL_POSIX_platform.data.diagnostics)
		{
			return IPlatformDiagnostics_queryInterface(PAL_POSIX_platform.data.diagnostics, iid, out);
		}
		PALLOGF((LOG_CONDITION, "%%E-NOT-AVAIL: the platform diagnostics object is not available"));
	}
	/* Class unsupported */
	PALLOGF((LOG_CONDITION, "%%E-NOENT: PAL::POSIX::metaClass(): unsupported clsid:{ %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x } requested via PAL$metaClass()",
		clsid->uuid.time_low, clsid->uuid.time_mid, clsid->uuid.time_hi_and_version,
		clsid->uuid.clock_seq_hi_and_reserved, clsid->uuid.clock_seq_low,
		clsid->uuid.node[0], clsid->uuid.node[1], clsid->uuid.node[2],
		clsid->uuid.node[3], clsid->uuid.node[4], clsid->uuid.node[5]));
	return E_NOENT;
}
