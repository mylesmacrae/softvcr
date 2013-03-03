/*
 * CWebParser Implementation - See WebParser.h for description
 */

#include "stdafx.h"
#include "afxinet.h"
#include "parsertypes.h"
#include "WebParser.h"
#include "Token.h"


//Constructor
CWebParser::CWebParser(CString parsertouse)
{
	m_parserpath = parsertouse;
	LoadParser();

}

CWebParser::~CWebParser()
{
	POSITION pos;
	CString strKey;
	CParserData * pParserData;

	pos = m_parsermachine.GetStartPosition();
	while(NULL != pos)
	{
		m_parsermachine.GetNextAssoc(pos, strKey, pParserData);
		if (pParserData)
		{
			
			//pParserData->action.RemoveAll();
			//pParserData->attribute.RemoveAll();
			//pParserData->nextstate.RemoveAll();
			//pParserData->trigger.RemoveAll();
			//delete pParserData;				
			m_parsermachine.RemoveKey(strKey);
		
		}
	}
	ASSERT(NULL == m_parsermachine.GetCount());
}

//This function has the task of loading the parser specified in the constructor, into memory.
BOOL CWebParser::LoadParser()
{
	CStdioFile parserfile;
	CString currentline;
	ParserState thestate = outside;

	if(!parserfile.Open(m_parserpath, CFile::modeRead | CFile::typeText))
	{
		return FALSE;
	}

	//Okay.. the first line should be <LPF V1.0>
	//check to see that this file is correct

	parserfile.ReadString(currentline);
	if (currentline != "<LPF V1.0>"){
		parserfile.Close();
		return FALSE;
	}

	while (parserfile.ReadString(currentline))
	{
		currentline.TrimLeft();  //The file is allowed to be structured using tabs
		currentline.TrimRight(); //clean any crap off the end of lines as well :-)

		switch(thestate)
		{
		case outside:
			{
				if(currentline == "<PARSERINFO>"){
					thestate = parserinfo;
				}else if(currentline == "<CHANNEL>"){
					thestate = channel;
				}else if(currentline == "<URL>"){
					thestate = url;
				}else if(currentline == "<URLATTRIBUTE>"){
					thestate = urlattribute;
				}else if(currentline == "<ATTRIBUTE>"){
					thestate = attribute;
				}else if(currentline == "<STATETABLE>"){
					thestate = statetable;
				}else{
					//err...  not sure yet... 
				}
				break;
			}
		case parserinfo:
			{
				CString command,parameter;
				command= currentline.SpanExcluding(":");
				parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);

				if (command == "PARSERNAME"){
					m_parsername = parameter;
				}else if(command == "BASE URL"){
					m_parserurl = parameter;
				}else if(command == "</PARSERINFO>"){
					thestate = outside;
				}else{
					//again, I'm not exactly sure what else could go here.
				}
				break;
			}
		case channel:
			//This won't actually be needed by the parser, only during parser setup
			//so skip over the contents
			{
				if (currentline == "</CHANNEL>"){
					thestate = outside;
				}
				break;
			}
		case url:
			{
				if(currentline != "</URL>"){
					m_nameresolution.Add(currentline);
				}else{
					thestate = outside;
				}
				break;
			}
		case urlattribute:
			{
				CString command,parameter;
				command = currentline.SpanExcluding(":");
				parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);

				if (command == "PERIODDURATION"){
					m_periodduration.Add(parameter);
				}else if (command == "ATTRIBUTE"){
					m_perioddurationtype = parameter;
				}else if (command == "</URLATTRIBUTE>"){
					thestate = outside;
				}else{
					//hmmmm....
				}
				break;

			}
		case attribute:
			{
				CString command,parameter;
				command = currentline.SpanExcluding(":");
				parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);

				if (command == "DATE"){
					m_dateformat = parameter;
				}else if(command == "DATEDELIM"){
					m_datedelim = parameter;
				}else if(command == "TIME"){
					m_timeformat = parameter;
				}else if(command == "TIMEDELIM"){
					m_timedelim = parameter;
				}else if(command == "DESCRIPTIONTYPE"){
					m_descriptiontype = parameter;
				}else if(command == "DESCRIPTIONDELIM"){
					m_descriptiondelim = parameter;
				}else if(command == "</ATTRIBUTE>"){
					thestate = outside;
				}else{
					//hmmmmm....
				}
				break;
			}
		case statetable:
			{
				if (currentline == "<INITIALIZE>"){
					thestate = stateinitialize;
				}else if (currentline == "<STATE>"){
					thestate = state;
				}else if (currentline == "</STATETABLE>"){
					thestate = outside;
				}else{
					//hmmmmm....
				}
				break;
			}
		case stateinitialize:
			{
				CString command,parameter;
				command = currentline.SpanExcluding(":");
				parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);

				if (command == "STRING"){
					m_initialstring = parameter;
				}else if (command == "</INITIALIZE>"){
					thestate = statetable;
				}else{
					///hmmmm...
				}
				break;
			}
		case state:
			{
				//I can't leave this state until the entire parserstate is read in
				//so I must loop.  I must also check to see if the State has already been
				//created so I can modify it if necessary.

				CString command,parameter, tempstate;
				CParserData * pParserData;

			

				//pParserData = new CParserData;

				while (currentline != "</STATE>")
				{
					command = currentline.SpanExcluding(":");
					parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);
					
					if (command == "STATE"){
						//This has to be the first command after the <STATE> tag
						if(!m_parsermachine.Lookup(parameter,pParserData)){
							pParserData = new CParserData;
							pParserData->state = parameter;
							tempstate = parameter;
						}
					}else if (command == "NEXT"){
						pParserData->nextstate.Add(parameter);
					}else if (command == "TRIGGER"){
						pParserData->trigger.Add(parameter);
					}else if (command == "ACTION"){
						pParserData->action.Add(parameter);
						if(parameter == "NULL"){
							pParserData->searchstring.Add("NULL");
							pParserData->attribute.Add("NULL");
						}
					}else if (command == "SEARCHSTRING"){
						pParserData->searchstring.Add(parameter);
					}else if (command == "ATTRIBUTE"){
						pParserData->attribute.Add(parameter);
					}else{
						//hmmmm....
					}

					parserfile.ReadString(currentline);
					currentline.TrimLeft();
					currentline.TrimRight();
				}

				m_parsermachine.SetAt(tempstate,pParserData);
				
				thestate = statetable;

				break;

			}
		}
	}

	parserfile.Close();
	return TRUE;
}

