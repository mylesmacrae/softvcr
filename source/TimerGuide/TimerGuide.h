// TimerGuide.h : main header file for the TIMERGUIDE DLL
//

#if !defined(AFX_TIMERGUIDE_H__C0020476_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_)
#define AFX_TIMERGUIDE_H__C0020476_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTimerGuideApp
// See TimerGuide.cpp for the implementation of this class
//

class CTimerGuideApp : public CWinApp
{
public:
	CTimerGuideApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerGuideApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTimerGuideApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERGUIDE_H__C0020476_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_)
