#if !defined(AFX_SETTINGDLG_H__213F04F5_0A7E_4124_A07C_5AA48D8E260E__INCLUDED_)
#define AFX_SETTINGDLG_H__213F04F5_0A7E_4124_A07C_5AA48D8E260E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_SETTING };
	BOOL	m_connect_auto;
	UINT	m_max_connections;
	BOOL	m_disable_poptips;
	CString	m_off;
	CString	m_in;
	CString	m_set;
	BOOL	m_useautio;
	bool m_bFirstShow;
	UINT	m_listen_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual BOOL OnInitDialog();
	virtual CString GetOpenSoundFile();
	virtual BOOL IsFileExist(LPCTSTR strFileName);
	afx_msg void OnUseornot();
	afx_msg void OnIfonline();
	afx_msg void OnIfoffline();
	afx_msg void OnIfsuccess();
	afx_msg void OnDisablePoptips();
	afx_msg void OnResetport();
	afx_msg void OnExit();
	afx_msg void OnConnectAuto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__213F04F5_0A7E_4124_A07C_5AA48D8E260E__INCLUDED_)
