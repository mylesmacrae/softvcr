// RecompressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VidLibrary.h"
#include "RecompressDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecompressDlg dialog


CRecompressDlg::CRecompressDlg(CLibraryData * filetocompress, CWnd* pParent /*=NULL*/)
	: CDialog(CRecompressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecompressDlg)
	m_timerreturn = FALSE;
	m_stprogress = _T("");
	//}}AFX_DATA_INIT

	AfxEnableControlContainer();
	CoInitialize(NULL);

	m_filetocompress = filetocompress;
	timestart = CTime::GetCurrentTime();
	timenow = CTime::GetCurrentTime();

}


void CRecompressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecompressDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_encodeprogress);
	DDX_Control(pDX, IDC_REALPRODUCER2, m_producercontrol);
	DDX_Check(pDX, IDC_TIMERRETURN, m_timerreturn);
	DDX_Text(pDX, IDC_STPROGRESS, m_stprogress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecompressDlg, CDialog)
	//{{AFX_MSG_MAP(CRecompressDlg)
	ON_BN_CLICKED(IDC_TIMERRETURN, OnTimerreturn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecompressDlg message handlers

BEGIN_EVENTSINK_MAP(CRecompressDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRecompressDlg)
	ON_EVENT(CRecompressDlg, IDC_REALPRODUCER2, 5002 /* OnEncodingStopped */, OnEncodingStoppedRP, VTS_NONE)
	ON_EVENT(CRecompressDlg, IDC_REALPRODUCER2, 5005 /* OnEncodingProgressChanged */, OnOnEncodingProgressChanged, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRecompressDlg::OnEncodingStoppedRP() 
{
	// TODO: Add your control notification handler code here
	if(!usercancel)
	{
		CFileStatus status;
		m_filetocompress->m_path = m_producercontrol.GetOutputFilename();
		CFile::GetStatus(m_filetocompress->m_path,status);
		m_filetocompress->m_filesize = status.m_size;
		m_filetocompress->m_filetype = FILE_REALG2;

		DeleteFile(m_oldfilename);
		UpdateData(TRUE);
		quittotimer = m_timerreturn;

		OnOK();
	}
	
}


BOOL CRecompressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	usercancel = FALSE;
	quittotimer = FALSE;
	
	// TODO: Add extra initialization here
	if(m_filetocompress->m_filetype == FILE_REALG2) return FALSE;

	m_encodeprogress.SetRange(0,1000);
	
	//m_filetocompress = filetocompress;

	CString newfilename = m_oldfilename = m_filetocompress->m_path;
	newfilename = newfilename.Left(newfilename.GetLength() - 3);
	newfilename += "rm";
	
	
	
	m_producercontrol.LoadProducerSettings();
	m_producercontrol.SetInputType(0);
	m_producercontrol.SetInputDoAudio(TRUE);
	m_producercontrol.SetInputDoVideo(TRUE);
	m_producercontrol.SetInputFilename(m_filetocompress->m_path);

	m_producercontrol.SetDoOutputFile(TRUE);
	m_producercontrol.SetOutputFilename(newfilename);
	m_producercontrol.SetTitle(m_filetocompress->m_programme);
	m_producercontrol.SetAuthor("SoftVCR");
	m_producercontrol.SetCopyright("SoftVCR by Myles MacRae");

	m_producercontrol.SetSureStream(FALSE);
	m_producercontrol.SetTarget28KModem(FALSE);
	m_producercontrol.SetTarget56KModem(FALSE);
	m_producercontrol.SetTargetSingleISDN(FALSE);
	m_producercontrol.SetTargetDualISDN(FALSE);
	m_producercontrol.SetTargetDSLCableModem(FALSE);
	m_producercontrol.SetTargetLAN(FALSE);
	m_producercontrol.SetTarget256KDSLCableModem(FALSE);
	m_producercontrol.SetTarget384KDSLCableModem(FALSE);
	m_producercontrol.SetTarget512KDSLCableModem(TRUE);
	m_producercontrol.SetEmphasizeAudio(FALSE);
	m_producercontrol.SetTwoPassEncoding(FALSE);
	m_producercontrol.SetVbrEncoding(TRUE);
	
	

	m_producercontrol.StartEncoding();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecompressDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CRecompressDlg::OnOnEncodingProgressChanged(long duration, long timestamp, long PercentDone, long AudioPeakLevel) 
{
	// TODO: Add your control notification handler code here
	double percent;
	timenow = CTime::GetCurrentTime();
	CTimeSpan elapsed = timenow - timestart;

	percent = (((double)duration/1000)/(double)m_filetocompress->m_duration.GetTotalSeconds()) * 100;
	double timeleft = (100 - percent) * ((double)elapsed.GetTotalSeconds()/percent);

	CString temp;
	CTimeSpan tempspan((int)ceil(timeleft));
	temp.Empty();
	if(tempspan.GetHours()>0) temp += tempspan.Format("%Hhr");
	if(tempspan.GetMinutes()>0)  temp += tempspan.Format("%Mmin");
	temp += tempspan.Format("%Ssec");
	
	


	CString tempstr;
	tempstr.Format(_T("Encoding Progress - %.0f%% - Time Left - "),floor(percent));
	tempstr += temp;
	m_stprogress = tempstr;
	m_encodeprogress.SetPos((int)ceil(percent*10));
	UpdateData(FALSE);
	//UpdateData(TRUE);

	this->RedrawWindow(NULL,NULL,RDW_UPDATENOW);
	
}

void CRecompressDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	usercancel=TRUE;
	m_producercontrol.StopEncoding();
	CString temp = m_producercontrol.GetOutputFilename();
	DeleteFile(temp);
	
	CDialog::OnCancel();
}

void CRecompressDlg::OnTimerreturn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
}
