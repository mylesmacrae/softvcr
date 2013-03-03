#if !defined(AFX_MEDIAPLAYER2_H__EC223689_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
#define AFX_MEDIAPLAYER2_H__EC223689_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CMediaPlayerDvd;

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayer2 wrapper class

class CMediaPlayer2 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CMediaPlayer2)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x22d6f312, 0xb0f6, 0x11d0, { 0x94, 0xab, 0x0, 0x80, 0xc7, 0x4c, 0x7e, 0x95 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	double GetCurrentPosition();
	void SetCurrentPosition(double newValue);
	double GetDuration();
	long GetImageSourceWidth();
	long GetImageSourceHeight();
	long GetMarkerCount();
	BOOL GetCanScan();
	BOOL GetCanSeek();
	BOOL GetCanSeekToMarkers();
	long GetCurrentMarker();
	void SetCurrentMarker(long nNewValue);
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	CString GetSourceLink();
	DATE GetCreationDate();
	CString GetErrorCorrection();
	long GetBandwidth();
	long GetSourceProtocol();
	long GetReceivedPackets();
	long GetRecoveredPackets();
	long GetLostPackets();
	long GetReceptionQuality();
	long GetBufferingCount();
	BOOL GetIsBroadcast();
	long GetBufferingProgress();
	CString GetChannelName();
	CString GetChannelDescription();
	CString GetChannelURL();
	CString GetContactAddress();
	CString GetContactPhone();
	CString GetContactEmail();
	double GetBufferingTime();
	void SetBufferingTime(double newValue);
	BOOL GetAutoStart();
	void SetAutoStart(BOOL bNewValue);
	BOOL GetAutoRewind();
	void SetAutoRewind(BOOL bNewValue);
	double GetRate();
	void SetRate(double newValue);
	BOOL GetSendKeyboardEvents();
	void SetSendKeyboardEvents(BOOL bNewValue);
	BOOL GetSendMouseClickEvents();
	void SetSendMouseClickEvents(BOOL bNewValue);
	BOOL GetSendMouseMoveEvents();
	void SetSendMouseMoveEvents(BOOL bNewValue);
	long GetPlayCount();
	void SetPlayCount(long nNewValue);
	BOOL GetClickToPlay();
	void SetClickToPlay(BOOL bNewValue);
	BOOL GetAllowScan();
	void SetAllowScan(BOOL bNewValue);
	BOOL GetEnableContextMenu();
	void SetEnableContextMenu(BOOL bNewValue);
	long GetCursorType();
	void SetCursorType(long nNewValue);
	long GetCodecCount();
	BOOL GetAllowChangeDisplaySize();
	void SetAllowChangeDisplaySize(BOOL bNewValue);
	BOOL GetIsDurationValid();
	long GetOpenState();
	BOOL GetSendOpenStateChangeEvents();
	void SetSendOpenStateChangeEvents(BOOL bNewValue);
	BOOL GetSendWarningEvents();
	void SetSendWarningEvents(BOOL bNewValue);
	BOOL GetSendErrorEvents();
	void SetSendErrorEvents(BOOL bNewValue);
	long GetPlayState();
	BOOL GetSendPlayStateChangeEvents();
	void SetSendPlayStateChangeEvents(BOOL bNewValue);
	long GetDisplaySize();
	void SetDisplaySize(long nNewValue);
	BOOL GetInvokeURLs();
	void SetInvokeURLs(BOOL bNewValue);
	CString GetBaseURL();
	void SetBaseURL(LPCTSTR lpszNewValue);
	CString GetDefaultFrame();
	void SetDefaultFrame(LPCTSTR lpszNewValue);
	BOOL GetHasError();
	CString GetErrorDescription();
	long GetErrorCode();
	BOOL GetAnimationAtStart();
	void SetAnimationAtStart(BOOL bNewValue);
	BOOL GetTransparentAtStart();
	void SetTransparentAtStart(BOOL bNewValue);
	long GetVolume();
	void SetVolume(long nNewValue);
	long GetBalance();
	void SetBalance(long nNewValue);
	long GetReadyState();
	double GetSelectionStart();
	void SetSelectionStart(double newValue);
	double GetSelectionEnd();
	void SetSelectionEnd(double newValue);
	BOOL GetShowDisplay();
	void SetShowDisplay(BOOL bNewValue);
	BOOL GetShowControls();
	void SetShowControls(BOOL bNewValue);
	BOOL GetShowPositionControls();
	void SetShowPositionControls(BOOL bNewValue);
	BOOL GetShowTracker();
	void SetShowTracker(BOOL bNewValue);
	BOOL GetEnablePositionControls();
	void SetEnablePositionControls(BOOL bNewValue);
	BOOL GetEnableTracker();
	void SetEnableTracker(BOOL bNewValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	unsigned long GetDisplayForeColor();
	void SetDisplayForeColor(unsigned long newValue);
	unsigned long GetDisplayBackColor();
	void SetDisplayBackColor(unsigned long newValue);
	long GetDisplayMode();
	void SetDisplayMode(long nNewValue);
	BOOL GetVideoBorder3D();
	void SetVideoBorder3D(BOOL bNewValue);
	long GetVideoBorderWidth();
	void SetVideoBorderWidth(long nNewValue);
	unsigned long GetVideoBorderColor();
	void SetVideoBorderColor(unsigned long newValue);
	BOOL GetShowGotoBar();
	void SetShowGotoBar(BOOL bNewValue);
	BOOL GetShowStatusBar();
	void SetShowStatusBar(BOOL bNewValue);
	BOOL GetShowCaptioning();
	void SetShowCaptioning(BOOL bNewValue);
	BOOL GetShowAudioControls();
	void SetShowAudioControls(BOOL bNewValue);
	CString GetCaptioningID();
	void SetCaptioningID(LPCTSTR lpszNewValue);
	BOOL GetMute();
	void SetMute(BOOL bNewValue);
	BOOL GetCanPreview();
	BOOL GetPreviewMode();
	void SetPreviewMode(BOOL bNewValue);
	BOOL GetHasMultipleItems();
	long GetLanguage();
	void SetLanguage(long nNewValue);
	long GetAudioStream();
	void SetAudioStream(long nNewValue);
	CString GetSAMIStyle();
	void SetSAMIStyle(LPCTSTR lpszNewValue);
	CString GetSAMILang();
	void SetSAMILang(LPCTSTR lpszNewValue);
	CString GetSAMIFileName();
	void SetSAMIFileName(LPCTSTR lpszNewValue);
	long GetStreamCount();
	CString GetClientId();
	long GetConnectionSpeed();
	BOOL GetAutoSize();
	void SetAutoSize(BOOL bNewValue);
	BOOL GetEnableFullScreenControls();
	void SetEnableFullScreenControls(BOOL bNewValue);
	LPDISPATCH GetActiveMovie();
	LPDISPATCH GetNSPlay();
	BOOL GetWindowlessVideo();
	void SetWindowlessVideo(BOOL bNewValue);
	void Play();
	void Stop();
	void Pause();
	double GetMarkerTime(long MarkerNum);
	CString GetMarkerName(long MarkerNum);
	void AboutBox();
	BOOL GetCodecInstalled(long CodecNum);
	CString GetCodecDescription(long CodecNum);
	CString GetCodecURL(long CodecNum);
	CString GetMoreInfoURL(long MoreInfoType);
	CString GetMediaInfoString(long MediaInfoType);
	void Cancel();
	void Open(LPCTSTR bstrFileName);
	BOOL IsSoundCardEnabled();
	void Next();
	void Previous();
	void StreamSelect(long StreamNum);
	void FastForward();
	void FastReverse();
	CString GetStreamName(long StreamNum);
	long GetStreamGroup(long StreamNum);
	BOOL GetStreamSelected(long StreamNum);
	CMediaPlayerDvd GetDvd();
	CString GetMediaParameter(long EntryNum, LPCTSTR bstrParameterName);
	CString GetMediaParameterName(long EntryNum, long Index);
	long GetEntryCount();
	long GetCurrentEntry();
	void SetCurrentEntry(long EntryNumber);
	void ShowDialog(long mpDialogIndex);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIAPLAYER2_H__EC223689_318A_11D4_8F05_C38B8F3F7A3C__INCLUDED_)
