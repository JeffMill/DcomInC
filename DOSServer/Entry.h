// Entry.h: interface for the CEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTRY_H__DA69C75D_3EDA_4C51_B3AD_A6027E30D1A4__INCLUDED_)
#define AFX_ENTRY_H__DA69C75D_3EDA_4C51_B3AD_A6027E30D1A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\DOSProxy\DOSProxy.h"
#include "Boss.h"

class CEntry : public IDOSServer
{
private:
    unsigned long m_cRef;
   ~CEntry();
   
public:
    CEntry();
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppv);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	//
	HRESULT STDMETHODCALLTYPE createBoss();
	HRESULT STDMETHODCALLTYPE destroyBoss();
	HRESULT STDMETHODCALLTYPE getBossId(int* nId);

protected:
	CBoss* boss;
};

#endif // !defined(AFX_ENTRY_H__DA69C75D_3EDA_4C51_B3AD_A6027E30D1A4__INCLUDED_)
