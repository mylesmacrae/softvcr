//{{AFX_INCLUDES()
#include "activemovie3.h"
//}}AFX_INCLUDES
#if !defined(AFX_ACTIVEMOVIEDLG_H__EC22368E_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
#define AFX_ACTIVEMOVIEDLG_H__EC22368E_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ActiveMovieDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActiveMovieDlg dialog

class CActiveMovieDlg : public CDialog
{
// Construction
public:

	char videoname[256];
	CActiveMovieDlg(LPCTSTR filename, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveMovieDlg)
	enum { IDD = IDD_PLAYER2 };
	CActiveMovie3	m_activemovie;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveMovieDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CActiveMovieDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEMOVIEDLG_H__EC22368E_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
