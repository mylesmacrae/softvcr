// TimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "TimerDlg.h"
#include "AddTimer.h"
#include "../libraryexport.h"

#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_STARTTIME	2
#define COL_ENDTIME		3
#define COL_PROGNAME	0
#define COL_CHANNEL		1
#define COL_DURATION	4
#define COL_FREQUENCY	5

#define DATA_FILE _T("TimerData.dat")

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog



CTimerDlg::CTimerDlg(LPCTSTR librarypath, CWnd* pParent /*=NULL*/)
	: CDialog(CTimerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if (librarypath!=NULL)
	LibraryPath = librarypath;

	LoadRecords();
}


void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimerDlg)
	DDX_Control(pDX, IDC_TIMERLIST, m_timerlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTimerDlg, CDialog)
	//{{AFX_MSG_MAP(CTimerDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADDTIMER, OnAddtimer)
	ON_BN_CLICKED(IDC_DELETETIMER, OnDeletetimer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg message handlers

BOOL CTimerDlg::CanSerialize()
{
	return (0 == _access(DATA_FILE, 6));
}

void CTimerDlg::LoadRecords()
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

void CTimerDlg::SaveRecords()
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

void CTimerDlg::FillTimerList()
{
	CString strKey;
	CTimerData * pTimerData;

	int currentrow = 0;

	m_timerlist.DeleteAllItems();

	m_timerlist.SetRedraw(FALSE);

	for(int i = 0; i<m_timerarray.GetSize(); i++)
	{
		pTimerData = m_timerarray.GetAt(i);
		
		if (pTimerData)
		{
			//Set Progname
			m_timerlist.InsertItem(i, pTimerData->m_programme, COL_PROGNAME);
			m_timerlist.SetColumnWidth(COL_PROGNAME,LVSCW_AUTOSIZE);
			int nCurrWidth = m_timerlist.GetColumnWidth(COL_PROGNAME);
			m_timerlist.SetColumnWidth(COL_PROGNAME,LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_timerlist.GetColumnWidth(COL_PROGNAME);
			m_timerlist.SetColumnWidth(COL_PROGNAME, max(nCurrWidth,nColHdrWidth));

			//Set Starttime (saved as DWORD)
			CTime * st;
			st = new CTime((time_t)(pTimerData->m_starttime));
			CString sttemp = st->Format("%#I.%M%p %a %b %#d");
			m_timerlist.SetItemText(i, COL_STARTTIME, sttemp);
			m_timerlist.SetColumnWidth(COL_STARTTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_STARTTIME);
			m_timerlist.SetColumnWidth(COL_STARTTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_STARTTIME);
			m_timerlist.SetColumnWidth(COL_STARTTIME, max(nCurrWidth,nColHdrWidth));
			delete st;
			
			//Set Endtime
			st = new CTime((time_t)(pTimerData->m_endtime));
			if(st->GetSecond() != 0) *st += CTimeSpan(0,0,1,0);
			sttemp = st->Format("%#I.%M%p %a");
			m_timerlist.SetItemText(i, COL_ENDTIME, sttemp);
			m_timerlist.SetColumnWidth(COL_ENDTIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_ENDTIME);
			m_timerlist.SetColumnWidth(COL_ENDTIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_ENDTIME);
			m_timerlist.SetColumnWidth(COL_ENDTIME, max(nCurrWidth,nColHdrWidth));
			delete st;

			//set duration
			CTimeSpan sd = pTimerData->m_endtime - pTimerData->m_starttime;
			sttemp.Empty();
			//if(sd.GetHours()>0) sttemp += sd.Format("%Hhr");
			//if(sd.GetMinutes()>0)
			//{
			int t = sd.GetTotalMinutes() + 1;
			sttemp.Format("%0.2dmin", t);
				
			//}
			//if(sd.GetSeconds()>0) sttemp += sd.Format("%Ssec");
			m_timerlist.SetItemText(i, COL_DURATION, sttemp);
			m_timerlist.SetColumnWidth(COL_DURATION,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_DURATION);
			m_timerlist.SetColumnWidth(COL_DURATION,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_DURATION);
			m_timerlist.SetColumnWidth(COL_DURATION, max(nCurrWidth,nColHdrWidth));
		

			//read channel name
			m_timerlist.SetItemText(i, COL_CHANNEL, pTimerData->m_channel);
			m_timerlist.SetColumnWidth(COL_CHANNEL,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_CHANNEL);
			m_timerlist.SetColumnWidth(COL_CHANNEL,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_CHANNEL);
			m_timerlist.SetColumnWidth(COL_CHANNEL, max(nCurrWidth,nColHdrWidth));

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
			m_timerlist.SetItemText(i, COL_FREQUENCY, sttemp);
			m_timerlist.SetColumnWidth(COL_FREQUENCY,LVSCW_AUTOSIZE);
			nCurrWidth = m_timerlist.GetColumnWidth(COL_FREQUENCY);
			m_timerlist.SetColumnWidth(COL_FREQUENCY,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_timerlist.GetColumnWidth(COL_FREQUENCY);
			m_timerlist.SetColumnWidth(COL_FREQUENCY, max(nCurrWidth,nColHdrWidth));


			//Finally, add the pLibraryData structure as ItemData
			m_timerlist.SetItemData(i,(DWORD)pTimerData);
		
		}
	}

	m_timerlist.SetRedraw(TRUE);
	m_timerlist.Invalidate();
}

BOOL CTimerDlg::addToTimer(LPCTSTR progname, 
						   DWORD starttime, 
						   DWORD endtime,
						   LPCTSTR channel,
						   int channelID,
						   int frequency)
{
	CTimerData * pTimerData;
	BOOL result;

	pTimerData = new CTimerData;

	pTimerData->m_programme = progname;
	pTimerData->m_starttime = starttime;
	pTimerData->m_endtime = endtime;
	pTimerData->m_channel = channel;
	pTimerData->m_channelID = channelID;
	pTimerData->m_frequency = frequency;

	result = addToTimer(pTimerData);

	if(!result) delete pTimerData;

	return result;
	
}

BOOL CTimerDlg::addToTimer(CTimerData * newTimerData)
{
	
	CTimerData * currentdata;
	BOOL InsertSuccess = FALSE;

	LoadRecords();

	//I need to check if there is space on the library drive to store the requested program.
	//If not, we should display the library and ask user to delete files to make room.
	
	int arraysize = m_timerarray.GetSize();

	if(arraysize == 0){
		//insert straight in
		m_timerarray.Add(newTimerData);
		InsertSuccess = TRUE;

	}else{
		for (int i = m_timerarray.GetUpperBound(); i >= 0; i--)
		{
			currentdata = m_timerarray.GetAt(i);

			if(newTimerData->m_endtime<=currentdata->m_starttime)
			{
				if (i == 0)
				{
					m_timerarray.InsertAt(0,newTimerData);
					InsertSuccess = TRUE;
					break;
				}
				else
				{
					currentdata = m_timerarray.GetAt(i-1);
					if (currentdata->m_endtime <= newTimerData->m_starttime)
					{
						m_timerarray.InsertAt(i, newTimerData);
						InsertSuccess = TRUE;
						break;
					}
					else
					{
						InsertSuccess = FALSE;
						//break;
					}
				}
			}
			else if (newTimerData->m_starttime >= currentdata->m_endtime)
			{
				if(i == m_timerarray.GetUpperBound())
				{
					m_timerarray.Add(newTimerData);
					InsertSuccess = TRUE;
					break;
				}
				else
				{
					currentdata = m_timerarray.GetAt(i+1);
					if (currentdata->m_starttime > newTimerData->m_endtime)
					{
						m_timerarray.InsertAt(i+1,newTimerData);
						InsertSuccess = TRUE;
						break;
					}
					else
					{
						InsertSuccess = FALSE;
						//break;
					}
				}
			}
		}
	}


	SaveRecords();

	return InsertSuccess;

}

BOOL CTimerDlg::getNextTimer(DWORD timenow, LPSTR progname, DWORD * starttime, int * duration, int * channelID)
{
	
	CTimerData * pTimerData;
	char buf[256];
	double difference;

	LoadRecords();

	for (int i = 0; i < m_timerarray.GetSize(); i++)
	{
		pTimerData = m_timerarray.GetAt(i);

		if ((pTimerData->m_starttime <= timenow) && (pTimerData->m_endtime > timenow))
		{
		
			//It should start now.  Return parameters and delete off array.
			lstrcpy(buf,pTimerData->m_programme.GetBuffer(256));
			lstrcpy(progname,buf);
			*starttime = pTimerData->m_starttime;
			difference = difftime(timenow, pTimerData->m_starttime);
			*duration = (int)(pTimerData->m_endtime - pTimerData->m_starttime - difference);
			*channelID = pTimerData->m_channelID;

			//I should check the frequency of the timer, and update the starttime/endtime

			switch(pTimerData->m_frequency)
			{
			case TIMER_ONCE:
				//delete the timer
				m_timerarray.RemoveAt(i);
				SaveRecords();
				delete pTimerData;
				break;
			case TIMER_DAILY:
				{
					//set the timer for next day
					CTimeSpan sp(1,0,0,0);
					BOOL success = FALSE;
					
					m_timerarray.RemoveAt(i);
					SaveRecords();

					while(!success){
						pTimerData->m_starttime += sp.GetTotalSeconds();
						pTimerData->m_endtime += sp.GetTotalSeconds();
						success = addToTimer(pTimerData);
					}
					break;
				}
			case TIMER_WEEKLY:
				{
					//set the timer for 7 days time
					CTimeSpan sp(7,0,0,0);
					BOOL success = FALSE;

					m_timerarray.RemoveAt(i);
					SaveRecords();

					while(!success){
						pTimerData->m_starttime += sp.GetTotalSeconds();
						pTimerData->m_endtime += sp.GetTotalSeconds();
						success = addToTimer(pTimerData);
					}
					break;
				}
			case TIMER_WEEKDAY:
				{
					//set timer for next day, except Friday - set for 3 days time
					CTime sttime(pTimerData->m_starttime);
					BOOL success = FALSE;

					m_timerarray.RemoveAt(i);
					SaveRecords();

					while(!success){
						if(sttime.GetDayOfWeek() == 6)
						{
							CTimeSpan sp(3,0,0,0);
							pTimerData->m_starttime += sp.GetTotalSeconds();
							pTimerData->m_endtime += sp.GetTotalSeconds();
							sttime += sp;
						}else{
							CTimeSpan sp(1,0,0,0);
							pTimerData->m_starttime += sp.GetTotalSeconds();
							pTimerData->m_endtime += sp.GetTotalSeconds();
							sttime += sp;
						}
						success = addToTimer(pTimerData);
					}
					break;
				}
			case TIMER_WEEKEND:
				{
					//set for next day, except Sunday - set for 6 days time
					CTime sttime(pTimerData->m_starttime);
					BOOL success = FALSE;

					m_timerarray.RemoveAt(i);
					SaveRecords();

					while(!success)
					{
						if(sttime.GetDayOfWeek() == 1)
						{
							CTimeSpan sp(6,0,0,0);
							pTimerData->m_starttime += sp.GetTotalSeconds();
							pTimerData->m_endtime += sp.GetTotalSeconds();
							sttime += sp;
						}else{
							CTimeSpan sp(1,0,0,0);
							pTimerData->m_starttime += sp.GetTotalSeconds();
							pTimerData->m_endtime += sp.GetTotalSeconds();
							sttime += sp;
						}
						success = addToTimer(pTimerData);
					}
					break;
				}
			}

			return TRUE;
		}else if(pTimerData->m_endtime < timenow){
			//it should have finished already...  delete it...
			m_timerarray.RemoveAt(i);
			delete pTimerData;

			SaveRecords();

		}
	}

		

	SaveRecords();
	return FALSE;

}


void CTimerDlg::Serialize(CArchive& ar) 
{
	m_timerarray.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CTimerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// Create Coloumns : Programme Name ; Channel ; Time/Date Recorded ; filename?
	
	static struct
	{
		LPTSTR szColText;
		UINT uiFormat;
	} columns[] = {
		_T("Programme Name"), LVCFMT_LEFT,
		_T("Channel"), LVCFMT_LEFT,
		_T("Start Time"), LVCFMT_LEFT,
		_T("End Time"), LVCFMT_LEFT,
		_T("Duration"), LVCFMT_LEFT,
		_T("Frequency"), LVCFMT_LEFT
	};

	for (int i = 0; i < sizeof columns / sizeof columns [0]; i++){
		m_timerlist.InsertColumn(i, columns[i].szColText, columns[i].uiFormat);
	}


	// Resize columns

	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_timerlist.GetDlgItem(0);
	ASSERT(pHeader);
	if(pHeader)
	{
		//turn off redraw until colums have been resized
		m_timerlist.SetRedraw(FALSE);

		//get number of columns
		int iNumberCols = pHeader->GetItemCount();
		//int iNumberCols = GetColumnCount();
		
		for (int iCurrentCol = 0; iCurrentCol < iNumberCols; iCurrentCol++)
		{
			m_timerlist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE);

			int nCurrWidth = m_timerlist.GetColumnWidth(iCurrentCol);

			m_timerlist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE_USEHEADER);

			int nColHdrWidth = m_timerlist.GetColumnWidth(iCurrentCol);

			m_timerlist.SetColumnWidth(iCurrentCol, max(nCurrWidth,nColHdrWidth));
		}

		m_timerlist.SetRedraw(TRUE);
		m_timerlist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		m_timerlist.Invalidate();
	}



	FillTimerList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CTimerData * pLibraryData;

	for(int i = 0 ; i < m_timerarray.GetSize() ; i++)
	{
		pLibraryData = m_timerarray.GetAt(i);
		if (pLibraryData)
		{
			delete pLibraryData;
		}
	}

	m_timerarray.RemoveAll();

	ASSERT(NULL == m_timerarray.GetSize());
	
}

void CTimerDlg::OnOK() 
{
	// TODO: Add extra validation here
	SaveRecords();
	
	CDialog::OnOK();
}

void CTimerDlg::OnAddtimer() 
{
	// TODO: Add your control notification handler code here
	CAddTimer addtimerdlg;
	char buf[256], buf2[256];
	BOOL timeradded = FALSE;

	int result = addtimerdlg.DoModal();
		
	if(result == IDOK){
		//get timer details from dialog object and create new timer event
		//I am assuming the dialog has returned a sensible set of data only.
		//we need: progname, starttime, endtime, channel, channelID
		lstrcpy(buf,addtimerdlg.m_progname.GetBuffer(256));
		//int chan = addtimerdlg.m_channellist.GetCurSel();

		lstrcpy(buf2,addtimerdlg.selchannel.GetBuffer(256));

		CTimeSpan diff = addtimerdlg.endtime - addtimerdlg.starttime;

		if(!CheckSpace(diff.GetTotalSeconds()))
		{
			MessageBox("There will probably not be enough room in the library to store the requested show. Click okay to goto the library and make room");
			showLibraryDlg(NULL,LibraryPath);
			return;
		}

		
		
		if(!addToTimer(buf, addtimerdlg.starttime.GetTime(), addtimerdlg.endtime.GetTime(), buf2, (int)(addtimerdlg.selchannelID), addtimerdlg.selfrequency))
		{
			MessageBox("There is a conflict between your request and the existing timer list. Please try again",
				"There's a problem",MB_ICONWARNING | MB_OK);
	
		}else{
			FillTimerList();
			UpdateData(FALSE);
			timeradded = TRUE;
		}

	}	
}

void CTimerDlg::OnDeletetimer() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CTimerData * pTimerData;

	int result = MessageBox("Are you sure you want to delete this event?","Confirm Delete",MB_YESNO | MB_ICONEXCLAMATION);

	if (result == IDYES){
		pos = m_timerlist.GetFirstSelectedItemPosition();
		if (pos != NULL){
			//pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos - 1);
			//lstrcpy(itemtodelete,videopaths.GetAt((int)pos-1));
			pTimerData = m_timerarray.GetAt((int)pos-1);
			m_timerarray.RemoveAt((int)pos -1);
			delete pTimerData;

			FillTimerList();
		}
	}
	//ASSERT(m_timerarray.GetSize() == 0);
	SaveRecords();
	
}

BOOL CTimerDlg::CheckSpace(int duration)  //in seconds
{

	ULARGE_INTEGER spaceremaining, spaceremaining2, spaceremaining3;
	ULONGLONG spacerequired;
	CTimerData * pTimerData;

	double totalduration = (double)duration;

	//I need to get the total committed durations from the timerlist
	for(int i = 0; i < m_timerarray.GetSize(); i++)
	{
		pTimerData = m_timerarray.GetAt(i);
		totalduration += difftime((time_t)pTimerData->m_endtime, (time_t)pTimerData->m_starttime);
	}


	spacerequired = (ULONGLONG)totalduration * 400000;
		
	///Calculate Remaining time by remainingdiskspce / (totalfile/duration)
	GetDiskFreeSpaceEx(LibraryPath,&spaceremaining,&spaceremaining2,&spaceremaining3);

	
	if(spacerequired < spaceremaining.QuadPart){
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

