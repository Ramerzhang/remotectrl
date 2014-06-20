#if !defined(AFX_SERATTRIBDLG_H__E5509479_8FE9_4066_BDD0_C0BF8161FE5F__INCLUDED_)
#define AFX_SERATTRIBDLG_H__E5509479_8FE9_4066_BDD0_C0BF8161FE5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerAttribDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerAttribDlg dialog

class CSerAttribDlg : public CDialog
{
// Construction
public:
	void init(int* indexed, int* counted, CString* info,CIOCPServer* m_iocpServer,ClientContext* m_pContext);
	CSerAttribDlg(CWnd* pParent = NULL);   // standard constructor
	int count;                     //选择了何种方式   1自动,2禁止,3手动
	int index;
	int* indexed;
	int* counted;
	CString* info;
	CIOCPServer* m_iocpServer;
	ClientContext* m_pContext;
// Dialog Data
	//{{AFX_DATA(CSerAttribDlg)
	enum { IDD = IDD_SER_ATTRIB_DLG };
	CComboBox	m_start_com;
	CString	m_name;
	CString	m_showname;
	CString	m_miaoshu;
	CString	m_path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerAttribDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSerAttribDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERATTRIBDLG_H__E5509479_8FE9_4066_BDD0_C0BF8161FE5F__INCLUDED_)
