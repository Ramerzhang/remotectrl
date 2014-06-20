/*------------------------------------------------------------------------------*\
 [模块名称]
	CWaveOut

 [文件名称]
	CWaveOut.h

 [相关文件]
	CWaveOut.cpp

 [目的]
 
     方便音频播放
     	  
 [描述]
		
	封装 waveout api
	只使用了 pcm 方式
	
 [注意]

	PLAY_DELAY 10	//播放时候的延迟，大于它，说明有PLAY_DELAY个包没有播放完成，后面的包不应再播放

 [依赖性]
	
	 Winmm.lib 
 
 [版权]
 
   2002.12 hb  版权所有

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-16  ~  02-12-17   
  作者:    hb
  Mial:		sendh@21cn.com
  备注:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _WAVEOUT_H_
#define _WAVEOUT_H_

#define WOSA_POOR	8000
#define WOSA_LOW	11025
#define WOSA_NORMAL	22050
#define WOSA_HIGH	44100

#define PLAY_DELAY 10

#include <mmsystem.h>
#include <afxmt.h>

/**
 * 音频播放器
 */
class CWaveOut  
{
public:
	static DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);
public:
	BOOL SetFormatByFile(CString file);
	BOOL Play(char* buf,UINT uSize);

	BOOL StartPlay();
	BOOL StopPlay();	

	inline int GetBufferNum();
	inline void BufferSub();
	inline void BufferAdd();

	inline DWORD GetInstance();
	inline WORD GetBit();
	inline DWORD GetSample();
	inline WORD GetChannel();

	inline void SetBit(WORD wBit);
	inline void SetSample(DWORD dwSample);
	inline void SetChannel(WORD wChannel);

	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();

	CWaveOut();
	virtual ~CWaveOut();
protected:
	BOOL OpenDev();
	BOOL CloseDev();

	BOOL StopThread();
	BOOL StartThread();
protected:
	static DWORD s_dwInstance;
protected:
	WORD m_wChannel;
	DWORD m_dwSample;
	WORD m_wBit;
protected:
	MMRESULT m_mmr;
	HWAVEOUT m_hOut;
	HANDLE m_hAudioOut;
	DWORD m_dwAudioOutId;

	int m_iBufferNum;
	CCriticalSection m_csLock;

	BOOL m_bThreadStart;
	BOOL m_bDevOpen;
	friend DWORD WINAPI AudioOutThreadProc(LPVOID lpParameter);
};

#endif
