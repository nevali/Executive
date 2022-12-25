#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
# include "BuildInformation.h"
# include "ProductInformation.h"
#endif

#include "p_PAL.h"

using namespace PAL::Simulator;

static Platform platform;

void *
operator new(unsigned long nbytes)
{
	return calloc(1, nbytes);
}

void
operator delete(void *ptr)
{
	return free(ptr);
}

EXTERN_C STATUS
metaClass(REFUUID clsid, REFUUID iid, void **out)
{
	Platform::tracef("PAL::Simulator::metaClass(): clsid:" UUID_PRINTF_FORMAT " iid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid), UUID_PRINTF_ARGS(iid));
	if(out)
	{
		*out = NULL;
	}
	if(0 == memcmp(&clsid, &CLSID_PAL_Platform, sizeof(UUID)))
	{
		return platform.queryInterface(iid, out);
	}
	if(0 == memcmp(&clsid, &CLSID_PAL_MemoryManager, sizeof(UUID)))
	{
		return platform.addressSpace.queryInterface(iid, out);
	}
	if(0 == memcmp(&clsid, &CLSID_PAL_PlatformDiagnostics, sizeof(UUID)))
	{
		return platform.diagnostics.queryInterface(iid, out);
	}
	platform.logf(LOG_CONDITION, "%%E-NOENT: PAL::Simulator::metaClass(): unsupported clsid:" UUID_PRINTF_FORMAT, UUID_PRINTF_ARGS(clsid));
	return E_NOENT;
}

Platform::Platform():
	diagnostics(),
	addressSpace(),
	phase_(PHASE_UNKNOWN),
	allocator_(NULL)
{
#ifdef EXEC_BUILD_CONFIG
	log(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - Simulator Platform Adaptation Layer [" EXEC_BUILD_CONFIG " build " PRODUCT_BUILD_ID_STR "]");
#else
	log(LOG_DEBUG, PRODUCT_FULLNAME " " PACKAGE_NAME " - Simulator Platform Adaptation Layer [build " PRODUCT_BUILD_ID_STR "]");
#endif
}

/* Static utility methods */
void
Platform::log(LogLevel level, const char *str)
{
	platform.diagnostics.log(level, str);
}

void
Platform::logf(LogLevel level, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	platform.diagnostics.vlogf(level, format, args);
	va_end(args);
}

void
Platform::trace(const char *str)
{
	platform.diagnostics.log(LOG_TRACE, str);
}

void
Platform::tracef(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	platform.diagnostics.vlogf(LOG_TRACE, format, args);
	va_end(args);
}

/*PRIVATE*/
bool
Platform::createPlatformContainer(void)
{
	IMutableContainer *devices;

	/* XXX wait until we have a namespace */
	Platform::trace("PAL::Simulator::Platform::createPlatformContainer(): creating platform container");
	if(E_SUCCESS != Executive_createObjectByName("Executive::Container", IID_IMutableContainer, (void **) &(platformContainer_)))
	{
		Platform::panic("PAL::Simulator::Platform::createPlatformContainer(): Executive::createObjectByName(Executive::Container, IMutableContainer) failed");
		return false;
	}
	if(E_SUCCESS != platformContainer_->create("Devices", CLSID_Executive_Container, IID_IMutableContainer, (void **) &devices))
	{
		Platform::panic("PAL::Simulator::Platform::createPlatformContainer(): IMutableContainer::create('Devices') failed");
		return false;
	}
	devices->add("Diagnostics", CLSID_PAL_PlatformDiagnostics, static_cast<IPlatformDiagnostics *>(&diagnostics));
	devices->add("Console", CLSID_PAL_PlatformDiagnostics, static_cast<IPlatformDiagnostics *>(&diagnostics));
	devices->add("AddressSpace", CLSID_PAL_MemoryManager, static_cast<IAddressSpace *>(&addressSpace));
	devices->release();
	Platform::logf(LOG_DEBUG, "PAL::Simulator::Platform::createPlatformContainer(): platform container successfully created");
	return true;
}

/* IObject */

STATUS
Platform::queryInterface(REFUUID iid, void **out)
{
	if(out)
	{
		*out = NULL;
	}
	if(!memcmp(&iid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			*out = static_cast<IPlatform *>(this);
		}
		return E_SUCCESS;
	}
	if(!memcmp(&iid, &IID_IPlatform, sizeof(UUID)))
	{
		if(out)
		{
			*out = static_cast<IPlatform *>(this);
		}
		return E_SUCCESS;
	}
	if(!memcmp(&iid, &IID_IContainer, sizeof(UUID)))
	{
		if(!platformContainer_)
		{
			if(!createPlatformContainer())
			{
				return E_NOTIMPL;
			}
		}
		if(out)
		{
			*out = static_cast<IContainer *>(this);
		}
		return E_SUCCESS;
	}
	logf(LOG_DEBUG7, "PAL::Simulator::Platform::queryInterface(iid:" UUID_PRINTF_FORMAT ") not supported", UUID_PRINTF_ARGS(iid));
	return E_NOENT;
}

/* IPlatform */

void
Platform::panic(const char *string)
{
	log(LOG_EMERGENCY, string);
	diagnostics.panic(phase_, string);
}

void
Platform::allocatorActivated(IAllocator *allocator)
{
	tracef("PAL::Simulator::Platform::allocatorActivated(%p)", allocator);
	allocator->retain();
	if(allocator_)
	{
		allocator_->release();
	}
	allocator_ = allocator;
}

void
Platform::namespaceActivated(INamespace *ns)
{
	tracef("PAL::Simulator::Platform::namespaceActivated(%p)", ns);
	ns->retain();
	if(ns_)
	{
		ns_->release();
	}
	ns_ = ns;
}

void
Platform::nap(void)
{
	trace("PAL::Simulator::Platform::nap()");
}

void
Platform::tick(void)
{
	trace("PAL::Simulator::Platform::tick()");
}

void
Platform::phaseTransition(PHASE phase)
{
	tracef("PAL::Simulator::Platform::phaseTransition(%04x)", phase);
	if(phase == phase_)
	{
		return;
	}
	if(phase < phase_)
	{
		logf(LOG_EMERGENCY, "new phase %04x is less than previous %04x", phase, phase_);
		panic("attempt to revert to a previous system phase");
	}
#if !EXEC_BUILD_RELEASE
	if(phase / 0x1000 != phase_ / 0x1000)
	{
		logf(LOG_ALERT, ">>>> PHASE TRANSITION >>>> new system phase is %04x (previous phase was %04x)", phase, phase_);
	}
	else if(phase / 0x100 != phase_ / 0x100)
	{
		logf(LOG_ALERT, " >>> PHASE SHIFT       >>> new system phase is %04x (previous phase was %04x)", phase, phase_);
	}
	else if(phase / 0x10 != phase_ / 0x10)
	{
		logf(LOG_ALERT, "  >> PHASE JUMP         >> new system phase is %04x (previous phase was %04x)", phase, phase_);
	}
	else
	{
		logf(LOG_ALERT, "   > PHASE STEP          > new system phase is %04x (previous phase was %04x)", phase, phase_);
	}
#endif /*!EXEC_BUILD_RELEASE*/
	phase_ = phase;
}

/* IContainer */

STATUS
Platform::resolve(const char *name, IDirectoryEntry **entry)
{
	if(entry)
	{
		*entry = NULL;
	}
	if(!platformContainer_)
	{
		return E_NOTIMPL;
	}
	return platformContainer_->resolve(name, entry);
}

IIterator *
Platform::iterator(void)
{
	if(!platformContainer_)
	{
		return NULL;
	}
	return platformContainer_->iterator();
}
