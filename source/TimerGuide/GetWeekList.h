#if !defined(AFX_GETWEEKLIST_H__FDE7A4C3_4906_11D4_A6EC_009027D11084__INCLUDED_)
#define AFX_GETWEEKLIST_H__FDE7A4C3_4906_11D4_A6EC_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetWeekList.h : header file
//
#include "ListingData.h"
#include "TimerData.h"
#include "ParserSetup.h"
#include "WebParser.h"

/////////////////////////////////////////////////////////////////////////////
// CGetWeekList dialog

class CGetWeekList : public CDialog
{
// Construction
public:
	CGetWeekList(TTimerDataArray * guidearray, CWnd* pParent = NULL);   // standard constructor

	BOOL CanSerialize();
	void LoadRecords();
	void SaveRecords();

	void FillListingCombo();
	void FillChannelArray();
	void EmptyTimerList(TTimerDataArray * timerlist);

// Dialog Data
	//{{AFX_DATA(CGetWeekList)
	enum { IDD = IDD_GETWEEKLIST };
	CComboBox	m_source;
	CString	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetWeekList)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	TListingDataArray m_listingdata;
	TTimerDataArray * m_guidearray;
	CStringArray m_channelarray;

	// Generated message map functions
	//{{AFX_MSG(CGetWeekList)
	virtual void OnOK();
	afx_msg void OnAddSource();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETWEEKLIST_H__FDE7A4C3_4906_11D4_A6EC_009027D11084__INCLUDED_)
