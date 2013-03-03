#include "stdafx.h"
#include "ListingData.h"

IMPLEMENT_SERIAL(CListingData, CObject, 1)
void CListingData::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);

	m_listingID.Serialize(ar);
	
	if (ar.IsLoading())
	{
		//ar >> m_listingconfigfile;
		ar >> m_parsername;
		ar >> m_path;
		
	}
	else
	{
		//ar << m_listingconfigfile;
		ar << m_parsername;
		ar << m_path;
	}
}
