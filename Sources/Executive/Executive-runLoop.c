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

/* RUNTIME */
STATUS
Executive_runLoop(Executive *self)
{
	UNUSED__(self);
	
	ExPhaseShift(PHASE_RUNNING);
	if(executive.data.tasker)
	{
		EXLOGF((LOG_INFO, "Launching initial tasks..."));
		IPlatform_tick(executive.data.platform);
		ITasker_yield(executive.data.tasker);
		ExPanic("Tasker unexpectedly returned control to the Executive");
	}
	return E_NOTIMPL;
}
