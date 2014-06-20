// ShowNum.cpp : implementation file
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "ShowNum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CShowNum* g_pNumDlg;
/////////////////////////////////////////////////////////////////////////////
// CShowNum

IMPLEMENT_DYNCREATE(CShowNum, CFormView)

CShowNum::CShowNum()
	: CFormView(CShowNum::IDD)
{
	//{{AFX_DATA_INIT(CShowNum)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	g_pNumDlg = this;
	NT = 0;
	XP = 0;
	Vista = 0;
	Win7 = 0;
	Win2000 = 0;
	Win2003 = 0;
	Win2008 = 0;
}

CShowNum::~CShowNum()
{
}

void CShowNum::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowNum)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowNum, CFormView)
	//{{AFX_MSG_MAP(CShowNum)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowNum diagnostics

#ifdef _DEBUG
void CShowNum::AssertValid() const
{
	CFormView::AssertValid();
}

void CShowNum::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowNum message handlers

void CShowNum::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetDlgItemInt(IDC_WIN_NT, NT, FALSE);
	SetDlgItemInt(IDC_WIN_XP, XP, FALSE);
	SetDlgItemInt(IDC_WIN_VISTA, Vista, FALSE);
	SetDlgItemInt(IDC_WIN_7, Win7, FALSE);
	SetDlgItemInt(IDC_WIN_2000, Win2000, FALSE);
	SetDlgItemInt(IDC_WIN_2003, Win2003, FALSE);
	SetDlgItemInt(IDC_WIN_2008, Win2008, FALSE);
}

UINT CShowNum::GetNum( int nID )
{	
	UpdateData(TRUE);
	return	GetDlgItemInt( nID, NULL, FALSE );
}

void CShowNum::SetNum( int uID, UINT nValue )
{	
	UpdateData(TRUE);
	SetDlgItemInt( uID, nValue );
}
