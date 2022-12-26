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
# include <Executive/ILink.h>

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
	typedef union Runtime_Client name ##_Client; \
	EXTERN_C name *name ##_Client_create(int descriptor) RUNTIME_LINKAGE__(name ## _Client_create);

DECLARE_CLIENT(ITask);
DECLARE_CLIENT(IThread);
DECLARE_CLIENT(INamespace);
DECLARE_CLIENT(IAddressSpace);
DECLARE_CLIENT(IRegion);
DECLARE_CLIENT(IContainer);
DECLARE_CLIENT(IWriteChannel);
DECLARE_CLIENT(IIterator);
DECLARE_CLIENT(IDirectoryEntry);
DECLARE_CLIENT(ILink);

/* Invoked by the runtime during initialisation */
EXTERN_C void IAddressSpace_Client_init_(IAddressSpace_Client *self, int descriptor) RUNTIME_PRIVATE__(IAddressSpace_Client_init_);
/* Invoked by the allocator after allocating a block of memory */
EXTERN_C void IRegion_Client_update_(void) RUNTIME_PRIVATE__(IRegion_Cliient_update_);

#endif /*!RUNTIME_INTERNAL_CLIENT_H_*/
