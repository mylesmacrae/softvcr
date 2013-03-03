// ActiveMovieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "playback.h"
#include "ActiveMovieDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveMovieDlg dialog


CActiveMovieDlg::CActiveMovieDlg(LPCTSTR filename, CWnd* pParent /*=NULL*/)
	: CDialog(CActiveMovieDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CActiveMovieDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	lstrcpy(videoname,filename);
}


void CActiveMovieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveMovieDlg)
	DDX_Control(pDX, IDC_ACTIVEMOVIECONTROL2, m_activemovie);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActiveMovieDlg, CDialog)
	//{{AFX_MSG_MAP(CActiveMovieDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveMovieDlg message handlers

BOOL CActiveMovieDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	m_activemovie.SetFileName(videoname);
	m_activemovie.Run();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
