#ifndef VIDLIBRARYEXPORT
#define VIDLIBRARYEXPORT




#ifdef __cplusplus
	extern "C" {
#endif

BOOL showLibraryDlg(HWND hWndparent,LPCTSTR LibraryPath);
BOOL addToLibrary(LPCTSTR progname, 
				  LPCTSTR channel, 
				  LONG timedate, 
				  double duration,
				  LPCTSTR path, 
				  int channelID);

#ifdef __cplusplus
	}
#endif



#endif