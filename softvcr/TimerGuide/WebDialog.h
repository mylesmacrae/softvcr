//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_WEBDIALOG_H__D1B7C765_3CA3_11D4_A6DC_009027D11084__INCLUDED_)
#define AFX_WEBDIALOG_H__D1B7C765_3CA3_11D4_A6DC_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WebDialog.h : header file
//
#include "webbrowser2.h"
/////////////////////////////////////////////////////////////////////////////
// CWebDialog dialog

class CWebDialog : public CDialog
{
// Construction
public:
	CWebDialog(CString URL, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWebDialog)
	enum { IDD = IDD_WEBBROWSER };
	CWebBrowser2	m_WebBrowser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_url;

	// Generated message map functions
	//{{AFX_MSG(CWebDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEBDIALOG_H__D1B7C765_3CA3_11D4_A6DC_009027D11084__INCLUDED_)
