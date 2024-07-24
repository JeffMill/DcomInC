// Factory.cpp: implementation of the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Entry.h"
#include "Factory.h"
#include "glof.h"

extern "C" const CLSID CLSID_DOSServer 
    = {0xce5a1814, 0x7557, 0x497c, { 0x9b, 0xb9, 0xa5, 0xf3, 0xd9, 0x6f, 0xc7, 0x92}};

CFactory::~CFactory() {
	
	ObjectDestroyed();
}

CFactory::CFactory() {
	
	m_cRef = 1;
	ObjectCreated();
}

ULONG STDMETHODCALLTYPE CFactory::AddRef() {

    InterlockedIncrement((long *) &m_cRef);
    return m_cRef;
}

ULONG STDMETHODCALLTYPE CFactory::Release() {
    
	unsigned long count;
    count = m_cRef - 1;

    if(InterlockedDecrement((long *) &m_cRef) == 0) {

        count = 0;
        ObjectDestroyed();
    }

    return count;
}

HRESULT STDMETHODCALLTYPE CFactory::QueryInterface (REFIID iid, void **ppv ) {

    HRESULT hr;

    if (IsEqualGUID(iid, IID_IUnknown) || IsEqualGUID(iid, IID_IClassFactory)) {

        *ppv = this;
        AddRef();
        hr = S_OK;
    }
    else {

        *ppv = 0;
        hr = E_NOINTERFACE;
    }

    return hr;
}

HRESULT STDMETHODCALLTYPE CFactory::CreateInstance (IUnknown *punkOuter, REFIID riid, void **ppv) {
    
	HRESULT hr;
    CEntry *pEntry;

    if(punkOuter != 0) {
		
		return CLASS_E_NOAGGREGATION;
    }

    pEntry = new CEntry();
    if(pEntry != 0) {

        hr = pEntry->QueryInterface(riid, ppv);
        pEntry->Release();
    }
    else {
        
		hr = E_OUTOFMEMORY;
        *ppv = 0;
    }

    return hr;
}

HRESULT STDMETHODCALLTYPE CFactory::LockServer(BOOL fLock) {

    if (fLock == TRUE)
        IncrementLockCount();
    else
        DecrementLockCount();

    return S_OK;
}