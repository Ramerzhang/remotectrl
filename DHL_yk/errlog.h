////////////////////////////////////////////////////////////////////////////////////////////////////
//	Module Name:
//		ErrLog.h
//	Author:
//		Chun-Hyok, Chong.
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __ERRLOG_H__
#define __ERRLOG_H__

#define ERRLOC									__FILE__, __LINE__
#define ERR_MSG_LEN								204800 // dynamic allocation only.
#define ERR_INVALID_VALUE						-1

#define ERR_PATH_LEN							512
#define ERR_FILE_NAME_LEN						256
#define ERR_FILE_EXTENT_LEN						32
#define ERR_PATH_FILE_LEN						1024

class OErrLog
{
private:
	char m_Path[ERR_PATH_LEN];
	char m_FileName[ERR_FILE_NAME_LEN];
	char m_FileExtent[ERR_FILE_EXTENT_LEN];
	char m_WholePathFile[ERR_PATH_FILE_LEN];
	int m_AccessType;

public:
	OErrLog()
	{
		Init();
	}
	~OErrLog()
	{
	}

	void Init();
	int SetErrLogFile(const char *InsertedPathFile);
	int ErrLog(const char *SrcCodeFileName, int SrcCodeLine, const char *Msg, ...);
};

#endif // __ERRLOG_H__