int CWebParser::getListing(TTimerDataArray * result, 
						   CTime date,
						   CString channel,
						   CString channelname,
						   int channelID)
{
	// Here, I should convert the time parameters he format needed for the URL.  Once this is done
	// I should give it to TryURL for testing.  Next step will be to parse the information.

	//I should get 24hours worth of listings
		
	CInternetSession session;
	
	CInternetFile * theFile = NULL;

	pProgDataOld = NULL;

	CString theURL;
	CString command,parameter,currentline;
	m_date = date;
	m_date = CTime(m_date.GetYear(), m_date.GetMonth(), m_date.GetDay(),0,0,0);
	m_end = m_start = m_date;
	//m_end = endtime;

	m_channelname = channelname;
	m_channelID = channelID;
	m_channel = channel;

	//m_currentperiod = 0;

	for(int i = 0; i < m_periodduration.GetSize(); i++)
	{
		m_currentperiod = m_periodduration.GetAt(i);
		m_end = m_start = m_date;

		if(m_perioddurationtype == "DATE"){
			m_end += CTimeSpan(0,atoi(m_currentperiod),0,0);
		}

		theURL.Empty();
		ConstructURL(&theURL);
		try
		{
			//We know for sure this is an Internet file,
			//so the cast is safe
			theFile = (CInternetFile*) session.OpenURL(theURL);
		}
		catch (CInternetException* pEx)
		{
			//if anything went wrong, just set file to NULL
			theFile = NULL;
			pEx->Delete();
		}
    
		if (theFile)
		{
			//Parse the file into something meaningful
			
			ParseFile(result, theFile, FALSE);
	
			theFile->Close();
			delete theFile;
		}

		//Now I can safely update the period duration

		if(m_perioddurationtype == "DATE"){
			m_date += CTimeSpan(0,atoi(m_currentperiod),0,0);
		}


	}

	//This bit is too get the first entry off the next periods listings so that
	//We can get the finish time for the last programme

	m_currentperiod += m_periodduration.GetAt(0);
	ConstructURL(&theURL);
	theFile = (CInternetFile*) session.OpenURL(theURL);
	ParseFile(result,theFile,TRUE);


	return 0;
}	 

BOOL CWebParser::ConstructURL(CString * theURL)
{
	CString currentline, command, parameter;

	theURL->Empty();

	for(int i = 0; i < m_nameresolution.GetSize(); i++)
	{
		currentline = m_nameresolution.GetAt(i);
		command = currentline.SpanExcluding(":");
		parameter = currentline.Right(currentline.GetLength() - command.GetLength() - 1);

		if(command == "STRING"){
			*theURL += parameter;
		}else if (command == "STARTTIME"){
			*theURL += m_start.Format(parameter);
		}else if (command == "ENDTIME"){
			*theURL += m_end.Format(parameter);
		}else if (command == "DATE"){
			*theURL += m_date.Format(parameter);
		}else if (command == "RELATIVEDAY"){
			CTime today = CTime::GetCurrentTime();
			int diff = m_date.GetDay() - today.GetDay() + 1;
			CString temp;
			temp.Format("%d",diff);

			*theURL += temp;
		}else if (command == "CHANNELID"){
			*theURL += m_channel;
		}else if (command == "PERIOD"){
			CString temp;
			temp.Format("%d",m_currentperiod);
			*theURL += temp;
		}
	}

	return TRUE;

}

