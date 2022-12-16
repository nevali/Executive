/* DO NOT EDIT: Automatically generated from UUID.idl by idl */

#ifndef UUID_H_IDL_
# define UUID_H_IDL_

/* Executive Microkernel
 * UUID.idl
 *   Defines the UUID type used to identify interfaces, classes, and
 *   many other types of object
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
# include <Executive/Types.h>

/* UUID version 0.0 */

# ifndef __UUID_INTERFACE_DEFINED__
#  define __UUID_INTERFACE_DEFINED__
#if 0
typedef unsigned char uuid_t[16];
typedef const uuid_t REFUUID;
#endif
typedef union UUID 
{ 
	struct 
	{ 
		uint32_t time_low; 
		uint16_t time_mid; 
		uint16_t time_hi_and_version; 
		uint8_t clock_seq_hi_and_reserved; 
		uint8_t clock_seq_low; 
		uint8_t node[6]; 
	} uuid; 
	uint8_t bytes[16]; 
	struct 
	{		uint32_t d1; 
		uint32_t d2; 
		uint32_t d3; 
		uint32_t d4; 
	} d; 
	struct 
	{ 
		uint32_t data1; 
		uint16_t data2; 
		uint16_t data3; 
		uint8_t data4[8]; 
	} guid; 
} UUID;
#ifndef _UUID_T
#define _UUID_T
typedef union UUID uuid_t;
#endif
#ifdef __cplusplus
#define REFUUID const union UUID &
#else
#define REFUUID const union UUID * const
#endif
#define UUID_PRINTF_FORMAT "{ %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x }"
#define UUID_PRINTF_ARGS(uu) (uu)->uuid.time_low, (uu)->uuid.time_mid, (uu)->uuid.time_hi_and_version, (uu)->uuid.clock_seq_hi_and_reserved, (uu)->uuid.clock_seq_low, (uu)->uuid.node[0], (uu)->uuid.node[1], (uu)->uuid.node[2], (uu)->uuid.node[3], (uu)->uuid.node[4], (uu)->uuid.node[5]
#  undef INTERFACE
# endif /*!__UUID_INTERFACE_DEFINED__*/

#include <Executive/initguid.h>

#endif /*!UUID_H_IDL_*/

