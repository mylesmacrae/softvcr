// VidLibrary.h : main header file for the VIDLIBRARY DLL
//

#if !defined(AFX_VIDLIBRARY_H__A98414F3_325A_11D4_9418_009027A3343B__INCLUDED_)
#define AFX_VIDLIBRARY_H__A98414F3_325A_11D4_9418_009027A3343B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "VideoLibraryDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CVidLibraryApp
// See VidLibrary.cpp for the implementation of this class
//


class CVidLibraryApp : public CWinApp
{
public:
	CVidLibraryApp();
	//CVideoLibraryDlg vidlibdlg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVidLibraryApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVidLibraryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDLIBRARY_H__A98414F3_325A_11D4_9418_009027A3343B__INCLUDED_)
