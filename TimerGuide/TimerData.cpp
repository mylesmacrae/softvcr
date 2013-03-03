#include "stdafx.h"
#include "TimerData.h"

IMPLEMENT_SERIAL(CTimerData, CObject, 1)
void CTimerData::Serialize(CArchive &ar)
{
	if(ar.IsLoading())
	{
		ar >> m_starttime;
		ar >> m_endtime;
		ar >> m_programme;
		ar >> m_channel;
		ar >> m_channelID;
		ar >> m_description;
		ar >> m_url;
		ar >> m_frequency;
	}else{
		ar << m_starttime;
		ar << m_endtime;
		ar << m_programme;
		ar << m_channel;
		ar << m_channelID;
		ar << m_description;
		ar << m_url;
		ar << m_frequency;
	}
}