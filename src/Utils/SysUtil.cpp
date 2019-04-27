#include "StdAfx.h"                                // Pre-compiled headers
#include "SysUtil.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <time.h>
    #include <sys/timeb.h>
    #include <tlhelp32.h>                            // Win95 PS functions
    #include <process.h>                            // Threading (beginthreadex, etc)
    #include <limits.h>                                // UINT_MAX etc
    #include <wininet.h>
    #include <shlobj.h>
    #include <ctype.h>
#endif

#include "OSVersion.h"
#include "StrUtil.h"
#include "mt19937ar-cok.h"
#include "Engine/Type/AString.h"

// Defines
#define UTIL_WINTEXTBUFFERSIZE    32767            // 64KB is enough wintext for anyone! :) (64kb is max for win95) (32KB max for WM_GETTEXT)

SysUtil g_oSysUtil = SysUtil();

typedef struct                                    // Storage for MessageBoxEx thread
{
    DWORD      CurrentThreadID;
    DWORD      dwTimeout;
} MsgBoxExData;


// Globaldata unique to this file (used by some of the callbacks/threads)
HWND    g_hwndMsgBox;
bool    g_bMsgBoxThreadEnabled;
bool    g_bMsgBoxTimedOut;

char    g_szWinTextBuffer[UTIL_WINTEXTBUFFERSIZE+1];
bool    g_bDetectHiddenText;

HICON   g_IconFind_hIcon;
int     g_IconFind_nWidth;
int     g_IconFind_nHeight;
int     g_IconFind_nDepth;

///////////////////////////////////////////////////////////////////////////////
// SysUtil::GetFileVersion()
//
// Gets the FileVersion info for a given filename, returns false if unsuccessful.
// szVersion must be 43+1 chars long for maxium version number size
//
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::GetFileVersion(char *szFile, char *szVersion)
{
    // Get size of the info block
    DWORD                dwUnused;
    DWORD dwSize = GetFileVersionInfoSize(szFile, &dwUnused);

    if (dwSize)
    {
        VS_FIXEDFILEINFO    *pFFI;
        UINT                uSize;

        BYTE *pInfo = new BYTE[dwSize];

        // Read the version resource
        GetFileVersionInfo((LPSTR)szFile, 0, dwSize, (LPVOID)pInfo);

        // Locate the fixed information
        if (VerQueryValue(pInfo, "\\", (LPVOID *)&pFFI, &uSize)!=0)
        {
            //extract the fields you want from pFFI
            uint iFileMS = (uint)pFFI->dwFileVersionMS;
            uint iFileLS = (uint)pFFI->dwFileVersionLS;
            sprintf(szVersion, "%u.%u.%u.%u", (iFileMS >> 16), (iFileMS & 0xffff), (iFileLS >> 16), (iFileLS & 0xffff) );

            //free(pInfo);
            delete [] pInfo;
            return true;
        }
        else
        {
            delete [] pInfo;
            return false;
        }
    }
    else
        return false;

} // SysUtil::GetFileVersion

///////////////////////////////////////////////////////////////////////////////
// SysUtil::FatalError()
//
// Displays a message box with an error message (either from a string resource
// or passed string).
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::FatalError(UINT iErrTitle, UINT iErrMsg, HWND hWnd)
{
    char szTitle[256+1];                        // Max message is 256 characters
    char szText[256+1];                            // Max message is 256 characters

    LoadString(GetModuleHandle(NULL), iErrTitle, szTitle, 256);
    LoadString(GetModuleHandle(NULL), iErrMsg, szText, 256);
    MessageBox(hWnd, szText, szTitle, MB_ICONSTOP | MB_OK | MB_SYSTEMMODAL | MB_SETFOREGROUND);

} // SysUtil::FatalError()


void SysUtil::FatalError(const char *szTitle, const char *szText, HWND hWnd)
{
    MessageBox(hWnd, szText, szTitle, MB_ICONSTOP | MB_OK | MB_SYSTEMMODAL | MB_SETFOREGROUND);

} // SysUtil::FatalError()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::IsWinHung()
//
// Safely checks if a window a in a hung state (default timeout is 5000ms)
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::IsWinHung(HWND hWnd, UINT nTimeOut)
{
    DWORD_PTR dwResult;

    if (SendMessageTimeout(hWnd, WM_NULL, 0, 0, SMTO_ABORTIFHUNG, nTimeOut, &dwResult))
        return false;
    else
        return true;

} // SysUtil::IsWinHung()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::AttachThreadInput()
//
// Attaches this thread to another input thread - doesn't if hung
///////////////////////////////////////////////////////////////////////////////

void SysUtil::AttachThreadInput(HWND hWnd, bool bAttach)
{
    if (bAttach == true)
    {
        if (IsWinHung(hWnd) == false)
            ::AttachThreadInput(::GetCurrentThreadId(), ::GetWindowThreadProcessId(hWnd, NULL), TRUE);
    }
    else
        ::AttachThreadInput(::GetCurrentThreadId(), ::GetWindowThreadProcessId(hWnd, NULL), FALSE);

} // SysUtil::AttachThreadInput()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::MouseDown()
//
// Produces a Mouse Down event
// Buttons recognized:  left|middle|right|main|menu|primary|secondary
///////////////////////////////////////////////////////////////////////////////

