; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=10
Class1=CTimerGuideApp
LastClass=CGetWeekList
NewFileInclude2=#include "TimerGuide.h"
ResourceCount=9
NewFileInclude1=#include "stdafx.h"
Class2=CTimerDlg
LastTemplate=CDialog
Resource1=IDD_GUIDDLG
Class3=CProgGuideDlg
Resource2=IDD_TIMERDLG
Class4=CAddTimer
Resource3=IDD_PARSERCONFIG
Class5=CGetListingDlg
Resource4=IDD_GETLISTING
Class6=CParserSetup
Resource5=IDD_WEBBROWSER
Class7=CGetListingDlg2
Resource6=IDD_ADDTIMER
Class8=CWebDialog
Resource7=IDD_GETLISTING2
Class9=CFrequencyDlg
Resource8=IDD_FREQUENCY
Class10=CGetWeekList
Resource9=IDD_GETWEEKLIST

[CLS:CTimerGuideApp]
Type=0
HeaderFile=TimerGuide.h
ImplementationFile=TimerGuide.cpp
Filter=N
LastObject=CTimerGuideApp

[DLG:IDD_TIMERDLG]
Type=1
Class=CTimerDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_TIMERLIST,SysListView32,1350631429
Control3=IDC_STATIC,button,1342177287
Control4=IDC_DELETETIMER,button,1342242816
Control5=IDC_ADDTIMER,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352

[CLS:CTimerDlg]
Type=0
HeaderFile=TimerDlg.h
ImplementationFile=TimerDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTimerDlg

[DLG:IDD_GUIDDLG]
Type=1
Class=CProgGuideDlg
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDC_ProgGuide,SysListView32,1350631493
Control3=IDC_TIMERLIST,SysListView32,1350631493
Control4=IDC_ADDTOTTIMER,button,1476460544
Control5=IDC_REMOVETIMER,button,1476460544
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_GetListings,button,1342242816
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_SHOWDESC,button,1476460544
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DISPCHAN,combobox,1344340227
Control15=IDC_DISPDATE,combobox,1344340227
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287

[CLS:CProgGuideDlg]
Type=0
HeaderFile=ProgGuideDlg.h
ImplementationFile=ProgGuideDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CProgGuideDlg
VirtualFilter=dWC

[DLG:IDD_ADDTIMER]
Type=1
Class=CAddTimer
ControlCount=17
Control1=IDOK,button,1476460545
Control2=IDCANCEL,button,1342242816
Control3=IDC_STARTTIMEPICKER,SysDateTimePick32,1342242857
Control4=IDC_MONTHCALENDAR1,SysMonthCal32,1342177280
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ENDDATETIMEPICKER,SysDateTimePick32,1342242857
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_DURATION,edit,1476460673
Control13=IDC_CHANNELLIST,listbox,1352728833
Control14=IDC_STATIC,button,1342177287
Control15=IDC_PROGNAME,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_FREQUENCY,combobox,1344339971

[CLS:CAddTimer]
Type=0
HeaderFile=AddTimer.h
ImplementationFile=AddTimer.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAddTimer

[DLG:IDD_GETLISTING]
Type=1
Class=CGetListingDlg
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTINGCOMBO,combobox,1344340227
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_DATE,SysDateTimePick32,1342242848
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STARTTIME,SysDateTimePick32,1342242857
Control9=IDC_ENDTIME,SysDateTimePick32,1342242857
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CHANNELCOMBO,combobox,1344342275
Control13=IDC_STATIC,button,1342177287
Control14=IDC_ADDPARSER,button,1342242816

[CLS:CGetListingDlg]
Type=0
HeaderFile=GetListingDlg.h
ImplementationFile=GetListingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CGetListingDlg
VirtualFilter=dWC

[DLG:IDD_PARSERCONFIG]
Type=1
Class=CParserSetup
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CURRENTCHANNEL,edit,1342242945
Control5=IDC_LISTISTINGLIST,listbox,1352728833

[CLS:CParserSetup]
Type=0
HeaderFile=ParserSetup.h
ImplementationFile=ParserSetup.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CParserSetup

[DLG:IDD_GETLISTING2]
Type=1
Class=CGetListingDlg2
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTINGCOMBO,combobox,1344340227
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_DATE,SysDateTimePick32,1342242848
Control7=IDC_CHANNELCOMBO,combobox,1344342275
Control8=IDC_STATIC,button,1342177287
Control9=IDC_ADDPARSER,button,1342242816

[CLS:CGetListingDlg2]
Type=0
HeaderFile=GetListingDlg2.h
ImplementationFile=GetListingDlg2.cpp
BaseClass=CDialog
Filter=D
LastObject=CGetListingDlg2
VirtualFilter=dWC

[DLG:IDD_WEBBROWSER]
Type=1
Class=CWebDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EXPLORER3,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

[CLS:CWebDialog]
Type=0
HeaderFile=WebDialog.h
ImplementationFile=WebDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CWebDialog
VirtualFilter=dWC

[DLG:IDD_FREQUENCY]
Type=1
Class=CFrequencyDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_FREQUENCYLIST,combobox,1344339971

[CLS:CFrequencyDlg]
Type=0
HeaderFile=FrequencyDlg.h
ImplementationFile=FrequencyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFrequencyDlg

[DLG:IDD_GETWEEKLIST]
Type=1
Class=CGetWeekList
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO1,combobox,1344340226
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_PROGSTRING,edit,1484849281

[CLS:CGetWeekList]
Type=0
HeaderFile=GetWeekList.h
ImplementationFile=GetWeekList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDCANCEL

