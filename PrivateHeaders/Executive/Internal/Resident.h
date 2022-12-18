#ifndef EXECUTIVE_INTERNAL_RESIDENT_H_
# define EXECUTIVE_INTERNAL_RESIDENT_H_ 1

# include <Executive/IObject.h>

typedef struct Executive_Resident_Object Executive_Resident_Object;

struct Executive_Resident_Object
{
	const char *name;
	REFUUID classid;
	IObject *instance;
};

extern Executive_Resident_Object *Executive_Resident_objects(void);

#endif /*!EXECUTIVE_INTERNAL_RESIDENT_H_*/
