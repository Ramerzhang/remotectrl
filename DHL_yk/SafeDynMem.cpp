////////////////////////////////////////////////////////////////////////////////////////////////////
//	Module Name:
//		SafeDynMem.cpp
//	Author:
//		Chun-Hyok, Chong.
//	Description:
//		It is a safe dynamic allocation class to prevent a project from the memory leak.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SafeDynMem.h"

void OSafeDynMem::Init()
{
	m_pMem = NULL;
} // Init()

void OSafeDynMem::DeInit()
{
	if (NULL != m_pMem)
	{
		VirtualFree(m_pMem, 0, MEM_RELEASE);
		m_pMem = NULL;
	}
} // DeInit()

void *OSafeDynMem::Allocate(DWORD Size)
{
	if (NULL != m_pMem)
	{
		VirtualFree(m_pMem, 0, MEM_RELEASE);
		m_pMem = NULL;
	}

	m_pMem = (void *)VirtualAlloc(NULL, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	return m_pMem;
} // Allocate()

BOOL OSafeDynMem::Free()
{
	if (NULL != m_pMem)
	{
		VirtualFree(m_pMem, 0, MEM_RELEASE);
		m_pMem = NULL;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
} // Free()