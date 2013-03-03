// WebDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "WebDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWebDialog dialog


CWebDialog::CWebDialog(CString URL, CWnd* pParent /*=NULL*/)
	: CDialog(CWebDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWebDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_url = URL;
	AfxEnableControlContainer();
	CoInitialize(NULL);
}


void CWebDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWebDialog)
	DDX_Control(pDX, IDC_EXPLORER3, m_WebBrowser);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWebDialog, CDialog)
	//{{AFX_MSG_MAP(CWebDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWebDialog message handlers

BOOL CWebDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	
	m_WebBrowser.Navigate(m_url, NULL, NULL, NULL, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
