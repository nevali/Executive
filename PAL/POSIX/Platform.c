#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include "p_POSIX.h"

#define INTF_TO_CLASS(i) (PAL_POSIX_Platform *)((void *)(i)->instptr)

static void PAL_POSIX_setEnvironmentLogLevel(void);

static STATUS PAL_POSIX_Platform_queryInterface(IObject *self, REFUUID iid, void **out);
static REFCOUNT PAL_POSIX_Platform_retain(IObject *self);
static REFCOUNT PAL_POSIX_Platform_release(IObject *self);
static void PAL_POSIX_Platform_panic(IPlatform *self, const char *str);
static void PAL_POSIX_Platform_allocatorActivated(IPlatform *self, IAllocator *allocator);
static void PAL_POSIX_Platform_namespaceActivated(IPlatform *self, INamespace *ns);
static void PAL_POSIX_Platform_nap(IPlatform *self);
static void PAL_POSIX_Platform_tick(IPlatform *self);
static void PAL_POSIX_Platform_phaseTransition(IPlatform *self, PHASE phase);
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
	PAL_POSIX_Platform_nap,
	PAL_POSIX_Platform_tick,
	PAL_POSIX_Platform_allocatorActivated,
	PAL_POSIX_Platform_namespaceActivated,
	PAL_POSIX_Platform_phaseTransition
};
/* IContainer */
static struct IContainer_vtable_ platform_IContainer_vtable = {
	(STATUS (*)(IContainer *, REFUUID, void **)) &PAL_POSIX_Platform_queryInterface,
	(REFCOUNT (*)(IContainer *)) &PAL_POSIX_Platform_retain,
	(REFCOUNT (*)(IContainer *)) &PAL_POSIX_Platform_release,
	PAL_POSIX_Platform_resolve,
	PAL_POSIX_Platform_iterator
};

static PAL_POSIX_Platform PAL_POSIX_platform;
PAL_POSIX_Platform *PAL_POSIX = NULL;
PHASE PAL_POSIX_phase = PHASE_UNKNOWN;

