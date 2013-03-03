//{{AFX_INCLUDES()
#include "producercontrol2.h"
//}}AFX_INCLUDES
#if !defined(AFX_RECOMPRESSDLG_H__D0B1C248_3D77_11D4_A6DD_009027D11084__INCLUDED_)
#define AFX_RECOMPRESSDLG_H__D0B1C248_3D77_11D4_A6DD_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecompressDlg.h : header file
//
#include "LibraryData.h"
/////////////////////////////////////////////////////////////////////////////
// CRecompressDlg dialog

class CRecompressDlg : public CDialog
{
// Construction
public:
	CRecompressDlg(CLibraryData * filetocompress, CWnd* pParent = NULL);   // standard constructor
	BOOL quittotimer;

// Dialog Data
	//{{AFX_DATA(CRecompressDlg)
	enum { IDD = IDD_REALPRODUCER };
	CProgressCtrl	m_encodeprogress;
	CProducerControl2	m_producercontrol;
	BOOL	m_timerreturn;
	CString	m_stprogress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecompressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CLibraryData * m_filetocompress;
	CString m_oldfilename;
	BOOL usercancel;
	CTime timenow;
	CTime timestart;


	// Generated message map functions
	//{{AFX_MSG(CRecompressDlg)
	afx_msg void OnEncodingStoppedRP();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnOnEncodingProgressChanged(long duration, long timestamp, long PercentDone, long AudioPeakLevel);
	virtual void OnCancel();
	afx_msg void OnTimerreturn();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECOMPRESSDLG_H__D0B1C248_3D77_11D4_A6DD_009027D11084__INCLUDED_)
