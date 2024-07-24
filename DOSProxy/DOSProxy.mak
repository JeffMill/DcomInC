#--------------------------------------------------
#
# File: DOSProxy.mak
#
#--------------------------------------------------

!include <ntwin32.mak>

!ifndef MIDL
MIDL            = midl
!endif

MIDLFLAGS    = /Oi /ms_ext /c_ext /cpp_cmd $(CC)

.c.obj:
    $(CC) $(cdebug) $(cflags) $(cvarsdll) /c $<

all:  DOSProxy.dll 

# Clean up everything but the .EXEs
clean:
        @-del *.obj
        @-del DOSProxy.dll
        @-del DOSProxy.h
        @-del DOSProxy.lib
        @-del DOSProxy.exp
        @-del dlldata.c
        @-del DOSProxy_?.c

#Run MIDL compiler to generate the header file and the proxy DLL files.
DOSProxy.h dlldata.c DOSProxy_p.c DOSProxy_i.c : DOSProxy.idl
    $(MIDL) $(MIDLFLAGS) DOSProxy.idl

#Build the files for the proxy DLL.
dlldata.obj : dlldata.c
    $(CC) $(cdebug) $(cflags) -DREGISTER_PROXY_DLL $(cvarsdll) /c dlldata.c

DOSProxy_i.obj : DOSProxy_i.c

DOSProxy_p.obj : DOSProxy_p.c DOSProxy.h

#Link the proxy DLL.
DOSProxy.dll: DOSProxy_p.obj DOSProxy_i.obj dlldata.obj DOSProxy.def
    $(link) $(linkdebug) -DLL -OUT:DOSProxy.dll -DEF:DOSProxy.def \
    DOSProxy_p.obj DOSProxy_i.obj dlldata.obj rpcrt4.lib uuid.lib kernel32.lib

	regsvr32 DOSProxy.dll