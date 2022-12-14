#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_PlatformDiagnostics *)((void *)(i))

static int PAL_POSIX_PlatformDiagnostics_queryInterface(struct IPlatformDiagnostics *self, REFUUID iid, void **out);
static int32_t PAL_POSIX_PlatformDiagnostics_retain(struct IPlatformDiagnostics *self);
static int32_t PAL_POSIX_PlatformDiagnostics_release(struct IPlatformDiagnostics *self);

static struct IPlatformDiagnostics_vtable_ PAL_POSIX_PlatformDiagnostics_vtable = {
	PAL_POSIX_PlatformDiagnostics_queryInterface,
	PAL_POSIX_PlatformDiagnostics_retain,
	PAL_POSIX_PlatformDiagnostics_release,
	PAL_POSIX_PlatformDiagnostics_log
};

PAL_POSIX_PlatformDiagnostics PAL_POSIX_diagnostics;

void
PAL_POSIX_PlatformDiagnostics_init(void)
{
	memset(&PAL_POSIX_diagnostics, 0, sizeof(PAL_POSIX_PlatformDiagnostics));
	PAL_POSIX_diagnostics.PlatformDiagnostics.lpVtbl = &PAL_POSIX_PlatformDiagnostics_vtable;
}

static int
PAL_POSIX_PlatformDiagnostics_queryInterface(IPlatformDiagnostics *self, REFUUID riid, void **ptr)
{
	PAL_POSIX_PlatformDiagnostics *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, &IID_IObject, sizeof(UUID)))
	{
		if(*ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(me->Object);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IPlatformDiagnostics, sizeof(UUID)))
	{
		if(*ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(me->PlatformDiagnostics);
		}
		return E_SUCCESS;
	}
	return E_NOENT;
}

static int32_t
PAL_POSIX_PlatformDiagnostics_retain(IPlatformDiagnostics *self)
{
	UNUSED__(self);
	
	/* PAL_POSIX_PlatformDiagnostics is a singleton */
	return 2;
}

static int32_t
PAL_POSIX_PlatformDiagnostics_release(IPlatformDiagnostics *self)
{
	UNUSED__(self);

	/* PAL_POSIX_PlatformDiagnostics is a singleton */
	return 1;
}

void
PAL_POSIX_PlatformDiagnostics_log(struct IPlatformDiagnostics *self, LogLevel level, const char *str)
{
	UNUSED__(self);

	fprintf(stderr, "<%d> %s\n", level, str);
}
