// VideoLibraryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VidLibrary.h"
#include "VideoLibraryDlg.h"
#include "SearchLibDlg.h"
#include "RenameClip.h"
#include "RecompressDlg.h"
#include <fstream.h>
#include <afxcoll.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COL_PROG	  0
#define COL_CHANNEL	  1
#define COL_TIME	  2
#define COL_DURATION  4
#define COL_ARCHIVE	  3
#define COL_PATH	  5
#define COL_CHANNELID 6

#define DATA_FILE _T("LibraryData.dat") //for the serialization

/////////////////////////////////////////////////////////////////////////////
// CVideoLibraryDlg dialog


CVideoLibraryDlg::CVideoLibraryDlg(CWnd* pParent /*=NULL*/, LPCTSTR LibPath)
	: CDialog(CVideoLibraryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoLibraryDlg)
	m_libduration = _T("");
	m_timeremain = _T("");
	m_librarypath = _T("");
	//}}AFX_DATA_INIT
	LibraryPath = LibPath;

	
}


void CVideoLibraryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoLibraryDlg)
	DDX_Control(pDX, IDC_RECOMPRESS, m_recompress);
	DDX_Control(pDX, IDC_PLAYCLIP, m_playclip);
	DDX_Control(pDX, IDC_FILERENAME, m_filerename);
	DDX_Control(pDX, IDC_DELETE, m_delete);
	DDX_Control(pDX, IDC_LIBRARYLIST, m_librarylist);
	DDX_Text(pDX, IDC_LIBRARYDURATION, m_libduration);
	DDX_Text(pDX, IDC_TIMEREMAIN, m_timeremain);
	DDX_Text(pDX, IDC_LIBRARYPATH, m_librarypath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoLibraryDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoLibraryDlg)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_FILERENAME, OnFileRename)
	ON_BN_CLICKED(IDC_PLAYCLIP, OnPlayClip)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIBRARYLIST, OnClickLibrarylist)
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_RECOMPRESS, OnRecompress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoLibraryDlg message handlers

void CVideoLibraryDlg::SetLibraryPath(LPCTSTR libpath)
{
	LibraryPath = libpath;

}

BOOL CVideoLibraryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//LVCOLUMN column;
	// TODO: Add extra initialization here
	
	// Create Coloumns : Programme Name ; Channel ; Time/Date Recorded ; filename?
	static struct
	{
		LPTSTR szColText;
		UINT uiFormat;
	} columns[] = {
		_T("Programme Name"), LVCFMT_LEFT,
		_T("Channel"), LVCFMT_LEFT,
		_T("Time/Date Recorded"), LVCFMT_LEFT,
		_T("Archived"), LVCFMT_LEFT,
		_T("Duration"), LVCFMT_LEFT
	};

	for (int i = 0; i < sizeof columns / sizeof columns [0]; i++){
		m_librarylist.InsertColumn(i, columns[i].szColText, columns[i].uiFormat);
	}


	// Resize columns

	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_librarylist.GetDlgItem(0);
	ASSERT(pHeader);
	if(pHeader)
	{
		//turn off redraw until colums have been resized
		m_librarylist.SetRedraw(FALSE);

		//get number of columns
		int iNumberCols = pHeader->GetItemCount();
		//int iNumberCols = GetColumnCount();
		
		for (int iCurrentCol = 0; iCurrentCol < iNumberCols; iCurrentCol++)
		{
			m_librarylist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE);

			int nCurrWidth = m_librarylist.GetColumnWidth(iCurrentCol);

			m_librarylist.SetColumnWidth(iCurrentCol,LVSCW_AUTOSIZE_USEHEADER);

			int nColHdrWidth = m_librarylist.GetColumnWidth(iCurrentCol);

			m_librarylist.SetColumnWidth(iCurrentCol, max(nCurrWidth,nColHdrWidth));
		}

		m_librarylist.SetRedraw(TRUE);
		m_librarylist.SetExtendedStyle(LVS_EX_FULLROWSELECT);
		m_librarylist.Invalidate();
	}

	LoadLibrary();
	FillLibraryList();
	CalcStatistics();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CVideoLibraryDlg::PlayVideo(LPCTSTR filename)
{
	HINSTANCE playbackLibrary;
	pPlayFileDef pPlayFile;

	playbackLibrary = LoadLibraryEx("playback.dll",NULL,NULL);
	pPlayFile = (pPlayFileDef)GetProcAddress(playbackLibrary, "playVideo");
	pPlayFile(NULL, filename);
	FreeLibrary(playbackLibrary);
}

