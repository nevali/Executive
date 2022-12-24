#ifndef SIMULATOR_INTERNAL_REGION_H_
# define SIMULATOR_INTERNAL_REGION_H_  1

# include <PAL/PAL.h>

namespace PAL
{
	namespace Simulator
	{
		class Region: public IRegion
		{
		public:
			Region(AddressSpace *addressSpace, RegionFlags flags, IRegionHolder *holder, void *ptr, size_t count);
			virtual ~Region();
		protected:
			REFCOUNT refCount_;
			AddressSpace *addressSpace_;
			IRegionHolder *holder_;
			RegionFlags flags_;
			uint8_t *base_;
			size_t count_;
			size_t pageSize_;
		public:
			/* IObject */
			virtual STATUS queryInterface(REFUUID iid, void **out);
			virtual REFCOUNT retain(void);
			virtual REFCOUNT release(void);
		public:
			/* IRegion */

			virtual RegionFlags flags(void)
			{
				return flags_;
			}

			virtual STATUS queryOwnerInterface(REFUUID iid, void **out)
			{
				return holder_->queryInterface(iid, out);
			}

			virtual uint8_t *base(void)
			{
				return base_;
			}

			virtual size_t pages(void)
			{
				return count_;
			}

			virtual size_t bytes(void)
			{
				return count_ * pageSize_;
			}
		};
	}
}

#endif /*!SIMULATOR_INTERNAL_REGION_H_*/
