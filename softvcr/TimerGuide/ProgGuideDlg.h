#if !defined(AFX_PROGGUIDEDLG_H__C21983D5_3625_11D4_941C_009027A3343B__INCLUDED_)
#define AFX_PROGGUIDEDLG_H__C21983D5_3625_11D4_941C_009027A3343B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgGuideDlg.h : header file
//

#include "TimerData.h"
#include "TimerDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CProgGuideDlg dialog

class CProgGuideDlg : public CDialog
{
// Construction
public:
	CProgGuideDlg(int currchan, LPCTSTR librarypath, CWnd* pParent = NULL);   // standard constructor
	~CProgGuideDlg();
	BOOL CanSerialize();
	void LoadGuide();
	void SaveGuide();
	void FillGuideList();
	void FillTimerList();
	void FillChannelList();
	void FillDateList();
	BOOL getCurrentProg(LPSTR progname, int currchan);
	CString getProg(int currchan, CTime progtime);
	BOOL checkGuideValidity();

	LPCTSTR LibraryPath;

// Dialog Data
	//{{AFX_DATA(CProgGuideDlg)
	enum { IDD = IDD_GUIDDLG };
	CComboBox	m_dispdate;
	CComboBox	m_dispchan;
	CButton	m_addtotimer;
	CButton	m_removetimer;
	CButton	m_showdesc;
	CListCtrl	m_timerlist;
	CListCtrl	m_progguidelist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgGuideDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	TTimerDataArray m_guidearray;
	CTimerDlg * timerdlg;
	CTime m_expirydate;
	int m_currentchannel;

	void DestroyGuide();

	// Generated message map functions
	//{{AFX_MSG(CProgGuideDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	afx_msg void OnRemoveTimer();
	afx_msg void OnGetListings();
	afx_msg void OnAddTimer();
	afx_msg void OnClickProgGuide(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTimerList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowDesc();
	afx_msg void OnSelchangeDispchan();
	afx_msg void OnSelchangeDispdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGGUIDEDLG_H__C21983D5_3625_11D4_941C_009027A3343B__INCLUDED_)
