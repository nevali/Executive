#ifndef SIMULATOR_INTERNAL_PLATFORM_H_
# define SIMULATOR_INTERNAL_PLATFORM_H_ 1

# include <signal.h>

# include <PAL/PAL.h>
# include <Simulator/Internal/Diagnostics.h>
# include <Simulator/Internal/AddressSpace.h>

namespace PAL
{
	namespace Simulator
	{
		EXTERN_C STATUS metaClass(REFUUID clsid, REFUUID iid, void **out) PAL_LINKAGE__(metaClass, "0.0");
		EXTERN_C void panic(const char *str) PAL_LINKAGE__(__panic, "0.0");

		class Platform: public IPlatform, public IContainer
		{
		public:
			Diagnostics diagnostics;
			AddressSpace addressSpace;
		private:
			PHASE phase_;
			IAllocator *allocator_;
			IMutableContainer *platformContainer_;
			INamespace *ns_;
		public:
			/* Constructor */
			Platform();
		public:
			/* Static APIs and helpers */
			static STATUS metaClass(REFUUID clsid, REFUUID iid, void **out);
			static void log(LogLevel level, const char *str);
			static void logf(LogLevel level, const char *format, ...);
			static void trace(const char *str);
			static void tracef(const char *format, ...);
		public:
			/* IObject */
			virtual STATUS queryInterface(REFUUID iid, void **out);

			virtual REFCOUNT retain(void)
			{
				/* the Platform object is always a singleton */
				return 2;
			}

			virtual REFCOUNT release(void)
			{
				return 1;
			}
		public:
			/* IPlatform */
			virtual void panic(const char *str);
			virtual void allocatorActivated(IAllocator *allocator);
			virtual void namespaceActivated(INamespace *ns);
			virtual void nap(void);
			virtual void tick(void);
			virtual void phaseTransition(PHASE phase);
		public:
			/* IContainer */
			virtual STATUS resolve(const char *name, IDirectoryEntry **entry);
			virtual IIterator *iterator(void);
		private:
			bool createPlatformContainer(void);
			void installSignalHandlers(void);
		private:
			static void powerSignalHandler(int signo);
			static void exceptionHandler(int signo, siginfo_t *info, void *context);
		};
	}
}

#endif /*!SIMULATOR_INTERNAL_PLATFORM_H_*/
