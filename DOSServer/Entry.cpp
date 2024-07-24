// Entry.cpp: implementation of the CEntry class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Entry.h"
#include "glof.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntry::CEntry() {

	m_cRef = 1;
	ObjectCreated();
	IncrementLockCount();
}

CEntry::~CEntry() {

	DecrementLockCount();
	ObjectDestroyed();
}

ULONG STDMETHODCALLTYPE CEntry::AddRef() {

	InterlockedIncrement((long *) &m_cRef);
	return m_cRef;
}

ULONG STDMETHODCALLTYPE CEntry::Release() {

	unsigned long count;
	count = m_cRef - 1;

	if(InterlockedDecrement((long *) &m_cRef) == 0) {

		count = 0;
		delete this;
	}

	return count;
}

HRESULT STDMETHODCALLTYPE CEntry::QueryInterface (REFIID iid, void **ppv ) {

	HRESULT hr;

	if (IsEqualGUID(iid, IID_IUnknown) || IsEqualGUID(iid, IID_IDOSServer)) {

		*ppv = (IDOSServer *) this;
		AddRef();
		hr = S_OK;
	}
	else {

		*ppv = 0;
		hr = E_NOINTERFACE;
	}

	return hr;
}

/***************************************************************************
	List of interface functions
***************************************************************************/

HRESULT STDMETHODCALLTYPE CEntry::createBoss() {

	boss = NULL;
	boss = new CBoss();

	if (boss == NULL) {
		return E_OUTOFMEMORY;
	}
	else {
		return S_OK;
	}
}

HRESULT STDMETHODCALLTYPE CEntry::destroyBoss() {

	delete boss;
	boss = NULL;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CEntry::getBossId(int* nId) {

	*nId = boss->getId();
	return S_OK;
}

/***************************************************************************
	End of list of interface functions
***************************************************************************/