int SysUtil::MouseDown(const char *szButton)
{
    char swapped[4];
    DWORD event=0;

    if ( szButton[0] == '\0' || stricmp(szButton, "LEFT")==0 ) // empty string or "left"
        event = MOUSEEVENTF_LEFTDOWN;
    else if ( stricmp(szButton,"RIGHT")==0 )
        event = MOUSEEVENTF_RIGHTDOWN;
    else if ( stricmp(szButton,"MIDDLE")==0 )
        event = MOUSEEVENTF_MIDDLEDOWN;
    else
    {
        SysUtil::RegReadString(HKEY_CURRENT_USER, "Control Panel\\Mouse", "SwapMouseButtons", 4, swapped );
        if ( swapped[0] == '1')    // buttons swapped
        {
            if ( stricmp(szButton,"MAIN")==0 || stricmp(szButton, "PRIMARY"))
                event = MOUSEEVENTF_RIGHTDOWN;
            else if ( stricmp(szButton,"MENU")==0 || stricmp(szButton, "SECONDARY"))
                event = MOUSEEVENTF_LEFTDOWN;
        }
        else
        {
            if ( stricmp(szButton,"MAIN")==0 || stricmp(szButton, "PRIMARY"))
                event = MOUSEEVENTF_LEFTDOWN;
            else if ( stricmp(szButton,"MENU")==0 || stricmp(szButton, "SECONDARY"))
                event = MOUSEEVENTF_RIGHTDOWN;
        }
    }
    if (event != 0) {
        mouse_event(event, 0, 0, 0, 0);
        return 1;
    }
    else
        return 0;

} // SysUtil::MouseDown()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::MouseUp()
//
// Produces a Mouse Down event
///////////////////////////////////////////////////////////////////////////////

int SysUtil::MouseUp(const char *szButton)
{
    char swapped[4];
    DWORD event = 0;    // default to 0 in case no strings match

    if ( szButton[0] == '\0' || stricmp(szButton, "LEFT")==0 ) // empty string or "left"
        event = MOUSEEVENTF_LEFTUP;
    else if ( stricmp(szButton,"RIGHT")==0 )
        event = MOUSEEVENTF_RIGHTUP;
    else if ( stricmp(szButton,"MIDDLE")==0 )
        event = MOUSEEVENTF_MIDDLEUP;
    else
    {
        SysUtil::RegReadString(HKEY_CURRENT_USER, "Control Panel\\Mouse", "SwapMouseButtons", 4, swapped );
        if ( swapped[0] = '1')    // buttons swapped
        {
            if ( stricmp(szButton,"MAIN")==0 || stricmp(szButton, "PRIMARY"))
                event = MOUSEEVENTF_RIGHTUP;
            else if ( stricmp(szButton,"MENU")==0 || stricmp(szButton, "SECONDARY"))
                event = MOUSEEVENTF_LEFTUP;
        }
        else
        {
            if ( stricmp(szButton,"MAIN")==0 || stricmp(szButton, "PRIMARY"))
                event = MOUSEEVENTF_LEFTUP;
            else if ( stricmp(szButton,"MENU")==0 || stricmp(szButton, "SECONDARY"))
                event = MOUSEEVENTF_RIGHTUP;
        }
    }
    if (event != 0) {
        mouse_event(event, 0, 0, 0, 0);
        return 1;
    }
    else
        return 0;

} // SysUtil::MouseUp()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::MouseWheel()
//
// Produces a Mouse Down event
///////////////////////////////////////////////////////////////////////////////

int SysUtil::MouseWheel(const char *szDirection)
{
    if ( stricmp(szDirection,"UP")==0 )
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, +120, 0);
    else if ( stricmp(szDirection, "DOWN")==0 )
        mouse_event(MOUSEEVENTF_WHEEL, 0, 0, (DWORD)-120, 0);
    else
        return 0;

    return 1;

} // SysUtil::MouseWheel()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::NewHandler()
//
// This function is called when the "new" or "malloc" functions fail to allocate
// memory
//
///////////////////////////////////////////////////////////////////////////////

int SysUtil::NewHandler( size_t size)
{
    MessageBox(NULL, "Error allocating memory.", "AutoIt", MB_ICONSTOP | MB_OK);
    exit(1);                                    // Force termination

    return 0;                                    // Never reached, but compiler wants a return value
}


