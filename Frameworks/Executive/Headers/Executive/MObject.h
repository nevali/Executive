/* DO NOT EDIT: Automatically generated from MObject.idl by idl */

#ifndef MObject_FWD_DEFINED
# define MObject_FWD_DEFINED
typedef struct MObject MObject;
#endif

#ifndef MOBJECT_H_IDL_
# define MOBJECT_H_IDL_

# include <Executive/IObject.h>
# include <Executive/IAllocator.h>

/* MObject version 0.0 */

# ifndef __MObject_INTERFACE_DEFINED__
#  define __MObject_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE MObject


DECLARE_INTERFACE_(MObject, IObject)
{
	BEGIN_INTERFACE

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(STATUS, queryInterface)(THIS_ REFUUID riid, void **object) PURE;
	STDMETHOD_(REFCOUNT, retain)(THIS) PURE;
	STDMETHOD_(REFCOUNT, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* MObject */
	STDMETHOD_(STATUS, create)(THIS_ IAllocator *allocator, REFUUID iid, void **out) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define MObject_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define MObject_retain(__this) __this->lpVtbl->retain(__this)
#   define MObject_release(__this) __this->lpVtbl->release(__this)
#   define MObject_create(__this, allocator, iid, out) __this->lpVtbl->create(__this, allocator, iid, out)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__MObject_INTERFACE_DEFINED__*/


#endif /*!MOBJECT_H_IDL_*/

#if defined(INITGUID) || !defined(MOBJECT_H_GUIDS_DEFINED_)
# define MOBJECT_H_GUIDS_DEFINED_

/* IID_MObject = {8e0b94ab-06e9-4b01-8fd3-26da890a8af5} */
UUID_DEFINE(IID_MObject, 0x8e, 0x0b, 0x94, 0xab,  0x06, 0xe9, 0x4b, 0x01, 0x8f, 0xd3, 0x26, 0xda, 0x89, 0x0a, 0x8a, 0xf5);
#endif /*INITGUID || !MOBJECT_H_GUIDS_DEFINED_ */

