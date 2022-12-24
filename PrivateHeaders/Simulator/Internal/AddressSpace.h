#ifndef SIMULATOR_INTERNAL_ADDRESSSPACE_H_
# define SIMULATOR_INTERNAL_ADDRESSSPACE_H_ 1

# include <PAL/PAL.h>

namespace PAL
{
	namespace Simulator
	{
		class AddressSpace: public IAddressSpace
		{
		public:
			/* Constructor */
			AddressSpace();
		public:
			/* IObject */
			virtual STATUS queryInterface(REFUUID iid, void **out);

			virtual REFCOUNT retain(void)
			{
				return 2;
			}

			virtual REFCOUNT release(void)
			{
				return 1;
			}

			/* IAddressSpace */

			virtual int regionFromPointer(void *ptr, IRegion **out)
			{
				UNUSED__(ptr);

				if(out)
				{
					*out = NULL;
				}
				return E_NOTIMPL;
			}

			virtual int pageSize(void)
			{
				return pageSize_;
			}

			virtual int obtainRegion(size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **out)
			{
				if(flags & RF_TRANSIENT)
				{
					return obtainTransientRegion(count, flags, owner, out);
				}
				return E_NOMEM;
			}

			virtual int obtainTransientRegion(size_t count, RegionFlags flags, IRegionHolder *owner, IRegion **out);
			virtual STATUS createContext(IThread *thread, void *stackBase, size_t stackSize, ThreadEntrypoint ip, IContext **out);
		private:
			int pageSize_;
		};
	}
}

#endif /*!SIMULATOR_INTERNAL_ADDRESSSPACE_H_*/
