/**************************************************************

	File: glof.cpp

**************************************************************/

#include "glof.h"
#include <stdio.h>
#include "Factory.h"

HRESULT RegisterLocalServer(REFCLSID rclsid)
{
    HRESULT hr;
    LONG error;
    HKEY hKeyCLSID;         // key for ...\Classes\CLSID
    HKEY hKeyClassID;
    HKEY hKey;              // current key
    DWORD dwDisposition;
    char szServer[MAX_PATH];
    char szClassID[39];
    unsigned long length;

    length = GetModuleFileNameA(0, szServer, sizeof(szServer));

    if(length == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return hr;
    }

    //create the CLSID key
    error = RegCreateKeyExA(
            HKEY_CLASSES_ROOT, 
            "CLSID",
            0, 
            "REG_SZ", 
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            0,
            &hKeyCLSID,
            &dwDisposition);

    if(!error)
    {
        //convert the class ID to a registry key name.
        sprintf_s(szClassID, ARRAYSIZE(szClassID), "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                rclsid.Data1, rclsid.Data2, rclsid.Data3,
                rclsid.Data4[0], rclsid.Data4[1],
                rclsid.Data4[2], rclsid.Data4[3],
                rclsid.Data4[4], rclsid.Data4[5],
                rclsid.Data4[6], rclsid.Data4[7]);
  
        //create key for the server class
        error = RegCreateKeyExA(hKeyCLSID, 
                                szClassID,
                                0, 
                                "REG_SZ", 
                                REG_OPTION_NON_VOLATILE,
                                KEY_ALL_ACCESS,
                                0,
                                &hKeyClassID,
                                &dwDisposition);

        if(!error)
        {
            //create LocalServer32 key.
            error = RegCreateKeyExA(hKeyClassID,           
                                    "LocalServer32",
                                    0, 
                                    "REG_SZ", 
                                    REG_OPTION_NON_VOLATILE,
                                    KEY_ALL_ACCESS,
                                    0,            
                                    &hKey,
                                    &dwDisposition);

            if(!error)
            {
                //Set the server name.
                error = RegSetValueExA(hKey, 
                                       "", 
                                       0, 
                                       REG_SZ, 
                                       (const unsigned char *)szServer,
                                       strlen(szServer) + 1);

                RegFlushKey(hKey);
                RegCloseKey(hKey);
            }
            RegCloseKey(hKeyClassID);
        }
        RegCloseKey(hKeyCLSID);
    }

    if(!error)
        hr = S_OK;
    else
        hr = HRESULT_FROM_WIN32(error);

    return hr;
}

HRESULT UnregisterLocalServer(REFCLSID rclsid)
{
    HRESULT hr;
    HKEY hKeyCLSID;
    HKEY hKeyClassID;
    long error;
    char szClassID[39];

    //open the CLSID key
    error = RegOpenKeyExA(
        HKEY_CLASSES_ROOT, 
        "CLSID",
        0, 
        KEY_ALL_ACCESS,
        &hKeyCLSID);

    if(!error)
    { 
    //convert the class ID to a registry key name.
    sprintf_s(szClassID, ARRAYSIZE(szClassID), "{%08lX-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            rclsid.Data1, rclsid.Data2, rclsid.Data3,
            rclsid.Data4[0], rclsid.Data4[1],
            rclsid.Data4[2], rclsid.Data4[3],
            rclsid.Data4[4], rclsid.Data4[5],
            rclsid.Data4[6], rclsid.Data4[7]);

        //open registry key for class ID string
        error = RegOpenKeyExA(
            hKeyCLSID, 
            szClassID,
            0, 
            KEY_ALL_ACCESS,
            &hKeyClassID);

        if(!error)
        {
            //delete LocalServer32 key. 
            error = RegDeleteKeyA(hKeyClassID, "LocalServer32");
            RegCloseKey(hKeyClassID);          
        }

        error = RegDeleteKeyA(hKeyCLSID, szClassID);
        RegCloseKey(hKeyCLSID);
    }

    if(!error)
        hr = S_OK;
    else
        hr = HRESULT_FROM_WIN32(error);

    return hr;
}

void ObjectCreated()
{
    InterlockedIncrement(&g_ObjectCount);
}

void ObjectDestroyed()
{
    if(InterlockedDecrement(&g_ObjectCount) == 0)
    {
        //When the last object is released, post a quit message.
        PostQuitMessage(0);
    }
}

HRESULT RegisterClassFactory()
{
    HRESULT hr;
    CFactory *pFactory;

    if(InterlockedExchange(&g_fClassRegistered, TRUE) == FALSE)
    {
        pFactory = new CFactory;
        
        if(pFactory != 0)
        {
            hr = CoRegisterClassObject(CLSID_DOSServer,
	   	        		               (IUnknown *) pFactory,
	    	        	               CLSCTX_LOCAL_SERVER,
		    	                       REGCLS_MULTIPLEUSE,
			                           &g_dwRegister);
          	pFactory->Release();
        }
        else
        {
           hr = E_OUTOFMEMORY;
        }
    }
    else
    {
        hr = S_OK;
    }
    return hr;  
}

HRESULT RevokeClassFactory()
{
    HRESULT hr;

    if(InterlockedExchange(&g_fClassRegistered, FALSE) == TRUE)
    {
        hr = CoRevokeClassObject(g_dwRegister);
    }
    else
    {
        hr = S_OK;
    }
    return hr;
}

void DecrementLockCount()
{
    //Decrement the lock count.
    if(InterlockedDecrement(&g_LockCount) == 0)
    {
        //When the lock count is decremented to zero,
        //revoke the class factory.
        RevokeClassFactory();
    }
}

void IncrementLockCount()
{
    if(g_LockCount == 0)
    {
        //Increment the lock count.
        InterlockedIncrement(&g_LockCount);

        //Reregister the class factory if necessary.
        RegisterClassFactory();
    }
    else
    {
        //Increment the lock count.
        InterlockedIncrement(&g_LockCount);
    }
}