///////////////////////////////////////////////////////////////////////////////
// SysUtil::RandInit()
//
// Call this function to initialise the C random number routine so that it
// at least _tries_ to produce random numbers
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::RandInit(void)
{
    // Initialize the awful C random number routine
    struct _timeb timebuffer;
    _ftime( &timebuffer );
    //srand(timebuffer.millitm * (int)time(NULL));

    // Init our custom random number routine
    init_genrand(timebuffer.millitm * (int)time(NULL));

} // SysUtil::RandInit()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::RegReadString()
//
// Read a string from a registry key
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::RegReadString(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwBufLen, char *szValue )
{
    HKEY    hRegKey;

    // Make sure the return value is blank just in case we error
    szValue[0] = '\0';

    if (RegOpenKeyEx(hKey, lpSubKey, 0, KEY_QUERY_VALUE, &hRegKey) != ERROR_SUCCESS)
        return;

    RegQueryValueEx(hRegKey, lpValueName, NULL, NULL, (LPBYTE)szValue, &dwBufLen);

    RegCloseKey(hRegKey);

} // SysUtil::RegReadString()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::WinKill()
//
// Closes a window with extreme predjudice
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::WinKill(HWND hWnd)
{
    DWORD_PTR      dwResult;

    LRESULT lResult = SendMessageTimeout(hWnd, WM_CLOSE, 0, 0, SMTO_ABORTIFHUNG, 500, &dwResult);    // wait 500ms

    if( !lResult )
    {
        // Use more force - Mwuahaha

        // Get the ProcessId for this window.
        DWORD    pid;
        GetWindowThreadProcessId( hWnd, &pid );

        // Open the process with all access.
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

        // Terminate the process.
        TerminateProcess(hProcess, 0);

        CloseHandle(hProcess);
    }

} // SysUtil::WinKill()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::DoesProcessExist()
//
// Checks for the existance of a process name - it will determine the OS version
// and run once piece of code for NT4 and another for 9x/2000+
//
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::DoesProcessExist(const char *szName, DWORD &dwPid, bool &bResult)
{
    if (g_oVersion.IsWinNT4())
    {
        // NT4
        return SysUtil::DoesProcessExistNT(szName, dwPid, bResult);
    }
    else
    {
        // 9x/2000+
        return SysUtil::DoesProcessExist9x2000(szName, dwPid, bResult);
    }

} // SysUtil::DoesProcessExist()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::DoesProcessExist9x()
//
// Checks for the existance of a process name (NT version)
//
// Actually this will run under 2000 and XP too
//
// Dynamincally load functions to retain Win NT compatability - yes it is a
// PAIN IN THE ARSE!
//
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::DoesProcessExist9x2000(const char *szName, DWORD &dwPid, bool &bResult)
{
typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);

    HANDLE            snapshot;
    PROCESSENTRY32    proc;
    HINSTANCE        hinstLib;
    CREATESNAPSHOT    lpfnCreateToolhelp32Snapshot = NULL;
    PROCESSWALK        lpfnProcess32First = NULL;
    PROCESSWALK        lpfnProcess32Next  = NULL;
    char            szDrive[_MAX_PATH+1];
    char            szDir[_MAX_PATH+1];
    char            szFile[_MAX_PATH+1];
    char            szExt[_MAX_PATH+1];
    DWORD            dwTemp;

    // We must dynamically load the function to retain compatibility with WinNT
    hinstLib = GetModuleHandle("KERNEL32.DLL");
    if (hinstLib == NULL)
        return false;

    lpfnCreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(hinstLib, "CreateToolhelp32Snapshot");
    lpfnProcess32First = (PROCESSWALK)GetProcAddress(hinstLib, "Process32First");
    lpfnProcess32Next  = (PROCESSWALK)GetProcAddress(hinstLib, "Process32Next");

    if (lpfnCreateToolhelp32Snapshot == NULL || lpfnProcess32First == NULL ||
        lpfnProcess32Next == NULL )
    {
        FreeLibrary(hinstLib);                    // Free the DLL module.
        return false;
    }

    proc.dwSize = sizeof(proc);
    snapshot = lpfnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    lpfnProcess32First(snapshot, &proc);

    bResult = false;
    dwTemp = (DWORD)atoi(szName);                // Get the int value of the string (in case it is a PID)
    while (bResult == false && lpfnProcess32Next(snapshot, &proc) == TRUE )
    {
        _splitpath( proc.szExeFile, szDrive, szDir, szFile, szExt );    // Split the filename
        strcat(szFile, szExt);
        //MessageBox(NULL, szFile, szName, MB_OK);

        if (!stricmp(szFile, szName))
        {
            bResult    = true;                        // Try matching as a name
            dwPid    = proc.th32ProcessID;
        }
        else
        {
            if (dwTemp != 0 && dwTemp == proc.th32ProcessID)
            {
                bResult    = true;
                dwPid    = proc.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    //FreeLibrary(hinstLib);                    // GetModuleHandle does not need a freelibrary

    return true;

} // SysUtil::DoesProcessExist9x2000()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::DoesProcessExistNT()
//
// Checks for the existance of a process name (NT version).
//
// REQUIRES PSAPI.DLL - not standard under NT 4
//
// Dynamincally load functions to retain Win 9x compatability - yes it is a
// PAIN IN THE ARSE!
//
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::DoesProcessExistNT(const char *szName, DWORD &dwPid, bool &bResult)
{
typedef BOOL (WINAPI *MyEnumProcesses)(DWORD*, DWORD, DWORD*);
typedef BOOL (WINAPI *MyEnumProcessModules)(HANDLE, HMODULE*, DWORD, LPDWORD);
typedef DWORD (WINAPI *MyGetModuleBaseName)(HANDLE, HMODULE, LPTSTR, DWORD);

//BOOL EnumProcesses(
//  DWORD *lpidProcess,  // array of process identifiers
//  DWORD cb,            // size of array
//  DWORD *cbNeeded      // number of bytes returned
//);

//BOOL EnumProcessModules(
//  HANDLE hProcess,      // handle to process
//  HMODULE *lphModule,   // array of module handles
//  DWORD cb,             // size of array
//  LPDWORD lpcbNeeded    // number of bytes required
//);

//DWORD GetModuleBaseName(
//  HANDLE hProcess,    // handle to process
//  HMODULE hModule,    // handle to module
//  LPTSTR lpBaseName,  // base name buffer
//  DWORD nSize         // maximum characters to retrieve
//);

    HINSTANCE                hinstLib;

    MyEnumProcesses            lpfnEnumProcesses;
    MyEnumProcessModules    lpfnEnumProcessModules;
    MyGetModuleBaseName        lpfnGetModuleBaseName;

    DWORD                    idProcessArray[512];        // 512 processes max
    DWORD                    cbNeeded;                    // Bytes returned
    DWORD                    cProcesses;                    // Number of processes
    unsigned int            i;
    char                    szProcessName[_MAX_PATH+1];
    HMODULE                    hMod;
    HANDLE                    hProcess;
    char                    szDrive[_MAX_PATH+1];
    char                    szDir[_MAX_PATH+1];
    char                    szFile[_MAX_PATH+1];
    char                    szExt[_MAX_PATH+1];
    DWORD                    dwTemp;

    // We must dynamically load the function to retain compatibility with Win95
    // Get a handle to the DLL module that contains EnumProcesses
    hinstLib = LoadLibrary("psapi.dll");
    if (hinstLib == NULL)
        return false;

      lpfnEnumProcesses        = (MyEnumProcesses)GetProcAddress(hinstLib, "EnumProcesses");
    lpfnEnumProcessModules    = (MyEnumProcessModules)GetProcAddress(hinstLib, "EnumProcessModules");
    lpfnGetModuleBaseName    = (MyGetModuleBaseName)GetProcAddress(hinstLib, "GetModuleBaseNameA");

    if (lpfnEnumProcesses == NULL || lpfnEnumProcessModules == NULL ||
        lpfnGetModuleBaseName == NULL )
    {
        FreeLibrary(hinstLib);                    // Free the DLL module.
        return false;
    }


    // Get the list of processes running
    if ( !lpfnEnumProcesses(idProcessArray, sizeof(idProcessArray), &cbNeeded))
    {
        FreeLibrary(hinstLib);                    // Free the DLL module.
        return false;
    }

    // Get the count of PIDs in the array
    cProcesses = cbNeeded / sizeof(DWORD);

    bResult = false;
    dwTemp = (DWORD)atoi(szName);                // Get the int value of the string (in case it is a PID)
    for(i = 0; i<cProcesses && bResult==false; i++)
    {
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, idProcessArray[i] );
        lpfnEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded);

        if ( lpfnGetModuleBaseName(hProcess, hMod, szProcessName, _MAX_PATH) )
        {
            _splitpath( szProcessName, szDrive, szDir, szFile, szExt );    // Split the filename
            strcat(szFile, szExt);
            //MessageBox(NULL, szFile, "Process NT", MB_OK);

            if (!stricmp(szFile, szName))
            {
                bResult    = true;                    // Try matching as a name
                dwPid    = idProcessArray[i];
            }
            else
            {
                if (dwTemp != 0 && dwTemp == idProcessArray[i])
                {
                    bResult    = true;
                    dwPid    = idProcessArray[i];
                }
            }
        }

        CloseHandle(hProcess);
    }

    FreeLibrary(hinstLib);                    // Free the DLL module.

    return true;

} // SysUtil::DoesProcessExistNT()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::MessageBoxEx()
//
// Windows message box with an optional timeout (0=wait forever)
///////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK FindMsgBoxProc(HWND hwnd, LPARAM lParam)
{
  char    szClassname[256];
  BOOL    RetVal = TRUE;

  int nRes = GetClassName(hwnd, szClassname, 256);
  if (!strcmp(szClassname, "#32770") )            // Class name for a MessageBox window
  {
    g_hwndMsgBox = hwnd;
    RetVal = FALSE;
  }

  return RetVal;
}

