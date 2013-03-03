#if !defined(AFX_GETLISTINGDLG_H__8019EF34_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_)
#define AFX_GETLISTINGDLG_H__8019EF34_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetListingDlg.h : header file
//

#include "ListingData.h"
#include "TimerData.h"

/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg dialog

class CGetListingDlg : public CDialog
{
// Construction
public:
	CGetListingDlg(TTimerDataArray * guideinfo, CWnd* pParent = NULL);   // standard constructor

	void LoadSettings();
	void SaveSettings();
	BOOL CanSerialize();
	void FillListingCombo();
	void FillChannelCombo();

	TListingDataArray m_listingdata;
	TTimerDataArray* m_guidedata;
// Dialog Data
	//{{AFX_DATA(CGetListingDlg)
	enum { IDD = IDD_GETLISTING };
	CComboBox	m_channelcombo;
	CComboBox	m_listingcombo;
	CTime	m_date;
	CTime	m_endtime;
	CTime	m_starttime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetListingDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStringArray channelarray;

	// Generated message map functions
	//{{AFX_MSG(CGetListingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddParser();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETLISTINGDLG_H__8019EF34_37A6_11D4_A6E9_00D0B7221A0E__INCLUDED_)