/*
BOOL CWebParser::TryURL(TTimerDataArray * result, CString URL, CInternetFile * theFile)
{
	//This function should simply connect to the URL generated above and pass the
	//stream onto the Parse function
     
	
     
	try
    {
		//We know for sure this is an Internet file,
        //so the cast is safe
       theFile = (CInternetFile*) session.OpenURL(URL);
	}
    catch (CInternetException* pEx)
	{
		//if anything went wrong, just set file to NULL
        theFile = NULL;
        pEx->Delete();
	}
    
	if (file)
    {
		//Parse the file into something meaningful
		BOOL parseresult; //parseBBCfile2(result, file);
		parseresult = ParseFile(result, file, FALSE);
	
        file->Close();
        delete file;
		return parseresult;
	}else{
		//No File   
		return FALSE;
    }

}
*/

BOOL CWebParser::ParseFile(TTimerDataArray* result, CInternetFile* theFile, BOOL getfirstonly)
{
	CString currentline,currenttag,currentstate;
	int index = 0;
	//CTimerData * pProgData;
	//CTimerData * pProgDataOld = NULL;
	CTime starttime, endtime;
	
	

	//Quickly goto the initial string
	if (!findToken(m_initialstring,theFile)) return FALSE;
	currentstate = "initial";
	CParserData * pParserData;

	if(!m_parsermachine.Lookup(currentstate,pParserData)){
		MessageBox(NULL,"We have a problem looking up the state","",MB_ICONEXCLAMATION);
		return FALSE;
	}
		
	while(theFile->ReadString(currentline))
	{
		while((index+1) < currentline.GetLength())
		{
			index = getTag(currentline, index, &currenttag);
			
			for(int j = 0; j<pParserData->trigger.GetSize(); j++)
			{
				//Check to see if the current tag should trigger the machine
				if (currenttag.Find(pParserData->trigger.GetAt(j)) >= 0)
				{
					//perform an action (if any) and set to nextstate
					if (pParserData->action.GetAt(j) == "TERMINATE"){
						return TRUE;
					}
					
					
					if (pParserData->action.GetAt(j) == "NEWENTRY")
					{
						pProgData = new CTimerData;
						pProgData->m_channel = m_channelname;
						pProgData->m_channelID = m_channelID;
					}
					if (pParserData->action.GetAt(j) != "NULL")
					{
						//get data
						if (pParserData->attribute.GetAt(j) == "TIME"){
							CString tempstr, tempsearch;
							
							tempsearch = pParserData->searchstring.GetAt(j);

							extractText(tempsearch,(index-currenttag.GetLength()),currentline,&tempstr);
							starttime = StringToTime(m_timeformat,tempstr,m_timedelim);

							pProgData->m_starttime = starttime.GetTime();

							//Because I need both the start and end time for a timer. A timer can't be saved until
							//I have the starttime of the next show.

							if(pProgDataOld){
								endtime = starttime - CTimeSpan(0,0,0,5);
								pProgDataOld->m_endtime = endtime.GetTime();
								result->Add(pProgDataOld);
								if(getfirstonly) return TRUE;
							}
						
						}else if(pParserData->attribute.GetAt(j) == "PROGRAMME"){
							extractText(pParserData->searchstring.GetAt(j),(index-currenttag.GetLength()),currentline,&(pProgData->m_programme));

						}else if(pParserData->attribute.GetAt(j) == "DESCRIPTION"){
							CString temp;
							extractText(pParserData->searchstring.GetAt(j),(index-currenttag.GetLength()+1),currentline,&temp,m_descriptiondelim.GetAt(0));
							
							if(m_descriptiontype == "EXTERNAL"){
								pProgData->m_description = m_descriptiontype + ":" + m_parserurl + temp;
							}else{
								pProgData->m_description = temp;
							}

						}
					}
					if (pParserData->action.GetAt(j) == "ENDENTRY")
					{
						pProgDataOld = pProgData;
					}

					currentstate = pParserData->nextstate.GetAt(j);
					m_parsermachine.Lookup(currentstate,pParserData);
				}
			}
		}
		index = 0;
	}
	return TRUE;
}



