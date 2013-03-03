// GetWeekList.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "GetWeekList.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DATA_FILEG _T("ParserSettings.dat")

/////////////////////////////////////////////////////////////////////////////
// CGetWeekList dialog


CGetWeekList::CGetWeekList(TTimerDataArray * guidearray, CWnd* pParent /*=NULL*/)
	: CDialog(CGetWeekList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetWeekList)
	m_progress = _T("");
	//}}AFX_DATA_INIT
	
	m_guidearray = guidearray;
}


void CGetWeekList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetWeekList)
	DDX_Control(pDX, IDC_COMBO1, m_source);
	DDX_Text(pDX, IDC_PROGSTRING, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetWeekList, CDialog)
	//{{AFX_MSG_MAP(CGetWeekList)
	ON_BN_CLICKED(IDC_BUTTON1, OnAddSource)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetWeekList message handlers

BOOL CGetWeekList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LoadRecords();
	FillChannelArray();
	FillListingCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGetWeekList::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	
	int cur = m_source.GetCurSel();
	CListingData * pListingData = (CListingData*)(m_source.GetItemData(cur));
	CString mappedid;
	CString currentchannel;
	// Call the parser
	CWebParser theWebParser(pListingData->m_path);
	//TTimerDataArray * currenttimerarray;
	CTime now = CTime::GetCurrentTime();
	CTime m_date;

	BeginWaitCursor();

	EmptyTimerList(m_guidearray);
	
	for(int j = 0; j<m_channelarray.GetSize(); j++)
	{

		//Map channel num to channel
		//int chan = m_channelcombo.GetItemData(m_channelcombo.GetCurSel());
		m_date = CTime(now.GetYear(),now.GetMonth(),now.GetDay(),0,0,0);
		mappedid = pListingData->m_listingID.GetAt(j);

		currentchannel = m_channelarray.GetAt(j);
		//currenttimerarray = m_guidearray->GetAt(j);
		//if(currenttimerarray == NULL) 
		//currenttimerarray = new TTimerDataArray;

		//m_channelcombo.GetLBText(m_channelcombo.GetCurSel(),tempstr);

		//this->ShowWindow(SW_HIDE)

		for(int k = 0; k<7 ; k++)
		{
			m_progress.Empty();
			m_progress += currentchannel;
			m_progress += " ";
			m_progress += m_date.Format("%d %B");
			UpdateData(FALSE);
			RedrawWindow(NULL,NULL,RDW_UPDATENOW);
			theWebParser.getListing(m_guidearray,m_date,mappedid, currentchannel, j);
			m_date += CTimeSpan(1,0,0,0);
		}
		//m_guidearray->Add(currenttimerarray);
	}

	SaveRecords();
	EndWaitCursor();
	
	
	CDialog::OnOK();
}

void CGetWeekList::OnAddSource() 
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
	
	
		for (int i = 0 ; i < m_channelarray.GetSize(); i++)
		{
			temp = m_channelarray.GetAt(i);
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

void CGetWeekList::OnDestroy() 
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

void CGetWeekList::EmptyTimerList(TTimerDataArray * timerlist)
{
	CTimerData* pTimerData;
	int timersize = timerlist->GetSize();

	for(int i = 0; i< timersize; i++)
	{
		pTimerData = timerlist->GetAt(0);
		timerlist->RemoveAt(0);
		delete pTimerData;
	}
	ASSERT(NULL == timerlist->GetSize());

}

void CGetWeekList::SaveRecords()
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

void CGetWeekList::LoadRecords()
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

BOOL CGetWeekList::CanSerialize()
{
	return (0 == _access(DATA_FILEG, 6));
}

void CGetWeekList::FillListingCombo()
{
	CListingData * pListingData;

	int iIndex;

	m_source.ResetContent();

	for(int i = 0; i < m_listingdata.GetSize(); i++)
	{
		pListingData = m_listingdata.GetAt(i);

		if(pListingData)
		{
			if(CB_ERR != (iIndex = m_source.AddString(pListingData->m_parsername)))
			{
				m_source.SetItemData(iIndex, (DWORD)pListingData);
			}
		}
	}

	m_source.SetCurSel(0);
}

void CGetWeekList::FillChannelArray()
{
	CStdioFile * channelfile;
	
	channelfile = new CStdioFile("channel.inf", CFile::modeRead | CFile::shareDenyNone);

	CString channame, channum, currentline;
	int counter = 0;
	//int iIndex;
	
	m_channelarray.RemoveAll();

	while(channelfile->ReadString(currentline)){
		channame = currentline.SpanExcluding(" ");
		
		m_channelarray.SetAtGrow(counter,channame);
		//m_channelcombo.SetItemData(counter,counter);
		counter++;
	}
	
	channelfile->Close();

	delete channelfile;

	//m_channelcombo.SetCurSel(0);

}

void CGetWeekList::Serialize(CArchive& ar) 
{
	m_listingdata.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

void CGetWeekList::OnCancel() 
{
	// TODO: Add extra cleanup here
	SaveRecords();
	
	CDialog::OnCancel();
}
