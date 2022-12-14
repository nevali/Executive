#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include <Executive/Linkage.h>

#undef PAL_LINKAGE__
#define PAL_LINKAGE__(name, version)    WEAK_IMPORT__ WEAK_STUB__ SYM__("PAL", name, version)

#include <PAL/PAL.h>

/* PAL$metaClass() is the main interface between the Executive and the PAL.
 * It obtains the metaclass interface identified by the UUID in iid from
 * the "well-known" class identified by the UUID in clsid.
 *
 * In the case of the PAL, the Platform, Boot Environment, and Memory Manager
 * objects are retrieved this way: because they're singletons that exist for
 * the lifetime of the system, they only have "class methods" (as opposed to
 * "instance methods") and thus there's no need to have a factory interface
 * perform construction of a new instance.
 */
int
PAL_metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	UNUSED__(clsid);
	UNUSED__(iid);
	UNUSED__(out);

	return E_NOTIMPL;
}

/* PAL$__panic() is identical to IPlatform::panic() but, available as a global
 * for convenience
 */
void
PAL_panic(const char *str)
{
	UNUSED__(str);
}