// SearchLibDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VidLibrary.h"
#include "SearchLibDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "LibraryData.h"
/////////////////////////////////////////////////////////////////////////////
// CSearchLibDlg dialog


CSearchLibDlg::CSearchLibDlg(CListCtrl * theList, CWnd* pParent /*=NULL*/)
	: CDialog(CSearchLibDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchLibDlg)
	m_searchstring = _T("");
	m_searchdate = 0;
	//}}AFX_DATA_INIT

	m_vidlib = theList;
}


void CSearchLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchLibDlg)
	DDX_Control(pDX, IDC_EDIT1, m_searchnamectrl);
	DDX_Control(pDX, IDC_RADIO4, m_searchbyname);
	DDX_Control(pDX, IDC_RADIO5, m_searchbydate);
	DDX_Text(pDX, IDC_EDIT1, m_searchstring);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_searchdate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchLibDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchLibDlg)
	ON_BN_CLICKED(IDC_RADIO5, OnSearchDateButton)
	ON_BN_CLICKED(IDC_RADIO4, OnSearchNameButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchLibDlg message handlers



void CSearchLibDlg::OnSearchDateButton() 
{
	// TODO: Add your control notification handler code here
	m_searchnamectrl.EnableWindow(FALSE);
	//m_searchdatectrl.EnableWindow(TRUE);
	//UpdateData(FALSE);
}

void CSearchLibDlg::OnSearchNameButton() 
{
	// TODO: Add your control notification handler code here
	m_searchnamectrl.EnableWindow(TRUE);
	//m_searchdatectrl.EnableWindow(FALSE);
	//UpdateData(FALSE);
	
}

void CSearchLibDlg::OnOK() 
{
	// TODO: Add extra validation here
	// Depending on which radio box is selected, I check the list for all
	// matching entries and mark them selected
	int nCount = m_vidlib->GetItemCount();
	CLibraryData * currentdata;


	UpdateData(TRUE);

	//CTime selecteddate;
	//m_searchdatectrl.GetCurSel(selecteddate);

	if(m_searchbyname.GetCheck() == BST_CHECKED)
	{
		//Search by Prog Name
		CString temp;

		m_searchstring.TrimLeft();
		m_searchstring.TrimRight();
		m_searchstring.MakeLower();

		for(int i = 0; i< nCount; i++)
		{
			currentdata = (CLibraryData*)m_vidlib->GetItemData(i);
			temp = currentdata->m_programme;
			temp.MakeLower();

			if(temp.Find(m_searchstring,0) >=0)
			{
				//Search string is in this item, mark it.
				m_vidlib->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			}else{
				m_vidlib->SetItemState(i, 0, LVIS_SELECTED);
			}
		}

	}
	else if (m_searchbydate.GetCheck() == BST_CHECKED)
	{
			
		//Search by Date
		for(int j = 0; j< nCount; j++)
		{
			currentdata = (CLibraryData*)m_vidlib->GetItemData(j);

			if((currentdata->m_timedate.GetYear() == m_searchdate.GetYear()) &&
			   (currentdata->m_timedate.GetMonth() == m_searchdate.GetMonth()) &&
			   (currentdata->m_timedate.GetDay() == m_searchdate.GetDay()))
			   //if((currentdata->m_timedate.GetYear() == selecteddate.GetYear()) &&
			   //(currentdata->m_timedate.GetMonth() == selecteddate.GetMonth()) &&
			   //(currentdata->m_timedate.GetDay() == selecteddate.GetDay()))
			{
			   m_vidlib->SetItemState(j, LVIS_SELECTED, LVIS_SELECTED);
			}else{
				m_vidlib->SetItemState(j, 0, LVIS_SELECTED);
			}
		}
	}
	
	CDialog::OnOK();
}

BOOL CSearchLibDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime now = CTime::GetCurrentTime();

	m_searchdate = now;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
