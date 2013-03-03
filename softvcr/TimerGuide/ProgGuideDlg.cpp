// ProgGuideDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "ProgGuideDlg.h"
#include "GetListingDlg2.h"
#include "GetWeekList.h"
#include "WebDialog.h"
#include "FrequencyDlg.h"
#include "../libraryexport.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_P_STARTTIME	1
#define COL_P_ENDTIME	2
#define COL_P_PROGNAME	0
#define COL_P_CHANNEL	4
#define COL_P_DURATION	3
#define COL_P_FREQUENCY	5


#define COL_T_STARTTIME	2
#define COL_T_ENDTIME	3
#define COL_T_PROGNAME	0
#define COL_T_CHANNEL	1
#define COL_T_DURATION	4
#define COL_T_FREQUENCY	5


#define DATA_FILE _T("ProgGuide.dat")

/////////////////////////////////////////////////////////////////////////////
// CProgGuideDlg dialog


CProgGuideDlg::CProgGuideDlg(int currchan, LPCTSTR librarypath, CWnd* pParent /*=NULL*/)
	: CDialog(CProgGuideDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgGuideDlg)
	//}}AFX_DATA_INIT
	timerdlg = new CTimerDlg(librarypath, NULL);
	m_currentchannel = currchan;

	LibraryPath = librarypath;
}
CProgGuideDlg::~CProgGuideDlg()
{
	delete timerdlg;
	CDialog::~CDialog();
}


void CProgGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgGuideDlg)
	DDX_Control(pDX, IDC_DISPDATE, m_dispdate);
	DDX_Control(pDX, IDC_DISPCHAN, m_dispchan);
	DDX_Control(pDX, IDC_ADDTOTTIMER, m_addtotimer);
	DDX_Control(pDX, IDC_REMOVETIMER, m_removetimer);
	DDX_Control(pDX, IDC_SHOWDESC, m_showdesc);
	DDX_Control(pDX, IDC_TIMERLIST, m_timerlist);
	DDX_Control(pDX, IDC_ProgGuide, m_progguidelist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgGuideDlg, CDialog)
	//{{AFX_MSG_MAP(CProgGuideDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_REMOVETIMER, OnRemoveTimer)
	ON_BN_CLICKED(IDC_GetListings, OnGetListings)
	ON_BN_CLICKED(IDC_ADDTOTTIMER, OnAddTimer)
	ON_NOTIFY(NM_CLICK, IDC_ProgGuide, OnClickProgGuide)
	ON_NOTIFY(NM_CLICK, IDC_TIMERLIST, OnClickTimerList)
	ON_BN_CLICKED(IDC_SHOWDESC, OnShowDesc)
	ON_CBN_SELCHANGE(IDC_DISPCHAN, OnSelchangeDispchan)
	ON_CBN_SELCHANGE(IDC_DISPDATE, OnSelchangeDispdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgGuideDlg message handlers

BOOL CProgGuideDlg::CanSerialize()
{
	return (0 == _access(DATA_FILE, 6));
}

void CProgGuideDlg::LoadGuide()
{
	if (CanSerialize())
	{
		CFile file;
		CFileException fe;

		if (file.Open(DATA_FILE, CFile::typeBinary | CFile::modeRead, &fe))

		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
		}
	}
}

void CProgGuideDlg::SaveGuide()
{
	BOOL bCanSave = FALSE;

	UINT nFlags = CFile::typeBinary | CFile::modeWrite;

	if (_access(DATA_FILE, 0))
	{
		nFlags |= CFile::modeCreate;
		bCanSave = TRUE;
	}else{
		bCanSave = CanSerialize();
	}

	if (bCanSave)
	{
		CFile file;
		CFileException fe;

		if (file.Open(DATA_FILE, nFlags, &fe))
		{
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
		}
	}
}

