#pragma once
#include "afxtempl.h"

#define FILE_AVI	1
#define FILE_REALG2 2

class CLibraryData : public CObject
{
public:
	DECLARE_SERIAL(CLibraryData)

	CLibraryData(){};

	CString m_path;
	CString m_programme;
	CString m_channel;
	CTime m_timedate;
	CTimeSpan m_duration; //THe duration in seconds
	int m_channelID; //The channelID
	LONG m_filesize;
	int m_filetype;

	virtual void Serialize(CArchive& ar);
};

class CLibraryDataCollection : public CMapStringToOb
{
public:
	CLibraryDataCollection(int nBlockSize = 10)
		: CMapStringToOb(nBlockSize){};
};

typedef CTypedPtrMap<CLibraryDataCollection, CString /* Path */, CLibraryData*>TLibraryDataCollection;