

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Jan 08 21:24:31 2017
 */
/* Compiler settings for IrisIdentityOCX.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __IrisIdentityOCXidl_h__
#define __IrisIdentityOCXidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DIrisIdentityOCX_FWD_DEFINED__
#define ___DIrisIdentityOCX_FWD_DEFINED__
typedef interface _DIrisIdentityOCX _DIrisIdentityOCX;

#endif 	/* ___DIrisIdentityOCX_FWD_DEFINED__ */


#ifndef ___DIrisIdentityOCXEvents_FWD_DEFINED__
#define ___DIrisIdentityOCXEvents_FWD_DEFINED__
typedef interface _DIrisIdentityOCXEvents _DIrisIdentityOCXEvents;

#endif 	/* ___DIrisIdentityOCXEvents_FWD_DEFINED__ */


#ifndef __IrisIdentityOCX_FWD_DEFINED__
#define __IrisIdentityOCX_FWD_DEFINED__

#ifdef __cplusplus
typedef class IrisIdentityOCX IrisIdentityOCX;
#else
typedef struct IrisIdentityOCX IrisIdentityOCX;
#endif /* __cplusplus */

#endif 	/* __IrisIdentityOCX_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IrisIdentityOCX_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_IrisIdentityOCX_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IrisIdentityOCX_0000_0000_v0_0_s_ifspec;


#ifndef __IrisIdentityOCXLib_LIBRARY_DEFINED__
#define __IrisIdentityOCXLib_LIBRARY_DEFINED__

/* library IrisIdentityOCXLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_IrisIdentityOCXLib;

#ifndef ___DIrisIdentityOCX_DISPINTERFACE_DEFINED__
#define ___DIrisIdentityOCX_DISPINTERFACE_DEFINED__

/* dispinterface _DIrisIdentityOCX */
/* [uuid] */ 


EXTERN_C const IID DIID__DIrisIdentityOCX;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("936F559C-13D0-4E46-A912-13FA39D39921")
    _DIrisIdentityOCX : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DIrisIdentityOCXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DIrisIdentityOCX * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DIrisIdentityOCX * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DIrisIdentityOCX * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DIrisIdentityOCX * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DIrisIdentityOCX * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DIrisIdentityOCX * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DIrisIdentityOCX * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DIrisIdentityOCXVtbl;

    interface _DIrisIdentityOCX
    {
        CONST_VTBL struct _DIrisIdentityOCXVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DIrisIdentityOCX_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DIrisIdentityOCX_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DIrisIdentityOCX_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DIrisIdentityOCX_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DIrisIdentityOCX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DIrisIdentityOCX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DIrisIdentityOCX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DIrisIdentityOCX_DISPINTERFACE_DEFINED__ */


#ifndef ___DIrisIdentityOCXEvents_DISPINTERFACE_DEFINED__
#define ___DIrisIdentityOCXEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DIrisIdentityOCXEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DIrisIdentityOCXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("F13873FB-C4AD-4D5A-BA5A-C775A32BDC12")
    _DIrisIdentityOCXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DIrisIdentityOCXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DIrisIdentityOCXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DIrisIdentityOCXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DIrisIdentityOCXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DIrisIdentityOCXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DIrisIdentityOCXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DIrisIdentityOCXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DIrisIdentityOCXEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DIrisIdentityOCXEventsVtbl;

    interface _DIrisIdentityOCXEvents
    {
        CONST_VTBL struct _DIrisIdentityOCXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DIrisIdentityOCXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DIrisIdentityOCXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DIrisIdentityOCXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DIrisIdentityOCXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DIrisIdentityOCXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DIrisIdentityOCXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DIrisIdentityOCXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DIrisIdentityOCXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_IrisIdentityOCX;

#ifdef __cplusplus

class DECLSPEC_UUID("76E62D85-A6FF-4510-95A5-A85082B60E5A")
IrisIdentityOCX;
#endif
#endif /* __IrisIdentityOCXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


