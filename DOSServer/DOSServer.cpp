/**********************************************************
	
	  File: DOSServer.cpp

**********************************************************/


#include <stdio.h>
#include "..\DOSProxy\DOSProxy.h"
#include "..\DOSProxy\DOSProxy_i.c"
#include "Factory.h"
#include "glof.h"

int _cdecl main(int argc, char *argv[])
{
    HRESULT hr = S_OK;
    int i;
    BOOL fRegisterServer = FALSE;
    BOOL fUnregisterServer = FALSE;
    BOOL fEmbedding = FALSE;
    BOOL fHelp = FALSE;
    MSG msg;

    for (i = 1; i < argc; i++)
    {
        if (stricmp( argv[i], "-Embedding" ) == 0)
        {
            //This server has been activated by OLE.
            fEmbedding = TRUE;
        }
        else if (stricmp( argv[i], "/REGSERVER" ) == 0)
        {
            fRegisterServer = TRUE;
        }
        else if (stricmp( argv[i], "/UNREGSERVER" ) == 0)
        {
            fUnregisterServer = TRUE;
        }
        else
        {
            fHelp = TRUE;
        }
    }

    if(fHelp == TRUE)
        {
        printf("USAGE: server /REGSERVER   - Installs server in the registry.\n");
        printf("       server /UNREGSERVER - Removes server from the registry.\n");
        printf("       server -Embedding   - Server was auto-started by OLE.\n");
        return 0;
    }
    else if(fUnregisterServer == TRUE)
    {
        hr = UnregisterLocalServer(CLSID_DOSServer);
        if(FAILED(hr))
        {
            printf("Failed to remove local server from the registry.\n");
         }
        return 0;
    }
    else if (fRegisterServer == TRUE) 
	{
		hr = RegisterLocalServer(CLSID_DOSServer);
		if(FAILED(hr))
		{
			printf("Failed to install local server in the registry.\n");
		}
	}

    if(fRegisterServer == TRUE || fUnregisterServer == TRUE || fHelp == TRUE)
        return 0;
  
    //
    // Initialize OLE before calling any other OLE functions.
    //

    hr = CoInitialize(NULL);

    if(SUCCEEDED(hr))
    {   
        hr = RegisterClassFactory();

        if(SUCCEEDED(hr))
        {
            printf("Waiting for client to connect...\n");
            // Main message loop.  We will remain in the message loop 
            // until we get a WM_QUIT message.
    	    while (GetMessage(&msg, NULL, 0, 0))
    	    {
        	    TranslateMessage(&msg);
        	    DispatchMessage(&msg);
        	}

            //If the class factory is still registered in the 
            //class table, revoke it before we shut down.
            RevokeClassFactory();
	    }
        else
        {
            printf("Failed to register class factory.\n");
          }
        CoUninitialize();
    }
    else
    {
        printf("CoInitialize failed.\n");
    }

    return 0;
}
