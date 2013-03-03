#ifndef TIMERGUIDEEXPORT
#define TIMERGUIDEEXPORT


#ifdef __cplusplus
	extern "C" {
#endif

BOOL showTimerDlg(HWND hWndParent, LPCTSTR librarypath);

BOOL addToTimer(LPCTSTR progname, 
				DWORD starttime, 
				DWORD endtime,
				LPCTSTR channel,
				int channelID);

BOOL getNextTimer(DWORD timenow,
				  LPSTR progname,
				  DWORD *starttime,
				  int *duration,
				  int *channelID);

BOOL showGuideDlg(HWND hWndParent, LPCTSTR librarypath, int currchan);
BOOL getCurrentProg(LPSTR progname, int currchan);
BOOL checkGuideValidity();

#ifdef __cplusplus
	}
#endif



#endif