void CProgGuideDlg::FillGuideList()
{
	CString strKey;
	CTimerData * pProgGuideData;
	CTime timenow = CTime::GetCurrentTime();
	CTime currentstarttime, currentendtime;
	int selchannel = m_dispchan.GetCurSel();
	CTime seldate((time_t) m_dispdate.GetItemData(m_dispdate.GetCurSel()));

	int currentrow = 0;

	m_progguidelist.DeleteAllItems();

	this->SetRedraw(FALSE);

	for(int i = 0; i<m_guidearray.GetSize(); i++)
	{
		pProgGuideData = m_guidearray.GetAt(i);

		
		if (pProgGuideData)
		{

			//I want to check whether its in the past..  if so, delete it

			//I then want to check if its the right date and channel, only then do I display it
			currentstarttime = CTime(pProgGuideData->m_starttime);
			currentendtime = CTime(pProgGuideData->m_endtime);
			if((currentstarttime.GetDay() == seldate.GetDay()) && 
				(pProgGuideData->m_channelID == selchannel) &&
				(currentendtime > timenow))
			{
			
			//Set Progname
			m_progguidelist.InsertItem(currentrow, pProgGuideData->m_programme, COL_P_PROGNAME);
			m_progguidelist.SetColumnWidth(COL_P_PROGNAME,LVSCW_AUTOSIZE);
			int nCurrWidth = m_progguidelist.GetColumnWidth(COL_P_PROGNAME);
			m_progguidelist.SetColumnWidth(COL_P_PROGNAME,LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_progguidelist.GetColumnWidth(COL_P_PROGNAME);
			m_progguidelist.SetColumnWidth(COL_P_PROGNAME, max(nCurrWidth,nColHdrWidth));

			
			//Set Starttime (saved as DWORD)
			CTime * st;
			st = new CTime((time_t)(pProgGuideData->m_starttime));
			CString sttemp = st->Format("%#I.%M%p");
			m_progguidelist.SetItemText(currentrow, COL_P_STARTTIME, sttemp);
			m_progguidelist.SetColumnWidth(COL_P_STARTTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_progguidelist.GetColumnWidth(COL_P_STARTTIME);
			m_progguidelist.SetColumnWidth(COL_P_STARTTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_progguidelist.GetColumnWidth(COL_P_STARTTIME);
			m_progguidelist.SetColumnWidth(COL_P_STARTTIME, max(nCurrWidth,nColHdrWidth));
			delete st;
			
			//Set Endtime
			st = new CTime((time_t)(pProgGuideData->m_endtime));
			if(st->GetSecond() != 0) *st += CTimeSpan(0,0,1,0);
			sttemp = st->Format("%#I.%M%p");
			m_progguidelist.SetItemText(currentrow, COL_P_ENDTIME, sttemp);
			m_progguidelist.SetColumnWidth(COL_P_ENDTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_progguidelist.GetColumnWidth(COL_P_ENDTIME);
			m_progguidelist.SetColumnWidth(COL_P_ENDTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_progguidelist.GetColumnWidth(COL_P_ENDTIME);
			m_progguidelist.SetColumnWidth(COL_P_ENDTIME, max(nCurrWidth,nColHdrWidth));
			delete st;

			//set duration
			CTimeSpan sd = pProgGuideData->m_endtime - pProgGuideData->m_starttime;
			sttemp.Empty();
			//if(sd.GetHours()>0) sttemp += sd.Format("%Hhr");
			//if(sd.GetMinutes()>0) // sttemp += sd.Format("%Mmin");
			//if(sd.GetSeconds()>0)
			//{
			int t = sd.GetTotalMinutes() + 1;
			//CString tt;
			sttemp.Format("%0.2dmin", t);
			//}
			m_progguidelist.SetItemText(currentrow, COL_P_DURATION, sttemp);
			m_progguidelist.SetColumnWidth(COL_P_DURATION,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_P_DURATION);
			m_progguidelist.SetColumnWidth(COL_P_DURATION,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_P_DURATION);
			m_progguidelist.SetColumnWidth(COL_P_DURATION, max(nCurrWidth,nColHdrWidth));



			
			//read time/date
			m_progguidelist.SetItemText(currentrow, COL_P_CHANNEL, pProgGuideData->m_channel);
			m_progguidelist.SetColumnWidth(COL_P_CHANNEL,LVSCW_AUTOSIZE);
			nCurrWidth = m_progguidelist.GetColumnWidth(COL_P_CHANNEL);
			m_progguidelist.SetColumnWidth(COL_P_CHANNEL,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_progguidelist.GetColumnWidth(COL_P_CHANNEL);
			m_progguidelist.SetColumnWidth(COL_P_CHANNEL, max(nCurrWidth,nColHdrWidth));

			//Finally, add the pLibraryData structure as ItemData
			m_progguidelist.SetItemData(currentrow,(DWORD)pProgGuideData);
			currentrow++;
			}
		
		}
	}

	this->SetRedraw(TRUE);
	this->Invalidate();
}

void CProgGuideDlg::FillChannelList()
{
	CStdioFile * channelfile;
	
	channelfile = new CStdioFile("channel.inf", CFile::modeRead | CFile::shareDenyNone);

	CString channame, channum, currentline;
	int counter = 0;
	//int iIndex;
	
	m_dispchan.ResetContent();

	while(channelfile->ReadString(currentline)){
		channame = currentline.SpanExcluding(" ");
		
		m_dispchan.InsertString(counter,channame);
		m_dispchan.SetItemData(counter,counter);
		counter++;
	}
	
	channelfile->Close();

	delete channelfile;

	m_dispchan.SetCurSel(m_currentchannel);

	UpdateData(FALSE);

}

void CProgGuideDlg::FillDateList()
{
	CTime now = CTime::GetCurrentTime();
	CTime tempdate(now.GetYear(),now.GetMonth(),now.GetDay(),0,0,0);
	DWORD currentdate;

	CTimeSpan temp = m_expirydate - now;

	m_dispdate.ResetContent();

	for (int i = 0; i <= temp.GetDays(); i++)
	{
		m_dispdate.InsertString(i,tempdate.Format("%a %d %B"));
		currentdate = (DWORD)tempdate.GetTime();
		m_dispdate.SetItemData(i,currentdate);
		tempdate += CTimeSpan(1,0,0,0);
	}

	m_dispdate.SetCurSel(0);

	UpdateData(FALSE);

}

void CProgGuideDlg::FillTimerList()
{
	CString strKey;
	CTimerData * pTimerData;

	int currentrow = 0;

	m_timerlist.DeleteAllItems();

	this->SetRedraw(FALSE);

	for(int i = 0; i<timerdlg->m_timerarray.GetSize(); i++)
	{
		pTimerData = timerdlg->m_timerarray.GetAt(i);
		
		if (pTimerData)
		{

		//Set Progname
			m_timerlist.InsertItem(i, pTimerData->m_programme, COL_T_PROGNAME);
			m_timerlist.SetColumnWidth(COL_T_PROGNAME,LVSCW_AUTOSIZE);
			int nCurrWidth = m_timerlist.GetColumnWidth(COL_T_PROGNAME);
			m_timerlist.SetColumnWidth(COL_T_PROGNAME,LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_PROGNAME);
			m_timerlist.SetColumnWidth(COL_T_PROGNAME, max(nCurrWidth,nColHdrWidth));

			//Set Starttime (saved as DWORD)
			CTime * st;
			st = new CTime((time_t)(pTimerData->m_starttime));
			CString sttemp = st->Format("%#I.%M%p %a %b %#d");
			m_timerlist.SetItemText(i, COL_T_STARTTIME, sttemp);
			m_timerlist.SetColumnWidth(COL_T_STARTTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_T_STARTTIME);
			m_timerlist.SetColumnWidth(COL_T_STARTTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_STARTTIME);
			m_timerlist.SetColumnWidth(COL_T_STARTTIME, max(nCurrWidth,nColHdrWidth));
			delete st;
			
			//Set Endtime
			st = new CTime((time_t)(pTimerData->m_endtime));
			if(st->GetSecond() != 0) *st += CTimeSpan(0,0,1,0);
			sttemp = st->Format("%#I.%M%p %a");
			m_timerlist.SetItemText(i, COL_T_ENDTIME, sttemp);
			m_timerlist.SetColumnWidth(COL_T_ENDTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_T_ENDTIME);
			m_timerlist.SetColumnWidth(COL_T_ENDTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_ENDTIME);
			m_timerlist.SetColumnWidth(COL_T_ENDTIME, max(nCurrWidth,nColHdrWidth));
			delete st;

			//set duration
			CTimeSpan sd = pTimerData->m_endtime - pTimerData->m_starttime;
			sttemp.Empty();
			//if(sd.GetHours()>0) sttemp += sd.Format("%Hhr");
			//if(sd.GetMinutes()>0) // sttemp += sd.Format("%Mmin");
			//if(sd.GetSeconds()>0)
			//{
				int t = sd.GetTotalMinutes() + 1;
				//CString tt;
				sttemp.Format("%0.2dmin", t);
				//sttemp+=tt;
			//}
			m_timerlist.SetItemText(i, COL_T_DURATION, sttemp);
			m_timerlist.SetColumnWidth(COL_T_DURATION,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_T_DURATION);
			m_timerlist.SetColumnWidth(COL_T_DURATION,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_DURATION);
			m_timerlist.SetColumnWidth(COL_T_DURATION, max(nCurrWidth,nColHdrWidth));
		

			//read time/date
			m_timerlist.SetItemText(i, COL_T_CHANNEL, pTimerData->m_channel);
			m_timerlist.SetColumnWidth(COL_T_CHANNEL,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_T_CHANNEL);
			m_timerlist.SetColumnWidth(COL_T_CHANNEL,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_CHANNEL);
			m_timerlist.SetColumnWidth(COL_T_CHANNEL, max(nCurrWidth,nColHdrWidth));

			//set frequency
			sttemp.Empty();
			switch(pTimerData->m_frequency)
			{
			case TIMER_ONCE:
				sttemp = "Once";
				break;
			case TIMER_DAILY:
				sttemp = "Daily";
				break;
			case TIMER_WEEKLY:
				sttemp = "Weekly";
				break;
			case TIMER_WEEKDAY:
				sttemp = "Week Days";
				break;
			case TIMER_WEEKEND:
				sttemp = "Weekends";
				break;
			}
			m_timerlist.SetItemText(i, COL_T_FREQUENCY, sttemp);
			m_timerlist.SetColumnWidth(COL_T_FREQUENCY,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_T_FREQUENCY);
			m_timerlist.SetColumnWidth(COL_T_FREQUENCY,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_T_FREQUENCY);
			m_timerlist.SetColumnWidth(COL_T_FREQUENCY, max(nCurrWidth,nColHdrWidth));


			//Finally, add the pLibraryData structure as ItemData
		
		}
	}

	this->SetRedraw(TRUE);
	this->Invalidate();
}

BOOL CProgGuideDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	// Create Coloumns : Programme Name ; Channel ; Time/Date Recorded ; filename?
	


	static struct
	{
		LPTSTR szColText;
		UINT uiFormat;
	} gcolumns[] = {
		_T("Programme Name"), LVCFMT_LEFT,
		_T("Start Time"), LVCFMT_LEFT,
		_T("End Time"), LVCFMT_LEFT,
		_T("Duration"), LVCFMT_LEFT,
	};

	static struct
	{
		LPSTR szColText;
		UINT uiFormat;
	} tcolumns[] = {
		_T("Programme Name"), LVCFMT_LEFT,
		_T("Channel"), LVCFMT_LEFT,
		_T("Start Time"), LVCFMT_LEFT,
		_T("End Time"), LVCFMT_LEFT,
		_T("Duration"), LVCFMT_LEFT,
		_T("Frequency"), LVCFMT_LEFT
	};


	for (int i = 0; i < sizeof tcolumns / sizeof tcolumns [0]; i++){
		m_timerlist.InsertColumn(i, tcolumns[i].szColText, tcolumns[i].uiFormat);
	
	}
	for (int j = 0; j < sizeof gcolumns / sizeof gcolumns [0]; j++){
		m_progguidelist.InsertColumn(j, gcolumns[j].szColText, gcolumns[j].uiFormat);
	
	}
	// Resize columns

	CHeaderCtrl* pTimerHeader = (CHeaderCtrl*)m_timerlist.GetDlgItem(0);
	CHeaderCtrl* pProgGuideHeader = (CHeaderCtrl*)m_progguidelist.GetDlgItem(0);

	ASSERT(pTimerHeader);
	ASSERT(pProgGuideHeader);

	if(pTimerHeader && pProgGuideHeader)
	{
		//turn off redraw until colums have been resized
		m_timerlist.SetRedraw(FALSE);
		m_progguidelist.SetRedraw(FALSE);

		//get number of columns
		int iTimerNumberCols = pTimerHeader->GetItemCount();
		int iGuideNumberCols = pProgGuideHeader->GetItemCount();
		//int iNumberCols = GetColumnCount();
		
		for (int iCurrentCol = 0; iCurrentCol < iTimerNumberCols; iCurrentCol++)
		{
			m_timerlist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE);

			int nCurrWidth = m_timerlist.GetColumnWidth(iCurrentCol);

			m_timerlist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE_USEHEADER);

			int nColHdrWidth = m_timerlist.GetColumnWidth(iCurrentCol);

			m_timerlist.SetColumnWidth(iCurrentCol, max(nCurrWidth,nColHdrWidth));
		}

		for (iCurrentCol = 0; iCurrentCol < iGuideNumberCols; iCurrentCol++)
		{
			m_progguidelist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE);

			int nCurrWidth = m_progguidelist.GetColumnWidth(iCurrentCol);

			m_progguidelist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE_USEHEADER);

			int nColHdrWidth = m_progguidelist.GetColumnWidth(iCurrentCol);

			m_progguidelist.SetColumnWidth(iCurrentCol, max(nCurrWidth,nColHdrWidth));
		}

		m_timerlist.SetRedraw(TRUE);
		m_progguidelist.SetRedraw(TRUE);
		m_timerlist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		m_progguidelist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		m_timerlist.Invalidate();
		m_progguidelist.Invalidate();
	}

	
	checkGuideValidity();
	//m_dispchan.SetCurSel(m_currentchannel);
	LoadGuide();
	FillChannelList();
	FillDateList();
	
	FillGuideList();
	FillTimerList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgGuideDlg::Serialize(CArchive& ar) 
{
	m_guidearray.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

void CProgGuideDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	// TODO: Add your message handler code here
	CTimerData * pTimerData;

	//TTimerDataArray * pTimerArray;
	
	int timersize = timerdlg->m_timerarray.GetSize();

	for(int i = 0 ; i < timersize ; i++)
	{
		pTimerData = timerdlg->m_timerarray.GetAt(0);
		if (pTimerData)
		{
			timerdlg->m_timerarray.RemoveAt(0);
			delete pTimerData;
		}
	}

	//timerdlg->m_timerarray.RemoveAll();
	
	ASSERT(NULL == timerdlg->m_timerarray.GetSize());
	
	DestroyGuide();
	
	
}

void CProgGuideDlg::DestroyGuide()
{
	CTimerData * pProgGuideData;
	int guidesize = m_guidearray.GetSize();

	for(int k = 0 ; k < guidesize ; k++)
	{
		pProgGuideData = m_guidearray.GetAt(0);
		m_guidearray.RemoveAt(0);
		delete pProgGuideData;
	}

	ASSERT(NULL == m_guidearray.GetSize());

	

}

void CProgGuideDlg::OnOK() 
{
	// TODO: Add extra validation here
	SaveGuide();
	timerdlg->SaveRecords();

	// TODO:  I should probably save the Timer here as well
	
	CDialog::OnOK();
}

void CProgGuideDlg::OnRemoveTimer() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	//CTimerData * pTimerData;

	int result = MessageBox("Are you sure you want to delete this event?","Confirm Delete",MB_YESNO | MB_ICONEXCLAMATION);

	if (result == IDYES){
		pos = m_timerlist.GetFirstSelectedItemPosition();
		if (pos != NULL){
			//pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos - 1);
			//lstrcpy(itemtodelete,videopaths.GetAt((int)pos-1));
			timerdlg->m_timerarray.RemoveAt((int)pos -1);
			timerdlg->SaveRecords();

			FillTimerList();
		}
	}
	
}

void CProgGuideDlg::OnGetListings() 
{
	// TODO: Add your control notification handler code here
	//m_guidearray.RemoveAll();

	//CGetListingDlg2 getlistingdlg(&m_guidearray);
	CGetWeekList getweeklist(&m_guidearray);

	//getlistingdlg.DoModal();
	getweeklist.DoModal();
	SaveGuide();
	checkGuideValidity();
	LoadGuide();
	FillDateList();
	FillGuideList();
	
}

void CProgGuideDlg::OnAddTimer() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CTimerData * pTimerData;
	CTimerData * newTimerData;

	pos = m_progguidelist.GetFirstSelectedItemPosition();
	if (pos != NULL){
		pTimerData = (CTimerData*)m_progguidelist.GetItemData((int)pos - 1);
	
		//int result = MessageBox("Are you sure you want record the program?",
			//"Confirm Timer",MB_YESNO | MB_ICONEXCLAMATION);

		//if (result == IDYES){

			CFrequencyDlg freqdlg;

			freqdlg.DoModal();

			CTimeSpan diff = pTimerData->m_endtime - pTimerData->m_starttime;

			//check frequency
			CTime st(pTimerData->m_starttime);

			if((st.GetDayOfWeek() == 7) || (st.GetDayOfWeek() == 1))
			{
				if (freqdlg.selfrequency == TIMER_WEEKDAY){
					MessageBox("Sorry, it's the weekend. You can't set a week day timer");
					return;
				}
			}else{
				if (freqdlg.selfrequency == TIMER_WEEKEND){
					MessageBox("Sorry, it's a weekday, You can't set a weekend timer");
					return;
				}
			}

			//check disk space

			if(!timerdlg->CheckSpace(diff.GetTotalSeconds())){
				MessageBox("There will probably not be enough room in the library to store the requested show.\nClick okay to goto the library and make room");
				showLibraryDlg(NULL,LibraryPath);
				return;
			}

			newTimerData = new CTimerData;
			newTimerData->m_programme = pTimerData->m_programme;
			newTimerData->m_channel = pTimerData->m_channel;
			newTimerData->m_starttime = pTimerData->m_starttime;
			newTimerData->m_endtime = pTimerData->m_endtime;
			newTimerData->m_channelID = pTimerData->m_channelID;
			newTimerData->m_description = pTimerData->m_description;
			newTimerData->m_url = pTimerData->m_url;
			newTimerData->m_frequency = freqdlg.selfrequency;

			if(!timerdlg->addToTimer(newTimerData)){
				MessageBox("There is a conflict with existing timer entries","");
				delete newTimerData;
			}
					
			FillTimerList();
		//}
	}
	
}

