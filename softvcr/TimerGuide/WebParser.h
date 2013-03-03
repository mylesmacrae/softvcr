#pragma once
/*
 * CWebParser
 *
 * This class represents an abstract parser for extracting listing information from
 * TV Listings Websites.  It will take information about websites from external data files
 * written in a standard format.
 *
 * Information is then used by parser to connect to a website, pull the correct page based on given parameters and
 * extract programme names, times, dates and channels
 * 
 * Mapping between the channelID numbers used in softvcr and the ones used in websites should be done
 * here based on some seperate config file - possibly serialized.
 */

#include "TimerData.h"
#include <afxinet.h>

//Enumerated types used by parser;


enum ParserState {
	outside,
	parserinfo,
	channel,
	url,
	urlattribute,
	attribute,
	statetable,
	stateinitialize,
	state
};

class CParserData
{
public:
	CString state;
	CStringArray nextstate;
	CStringArray trigger;
	CStringArray action;
	CStringArray searchstring;
	CStringArray attribute;
};

typedef CTypedPtrMap<CMapStringToPtr,CString,CParserData*>CParserMachine;

class CWebParser
{
public:
	CWebParser(CString parsertouse);
	~CWebParser();

	int getListing(TTimerDataArray * result, 
		CTime date,
		CString channel,
		CString channelname,
		int channelID);
	
private:
	CString m_parserpath;  // Path of the parser definition file
	CString m_parsername;  // Name of the Parser
	CString m_parserurl;   //Base URL of the website
	CString m_dateformat, m_datedelim, m_timeformat, m_timedelim;  //used when reading in text
	CStringArray m_nameresolution;  //The sequence of tokens used to make up an URL
	CString m_initialstring; // the first string to find in a web page before parsing begins.
	CParserMachine m_parsermachine;
	CTime m_date, m_start, m_end;
	CString m_channelname;
	int m_channelID;
	CString m_currentperiod;
	CString m_channel;
	CTimerData * pProgData;
	CTimerData * pProgDataOld;
	CStringArray m_periodduration;  //period duration is the number of hours to add onto a date
	CString m_perioddurationtype;      // to get teh next set of pages.
	CString m_descriptiontype, m_descriptiondelim;
	
	BOOL LoadParser();
	BOOL ConstructURL(CString * result);
	//BOOL TryURL(TTimerDataArray * result, CString URL, CInternetFile * theFile);		
	BOOL ParseFile(TTimerDataArray * result, CInternetFile * theFile, BOOL getfirstonly);

	//first function called is getBBClisting, which simply constructs the correct URL for the given parameters
	//TryURL then connects to the website and establishes a stream which is given to
	//ParseBBCfile2 which parses and prints to m_out the  current page.
//	void getBBCListing(ProgrammeList * result, CTime date, CTime starttime, CTime endtime, int channel);

	//void parseBBCfile2(ProgrammeList * result, CInternetFile * thefile);

	//ParseBBCfile2 uses the following functions
	BOOL findToken(CString searchstring, CInternetFile * thefile);
	int getTag(CString searchstring, int index, CString * result);
	//void extractText(CString tag , CString line, CString * result);
	void extractText(CString tag , int index, CString line, CString * result, char terminate = '<');
	//HTMLtag converttag (CString tag);
	CTime convertTime (CString time);
	CTime StringToTime(CString format, CString input, CString delim);

//getBBClisting uses this function for getting the correct channel number.
	int mapBBCChannel(int in);
};




