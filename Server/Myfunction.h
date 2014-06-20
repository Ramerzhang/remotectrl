// Myfunction.h: interface for the Myfunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYFUNCTION_H__F52A3F83_C9EA_4B0D_A0B8_0414B2A8F6D3__INCLUDED_)
#define AFX_MYFUNCTION_H__F52A3F83_C9EA_4B0D_A0B8_0414B2A8F6D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Myfunction  
{
public:
	Myfunction();
	virtual ~Myfunction();
	char * my_strstr(const char * str1,const char * str2);
	int my_stricmp(const char *dst, const char *src);
	char * my_strchr(const char *str, int ch);
	int my_strnicmp(const char *dst,const char *src,int count);
	char * DelSpace(char *szData);
	int my_sprintf(char* buf,const char* fmt,...);
	double my_ceil(double x);
	void * my_memcpy(void * dst, const void * src, size_t count);
	int my_strncmp(const char *first,const char *last,int count);
	char * my_substr(char   *str,int   istar,int   iend);
	char * my_strncpy( char * dest, const char * source, int count );


};

#endif // !defined(AFX_MYFUNCTION_H__F52A3F83_C9EA_4B0D_A0B8_0414B2A8F6D3__INCLUDED_)
