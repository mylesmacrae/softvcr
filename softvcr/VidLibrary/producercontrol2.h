#if !defined(AFX_PRODUCERCONTROL2_H__D0B1C247_3D77_11D4_A6DD_009027D11084__INCLUDED_)
#define AFX_PRODUCERCONTROL2_H__D0B1C247_3D77_11D4_A6DD_009027D11084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CRmFile;
class CTargetAudienceInfo;
class CEnumIDispatch;
class CCodecInfo;

/////////////////////////////////////////////////////////////////////////////
// CProducerControl2 wrapper class

class CProducerControl2 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CProducerControl2)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x56919d41, 0xbe39, 0x11d2, { 0xa4, 0x4, 0x0, 0x10, 0x4b, 0xdf, 0x47, 0x55 } };
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
	void SetBackColor(unsigned long newValue);
	unsigned long GetBackColor();
	void SetBackStyle(long nNewValue);
	long GetBackStyle();
	BOOL GetIsSourceOpen();
	BOOL GetIsEncoding();
	void OpenSource();
	void StartEncoding();
	void StopEncoding();
	long GetLastError();
	CString GetErrorString(long ErrorCode);
	void SendRealMediaEvent(long EventType, LPCTSTR EventText, long timestamp, long duration);
	void LoadProducerSettings();
	long GetOutputVideoWindowTarget();
	void SetOutputVideoWindowTarget(long nNewValue);
	void ShowVideoCardFormatDialog();
	void ShowVideoCardSourceDialog();
	void ShowVideoCardCompressionDialog();
	long GetNumTargetStreams();
	long GetNumAudioStreams();
	long GetNumVideoStreams();
	void GetTargetStream(long StreamIndex, long* TargetAudience, long* AudioStreamIndex, long* VideoStreamIndex, BOOL* Compatible50);
	void GetAudioStream(long StreamIndex, BSTR* CodecName, long* Bitrate, long* FrequencyResponse, long* Latency, long* Performance, BOOL* Compatible50);
	void GetVideoStream(long StreamIndex, BSTR* CodecName, long* Bitrate, float* FrameRate, long* Latency, long* Quality, long* Performance, BOOL* Compatible50);
	void UpdateStatistics();
	long GetInputType();
	void SetInputType(long nNewValue);
	CString GetInputFilename();
	void SetInputFilename(LPCTSTR lpszNewValue);
	long GetInputCaptureAudioDriver();
	void SetInputCaptureAudioDriver(long nNewValue);
	long GetInputCaptureVideoDriver();
	void SetInputCaptureVideoDriver(long nNewValue);
	BOOL GetInputDoAudio();
	void SetInputDoAudio(BOOL bNewValue);
	BOOL GetInputDoVideo();
	void SetInputDoVideo(BOOL bNewValue);
	BOOL GetInputDoEvents();
	void SetInputDoEvents(BOOL bNewValue);
	long GetNumAudioDrivers();
	long GetNumVideoDrivers();
	void GetAudioDriverName(long Index, BSTR* AudioDriver);
	void GetVideoDriverName(long Index, BSTR* VideoDriver);
	BOOL GetDoOutputFile();
	void SetDoOutputFile(BOOL bNewValue);
	BOOL GetDoOutputServer();
	void SetDoOutputServer(BOOL bNewValue);
	CString GetOutputFilename();
	void SetOutputFilename(LPCTSTR lpszNewValue);
	CString GetTempDirectory();
	void SetTempDirectory(LPCTSTR lpszNewValue);
	CString GetServerName();
	void SetServerName(LPCTSTR lpszNewValue);
	long GetServerPort();
	void SetServerPort(long nNewValue);
	CString GetServerFilename();
	void SetServerFilename(LPCTSTR lpszNewValue);
	CString GetServerUsername();
	void SetServerUsername(LPCTSTR lpszNewValue);
	CString GetServerPassword();
	void SetServerPassword(LPCTSTR lpszNewValue);
	long GetServerTransport();
	void SetServerTransport(long nNewValue);
	BOOL GetListBroadcast();
	void SetListBroadcast(BOOL bNewValue);
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	CString GetAuthor();
	void SetAuthor(LPCTSTR lpszNewValue);
	CString GetCopyright();
	void SetCopyright(LPCTSTR lpszNewValue);
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	CString GetKeywords();
	void SetKeywords(LPCTSTR lpszNewValue);
	long GetRating();
	void SetRating(long nNewValue);
	BOOL GetIndexable();
	void SetIndexable(BOOL bNewValue);
	BOOL GetSelectiveRecord();
	void SetSelectiveRecord(BOOL bNewValue);
	BOOL GetMobilePlay();
	void SetMobilePlay(BOOL bNewValue);
	void GetStringProperty(LPCTSTR PropertyName, BSTR* Value);
	void SetStringProperty(LPCTSTR PropertyName, LPCTSTR Value);
	void GetNumberProperty(LPCTSTR PropertyName, long* Value);
	void SetNumberProperty(LPCTSTR PropertyName, long Value);
	void RemoveProperty(LPCTSTR PropertyName);
	BOOL GetVideoCroppingEnabled();
	void SetVideoCroppingEnabled(BOOL bNewValue);
	BOOL GetVideoResizingEnabled();
	void SetVideoResizingEnabled(BOOL bNewValue);
	long GetVideoCropLeft();
	void SetVideoCropLeft(long nNewValue);
	long GetVideoCropTop();
	void SetVideoCropTop(long nNewValue);
	long GetVideoCropWidth();
	void SetVideoCropWidth(long nNewValue);
	long GetVideoCropHeight();
	void SetVideoCropHeight(long nNewValue);
	long GetVideoOutputWidth();
	void SetVideoOutputWidth(long nNewValue);
	long GetVideoOutputHeight();
	void SetVideoOutputHeight(long nNewValue);
	long GetVideoNoiseFiltering();
	void SetVideoNoiseFiltering(long nNewValue);
	void GetInputVideoSize(long* Width, long* Height);
	BOOL GetTarget28KModem();
	void SetTarget28KModem(BOOL bNewValue);
	BOOL GetTarget56KModem();
	void SetTarget56KModem(BOOL bNewValue);
	BOOL GetTargetSingleISDN();
	void SetTargetSingleISDN(BOOL bNewValue);
	BOOL GetTargetDualISDN();
	void SetTargetDualISDN(BOOL bNewValue);
	BOOL GetTargetDSLCableModem();
	void SetTargetDSLCableModem(BOOL bNewValue);
	BOOL GetTargetLAN();
	void SetTargetLAN(BOOL bNewValue);
	long GetAudioContent();
	void SetAudioContent(long nNewValue);
	long GetVideoQuality();
	void SetVideoQuality(long nNewValue);
	BOOL GetSureStream();
	void SetSureStream(BOOL bNewValue);
	long GetPlayerCompatibility();
	void SetPlayerCompatibility(long nNewValue);
	BOOL GetEmphasizeAudio();
	void SetEmphasizeAudio(BOOL bNewValue);
	BOOL GetDoAudioOnlyMultimedia();
	void SetDoAudioOnlyMultimedia(BOOL bNewValue);
	CRmFile GetOpenRmFile(LPCTSTR bstrFilePath);
	CTargetAudienceInfo GetTargetAudienceInfo(long TargetAudience);
	void RestoreTargetDefaults();
	CEnumIDispatch GetAudioCodecEnum();
	CEnumIDispatch GetVideoCodecEnum();
	CCodecInfo GetCodecInfo(LPDISPATCH codecId);
	BOOL GetTarget256KDSLCableModem();
	void SetTarget256KDSLCableModem(BOOL bNewValue);
	BOOL GetTarget384KDSLCableModem();
	void SetTarget384KDSLCableModem(BOOL bNewValue);
	BOOL GetTarget512KDSLCableModem();
	void SetTarget512KDSLCableModem(BOOL bNewValue);
	BOOL GetTwoPassEncoding();
	void SetTwoPassEncoding(BOOL bNewValue);
	BOOL GetVbrEncoding();
	void SetVbrEncoding(BOOL bNewValue);
	long GetVbrMaxStartupLatency();
	void SetVbrMaxStartupLatency(long nNewValue);
	long GetMaxTimeBetweenKeyframes();
	void SetMaxTimeBetweenKeyframes(long nNewValue);
	BOOL GetLossProtection();
	void SetLossProtection(BOOL bNewValue);
	BOOL GetHighQualityResize();
	void SetHighQualityResize(BOOL bNewValue);
	BOOL GetInverseTelecineFilter();
	void SetInverseTelecineFilter(BOOL bNewValue);
	BOOL GetDeInterlaceFilter();
	void SetDeInterlaceFilter(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCERCONTROL2_H__D0B1C247_3D77_11D4_A6DD_009027D11084__INCLUDED_)