void CVideoLibraryDlg::addToLibrary(LPCTSTR progname, 
									LPCTSTR channel, 
									LONG timedate, 
									double duration, 
									LPCTSTR path, 
									int channelID)
{
	CLibraryData* pLibraryData;
	CFileStatus status;
	LoadLibrary();

	CFile::GetStatus(path,status);

	pLibraryData = new CLibraryData;

	pLibraryData->m_programme = progname;
	pLibraryData->m_channel = channel;
	pLibraryData->m_timedate = CTime((time_t)timedate);
	pLibraryData->m_duration = CTimeSpan((time_t)duration);
	pLibraryData->m_path = path;
	pLibraryData->m_channelID = channelID;
	pLibraryData->m_filesize = status.m_size;
	pLibraryData->m_filetype = FILE_AVI;

	m_LibraryData.SetAt(CString(path),pLibraryData);
	SaveLibrary();
}

void CVideoLibraryDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	
	//char buffer[256];
	//char itemtodelete[256];
	//BOOL failed;
	POSITION pos;
	CLibraryData * pLibraryData;

	int result = MessageBox("Are you sure you want to delete this video?","Confirm Delete",MB_YESNO | MB_ICONEXCLAMATION);

	if (result == IDYES){
		pos = m_librarylist.GetFirstSelectedItemPosition();
		if (pos != NULL){
			pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos - 1);
			//lstrcpy(itemtodelete,videopaths.GetAt((int)pos-1));
			
			if(DeleteFile(pLibraryData->m_path) == 0) MessageBox("File Already Deleted","Warning");

			m_LibraryData.RemoveKey(pLibraryData->m_path);
			delete pLibraryData;
					
			FillLibraryList();
			CalcStatistics();
		}
	}
	
}

void CVideoLibraryDlg::OnFileRename() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	char * temp;

	CLibraryData * pLibraryData;

	pos = m_librarylist.GetFirstSelectedItemPosition();
	//m_librarylist.GetItemText((int)pos - 1,COL_PROG,temp,256);
	pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos - 1);
	temp = pLibraryData->m_programme.GetBuffer(256);

	CRenameClip renameclip(temp);
	int nResult = renameclip.DoModal();
	if (IDOK == nResult)
	{
		renameclip.GetNewName(temp);
		m_librarylist.SetItemText((int)pos - 1,COL_PROG,temp);
		m_librarylist.Invalidate();
		pLibraryData->m_programme = temp;
	}

}

void CVideoLibraryDlg::OnPlayClip() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CLibraryData * pLibraryData;

	pos = m_librarylist.GetFirstSelectedItemPosition();

	pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos-1);

	if(pLibraryData->m_filetype == FILE_AVI){
		PlayVideo(pLibraryData->m_path.GetBuffer(256));
	}else{
		ShellExecute(NULL,"open",pLibraryData->m_path,NULL,NULL,SW_SHOWNORMAL);
	}
	
}

void CVideoLibraryDlg::Serialize(CArchive& ar) 
{
	m_LibraryData.Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CVideoLibraryDlg::CanSerialize()
{
	return(0 == _access(DATA_FILE,6));
}

void CVideoLibraryDlg::LoadLibrary()
{
	if(CanSerialize())
	{
		CFile file;
		CFileException fe;

		if(file.Open(DATA_FILE, CFile::typeBinary | CFile::modeRead, &fe))
		{
			CArchive ar(&file, CArchive::load);
			Serialize(ar);
		}
	}
}

void CVideoLibraryDlg::SaveLibrary()
{
	BOOL bCanSave = FALSE;

	UINT nFlags = CFile::typeBinary | CFile::modeWrite;

	// file doesn't exist, so create it
	if (_access(DATA_FILE, 0))
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
		if(file.Open(DATA_FILE, nFlags, &fe))
		{
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
		}
	}
}

