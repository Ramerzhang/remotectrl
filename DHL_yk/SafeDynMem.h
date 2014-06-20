////////////////////////////////////////////////////////////////////////////////////////////////////
//	Module Name:
//		SafeDynMem.h
//	Author:
//		Chun-Hyok, Chong.
//	Description:
//		It is a safe dynamic allocation class to prevent a project from the memory leak.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SAFEDYNMEM_H__
#define __SAFEDYNMEM_H__

#include <windows.h>

class OSafeDynMem
{
private:
	void *m_pMem;

public:
	OSafeDynMem()
	{
		Init();
	}
	~OSafeDynMem()
	{
		DeInit();
	}

	void Init();
	void DeInit();
	void *Allocate(DWORD Size);
	BOOL Free();
};

#endif // __SAFEDYNMEM_H__