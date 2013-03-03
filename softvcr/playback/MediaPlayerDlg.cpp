// MediaPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "playback.h"
#include "MediaPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog


CMediaPlayerDlg::CMediaPlayerDlg(LPCTSTR filename, CWnd* pParent /*=NULL*/)
	: CDialog(CMediaPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMediaPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	AfxEnableControlContainer();
	lstrcpy(videoname,filename);
}


void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMediaPlayerDlg)
	DDX_Control(pDX, IDC_MEDIAPLAYER1, m_mplayer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMediaPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMediaPlayerDlg)
	ON_BN_CLICKED(IDC_FULLSCREEN, OnFullscreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg message handlers

BOOL CMediaPlayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_mplayer.SetFileName(videoname);
	m_mplayer.SetVolume(-700);
	m_mplayer.Play();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMediaPlayerDlg::OnFullscreen() 
{
	// TODO: Add your control notification handler code here
	m_mplayer.SetDisplaySize(3);
	
}
