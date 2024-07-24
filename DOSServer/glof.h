/*******************************************************

  File: glof.h

*******************************************************/

#if !defined GLOF_H
#define GLOF_H

#include <windows.h>

extern "C" {
	//
	HRESULT RegisterLocalServer(REFCLSID rclsid);
	HRESULT UnregisterLocalServer(REFCLSID rclsid);
	//
	static long g_ObjectCount = 0;
	void ObjectCreated();
	void ObjectDestroyed();
	//
	static long g_fClassRegistered = FALSE;
	static DWORD g_dwRegister = 0;
	HRESULT RegisterClassFactory();
	HRESULT RevokeClassFactory();
	//
	static long g_LockCount = 0;
	void DecrementLockCount();
	void IncrementLockCount();
}

#endif