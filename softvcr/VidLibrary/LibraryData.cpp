#include "stdafx.h"
#include "LibraryData.h"

IMPLEMENT_SERIAL(CLibraryData, CObject, 1)
void CLibraryData::Serialize(CArchive &ar)
{
	if (ar.IsLoading())
	{
		ar >> m_path;
		ar >> m_programme;
		ar >> m_channel;
		ar >> m_timedate;
		ar >> m_duration;
		ar >> m_channelID;
		ar >> m_filesize;
		ar >> m_filetype;
	}
	else
	{
		ar << m_path;
		ar << m_programme;
		ar << m_channel;
		ar << m_timedate;
		ar << m_duration;
		ar << m_channelID;
		ar << m_filesize;
		ar << m_filetype;
	}
}