static unsigned int _stdcall TimeoutMsgBoxThread(void *pParam)
{
    MsgBoxExData *pMyData = (MsgBoxExData *)pParam;
    DWORD    dwStart, dwDiff, dwCur;

    // Get the current time, and close the message box after the timeout has been
    // exceeded - check every 10ms to avoid CPU load
    dwStart = timeGetTime();
    for (;;)
    {
        if (g_bMsgBoxThreadEnabled == false)
            return 0;                            // Caller requested close

        // Get current time in ms
        dwCur = timeGetTime();
        if (dwCur < dwStart)
            dwDiff = (UINT_MAX - dwStart) + dwCur; // timer wraps at 2^32
        else
            dwDiff = dwCur - dwStart;

        // Timer elapsed?
        if (dwDiff >= pMyData->dwTimeout)
            break;
        else
            Sleep(10);
    }

    // Find and close the msgbox
    g_hwndMsgBox = NULL;
    EnumThreadWindows(pMyData->CurrentThreadID, FindMsgBoxProc, 0);
    if (g_hwndMsgBox == NULL)
        return 0;                            // MsgBox doesn't exist, just exit

    // Signal the timeout
    g_bMsgBoxTimedOut = true;

    // End the MessageBox with our special message
    EndDialog(g_hwndMsgBox, 1);                // Id 1 works no matter what buttons are used

  return 0;
}

