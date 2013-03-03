#if !defined(AFX_RENAMECLIP_H__F5C966C4_33D4_11D4_9418_009027A3343B__INCLUDED_)
#define AFX_RENAMECLIP_H__F5C966C4_33D4_11D4_9418_009027A3343B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameClip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenameClip dialog

class CRenameClip : public CDialog
{
// Construction
public:
	CRenameClip(LPTSTR clipname, CWnd* pParent = NULL);   // standard constructor

	void GetNewName(LPTSTR newname);

// Dialog Data
	//{{AFX_DATA(CRenameClip)
	enum { IDD = IDD_RENAMEFILE };
	CString	m_newname;
	CString	m_origname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenameClip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRenameClip)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAMECLIP_H__F5C966C4_33D4_11D4_9418_009027A3343B__INCLUDED_)
