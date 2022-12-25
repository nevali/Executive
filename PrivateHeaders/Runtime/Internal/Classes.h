#ifndef RUNTIME_INTERNAL_CLASSES_H_
# define RUNTIME_INTERNAL_CLASSES_H_   1

# define RUNTIME_INTF_TO(i, class) ((class *)((IObject *)(void *)(i))->instptr)
# define RUNTIME_SUPPORTS(basename) \
	if(ExUuidEqual(iid, &IID_I ## basename)) \
	{ \
		if(out) \
		{ \
			I ## basename ##_retain((&(self->basename))); \
			*out = &(self->basename); \
		} \
		return E_SUCCESS; \
	}
# define RUNTIME_NOTIMPL \
	if(out) \
	{ \
		*out = NULL; \
	} \
	return E_NOTIMPL;
# define RUNTIME_SUPPORTS_DEFAULT \
	RUNTIME_SUPPORTS(Object); \
	RUNTIME_NOTIMPL
# define RUNTIME_RETAIN(class) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount++; \
	return self->data.refCount;
# define RUNTIME_RELEASE(class, fini) \
	class *self = INTF_TO_CLASS(me); \
	self->data.refCount--; \
	if(!self->data.refCount) \
	{ \
		fini; \
		return 0; \
	} \
	return self->data.refCount;
# define RUNTIME_DECL_QUERYINTERFACE(classname) STATUS classname ## _queryInterface(IObject *me, REFUUID iid, void **out)
# define RUNTIME_DECL_RETAIN(classname) REFCOUNT classname ## _retain(IObject *me)
# define RUNTIME_DECL_RELEASE(classname) REFCOUNT classname ## _release(IObject *me)
# define RUNTIME_DECL_IOBJECT(classname) \
	EXTERN_C RUNTIME_DECL_QUERYINTERFACE(classname); \
	EXTERN_C RUNTIME_DECL_RETAIN(classname); \
	EXTERN_C RUNTIME_DECL_RELEASE(classname);
# define RUNTIME_STATIC_IOBJECT(classname) \
	static RUNTIME_DECL_QUERYINTERFACE(classname); \
	static RUNTIME_DECL_RETAIN(classname); \
	static RUNTIME_DECL_RELEASE(classname);
# define RUNTIME_VTABLE_IOBJECT(classname, coerce) \
	(STATUS (*) (coerce *, REFUUID, void **)) &classname ## _queryInterface, \
	(REFCOUNT (*) (coerce *)) &classname ## _retain, \
	(REFCOUNT (*) (coerce *)) &classname ## _release

#endif /*!RUNTIME_INTERNAL_CLASSES_H_*/
