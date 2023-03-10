/* Executive Microkernel
 *   PrivateHeaders/Executive/Internal/Resident.h
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

#ifndef EXECUTIVE_INTERNAL_RESIDENT_H_
# define EXECUTIVE_INTERNAL_RESIDENT_H_ 1

# include <Executive/IObject.h>

typedef struct Executive_Resident_Object Executive_Resident_Object;

struct Executive_Resident_Object
{
	const char *name;
	REFUUID classid;
	IObject *instance;
};

extern Executive_Resident_Object *Executive_Resident_objects(void);

#endif /*!EXECUTIVE_INTERNAL_RESIDENT_H_*/
