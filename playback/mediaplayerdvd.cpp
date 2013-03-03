// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "mediaplayerdvd.h"


/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDvd properties

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDvd operations

void CMediaPlayerDvd::ButtonSelectAndActivate(unsigned long uiButton)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5f6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 uiButton);
}

void CMediaPlayerDvd::UpperButtonSelect()
{
	InvokeHelper(0x5f1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::LowerButtonSelect()
{
	InvokeHelper(0x5f2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::LeftButtonSelect()
{
	InvokeHelper(0x5f3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::RightButtonSelect()
{
	InvokeHelper(0x5f4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::ButtonActivate()
{
	InvokeHelper(0x5f5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::ForwardScan(double dwSpeed)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5ed, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 dwSpeed);
}

void CMediaPlayerDvd::BackwardScan(double dwSpeed)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5ee, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 dwSpeed);
}

void CMediaPlayerDvd::PrevPGSearch()
{
	InvokeHelper(0x5ea, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::TopPGSearch()
{
	InvokeHelper(0x5eb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::NextPGSearch()
{
	InvokeHelper(0x5ec, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::TitlePlay(unsigned long uiTitle)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5e3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 uiTitle);
}

void CMediaPlayerDvd::ChapterPlay(unsigned long uiTitle, unsigned long uiChapter)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x5e4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 uiTitle, uiChapter);
}

void CMediaPlayerDvd::ChapterSearch(unsigned long Chapter)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5e9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Chapter);
}

void CMediaPlayerDvd::MenuCall(long MenuID)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5ef, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuID);
}

void CMediaPlayerDvd::ResumeFromMenu()
{
	InvokeHelper(0x5f0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::TimePlay(unsigned long uiTitle, LPCTSTR bstrTime)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x5e5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 uiTitle, bstrTime);
}

void CMediaPlayerDvd::TimeSearch(LPCTSTR bstrTime)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5e8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bstrTime);
}

void CMediaPlayerDvd::ChapterPlayAutoStop(unsigned long ulTitle, unsigned long ulChapter, unsigned long ulChaptersToPlay)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x605, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ulTitle, ulChapter, ulChaptersToPlay);
}

void CMediaPlayerDvd::StillOff()
{
	InvokeHelper(0x5f7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CMediaPlayerDvd::GoUp()
{
	InvokeHelper(0x5e7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CMediaPlayerDvd::GetTotalTitleTime()
{
	CString result;
	InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetNumberOfChapters(unsigned long ulTitle)
{
	unsigned long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ulTitle);
	return result;
}

CString CMediaPlayerDvd::GetAudioLanguage(unsigned long ulStream)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		ulStream);
	return result;
}

CString CMediaPlayerDvd::GetSubpictureLanguage(unsigned long ulStream)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		ulStream);
	return result;
}

VARIANT CMediaPlayerDvd::GetAllGPRMs()
{
	VARIANT result;
	InvokeHelper(0x618, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT CMediaPlayerDvd::GetAllSPRMs()
{
	VARIANT result;
	InvokeHelper(0x617, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL CMediaPlayerDvd::UOPValid(unsigned long ulUOP)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x62b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		ulUOP);
	return result;
}

unsigned long CMediaPlayerDvd::GetButtonsAvailable()
{
	unsigned long result;
	InvokeHelper(0x623, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentButton()
{
	unsigned long result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetAudioStreamsAvailable()
{
	unsigned long result;
	InvokeHelper(0x607, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentAudioStream()
{
	unsigned long result;
	InvokeHelper(0x608, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetCurrentAudioStream(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x608, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMediaPlayerDvd::GetCurrentSubpictureStream()
{
	unsigned long result;
	InvokeHelper(0x609, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetCurrentSubpictureStream(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x609, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMediaPlayerDvd::GetSubpictureStreamsAvailable()
{
	unsigned long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CMediaPlayerDvd::GetSubpictureOn()
{
	BOOL result;
	InvokeHelper(0x60b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetSubpictureOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

unsigned long CMediaPlayerDvd::GetAnglesAvailable()
{
	unsigned long result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentAngle()
{
	unsigned long result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetCurrentAngle(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CMediaPlayerDvd::GetCurrentTitle()
{
	unsigned long result;
	InvokeHelper(0x61f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentChapter()
{
	unsigned long result;
	InvokeHelper(0x620, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CMediaPlayerDvd::GetCurrentTime()
{
	CString result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetRoot(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CMediaPlayerDvd::GetRoot()
{
	CString result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetFramesPerSecond()
{
	unsigned long result;
	InvokeHelper(0x625, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentDomain()
{
	unsigned long result;
	InvokeHelper(0x626, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetTitlesAvailable()
{
	unsigned long result;
	InvokeHelper(0x627, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetVolumesAvailable()
{
	unsigned long result;
	InvokeHelper(0x628, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentVolume()
{
	unsigned long result;
	InvokeHelper(0x629, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetCurrentDiscSide()
{
	unsigned long result;
	InvokeHelper(0x62a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL CMediaPlayerDvd::GetCCActive()
{
	BOOL result;
	InvokeHelper(0x62d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetCCActive(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x62d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

unsigned long CMediaPlayerDvd::GetCurrentCCService()
{
	unsigned long result;
	InvokeHelper(0x62c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetCurrentCCService(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x62c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString CMediaPlayerDvd::GetUniqueID()
{
	CString result;
	InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

unsigned long CMediaPlayerDvd::GetColorKey()
{
	unsigned long result;
	InvokeHelper(0x631, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CMediaPlayerDvd::SetColorKey(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x631, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}