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
#include "Engine/Type/AString.h"
#include "Engine/Type/Variant.h"
#include "Engine/Type/VectorVariant.h"
#include "Engine/ScriptFile.h"
#include "Engine/Parser/Parser.h"

#include "Utils/OSVersion.h"
#include "Utils/SendKeys.h"
#include "Utils/SetForegroundWinEx.h"

// Possible states of the script
enum
{
    AUT_RUN, AUT_QUIT,
    AUT_SLEEP,

    AUT_WINWAIT,
    AUT_WINWAITCLOSE,
    AUT_WINWAITACTIVE,
    AUT_WINWAITNOTACTIVE,
    AUT_RUNWAIT,
    AUT_PROCESSWAIT,
    AUT_PROCESSWAITCLOSE,

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
class Engine;                            // Forward declaration of Engine

//typedef AUT_RESULT (Engine::*AU3_FUNCTION)(VectorVariant &vParams, Variant &vResult);
typedef AUT_RESULT (*FUNC_CALLER)(void* self, VectorVariant &vParams, Variant &vResult);

//typedef struct {
//    void* self;
//    const char* szModule;
//    const char* szName;
//    FUNC_CALLER lpFunc;
//    int nMin;
//    int nMax;
//} AU3_FuncType;

typedef struct
{
    void*           lpSelf;
    const char*     szModule;
    const char      *szName;                    // Function name
    FUNC_CALLER     lpFunc;                     // Pointer to function
    int             nMin;                       // Min params
    int             nMax;                       // Max params
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

typedef bool        (*HandleFunc)(void);


///////////////////////////////////////////////////////////////////////////////

class Lexer;
// The AutoIt Script object
class Engine
{
    friend class Lexer;
    friend class Parser;
public:
    // Variables

    // Functions
    Engine();                            // Constructor
    ~Engine();                            // Destrucutor

    void initModules(AU3_FuncInfo * funcList, int size);

    AUT_RESULT        InitScript(char *szFile);    // Perform setup of a loaded script
    int               ProcessMessages();
    AUT_RESULT        Execute(int nScriptLine=0);    // Run script at this line number
    int               GetCurLineNumber (void) const;

private:
    // Variables
    HS_SendKeys     m_oSendKeys;                // SendKeys object
    AString         m_sScriptName;                // Filename of script
    AString         m_sScriptFullPath;            // Full pathname of script
    AString         m_sScriptDir;                // Directory the script is in

    int             m_nExecuteRecursionLevel;    // Keeps track of the recursive calls of Execute()
    bool            m_bWinQuitProcessed;        // True when windows WM_QUIT message has been processed

    // Options (AutoItSetOption)
    int             m_nCoordMouseMode;            // Mouse position mode (screen or relative to active window)
    int             m_nCoordPixelMode;            // Pixel position mode (screen or relative to active window)
    int             m_nCoordCaretMode;
    bool            m_bRunErrorsFatal;            // Determines if "Run" function errors are fatal
    bool            m_bExpandEnvStrings;        // Determines if %Env% are expanded in strings
    bool            m_bExpandVarStrings;        // Determines if $Env$ @Env@ are expanded in strings
    bool            m_bMustDeclareVars;            // Must declare variables efore use
    bool            m_bColorModeBGR;            // True if using the old BGR (rather than RGB) colour mode
    AString         m_sOnExitFunc;                // Name of our OnExit function
    bool            m_bFtpBinaryMode;            // True if binary mode ftp is required

    // mouse
    int             m_nMouseClickDelay;            // Time between mouse clicks
    int             m_nMouseClickDownDelay;        // Time the click is held down
    int             m_nMouseClickDragDelay;        // The delay at the start and end of a drag operation

public:
    // TODO: these vars as modules option, can use format like json to save, not
    // depend on engine.
    // options setter getter
    inline int nCoordMouseMode() { return m_nCoordMouseMode; }
    inline void setCoordMouseMode(int mode) { m_nCoordMouseMode = mode; }

    inline int nCoordPixelMode() { return m_nCoordPixelMode; }
    inline void setCoordPixelMode(int mode) { m_nCoordPixelMode = mode; }

    inline int nCoordCaretMode() { return m_nCoordCaretMode; }
    inline void setCoordCaretMode(int mode) { m_nCoordCaretMode = mode; }

    inline bool bRunErrorsFatal() { return m_bRunErrorsFatal; }
    inline void setRunErrorsFatal(bool opt) { m_bRunErrorsFatal = opt; }

    inline bool bExpandEnvStrings() { return m_bExpandEnvStrings; }
    inline void setExpandEnvStrings(bool opt) { m_bExpandEnvStrings = opt; }

    inline bool bExpandVarStrings() { return m_bExpandVarStrings; }
    inline void setExpandVarStrings(bool opt) { m_bExpandVarStrings = opt; }

    inline bool bMustDeclareVars() { return m_bMustDeclareVars; }
    inline void setMustDeclareVars(bool opt) { m_bMustDeclareVars = opt; }

    inline bool bColorModeBGR() { return m_bColorModeBGR; }
    inline void setColorModeBGR(bool opt) {m_bColorModeBGR = opt; }

    inline AString sOnExitFunc() { return m_sOnExitFunc; }
    inline void setOnExitFunc(const AString &func) { m_sOnExitFunc = func; }

    inline bool bFtpBinaryMode() { return m_bFtpBinaryMode; }
    inline void setFtpBinaryMode(bool opt) { m_bFtpBinaryMode = opt; } 

    int nMouseClickDelay() { return m_nMouseClickDelay; }
    void setMouseClickDelay(int opt) { m_nMouseClickDelay = opt; }

    int nMouseClickDownDelay() { return m_nMouseClickDownDelay; }
    void setMouseClickDownDelay(int opt) { m_nMouseClickDownDelay = opt; }

    int nMouseClickDragDelay() { return m_nMouseClickDragDelay; }
    void setMouseClickDragDelay(int opt) { m_nMouseClickDragDelay = opt; }

private:
    // Net download details
    InetGetDetails  m_InetGetDetails;

    bool            m_bUserFuncReturned;        // Becomes true when userfunctions end (return or endfunc)


    // Plugin variables
    //PluginFuncs        *m_PluginFuncs;                // Linked list of plugin functions

    // DLL variables
    HINSTANCE            m_DLLHandleDetails[AUT_MAXOPENFILES];

    // module register function list
    AU3_FuncInfo       *m_FuncList;                // List of functions and details for each
    int                m_nFuncListSize;            // Number of functions

    int                m_nWindowSearchMatchMode;    // Window title substring match mode
    int                m_nWindowSearchTextMode;    // Window title substring match mode

    bool            m_bDetectHiddenText;        // Detect hidden window text in window searches?
    bool            m_bWinSearchChildren;        // Search just top level windows or children too?

    int                m_nWinWaitDelay;            // 500 = default (wait this long after a window is matched)

    // ADLIB related vars
    AString         m_sAdlibFuncName;            // The name of the current adlib function
    bool            m_bAdlibEnabled;            // True if an adlib function is specified
    bool            m_bAdlibInProgress;            // True if we are currently running adlib function
    DWORD           m_tAdlibTimerStarted;        // Time in millis that timer was started
    DWORD           m_nAdlibTimeout;            // Time (ms) left before timeout (0=no timeout)


    // GUI related vars
    bool            m_bGuiEventInProgress;        // True if we are currently GUI event function


    // WinList() structs and vars

    HandleFunc _handleAdlib;
    HandleFunc _handleHotkey;
    HandleFunc _handleGuiEvent;

public:
    int nWindowSearchMatchMode() { return m_nWindowSearchMatchMode; }
    void setWindowSearchMatchMode(int mode) { m_nWindowSearchMatchMode = mode; }

    int nWindowSearchTextMode() { return m_nWindowSearchTextMode; }
    void setWindowSearchTextMode(int mode) { m_nWindowSearchTextMode = mode; }

    bool bDetectHiddenText() { return m_bDetectHiddenText; }
    void setDetectHiddenText(bool opt) { m_bDetectHiddenText = opt; }

    int nWinWaitDelay() { return m_nWinWaitDelay; }
    void setWinWaitDelay(int opt) { m_nWinWaitDelay = opt; }

    bool bWinSearchChildren() { return m_bWinSearchChildren; }
    void setWinSearchChildren(bool opt) { m_bWinSearchChildren = opt; }

    AString sAdlibFuncName() { return m_sAdlibFuncName; }
    void setAdlibFuncName(const AString &name) { m_sAdlibFuncName = name; }

    DWORD tAdlibTimerStarted() { return m_tAdlibTimerStarted; }
    void setAdlibTimerStarted(DWORD val) { m_tAdlibTimerStarted = val; }

    bool bAdlibEnabled() { return m_bAdlibEnabled; }
    void setAdlibEnabled(bool opt) { m_bAdlibEnabled = opt; }

    DWORD nAdlibTimeout() { return m_nAdlibTimeout; }
    void setAdlibTimeout(DWORD timeout) { m_nAdlibTimeout = timeout; }

private:
    Parser*     _parser;
    Lexer*      _lexer;

public:
    inline Parser* parser() { return _parser; }
    void quit();

    HS_SendKeys& oSendKeys() { return m_oSendKeys; }

    AUT_RESULT AssignVar(const char* szName, Variant &vValue, int nReqScope, bool bCreate, Variant &vResult);

public:
    // === export engine function ===
    // Assign variable
    inline bool Assign(const AString &sVarName, const Variant &vVariant, bool bConst = false, int nReqScope = VARTABLE_ANY)
    { return _parser->m_oVarTable.Assign(sVarName, vVariant, bConst, nReqScope); }
    // Get pointer to a variable
    inline bool GetRef(const AString &sVarName, Variant **pvVariant, bool &bConst, int nReqScope = VARTABLE_ANY)
    { return _parser->m_oVarTable.GetRef(sVarName, pvVariant, bConst, nReqScope); }

    // Return true if the reference variable exists (and type of variable, global/local etc)
    inline int isDeclared(const AString &sVarName)
    { return _parser->m_oVarTable.isDeclared(sVarName); }

    inline void SetFuncErrorCode(int nCode)
    { return _parser->SetFuncErrorCode(nCode); }

public:

    //bool        HandleDelayedFunctions(void);                        // Handle delayed commands

    int         processEvents(void);

    void setHandleAdlib(HandleFunc func) { _handleAdlib = func; }
    void sethandleHotkey(HandleFunc func) { _handleHotkey = func; }
    void setHandleGuiEvent(HandleFunc func) { _handleGuiEvent = func; }

public:
    // Global data
    HINSTANCE               g_hInstance;            // Main application instance
    
    HWND                    g_hWnd;                 // Main window handle
    HWND                    g_hWndEdit;             // Main window edit control handle
    HWND                    g_hWndProgress;         // Progress window handle
    HWND                    g_hWndProgBar;          // Progress progressbar control handle
    HWND                    g_hWndProgLblA;         // Progress Top label control handle
    HWND                    g_hWndProgLblB;         // Progress Bottom label control handle
    
    HWND                    g_hWndSplash;           // Splash window handle
    HBITMAP                 g_hSplashBitmap;        // Splash window bitmap

    #ifdef AUT_CONFIG_GUI                           // Is GUI enabled?
    CGuiBox                 g_oGUI;                 // GUI object
    #endif
    
    int                     g_nExitCode;            // Windows exit code
    int                     g_nExitMethod;          // The way AutoIt finished
    
    OS_Version              g_oVersion;             // Version object
    
    //AutoIt_App            g_oApplication;         // Main application object
    //AutoIt_Script         g_oScript;              // The scripting engine object
    
    SetForegroundWinEx      g_oSetForeWinEx;        // Foreground window hack object
    
    ScriptFile              g_oScriptFile;          // The script file object
    
    
    // Script/main window comms
    bool                    g_bScriptPaused;        // True when script is paused
    bool                    g_bBreakEnabled;        // True when user is allowed to quit script
    bool                    g_bTrayIcon;            // True when tray icon is displayed
    bool                    g_bTrayIconInitial;     // Initial state of tray icon
    bool                    g_bTrayIconDebug;       // True when TrayIcon debugng is allowed
    bool                    g_bStdOut;              // True when /ErrorStdOut used on the command line
    bool                    g_bTrayExitClicked;     // True when the user clicks "exit"
    bool                    g_bKillWorkerThreads;   // True when requesting all thread finish up (script is about to die)
    
    WPARAM                  g_HotKeyQueue[AUT_HOTKEYQUEUESIZE];    // Queue for hotkeys pressed
    int                     g_HotKeyNext;           // Next free hotkey position in queue
};

///////////////////////////////////////////////////////////////////////////////
