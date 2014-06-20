/*------------------------------------------------------------------------------
 [模块名称]
	CAudioCode

 [文件名称]
	AudioCode.h

 [相关文件]
	AudioCode.cpp

 [目的]
	方便音频解压缩 
     	  
 [描述]		
	封装 g.729 api
	
 [依赖性]	
	G729a.lib
                                               
------------------------------------------------------------------------------*/
#include <afxwin.h>
#ifndef _AUDIOCODE_H_
#define _AUDIOCODE_H_

// 定义音频数据帧的大小
#define SIZE_AUDIO_FRAME 960
// 定义音频数据包大小
#define SIZE_AUDIO_PACKED 60

class CAudioCode
{
public:
	virtual  ~CAudioCode();
	CAudioCode();
	// 编码音频数据
	BOOL EncodeAudioData(char *pin,int len,char* pout,int* lenr);
	// 解码音频数据
	BOOL DecodeAudioData(char *pin,int len,char* pout,int* lenr);
};


#endif