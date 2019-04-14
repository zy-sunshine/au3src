#pragma once
///////////////////////////////////////////////////////////////////////////////
//
// AutoIt v3
//
// Copyright (C)1999-2005:
//        - Jonathan Bennett <jon at hiddensoft dot com>
//        - See "AUTHORS.txt" for contributors.
//
// This file is part of AutoIt.
//
// AutoIt source code is copyrighted software distributed under the terms of the
// AutoIt source code license.
//
// You may:
//
// - Customize the design and operation of the AutoIt source code to suit
// the internal needs of your organization except to the extent not
// permitted in this Agreement
//
// You may not:
//
// - Distribute the AutoIt source code and/or compiled versions of AutoIt
// created with the AutoIt source code.
// - Create derivative works based on the AutoIt source code for distribution
// or usage outside your organisation.
// - Modify and/or remove any copyright notices or labels included in the
// AutoIt source code.
//
// AutoIt is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// See the LICENSE.txt file that accompanies the AutoIt source
// code for more details.
//
///////////////////////////////////////////////////////////////////////////////
//
// script.h
//
// The main script object.
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <wininet.h>
#endif

#include "AutoIt.h"
#include "variant_datatype.h"
#include "token_datatype.h"
#include "vector_variant_datatype.h"
#include "vector_token_datatype.h"
#include "stack_statement_datatype.h"
#include "stack_int_datatype.h"
#include "stack_variant_datatype.h"
#include "variabletable.h"
#include "os_version.h"
#include "sendkeys.h"
#include "userfunction_list.h"
#include "regexp.h"


// Possible states of the script
enum
{
    AUT_RUN, AUT_QUIT,
    AUT_SLEEP,
    AUT_WINWAIT, AUT_WINWAITCLOSE,
    AUT_WINWAITACTIVE, AUT_WINWAITNOTACTIVE,
    AUT_RUNWAIT,
    AUT_PROCESSWAIT, AUT_PROCESSWAITCLOSE,
    AUT_INETGET,
    AUT_PAUSED                                    // Not actually used except for a ProcessMessages() return value
};


// Possible exit methods
enum { AUT_EXITBY_NATURAL, AUT_EXITBY_EXITKEYWORD, AUT_EXITBY_TRAY };

// ControlSearch methods
enum { AUT_CONTROLSEARCH_CLASS, AUT_CONTROLSEARCH_TEXT, AUT_CONTROLSEARCH_ID };


#ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
// Possible Gui controls
enum
{
    AUT_GUI_COMBO=0,
    AUT_GUI_LIST=1,

    AUT_GUI_EDIT=2,
    AUT_GUI_INPUT=3,
    AUT_GUI_GROUP=4,
    AUT_GUI_DATE=5,
    AUT_GUI_PIC=6,
    AUT_GUI_ICON=7,
    AUT_GUI_PROGRESS=8,
    AUT_GUI_AVI=9,
    AUT_GUI_TAB=10,
    AUT_GUI_TABITEM=11,
    AUT_GUI_CONTEXTMENU=12,
    AUT_GUI_TRAYMENU=13,
    AUT_GUI_MENU=14,
    AUT_GUI_MENUITEM=15,
    AUT_GUI_TREEVIEW=16,
    AUT_GUI_TREEVIEWITEM=17,
    AUT_GUI_SLIDER=18,
    AUT_GUI_LISTVIEW=19,
    AUT_GUI_LISTVIEWITEM=20,
    AUT_GUI_DUMMY=21,
    AUT_GUI_UPDOWN=22,
    AUT_GUI_LABEL=23,
    AUT_GUI_BUTTON=24,
    AUT_GUI_CHECKBOX=25,
    AUT_GUI_RADIO=26,

    // subtype to suppress action during the creation by CtrlCreate
    AUT_GUI_NOFONT = 1,
    AUT_GUI_NORESIZE = 2,
    AUT_GUI_NOTEXTSIZE = 4
};
#endif


// Keyword values (must match the order as in script.cpp)
enum
{
    K_AND = 0, K_OR, K_NOT,
    K_IF, K_THEN, K_ELSE, K_ELSEIF, K_ENDIF,
    K_WHILE, K_WEND,
    K_DO, K_UNTIL,
    K_FOR, K_NEXT, K_TO, K_STEP,
    K_EXITLOOP, K_CONTINUELOOP,
    K_SELECT, K_CASE, K_ENDSELECT,
    K_DIM, K_REDIM, K_LOCAL, K_GLOBAL, K_CONST,
    K_FUNC, K_ENDFUNC, K_RETURN,
    K_EXIT,
    K_BYREF,
    K_MAX
};


