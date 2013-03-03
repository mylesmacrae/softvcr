#if !defined(AFX_ADDTIMER_H__AF71FA83_3646_11D4_A6E7_00D0B7221A0E__INCLUDED_)
#define AFX_ADDTIMER_H__AF71FA83_3646_11D4_A6E7_00D0B7221A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddTimer.h : header file
//

#define IDM_T_COMPOSITE			  700

#define TIMER_ONCE		0
#define TIMER_DAILY		1
#define TIMER_WEEKLY	2
#define TIMER_WEEKDAY	3
#define TIMER_WEEKEND	4

/////////////////////////////////////////////////////////////////////////////
// CAddTimer dialog

class CAddTimer : public CDialog
{
// Construction
public:
	CAddTimer(CWnd* pParent = NULL);   // standard constructor
	CTime endtime, starttime;
	int selchannelID, selfrequency;
	CString selchannel;

// Dialog Data
	//{{AFX_DATA(CAddTimer)
	enum { IDD = IDD_ADDTIMER };
	CButton	m_ok;
	CComboBox	m_frequencylist;
	CListBox	m_channellist;
	CDateTimeCtrl	m_starttime;
	CDateTimeCtrl	m_endtime;
	CString	m_duration;
	CString	m_progname;
	CTime	m_endtimex;
	CTime	m_datex;
	CTime	m_starttimex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddTimer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//CTimeSpan duration;
	CTime today;
	void UpdateDuration();

	// Generated message map functions
	//{{AFX_MSG(CAddTimer)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEndTimeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartTimeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeChannellist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTIMER_H__AF71FA83_3646_11D4_A6E7_00D0B7221A0E__INCLUDED_)
