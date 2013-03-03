// VidLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "VidLibrary.h"
//#include "VideoLibraryDlg.h"
#include "../libraryexport.h"
#include <fstream.h>

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
// Exported Function
extern "C" BOOL showLibraryDlg(HWND hWndParent, LPCTSTR LibraryPath){

	TRY
	{
		CVideoLibraryDlg dlg(CWnd::FromHandle(hWndParent), LibraryPath);
		//vidlibdlg.SetLibraryPath(LibraryPath);

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

extern "C" BOOL addToLibrary(LPCTSTR progname, 
							 LPCTSTR channel, 
							 LONG timedate, 
							 double duration, 
							 LPCTSTR path, 
							 int channelID)
{
	
	CVideoLibraryDlg dlg;

	dlg.addToLibrary(progname, channel, timedate, duration, path, channelID);
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVidLibraryApp

BEGIN_MESSAGE_MAP(CVidLibraryApp, CWinApp)
	//{{AFX_MSG_MAP(CVidLibraryApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVidLibraryApp construction

CVidLibraryApp::CVidLibraryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVidLibraryApp object

CVidLibraryApp theApp;
