// CursorInfo.h: interface for the CCursorInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURSORINFO_H__CE8C6529_4ACB_4BC3_96A8_C5C255A81289__INCLUDED_)
#define AFX_CURSORINFO_H__CE8C6529_4ACB_4BC3_96A8_C5C255A81289__INCLUDED_
#include <windows.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_CURSOR_TYPE	16

////////////////////////////////////////////////////////////////////
typedef BOOL
(WINAPI
*GetCursorInfoT)(
    __inout PCURSORINFO pci);

typedef HCURSOR
(WINAPI
*LoadCursorAT)(
    __in_opt HINSTANCE hInstance,
    __in LPCSTR lpCursorName);

typedef BOOL
(WINAPI
*DestroyCursorT)(
    __in HCURSOR hCursor);

////////////////////////////////////////////////////////////////////

class CCursorInfo  
{
private:
	LPCTSTR	m_CursorResArray[MAX_CURSOR_TYPE];
	HCURSOR	m_CursorHandleArray[MAX_CURSOR_TYPE];

public:
	CCursorInfo()
	{
		LPCTSTR	CursorResArray[MAX_CURSOR_TYPE] = 
		{
			IDC_APPSTARTING,
			IDC_ARROW,
			IDC_CROSS,
			IDC_HAND,
			IDC_HELP,
			IDC_IBEAM,
			IDC_ICON,
			IDC_NO,
			IDC_SIZE,
			IDC_SIZEALL,
			IDC_SIZENESW,
			IDC_SIZENS,
			IDC_SIZENWSE,
			IDC_SIZEWE,
			IDC_UPARROW,
			IDC_WAIT
		};
		char DYrEN56[] = {'L','o','a','d','C','u','r','s','o','r','A','\0'};
		LoadCursorAT pLoadCursorA=(LoadCursorAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN56);
		for (int i = 0; i < MAX_CURSOR_TYPE; i++)
		{
			m_CursorResArray[i] = CursorResArray[i];
			m_CursorHandleArray[i] = pLoadCursorA(NULL, CursorResArray[i]);
		}
	}

	virtual ~CCursorInfo()
	{
		char DYrEN57[] = {'D','e','s','t','r','o','y','C','u','r','s','o','r','\0'};
		DestroyCursorT pDestroyCursor=(DestroyCursorT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN57);
		for (int i = 0; i < MAX_CURSOR_TYPE; i++)
		pDestroyCursor(m_CursorHandleArray[i]);
	}

	int getCurrentCursorIndex()
	{
		CURSORINFO	ci;
		int i;
		ci.cbSize = sizeof(CURSORINFO);
	    char CtxPW57[] = {'G','e','t','C','u','r','s','o','r','I','n','f','o','\0'};
        GetCursorInfoT pGetCursorInfo=(GetCursorInfoT)GetProcAddress(LoadLibrary("USER32.dll"),"GetCursorInfo");
		if (!pGetCursorInfo(&ci) || ci.flags != CURSOR_SHOWING)
			return -1;
		
		
		for (i = 0; i < MAX_CURSOR_TYPE; i++)
		{
			if (ci.hCursor == m_CursorHandleArray[i])
				break;
		}
		char DYrEN57[] = {'D','e','s','t','r','o','y','C','u','r','s','o','r','\0'};
		DestroyCursorT pDestroyCursor=(DestroyCursorT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN57);
		pDestroyCursor(ci.hCursor);
		
		int	nIndex = i == MAX_CURSOR_TYPE ? -1 : i;
		return nIndex;
	}
	
	HCURSOR getCursorHandle( int nIndex )
	{
		if (nIndex >= 0 && nIndex < MAX_CURSOR_TYPE)
			return	m_CursorHandleArray[nIndex];
		else
			return NULL;
	}
};

#endif // !defined(AFX_CURSORINFO_H__CE8C6529_4ACB_4BC3_96A8_C5C255A81289__INCLUDED_)
