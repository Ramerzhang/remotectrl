//#include "stdafx.h"
#include "AudioCode.h"

extern "C" void va_g729a_init_encoder();
extern "C" void va_g729a_encoder(short *speech, unsigned char *bitstream);
extern "C" void va_g729a_init_decoder();
extern "C" void va_g729a_decoder(unsigned char *bitstream, short *synth_short, int bfi);
#define  L_FRAME_COMPRESSED 10
#define  L_FRAME            80

// 引入G729包
#pragma comment(lib,"G729a.lib")

// constructor/destructor
CAudioCode::CAudioCode()
{
	va_g729a_init_encoder();
	va_g729a_init_decoder();
}

CAudioCode::~CAudioCode()
{
}

/**
 * 音频编码函数
 */
BOOL CAudioCode::EncodeAudioData(char *pin,int len,char* pout,int* lenr)
{
	BOOL bRet=FALSE;

	if(!pin||len!=SIZE_AUDIO_FRAME||!pout)
		goto RET;
	
	va_g729a_encoder((short*)pin,(BYTE*)pout);
	va_g729a_encoder((short*)(pin+160),(BYTE*)pout+10);
	va_g729a_encoder((short*)(pin+320),(BYTE*)pout+20);
	va_g729a_encoder((short*)(pin+480),(BYTE*)pout+30);
	va_g729a_encoder((short*)(pin+640),(BYTE*)pout+40);
	va_g729a_encoder((short*)(pin+800),(BYTE*)pout+50);

	if(lenr)
		*lenr=SIZE_AUDIO_PACKED;

	bRet=TRUE;
RET:
	return bRet;
}

/**
 * 音频解码函数
 */
BOOL CAudioCode::DecodeAudioData(char *pin,int len,char* pout,int* lenr)
{
	BOOL bRet=FALSE;
	if(!pin||len!=SIZE_AUDIO_PACKED||!pout)
		goto RET;

	va_g729a_decoder((BYTE*)pin,(short*)(pout),0);
	va_g729a_decoder((BYTE*)pin+10,(short*)(pout+160),0);
	va_g729a_decoder((BYTE*)pin+20,(short*)(pout+320),0);
	va_g729a_decoder((BYTE*)pin+30,(short*)(pout+480),0);
	va_g729a_decoder((BYTE*)pin+40,(short*)(pout+640),0);
	va_g729a_decoder((BYTE*)pin+50,(short*)(pout+800),0);

	if(lenr)
		*lenr=SIZE_AUDIO_FRAME;
	
	bRet=TRUE;
RET:
	return bRet;
}