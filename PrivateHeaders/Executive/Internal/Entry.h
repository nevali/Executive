/* Executive Microkernel
 *   PrivateHeaders/Executive/Internal/Entry.h
 */

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

#ifndef EXECUTIVE_INTERNAL_ENTRY_H_
# define EXECUTIVE_INTERNAL_ENTRY_H_

# include <Executive/Linkage.h>
# include <Executive/Types.h>
# include <Executive/Errors.h>
# include <Executive/UUID.h>

typedef enum
{
	EEF_HAVE_ARGS = (1<<0),
	EEF_HAVE_ENVIRON = (1<<1),
	EEF_HAVE_PAL_METACLASS = (1<<2),
	EEF_HAVE_HOSTID = (1<<3),
	EEF_HAVE_HOSTUUID = (1<<4),
	EEF_SIMULATOR = (1<<5)
} ExecutiveEntryFlags;

struct ExecutiveEntryParameters
{
	ExecutiveEntryFlags flags;
	int argc;
	char **argv;
	char **environ;
	int (*PAL_metaClass)(REFUUID clsid, REFUUID iid, void **out);
	char hostid[64];
	UUID hostuuid;
};

void Executive_start(struct ExecutiveEntryParameters *params) EXEC_LINKAGE__(__start, "0.0");

#endif /*EXECUTIVE_INTERNAL_ENTRY_H_*/