void CProgGuideDlg::OnClickProgGuide(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	if(m_progguidelist.GetFirstSelectedItemPosition() != NULL){
		m_showdesc.EnableWindow(TRUE);
		m_addtotimer.EnableWindow(TRUE);
	}else{
		m_showdesc.EnableWindow(FALSE);
		m_addtotimer.EnableWindow(FALSE);
	}
	UpdateData(FALSE);


	
	*pResult = 0;
}

void CProgGuideDlg::OnClickTimerList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	if(m_timerlist.GetFirstSelectedItemPosition() != NULL){
		m_removetimer.EnableWindow(TRUE);
	}else{
		m_removetimer.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	
	*pResult = 0;
}

void CProgGuideDlg::OnShowDesc() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CTimerData * pTimerData;

	pos = m_progguidelist.GetFirstSelectedItemPosition();

	if(pos != NULL){
		pTimerData = (CTimerData*)m_progguidelist.GetItemData((int)pos-1);

		CString temp = pTimerData->m_description;

		if (temp.Find("EXTERNAL:") >= 0)
		{
			CWebDialog webdlg(temp.Right(temp.GetLength() - 9));
			webdlg.DoModal();
		}else{
			MessageBox(temp,"Programme Description");
		}
	}
}


void CProgGuideDlg::OnSelchangeDispchan() 
{
	// TODO: Add your control notification handler code here
	FillGuideList();
	
}

