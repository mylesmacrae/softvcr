// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "codeccookie.h"


/////////////////////////////////////////////////////////////////////////////
// CCodecCookie properties

/////////////////////////////////////////////////////////////////////////////
// CCodecCookie operations

long CCodecCookie::GetCodecId()
{
	long result;
	InvokeHelper(0xc1d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CCodecCookie::GetFlavorId()
{
	long result;
	InvokeHelper(0xc1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}