int SysUtil::MessageBoxEx(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uTimeout)
{
    MsgBoxExData    MyData;
    unsigned int    uThreadID;
    HANDLE            hThreadHandle = NULL;

    // Reset the timed out flag
    g_bMsgBoxTimedOut = false;

    if (uTimeout)
    {
        g_bMsgBoxThreadEnabled    = true;
        MyData.CurrentThreadID    = GetCurrentThreadId();
        MyData.dwTimeout        = (DWORD)uTimeout;
        hThreadHandle = (HANDLE)_beginthreadex(NULL, 0, TimeoutMsgBoxThread, (void*)&MyData, 0, &uThreadID);
    }

    // Run the windows message box - the spawned thread will force it to close if it times out
    int Res = MessageBox(hWnd, lpText, lpCaption, uType);

    if (hThreadHandle)
    {
        g_bMsgBoxThreadEnabled = false;            // Signal thread to terminate (if not already)
        WaitForSingleObject(hThreadHandle, INFINITE);
        CloseHandle(hThreadHandle);
    }

    if (g_bMsgBoxTimedOut == true)
        return -1;                                // Timed out
    else
        return Res;
}

///////////////////////////////////////////////////////////////////////////////
// SysUtil::GetWinTextProc()
//
// Handler function for EnumChildWindows
///////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK GetWinTextProc(HWND hWnd, LPARAM lParam)
{
    char    *szWinText = g_szWinTextBuffer;
    SysUtil *self = (SysUtil*)lParam;
    char    szBuffer[UTIL_WINTEXTBUFFERSIZE+1];    // Maximum under win95

    // Don't do any more testing on this child window if it is hung
    if ( self->IsWinHung(hWnd) )
        return TRUE;                            // Carry on searching

    // Ensure the buffer is blank
    szBuffer[0] = '\0';

    // Hidden text?
    if ( (IsWindowVisible(hWnd)) || (g_bDetectHiddenText == true) )
    {
        if (SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0) > 0)
        {
            // if (SendMessage(hWnd,(UINT)WM_GETTEXT,(WPARAM)AUT_WINTEXTBUFFER,(LPARAM)szBuffer))
            // GetWindowText(hWnd, szBuffer, AUT_WINTEXTBUFFER);
            SendMessage(hWnd, WM_GETTEXT,(WPARAM)AUT_WINTEXTBUFFER,(LPARAM)szBuffer);
            szBuffer[UTIL_WINTEXTBUFFERSIZE] = '\0';        // Ensure terminated if large amount of return text
            g_oStrUtil.AddTextToBuffer(szBuffer, szWinText, UTIL_WINTEXTBUFFERSIZE);
            g_oStrUtil.AddTextToBuffer("\n", szWinText, UTIL_WINTEXTBUFFERSIZE);
        }
    }

    return TRUE;                // Carry on searching

} // SysUtil::GetWinTextProc()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::GetWinText()
//
// Gets the title, text and misc information on the specified window
//
///////////////////////////////////////////////////////////////////////////////

