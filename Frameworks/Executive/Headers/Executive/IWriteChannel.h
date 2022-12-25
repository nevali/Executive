/* DO NOT EDIT: Automatically generated from IWriteChannel.idl by idl */

#ifndef IWriteChannel_FWD_DEFINED
# define IWriteChannel_FWD_DEFINED
typedef struct IWriteChannel IWriteChannel;
#endif

#ifndef IWRITECHANNEL_H_IDL_
# define IWRITECHANNEL_H_IDL_

/* Executive Microkernel
 * IWriteChannel.idl
 *
 */

/* Copyright 2015-2022 Mo McRoberts.
 *
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

/* IWriteChannel version 0.0 */

# ifndef __IWriteChannel_INTERFACE_DEFINED__
#  define __IWriteChannel_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IWriteChannel


DECLARE_INTERFACE_(IWriteChannel, IObject)
{
	BEGIN_INTERFACE

#  ifdef __cplusplus
	static const int32_t IWriteChannel_ID_send = 3;
	static const int32_t IWriteChannel_ID_write = 4;
	static const int32_t IWriteChannel_ID_writeLn = 5;

#  else /*__cplusplus*/

#  define IWriteChannel_ID_send 3
#  define IWriteChannel_ID_write 4
#  define IWriteChannel_ID_writeLn 5
#  endif /*__cplusplus*/

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IWriteChannel */
	STDMETHOD_(size_t, send)(THIS_ const uint8_t *buf, size_t nbytes) PURE;
	STDMETHOD_(size_t, write)(THIS_ const char *str) PURE;
	STDMETHOD_(size_t, writeLn)(THIS_ const char *str) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IWriteChannel_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IWriteChannel_retain(__this) __this->lpVtbl->retain(__this)
#   define IWriteChannel_release(__this) __this->lpVtbl->release(__this)
#   define IWriteChannel_send(__this, buf, nbytes) __this->lpVtbl->send(__this, buf, nbytes)
#   define IWriteChannel_write(__this, str) __this->lpVtbl->write(__this, str)
#   define IWriteChannel_writeLn(__this, str) __this->lpVtbl->writeLn(__this, str)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IWriteChannel_INTERFACE_DEFINED__*/

#  define IWriteChannel_ID_write 4
#  define IWriteChannel_ID_writeLn 5

#endif /*!IWRITECHANNEL_H_IDL_*/

#if defined(INITGUID) || !defined(IWRITECHANNEL_H_GUIDS_DEFINED_)
# define IWRITECHANNEL_H_GUIDS_DEFINED_

/* IID_IWriteChannel = {a2951acc-c69c-4ccc-8316-95161162ccb6} */
UUID_DEFINE(IID_IWriteChannel, 0xa2, 0x95, 0x1a, 0xcc,  0xc6, 0x9c, 0x4c, 0xcc, 0x83, 0x16, 0x95, 0x16, 0x11, 0x62, 0xcc, 0xb6);
#endif /*INITGUID || !IWRITECHANNEL_H_GUIDS_DEFINED_ */