void
PAL_POSIX_Platform_init(void)
{
	if(PAL_POSIX)
	{
		return;
	}
#if EXEC_BUILD_RELEASE
	PAL_POSIX_platform.data.logLevel = LOG_NOTICE;
#elif EXEC_BUILD_DEBUG
	PAL_POSIX_platform.data.logLevel = LOG_INFO;
#else
	PAL_POSIX_platform.data.logLevel = LOG_CONDITION;
#endif
	PAL_POSIX_setEnvironmentLogLevel();
	/* do this early so that diagnostics can check the log level */
	PAL_POSIX = &PAL_POSIX_platform;
#ifdef EXEC_BUILD_CONFIG
	PALLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - POSIX Platform Adaptation Layer [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	PALLog(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - POSIX Platform Adaptation Layer [build " PRODUCT_BUILD_ID_STR "]");
#endif
	PALLOGF((LOG_DEBUG6, "PAL::POSIX::Platform::init(): initialising PAL metaclasses"));
	PAL_POSIX_platform.Object.lpVtbl = &platform_IObject_vtable;
	PAL_POSIX_platform.Object.instptr = &PAL_POSIX_platform;
	PAL_POSIX_platform.Platform.lpVtbl = &platform_IPlatform_vtable;
	PAL_POSIX_platform.Platform.instptr = &PAL_POSIX_platform;
	PAL_POSIX_platform.Container.lpVtbl = &platform_IContainer_vtable;
	PAL_POSIX_platform.Container.instptr = &PAL_POSIX_platform;
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX = %p, <IObject> = %p", &(PAL_POSIX_platform), &(PAL_POSIX_platform.Object)));
	PAL_POSIX_AddressSpace_init();
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX::addressSpace<IAddressSpace> = %p", PAL_POSIX_platform.data.addressSpace));
#if FEATURE_PAL_DIAGNOSTICS
	PAL_POSIX_PlatformDiagnostics_init();
	PALLOGF((LOG_DEBUG7, "- PAL::POSIX::diagnostics<IPlatformDiagnostics> = %p", PAL_POSIX_platform.data.diagnostics));
#endif
#if FEATURE_CONSOLE
	PAL_POSIX_Console_init();
#endif
	PALLOGF((LOG_DEBUG6, "PAL::POSIX::init(): early initialisation complete"));
}

/* INTERNAL */
void
PAL_POSIX_Platform_setAddressSpace(IAddressSpace *addressSpace)
{
	PALLOGF((LOG_TRACE, "PAL::POSIX::Platform::setAddressSpace(%p): kernel address space object is available", addressSpace));
	if(!PAL_POSIX_platform.data.addressSpace)
	{
		PAL_POSIX_platform.data.addressSpace = addressSpace;
	}
}

/*INTERNAL*/
void
PAL_POSIX_Platform_setDiagnostics(IPlatformDiagnostics *diag)
{
	UNUSED__(diag);

#if FEATURE_PAL_DIAGNOSTICS
	if(!PAL_POSIX_platform.data.diagnostics)
	{
		PAL_POSIX_platform.data.diagnostics = diag;
	}
	PALLOGF((LOG_TRACE, "PAL::POSIX::Platform::setDiagnostics(): PlatformDiagnostics object is available"));
#endif
}

/*INTERNAL*/
void
PAL_POSIX_Platform_setConsole(PAL_POSIX_Console *console)
{
	UNUSED__(console);

#if FEATURE_CONSOLE
	if(!PAL_POSIX_platform.data.console)
	{
		PAL_POSIX_platform.data.console = console;
	}
	PALLOGF((LOG_TRACE, "PAL::POSIX::Platform::setConsole(): Console object is available"));
#endif
}

/* IObject */

static STATUS
PAL_POSIX_Platform_queryInterface(IObject *self, REFUUID iid, void **out)
{
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
		if(out)
		{
			*out = &(PAL_POSIX_platform.Container);
		}
		PALLOGF((LOG_DEBUG7, "PAL::POSIX::Platform::queryInterface(): returning PAL::POSIX::Platform<IContainer>"));
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
PAL_POSIX_Platform_allocatorActivated(IPlatform *self, IAllocator *allocator)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

	IAllocator_retain(allocator);
	if(me->data.allocator)
	{
		IAllocator_release(me->data.allocator);
	}
	me->data.allocator = allocator;
	PALDebug("PAL::POSIX::Platform::allocatorActivated(): new default allocator activated");
}

static void
PAL_POSIX_Platform_namespaceActivated(IPlatform *self, INamespace *ns)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);
	IMutableContainer *devices;
	STATUS status;

	INamespace_retain(ns);
	if(me->data.rootNS)
	{
		INamespace_release(me->data.rootNS);
	}
	me->data.rootNS = ns;
	PALDebug("PAL::POSIX::Platform::namespaceActivated(): new root namespace activated");
	if(me->data.platformContainer)
	{
		IMutableContainer_release(me->data.platformContainer);
	}
	PALDebug("PAL::POSIX::Platform::namespaceActivated(): creating platform container");
	if(E_SUCCESS != (status = Executive_createObject(&CLSID_Executive_Container, &IID_IMutableContainer, (void **) &(PAL_POSIX_platform.data.platformContainer))))
	{
		PAL_panic("PAL::POSIX::Platform::namespaceActivated(): Executive::createObjectByName(Executive::Container, IMutableContainer) failed");
	}
	if(E_SUCCESS != (status = IMutableContainer_create((PAL_POSIX_platform.data.platformContainer), "Devices", &CLSID_Executive_Container, &IID_IMutableContainer, (void **) &devices)))
	{
		PAL_panic("PAL::POSIX::Platform::namespaceActivated(): IMutableContainer::create('Devices') failed");
	}
#if FEATURE_PAL_DIAGNOSTICS
	if(PAL_POSIX_platform.data.diagnostics)
	{
		IMutableContainer_add(devices, "Diagnostics", &CLSID_PAL_PlatformDiagnostics, (IObject *) (void *) PAL_POSIX_platform.data.diagnostics);
	}
#endif /*FEATURE_PAL_DIAGNOSTICS*/
#if FEATURE_CONSOLE
	if(PAL_POSIX_platform.data.console)
	{
		IMutableContainer_add(devices, "Console", &CLSID_PAL_PlatformDiagnostics, &(PAL_POSIX_platform.data.console->Object));
	}
#endif /*FEATURE_CONSOLE*/
	IMutableContainer_add(devices, "AddressSpace", &CLSID_PAL_MemoryManager, (IObject *) (void *) PAL_POSIX_platform.data.addressSpace);
	IMutableContainer_release(devices);
	PALDebug("PAL::POSIX::Platform::namespaceActivated(): population of Platfom container complete");
}

static void
PAL_POSIX_Platform_nap(IPlatform *self)
{
	UNUSED__(self);
	
	PALTrace("PAL::POSIX::Platform::nap()");
	sleep(1);
}

static void
PAL_POSIX_Platform_tick(IPlatform *self)
{
	UNUSED__(self);
	
	PALTrace("PAL::POSIX::Platform::tick()");
	sleep(1);
}

