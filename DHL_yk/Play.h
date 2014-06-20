#if !defined(AFX_PLAY_H__8E368A1F_B123_408A_9361_C0A363FFEE92__INCLUDED_)
#define AFX_PLAY_H__8E368A1F_B123_408A_9361_C0A363FFEE92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Play.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlay form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPlay : public CFormView
{
protected:
	CPlay();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPlay)

// Form Data
public:
	//{{AFX_DATA(CPlay)
	enum { IDD = IDD_PLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlay();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPlay)
	afx_msg void Onzhuomian1();
	afx_msg void Onzhuomian();
	afx_msg void Onrenwulan();
	afx_msg void Onrenwulan2();
	afx_msg void OnXianshiqi();
	afx_msg void Onguangqu();
	afx_msg void Onzaoyin();
	afx_msg void Onshanping();
//	afx_msg void OnKillmbr();
	afx_msg void Onguangqu2();
	afx_msg void OnXianshiqi2();
	afx_msg void OnMouse();
	afx_msg void OnMouse2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAY_H__8E368A1F_B123_408A_9361_C0A363FFEE92__INCLUDED_)
