#define INITGUID_EXTERN                1

#include <Executive/Internal/Resident.h>
#include <Executive/Classes.h>

extern IObject *bootstrap_IObject;

static Executive_Resident_Object resident[] = {
	{ "Bootstrap", &CLSID_Executive_Subsystem, NULL },
	{ NULL, NULL, NULL }
};

Executive_Resident_Object *
Executive_Resident_objects(void)
{
	resident[0].instance = bootstrap_IObject;
	return resident;
}
