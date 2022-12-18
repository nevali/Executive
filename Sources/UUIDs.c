# define INITGUID_EXTERN       1

/* include all of the files to get the declarations */

#include "p_UUIDs.h"

#define INITGUID
#include <Executive/initguid.h>

/* now include them again to define the UUIDs */

#include "p_UUIDs.h"
