#if !defined(AFX_FREQUENCYDLG_H__FE489C94_41E5_11D4_A6E2_009027D11084__INCLUDED_)
#define AFX_FREQUENCYDLG_H__FE489C94_41E5_11D4_A6E2_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrequencyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg dialog

class CFrequencyDlg : public CDialog
{
// Construction
public:
	CFrequencyDlg(CWnd* pParent = NULL);   // standard constructor
	int selfrequency;

// Dialog Data
	//{{AFX_DATA(CFrequencyDlg)
	enum { IDD = IDD_FREQUENCY };
	CComboBox	m_frequencylist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrequencyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFrequencyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQUENCYDLG_H__FE489C94_41E5_11D4_A6E2_009027D11084__INCLUDED_)