static void
PAL_POSIX_Platform_phaseTransition(IPlatform *me, PHASE phase)
{
	UNUSED__(me);
#if FEATURE_DEBUG_PHASING
	PALLOGF((LOG_TRACE, "PAL::POSIX::Platform::phaseTransition(%04x)", phase));
	if(phase == PAL_POSIX_phase)
	{
		return;
	}
	if(phase < PAL_POSIX_phase)
	{
		PALLOGF((LOG_EMERGENCY, "new phase %04x is less than previous %04x", phase, PAL_POSIX_phase));
		PAL_panic("attempt to revert to a previous system phase");
	}
#if !EXEC_BUILD_RELEASE
	if(phase / 0x1000 != PAL_POSIX_phase / 0x1000)
	{
		PALLOGF((LOG_INFO, ">>>> PHASE TRANSITION >>>> new system phase is %04x (previous phase was %04x)", phase, PAL_POSIX_phase));
#if EXEC_BUILD_DEBUG
		fprintf(stderr, "\n\n"
			"++===================================================================++\n"
			"||           S Y S T E M    P H A S E    T R A N S I T I O N         ||\n"
			"++===================================================================++\n"
			"    NEW PHASE:       %04x\n"
			"    PREVIOUS PHASE:  %04x\n"
			"=======================================================================\n",
			phase, PAL_POSIX_phase);
#endif
	}
	else if(phase / 0x100 != PAL_POSIX_phase / 0x100)
	{
		PALLOGF((LOG_DEBUG, " >>> PHASE SHIFT       >>> new system phase is %04x (previous phase was %04x)", phase, PAL_POSIX_phase));
#if EXEC_BUILD_DEBUG
		fprintf(stderr, "\n"
			"||   P H A S E   S H I F T  > > >  NEW phase: %04x, previous phase = %04x\n"
			"\n",
			phase, PAL_POSIX_phase);
#endif
	}
	else if(phase / 0x10 != PAL_POSIX_phase / 0x10)
	{
		PALLOGF((LOG_DEBUG2, "  >> PHASE JUMP         >> new system phase is %04x (previous phase was %04x)", phase, PAL_POSIX_phase));
	}
	else
	{
		PALLOGF((LOG_DEBUG3, "   > PHASE STEP          > new system phase is %04x (previous phase was %04x)", phase, PAL_POSIX_phase));
	}
#endif

#endif /*FEATURE_DEBUG_PHASING*/
	PAL_POSIX_phase = phase;
}

/* IContainer */
static STATUS
PAL_POSIX_Platform_resolve(IContainer *self, const char *name, IDirectoryEntry **entry)
{
	PAL_POSIX_Platform *me = INTF_TO_CLASS(self);

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

	if(!me->data.platformContainer)
	{
		return NULL;
	}
	return IMutableContainer_iterator(me->data.platformContainer);
}

/*INTERNAL*/
static void
PAL_POSIX_setEnvironmentLogLevel(void)
{
	const char *level;
	size_t c;
	const struct { const char *name; LogLevel level; } levels[] = {
		{ "emerg", LOG_EMERGENCY },
		{ "emergency", LOG_EMERGENCY },
		{ "alert", LOG_ALERT },
		{ "crit", LOG_CRITICAL },
		{ "critical", LOG_CRITICAL },
		{ "notice", LOG_NOTICE },
		{ "err", LOG_ERROR },
		{ "error", LOG_ERROR },
		{ "warn", LOG_WARNING },
		{ "warning", LOG_WARNING },
		{ "info", LOG_INFO },
		{ "condition", LOG_CONDITION },
		{ "cond", LOG_CONDITION },
		{ "debug", LOG_DEBUG },
		{ "debug2", LOG_DEBUG2 },
		{ "debug3", LOG_DEBUG3 },
		{ "debug4", LOG_DEBUG4 },
		{ "debug5", LOG_DEBUG5 },
		{ "debug6", LOG_DEBUG6 },
		{ "debug7", LOG_DEBUG7 },
		{ "trace", LOG_TRACE },
		{ NULL, 0 }
	};
	if(NULL != (level = getenv("EXEC_PAL_LOGLEVEL")))
	{
		PALLOGF((LOG_DEBUG, "PAL::POSIX::Platform: EXEC_PAL_LOGLEVEL='%s'\n", level));
		for(c = 0; levels[c].name; c++)
		{
			if(!strcasecmp(levels[c].name, level))
			{
				PAL_POSIX_platform.data.logLevel = levels[c].level;
				PALLOGF((LOG_INFO, "Log level set to '%s' (%d) via EXEC_PAL_LOGLEVEL environment variable", level, levels[c].level));
				return;
			}
		}
		fprintf(stderr, "POSIX: WARNING: unknown log level '%s'\n", level);
	}
}
