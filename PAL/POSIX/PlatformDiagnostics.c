#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_PlatformDiagnostics *)((i)->instptr)

static STATUS PAL_POSIX_PlatformDiagnostics_queryInterface(struct IPlatformDiagnostics *self, REFUUID iid, void **out);
static REFCOUNT PAL_POSIX_PlatformDiagnostics_retain(struct IPlatformDiagnostics *self);
static REFCOUNT PAL_POSIX_PlatformDiagnostics_release(struct IPlatformDiagnostics *self);

static size_t PAL_POSIX_PlatformDiagnostics_write(struct IWriteChannel *self, const uint8_t *buf, size_t nbytes);

static struct IPlatformDiagnostics_vtable_ PAL_POSIX_PlatformDiagnostics_vtable = {
	PAL_POSIX_PlatformDiagnostics_queryInterface,
	PAL_POSIX_PlatformDiagnostics_retain,
	PAL_POSIX_PlatformDiagnostics_release,
	PAL_POSIX_PlatformDiagnostics_log
};

static struct IWriteChannel_vtable_ PAL_POSIX_PlatformDiagnostics_IWriteChannel_vtable = {
	(STATUS (*)(IWriteChannel *, REFUUID, void **)) &PAL_POSIX_PlatformDiagnostics_queryInterface,
	(REFCOUNT (*)(IWriteChannel *)) &PAL_POSIX_PlatformDiagnostics_retain,
	(REFCOUNT (*)(IWriteChannel *))PAL_POSIX_PlatformDiagnostics_release,
	PAL_POSIX_PlatformDiagnostics_write
};

PAL_POSIX_PlatformDiagnostics PAL_POSIX_diagnostics = {
	{ NULL, NULL }, /* PlatformDiagnostics*/
	{ NULL, NULL }, /* Object */
	{ NULL, NULL }, /* WriteChannel */
	{
#if EXEC_BUILD_DEBUG
		LOG_TRACE
#else
		LOG_CONDITION
#endif
	}
};

void
PAL_POSIX_PlatformDiagnostics_init(void)
{
	memset(&PAL_POSIX_diagnostics, 0, sizeof(PAL_POSIX_PlatformDiagnostics));
#if EXEC_BUILD_DEBUG
	PAL_POSIX_diagnostics.data.level = LOG_TRACE;
#elif EXEC_BUILD_FREE
	PAL_POSIX_diagnostics.data.level = LOG_INFO;
#else
	PAL_POSIX_diagnostics.data.level = LOG_NOTICE;
#endif
	PAL_POSIX_diagnostics.PlatformDiagnostics.lpVtbl = &PAL_POSIX_PlatformDiagnostics_vtable;
	PAL_POSIX_diagnostics.PlatformDiagnostics.instptr = &PAL_POSIX_diagnostics;
	PAL_POSIX_diagnostics.Object.lpVtbl = (void *) &PAL_POSIX_PlatformDiagnostics_vtable;
	PAL_POSIX_diagnostics.Object.instptr = &PAL_POSIX_diagnostics;
	PAL_POSIX_diagnostics.WriteChannel.lpVtbl = &PAL_POSIX_PlatformDiagnostics_IWriteChannel_vtable;
	PAL_POSIX_diagnostics.WriteChannel.instptr = &PAL_POSIX_diagnostics;
}

static int
PAL_POSIX_PlatformDiagnostics_queryInterface(IPlatformDiagnostics *self, REFUUID riid, void **ptr)
{
	PAL_POSIX_PlatformDiagnostics *me = INTF_TO_CLASS(self);
	
	if(!memcmp(riid, &IID_IObject, sizeof(UUID)))
	{
		if(ptr)
		{
			/* no retain() because this class is a singleton */
			*ptr = &(me->Object);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IPlatformDiagnostics, sizeof(UUID)))
	{
		if(ptr)
		{
			*ptr = &(me->PlatformDiagnostics);
		}
		return E_SUCCESS;
	}
	if(!memcmp(riid, &IID_IWriteChannel, sizeof(UUID)))
	{
		if(ptr)
		{
			*ptr = &(me->WriteChannel);
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

	if(level >= PAL_POSIX_diagnostics.data.level)
	{
		fprintf(stderr, "<%d> %s\n", level, str);
	}
}

size_t
PAL_POSIX_PlatformDiagnostics_write(IWriteChannel *self, const uint8_t *buf, size_t nbytes)
{
	UNUSED__(self);

	fprintf(stderr, "\033[0;33m");
	fwrite((void *) buf, nbytes, 1, stderr);
	fprintf(stderr, "\033[0m");
	return nbytes;
}

