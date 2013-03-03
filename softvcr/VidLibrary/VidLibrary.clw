; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=5
Class1=CVidLibraryApp
LastClass=CRecompressDlg
NewFileInclude2=#include "VidLibrary.h"
ResourceCount=6
NewFileInclude1=#include "stdafx.h"
Class2=CVideoLibraryDlg
LastTemplate=CDialog
Resource1=IDD_RENAMEFILE (English (U.S.))
Class3=CRenameClip
Resource2=IDD_RENAMEFILE
Resource3=IDD_LIBRARY (English (U.S.))
Resource4=IDD_LIBRARY
Class4=CSearchLibDlg
Resource5=IDD_SEARCH
Class5=CRecompressDlg
Resource6=IDD_REALPRODUCER

[CLS:CVidLibraryApp]
Type=0
HeaderFile=VidLibrary.h
ImplementationFile=VidLibrary.cpp
Filter=N
LastObject=CVidLibraryApp

[DLG:IDD_LIBRARY]
Type=1
Class=CVideoLibraryDlg
ControlCount=19
Control1=IDOK,button,1342242817
Control2=IDC_LIBRARYLIST,SysListView32,1350664449
Control3=IDC_DELETE,button,1476460544
Control4=IDC_STATIC,button,1342177287
Control5=IDC_FILERENAME,button,1476460544
Control6=IDC_STATIC,button,1342177287
Control7=IDC_PLAYCLIP,button,1476460544
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_LIBRARYDURATION,edit,1350631553
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TIMEREMAIN,edit,1350631553
Control14=IDC_STATIC,static,1342308352
Control15=IDC_LIBRARYPATH,edit,1350631553
Control16=IDC_SEARCH,button,1342242816
Control17=IDC_RECOMPRESS,button,1476460544
Control18=IDC_STATIC,static,1342308353
Control19=IDC_STATIC,static,1342308353

[CLS:CVideoLibraryDlg]
Type=0
HeaderFile=VideoLibraryDlg.h
ImplementationFile=VideoLibraryDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVideoLibraryDlg

[DLG:IDD_RENAMEFILE]
Type=1
Class=CRenameClip
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ORIGNAME,edit,1484849280
Control4=IDC_NEWNAME,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287

[CLS:CRenameClip]
Type=0
HeaderFile=RenameClip.h
ImplementationFile=RenameClip.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CRenameClip

[DLG:IDD_LIBRARY (English (U.S.))]
Type=1
Class=CVideoLibraryDlg
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIBRARYLIST,SysListView32,1350631681
Control4=IDC_DELETE,button,1476460544
Control5=IDC_STATIC,button,1342177287
Control6=IDC_FILERENAME,button,1476460544
Control7=IDC_STATIC,button,1342177287
Control8=IDC_PLAYCLIP,button,1476460544
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_LIBRARYDURATION,edit,1476460672
Control13=IDC_STATIC,static,1342308352
Control14=IDC_TIMEREMAIN,edit,1476460672
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_RENAMEFILE (English (U.S.))]
Type=1
Class=CRenameClip
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ORIGNAME,edit,1484849280
Control4=IDC_NEWNAME,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287

[DLG:IDD_SEARCH]
Type=1
Class=CSearchLibDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1484849280
Control4=IDC_MONTHCALENDAR1,SysMonthCal32,1342242832
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_RADIO4,button,1342308361
Control8=IDC_RADIO5,button,1342177289

[CLS:CSearchLibDlg]
Type=0
HeaderFile=SearchLibDlg.h
ImplementationFile=SearchLibDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MONTHCALENDAR1

[DLG:IDD_REALPRODUCER]
Type=1
Class=CRecompressDlg
ControlCount=6
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1342242816
Control3=IDC_REALPRODUCER2,{56919D41-BE39-11D2-A404-00104BDF4755},1342242816
Control4=IDC_PROGRESS1,msctls_progress32,1350565889
Control5=IDC_STPROGRESS,static,1342308352
Control6=IDC_TIMERRETURN,button,1342242819

[CLS:CRecompressDlg]
Type=0
HeaderFile=RecompressDlg.h
ImplementationFile=RecompressDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TIMERRETURN
VirtualFilter=dWC

