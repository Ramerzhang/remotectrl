#include "stdafx.h"
#include "Filter.h"
#include "WaveIn.h"
#include "resource.h"
#include  <math.h>

unsigned short wBitsPerSample0;
unsigned short wBitsPerSample1;
HWND m_hWnd0;
HWND m_hWnd1;

CFilter::CFilter()
{
	m_hWnd0 = NULL;
	m_hWnd1 = NULL;
	wBitsPerSample0 = 0;
	wBitsPerSample1 = 0;
}

CFilter::~CFilter()
{
	m_MDC0.DeleteDC();
	m_MDC1.DeleteDC();
}

void CFilter::MiInit(HWND hWnd,unsigned short wBits)   //话筒画线初始化
{
	m_hWnd0 = hWnd;
	wBitsPerSample0 = wBits;
	m_MDC0.CreateCompatibleDC (NULL);
//	brush0.CreateSolidBrush(RGB(0,0,0));
	pen0.CreatePen (PS_SOLID,0,RGB(0,0,255));  //蓝色
	GetClientRect(hWnd,&memrec0);
}

int CFilter::MiFilter(char* pBuf)  //话筒画线函数
{
	if( m_hWnd0 == NULL || wBitsPerSample0 == 0 )
		return -1;

	BOOL bTalk = FALSE;
	int x,y;
	CBitmap m_bitmap;
	CBitmap *m_pOldBitmap;

	HDC hdc=GetDC(m_hWnd0);
	m_bitmap.CreateCompatibleBitmap(CDC::FromHandle(hdc),memrec0.Width (),memrec0.Height ());
	m_pOldBitmap =(CBitmap*)SelectObject(m_MDC0.GetSafeHdc (),m_bitmap);
	m_MDC0.Rectangle (0,0,memrec0.Width (),memrec0.Height ());
//	m_bitmap.DeleteObject(); //删除Bitmap对象
	oldpen0 = m_MDC0.SelectObject (&pen0);
	CBrush brush0;
	brush0.CreateSolidBrush(RGB(0,0,0));
	m_MDC0.FillRect(memrec0,&brush0);
	DeleteObject(brush0);

	DWORD size;
	size = wBitsPerSample0 == 16 ? SIZE_AUDIO_FRAME/2 : SIZE_AUDIO_FRAME;
	
	int yy = memrec0.Height()/2;
	m_MDC0.MoveTo (0,yy);
	int h=yy;

	short sample;
	for(int register i = 0 ; i <(long)size ; i++)	//to draw first channel
	{
		sample = wBitsPerSample0 == 16 ? ((*((short*)pBuf+i))*h)/(65535/2) : ( (*((BYTE*)pBuf+i)-128)*h)/128;
		x = int(((float)i/size)*(memrec0.Width()));
		y = yy-sample;
		if( abs(sample) > 15 && !bTalk )
		{
			bTalk = TRUE;
		}
		m_MDC0.LineTo (x,y);
	}

	m_MDC0.SelectObject(oldpen0);

	CRect rc;
	GetClientRect(m_hWnd0,&rc);
	StretchBlt(hdc,0,0,rc.Width (),rc.Height (),m_MDC0.GetSafeHdc(),0,0,memrec0.Width(),memrec0.Height(),SRCCOPY);
	ReleaseDC(NULL,hdc);

	if( bTalk )
		return 1;
	return 0;
}

void CFilter::HoInit(HWND hWnd,unsigned short wBits)   //喇叭画线初始化
{
	m_hWnd1 = hWnd;
	wBitsPerSample1 = wBits;
	m_MDC1.CreateCompatibleDC (NULL);
//	brush1.CreateSolidBrush(RGB(0,0,0));
	pen1.CreatePen (PS_SOLID,0,RGB(0,255,0));  //绿色
	GetClientRect(hWnd,&memrec1);
}

int CFilter::HoFilter(char* pBuf)  //喇叭画线函数
{
	if( m_hWnd1 == NULL || wBitsPerSample1 == 0 )
		return -1;

	BOOL bTalk = FALSE;
	int x,y;
	CBitmap m_bitmap;
	CBitmap *m_pOldBitmap;

	HDC hdc=GetDC(m_hWnd1); 
	m_bitmap.CreateCompatibleBitmap(CDC::FromHandle(hdc),memrec1.Width (),memrec1.Height ());
	m_pOldBitmap =(CBitmap*)SelectObject(m_MDC1.GetSafeHdc (),m_bitmap);
	m_MDC1.Rectangle (0,0,memrec1.Width (),memrec1.Height ());
	oldpen1 = m_MDC1.SelectObject (&pen1);
	CBrush brush1;
	brush1.CreateSolidBrush(RGB(0,0,0));
	m_MDC1.FillRect(memrec1,&brush1);
	DeleteObject(brush1);
	
	DWORD size;
	size = wBitsPerSample1 == 16 ? SIZE_AUDIO_FRAME/2 : SIZE_AUDIO_FRAME;
	
	int yy = memrec1.Height()/2;
	m_MDC1.MoveTo (0,yy);
	int h=yy;

	short sample;
	for(int register i = 0 ; i <(long)size ; i++)	//to draw first channel
	{
		sample = wBitsPerSample1 == 16 ? ((*((short*)pBuf+i))*h)/(65535/2) : ( (*((BYTE*)pBuf+i)-128)*h)/128;
		x = int(((float)i/size)*(memrec1.Width()));
		y = yy-sample;
		if( abs(sample) > 15 && !bTalk )
		{
			bTalk = TRUE;
		}
		m_MDC1.LineTo (x,y);
	}

	m_MDC1.SelectObject(oldpen1);

	CRect rc;
	GetClientRect(m_hWnd1,&rc);
	StretchBlt(hdc,0,0,rc.Width (),rc.Height (),m_MDC1.GetSafeHdc(),0,0,memrec1.Width (),memrec1.Height(),SRCCOPY);
	ReleaseDC(NULL,hdc);

	if( bTalk )
		return 1;
	return 0;
}