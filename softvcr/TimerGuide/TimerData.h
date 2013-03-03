#pragma once
#include "afxtempl.h"

class CTimerData : public CObject
{
public:
	DECLARE_SERIAL(CTimerData)

	DWORD m_starttime;
	DWORD m_endtime;
	CString m_programme;
	CString m_channel;
	int m_channelID;
	CString m_description;
	CString m_url;
	int m_frequency;
	

	virtual void Serialize(CArchive& ar);
};

typedef CTypedPtrArray<CObArray, CTimerData*>TTimerDataArray;

//typedef CTypedPtrArray<CObArray, TTimerDataArray*>TChannelGuide; //one for each channel