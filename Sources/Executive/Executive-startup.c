/* Executive Microkernel
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

#ifdef HAVE_CONFIG_H
# include "BuildConfiguration.h"
#endif

#include "p_Executive.h"

/* BOOTSTRAP SUBSYSTEM */
STATUS
Executive_startup(Executive *self)
{
	ISubsystem *subsystem;
	STATUS status;

	UNUSED__(self);
	
	ExPhaseShift(PHASE_STARTUP_EXECTASK);
	ExLog(PROGRESS_LOGLEVEL, "Preparing the Bootstrap subsystem...");

	/* Open the Bootstrap subsystem */
	if(E_SUCCESS != (status = ExOpen("/System/Subsystems/Bootstrap", &IID_ISubsystem, &subsystem)))
	{
		ExPanic("failed to open the ISubsystem interface on /System/Subsystems/Bootstrap");
		return status;
	}
	/* Ask it to start, supplying it with the root namespace interface pointer */
	if(E_SUCCESS != (status = ISubsystem_start(subsystem, executive.data.rootNS)))
	{
		ExPanic("The Bootstrap subsystem failed to start");
	}
	ExLog(PROGRESS_LOGLEVEL, "The Bootstrap subsystem has been started.");
	/* Release the reference */
	ISubsystem_release(subsystem);
	return status;
}
