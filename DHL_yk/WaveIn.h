/*------------------------------------------------------------------------------*\
 [模块名称]
	CWaveIn

 [文件名称]
	WaveIn.h

 [相关文件]
	WaveIn.cpp

 [目的]
 
     方便音频采集  
     	  
 [描述]
		
	封装 wavein api
	只使用了 pcm 方式
	只使用 函数回调方式
	所有的设置属性的函数只应在录音前使用，否者会在下次录音时才生效
	应该重载 virtual void GetData(char *pBuffer,int iLen);
	
 [注意]
	对于 StartRecord 中的PerPareBuffer() OpenRecord()是乎应该同时调用，
	要么就都不调用，其原因好象是 waveInAddBuffer 之后必须 使用saveInStart
	否则好象不能关闭设备
	SIZE_AUDIO_FRAME 是 160 倍数
	SIZE_AUDIO_PACKED 是 对应的输出 为 SIZE_AUDIO_FRAME / 160 * 10
	关闭的时候注意，在closerecord后有可能线程中还有数据到来，导致关闭不正确，所以关闭的时候sleep(1000),详细原因我也不太清楚
 
 [依赖性]
	
	 Winmm.lib 
 
 [版权]
 
   2002.12 hb  版权所有 

 [修改记录]
 
  版本:    1.01.01
  日期:    02-12-13 ~ 02-12-16      
  作者:    hb
  Mial:		sendh@21cn.com
  备注:
                                               
\*------------------------------------------------------------------------------*/

#ifndef _WAVEIN_H_
#define _WAVEIN_H_
#define WISA_POOR	8000
#define WISA_LOW	11025
#define WISA_NORMAL	22050
#define WISA_HIGH	44100

#define NUM_BUF 10				// 缓存数目
#define SIZE_AUDIO_FRAME 960	// 音频帧的大小
#define SIZE_AUDIO_PACKED 60	// 音频包的大小

#include <mmsystem.h>

class CWaveIn
{
public:
	static DWORD WINAPI AudioInThreadProc(LPVOID lpParameter);
public:
//	virtual void GetData(char *pBuffer,int iLen);
	// 开始录音
	BOOL StartRec();
	// 停止录音
	BOOL StopRec();
	// 获取实例
	inline DWORD GetInstance();
	// 获取声音数据位数
	inline WORD GetBit();
	// 获取采样率
	inline DWORD GetSample();
	// 获取声道数
	inline WORD GetChannel();
	// 参数设置
	inline void SetBit(WORD wBit);
	inline void SetSample(DWORD dwSample);
	inline void SetChannel(WORD wChannel);
	// 返回最后发生的错误
	inline MMRESULT GetLastMMError();
	CString GetLastErrorString();
	
	CWaveIn();
	virtual ~CWaveIn();	
protected:
	BOOL OpenDev();
	BOOL CloseDev();

	BOOL StopThread();
	BOOL StartThread();

	BOOL PerPareBuffer();
	BOOL FreeBuffer();

	BOOL OpenRecord();
	BOOL CloseRecord();
protected:
	static DWORD s_dwInstance;
protected:
	WORD m_wChannel;
	DWORD m_dwSample;
	WORD m_wBit;

protected:
	HWAVEIN m_hIn;
	MMRESULT m_mmr;
	DWORD m_dwAudioInId;
	HANDLE m_hAudioIn;
	WAVEHDR* m_pHdr;

//	BOOL m_bThreadStart;
//	BOOL m_bDevOpen;
//	BOOL m_bAllocBuffer;
//	BOOL m_bRecord;
};

#endif