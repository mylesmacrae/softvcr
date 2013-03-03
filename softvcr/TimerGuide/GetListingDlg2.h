#if !defined(AFX_GETLISTINGDLG2_H__71F25954_3A4F_11D4_9421_009027A3343B__INCLUDED_)
#define AFX_GETLISTINGDLG2_H__71F25954_3A4F_11D4_9421_009027A3343B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetListingDlg2.h : header file
//
#include "ListingData.h"
#include "TimerData.h"
#include "ParserSetup.h"

/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg2 dialog

class CGetListingDlg2 : public CDialog
{
// Construction
public:
	CGetListingDlg2(TTimerDataArray * guidearray, CWnd* pParent = NULL);   // standard constructor

	BOOL CanSerialize();
	void LoadRecords();
	void SaveRecords();

	void FillListingCombo();
	void FillChannelCombo();

// Dialog Data
	//{{AFX_DATA(CGetListingDlg2)
	enum { IDD = IDD_GETLISTING2 };
	CButton	m_okbutton;
	CButton	m_cancelbutton;
	CButton	m_addparser;
	CDateTimeCtrl	m_datectrl;
	CComboBox	m_channelcombo;
	CComboBox	m_listingcombo;
	CTime	m_date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetListingDlg2)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	TListingDataArray m_listingdata;
	TTimerDataArray * m_guidearray;
	// Generated message map functions
	//{{AFX_MSG(CGetListingDlg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnAddParser();
	virtual void OnCancel();
	afx_msg void OnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETLISTINGDLG2_H__71F25954_3A4F_11D4_9421_009027A3343B__INCLUDED_)
