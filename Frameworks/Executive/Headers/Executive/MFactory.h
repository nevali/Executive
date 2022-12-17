/* DO NOT EDIT: Automatically generated from MFactory.idl by idl */

#ifndef MFactory_FWD_DEFINED
# define MFactory_FWD_DEFINED
typedef struct MFactory MFactory;
#endif

#ifndef MFACTORY_H_IDL_
# define MFACTORY_H_IDL_

# include <Executive/IObject.h>

/* MFactory version 0.0 */

# ifndef __MFactory_INTERFACE_DEFINED__
#  define __MFactory_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE MFactory


DECLARE_INTERFACE_(MFactory, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* MFactory */
	STDMETHOD_(STATUS, createInstance)(THIS_ IObject *outer, REFUUID iid, void **object) PURE;
	STDMETHOD_(STATUS, lock)(THIS_ bool lock) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define MFactory_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define MFactory_retain(__this) __this->lpVtbl->retain(__this)
#   define MFactory_release(__this) __this->lpVtbl->release(__this)
#   define MFactory_createInstance(__this, outer, iid, object) __this->lpVtbl->createInstance(__this, outer, iid, object)
#   define MFactory_lock(__this, lock) __this->lpVtbl->lock(__this, lock)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__MFactory_INTERFACE_DEFINED__*/


#endif /*!MFACTORY_H_IDL_*/

#if defined(INITGUID) || !defined(MFACTORY_H_GUIDS_DEFINED_)
# define MFACTORY_H_GUIDS_DEFINED_

/* IID_MFactory = {00000001-0000-0000-c000-000000000046} */
UUID_DEFINE(IID_MFactory, 0x00, 0x00, 0x00, 0x01,  0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
#endif /*INITGUID || !MFACTORY_H_GUIDS_DEFINED_ */

