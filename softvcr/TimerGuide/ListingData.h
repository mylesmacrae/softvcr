#pragma once
#include "afxtempl.h"

class CListingData : public CObject
{
public:
	DECLARE_SERIAL(CListingData)

	CStringArray m_listingID;
	CString m_parsername;
	CString m_path;
	
	virtual void Serialize(CArchive& ar);
};


typedef CTypedPtrArray<CObArray, CListingData*>TListingDataArray;