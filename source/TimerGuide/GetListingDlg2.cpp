// GetListingDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "GetListingDlg2.h"
#include "WebParser.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DATA_FILEG _T("ParserSettings.dat")

/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg2 dialog


CGetListingDlg2::CGetListingDlg2(TTimerDataArray * guidearray, CWnd* pParent /*=NULL*/)
	: CDialog(CGetListingDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetListingDlg2)
	m_date = 0;
	//}}AFX_DATA_INIT

	m_guidearray = guidearray;
}


void CGetListingDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetListingDlg2)
	DDX_Control(pDX, IDOK, m_okbutton);
	DDX_Control(pDX, IDCANCEL, m_cancelbutton);
	DDX_Control(pDX, IDC_ADDPARSER, m_addparser);
	DDX_Control(pDX, IDC_DATE, m_datectrl);
	DDX_Control(pDX, IDC_CHANNELCOMBO, m_channelcombo);
	DDX_Control(pDX, IDC_LISTINGCOMBO, m_listingcombo);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetListingDlg2, CDialog)
	//{{AFX_MSG_MAP(CGetListingDlg2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADDPARSER, OnAddParser)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATE, OnDatetimechangeDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg2 message handlers

BOOL CGetListingDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CTime now = CTime::GetCurrentTime();
	
	m_date = now;
	//m_starttime = CTime(2000,1,1,0,0,0);
	//m_endtime = CTime(2000,1,1,23,59,0);

	//m_starttimectrl.SetFormat("h:mm tt");
	//m_endtimectrl.SetFormat("h:mm tt");
	m_datectrl.SetFormat("ddd d MMMM yyyy");

	LoadRecords();
	FillChannelCombo();
	FillListingCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGetListingDlg2::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	CListingData* pListingData;

	int listingsize = m_listingdata.GetSize();

	for (int i = 0; i < listingsize; i++)
	{
		pListingData = m_listingdata.GetAt(0);
		m_listingdata.RemoveAt(0);
		delete pListingData;
	}

	ASSERT(NULL == m_listingdata.GetSize());
	
}

void CGetListingDlg2::Serialize(CArchive& ar) 
{
	m_listingdata.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CGetListingDlg2::CanSerialize()
{
	return (0 == _access(DATA_FILEG, 6));
}

void CGetListingDlg2::LoadRecords()
{
	if(CanSerialize())
	{
		CFile file;
		CFileException fe;

		if (file.Open(DATA_FILEG, CFile::typeBinary | CFile::modeRead, &fe))
		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
		}
	}
}

void CGetListingDlg2::FillListingCombo()
{
	CListingData * pListingData;

	int iIndex;

	m_listingcombo.ResetContent();

	for(int i = 0; i < m_listingdata.GetSize(); i++)
	{
		pListingData = m_listingdata.GetAt(i);

		if(pListingData)
		{
			if(CB_ERR != (iIndex = m_listingcombo.AddString(pListingData->m_parsername)))
			{
				m_listingcombo.SetItemData(iIndex, (DWORD)pListingData);
			}
		}
	}

	m_listingcombo.SetCurSel(0);
}

void CGetListingDlg2::SaveRecords()
{
	BOOL bCanSave = FALSE;

	UINT nFlags = CFile::typeBinary | CFile::modeWrite;

	if(_access(DATA_FILEG, 0))
	{
		nFlags |= CFile::modeCreate;
		bCanSave = TRUE;
	}
	else
	{
		bCanSave = CanSerialize();
	}

	if(bCanSave)
	{
		CFile file;
		CFileException fe;

		if (file.Open(DATA_FILEG, nFlags, &fe))
		{
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
		}
	}
}





void CGetListingDlg2::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);

	
	int cur = m_listingcombo.GetCurSel();
	CListingData * pListingData = (CListingData*)(m_listingcombo.GetItemData(cur));


	//Map channel num to channel
	int chan = m_channelcombo.GetItemData(m_channelcombo.GetCurSel());
	CString mappedid = pListingData->m_listingID.GetAt(chan);

	// Call the parser
	CWebParser theWebParser(pListingData->m_path);

	CString tempstr;
	m_channelcombo.GetLBText(m_channelcombo.GetCurSel(),tempstr);

	//this->ShowWindow(SW_HIDE);
	BeginWaitCursor();
	m_channelcombo.EnableWindow(FALSE);
	m_listingcombo.EnableWindow(FALSE);
	m_datectrl.EnableWindow(FALSE);
	m_addparser.EnableWindow(FALSE);
	m_okbutton.EnableWindow(FALSE);
	m_cancelbutton.EnableWindow(FALSE);

	m_guidearray->RemoveAll();

	theWebParser.getListing(m_guidearray,m_date,mappedid, tempstr, chan);

	SaveRecords();
	EndWaitCursor();
	
	CDialog::OnOK();
}



void CGetListingDlg2::OnAddParser() 
{
	// TODO: Add your control notification handler code here
	
	CParserSetup * parsersetup;
	CListingData * pListingData = NULL;
	CString temp;
	CFileDialog filedlg(TRUE,"lpf",NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,"Listing Parser Files (*.lpf)|*.lpf|All Files (*.*)|*.*||");

	int result2;
	int result = filedlg.DoModal();

	//I should display a file open dialog
	
	if (result == IDOK)
	{
		pListingData = new CListingData;

		pListingData->m_path = filedlg.GetPathName();

		parsersetup = new CParserSetup(pListingData->m_path);
	
	
		for (int i = 0 ; i < m_channelcombo.GetCount(); i++)
		{
			m_channelcombo.GetLBText(i,temp);
			parsersetup->SetChannelName(temp);
			result2 = parsersetup->DoModal();

			if (result2 == IDOK)
			{	
				pListingData->m_listingID.Add(parsersetup->GetSelChannelNum());
			}else{
				return;
			}
		}	
	
		pListingData->m_parsername = parsersetup->GetParserName();

		m_listingdata.Add(pListingData);
	
		delete parsersetup;

		FillListingCombo();
	}
	
}


void CGetListingDlg2::FillChannelCombo()
{
	
	CStdioFile * channelfile;
	
	channelfile = new CStdioFile("channel.inf", CFile::modeRead | CFile::shareDenyNone);

	CString channame, channum, currentline;
	int counter = 0;
	//int iIndex;
	
	m_channelcombo.ResetContent();

	while(channelfile->ReadString(currentline)){
		channame = currentline.SpanExcluding(" ");
		
		m_channelcombo.InsertString(counter,channame);
		m_channelcombo.SetItemData(counter,counter);
		counter++;
	}
	
	channelfile->Close();

	delete channelfile;

	m_channelcombo.SetCurSel(0);

	UpdateData(FALSE);
}

void CGetListingDlg2::OnCancel() 
{
	// TODO: Add extra cleanup here
	SaveRecords();
	CDialog::OnCancel();
}


void CGetListingDlg2::OnDatetimechangeDate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