const char * SysUtil::GetWinText(HWND hWnd, bool bDetectHiddenText)
{
    // Clear the win text buffer
    g_szWinTextBuffer[0] = '\0';

    // Set our global flag for hidden text
    g_bDetectHiddenText = bDetectHiddenText;

    // Get window text from all the child windows
    ::EnumChildWindows(hWnd, (WNDENUMPROC)GetWinTextProc, (LPARAM)this);

    return g_szWinTextBuffer;

} // GetWinText()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::GetIPAddress()
//
// Gets an IP address for adapter nn (1 is first)
//
// szInetBuf must be at least 16 chars long
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::GetIPAddress(int nAdapter, char *szInetBuf)
{
    HOSTENT        *lpHost;
    IN_ADDR        inaddr;
    WSADATA        wsadata;
    char        szBuf[256];
    int            nNumAdapters;

    if( WSAStartup(MAKEWORD(1, 1), &wsadata) == 0 )
    {
        gethostname(szBuf, sizeof(szBuf) );
        lpHost = gethostbyname(szBuf);

        // How many adapters have we?
        nNumAdapters = 0;
        while(lpHost->h_addr_list[nNumAdapters] != NULL)
            nNumAdapters++;

        if (nAdapter > nNumAdapters)
            strcpy(szInetBuf, "0.0.0.0");
        else
        {
            memcpy(&inaddr,lpHost->h_addr_list[nAdapter-1], 4);
            strcpy(szInetBuf, (char*)inet_ntoa(inaddr));
        }

        WSACleanup();

    }

} // SysUtil::GetIPAddress()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::GetClassList()
//
// Gets List of classnames from a window
//
///////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK GetClassListProc(HWND hWnd, LPARAM lParam)
{
    char    *szWinText = (char*)lParam;
    char    szBuffer[UTIL_WINTEXTBUFFERSIZE+1];                    // Maximum under win95

    GetClassName(hWnd, szBuffer, sizeof(szBuffer));
    if (szBuffer[0] != '\0')
    {
        g_oStrUtil.AddTextToBuffer(szBuffer, szWinText, UTIL_WINTEXTBUFFERSIZE);
        g_oStrUtil.AddTextToBuffer("\n", szWinText, UTIL_WINTEXTBUFFERSIZE);
    }

    return TRUE;                // Carry on searching

} // SysUtil::GetClassListProc()

const char * SysUtil::GetClassList(HWND hWnd)
{
    // Clear the win text buffer
    g_szWinTextBuffer[0] = '\0';

    // Get class names from all the child windows
    EnumChildWindows(hWnd, (WNDENUMPROC)GetClassListProc, (LPARAM)g_szWinTextBuffer);

    return g_szWinTextBuffer;

}

///////////////////////////////////////////////////////////////////////////////
// SysUtil::SoundPlay()
// Asynchronous PlaySound
///////////////////////////////////////////////////////////////////////////////

void SysUtil::SoundPlay(const char *szFilename, bool bWait)
{
    AString    sMCI;
    char    szBuffer[256];

    sMCI = "open ";
    sMCI += '"';
    sMCI += szFilename;
    sMCI += '"';
    sMCI += " alias PlayMe";

    mciSendString("status PlayMe mode",szBuffer,sizeof(szBuffer),NULL);

    if ( !szBuffer[0] == '\0' )
        mciSendString("close PlayMe",NULL,0,NULL);

    if (szFilename[0] == '\0')
        return;                                    // No sound to play

    if ( mciSendString(sMCI.c_str(),NULL,0,NULL)==0 )
    {
        if (bWait)
        {
            mciSendString("play PlayMe wait",NULL,0,NULL);
            mciSendString("close PlayMe",NULL,0,NULL);
        }
        else
            mciSendString("play PlayMe",NULL,0,NULL);
    }

} // SysUtil::SoundPlay()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::Sleep()
//
// A more accurate Sleep(), uses performance counters if possible, otherwise
// just does a normal sleep (timegettime no more accurate than sleep!)
//
// A thread time slice is 10ms on NT, 15ms on NT multiprocessor and 55 ms on
// 9x
///////////////////////////////////////////////////////////////////////////////

void SysUtil::Sleep(int nTimeOut)
{
    // Handle the special cases -1 and 0 first
    if (nTimeOut < 0)
        return;                                    // No sleep at all for -ve numbers
    else if (nTimeOut == 0)
    {
        ::Sleep(0);                                // Special case for 0
        return;
    }

    __int64        start, cur, freq;
    double        diff;
    DWORD        dwMin;
    DWORD        dwTimeOut = (DWORD)nTimeOut;

    // Set the minimum Sleep accuracy
    if (g_oVersion.IsWin9x())
        dwMin = 55;
    else
        dwMin = 10;

    // If Sleep is >= dwMin or no performance counters are available then use native Sleep()
    if (dwTimeOut >= dwMin || !QueryPerformanceCounter((LARGE_INTEGER *)&start))
    {
        ::Sleep(dwTimeOut);
        return;
    }

    // Get frequency
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);

    // Note that we must at least do a Sleep(0) once otherwise the SendTo functions get out of
    // sync - especially on 9x/NT4 but also had one report for XP too (seems be on the keydowndelay)
    do
    {
        ::Sleep(0);                                // Reduce CPU usage - Sleep 0 is special
        QueryPerformanceCounter((LARGE_INTEGER *)&cur);
        diff = ((double)(cur - start) / (double)freq) * 1000.0;

    } while ((DWORD)diff < dwTimeOut);

} // SysUtil::Sleep()



///////////////////////////////////////////////////////////////////////////////
// SysUtil::WinPrintf()
//
// A formatting message box.
//
///////////////////////////////////////////////////////////////////////////////

