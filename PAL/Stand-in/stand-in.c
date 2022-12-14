/* This file is compiled into the library that is installed as libPAL.so (or
 * similar), and exists only to satisfy a runtime dynamic linker dependency -
 * the only symbol it exports is __PAL_ident
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

const char __PAL_ident[] = "@(#) $PAL: Stand-in [ " PACKAGE_STRING " build " PRODUCT_BUILD_ID_STR " by " PRODUCT_BUILD_USER "@" PRODUCT_BUILD_HOST " ] $";
