/* Executive Microkernel
 *   PrivateHeaders/Executive/Internal/Despatch.h
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

#ifndef EXECUTIVE_INTERNAL_DESPATCH_H_
# define EXECUTIVE_INTERNAL_DESPATCH_H_

# include <Executive/Types.h>
# include <Executive/Linkage.h>
# include <Executive/MObject.h>

typedef union ExecutiveDespatch ExecutiveDespatch;

typedef enum
{
	EDT_SYSCALL = 1,
	EDT_INTERRUPT = 2,
	EDT_EXCEPTION = 3,
	EDT_TRAP = 4,
	EDT_TIMER = 5,
	EDT_WATCHDOG = 6
} ExecutiveDespatchType;

union ExecutiveDespatch
{
	ExecutiveDespatchType type;
	struct
	{
		ExecutiveDespatchType type;
		uintptr_t arg[16];
		STATUS status;
	} syscall;
	struct
	{
		ExecutiveDespatchType type;
	} interrupt;
	struct
	{
		ExecutiveDespatchType type;
	} exception;
	struct
	{
		ExecutiveDespatchType type;
	} trap;
	struct
	{
		ExecutiveDespatchType type;
	} timer;
	struct
	{
		ExecutiveDespatchType type;
	} watchdog;
};

EXTERN_C MObject Executive_Despatch_Context_MObject;

EXTERN_C void Executive_despatch(ExecutiveDespatch *parameters) EXEC_LINKAGE__(despatch, "0.0");

#endif /*!EXECUTIVE_INTERNAL_DESPATCH_H_*/
