#pragma once
#include "AutoIt.h"
#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
#endif

class SysUtil {
public:
    bool    GetFileVersion(char *szFile, char *szVersion);

    bool    IsWinHung(HWND hWnd, UINT nTimeOut = 5000);
    void    AttachThreadInput(HWND hWnd, bool bAttach);

    int     MouseDown(const char *szButton);
    int     MouseUp(const char *szButton);
    int     MouseWheel(const char *szDirection);

    //bool    DownloadFile(const char *szUrl, const char *szOutFile, bool &bFatal);
    void    SoundPlay(const char *szFilename, bool bWait);

    void    GetIPAddress(int nAdapter, char *szInetBuf);

    void    Sleep(int nTimeOut);
    int     WinPrintf(const char *szTitle, const char *szFormat, ...);
    
    void    BGRtoRGB(int &nCol);
    void    RGBtoBGR(int &nCol);

    void    FatalError(UINT iErrTitle, UINT iErrMsg, HWND hWnd);
    void    FatalError(const char *szTitle, const char *szText, HWND hWnd);
    static int     NewHandler( size_t size);
    
    void    RandInit(void);
    
    void    RegReadString(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwBufLen, char *szValue);
    
    void    WinKill(HWND hWnd);
    
    bool    DoesProcessExist(const char *szName, DWORD &dwPid, bool &bResult);
    bool    DoesProcessExist9x2000(const char *szName, DWORD &dwPid, bool &bResult);
    bool    DoesProcessExistNT(const char *szName, DWORD &dwPid, bool &bResult);
    
    int     MessageBoxEx(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uTimeout);
    
    const char * GetWinText(HWND hWnd, bool bDetectHiddenText);
    const char * GetClassList(HWND hWnd);
    
    #ifdef _DEBUG
        void DebugMsg(const char *szFormat, ...);
    #endif
     
    HICON    LoadIcon(int nID, int nWidth, int nHeight, int nDepth, HINSTANCE instance);
    bool    ConvSystemTime(const char *szTime, SYSTEMTIME *st, bool bDate, int nSep);

    BOOL    Shutdown(int nFlag, HWND g_hWnd);
};

extern SysUtil g_oSysUtil;
