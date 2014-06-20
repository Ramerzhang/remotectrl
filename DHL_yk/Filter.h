#ifndef _CFilter_H_
#define _CFilter_H_

class CFilter
{
private:
	CDC m_MDC0;
	CRect memrec0;
	CPen pen0,*oldpen0;
	CBrush *oldBrush0;

	CDC m_MDC1;
	CRect memrec1;
	CPen pen1,*oldpen1;
	CBrush *oldBrush1;

private:
//	unsigned short wBitsPerSample;

public:
	CFilter();
	~CFilter();

	void MiInit(HWND hWnd,unsigned short wBits);
	int MiFilter(char* pBuf);
	void HoInit(HWND hWnd,unsigned short wBits);
	int HoFilter(char* pBuf);
};

#endif