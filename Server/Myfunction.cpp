// Myfunction.cpp: implementation of the Myfunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Myfunction.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Myfunction::Myfunction()
{

}

Myfunction::~Myfunction()
{

}

//strstr函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strstr(const char * str1,const char * str2)
{
        char *cp = (char *) str1;
        char *s1, *s2;
        if ( !*str2 )
            return((char *)str1);
        while (*cp)
        {
                s1 = cp;
                s2 = (char *) str2;

                while ( *s1 && *s2 && !(*s1-*s2) )
                        s1++, s2++;
                if (!*s2)
                        return(cp);
                cp++;
        }
        return(NULL);
}

//自定义函数 stricmp(字符串比较 不区分大小写)
////////////////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_stricmp(const char *dst, const char *src)
{
   int ch1, ch2;
   do 
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( ch1 && (ch1 == ch2) );
   return(ch1 - ch2);
}

//strchr函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strchr(const char *str, int ch)
{
   while (*str && *str != (char)ch)
        str++;
   if (*str == (char)ch)
        return((char *)str);
   return(NULL);
}

//源码strnicmp
/////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_strnicmp(const char *dst,const char *src,int count)
{
   int ch1, ch2;
   do
   {
      if ( ((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z') )
        ch1 += 0x20;
      if ( ((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z') )
        ch2 += 0x20;
   } while ( --count && ch1 && (ch1 == ch2) );
   return (ch1 - ch2);
}

//去除字符串类型前面的空格
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: DelSpace(char *szData)
{
	int i=0 ;
	while(1)
	{
		if(my_strnicmp(szData+i," ",1))
			break;
		i++;			
	}
	return (szData+i);
} 

//源码sprintf
/////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_sprintf(char* buf, const char* fmt, ...) 
{ 
        int   strlen; 
        va_list   ap; 
        va_start(ap,   fmt); 
        strlen   =   vsprintf(buf,   fmt,   ap); 
        va_end(ap); 
        return   strlen; 
} 

//ceil函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
double Myfunction:: my_ceil(double x)
{
    double y=x;
     if( (*( ( (int *) &y)+1) & 0x80000000) != 0)//或者if(x<0)
         return (float)((int)x);
     else                  //讨论非负的情况。
    {
         if(x == 0)
         return (float)((int)x);
         else
         return (float)((int)x) + 1;
    }
}

//memcpy函数源码
/////////////////////////////////////////////////////////////////////////////////////////////////
void * Myfunction:: my_memcpy(void * dst, const void * src, size_t count)
{
         void * ret = dst;
         while (count--) {
                 *(char *)dst = *(char *)src;
                 dst = (char *)dst + 1;
                 src = (char *)src + 1;
         }
         return(ret);
}

//strncmp函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
int Myfunction:: my_strncmp(const char *first,const char *last,int count)
{
   if (!count)
      return(0);
   while (--count && *first && *first == *last)first++,last++;
   return( *(unsigned char *)first - *(unsigned char *)last );
}

//substr函数源码
//////////////////////////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_substr(char   *str,int   istar,int   iend) 
{ 
	char   *p; 
	char   p1[100]={0}; 
	int   ip=0; 

    p=str; 
    ip=strlen(p); 
    if(istar> ip) 
		return   NULL; 
    else 
    { 
		p+=istar-1; 
    } 
    int   ipp=strlen(p); 
    if(ipp <iend) 
		strcpy(p1,p); 
    else 
    { 
        //p1+=iend; 
		my_memcpy(p1,p,iend); 
    }
	strcpy(str,p1);
    return   str; 
} 

//源码strncpy
/////////////////////////////////////////////////////////////////////////////
char * Myfunction:: my_strncpy( char * dest, const char * source, int count )
{
   char *p = dest;
   while (count && (*p++ = *source++)) count--;
   while(count--)
      *p++ = '\0';
   return(dest);
} 

/////////////////////////////////////////////////////////////////////////////////////////