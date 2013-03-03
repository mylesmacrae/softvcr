#if !defined(AFX_SEARCHLIBDLG_H__33DDB4B4_3D2A_11D4_A6DD_009027D11084__INCLUDED_)
#define AFX_SEARCHLIBDLG_H__33DDB4B4_3D2A_11D4_A6DD_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchLibDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchLibDlg dialog

class CSearchLibDlg : public CDialog
{
// Construction
public:
	CSearchLibDlg(CListCtrl * theList, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchLibDlg)
	enum { IDD = IDD_SEARCH };
	CEdit	m_searchnamectrl;
	CButton	m_searchbyname;
	CButton	m_searchbydate;
	CString	m_searchstring;
	CTime	m_searchdate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchLibDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CListCtrl * m_vidlib;

	// Generated message map functions
	//{{AFX_MSG(CSearchLibDlg)
	afx_msg void OnSearchDateButton();
	afx_msg void OnSearchNameButton();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHLIBDLG_H__33DDB4B4_3D2A_11D4_A6DD_009027D11084__INCLUDED_)
