// TimerGuide.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "timerguideexport.h"
#include "TimerDlg.h"
#include "ProgGuideDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//


/////////////////////////////////////////////////////////////////////////////
// Exported Functions


/*
 * Checks if requested program can be inserted in list without conflicting with 
 * existing members.  It will then add it to the list and return true.  False otherwise.
 */
extern "C" BOOL addToTimer(LPCTSTR progname, 
						   DWORD starttime, 
						   DWORD endtime,
						   LPCTSTR channel,
						   int channelID)
{
	TRY
	{
		CTimerDlg dlg(NULL);

		return(dlg.addToTimer(progname,starttime,endtime,channel,channelID,0));

	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL
}

extern "C" BOOL getNextTimer(DWORD timenow,
							 LPSTR progname,
							 DWORD *starttime,
							 int *duration,
							 int *channelID)
{
	TRY
	{
		CTimerDlg dlg(NULL);
		//DWORD ttimenow,tstarttime;
		//char tprogname[256];
		//int tduration, tchannelID;
		
		BOOL result = dlg.getNextTimer(timenow, progname, starttime, duration, channelID);

		return result;
	}
	CATCH_ALL(E)
	{
		return FALSE;
	}
	END_CATCH_ALL
}

extern "C" BOOL showTimerDlg(HWND hWndParent, LPCTSTR librarypath)
{
	TRY
	{
		CTimerDlg dlg(librarypath, CWnd::FromHandle(hWndParent));

		if(dlg.DoModal() != IDOK)
			return FALSE;

	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" BOOL showGuideDlg(HWND hWndParent, LPCTSTR librarypath, int currchan)
{
	TRY
	{
		CProgGuideDlg dlg(currchan, librarypath, CWnd::FromHandle(hWndParent));

		if(dlg.DoModal() != IDOK)
			return FALSE;

	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" BOOL getCurrentProg(LPSTR progname, int currchan)
{
	TRY
	{ 
		CProgGuideDlg dlg(NULL,NULL);

		BOOL result = dlg.getCurrentProg(progname, currchan);
		return result;
	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

extern "C" BOOL checkGuideValidity()
{
	TRY
	{ 
		CProgGuideDlg dlg(NULL,NULL);

		BOOL result = dlg.checkGuideValidity();
		return result;
	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTimerGuideApp

BEGIN_MESSAGE_MAP(CTimerGuideApp, CWinApp)
	//{{AFX_MSG_MAP(CTimerGuideApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerGuideApp construction

CTimerGuideApp::CTimerGuideApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTimerGuideApp object

CTimerGuideApp theApp;
