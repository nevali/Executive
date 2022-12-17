#ifndef EXECUTIVE_INTERNAL_CLASSES_H_
# define EXECUTIVE_INTERNAL_CLASSES_H_

# include <Executive/Linkage.h>
# include <Executive/Types.h>
# include <Executive/Errors.h>
# include <Executive/UUID.h>
# include <Executive/Classes.h>

STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_createObject(REFUUID clsid, REFUUID iid, void **out);

/* these should just be /System/Classes lookups */
STATUS Executive_classIdForName(const char *name, UUID *out);
STATUS Executive_createObjectByName(const char *name, REFUUID iid, void **out);
/* XXX this is not a good interface no no no */
const char *Executive_nameOfClass(REFUUID clsid);


#endif /*!EXECUTIVE_INTERNAL_CLASSES_H_*/
