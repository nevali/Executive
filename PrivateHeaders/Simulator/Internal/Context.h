#ifndef SIMULATOR_INTERNAL_CONTEXT_H_
# define SIMULATOR_INTERNAL_CONTEXT_H_ 1

# include <PAL/PAL.h>

namespace PAL
{
	namespace Simulator
	{
		class AddressSpace;
		class Context;

		struct IContextPrivate: public IObject
		{
			virtual Context *self(void) = 0;
		};

		class Context: public IContext, public IContextPrivate
		{
		public:
			Context(AddressSpace *addressSpace);
			virtual ~Context();
			void setup(void);
		protected:
			friend class AddressSpace;

			REFCOUNT refCount_;
			AddressSpace *addressSpace;
			IThread *thread;
			ThreadEntrypoint entry;
			uint8_t *stackBase;
			size_t stackSize;
			jmp_buf jb;
		public:
			/* IObject */
			virtual STATUS queryInterface(REFUUID iid, void **out);
			virtual REFCOUNT retain(void);
			virtual REFCOUNT release(void);
		public:
			/* IContext */
			virtual bool swap(IContext *to);
		public:
			/* IContextPrivate */
			virtual Context *self(void)
			{
				return this;
			}
		private:
			static void trampoline(int signo);
			static void bootstrap(void);
			void _start(void);
		};
	}
}

#endif /*!SIMULATOR_INTERNAL_CONTEXT_H_*/
