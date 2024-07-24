

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Sun Dec 24 18:28:47 2006
 */
/* Compiler settings for DOSProxy.idl:
    Oi, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DOSProxy_h__
#define __DOSProxy_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDOSServer_FWD_DEFINED__
#define __IDOSServer_FWD_DEFINED__
typedef interface IDOSServer IDOSServer;
#endif 	/* __IDOSServer_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IDOSServer_INTERFACE_DEFINED__
#define __IDOSServer_INTERFACE_DEFINED__

/* interface IDOSServer */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDOSServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7CCB1299-AC38-4cbc-A48E-E924BE10678C")
    IDOSServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE createBoss( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE destroyBoss( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getBossId( 
            /* [out] */ int *nId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDOSServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDOSServer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDOSServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDOSServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *createBoss )( 
            IDOSServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *destroyBoss )( 
            IDOSServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *getBossId )( 
            IDOSServer * This,
            /* [out] */ int *nId);
        
        END_INTERFACE
    } IDOSServerVtbl;

    interface IDOSServer
    {
        CONST_VTBL struct IDOSServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOSServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOSServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOSServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDOSServer_createBoss(This)	\
    (This)->lpVtbl -> createBoss(This)

#define IDOSServer_destroyBoss(This)	\
    (This)->lpVtbl -> destroyBoss(This)

#define IDOSServer_getBossId(This,nId)	\
    (This)->lpVtbl -> getBossId(This,nId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDOSServer_createBoss_Proxy( 
    IDOSServer * This);


void __RPC_STUB IDOSServer_createBoss_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDOSServer_destroyBoss_Proxy( 
    IDOSServer * This);


void __RPC_STUB IDOSServer_destroyBoss_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDOSServer_getBossId_Proxy( 
    IDOSServer * This,
    /* [out] */ int *nId);


void __RPC_STUB IDOSServer_getBossId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDOSServer_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


