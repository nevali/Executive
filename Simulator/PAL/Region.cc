
/* Copyright (c) 2015-2022 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_PAL.h"

using namespace PAL::Simulator;

Region::Region(AddressSpace *addressSpace, RegionFlags flags, IRegionHolder *holder, void *base, size_t count):
	refCount_(1),
	addressSpace_(addressSpace),
	holder_(holder),
	flags_(flags),
	base_((uint8_t *) base),
	count_(count)
{
	pageSize_ = addressSpace->pageSize();
}

Region::~Region()
{
	if(base_)
	{
		::munmap(base_, count_ * pageSize_);
	}

}

/* IObject */

int
Region::queryInterface(REFUUID iid, void **out)
{
	if(0 == memcmp(&iid, &IID_IObject, sizeof(UUID)))
	{
		if(out)
		{
			IObject *me = static_cast<IObject *>(this);
			me->retain();
			*out = me;
		}
		return E_SUCCESS;
	}
	if(0 == memcmp(&iid, &IID_IRegion, sizeof(UUID)))
	{
		if(out)
		{
			IRegion *me = static_cast<IRegion *>(this);
			me->retain();
			*out = me;
		}
		return E_SUCCESS;
	}
	/* Unsupported interface*/
	return E_NOENT;
}

REFCOUNT
Region::retain()
{
	/* XXX atomics */
	refCount_++;
	return refCount_;
}

REFCOUNT
Region::release()
{
	/* XXX atomics */
	refCount_--;
	if(!refCount_)
	{
		delete this;
		return 0;
	}
	return refCount_;
}
