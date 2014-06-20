////////////////////////////////////////////////////////////////////////////////////////////////////
//	Module Name:
//		ErrLog.cpp
//	Author:
//		Chun-Hyok, Chong.
////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ErrLog.h"
#include "SafeDynMem.h"

#define DIFF_BACK_SLASH								"\\"
#define DIFF_BACK_SLASH_CHAR						'\\'
#define DIFF_DRIVE_LETTER_HEADER_MARK				":\\\\"
#define DIFF_UNC_HEADER_MARK						"\\\\"
#define DIFF_DOT									"."

#define ACCESS_TYPE_DRIVE_LETTER					1
#define ACCESS_TYPE_UNC								2

// Return Code
#define RET_SUCCESS									1
#define RET_FAIL									-1

void OErrLog::Init()
{
	ZeroMemory(m_Path, sizeof (m_Path));
	ZeroMemory(m_FileName, sizeof (m_FileName));
	ZeroMemory(m_FileExtent, sizeof (m_FileExtent));
	ZeroMemory(m_WholePathFile, sizeof (m_WholePathFile));
	m_AccessType = ERR_INVALID_VALUE;
} // Init()

int OErrLog::SetErrLogFile(const char *InsertedPathFile)
{
	char *pTail;
	char *pPoint;
	
	if (0 == strlen(InsertedPathFile))
	{
		return RET_FAIL;
	}

	if (NULL != strstr(InsertedPathFile, DIFF_DRIVE_LETTER_HEADER_MARK))
	{
		m_AccessType = ACCESS_TYPE_DRIVE_LETTER;
	}
	else if (*InsertedPathFile == DIFF_BACK_SLASH_CHAR && *(InsertedPathFile + 1) == DIFF_BACK_SLASH_CHAR)
	{
		m_AccessType = ACCESS_TYPE_UNC;
	}
	else
	{
		return RET_FAIL;
	}

	// In the case of drive letter, the header formed like 'd:\\'(<DriveLetter>:\\) is valied.
	// In the case of UNC, the header formed like '\\sleepyrea\test'(\\<resource name>\<root>) is valid.
	if (ACCESS_TYPE_DRIVE_LETTER == m_AccessType)
	{
		pTail = (char*)(strstr(InsertedPathFile, DIFF_DRIVE_LETTER_HEADER_MARK) + strlen(DIFF_DRIVE_LETTER_HEADER_MARK));
		if (InsertedPathFile + strlen(InsertedPathFile) == pTail)
		{
			return RET_FAIL;
		}
	}
	else // if (ACCESS_TYPE_UNC == m_AccessType)
	{
		pTail = (char*)(strstr(InsertedPathFile, DIFF_UNC_HEADER_MARK) + strlen(DIFF_UNC_HEADER_MARK));
		pPoint = strstr(pTail, DIFF_BACK_SLASH);
		if (NULL == pPoint)
		{
			return RET_FAIL;
		}
		pTail = pPoint + 1;
		pPoint = strstr(pTail, DIFF_BACK_SLASH);
		if (NULL == pPoint)
		{
			return RET_FAIL;
		}
		pTail = pPoint + 1;
		if (InsertedPathFile + strlen(InsertedPathFile) == pTail)
		{
			return RET_FAIL;
		}
	}
	
	while (TRUE)
	{
		pPoint = strstr(pTail, DIFF_BACK_SLASH);
		if (NULL == pPoint)
		{
			ZeroMemory(m_Path, sizeof (m_Path));
			strncpy(m_Path, InsertedPathFile, pTail - InsertedPathFile);
			
			ZeroMemory(m_FileName, sizeof (m_FileName));
			ZeroMemory(m_FileExtent, sizeof (m_FileExtent));
			pPoint = strstr(pTail, DIFF_DOT);
			if (NULL == pPoint)
			{
				strncpy(m_FileName, pTail, InsertedPathFile + strlen(InsertedPathFile) - pTail);
			}
			else
			{
				strncpy(m_FileName, pTail, pPoint - pTail);
				strncpy(m_FileExtent, pPoint + 1, InsertedPathFile + strlen(InsertedPathFile) - pPoint - 1);
			}

			if (0 == strlen(m_FileName))
			{
				return RET_FAIL;
			}
			break;
		}
		pTail = pPoint + 1;
	}

	return RET_SUCCESS;
} // SetErrLogFile()

