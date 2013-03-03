// RenameClip.cpp : implementation file
//

#include "stdafx.h"
#include "VidLibrary.h"
#include "RenameClip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenameClip dialog

CRenameClip::CRenameClip(LPTSTR clipname, CWnd* pParent /*=NULL*/)
	: CDialog(CRenameClip::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRenameClip)
	m_newname = _T("");
	m_origname = _T("");
	//}}AFX_DATA_INIT

	m_newname = clipname;
	m_origname = clipname;

}


void CRenameClip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenameClip)
	DDX_Text(pDX, IDC_NEWNAME, m_newname);
	DDV_MaxChars(pDX, m_newname, 255);
	DDX_Text(pDX, IDC_ORIGNAME, m_origname);
	DDV_MaxChars(pDX, m_origname, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRenameClip, CDialog)
	//{{AFX_MSG_MAP(CRenameClip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRenameClip::GetNewName(LPTSTR newname)
{
	lstrcpy(newname,m_newname.GetBuffer(256));
}
/////////////////////////////////////////////////////////////////////////////
// CRenameClip message handlers