enum
{
    OPR_LESS,                                    // <
    OPR_GTR,                                    // >
    OPR_LESSEQUAL,                                // <=
    OPR_GTREQUAL,                                // >=
    OPR_NOTEQUAL,                                // NotEqual comparision
    OPR_EQUAL,                                    // = Equals comparison (case insensitive with strings)
    OPR_STRINGEQUAL,                            // == Equals comparison (case sensitive with strings)
    OPR_LOGAND,                                    // Logcial AND (keyword for conditions)
    OPR_LOGOR,                                    // Logical OR (keyword for conditions)
    OPR_CONCAT,                                    // &
    OPR_NOT,                                    // Unary NOT
    OPR_ADD,                                    // +
    OPR_SUB,                                    // -
    OPR_MUL,                                    // *
    OPR_DIV,                                    // /
    OPR_POW,                                    // ^
    OPR_UMI,                                    // Unary minus ( 4--3, etc)
    OPR_UPL,                                    // Unary plus
    OPR_LPR,                                    // (
    OPR_RPR,                                    // )
    OPR_END,                                    // $ (End)
    OPR_MAXOPR,                                    // Number of operators (used for array sizing)
    OPR_VAL,                                    // Value
    OPR_NULL                                    // Dummy value, used in parsing expression routine
};


// Coordinate modes (pixel, caret, mouse functions)
#define AUT_COORDMODE_WINDOW    0                // Relative to active window
#define AUT_COORDMODE_SCREEN    1                // Relative to the screen
#define AUT_COORDMODE_CLIENT    2                // Relative to active window's CLIENT area


// Structure for storing file handles for the File functions
#define AUT_MAXOPENFILES    64

// FileOpen/FileFind handles
enum { AUT_FILEOPEN, AUT_FILEFIND};
typedef struct
{
    int            nType;                            // Type of entry stored (fileopen, or filefind)

    // File Open
    FILE        *fptr;                            // File handle
    int            nMode;                            // Mode the file was opened in (0=read, 1=write)

    // File Find
    HANDLE        hFind;                            // Find handle
    char        *szFind;                        // First search result (or NULL on 2nd, 3rd, etc)

} FileHandleDetails;

// Structure for storing hotkeys
#define AUT_MAXHOTKEYS        64                    // Maximum number of hotkeys
typedef struct
{
    WPARAM    wParam;                                // Hotkey ID
    LPARAM    lParam;                                // Key and modifiers (control, alt, etc)
    AString    sFunction;                            // Function to call

} HotKeyDetails;


// Regular Expressions info
#define AUT_MAXREGEXPS        8                    // Size of regular expression cache


// Function lookup structures
class AutoIt_Script;                            // Forward declaration of AutoIt_Script

typedef AUT_RESULT (AutoIt_Script::*AU3_FUNCTION)(VectorVariant &vParams, Variant &vResult);

typedef struct
{
    const char      *szName;                    // Function name
    AU3_FUNCTION    lpFunc;                        // Pointer to function
    int             nMin;                        // Min params
    int             nMax;                        // Max params
} AU3_FuncInfo;


/*
// Plugin lookup structures
typedef struct _PluginFuncs
{
    HINSTANCE            hDll;                    // Handle of the loaded DLL
    char                *szFuncName;            // Name of the function
    struct _PluginFuncs    *lpNext;                // Next entry, or NULL for last entry
} PluginFuncs;
*/


// Proxy stuff
#define AUT_PROXY_REGISTRY    0
#define AUT_PROXY_DIRECT    1
#define AUT_PROXY_PROXY        2


// Lexer caching
// Assuming an average of 7 tokens per line at 256 bytes per line
// 256 lines of buffer = 64KB.
#define AUT_LEXER_CACHESIZE    256                    // Must be power of 2
#define AUT_LEXER_CACHEMASK    255                    // size - 1
typedef struct
{
    int            nLineNum;                        // Line cached here (or -1)
    VectorToken    vLine;                            // Cached line of tokens
} LexerCache;


// InetGet handles
typedef struct
{
//    HANDLE        hThread;                        // Handle to the internet worker thread
    bool        bInProgress;
    int            nBytesRead;
    HINTERNET    hInet, hConnect, hFile;
    FILE        *fptr;
    DWORD        dwService;
    bool        bRequestAbort;
} InetGetDetails;


// List structure for the WinGetList function
typedef struct _WinListNode
{
    HWND    hWnd;
    struct _WinListNode    *lpNext;                // next node (or NULL)
} WinListNode;


