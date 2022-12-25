/* Executive Microkernel
 *   PrivateHeaders/Executive/Internal/Classes.h
 */

/* Copyright (c) 2015-2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef EXECUTIVE_INTERNAL_CLASSES_H_
# define EXECUTIVE_INTERNAL_CLASSES_H_

# include <Executive/Linkage.h>
# include <Executive/Types.h>
# include <Executive/Errors.h>
# include <Executive/UUID.h>
# include <Executive/Classes.h>
# include <Executive/Internal/Runtime.h>

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
	EXTERN_C EXEC_COMMON_DECL_QUERYINTERFACE(classname); \
	EXTERN_C EXEC_COMMON_DECL_RETAIN(classname); \
	EXTERN_C EXEC_COMMON_DECL_RELEASE(classname);
# define EXEC_COMMON_STATIC_IOBJECT(classname) \
	static EXEC_COMMON_DECL_QUERYINTERFACE(classname); \
	static EXEC_COMMON_DECL_RETAIN(classname); \
	static EXEC_COMMON_DECL_RELEASE(classname);
# define EXEC_COMMON_VTABLE_IOBJECT(classname, coerce) \
	(STATUS (*) (coerce *, REFUUID, void **)) &classname ## _queryInterface, \
	(REFCOUNT (*) (coerce *)) &classname ## _retain, \
	(REFCOUNT (*) (coerce *)) &classname ## _release

EXTERN_C STATUS Executive_metaClass(REFUUID clsid, REFUUID iid, void **out);
EXTERN_C STATUS Executive_createObject(REFUUID clsid, REFUUID iid, void **out);

/* these should just be /System/Classes lookups */
EXTERN_C STATUS Executive_classIdForName(const char *name, UUID *out);
EXTERN_C STATUS Executive_createObjectByName(const char *name, REFUUID iid, void **out);
/* XXX this is not a good interface no no no */
EXTERN_C const char *Executive_nameOfClass(REFUUID clsid);

#endif /*!EXECUTIVE_INTERNAL_CLASSES_H_*/
