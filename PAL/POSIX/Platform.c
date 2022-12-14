#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_Platform *)((void *)(i))

static int PAL_POSIX_Platform_queryInterface(struct IPlatform *self, REFUUID iid, void **out);
static int32_t PAL_POSIX_Platform_retain(struct IPlatform *self);
static int32_t PAL_POSIX_Platform_release(struct IPlatform *self);
static void PAL_POSIX_Platform_panic(struct IPlatform *self, const char *str);
static void PAL_POSIX_Platform_setDefaultAllocator(struct IPlatform *self, IAllocator *allocator);
static void PAL_POSIX_Platform_nap(struct IPlatform *self);

static struct IPlatform_vtable_ platform_vtable = {
	PAL_POSIX_Platform_queryInterface,
	PAL_POSIX_Platform_retain,
	PAL_POSIX_Platform_release,
	PAL_POSIX_Platform_panic,
	PAL_POSIX_Platform_setDefaultAllocator,
	PAL_POSIX_Platform_nap
};

PAL_POSIX_Platform PAL_POSIX_platform;

void
PAL_POSIX_Platform_init(void)
{
	memset(&PAL_POSIX_platform, 0, sizeof(PAL_POSIX_platform));
	PAL_POSIX_platform.Platform.lpVtbl = &platform_vtable;
}

/* IObject */

static int
PAL_POSIX_Platform_queryInterface(struct IPlatform *self, REFUUID iid, void **out)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

	if(0 == memcmp(iid, &IID_IObject, sizeof(UUID)))
	{
		if(*out)
		{
			IPlatform_retain(self);
			*out = &(me->Object);
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(iid, &IID_IPlatform, sizeof(UUID)))
	{
		if(*out)
		{
			IPlatform_retain(self);
			*out = &(me->Platform);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

/* The Platform object is a singleton and cannot be destroyed, therefore
 * reference-counting is not implemented
 */
static int32_t
PAL_POSIX_Platform_retain(struct IPlatform *self)
{
	UNUSED__(self);

	return 2;
}

static int32_t
PAL_POSIX_Platform_release(struct IPlatform *self)
{
	UNUSED__(self);

	return 1;
}

/* IPlatform */

static void
PAL_POSIX_Platform_panic(struct IPlatform *self, const char *string)
{
	UNUSED__(self);

	PAL_panic(string);
}

static void
PAL_POSIX_Platform_setDefaultAllocator(struct IPlatform *self, IAllocator *allocator)
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
PAL_POSIX_Platform_nap(struct IPlatform *self)
{
	UNUSED__(self);
	
	PALDebug("PAL::POSIX::Platform::nap()");
	sleep(1);
}