void CVideoLibraryDlg::FillLibraryList()
{
	POSITION pos;
	CString strKey;
	CLibraryData * pLibraryData;

	int currentrow = 0;

	m_librarylist.DeleteAllItems();
	this->SetRedraw(FALSE);

	pos = m_LibraryData.GetStartPosition();
	while(NULL!=pos)
	{
		m_LibraryData.GetNextAssoc(pos, strKey, pLibraryData);
		if (pLibraryData)
		{
			//read programme name
			m_librarylist.InsertItem(currentrow, pLibraryData->m_programme, COL_PROG);
			m_librarylist.SetColumnWidth(COL_PROG,LVSCW_AUTOSIZE);
			int nCurrWidth = m_librarylist.GetColumnWidth(COL_PROG);
			m_librarylist.SetColumnWidth(COL_PROG,LVSCW_AUTOSIZE_USEHEADER);
			int nColHdrWidth = m_librarylist.GetColumnWidth(COL_PROG);
			m_librarylist.SetColumnWidth(COL_PROG, max(nCurrWidth,nColHdrWidth));
			
			//read channel
			m_librarylist.SetItemText(currentrow, COL_CHANNEL, pLibraryData->m_channel);
			m_librarylist.SetColumnWidth(COL_CHANNEL,LVSCW_AUTOSIZE);
			nCurrWidth = m_librarylist.GetColumnWidth(COL_CHANNEL);
			m_librarylist.SetColumnWidth(COL_CHANNEL,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_librarylist.GetColumnWidth(COL_CHANNEL);
			m_librarylist.SetColumnWidth(COL_CHANNEL, max(nCurrWidth,nColHdrWidth));

			//read time/date
			CString temp = pLibraryData->m_timedate.Format("%#I.%M%p %b %#d %Y");
			m_librarylist.SetItemText(currentrow, COL_TIME, temp);
			m_librarylist.SetColumnWidth(COL_TIME,LVSCW_AUTOSIZE);
			nCurrWidth = m_librarylist.GetColumnWidth(COL_TIME);
			m_librarylist.SetColumnWidth(COL_TIME,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_librarylist.GetColumnWidth(COL_TIME);
			m_librarylist.SetColumnWidth(COL_TIME, max(nCurrWidth,nColHdrWidth));

			//read duration
			CTimeSpan tempspan = pLibraryData->m_duration;
			temp.Empty();
			if(tempspan.GetHours()>0) temp += tempspan.Format("%Hhr");
			if(tempspan.GetMinutes()>0)  temp += tempspan.Format("%Mmin");
			temp += tempspan.Format("%Ssec");
			m_librarylist.SetItemText(currentrow, COL_DURATION, temp);
			m_librarylist.SetColumnWidth(COL_DURATION,LVSCW_AUTOSIZE);
			nCurrWidth = m_librarylist.GetColumnWidth(COL_DURATION);
			m_librarylist.SetColumnWidth(COL_DURATION,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_librarylist.GetColumnWidth(COL_DURATION);
			m_librarylist.SetColumnWidth(COL_DURATION, max(nCurrWidth,nColHdrWidth));

			//If video is realvideo, set archive to Yes
			temp.Empty();
			if(pLibraryData->m_filetype == FILE_REALG2) temp = "Yes";
			m_librarylist.SetItemText(currentrow, COL_ARCHIVE, temp);
			m_librarylist.SetColumnWidth(COL_ARCHIVE,LVSCW_AUTOSIZE);
			nCurrWidth = m_librarylist.GetColumnWidth(COL_ARCHIVE);
			m_librarylist.SetColumnWidth(COL_ARCHIVE,LVSCW_AUTOSIZE_USEHEADER);
			nColHdrWidth = m_librarylist.GetColumnWidth(COL_ARCHIVE);
			m_librarylist.SetColumnWidth(COL_ARCHIVE, max(nCurrWidth,nColHdrWidth));


			//Finally, add the pLibraryData structure as ItemData
			m_librarylist.SetItemData(currentrow,(DWORD)pLibraryData);
		
			
			currentrow++;
		}
	}

	m_librarylist.SortItems(CompareTime, (LPARAM) &m_librarylist);
	this->SetRedraw(TRUE);
	this->Invalidate();


}

static int CALLBACK CompareTime(LPARAM lparam1, LPARAM lparam2, LPARAM lparamsort)
{
	CListCtrl * pListCtrl = (CListCtrl*) lparamsort;

	CLibraryData * libdat1 = (CLibraryData*)lparam1;
	CLibraryData * libdat2 = (CLibraryData*)lparam2;

	if(libdat1->m_timedate <= libdat2->m_timedate){
		return -1;
	}else{
		return 1;
	}

}


/*
 * this will return true is there is enough space on the library drive
 * to stroe the requested amount of video.
 */
BOOL CVideoLibraryDlg::CheckSpace(int duration)  //in seconds
{

	ULARGE_INTEGER spaceremaining, spaceremaining2, spaceremaining3;
	ULONGLONG spacerequired;

	spacerequired = (ULONGLONG)duration * 400000;
		
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


/*
 *This calculates the library statistics:
 *    Total Duration
 *    Estimated Time Remaining
 */
void CVideoLibraryDlg::CalcStatistics()
{
	POSITION pos;
	CString key;
	CLibraryData * pLibraryData;
	ULONGLONG space =0;
	LONG sptemp;
	LONG durationacc = 0;
	ULARGE_INTEGER spaceremaining, spaceremaining2, spaceremaining3;
	LONGLONG result;
	LONG result2;
	char achBuffer[256];

	pos = m_LibraryData.GetStartPosition();

	while(NULL != pos)
	{
		m_LibraryData.GetNextAssoc(pos,key,pLibraryData);
		if(pLibraryData){
			durationacc += pLibraryData->m_duration.GetTotalSeconds();
			
			sptemp = pLibraryData->m_filesize;
			space += (ULONGLONG)sptemp;
		}
	}

	CTimeSpan tempspan((time_t)durationacc);
	CString temp;
	if(tempspan.GetHours()>0) temp += tempspan.Format("%Hhr");
	if(tempspan.GetMinutes()>0)  temp += tempspan.Format("%Mmin");
	temp += tempspan.Format("%Ssec");
	m_libduration = temp;

	lstrcpy(achBuffer,LibraryPath.GetBuffer(256));
	///Calculate Remaining time by remainingdiskspce / (totalfile/duration)
	GetDiskFreeSpaceEx(achBuffer,&spaceremaining,&spaceremaining2,&spaceremaining3);

	if(space>0 && durationacc>0){
		result = (LONGLONG)(spaceremaining.QuadPart / (space/(ULONGLONG)durationacc)); //resul is number of seconds
	}else{
		result = (LONGLONG)(spaceremaining.QuadPart / 300000); //best guess based on known rate of IV50 Quick COmpress
	}


	result2 = (LONG)result;

	CTimeSpan tempspan2((time_t)result2);
	temp.Empty();
	if(tempspan2.GetHours()>0) temp += tempspan2.Format("%Hhr");
	if(tempspan2.GetMinutes()>0)  temp += tempspan2.Format("%Mmin");
	temp += tempspan2.Format("%Ssec");
	m_timeremain = temp;

	m_librarypath = LibraryPath;
	
	UpdateData(FALSE);


}



void CVideoLibraryDlg::OnOK() 
{
	// TODO: Add extra validation here
	SaveLibrary();
	
	CDialog::OnOK();
}

void CVideoLibraryDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	POSITION pos;
	CString strKey;
	CLibraryData * pLibraryData;

	pos = m_LibraryData.GetStartPosition();
	while(NULL != pos)
	{
		m_LibraryData.GetNextAssoc(pos, strKey, pLibraryData);
		if (pLibraryData)
		{
			m_LibraryData.RemoveKey(strKey);
			delete pLibraryData;
		}
	}
	ASSERT(NULL == m_LibraryData.GetCount());
}

void CVideoLibraryDlg::OnClickLibrarylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	if(m_librarylist.GetFirstSelectedItemPosition() != NULL){
		m_delete.EnableWindow(TRUE);
		m_filerename.EnableWindow(TRUE);
		m_playclip.EnableWindow(TRUE);
		m_recompress.EnableWindow(TRUE);
	}else{
		m_delete.EnableWindow(FALSE);
		m_filerename.EnableWindow(FALSE);
		m_playclip.EnableWindow(FALSE);
		m_recompress.EnableWindow(FALSE);
	}
	UpdateData(FALSE);


	
	*pResult = 0;
}

void CVideoLibraryDlg::OnSearch() 
{
	// TODO: Add your control notification handler code here
	CSearchLibDlg searchdlg(&m_librarylist);

	int result = searchdlg.DoModal();

	if(result == IDOK){
		m_librarylist.Invalidate();
		m_librarylist.SetFocus();
	}
	
}

void CVideoLibraryDlg::OnRecompress() 
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CLibraryData * pLibraryData;


	pos = m_librarylist.GetFirstSelectedItemPosition();

	if(pos != NULL){
		pLibraryData = (CLibraryData*)m_librarylist.GetItemData((int)pos-1);

		if(pLibraryData->m_filetype == FILE_REALG2)
		{
			MessageBox("This clip is already archived","");
			return;
		}

		int result = MessageBox("You are about to recompress the selected file with RealVideo.\nThe file size will be reduced but at the expense of some quality.\nAlso, this is a lengthy operation that will postpone timers until it is complete.\nAre you sure you want to continue?","Query User",MB_YESNO);

		if(result == IDYES){
			


			//removes the old entry from the map.
			m_LibraryData.RemoveKey(pLibraryData->m_path);
			
			CRecompressDlg recompressdlg(pLibraryData);
			recompressdlg.DoModal();


			m_LibraryData.SetAt(pLibraryData->m_path,pLibraryData);

			if(recompressdlg.quittotimer)
			{
				OnOK();
			}
		}
	}

	FillLibraryList();
	CalcStatistics();
	
}
