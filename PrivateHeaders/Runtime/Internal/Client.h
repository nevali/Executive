#ifndef RUNTIME_INTERNAL_CLIENT_H_
# define RUNTIME_INTERNAL_CLIENT_H_    1

# include <Runtime/UUID.h>

# include <Runtime/IObject.h>
# include <Runtime/IAllocator.h>
# include <Runtime/IRegionHolder.h>
# include <Runtime/Task.h>
# include <Executive/IAddressSpace.h>
# include <Executive/INamespace.h>

#define DECLARE_CLIENT(name) \
	typedef union I## name ##_Client I## name ##_Client; \
	union I## name ##_Client \
	{ \
		I## name name; \
		struct \
		{ \
			const void *vtable; \
			REFCOUNT refCount; \
			int descriptor; \
		} data; \
	}; \
	\
	EXTERN_C I## name *I## name ##_Client_create(int descriptor) RUNTIME_LINKAGE__(I ## name ## _Client_create);

DECLARE_CLIENT(Task);
DECLARE_CLIENT(Thread);
DECLARE_CLIENT(Namespace);
DECLARE_CLIENT(AddressSpace);

EXTERN_C void IAddressSpace_Client_init_(IAddressSpace_Client *self, int descriptor) RUNTIME_PRIVATE__(IAddressSpace_Client_init_);

#endif /*!RUNTIME_INTERNAL_CLIENT_H_*/
