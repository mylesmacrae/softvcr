// FrequencyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "FrequencyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg dialog


CFrequencyDlg::CFrequencyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFrequencyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFrequencyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrequencyDlg)
	DDX_Control(pDX, IDC_FREQUENCYLIST, m_frequencylist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrequencyDlg, CDialog)
	//{{AFX_MSG_MAP(CFrequencyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrequencyDlg message handlers

void CFrequencyDlg::OnOK() 
{
	// TODO: Add extra validation here
	selfrequency = m_frequencylist.GetCurSel();
	
	CDialog::OnOK();
}

BOOL CFrequencyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_frequencylist.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
