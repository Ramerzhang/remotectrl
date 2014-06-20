#if !defined(AFX_SHOWNUM_H__8D2A9D97_3343_4494_85CC_AD0E1E15FB69__INCLUDED_)
#define AFX_SHOWNUM_H__8D2A9D97_3343_4494_85CC_AD0E1E15FB69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowNum.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowNum form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CShowNum : public CFormView
{
protected:
	CShowNum();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CShowNum)

// Form Data
public:
	//{{AFX_DATA(CShowNum)
	enum { IDD = IDD_SHOW_NUM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	UINT GetNum( int nID );
	void SetNum( int uID, UINT nValue );
	
	int NT;
	int XP;
	int Vista;
	int Win7;
	int Win2000;
	int Win2003;
	int Win2008;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowNum)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CShowNum();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CShowNum)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWNUM_H__8D2A9D97_3343_4494_85CC_AD0E1E15FB69__INCLUDED_)