int SysUtil::WinPrintf(const char *szTitle, const char *szFormat, ...)
{
    char    szBuffer[1024];
    va_list    pArgList;

    va_start(pArgList, szFormat);

    _vsnprintf(szBuffer, sizeof(szBuffer), szFormat, pArgList);

    va_end(pArgList);

    return MessageBox(NULL, szBuffer, szTitle, MB_OK);

} // SysUtil::WinPrintf()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::BGRtoRGB()
//
// Converts a colour from BGR (MS colorref) to RGB
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::BGRtoRGB(int &nCol)
{
    int nR = (nCol & 0x0000ff) << 16;
    int nG = (nCol & 0x00ff00);
    int nB = (nCol & 0xff0000) >> 16;

    nCol = nR | nG | nB;

} // SysUtil::BGRtoRGB()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::RGBtoBGR()
//
// Converts a colour from RGB to BGR (MS colorref)
//
///////////////////////////////////////////////////////////////////////////////

void SysUtil::RGBtoBGR(int &nCol)
{
    int nR = (nCol & 0xff0000) >> 16;
    int nG = (nCol & 0x00ff00);
    int nB = (nCol & 0x0000ff) << 16;

    nCol = nR | nG | nB;

} // SysUtil::RGBtoBGR()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::DebugMsg()
//
// A formatting debug message
//
///////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

void SysUtil::DebugMsg(const char *szFormat, ...)
{
    char    szBuffer[1024];
    va_list    pArgList;

    va_start(pArgList, szFormat);

    _vsnprintf(szBuffer, sizeof(szBuffer), szFormat, pArgList);

    va_end(pArgList);

    OutputDebugString(szBuffer);

} // SysUtil::DebugMsg()

#endif


///////////////////////////////////////////////////////////////////////////////
// SysUtil::EnumResCallback()
///////////////////////////////////////////////////////////////////////////////

static BOOL CALLBACK EnumResCallback( HMODULE hExe,   // module handle
                                    LPCTSTR lpszType,  // resource type
                                    LPTSTR lpszName,   // resource name
                                    LPARAM lParam    // application-defined parameter
)
{
// #pragmas are used here to insure that the structure's
// packing in memory matches the packing of the EXE or DLL.
#pragma pack( push, 2 )
typedef struct
{
    BYTE    bWidth;               // Width, in pixels, of the image
    BYTE    bHeight;              // Height, in pixels, of the image
    BYTE    bColorCount;          // Number of colors in image (0 if >=8bpp)
    BYTE    bReserved;            // Reserved
    WORD    wPlanes;              // Color Planes
    WORD    wBitCount;            // Bits per pixel
    DWORD    dwBytesInRes;         // how many bytes in this resource?
    WORD    nID;                  // the ID
} GRPICONDIRENTRY, *LPGRPICONDIRENTRY;

typedef struct
{
    WORD            idReserved;   // Reserved (must be 0)
    WORD            idType;       // Resource type (1 for icons)
    WORD            idCount;      // How many images?
    GRPICONDIRENTRY    idEntries[1]; // The entries for each image
} GRPICONDIR, *LPGRPICONDIR;
#pragma pack( pop )


    HRSRC                hRsrc;
    HGLOBAL                hMem;
    DWORD                nDataLen;
    LPGRPICONDIR        pDirHeader;
    BYTE*                pData;
    unsigned int        k;
    char                szReqResName[6], szResName[6];

    sprintf(szResName, "%d", (int)lpszName);                // Convert requested ID into a string
    sprintf(szReqResName, "%d", (int)lParam);                // Convert requested ID into a string

    if (stricmp(szReqResName, szResName))
        return TRUE;                            // Not the right resource ID, get the next one

    hRsrc = FindResource(hExe, lpszName, RT_GROUP_ICON);
    hMem = LoadResource(hExe, hRsrc);
    pDirHeader = (LPGRPICONDIR)LockResource(hMem);

    for (k = 0; k < pDirHeader->idCount; k++)
    {
        hRsrc = FindResource(hExe, MAKEINTRESOURCE(pDirHeader->idEntries[k].nID), RT_ICON);
        hMem = LoadResource(hExe, hRsrc );

        nDataLen = SizeofResource( hExe, hRsrc );
        pData = (unsigned char *)LockResource(hMem);

        if (pDirHeader->idEntries[k].bWidth == g_IconFind_nWidth && pDirHeader->idEntries[k].bHeight == g_IconFind_nHeight &&
                pDirHeader->idEntries[k].wBitCount == g_IconFind_nDepth)
        {
            g_IconFind_hIcon = CreateIconFromResourceEx(pData, nDataLen, TRUE, 0x00030000, g_IconFind_nWidth, g_IconFind_nHeight, LR_DEFAULTCOLOR);
            break;                    // Stop the for loop
        }
    }

    return FALSE;                    // stop enumeration

} // SysUtil::EnumResCallback()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::LoadIcon()
//
// Same as LoadImage() for icons but allows you to specify a particular colour
// depth to return.  If the requested icon cannot be found the OS decides which
// icon to use - rarely what is wanted.
//
// Must call DestroyIcon on HICONs returned from this call
//
///////////////////////////////////////////////////////////////////////////////

