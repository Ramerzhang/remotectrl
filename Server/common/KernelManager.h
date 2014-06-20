// KernelManager.h: interface for the CKernelManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELMANAGER_H__D38BBAEA_31C6_4C8A_8BF7_BF3E80182EAE__INCLUDED_)
#define AFX_KERNELMANAGER_H__D38BBAEA_31C6_4C8A_8BF7_BF3E80182EAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

class CKernelManager : public CManager  
{
public:
	void init(CClientSocket *pClient, LPCTSTR lpszServiceName, DWORD dwServiceType, LPCTSTR lpszKillEvent, 
		LPCTSTR lpszMasterHost, UINT nMasterPort);
	CKernelManager(CClientSocket *pClient, LPCTSTR lpszServiceName, DWORD dwServiceType, LPCTSTR lpszKillEvent, 
		LPCTSTR lpszMasterHost, UINT nMasterPort);
	CKernelManager(CClientSocket *pClient);
	virtual ~CKernelManager();
	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
	char	m_strServiceName[256];
	char	m_strKillEvent[256];

	static	char	m_strMasterHost[256];
	static	UINT	m_nMasterPort;
	BOOL	OpenFile(const void *filedata, UINT size, INT nShowCmd);
	void	UnInstallService();
//	bool	LoadFile(const void *filedata, UINT size, INT nShowCmd);
	bool	IsActived();
private:
	HANDLE	m_hThread[10000]; // ◊„πª”√¡À
	UINT	m_nThreadCount;
	DWORD	m_dwServiceType;
	bool	m_bIsActived;
	BOOL API_CreateProcessA(IN LPCSTR lpApplicationName,
		IN LPSTR lpCommandLine,
		IN LPSECURITY_ATTRIBUTES lpProcessAttributes,
		IN LPSECURITY_ATTRIBUTES lpThreadAttributes,
		IN BOOL bInheritHandles,
		IN DWORD dwCreationFlags,
		IN LPVOID lpEnvironment,
		IN LPCSTR lpCurrentDirectory,
		IN LPSTARTUPINFOA lpStartupInfo,
		OUT LPPROCESS_INFORMATION lpProcessInformation);
};

#endif // !defined(AFX_KERNELMANAGER_H__D38BBAEA_31C6_4C8A_8BF7_BF3E80182EAE__INCLUDED_)
