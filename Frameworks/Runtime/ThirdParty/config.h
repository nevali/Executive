/* Build configuration file used by the snprintf implementation */

#include "BuildConfiguration.h"

#define INITGUID_EXTERN                1

#include <Runtime/Memory.h>

#define malloc(x) RtMemAlloc(x)

#undef HAVE_VASPRINTF
#undef HAVE_ASPRINTF
#undef HAVE_VSNPRINTF
#undef HAVE_SNPRINTF

#define rpl_vasprintf RtStrFormatArgs
#define vasprintf rpl_vasprintf
#define rpl_asprintf RtStrFormat
#define asprintf rpl_asprintf
#define rpl_vsnprintf RtStrBufFormatArgs
#define vsnprintf rpl_vsnprintf
#define rpl_snprintf RtStrBufFormat
#define snprintf rpl_snprintf
