#if !defined(AFX_VIDEOLIBRARYDLG_H__A98414FB_325A_11D4_9418_009027A3343B__INCLUDED_)
#define AFX_VIDEOLIBRARYDLG_H__A98414FB_325A_11D4_9418_009027A3343B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoLibraryDlg.h : header file
//
#include "LibraryData.h"

//typedefs for linking to playback
typedef void (WINAPIV* pPlayFileDef) (HWND, LPCTSTR);
typedef BOOL (WINAPIV* P_GDFSE) (LPCTSTR, PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);


/////////////////////////////////////////////////////////////////////////////
// CVideoLibraryDlg dialog

class CVideoLibraryDlg : public CDialog
{
// Construction
public:
	CVideoLibraryDlg(CWnd* pParent = NULL, LPCTSTR LibraryPath = "");   // standard constructor
	void addToLibrary(LPCTSTR progname, 
					  LPCTSTR channel, 
					  LONG timedate, 
					  double duration, 
					  LPCTSTR path, 
					  int channelID);
	CString LibraryPath;

	BOOL CheckSpace(int duration);
	void SetLibraryPath(LPCTSTR LibraryPath);
	
// Dialog Data
	//{{AFX_DATA(CVideoLibraryDlg)
	enum { IDD = IDD_LIBRARY };
	CButton	m_recompress;
	CButton	m_playclip;
	CButton	m_filerename;
	CButton	m_delete;
	CListCtrl	m_librarylist;
	CString	m_libduration;
	CString	m_timeremain;
	CString	m_librarypath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoLibraryDlg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:


	TLibraryDataCollection m_LibraryData;
	BOOL CanSerialize();
	void LoadLibrary();
	void SaveLibrary();
	void FillLibraryList();
	void PlayVideo(LPCTSTR filename);
	void CalcStatistics();


	// Generated message map functions
	//{{AFX_MSG(CVideoLibraryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	afx_msg void OnFileRename();
	afx_msg void OnPlayClip();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnClickLibrarylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearch();
	afx_msg void OnRecompress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL LoadLibraryData();

};

static int CALLBACK CompareTime(LPARAM lparam1, LPARAM lparam2, LPARAM lparamsort);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOLIBRARYDLG_H__A98414FB_325A_11D4_9418_009027A3343B__INCLUDED_)
