#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_Platform *)((void *)(i)->instptr)

static STATUS PAL_POSIX_Platform_queryInterface(IObject *self, REFUUID iid, void **out);
static REFCOUNT PAL_POSIX_Platform_retain(IObject *self);
static REFCOUNT PAL_POSIX_Platform_release(IObject *self);
static void PAL_POSIX_Platform_panic(struct IPlatform *self, const char *str);
static void PAL_POSIX_Platform_setDefaultAllocator(struct IPlatform *self, IAllocator *allocator);
static void PAL_POSIX_Platform_nap(struct IPlatform *self);
static STATUS PAL_POSIX_Platform_resolve(IContainer *self, const char *name, IDirectoryEntry **entry);
static IIterator *PAL_POSIX_Platform_iterator(IContainer *self);

/* IObject */
static struct IObject_vtable_ platform_IObject_vtable = {
	PAL_POSIX_Platform_queryInterface,
	PAL_POSIX_Platform_retain,
	PAL_POSIX_Platform_release,
};
/* IPlatform */
static struct IPlatform_vtable_ platform_IPlatform_vtable = {
	(STATUS (*)(IPlatform *, REFUUID, void **)) &PAL_POSIX_Platform_queryInterface,
	(REFCOUNT (*)(IPlatform *)) &PAL_POSIX_Platform_retain,
	(REFCOUNT (*)(IPlatform *)) &PAL_POSIX_Platform_release,
	PAL_POSIX_Platform_panic,
	PAL_POSIX_Platform_setDefaultAllocator,
	PAL_POSIX_Platform_nap
};
/* IContainer */
static struct IContainer_vtable_ platform_IContainer_vtable = {
	(STATUS (*)(IContainer *, REFUUID, void **)) &PAL_POSIX_Platform_queryInterface,
	(REFCOUNT (*)(IContainer *)) &PAL_POSIX_Platform_retain,
	(REFCOUNT (*)(IContainer *)) &PAL_POSIX_Platform_release,
	PAL_POSIX_Platform_resolve,
	PAL_POSIX_Platform_iterator
};

PAL_POSIX_Platform PAL_POSIX_platform;

void
PAL_POSIX_Platform_init(void)
{
	memset(&PAL_POSIX_platform, 0, sizeof(PAL_POSIX_platform));
	PAL_POSIX_platform.Object.lpVtbl = &platform_IObject_vtable;
	PAL_POSIX_platform.Object.instptr = &PAL_POSIX_platform;
	PAL_POSIX_platform.Platform.lpVtbl = &platform_IPlatform_vtable;
	PAL_POSIX_platform.Platform.instptr = &PAL_POSIX_platform;
	PAL_POSIX_platform.Container.lpVtbl = &platform_IContainer_vtable;
	PAL_POSIX_platform.Container.instptr = &PAL_POSIX_platform;
}

/* INTERNAL */
void
PAL_POSIX_Platform_setMemoryManager(IMemoryManager *mm)
{
	if(!PAL_POSIX_platform.data.memoryManager)
	{
		PAL_POSIX_platform.data.memoryManager = mm;
	}
}

/* INTERNAL */
void
PAL_POSIX_Platform_setDiagnostics(IPlatformDiagnostics *diag)
{
	if(!PAL_POSIX_platform.data.diagnostics)
	{
		PAL_POSIX_platform.data.diagnostics = diag;
	}
}

/* IObject */

static STATUS
PAL_POSIX_Platform_queryInterface(IObject *self, REFUUID iid, void **out)
{
	STATUS status;
	UNUSED__(self);

	PALLOGF((LOG_TRACE, "PAL::POSIX::Platform::queryInterface(iid:" UUID_PRINTF_FORMAT ")", UUID_PRINTF_ARGS(iid)));
	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			*out = &(PAL_POSIX_platform.Object);
		}
		PALLOGF((LOG_DEBUG7, "returning PAL::POSIX::Platform<IObject>"));
		return E_SUCCESS;
	}
	if(0 == memcmp(iid, &IID_IPlatform, sizeof(UUID)))
	{
		if(out)
		{
			*out = &(PAL_POSIX_platform.Platform);
		}
		PALLOGF((LOG_DEBUG7, "returning PAL::POSIX::Platform<IPlatform>"));
		return E_SUCCESS;
	}
	if(0 == memcmp(iid, &IID_IContainer, sizeof(UUID)))
	{
		if(!PAL_POSIX_platform.data.platformContainer)
		{
			/* XXX wait until we have a namespace */
			PALDebug("PAL::POSIX::Platform::queryInterface(): creating platform container");
			if(E_SUCCESS != (status = Executive_createObjectByName("Executive::Container", &IID_IMutableContainer, (void **) &(PAL_POSIX_platform.data.platformContainer))))
			{
				PAL_panic("Executive::createObject(Executive::Container, IMutableContainer) failed");
				return status;
			}
			PALDebug("PAL::POSIX::Platform::queryInterface(): created platform container!");
			IMutableContainer_create((PAL_POSIX_platform.data.platformContainer), "Devices", &CLSID_Executive_Container, NULL, NULL);
		}
		if(out)
		{
			*out = &(PAL_POSIX_platform.Container);
		}
		PALLOGF((LOG_DEBUG7, "returning PAL::POSIX::Platform<IContainer>"));
		return E_SUCCESS;
	}
	return E_NOTIMPL;
}

/* The Platform object is a singleton and cannot be destroyed, therefore
 * reference-counting is not implemented
 */
static REFCOUNT
PAL_POSIX_Platform_retain(IObject *self)
{
	UNUSED__(self);

	return 2;
}

static REFCOUNT
PAL_POSIX_Platform_release(IObject *self)
{
	UNUSED__(self);

	return 1;
}

/* IPlatform */

static void
PAL_POSIX_Platform_panic(IPlatform *self, const char *string)
{
	UNUSED__(self);

	PAL_panic(string);
}

static void
PAL_POSIX_Platform_setDefaultAllocator(IPlatform *self, IAllocator *allocator)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

	IAllocator_retain(allocator);
	if(me->data.allocator)
	{
		IAllocator_release(me->data.allocator);
	}
	me->data.allocator = allocator;
	PALDebug("PAL::POSIX::Platform::setDefaultAllocator(): new default allocator installed");
}

static void
PAL_POSIX_Platform_nap(IPlatform *self)
{
	UNUSED__(self);
	
	PALDebug("PAL::POSIX::Platform::nap()");
	sleep(1);
}

static STATUS
PAL_POSIX_Platform_resolve(IContainer *self, const char *name, IDirectoryEntry **entry)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

/*	fprintf(stderr, "PAL::POSIX::Platform<IContainer>::resolve('%s')\n", name); */
	if(entry)
	{
		*entry = NULL;
	}
	if(!me->data.platformContainer)
	{
		return E_NOTIMPL;
	}
	return IMutableContainer_resolve(me->data.platformContainer, name, entry);
}

static IIterator *
PAL_POSIX_Platform_iterator(IContainer *self)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

/*	fprintf(stderr, "PAL::POSIX::Platform<IContainer>::iterator()\n"); */
	if(!me->data.platformContainer)
	{
		return NULL;
	}
	return IMutableContainer_iterator(me->data.platformContainer);
}
