#include "../stdafx.h"
#include "WaveIn.h"
#include "math.h"
#include "AudioManager.h"
// 引入多媒体库
#pragma comment(lib,"Winmm")

DWORD CWaveIn::s_dwInstance = 0;

//音频输入线程函数
DWORD WINAPI CWaveIn::AudioInThreadProc(LPVOID lpParameter)
{
	CAudioManager *pWaveIn= (CAudioManager *)lpParameter;

	char buffer[1024];
	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		switch(msg.message )
		{
		// 输入缓存被填充或设备关闭时发送此消息
		case MM_WIM_DATA:
			WAVEHDR* pWH=(WAVEHDR*)msg.lParam;
			// 清空缓存
			waveInUnprepareHeader((HWAVEIN)msg.wParam,pWH,sizeof(WAVEHDR));
			// 设置以录音的字节数
			if(pWH->dwBytesRecorded!=SIZE_AUDIO_FRAME)
				break;
			// 将录音数据拷贝到buffer中
			memcpy(buffer,pWH->lpData,pWH->dwBytesRecorded);
			pWaveIn->ReadGetData(buffer ,pWH->dwBytesRecorded );
			// 为录音准备缓存
			waveInPrepareHeader((HWAVEIN)msg.wParam,pWH,sizeof(WAVEHDR));
			waveInAddBuffer((HWAVEIN)msg.wParam,pWH,sizeof(WAVEHDR));

			break;
		}
	}
	return msg.wParam;
}

CWaveIn::CWaveIn() :
	m_wChannel(1),
	m_dwSample (WISA_POOR),
	m_wBit(16)
{
	m_hIn=0;

	m_pHdr = NULL;
	m_dwAudioInId = 0;
	s_dwInstance ++;
}

CWaveIn::~CWaveIn()
{

}

/**
 * 关闭设备
 */
BOOL CWaveIn::CloseDev()
{

	if(!m_hIn)
	{
		return FALSE;
	}

	m_mmr=waveInClose(m_hIn);
	if(m_mmr)
	{
		m_hIn=0;
		return FALSE;
	}
	m_hIn=0;
	return TRUE;
}

/**
 * 打开设备
 */
BOOL CWaveIn::OpenDev()
{
	// 设置参数
	WAVEFORMATEX wfx;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = m_wChannel;
	wfx.nSamplesPerSec = m_dwSample;
	wfx.nAvgBytesPerSec = m_wChannel * m_dwSample * m_wBit / 8;
	wfx.nBlockAlign = m_wBit * m_wChannel / 8;
	wfx.wBitsPerSample = m_wBit;
	wfx.cbSize = 0;

	m_mmr=waveInOpen(0,WAVE_MAPPER,&wfx,0,0,WAVE_FORMAT_QUERY);
	if(m_mmr)
	{
		return FALSE;
	}

	m_mmr=waveInOpen(&m_hIn,WAVE_MAPPER,&wfx,m_dwAudioInId,s_dwInstance,CALLBACK_THREAD);
	if(m_mmr)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CWaveIn::StartThread()
{
	m_hAudioIn=CreateThread(0,0,AudioInThreadProc,this,0,&m_dwAudioInId);
	if(!m_hAudioIn)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CWaveIn::StopThread()
{
	if(m_hAudioIn)
	{
		int t=50;
		DWORD ExitCode;
		BOOL bEnd=FALSE;
		PostThreadMessage(m_dwAudioInId,WM_QUIT,0,0);
		while(t)
		{
			GetExitCodeThread(m_hAudioIn,&ExitCode);
			if(ExitCode!= STILL_ACTIVE)
			{
				bEnd=TRUE;
				break;
			}
			else
				Sleep(10);
			t--;
		}
		if(!bEnd)
		{
			TerminateThread(m_hAudioIn,0);
		}
		m_hAudioIn=0;
	}

	return TRUE;
}

/**
 * 开始录音
 */
BOOL CWaveIn::StartRec()  //开始录音
{
	BOOL bRet=FALSE;
	if (!StartThread())           
	{
		goto Exit;
	};
	if (!OpenDev())
	{
		goto Exit1;
	};
	if (!PerPareBuffer())
	{
		goto Exit2;
	}
	if (!OpenRecord())
	{
		goto Exit3;
	}
	bRet = TRUE;
	goto Exit;
Exit3:
	FreeBuffer();
Exit2:
	CloseDev ();
Exit1:
	StopThread ();
Exit:
	return bRet;
}

/**
 * 停止录音
 */
BOOL CWaveIn::StopRec()
{
	CloseRecord ();	
	Sleep(1500);

	FreeBuffer();
	if (CloseDev())
	{
		StopThread ();
	}

	return TRUE;
}

BOOL CWaveIn::PerPareBuffer()
{

	m_mmr=waveInReset(m_hIn);
	if(m_mmr)
	{
		return FALSE;
	}

	UINT i;
	m_pHdr=new WAVEHDR[NUM_BUF];
		
	for(i=0;i<NUM_BUF;i++)
	{
		ZeroMemory(&m_pHdr[i],sizeof(WAVEHDR));
		m_pHdr[i].lpData=new char[SIZE_AUDIO_FRAME];
		m_pHdr[i].dwBufferLength= SIZE_AUDIO_FRAME;
		m_mmr=waveInPrepareHeader(m_hIn,&m_pHdr[i],sizeof(WAVEHDR));
		if(m_mmr)
		{
			return FALSE;
		}
		
		m_mmr=waveInAddBuffer(m_hIn,&m_pHdr[i],sizeof(WAVEHDR));
		if(m_mmr)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CWaveIn::FreeBuffer()
{
	
	UINT i;
	if(!m_pHdr)
	{
		return FALSE;
	}

	for(i=0;i<NUM_BUF;i++)
	{
		m_mmr = waveInUnprepareHeader(m_hIn,&m_pHdr[i],sizeof(WAVEHDR));
		if(m_mmr)
		{
			Sleep(100);
			continue;
		}
		
		if(m_pHdr[i].lpData)
			delete []m_pHdr[i].lpData;
	
	}
	delete []m_pHdr;
	m_pHdr = NULL;

	return TRUE;
}

BOOL CWaveIn::OpenRecord()
{

	if(!m_hIn)
	{
		return FALSE;
	}

	m_mmr=waveInStart(m_hIn);
	if(m_mmr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CWaveIn::CloseRecord()
{

	if(!m_hIn)
	{
		return FALSE;
	}


	m_mmr=waveInReset(m_hIn);
	if(m_mmr)
	{
		return FALSE;
	}

	return TRUE;
}