///////////////////////////////////////////////////////////////////////////////


// The AutoIt Script object
class AutoIt_Script
{
public:
    // Variables

    // Functions
    AutoIt_Script();                            // Constructor
    ~AutoIt_Script();                            // Destrucutor

    AUT_RESULT        InitScript(char *szFile);    // Perform setup of a loaded script
    int                ProcessMessages();
//    AUT_RESULT        Execute(int nScriptLine=0);    // Run script at this line number
    int             GetCurLineNumber (void) const { return m_nErrorLine; }  // Return current line number for TrayTip debugging

private:

    // Variables
    HS_SendKeys        m_oSendKeys;                // SendKeys object
    AString            m_sScriptName;                // Filename of script
    AString            m_sScriptFullPath;            // Full pathname of script
    AString            m_sScriptDir;                // Directory the script is in

    HWND            m_hWndTip;                    // ToolTip window

    int                m_nExecuteRecursionLevel;    // Keeps track of the recursive calls of Execute()
    int                m_nErrorLine;                // Line number used to generate error messages
    int                m_nCurrentOperation;        // The current state of the script (RUN, WAIT, SLEEP, etc)
    bool            m_bWinQuitProcessed;        // True when windows WM_QUIT message has been processed

    // Options (AutoItSetOption)
    int                m_nCoordMouseMode;            // Mouse position mode (screen or relative to active window)
    int                m_nCoordPixelMode;            // Pixel position mode (screen or relative to active window)
    int                m_nCoordCaretMode;
    bool            m_bRunErrorsFatal;            // Determines if "Run" function errors are fatal
    bool            m_bExpandEnvStrings;        // Determines if %Env% are expanded in strings
    bool            m_bExpandVarStrings;        // Determines if $Env$ @Env@ are expanded in strings
    bool            m_bMustDeclareVars;            // Must declare variables efore use
    int                m_nMouseClickDelay;            // Time between mouse clicks
    int                m_nMouseClickDownDelay;        // Time the click is held down
    int                m_nMouseClickDragDelay;        // The delay at the start and end of a drag operation
    bool            m_bColorModeBGR;            // True if using the old BGR (rather than RGB) colour mode
    AString            m_sOnExitFunc;                // Name of our OnExit function
    bool            m_bFtpBinaryMode;            // True if binary mode ftp is required

    // Proxy Settings
    int                m_nHttpProxyMode;
    AString            m_sHttpProxy;
    AString            m_sHttpProxyUser;
    AString            m_sHttpProxyPwd;
    int                m_nFtpProxyMode;
    AString            m_sFtpProxy;
    AString            m_sFtpProxyUser;
    AString            m_sFtpProxyPwd;

    // Net download details
    InetGetDetails    m_InetGetDetails;


    // User functions variables
    UserFuncList    m_oUserFuncList;            // Details (line numbers, num params) for user defined functions
    Variant            m_vUserRetVal;                // Temp storage for return value of a user function (or winwait result)
    bool            m_bUserFuncReturned;        // Becomes true when userfunctions end (return or endfunc)
    int                m_nFuncErrorCode;            // Extended error code
    int                m_nFuncExtCode;                // Extended code
    int                m_nNumParams;                // Number of parameters when calling a user function


    // Plugin variables
    //PluginFuncs        *m_PluginFuncs;                // Linked list of plugin functions

    // Statement stacks
    StackStatement    m_StatementStack;            // Stack for tracking If/Func/Select/Loop statements


    // File variables
    int                    m_nNumFileHandles;                        // Number of file handles in use
    FileHandleDetails    *m_FileHandleDetails[AUT_MAXOPENFILES];    // Array contains file handles for File functions

    // DLL variables
    HINSTANCE            m_DLLHandleDetails[AUT_MAXOPENFILES];

    // HotKey stuff
    HotKeyDetails    *m_HotKeyDetails[AUT_MAXHOTKEYS];    // Array for tracking hotkey details
    int                m_nHotKeyQueuePos;                    // Position in the global hotkey queue


    // Lexing and parsing vars
#ifdef AUT_CONFIG_LEXERCACHE
    LexerCache         m_LexerCache[AUT_LEXER_CACHESIZE];
#endif
    static char        m_PrecOpRules[OPR_MAXOPR][OPR_MAXOPR];    // Table for precedence rules
    static const char  *m_szKeywords[];            // Valid keywords
    static const char  *m_szMacros[];                // Valid functions
    AU3_FuncInfo       *m_FuncList;                // List of functions and details for each
    int                m_nFuncListSize;            // Number of functions

