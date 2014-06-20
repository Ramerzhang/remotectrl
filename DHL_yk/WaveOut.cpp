#include "stdafx.h"
#include "WaveOut.h"
#pragma comment(lib,"Winmm")

DWORD CWaveOut::s_dwInstance = 0;

DWORD WINAPI CWaveOut::AudioOutThreadProc(LPVOID lpParameter)
{
	CWaveOut *pWaveIn = (CWaveOut *)lpParameter;

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

	m_bThreadStart = FALSE;
	m_bDevOpen = FALSE;

	s_dwInstance ++;
}

CWaveOut::~CWaveOut()
{

}

BOOL CWaveOut::StartThread()
{
	if (m_bThreadStart)
	{
		TRACE("CWaveOut::StartThread: Wave out thread has run.\n");
		return FALSE;
	}

	m_hAudioOut=CreateThread(0,0,AudioOutThreadProc,this,0,&m_dwAudioOutId);
	if(!m_hAudioOut)
	{
		TRACE("CWaveOut::StartThread: Strat wave out thread fail.\n");
		return FALSE;
	}
	m_bThreadStart = TRUE;
	return TRUE;
}
BOOL CWaveOut::StopThread()
{
	if (!m_bThreadStart)
	{
		TRACE("CWaveOut::StopThread: Wave out thread hasn't run.\n");
		return FALSE;
	}

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
			TRACE("CWaveOut::StopThread: TerminateThread wave out thread.\n");
		}
		m_hAudioOut=0;
	}
	m_bThreadStart = FALSE;
	return TRUE;
}

BOOL CWaveOut::OpenDev()
{
	if (m_bDevOpen)
	{
		TRACE("CWaveOut::OpenDev: Device has open.\n");
		return FALSE;
	}
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
		TRACE("CWaveOut::OpenDev: waveOutOpen error.\n");
		return FALSE;
	}

	m_mmr=waveOutOpen(&m_hOut,WAVE_MAPPER,&wfx,m_dwAudioOutId,s_dwInstance,CALLBACK_THREAD);
	if(m_mmr)
	{
		TRACE("CWaveOut::OpenDev: waveOutOpen error.\n");
		return FALSE;
	}
	m_bDevOpen = TRUE;
	m_iBufferNum = 0;
	return TRUE;
}

BOOL CWaveOut::CloseDev()
{
	if (!m_bDevOpen)
	{
		TRACE("CWaveOut::CloseDev: Device hasn't opened.\n");
		return FALSE;
	}

	if(!m_hOut)
	{
		TRACE("CWaveOut::CloseDev: Device hasn't opened.\n");
		return FALSE;
	}

	m_mmr=waveOutClose(m_hOut);
	if(m_mmr)
	{
		TRACE("CWaveOut::CloseDev: waveInClose error.\n");
		return FALSE;
	}
	m_hOut=0;
	m_bDevOpen = FALSE;
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
	return bRet;
}

BOOL CWaveOut::StopPlay()
{
	CloseDev();
	StopThread ();

	return TRUE;
}

MMRESULT CWaveOut::GetLastMMError()
{
	return m_mmr;
}

CString CWaveOut::GetLastErrorString()
{
	char buffer[256];
	memset(buffer,0,256);
	waveOutGetErrorText(m_mmr,buffer,256);
	return buffer;
}


void CWaveOut::SetChannel(WORD wChannel)
{
	m_wChannel = (m_wChannel == wChannel) ? 2:1;
}

void CWaveOut::SetSample(DWORD dwSample)
{
	m_dwSample = dwSample;
}

void CWaveOut::SetBit(WORD wBit)
{
	m_wBit = (wBit == 8) ? 8:16;
}

DWORD CWaveOut::GetInstance()
{
	return s_dwInstance;
}

WORD CWaveOut::GetBit()
{
	return m_wBit;
}

DWORD CWaveOut::GetSample()
{
	return m_dwSample;
}

WORD CWaveOut::GetChannel()
{
	return m_wChannel;
}

BOOL CWaveOut::Play(char* buf,UINT uSize)
{
	if (!m_bDevOpen)
	{
		TRACE("CWaveOut::Play: Device hasn't been open.\n");
		return FALSE;
	}
	if (GetBufferNum () > PLAY_DELAY)
	{
	//	TRACE("CWaveOut::Play: Delay too big pass over.\n");
		return TRUE;
	}
	char* p = FALSE;
	LPWAVEHDR pwh=new WAVEHDR;
	if(!pwh)
	{
		TRACE("CWaveOut::Play: alloc WAVEHDR memoyr error.\n");
		return FALSE;
	}
	
	p=new char[uSize];
	if(!p)
	{
		TRACE("CWaveOut::Play: alloc data memoyr error.\n");
		return FALSE;
	}

	CopyMemory(p,buf,uSize);
	ZeroMemory(pwh,sizeof(WAVEHDR));
	pwh->dwBufferLength=uSize;
	pwh->lpData=p;
	m_mmr=waveOutPrepareHeader(m_hOut,pwh,sizeof(WAVEHDR));
  	if (m_mmr)
	{
		TRACE("CWaveOut::CloseDev: waveOutPrepareHeader error.\n");
		return FALSE;
	}

	m_mmr=waveOutWrite(m_hOut,pwh,sizeof(WAVEHDR));
  	if (m_mmr)
	{
		TRACE("CWaveOut::CloseDev: waveOutWrite error.\n");
		return FALSE;
	}
	m_iBufferNum ++;
	return TRUE;
}

void CWaveOut::BufferAdd()
{
	m_csLock.Lock ();
	m_iBufferNum ++;
	m_csLock.Unlock ();
}

void CWaveOut::BufferSub()
{
	m_csLock.Lock ();
	m_iBufferNum --;
	m_csLock.Unlock ();
}

int CWaveOut::GetBufferNum()
{
	int iTemp;
	m_csLock.Lock ();
	iTemp = m_iBufferNum;
	m_csLock.Unlock ();
	return iTemp;

}

BOOL CWaveOut::SetFormatByFile(CString file)
{
	#pragma pack(push, 1)
	struct FileHeader
	{
		char cFlagFiff[4];
		unsigned __int32 iFileLen;
		char cFlagWave[4];
		char cFlagFmt[4];
		char cResove[4];
		unsigned __int16 cFormat;
		unsigned __int16 cChannel;
		unsigned __int32 cSample;
		unsigned __int32 cBytePerSec;
		unsigned __int16 cByteprocess;
		unsigned __int16 cBit;
		char cFlagDat[4];
		unsigned __int32 iLenData;
	};
	#pragma pack(pop)

	CFile fi;
	if (!fi.Open(file,CFile::modeRead,NULL))
	{
		return FALSE;
	};
	struct FileHeader head;
	fi.Read ((void *)&head,sizeof (head));
	fi.Close ();

	this->SetChannel (head.cChannel);
	this->SetSample (head.cSample);
	this->SetBit (head.cBit);
	return TRUE;
}
