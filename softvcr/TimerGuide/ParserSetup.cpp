// ParserSetup.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "ParserSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParserSetup dialog


CParserSetup::CParserSetup(CString path, CWnd* pParent /*=NULL*/)
	: CDialog(CParserSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParserSetup)
	m_currentchannel = _T("");
	//}}AFX_DATA_INIT
	m_path = path;
	


}


void CParserSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParserSetup)
	DDX_Control(pDX, IDC_LISTISTINGLIST, m_listinglist);
	DDX_Text(pDX, IDC_CURRENTCHANNEL, m_currentchannel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParserSetup, CDialog)
	//{{AFX_MSG_MAP(CParserSetup)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParserSetup message handlers

CString CParserSetup::GetParserName()
{
	return m_name;
}

CString CParserSetup::GetSelChannelNum()
{
	return m_cursel;
}

void CParserSetup::SetChannelName(CString name)
{
	m_currentchannel = name;
}

BOOL CParserSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int counter = 0;
	//char achbuff[256];

	CStdioFile thefile;
	CString currentline, channame;
	CString * channum;
	
	thefile.Open(m_path, CFile::modeRead | CFile::typeText);

	thefile.ReadString(currentline);
	if (currentline != "<LPF V1.0>"){
		thefile.Close();
		return FALSE;
	}


	while(currentline.Find("PARSERNAME") == -1)
	{
		thefile.ReadString(currentline);
	}

	channum = new CString;

	*channum = currentline.SpanExcluding(":");
	m_name = currentline.Right(currentline.GetLength() - channum->GetLength() - 1);

	delete channum;

	while(currentline.Find("<CHANNEL>") == -1)
	{
		thefile.ReadString(currentline);
	}

	thefile.ReadString(currentline);
	
	while(currentline.Find("</CHANNEL>") == -1)
	{
		channum = new CString;
		*channum = currentline.SpanExcluding(":");
		channame = currentline.Right(currentline.GetLength() - channum->GetLength() - 1);
		CString temp;

		if (m_selected.Lookup(*channum,temp) == NULL)
		{
			m_listinglist.InsertString(counter,channame);
			//lstrcpy(achbuf
			m_listinglist.SetItemData(counter,(DWORD)(channum));
			counter++;
		}

		thefile.ReadString(currentline);

	}

	thefile.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParserSetup::OnOK() 
{
	// TODO: Add extra validation here
	
	int cursel = m_listinglist.GetCurSel();

	if (cursel == CB_ERR){
		MessageBox("Please selext a channel from the list");
	}else{
		m_cursel = *((CString*)(m_listinglist.GetItemData(cursel)));
		m_selected.SetAt(m_cursel,m_cursel);
		CDialog::OnOK();
	}

}

void CParserSetup::OnDestroy() 
{
	CDialog::OnDestroy();
	CString * tempst;

	for(int i = 0; i < m_listinglist.GetCount(); i++)
	{
		tempst = (CString*)(m_listinglist.GetItemData(i));
		delete tempst;
	}

	
	// TODO: Add your message handler code here
	
}