int OErrLog::ErrLog(const char *SrcCodeFileName, int SrcCodeLine, const char *Msg, ...)
{
	HANDLE hFile;
	DWORD ErrorCode;
	char *pPoint;
	char *pTail;
	SYSTEMTIME TimeInfo;
	char GrowingPath[ERR_PATH_FILE_LEN];
	BOOL bRes;
	int	len;
	va_list args;
	char *ErrStr;
	char *ResultErrStr;
	DWORD dwRes;
	DWORD WrittenNum;
	OSafeDynMem MemForErrStr;
	OSafeDynMem MemForResultErrStr;

	if (0 == strlen(m_Path) || 0 == strlen(m_FileName))
	{
		return RET_SUCCESS;
	}

	// format error string
	ErrStr = (char *)MemForErrStr.Allocate(ERR_MSG_LEN);
	if (NULL == ErrStr)
	{
		return RET_FAIL;
	}

	va_start(args, Msg);				// Initialize variable arguments.
	len = vsprintf(ErrStr, Msg, args);
	va_end(args);						// Reset variable arguments.
  
	ResultErrStr = (char *)MemForResultErrStr.Allocate(ERR_MSG_LEN);
	if (NULL == ResultErrStr)
	{
		return RET_FAIL;
	}
	
	ZeroMemory(&TimeInfo, sizeof (TimeInfo));
	GetLocalTime(&TimeInfo);
	sprintf(ResultErrStr, "File: %s, Line: %d, Msg: %s,"
		" Date: %04d/%02d/%02d, Time: %02d:%02d:%02d\r\n",
		SrcCodeFileName, SrcCodeLine, ErrStr, TimeInfo.wYear, TimeInfo.wMonth, TimeInfo.wDay, TimeInfo.wHour, TimeInfo.wMinute, TimeInfo.wSecond);
	if (0 == MemForErrStr.Free())
	{
		return RET_FAIL;
	}

	if (0 == strlen(m_FileExtent))
	{
		sprintf(m_WholePathFile, "%s%s%04d%02d%02d", m_Path, m_FileName, TimeInfo.wYear, TimeInfo.wMonth, TimeInfo.wDay);
	}
	else
	{
		sprintf(m_WholePathFile, "%s%s%04d%02d%02d.%s", m_Path, m_FileName, TimeInfo.wYear, TimeInfo.wMonth, TimeInfo.wDay, m_FileExtent);
	}

	hFile = CreateFile(m_WholePathFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		// Drive Letter & UNC, No File -> ERROR_FILE_NOT_FOUND(2).
		// Drive Letter, No Path -> ERROR_PATH_NOT_FOUND(3).
		// UNC, No Path -> ERROR_BAD_NET_NAME(67).
		ErrorCode = GetLastError();
		if (ERROR_FILE_NOT_FOUND == ErrorCode)
		{
			hFile = CreateFile(m_WholePathFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile)
			{
				return RET_FAIL;
			}
			CloseHandle(hFile); // For creating.
		}
		else if (ERROR_PATH_NOT_FOUND == ErrorCode || ERROR_BAD_NET_NAME == ErrorCode)
		{
			ZeroMemory(GrowingPath, sizeof (GrowingPath));
			pTail = m_Path;
			if (ACCESS_TYPE_DRIVE_LETTER == m_AccessType)
			{
				pTail = strstr(pTail, DIFF_DRIVE_LETTER_HEADER_MARK) + strlen(DIFF_DRIVE_LETTER_HEADER_MARK);
				strncpy(GrowingPath, m_Path, pTail - m_Path);
			}
			else // if (ACCESS_TYPE_UNC == m_AccessType)
			{
				pTail += strlen(DIFF_UNC_HEADER_MARK);
				pTail = strstr(pTail, DIFF_BACK_SLASH) + 1;
				pTail = strstr(pTail, DIFF_BACK_SLASH) + 1;
								
				strncpy(GrowingPath, m_Path, pTail - m_Path);
			}

			while (TRUE)
			{
				if (!SetCurrentDirectory(GrowingPath))
				{
					ErrorCode = GetLastError();
					// If there is no exact directory(when Drive Letter & UNC), ERROR_FILE_NOT_FOUND is returned.
					if (ERROR_FILE_NOT_FOUND == ErrorCode)
					{
						if (!CreateDirectory(GrowingPath, NULL))
						{
							return RET_FAIL;
						}
					}
					else
					{
						return RET_FAIL;
					}

					if (!SetCurrentDirectory(GrowingPath))
					{
						return RET_FAIL;
					}
				}
			
				pPoint = strstr(pTail, DIFF_BACK_SLASH);
				if (m_Path + strlen(m_Path) == pTail || NULL == pPoint)
				{
					break;
				}
				char* pStr = new char[pPoint - pTail + 2];
				memset(pStr,0,pPoint - pTail + 2);
				memcpy(pStr,pTail - 1,pPoint - pTail + 1);
				strcat(GrowingPath,pStr);
				delete[] pStr;
//				strncat(GrowingPath, pTail - 1, pPoint - pTail + 1); // - 1 means back slash.
				pTail = pPoint + 1;
			}

			hFile = CreateFile(m_WholePathFile, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			if (INVALID_HANDLE_VALUE == hFile)
			{
				return RET_FAIL;
			}
			CloseHandle(hFile); // For creating.
		}
		else
		{
			return RET_FAIL;
		}

		// Open again.
		hFile = CreateFile(m_WholePathFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			return RET_FAIL;
		}
	}

	// Error logging.

	// if the file exists, write(append) the log into that file.
	dwRes = SetFilePointer(hFile, NULL, NULL, FILE_END);
	if (0xFFFFFFFF == dwRes)
	{
		CloseHandle(hFile);
		return RET_FAIL;
	}

	bRes = WriteFile(hFile, ResultErrStr, (DWORD)strlen(ResultErrStr), &WrittenNum, NULL);
	if ((0 == bRes) || (strlen(ResultErrStr) > WrittenNum))
	{
		CloseHandle(hFile);
		return RET_FAIL;
	}

	if (0 == MemForResultErrStr.Free())
	{
		return RET_FAIL;
	}

	if (!CloseHandle(hFile))
	{
		return RET_FAIL;
	}
	
	return RET_SUCCESS;
} // end ErrLog()