// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "targetaudienceinfo.h"

// Dispatch interfaces referenced by this interface
#include "codeccookie.h"


/////////////////////////////////////////////////////////////////////////////
// CTargetAudienceInfo properties

/////////////////////////////////////////////////////////////////////////////
// CTargetAudienceInfo operations

long CTargetAudienceInfo::GetTargetAudienceId()
{
	long result;
	InvokeHelper(0xd7b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString CTargetAudienceInfo::GetTargetAudienceName()
{
	CString result;
	InvokeHelper(0xd7c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

float CTargetAudienceInfo::GetTargetBitrate()
{
	float result;
	InvokeHelper(0xd7d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CTargetAudienceInfo::SetTargetBitrate(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xd7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

float CTargetAudienceInfo::GetMaxFrameRate()
{
	float result;
	InvokeHelper(0xd7e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
	return result;
}

void CTargetAudienceInfo::SetMaxFrameRate(float newValue)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xd7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CCodecCookie CTargetAudienceInfo::GetVideoCodec()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xd7f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CCodecCookie(pDispatch);
}

void CTargetAudienceInfo::SetVideoCodec(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0xd7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CCodecCookie CTargetAudienceInfo::GetAudioCodec(long TargetAudienceType, long AudioContent)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xd80, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, parms,
		TargetAudienceType, AudioContent);
	return CCodecCookie(pDispatch);
}

void CTargetAudienceInfo::SetAudioCodec(long TargetAudienceType, long AudioContent, LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_DISPATCH;
	InvokeHelper(0xd80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 TargetAudienceType, AudioContent, newValue);
}