// playback.h : main header file for the PLAYBACK DLL
//

#if !defined(AFX_PLAYBACK_H__EC223681_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
#define AFX_PLAYBACK_H__EC223681_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPlaybackApp
// See playback.cpp for the implementation of this class
//

class CPlaybackApp : public CWinApp
{
public:
	CPlaybackApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlaybackApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CPlaybackApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYBACK_H__EC223681_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
