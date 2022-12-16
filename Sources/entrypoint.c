/* Executive Microkernel
 * Sources/entrypoint.c
 *   Provides an entrypoint into the Executive for the Glue to call
 */

/* Copyright (c) 2022 Mo McRoberts.
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

#include "Executive/Internal/Entry.h"
#include "PAL/PAL.h"
#include "Executive/Internal/Executive.h"

void
Executive_start(struct ExecutiveEntryParameters *params)
{
	IPlatform *platform;

	if(!params)
	{
		return;
	}
	/* Obtain an interface pointer to the PAL's Platform object */
	if(!params->PAL_metaClass)
	{
		params->PAL_metaClass = PAL_metaClass;
		if(!PAL_metaClass)
		{
			/* Neither a dynamic loader nor the Glue provided us with a contact
			 * address for a PAL
			 *
			 * This could be an ExAssert() but there's no point - we can't output
			 * anything
			 */
			return;
		}
	}
	if(params->PAL_metaClass(&CLSID_PAL_Platform, &IID_IPlatform, (void *) &platform) != E_SUCCESS)
	{
		return;
	}
	if(!platform)
	{
		return;
	}
	/* Pass the entry parameters and the Platform object to the actual
	 * implementation of the Executive core logic, built as the
	 * libExecutiveServices convenience library
	 */
	Executive_initialise(params, platform);	
}
