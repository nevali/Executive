/* Executive Microkernel
 * Runtime Framework
 *   This framework provides low-level user-space APIs to applications, via
 *   the Executive's system call mechanism
 */

/* Copyright 2015-2022 Mo McRoberts.
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

#include "p_Runtime.h"

struct StatusMap
{
	STATUS status;
	const char *name;
	const char *msg;
};

static struct StatusMap statusMap[] = {
	{ E_SUCCESS, "%SUCCESS", "The operation completed successfully" },

	{ E_BADOBJ, "%E-BAD-OBJECT", "An invalid object descriptor was specified" },
	{ E_NOTIMPL, "%E-NOT-IMPL", "Interface is not implemented" },
	{ E_INVAL, "%E-BAD-PARAM", "Request parameter is invalid" },

	{ E_PERM, "%E-PERM", "Operation not permitted" },
	{ E_ACCESS, "%E-ACCESS", "Access denied" },
	{ E_NOENT, "%E-NOENT", "The specified object does not exist" },
	{ E_EXISTS, "%E-EXISTS", "The specified object already exists" },
	{ E_EOF, "%E-EOF", "End of file reached" },
	{ E_NOT_CONTAINER, "%E-NOT-CONTAINER", "The specified object is not a container" },
	{ E_NOMEM, "%E-NOMEM", "Out of memory" },

	{ E_IO, "%E-IO", "I/O error" },
	
	{ 0, NULL, NULL }
};

const char *
RtStatusName(STATUS s)
{
	size_t c;

	if(s >= 0)
	{
		return statusMap[0].name;
	}
	for(c = 0; statusMap[c].name; c++)
	{
		if(statusMap[c].status == s)
		{
			return statusMap[c].name;
		}
	}
	return "%E-UNKNOWN";
}

const char *
RtStatusMessage(STATUS s)
{
	size_t c;

	if(s >= 0)
	{
		return statusMap[0].msg;
	}
	for(c = 0; statusMap[c].name; c++)
	{
		if(statusMap[c].status == s)
		{
			return statusMap[c].msg;
		}
	}
	return "Unknown error";
}
