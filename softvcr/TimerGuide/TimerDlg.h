#if !defined(AFX_TIMERDLG_H__C002047D_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_)
#define AFX_TIMERDLG_H__C002047D_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimerDlg.h : header file
//

#include "TimerData.h"

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

#define TIMER_ONCE		0
#define TIMER_DAILY		1
#define TIMER_WEEKLY	2
#define TIMER_WEEKDAY	3
#define TIMER_WEEKEND	4

class CTimerDlg : public CDialog
{
// Construction
public:
	CTimerDlg(LPCTSTR librarypath, CWnd* pParent = NULL);   // standard constructor

	BOOL CanSerialize();
	void LoadRecords();
	void SaveRecords();
	void FillTimerList();
	BOOL CheckSpace(int duration);

	BOOL addToTimer(LPCTSTR progname, 
					  DWORD starttime, 
					  DWORD endtime,
					  LPCTSTR channel,
					  int channelID,
					  int frequency);
	BOOL addToTimer(CTimerData * pTimerData);

	BOOL getNextTimer(DWORD timenow, LPSTR progname, DWORD * starttime, int * duration, int * channelID);

	TTimerDataArray m_timerarray;
	LPCTSTR LibraryPath;

// Dialog Data
	//{{AFX_DATA(CTimerDlg)
	enum { IDD = IDD_TIMERDLG };
	CListCtrl	m_timerlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnAddtimer();
	afx_msg void OnDeletetimer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDLG_H__C002047D_360E_11D4_A6E7_00D0B7221A0E__INCLUDED_)