HICON SysUtil::LoadIcon(int nIconID, int nWidth, int nHeight, int nDepth, HINSTANCE instance)
{
    // If a depth of -1 was specified then just do a usual LoadImage and let the OS decide the
    // best depth
    if (nDepth == -1)
        return (HICON)LoadImage(instance, MAKEINTRESOURCE(nIconID), IMAGE_ICON,
                nWidth, nHeight, LR_DEFAULTCOLOR);

    g_IconFind_hIcon = NULL;
    g_IconFind_nWidth = nWidth;
    g_IconFind_nHeight = nHeight;
    g_IconFind_nDepth = nDepth;

    EnumResourceNames(NULL, RT_GROUP_ICON, EnumResCallback, (LPARAM)nIconID);

    // Did we get a match?  If we didn't then just let the OS load any old icon
    if (g_IconFind_hIcon == NULL)
        return (HICON)LoadImage(instance, MAKEINTRESOURCE(nIconID), IMAGE_ICON,
                nWidth, nHeight, LR_DEFAULTCOLOR);
    else
        return g_IconFind_hIcon;

} // SysUtil::LoadIcon()


///////////////////////////////////////////////////////////////////////////////
// SysUtil::ConvSystemTime()
//
///////////////////////////////////////////////////////////////////////////////

bool SysUtil::ConvSystemTime(const char *szTime, SYSTEMTIME *st, bool bDate, int nSep)
{
    char        szTemp[4+1];

    // Set LOCAL date/time defaults
    GetLocalTime(st);

    // Must at least have a year in the time (or completely blank)
    if ((szTime[0] == '\0') || (strlen(szTime) < 4))
        return false;

    if (bDate)
    {    // convert date
        strncpy(szTemp, szTime, 4);
        szTemp[4] = '\0';
        st->wYear = (WORD)atoi(szTemp);
        szTime += 4+nSep;

        if (strlen(szTime) >= 2)
        {
            strncpy(szTemp, szTime, 2);
            szTemp[2] = '\0';
            st->wMonth = (WORD)atoi(szTemp);
            szTime += 2+nSep;

            if (strlen(szTime) >= 2)
            {
                strncpy(szTemp, szTime, 2);
                szTemp[2] = '\0';
                st->wDay = (WORD)atoi(szTemp);
                szTime += 2;
                if (strlen(szTime)>0)
                    szTime += nSep;
            }
        }
    }

    // convert time
    if (strlen(szTime) >= 2)
    {
        strncpy(szTemp, szTime, 2);
        szTemp[2] = '\0';
        st->wHour = (WORD)atoi(szTemp);
        szTime += 2+nSep;

        if (strlen(szTime) >= 2)
        {
            strncpy(szTemp, szTime, 2);
            szTemp[2] = '\0';
            st->wMinute = (WORD)atoi(szTemp);
            szTime += 2+nSep;

            if (strlen(szTime) >= 2)
            {
                strncpy(szTemp, szTime, 2);
                szTemp[2] = '\0';
                st->wSecond = (WORD)atoi(szTemp);
            }
        }
    }

    return true;

} // SysUtil::ConvSystemTime()

///////////////////////////////////////////////////////////////////////////////
// SysUtil::Shutdown()
// Shutdown or logoff the system
//
// Returns false if the function could not get the rights to shutdown
///////////////////////////////////////////////////////////////////////////////

static BOOL ShutdownHandler(HWND hwnd, DWORD lParam)
{
    HWND g_hWnd = (HWND)lParam;
    // if the window is me, don't terminate!
    if (g_hWnd != hwnd)
        g_oSysUtil.WinKill(hwnd);

    // Continue the enumeration.
    return TRUE;

} // ShutdownHandler()

BOOL SysUtil::Shutdown(int nFlag, HWND g_hWnd)
{

/*
flags can be a combination of:
#define EWX_LOGOFF           0
#define EWX_SHUTDOWN         0x00000001
#define EWX_REBOOT           0x00000002
#define EWX_FORCE            0x00000004
#define EWX_POWEROFF         0x00000008 */

    HANDLE                hToken;
    TOKEN_PRIVILEGES    tkp;

    // If we are running NT, make sure we have rights to shutdown
    if (g_oVersion.IsWinNT())
    {
        // Get a token for this process.
         if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return FALSE;                        // Don't have the rights

        // Get the LUID for the shutdown privilege.
         LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

        tkp.PrivilegeCount = 1;  /* one privilege to set */
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // Get the shutdown privilege for this process.
         AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        // Cannot test the return value of AdjustTokenPrivileges.
         if (GetLastError() != ERROR_SUCCESS)
            return FALSE;                        // Don't have the rights
    }

    // if we are forcing the issue, AND this is 95/98 terminate all windows first
    if ( (g_oVersion.IsWin9x()) && (nFlag & EWX_FORCE) )
    {
        nFlag ^= EWX_FORCE;    // remove this flag - not valid in 95
        ::EnumWindows((WNDENUMPROC) ShutdownHandler, (LPARAM)g_hWnd);
    }

    // for suspend and hibernate code
    if ( (nFlag == 32) || (nFlag == 64) )
        return SetSystemPowerState(  (nFlag == 32),  FALSE);

    // ExitWindows
    return ExitWindowsEx(nFlag, 0);

} // Engine::Shutdown()
