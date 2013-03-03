// GetListingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "GetListingDlg.h"
#include "ParserSetup.h"
#include "WebParser.h"
#include <io.h>
#include <fstream.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DATA_FILEG _T("ListingData.dat")

/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg dialog


CGetListingDlg::CGetListingDlg(TTimerDataArray* guidedata, CWnd* pParent /*=NULL*/)
	: CDialog(CGetListingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetListingDlg)
	m_date = 0;
	m_endtime = 0;
	m_starttime = 0;
	//}}AFX_DATA_INIT

	m_guidedata = guidedata;
	LoadSettings();
}


void CGetListingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetListingDlg)
	DDX_Control(pDX, IDC_CHANNELCOMBO, m_channelcombo);
	DDX_Control(pDX, IDC_LISTINGCOMBO, m_listingcombo);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_date);
	DDX_DateTimeCtrl(pDX, IDC_ENDTIME, m_endtime);
	DDX_DateTimeCtrl(pDX, IDC_STARTTIME, m_starttime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetListingDlg, CDialog)
	//{{AFX_MSG_MAP(CGetListingDlg)
	ON_BN_CLICKED(IDC_ADDPARSER, OnAddParser)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CGetListingDlg message handlers

BOOL CGetListingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	FillListingCombo();
	FillChannelCombo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGetListingDlg::OnAddParser() 
{
	// TODO: Add your control notification handler code here
	CParserSetup * parsersetup;
	CListingData * pListingData;
	CFileDialog filedlg(TRUE,"lpf",NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,"Listing Parser Files (*.lpf)|*.lpf|All Files (*.*)|*.*||");

	filedlg.DoModal();

	//I should display a file open dialog
	
	pListingData = new CListingData;

	pListingData->m_path = filedlg.GetPathName();

	parsersetup = new CParserSetup(pListingData->m_path);
	


	for (int i = 0 ; i < channelarray.GetSize(); i++)
	{
		parsersetup->SetChannelName(channelarray.GetAt(i));
		int result = parsersetup->DoModal();

		if (result == IDOK)
		{
			//pListingData->m_listingID.Add(parsersetup->GetSelChannelNum());
		}
	}

	pListingData->m_parsername = parsersetup->GetParserName();

	m_listingdata.Add(pListingData);
	FillListingCombo();
	SaveSettings();

}

void CGetListingDlg::Serialize(CArchive& ar) 
{
	m_listingdata.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

/*
void CGetListingDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	POSITION pos;
	CString strKey;
	CListingData * pListingData;

	pos = m_listingdata.GetStartPosition();
	while(NULL != pos)
	{
		m_listingdata.GetNextAssoc(pos, strKey, pListingData);
		if (pListingData)
		{
			m_listingdata.RemoveKey(strKey);
			delete pListingData;
		}
	}
	ASSERT(NULL == m_listingdata.GetCount());
}
*/
void CGetListingDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CListingData * pListingData;

	for(int i = 0 ; i < m_listingdata.GetSize() ; i++)
	{
		pListingData = m_listingdata.GetAt(i);
		if (pListingData)
		{
			delete pListingData;
		}
	}
}

BOOL CGetListingDlg::CanSerialize()
{
	return(0 == _access(DATA_FILEG,6));
}

void CGetListingDlg::LoadSettings()
{
	if(CanSerialize())
	{
		CFile file;
		CFileException fe;

		if(file.Open(DATA_FILEG, CFile::typeBinary | CFile::modeRead, &fe))
		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
		}
	}
}

void CGetListingDlg::SaveSettings()
{
	BOOL bCanSave = FALSE;

	UINT nFlags = CFile::typeBinary | CFile::modeWrite;

	// file doesn't exist, so create it
	if (_access(DATA_FILEG, 0))
	{
		nFlags |= CFile::modeCreate;
		bCanSave = TRUE;
	}
	else
	{
		bCanSave = CanSerialize();
	}

	if (bCanSave)
	{
		CFile file;
		CFileException fe;

		// file exists with read & write permissions
		if(file.Open(DATA_FILEG, nFlags, &fe))
		{
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
		}
	}
}

void CGetListingDlg::FillListingCombo()
{
	POSITION pos;
	CString strKey;
	CListingData * pListingData;

	int currentrow = 0;

	m_listingcombo.ResetContent();

	for(int i = 0; i< m_listingdata.GetSize(); i++)
	{
		pListingData = m_listingdata.GetAt(i);

		if (pListingData)
		{
		    //read programme name
			m_listingcombo.InsertString(i, pListingData->m_parsername);
			
			//Finally, add the pLibraryData structure as ItemData
			m_listingcombo.SetItemData(i,(DWORD)pListingData);
						
		}
	}
}

void CGetListingDlg::FillChannelCombo()
{
	ifstream channelfile("channel.inf", ios::in | ios::nocreate);
	char buf[10];
	CString temp;
	int counter = 0;
	
	if(!channelfile.fail())
	{
		while(!channelfile.eof()){
			channelfile.getline(buf, 20, ' ');
			temp.Format(_T(buf));
			m_channelcombo.AddString(temp);
			channelarray.Add(temp);
			m_channelcombo.SetItemData(counter,counter);
			channelfile.getline(buf, 20, '\n');
			counter++;
		}
	
		channelfile.close();

	}

	UpdateData(FALSE);


}
void CGetListingDlg::OnOK() //Actually this is the Get Listings button :-)
{
	// TODO: Add extra validation here

	UpdateData(TRUE);


	
	int cur = m_listingcombo.GetCurSel();
	CListingData * pListingData = (CListingData*)(m_listingcombo.GetItemData(cur));


	//Map channel num to channel
	int chan = m_channelcombo.GetCurSel();
	int mappedid = 0;//pListingData->m_listingID.GetAt(chan);

	// Call the parser
	CWebParser theWebParser(pListingData->m_path);


	theWebParser.getListing(m_guidedata,m_date,m_starttime,m_endtime,mappedid);
	
	SaveSettings();
	CDialog::OnOK();
}

void CGetListingDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	SaveSettings();
	
	CDialog::OnCancel();
}