void CProgGuideDlg::OnSelchangeDispdate() 
{
	// TODO: Add your control notification handler code here
	FillGuideList();
	
}

BOOL CProgGuideDlg::getCurrentProg(LPSTR progname, int currchan)
{
	LoadGuide();
	CTimerData * pProgGuideData;

	CTime timenow = CTime::GetCurrentTime();
	CTime currentstarttime, currentendtime;

	for(int i = 0; i < m_guidearray.GetSize(); i++)
	{
		pProgGuideData = m_guidearray.GetAt(i);

		currentstarttime = CTime(pProgGuideData->m_starttime);
		currentendtime = CTime(pProgGuideData->m_endtime);

		if((currentstarttime < timenow) &&
			(currentendtime > timenow) &&
			(pProgGuideData->m_channelID == currchan))
		{
			lstrcpy(progname,pProgGuideData->m_programme.GetBuffer(256));
			DestroyGuide();
			return TRUE;

		}
	}
	DestroyGuide();
	//if(!::IsWindow(this->m_hWnd)) delete timerdlg;
	return FALSE;
}

CString CProgGuideDlg::getProg(int currchan, CTime progtime)
{
	LoadGuide();
	CTimerData * pProgGuideData;
	CString result;

	CTime currentstarttime, currentendtime;

	for(int i = 0; i < m_guidearray.GetSize(); i++)
	{
		pProgGuideData = m_guidearray.GetAt(i);

		currentstarttime = CTime(pProgGuideData->m_starttime);
		currentendtime = CTime(pProgGuideData->m_endtime);

		if((currentstarttime < progtime) &&
			(currentendtime > progtime) &&
			(pProgGuideData->m_channelID == currchan))
		{
			result = pProgGuideData->m_programme;
			DestroyGuide();
			return result;

		}
	}
	DestroyGuide();
	return "New Program";
}

BOOL CProgGuideDlg::checkGuideValidity()
{
	LoadGuide();
	CTime timenow = CTime::GetCurrentTime();
	int result = IDOK;

	if(m_guidearray.GetSize() == 0)
	{
		CGetWeekList getweeklist(&m_guidearray);
		result = getweeklist.DoModal();
	}
	
		//TTimerDataArray * temp = m_guidearray.GetAt(0);
	if(result == IDOK)
	{
		m_expirydate = m_guidearray.GetAt(m_guidearray.GetUpperBound())->m_starttime;
	
		if(m_expirydate < timenow)
		{
			CGetWeekList getweeklist(&m_guidearray);
			result = getweeklist.DoModal();
		}
	
		SaveGuide();
		DestroyGuide();
	}

	if(result == IDOK)
	{
		return TRUE;
	}else{
		return FALSE;
	}
}
