// Factory.h: interface for the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTORY_H__9C30F467_A471_4708_A8F3_D0CE867A09C1__INCLUDED_)
#define AFX_FACTORY_H__9C30F467_A471_4708_A8F3_D0CE867A09C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

extern "C" const CLSID CLSID_DOSServer;

class CFactory : public IClassFactory {

private:
    unsigned long m_cRef;
	~CFactory();

public:
    CFactory();

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppv);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *punkOuter, REFIID riid, void **ppv);
	HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
};


#endif // !defined(AFX_FACTORY_H__9C30F467_A471_4708_A8F3_D0CE867A09C1__INCLUDED_)
