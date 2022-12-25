#ifndef RUNTIME_INTERNAL_CLIENT_H_
# define RUNTIME_INTERNAL_CLIENT_H_    1

# include <Runtime/UUID.h>

# include <Runtime/IObject.h>
# include <Runtime/IAllocator.h>
# include <Runtime/IRegionHolder.h>
# include <Runtime/Task.h>
# include <Executive/IAddressSpace.h>
# include <Executive/INamespace.h>
# include <Executive/IWriteChannel.h>

typedef union Runtime_Client Runtime_Client;

union Runtime_Client
{
	IObject Object;
	IAddressSpace AddressSpace;
	IThread Thread;
	ITask Task;
	INamespace Namespace;
	IRegion Region;
	struct
	{
		const void *vtable;
		REFCOUNT refCount;
		int descriptor;
	} data;
};

#define DECLARE_CLIENT(name) \
	typedef union Runtime_Client I ## name ##_Client; \
	EXTERN_C I## name *I## name ##_Client_create(int descriptor) RUNTIME_LINKAGE__(I ## name ## _Client_create);

DECLARE_CLIENT(Task);
DECLARE_CLIENT(Thread);
DECLARE_CLIENT(Namespace);
DECLARE_CLIENT(AddressSpace);
DECLARE_CLIENT(Region);
DECLARE_CLIENT(Container);
DECLARE_CLIENT(WriteChannel);

EXTERN_C void IAddressSpace_Client_init_(IAddressSpace_Client *self, int descriptor) RUNTIME_PRIVATE__(IAddressSpace_Client_init_);

#endif /*!RUNTIME_INTERNAL_CLIENT_H_*/
