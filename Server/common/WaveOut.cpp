#include "../stdafx.h"
#include "WaveOut.h"
#pragma comment(lib,"Winmm")

DWORD CWaveOut::s_dwInstance = 0;

DWORD WINAPI CWaveOut::AudioOutThreadProc(LPVOID lpParameter)
{
	CWaveOut *pWaveIn;
	pWaveIn = (CWaveOut *)lpParameter;

	MSG msg;
	while(GetMessage(&msg,0,0,0))
	{
		switch(msg.message )
		{
		case WOM_DONE:
			WAVEHDR* pwh=(WAVEHDR*)msg.lParam;
			waveOutUnprepareHeader((HWAVEOUT)msg.wParam,pwh,sizeof(WAVEHDR));
			pWaveIn->BufferSub ();
			delete []pwh->lpData;//删除Play调用时分配的内存
			delete pwh;
			break;
		}
	}
	return msg.wParam;
}

CWaveOut::CWaveOut():
	 m_wChannel(1),
	 m_dwSample (WOSA_POOR),
	 m_wBit(16)
{
	m_hOut = 0;

	m_hAudioOut = 0;
	m_dwAudioOutId = 0;
	m_iBufferNum = 0;

	s_dwInstance ++;
}

CWaveOut::~CWaveOut()
{

}

BOOL CWaveOut::StartThread()
{

	m_hAudioOut=CreateThread(0,0,AudioOutThreadProc,this,0,&m_dwAudioOutId);
	if(!m_hAudioOut)
	{
		return FALSE;
	}
	
	return TRUE;
}
BOOL CWaveOut::StopThread()
{

	if(m_hAudioOut)
	{
		int t=50;
		DWORD ExitCode;
		BOOL bEnd=FALSE;
		PostThreadMessage(m_dwAudioOutId,WM_QUIT,0,0);
		while(t)
		{
			GetExitCodeThread(m_hAudioOut,&ExitCode);
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
			TerminateThread(m_hAudioOut,0);
		}
		m_hAudioOut=0;
	}

	return TRUE;
}

BOOL CWaveOut::OpenDev()
{
	WAVEFORMATEX wfx;
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = m_wChannel;
	wfx.nSamplesPerSec = m_dwSample;
	wfx.nAvgBytesPerSec = m_wChannel * m_dwSample * m_wBit / 8;
	wfx.nBlockAlign = m_wBit * m_wChannel / 8;
	wfx.wBitsPerSample = m_wBit;
	wfx.cbSize = 0;

	m_mmr=waveOutOpen (0,WAVE_MAPPER,&wfx,0,0,WAVE_FORMAT_QUERY);
	if(m_mmr)
	{
		return FALSE;
	}

	m_mmr=waveOutOpen(&m_hOut,WAVE_MAPPER,&wfx,m_dwAudioOutId,s_dwInstance,CALLBACK_THREAD);
	if(m_mmr)
	{
		return FALSE;
	}

	m_iBufferNum = 0;
	return TRUE;
}

BOOL CWaveOut::CloseDev()
{

	if(!m_hOut)
	{
		return FALSE;
	}

	m_mmr=waveOutClose(m_hOut);
	if(m_mmr)
	{
		return FALSE;
	}
	m_hOut=0;

	return TRUE;
}

BOOL CWaveOut::StartPlay()  //声音播放
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
	bRet = TRUE;
	goto Exit;
Exit1:
	StopThread ();
Exit:
	return 0;//bRet;
}

BOOL CWaveOut::StopPlay()
{
	CloseDev();
	StopThread ();

	return TRUE;
}

BOOL CWaveOut::Play(char* buf,UINT uSize)
{

	if (GetBufferNum () > PLAY_DELAY)
	{
		return TRUE;
	}
	char* p;
	LPWAVEHDR pwh=new WAVEHDR;
	if(!pwh)
	{
		return FALSE;
	}
	
	p=new char[uSize];
	if(!p)
	{
		return FALSE;
	}

	CopyMemory(p,buf,uSize);
	ZeroMemory(pwh,sizeof(WAVEHDR));
	pwh->dwBufferLength=uSize;
	pwh->lpData=p;
	m_mmr=waveOutPrepareHeader(m_hOut,pwh,sizeof(WAVEHDR));
  	if (m_mmr)
	{
		return FALSE;
	}

	m_mmr=waveOutWrite(m_hOut,pwh,sizeof(WAVEHDR));
  	if (m_mmr)
	{
		return FALSE;
	}
	m_iBufferNum ++;
	return TRUE;
}

void CWaveOut::BufferSub()
{
	m_iBufferNum --;

}

int CWaveOut::GetBufferNum()
{
	int iTemp;
	iTemp = m_iBufferNum;
	return iTemp;

}
