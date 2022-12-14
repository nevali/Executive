/* DO NOT EDIT: Automatically generated from IPlatformDiagnostics.idl by idl */

#ifndef IPlatformDiagnostics_FWD_DEFINED
# define IPlatformDiagnostics_FWD_DEFINED
typedef struct IPlatformDiagnostics IPlatformDiagnostics;
#endif

#ifndef IPLATFORMDIAGNOSTICS_H_IDL_
# define IPLATFORMDIAGNOSTICS_H_IDL_

/* Executive Microkernel
 * IPlatformDiagnostics.idl
 *   Defines the diagnostic interface the PAL provides to the Executive
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
# include <Executive/IObject.h>

/* IPlatformDiagnostics version 0.0 */

# ifndef __IPlatformDiagnostics_INTERFACE_DEFINED__
#  define __IPlatformDiagnostics_INTERFACE_DEFINED__
typedef enum 
{
	 	LOG_EMERG = 99,
	 	LOG_EMERGENCY = LOG_EMERG,
	 	LOG_ALERT = 50,
	 	LOG_CRIT = 40,
	 	LOG_CRITICAL = LOG_CRIT,
	 	LOG_ERR = 30,
	 	LOG_ERROR = LOG_ERR,
	 	LOG_WARN = 20,
	 	LOG_WARNING = LOG_WARN,
	 	LOG_NOTICE = 10,
	 	LOG_INFO = 0,
	 	LOG_CONDITION = -5,
	 	LOG_DEBUG = -10,
	 	LOG_DEBUG2 = -20,
	 	LOG_DEBUG3 = -30,
	 	LOG_DEBUG4 = -40,
	 	LOG_DEBUG5 = -50,
	 	LOG_DEBUG6 = -60,
	 	LOG_DEBUG7 = -70,
	 	LOG_TRACE = -99
}  LogLevel;
#  undef INTEFACE
#  define INTERFACE IPlatformDiagnostics


DECLARE_INTERFACE_(IPlatformDiagnostics, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IPlatformDiagnostics */
	STDMETHOD_(void, log)(THIS_ LogLevel level, const char *string) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IPlatformDiagnostics_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IPlatformDiagnostics_retain(__this) __this->lpVtbl->retain(__this)
#   define IPlatformDiagnostics_release(__this) __this->lpVtbl->release(__this)
#   define IPlatformDiagnostics_log(__this, level, string) __this->lpVtbl->log(__this, level, string)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IPlatformDiagnostics_INTERFACE_DEFINED__*/


#endif /*!IPLATFORMDIAGNOSTICS_H_IDL_*/

#if defined(INITGUID) || !defined(IPLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_)
# define IPLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_

/* IID_IPlatformDiagnostics = {5915ac8d-93d9-48e6-bbdf-d6ecdd1a8faf} */
UUID_DEFINE(IID_IPlatformDiagnostics, 0x59, 0x15, 0xac, 0x8d,  0x93, 0xd9, 0x48, 0xe6, 0xbb, 0xdf, 0xd6, 0xec, 0xdd, 0x1a, 0x8f, 0xaf);
#endif /*INITGUID || !IPLATFORMDIAGNOSTICS_H_GUIDS_DEFINED_ */

