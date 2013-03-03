// progguide.h : main header file for the PROGGUIDE DLL
//

#if !defined(AFX_PROGGUIDE_H__08C31EE5_2FDD_11D4_A6E6_0090279BCDD7__INCLUDED_)
#define AFX_PROGGUIDE_H__08C31EE5_2FDD_11D4_A6E6_0090279BCDD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgguideApp
// See progguide.cpp for the implementation of this class
//

class CProgguideApp : public CWinApp
{
public:
	CProgguideApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgguideApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CProgguideApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGGUIDE_H__08C31EE5_2FDD_11D4_A6E6_0090279BCDD7__INCLUDED_)
