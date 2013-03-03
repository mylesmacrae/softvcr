// AddTimer.cpp : implementation file
//

#include "stdafx.h"
#include "TimerGuide.h"
#include "ProgGuideDlg.h"
#include "AddTimer.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddTimer dialog


CAddTimer::CAddTimer(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTimer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddTimer)
	m_duration = _T("");
	m_progname = _T("");
	m_endtimex = 0;
	m_datex = 0;
	m_starttimex = 0;
	//}}AFX_DATA_INIT

}

	
void CAddTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddTimer)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_FREQUENCY, m_frequencylist);
	DDX_Control(pDX, IDC_CHANNELLIST, m_channellist);
	DDX_Control(pDX, IDC_STARTTIMEPICKER, m_starttime);
	DDX_Control(pDX, IDC_ENDDATETIMEPICKER, m_endtime);
	DDX_Text(pDX, IDC_DURATION, m_duration);
	DDV_MaxChars(pDX, m_duration, 256);
	DDX_Text(pDX, IDC_PROGNAME, m_progname);
	DDV_MaxChars(pDX, m_progname, 256);
	DDX_DateTimeCtrl(pDX, IDC_ENDDATETIMEPICKER, m_endtimex);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_datex);
	DDX_DateTimeCtrl(pDX, IDC_STARTTIMEPICKER, m_starttimex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddTimer, CDialog)
	//{{AFX_MSG_MAP(CAddTimer)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_ENDDATETIMEPICKER, OnEndTimeChange)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_STARTTIMEPICKER, OnStartTimeChange)
	ON_LBN_SELCHANGE(IDC_CHANNELLIST, OnSelchangeChannellist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddTimer message handlers

void CAddTimer::OnOK() 
{
	// TODO: Add extra validation here

	//Ok...  the date should be either today or in the future, not the past.
	//The Start time should be before the end time with the extra validation that
	//23:59 - 0:01 is a valid time. A channel must be selected.
	CTimeSpan aday(1,0,0,0);
	CTime date, start, end;

	int syear, smon, sday, shour, smin;
	int eyear, emon, eday, ehour, emin;
	int selch;

	UpdateData(TRUE);

	//m_date.GetCurSel(date);
	syear = eyear = m_datex.GetYear();
	smon = emon = m_datex.GetMonth();
	sday = eday = m_datex.GetDay();

	m_endtime.GetTime(end);
	m_starttime.GetTime(start);

	if (m_endtimex < m_starttimex) eday += 1;
	shour = m_starttimex.GetHour();
	ehour = m_endtimex.GetHour();
	smin  = m_starttimex.GetMinute();
	emin  = m_endtimex.GetMinute();

	starttime = CTime(syear,smon,sday,shour,smin,0);
	endtime = CTime(eyear,emon,eday,ehour,emin,0);

	if((starttime < today) || (endtime<today))
	{
		MessageBox("This timer is in the past.\nPlease Try Again");
		return;
	}

	//If the Frequency is set to week day and the day is the weekend, break.
	//Conversly, if set for weekend and is not weekend, break.
	selfrequency = m_frequencylist.GetCurSel();
	if((starttime.GetDayOfWeek() == 7) || (starttime.GetDayOfWeek() == 1))
	{
		if (selfrequency == TIMER_WEEKDAY){
			MessageBox("Sorry, it's the weekend. You can't set a week day timer");
			return;
		}
	}else{
		if (selfrequency == TIMER_WEEKEND){
			MessageBox("Sorry, it's a weekday, You can't set a weekend timer");
			return;
		}
	}

	selch = m_channellist.GetCurSel();
	if(selch != LB_ERR){
		selchannelID = (int)(m_channellist.GetItemData(selch));
		m_channellist.GetText(selch,selchannel);
		CDialog::OnOK();
	}else{
		MessageBox("Please select a channel to record","Missing Data");
		return;
	}
}

BOOL CAddTimer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ifstream channelfile("channel.inf", ios::in | ios::nocreate);
	char buf[10];
	int counter = 0;
	
	today = CTime::GetCurrentTime();

	// TODO: Add extra initialization here

	//Set time thingies to the right format
	m_starttime.SetFormat("h:mm tt");
	m_starttimex = today;
	m_endtime.SetFormat("h:mm tt");
	m_endtimex = today;
	m_datex = today;

	m_progname = "New Program";

	//Fill Channel Combo with channel data.. setting data item to correct ID
	if(!channelfile.fail())
	{
		while(!channelfile.eof()){
			channelfile.getline(buf, 20, ' ');
			m_channellist.InsertString(counter,buf);
			m_channellist.SetItemData(counter,counter);
			channelfile.getline(buf, 20, '\n');
			counter++;
		}
		//Add composite onto the end of the combo.
		m_channellist.InsertString(counter,"Composite");
		m_channellist.SetItemData(counter,IDM_T_COMPOSITE);

		channelfile.close();

	}

	m_frequencylist.SetCurSel(TIMER_ONCE);

	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddTimer::OnEndTimeChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateDuration();
	
	*pResult = 0;
}

void CAddTimer::OnStartTimeChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateDuration();
	
	*pResult = 0;
}

void CAddTimer::UpdateDuration()
{
	CTimeSpan aday(1,0,0,0);
	CTimeSpan tempduration;
	CTime end, start;
	UpdateData(TRUE);

	//m_endtime.GetTime(end);
	//m_starttime.GetTime(start);
	end = m_endtimex;
	start = m_starttimex;

	if (end < start) end += aday;

	tempduration = end - start;

	//Only enable ok button if duration is greater than 0
	if((tempduration.GetTotalSeconds() > 0) && (m_channellist.GetCurSel() != LB_ERR)){
		m_ok.EnableWindow(TRUE);
	}else{
		m_ok.EnableWindow(FALSE);
	}

	CString temp;
	if(tempduration.GetHours()>0) temp += tempduration.Format("%Hhr");
	if(tempduration.GetMinutes()>0)  temp += tempduration.Format("%Mmin");
	//temp += duration.Format("%Ssec");
	m_duration = temp;
	
	
	//Get programme name from guide
	CProgGuideDlg pgdlg(NULL,NULL);
	m_progname = pgdlg.getProg(m_channellist.GetCurSel(),m_starttimex);

	UpdateData(FALSE);

}

void CAddTimer::OnSelchangeChannellist() 
{
	// TODO: Add your control notification handler code here
	UpdateDuration();
	
}