BOOL CWebParser::findToken(CString searchstring, CInternetFile * thefile)
{
	CString currentline = "";

	while(currentline.Find(searchstring) == -1)
	{
		if(thefile->ReadString(currentline) == NULL)
		{
			MessageBox(NULL, "There are no listings on this page","Warning", MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	return TRUE;
}


//This function will take 2 strings and convert the second into a CTime object based on the format of the first
//in a sort of strftime fashion. For example if the format string was "%A %d %B", this would match to "Friday 6 June".
//Whitespace between words is irrelevant, so exact string format is not required(almost token like), although specfied characters
//such as \ or : will be noted and used.
//For dates, in the absence of a year, the current system year will be used
CTime CWebParser::StringToTime(CString format, CString input, CString delim)
{
	int year, month, day, hour, minute;
	CTime result;
	
	year = m_date.GetYear();
	month = m_date.GetMonth();
	day = m_date.GetDay();
	hour = 0;
	minute = 0;

	//if(m_end < m_start) day++;


	CToken tformat(format);
	CToken tinput(input);

	CString ftok, itok;
	//CString delim = format;
	
	tformat.SetToken(delim + " ");
	tinput.SetToken(delim + " ");

	while(tformat.MoreTokens() && tinput.MoreTokens())
	{
		ftok = tformat.GetNextToken();
		itok = tinput.GetNextToken();

		if (ftok == "%a"){ //Abbreviated Weekday Name
			//ignore this for the moment
		}else if (ftok == "%A"){ //Full Weekday Name
			//ignore this for the moment
		}else if (ftok == "%b"){ //Abbreviated Month Name
			CString abbrmonth = "janfebmaraprmayjunjulaugsepoctnovdec";
			itok.MakeLower();
			month = abbrmonth.Find(itok,0);
			if(month>0) month = month/3;
		}else if (ftok == "%B"){ //Full Month Name
			CString fullmonth = "january  february march    april    may      june     july     august   septemberoctober  november december ";
			itok.MakeLower();
			month = fullmonth.Find(itok,0);
			if(month>0) month = month/9;
		}else if (ftok == "%d"){ //Day of month as decimal (01 - 31)
			day = atoi(itok);
		}else if (ftok == "%dxx"){
			CString temp = itok.Left(itok.GetLength() - 2);
			day = atoi(temp);
		}else if (ftok == "%H"){ //hour in 24hr formar (00 - 23)
			hour = atoi(itok);
		}else if (ftok == "%I"){ //hour in 12hr format (01 - 12)
			hour = atoi(itok);
			if (hour == 12) hour = 0;

		}else if (ftok == "%m"){ //month as decimal number (01 - 12)
			month = atoi(itok);

		}else if (ftok == "%M"){ //minute as decimal number (00 - 59)
			minute = atoi(itok);

		}else if (ftok == "%p"){ //AM or PM
			itok.MakeUpper();
			if(itok == "PM") hour += 12;
		}else if (ftok == "%S"){ //Seconds as decimal number (00 - 59)
			//ignore this for the moment

		}else if (ftok == "%y"){ //Year without century (00-99)
			year = atoi(itok);
			if(year<70){
				year += 2000;
			}else{
				year += 1900;
			}

		}else if (ftok == "%Y"){ //Year with century
			year = atoi(itok);

		}else{ //Unrecognized Format Token
			

		}



	}

	result = CTime(year,month,day,hour,minute,0);
	return result;

}



// Finds and extracts html tag in string after the given index.  returns the index for the end of the tag.
// Will return -1 if end of line found.
int CWebParser::getTag(CString searchstring, int index, CString * result)
{
	int linelength = searchstring.GetLength();
	int i;
	bool tag = false;
	
	result->Empty();

	for (i = index; i<linelength; i++){
		if(!tag){
			if(searchstring.GetAt(i) == '<'){
				*result += searchstring.GetAt(i);
				tag = !tag;
			}
		}else{
			if(searchstring.GetAt(i) != '>'){
				*result += searchstring.GetAt(i);
			}else{
				*result += searchstring.GetAt(i);
				return i;
			}
		}
	}
	return linelength;
}


void CWebParser::extractText(CString tag, int nStart, CString line, CString * result, char terminate)
{
	// Take out the text following the tag found until the next tag
	CString tempstr;
	int index, max;
	index = line.Find(tag,nStart) + tag.GetLength();

    max = line.GetLength();
	
	result->Empty();
	for(index;index < max;index++)
	{
		if( (line.GetAt(index)) != terminate ){
			*result += line.GetAt(index);
		}else{
			//result[count++] = '\0';
			result->TrimRight();
			result->TrimLeft();
			return;
		}
	}

}

