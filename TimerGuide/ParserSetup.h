#if !defined(AFX_PARSERSETUP_H__8019EF35_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_)
#define AFX_PARSERSETUP_H__8019EF35_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParserSetup.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CParserSetup dialog

class CParserSetup : public CDialog
{
// Construction
public:
	CParserSetup(CString path, CWnd* pParent = NULL);   // standard constructor

	CString GetSelChannelNum();
	CString GetParserName();
	void SetChannelName(CString name);

// Dialog Data
	//{{AFX_DATA(CParserSetup)
	enum { IDD = IDD_PARSERCONFIG };
	CListBox	m_listinglist;
	CComboBox	m_listingcombo;
	CString	m_currentchannel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParserSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_path;
	CString m_name;
	CString m_cursel;
	CMapStringToString m_selected;

	// Generated message map functions
	//{{AFX_MSG(CParserSetup)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSERSETUP_H__8019EF35_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_)
