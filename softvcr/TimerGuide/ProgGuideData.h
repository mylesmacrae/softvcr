#pragma once
#include "afxtempl.h"

class CProgGuideData : public CObject
{
public:
	DECLARE_SERIAL(CTimerData)

	DWORD m_starttime;
	DWORD m_endtime;
	CString m_programme;
	CString m_channel;
	int m_channelID;

	virtual void Serialize(CArchive& ar);
};

typedef CTypedPtrArray<CObArray, CProgGuideData*>TProgGuideDataArray;