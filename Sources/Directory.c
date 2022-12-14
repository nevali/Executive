#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

#include "Executive/Internal/Directory.h"

/** Executive::Directory **/

/* Retrieve metaclass interfaces for any of the family of classes implemented
 * by this module
 */
STATUS
Executive_Directory_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
#ifndef NDEBUG
	UUIDBUF cbuf, ibuf;
#endif

#ifndef NDEBUG
	ExUuidStr(clsid, cbuf);
	ExUuidStr(iid, ibuf);
	EXLOGF((LOG_TRACE, "Executive::Directory::metaClass(clsid:%s, iid:%s)", cbuf, ibuf));
#endif
	if(out)
	{
		*out = NULL;
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_Container))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_Container_MDirectoryEntryTarget), iid, out);
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_Root))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_Root_MDirectoryEntryTarget), iid, out);
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_System))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_System_MDirectoryEntryTarget), iid, out);
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_Local))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_Local_MDirectoryEntryTarget), iid, out);
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_Cluster))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_Cluster_MDirectoryEntryTarget), iid, out);
	}
	if(ExUuidEqual(clsid, &CLSID_Executive_Network))
	{
		return MDirectoryEntryTarget_queryInterface((&Executive_Directory_Network_MDirectoryEntryTarget), iid, out);
	}
#ifndef NDEBUG
	EXLOGF((LOG_CONDITION, "%%E-NOENT: Executive::Directory::metaClass(): clsid:%s is not supported by this implementation", cbuf));
#endif
	return E_NOENT;
}
