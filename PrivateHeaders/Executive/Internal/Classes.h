#ifndef EXECUTIVE_INTERNAL_CLASSES_H_
# define EXECUTIVE_INTERNAL_CLASSES_H_

# include <Executive/Linkage.h>
# include <Executive/Types.h>
# include <Executive/Errors.h>
# include <Executive/UUID.h>
# include <Executive/Classes.h>

# define EXEC_COMMON_INTF_TO(i, class) ((class *)((IObject *)(void *)(i))->instptr)
# define EXEC_COMMON_SUPPORTS(basename) \
	if(ExUuidEqual(iid, &IID_I ## basename)) \
	{ \
		if(out) \
		{ \
			I ## basename ##_retain((&(self->basename))); \
			*out = &(self->basename); \
		} \
		return E_SUCCESS; \
	}
# define EXEC_COMMON_NOTIMPL \
	if(out) \
	{ \
		*out = NULL; \
	} \
	do { \
		UUIDBUF ibuf; \
		ExUuidStr(iid, ibuf); \
		EXLOGF((LOG_CONDITION, "%%E-NOTIMPL: %s(): iid:%s is not supported", __FUNCTION__, ibuf)); \
	} while(0); \
	return E_NOTIMPL;
# define EXEC_COMMON_SUPPORTS_DEFAULT \
	EXEC_COMMON_SUPPORTS(Object); \
	EXEC_COMMON_NOTIMPL
# define EXEC_COMMON_RETAIN(class) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount++; \
	return self->data.refCount;
# define EXEC_COMMON_RELEASE(class, fini) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount--; \
	if(!self->data.refCount) \
	{ \
		fini; \
		return 0; \
	} \
	return self->data.refCount;

# define EXEC_COMMON_DECL_QUERYINTERFACE(classname) STATUS classname ## _queryInterface(IObject *me, REFUUID iid, void **out)
# define EXEC_COMMON_DECL_RETAIN(classname) REFCOUNT classname ## _retain(IObject *me)
# define EXEC_COMMON_DECL_RELEASE(classname) REFCOUNT classname ## _release(IObject *me)
# define EXEC_COMMON_DECL_IOBJECT(classname) \
	EXEC_COMMON_DECL_QUERYINTERFACE(classname); \
	EXEC_COMMON_DECL_RETAIN(classname); \
	EXEC_COMMON_DECL_RELEASE(classname);
# define EXEC_COMMON_STATIC_IOBJECT(classname) \
	static EXEC_COMMON_DECL_QUERYINTERFACE(classname); \
	static EXEC_COMMON_DECL_RETAIN(classname); \
	static EXEC_COMMON_DECL_RELEASE(classname);
# define EXEC_COMMON_VTABLE_IOBJECT(classname, coerce) \
	(STATUS (*) (coerce *, REFUUID, void **)) &classname ## _queryInterface, \
	(REFCOUNT (*) (coerce *)) &classname ## _retain, \
	(REFCOUNT (*) (coerce *)) &classname ## _release

STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);
STATUS Executive_createObject(REFUUID clsid, REFUUID iid, void **out);

/* these should just be /System/Classes lookups */
STATUS Executive_classIdForName(const char *name, UUID *out);
STATUS Executive_createObjectByName(const char *name, REFUUID iid, void **out);
/* XXX this is not a good interface no no no */
const char *Executive_nameOfClass(REFUUID clsid);


#endif /*!EXECUTIVE_INTERNAL_CLASSES_H_*/