    // Window related vars
    Variant            m_vWindowSearchTitle;        // Title/text used for win searches
    Variant            m_vWindowSearchText;        // Title/text used for win searches
//    bool            m_bWinSearchFoundFlag;        // Temp var used in Window searches
    HWND               m_WindowSearchHWND;            // Temp var used in Window searches
    int                m_nWindowSearchMatchMode;    // Window title substring match mode
    int                m_nWindowSearchTextMode;    // Window title substring match mode
    WinListNode        *m_lpWinListFirst;            // First entry in window list
    WinListNode        *m_lpWinListLast;            // First entry in window list
    int                m_nWinListCount;            // Number of entries
    bool            m_bDetectHiddenText;        // Detect hidden window text in window searches?
    bool            m_bWinSearchChildren;        // Search just top level windows or children too?
    bool            m_bWindowSearchFirstOnly;    // When true will only find the first matching window (otherwise all)

    DWORD            m_nWinWaitTimeout;            // Time (ms) left before timeout (0=no timeout)
    int                m_nWinWaitDelay;            // 500 = default (wait this long after a window is matched)
    DWORD            m_tWinTimerStarted;            // Time in millis that timer was started

    int                m_nControlSearchMethod;        // Temp variable used in the search functions
    Variant            m_vControlSearchValue;        // The ID, classname or text to search for
    uint            m_iControlSearchInstance;    // Variable to keep track of class instance during search
    bool            m_bControlSearchFoundFlag;    // Temp variable used in the search functions
    HWND            m_ControlSearchHWND;        // Contains HWND of a successful control search


    // Process related vars
    AString            m_sProcessSearchTitle;        // Name of process to wait for
    DWORD            m_nProcessWaitTimeout;        // Time (ms) left before timeout (0=no timeout)
    DWORD            m_tProcessTimerStarted;        // Time in millis that timer was started
    HANDLE            m_piRunProcess;                // Used in RunWait command

    bool            m_bRunAsSet;                // Flag if we want to use RunAs user/password in the Run function
    DWORD            m_dwRunAsLogonFlags;        // RunAs logon flags
    wchar_t            *m_wszRunUser;                // User name for RunAs (wide char)
    wchar_t            *m_wszRunDom;                // Domain name for RunAs (wide char)
    wchar_t            *m_wszRunPwd;                // Password for RunAs (wide char)


    // ADLIB related vars
    AString            m_sAdlibFuncName;            // The name of the current adlib function
    bool            m_bAdlibEnabled;            // True if an adlib function is specified
    bool            m_bAdlibInProgress;            // True if we are currently running adlib function
    DWORD            m_tAdlibTimerStarted;        // Time in millis that timer was started
    DWORD            m_nAdlibTimeout;            // Time (ms) left before timeout (0=no timeout)


    // GUI related vars
    bool            m_bGuiEventInProgress;        // True if we are currently GUI event function


    // WinList() structs and vars


    // Functions
    void        SaveExecute(int nScriptLine, bool bRaiseScope, bool bRestoreErrorCode);        // Save state and then Execute()
    void        FatalError(int iErr, int nCol = -1);                // Output an error and signal quit (String resource errors)
    void        FatalError(int iErr, const char *szText2);            // Output an error and signal quit (passed text errors)
    const char * FormatWinError(DWORD dwCode = 0xffffffff);            // Gets the string output for a Windows error code

    void        SetFuncErrorCode(int nCode)
                    {m_nFuncErrorCode = nCode;};                    // Set script error info (@error code)
    void        SetFuncExtCode(int nCode)
                    {m_nFuncExtCode = nCode;};                        // Set script extended info (@extended code)

    AUT_RESULT    StoreUserFuncs(void);                                // Get all user function details
    AUT_RESULT    StoreUserFuncs2(VectorToken &LineTokens, uint &ivPos, const AString &sFuncName, int &nScriptLine);
    AUT_RESULT    StoreUserFuncsFindEnd(int &nScriptLine);            // Finds a matching endfunc during the StoreUserFuncs functions
    AUT_RESULT    VerifyUserFuncCalls(void);                            // Ensures user function calls are defined

    AUT_RESULT    StorePluginFuncs(void);                                // Get all plugin function details

    bool        HandleDelayedFunctions(void);                        // Handle delayed commands
    bool        HandleAdlib(void);
    bool        HandleHotKey(void);
    bool        HandleGuiEvent(void);
};

///////////////////////////////////////////////////////////////////////////////
