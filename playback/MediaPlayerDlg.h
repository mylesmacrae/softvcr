//{{AFX_INCLUDES()
#include "mediaplayer2.h"
//}}AFX_INCLUDES
#if !defined(AFX_MEDIAPLAYERDLG_H__EC223688_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
#define AFX_MEDIAPLAYERDLG_H__EC223688_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediaPlayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog

class CMediaPlayerDlg : public CDialog
{
// Construction
public:

	char videoname[256];

	CMediaPlayerDlg(LPCTSTR filename, CWnd* pParent);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CMediaPlayerDlg)
	enum { IDD = IDD_PLAYER };
	CMediaPlayer2	m_mplayer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMediaPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMediaPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnFullscreen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIAPLAYERDLG_H__EC223688_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
