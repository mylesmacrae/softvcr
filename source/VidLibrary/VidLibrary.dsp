# Microsoft Developer Studio Project File - Name="VidLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VidLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VidLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VidLibrary.mak" CFG="VidLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VidLibrary - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VidLibrary - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VidLibrary - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /incremental:yes /machine:I386

!ELSEIF  "$(CFG)" == "VidLibrary - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "VidLibrary - Win32 Release"
# Name "VidLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\codeccookie.cpp
# End Source File
# Begin Source File

SOURCE=.\codecinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\enumidispatch.cpp
# End Source File
# Begin Source File

SOURCE=.\LibraryData.cpp
# End Source File
# Begin Source File

SOURCE=.\producercontrol2.cpp
# End Source File
# Begin Source File

SOURCE=.\RecompressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RenameClip.cpp
# End Source File
# Begin Source File

SOURCE=.\rmfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchLibDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\targetaudienceinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoLibraryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VidLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\VidLibrary.def
# End Source File
# Begin Source File

SOURCE=.\VidLibrary.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\codeccookie.h
# End Source File
# Begin Source File

SOURCE=.\codecinfo.h
# End Source File
# Begin Source File

SOURCE=.\enumidispatch.h
# End Source File
# Begin Source File

SOURCE=.\LibraryData.h
# End Source File
# Begin Source File

SOURCE=..\libraryexport.h
# End Source File
# Begin Source File

SOURCE=.\producercontrol2.h
# End Source File
# Begin Source File

SOURCE=.\RecompressDlg.h
# End Source File
# Begin Source File

SOURCE=.\RenameClip.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rmfile.h
# End Source File
# Begin Source File

SOURCE=.\SearchLibDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\targetaudienceinfo.h
# End Source File
# Begin Source File

SOURCE=.\VideoLibraryDlg.h
# End Source File
# Begin Source File

SOURCE=.\VidLibrary.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VidLibrary.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section VidLibrary : {CFCDAA01-8BE4-11CF-B84B-0020AFBBCCFA}
# 	2:5:Class:CRealAudio
# 	2:10:HeaderFile:realaudio.h
# 	2:8:ImplFile:realaudio.cpp
# End Section
# Section VidLibrary : {F4F64778-B160-11D2-A3EF-00104BDF4755}
# 	2:5:Class:CTargetAudienceInfo
# 	2:10:HeaderFile:targetaudienceinfo.h
# 	2:8:ImplFile:targetaudienceinfo.cpp
# End Section
# Section VidLibrary : {F4F6477A-B160-11D2-A3EF-00104BDF4755}
# 	2:5:Class:CCodecInfo
# 	2:10:HeaderFile:codecinfo.h
# 	2:8:ImplFile:codecinfo.cpp
# End Section
# Section VidLibrary : {9F65D311-CDF7-11D3-9651-00D0B7068A6E}
# 	2:5:Class:CProducerControl2
# 	2:10:HeaderFile:producercontrol2.h
# 	2:8:ImplFile:producercontrol2.cpp
# End Section
# Section VidLibrary : {87659330-3F9D-11D3-87CA-00C0F031C266}
# 	2:5:Class:CRmFile
# 	2:10:HeaderFile:rmfile.h
# 	2:8:ImplFile:rmfile.cpp
# End Section
# Section VidLibrary : {F4F6477D-B160-11D2-A3EF-00104BDF4755}
# 	2:5:Class:CEnumIDispatch
# 	2:10:HeaderFile:enumidispatch.h
# 	2:8:ImplFile:enumidispatch.cpp
# End Section
# Section VidLibrary : {F4F64771-B160-11D2-A3EF-00104BDF4755}
# 	2:5:Class:CCodecCookie
# 	2:10:HeaderFile:codeccookie.h
# 	2:8:ImplFile:codeccookie.cpp
# End Section
# Section VidLibrary : {CFCDAA03-8BE4-11CF-B84B-0020AFBBCCFA}
# 	2:21:DefaultSinkHeaderFile:realaudio.h
# 	2:16:DefaultSinkClass:CRealAudio
# End Section
# Section VidLibrary : {56919D41-BE39-11D2-A404-00104BDF4755}
# 	2:21:DefaultSinkHeaderFile:producercontrol2.h
# 	2:16:DefaultSinkClass:CProducerControl2
# End Section
