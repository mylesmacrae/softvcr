#ifndef __PARSERTYPES__
#define __PARSERTYPES__



#include <vector>

using namespace std;




//program listing class...  this represents a single program listing. Collections made
//using STL vector template.
class Programme
{
private:	
	CString name, description;
	CTime starttime, endtime;
	int channel;

public:
	Programme(int channel, CString tname, CString tdesc, CTime tstart, CTime tend);
	//~Programme();

	int getchannel();
	CString getname();
	CString getdescription();
	CTime getstarttime();
	CTime getendtime();
};

typedef vector<Programme> ProgrammeList;
typedef vector<ProgrammeList> ProgrammeGuide;
typedef vector<CString> ChannelList;

//typedef CList<Programme, Programme&> CProgrammeList;
//typedef CList<CProgrammeList, CProgrammeList&> CProgrammeGuide;



#endif