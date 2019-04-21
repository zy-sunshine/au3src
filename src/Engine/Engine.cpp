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
// script.cpp
//
// The main script object.
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"                                // Pre-compiled headers
#include "Engine.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <limits.h>
#else
//    #include "qmath.h"                            // MinGW doesn't like our asm maths functions
#endif

#include "Utils/utility.h"
#include "Utils/StrUtil.h"


///////////////////////////////////////////////////////////////////////////////
// Initialize static data variables
//
// Note: the order of these keywords is critical and needs to match the order
// in script.h
//
///////////////////////////////////////////////////////////////////////////////

// Keyword values (must match the order as in script.cpp)
// Must be in UPPERCASE
const char * Engine::m_szKeywords[K_MAX] =    {
    "AND", "OR", "NOT",
    "IF", "THEN", "ELSE", "ELSEIF", "ENDIF",
    "WHILE", "WEND",
    "DO", "UNTIL",
    "FOR", "NEXT", "TO", "STEP",
    "EXITLOOP", "CONTINUELOOP",
    "SELECT", "CASE", "ENDSELECT",
    "DIM", "REDIM", "LOCAL", "GLOBAL", "CONST",
    "FUNC", "ENDFUNC", "RETURN",
    "EXIT",
    "BYREF"
};


///////////////////////////////////////////////////////////////////////////////
// Constructor()
///////////////////////////////////////////////////////////////////////////////

Engine::Engine()
{
    int i;

    // Store initial values and zero important variables (the splash and progress functions
    // in particular rely on these being NULL to work out their status)
    g_hWnd                = NULL;                    // Main window
    g_hWndEdit            = NULL;                    // Edit window
    g_hWndSplash        = NULL;                    // Splash window handle
    g_hSplashBitmap        = NULL;                    // Splash window bitmap
    g_hWndProgress        = NULL;                    // Progress window handle
    g_hWndProgBar        = NULL;                    // Progress progressbar control handle
    g_hWndProgLblA        = NULL;                    // Progress Top label control handle
    g_hWndProgLblB        = NULL;                    // Progress Bottom label control handle
    g_bTrayIcon            = false;                // Icon not initially visible
    g_bTrayIconInitial    = true;                    // Usually we want the tray icon to be displayed at start
    // Script/win communication defaults
    g_bScriptPaused            = false;
    g_bBreakEnabled            = true;
    g_bTrayIconDebug        = false;
    g_bStdOut                = false;
    g_bTrayExitClicked        = false;
    g_bKillWorkerThreads    = false;
    g_HotKeyNext        = 0;                    // Initial position in hot key buffer

    m_bWinQuitProcessed            = false;

    m_nCurrentOperation            = AUT_RUN;        // Current operation is to run the script
    m_nExecuteRecursionLevel    = 0;            // Reset our recursion tracker for the Execute() function

    m_nErrorLine                = 0;            // Set last line read as 0 by default (application.cpp may try reading it)
    m_nNumParams                = 0;            // Number of UDF parameters initially 0
    
    m_nCoordMouseMode            = AUT_COORDMODE_SCREEN;        // Mouse functions use screen coords by default
    m_nCoordPixelMode            = AUT_COORDMODE_SCREEN;        // Pixel functions use screen coords by default
    m_nCoordCaretMode            = AUT_COORDMODE_SCREEN;
    m_bRunErrorsFatal            = true;            // Run errors are fatal by default
    m_bExpandEnvStrings            = false;        // ENV expansion in strings is off by default
    m_bExpandVarStrings            = false;        // Var expansion in strings is off by default
    m_bMustDeclareVars            = false;        // Variables must be pre-declared
    m_bColorModeBGR                = false;        // Use RGB colours by default
    m_sOnExitFunc                = "OnAutoItExit";
    m_bFtpBinaryMode            = true;            // Use binary ftp transfers by default

    m_nWinWaitDelay                = 250;            // Wait 250 ms after a window wait operation

    m_nWindowSearchMatchMode    = 1;           // Title match mode default is 1
    m_nWindowSearchTextMode     = 1;           // Text match mode default is 1

    m_bAdlibEnabled                = false;        // True if an adlib function is specified
    m_bAdlibInProgress            = false;        // True if we are currently running adlib function

    m_bGuiEventInProgress        = false;        // True if we are currently running event function

    m_nMouseClickDelay            = 10;            // Time between mouse clicks
    m_nMouseClickDownDelay        = 10;            // Time the click is held down
    m_nMouseClickDragDelay        = 250;            // The delay at the start and end of a drag operation

    m_oSendKeys.Init();                            // Init sendkeys to defaults

    // Make sure our lexer cache is set to empty defaults
    for (i=0; i<AUT_LEXER_CACHESIZE; ++i)
        m_LexerCache[i].nLineNum = -1;
    
    // Initialise file handles to NULL
    m_nNumFileHandles = 0;                        // Initalise file handle count
    for (i=0; i<AUT_MAXOPENFILES; ++i)
        m_FileHandleDetails[i] = NULL;

    // Initialise DLL handles to NULL
    for (i=0; i<AUT_MAXOPENFILES; ++i)
        m_DLLHandleDetails[i] = NULL;
    
    // Internet download/upload defaults
    m_InetGetDetails.bInProgress    = false;
    m_InetGetDetails.nBytesRead        = -1;

    paser = new Parser();
} // Engine()

static int funcNameSort(AU3_FuncInfo *a0,  AU3_FuncInfo *a1)
{
    return strcmp(a->szName, b->szName);
}

void Engine::initModules(BaseModule *modules, int size)
{
    // Initialize the function list (very long - thank VC6 for being buggy)
    // Functon names to be in UPPERCASE and in ALPHABETICAL ORDER (Use the TextPad sort function or similar)
    // Failure to observe these instructions will be very bad...
    AU3_FuncInfo *info;
    unsigned j;

    m_nFuncListSize  = 0;
    for (unsigned idx=0; idx < size; idx++) {
        info = modules[idx]->funcInfo();
        j = 0;
        while (info) {
            if (!info->szName) { break; }
            m_nFuncListSize++;
            info = modules[idx]->funcInfo() + (++j);
        }
    }

    // Copy the function list into a member variable
    m_FuncList = new AU3_FuncInfo[m_nFuncListSize];
    unsigned funcIdx = 0;
    for (unsigned idx=0; idx < size; idx++) {
        info = modules[idx]->funcInfo();
        j = 0;
        while (info) {
            if (!info->szName) { break; }
            m_FuncList[funcIdx].szName = Util_StrCpyAlloc(info->szName);
            m_FuncList[funcIdx].lpFunc = info->lpFunc;
            m_FuncList[funcIdx].nMin = info->nMin;
            m_FuncList[funcIdx].nMax = info->nMax;
            m_FuncList[funcIdx].lpSelf = (void*)modules[idx];
            m_FuncList[funcIdx].lpCaller = modules[idx]->funcCaller();
            funcIdx++;
            info = modules[idx]->funcInfo() + (++j);
        }
    }

    Sort(m_FuncList, funcNameSort);

    for (i=0; i<m_nFuncListSize; ++i) 
    {
    }

// NOTE: because Lexer search function use binary search, enable these code now
//      but why not sort these function firstly, speed?
//#ifdef _DEBUG
        // test to make sure that the list is in order, but only during development
        if (i>0 && strcmp(m_FuncList[i-1].szName, m_FuncList[i].szName) > 0)    // out of sequence
        {
            // display out of order name before aborting.
            AUT_DEBUGMESSAGEBOX(m_FuncList[i].szName);
            AUT_ASSERT(strcmp(m_FuncList[i-1].szName, m_FuncList[i].szName) < 0);
        }
//#endif
}

///////////////////////////////////////////////////////////////////////////////
// Destructor()
///////////////////////////////////////////////////////////////////////////////

Engine::~Engine()
{
    int i;

    // Free up any thing

    // close SoundPlay handle
//    char    szBuffer[256] = "";
//    mciSendString("status PlayMe mode",szBuffer,sizeof(szBuffer),NULL);
//    if ( !szBuffer[0]=='\0' )
//        mciSendString("close PlayMe",NULL,0,NULL);
// NOTE: The above code was causing hanging in rare cases when SoundPlay wasn't even used
    mciSendString("close all", NULL, 0, NULL);

    // Close any file handles that script writer has not closed (naughty!)
    for (i=0; i<AUT_MAXOPENFILES; ++i)
    {
        if (m_FileHandleDetails[i] != NULL)
        {
            if (m_FileHandleDetails[i]->nType == AUT_FILEOPEN)
            {
                fclose(m_FileHandleDetails[i]->fptr);    // Close file
            }
            else
            {
                FindClose(m_FileHandleDetails[i]->hFind);
                delete [] m_FileHandleDetails[i]->szFind;
            }

            delete m_FileHandleDetails[i];            // Delete memory
        }
    }

    // Close any dll handles that script writer has not closed (naughty!)
    for (i=0; i<AUT_MAXOPENFILES; ++i)
    {
        if (m_DLLHandleDetails[i] != NULL)
            FreeLibrary(m_DLLHandleDetails[i]);
    }

    // Free up memory used in our function list
    for (i=0; i<m_nFuncListSize; ++i) 
        delete [] m_FuncList[i].szName;                // Free allocated string

    delete [] m_FuncList;                            // Delete the entire list

}


///////////////////////////////////////////////////////////////////////////////
// FatalError()
//
// This function will print a message box giving the line and line number
// of any script stopping errors, it will also set the flag that makes the
// script quit.
//
// The line used to print the error is the last one stored in m_nErrorLine,
// if the column number is < zero, this is also used in the error message
///////////////////////////////////////////////////////////////////////////////

void Engine::FatalError(int iErr, int nCol)
{
    char        szTitle[AUT_MAX_LINESIZE];
    char        szText[AUT_MAX_LINESIZE];
    char        szOutput[AUT_MAX_LINESIZE*3];
    char        szOutput2[AUT_MAX_LINESIZE*3];

    LoadString(g_hInstance, IDS_AUT_E_TITLE, szTitle, AUT_MAX_LINESIZE);
    LoadString(g_hInstance, iErr, szText, AUT_MAX_LINESIZE);

    // Get the line and include file
    const char *szScriptLine = g_oScriptFile.GetLine(m_nErrorLine);
    int nAutScriptLine = g_oScriptFile.GetAutLineNumber(m_nErrorLine);
    int nIncludeID = g_oScriptFile.GetIncludeID(m_nErrorLine);
    const char *szInclude = g_oScriptFile.GetIncludeName(nIncludeID);

    if (szInclude == NULL)
        sprintf(szOutput, "Line %d:\n\n", nAutScriptLine);
    else
        sprintf(szOutput, "Line %d  (File \"%s\"):\n\n", nAutScriptLine, szInclude);

    strcat(szOutput, szScriptLine);
    strcat(szOutput, "\n");

    if (nCol >= 0)
    {
        strcpy(szOutput2, szScriptLine);
        szOutput2[nCol] = '\0';
        strcat(szOutput2, "^ ERROR");
        
        strcat(szOutput, szOutput2);
        strcat(szOutput, "\n");
    }

    strcat(szOutput, "\nError: ");
    strcat(szOutput, szText);

    if (g_bStdOut)
        printf("%s (%d) : ==> %s: \n%s \n%s\n",szInclude, nAutScriptLine, szText, szScriptLine, szOutput2 );
    else
        MessageBox(g_hWnd, szOutput, szTitle, MB_ICONSTOP | MB_OK | MB_SYSTEMMODAL | MB_SETFOREGROUND);

    // Signal that we want to quit as soon as possible
    m_nCurrentOperation = AUT_QUIT;

} // FatalError()


///////////////////////////////////////////////////////////////////////////////
// FatalError()
//
// This function will print a message box giving the line and line number
// of any script stopping errors, it will also set the flag that makes the
// script quit.
//
// The line used to print the error is the last one stored in m_nErrorLine
//
///////////////////////////////////////////////////////////////////////////////

void Engine::FatalError(int iErr, const char *szText2)
{
    char    szTitle[AUT_MAX_LINESIZE];
    char    szText[AUT_MAX_LINESIZE];
    char    szOutput[AUT_MAX_LINESIZE*3];

    LoadString(g_hInstance, IDS_AUT_E_TITLE, szTitle, AUT_MAX_LINESIZE);
    LoadString(g_hInstance, iErr, szText, AUT_MAX_LINESIZE);

    // Get the line
    const char *szScriptLine = g_oScriptFile.GetLine(m_nErrorLine);
    int nAutScriptLine = g_oScriptFile.GetAutLineNumber(m_nErrorLine);
    int nIncludeID = g_oScriptFile.GetIncludeID(m_nErrorLine);
    const char *szInclude = g_oScriptFile.GetIncludeName(nIncludeID);

    if (szInclude == NULL)
        sprintf(szOutput, "Line %d:\n\n", nAutScriptLine);
    else
        sprintf(szOutput, "Line %d  (File \"%s\"):\n\n", nAutScriptLine, szInclude);

    strcat(szOutput, szScriptLine);
    strcat(szOutput, "\n\nError: ");
    strcat(szOutput, szText);
    strcat(szOutput, "\n\n");
    strcat(szOutput, szText2);

    if (g_bStdOut)
        printf("%s (%d) : ==> %s: \n%s \n%s\n",szInclude, nAutScriptLine, szText, szScriptLine, szText2);
    else
        MessageBox(g_hWnd, szOutput, szTitle, MB_ICONSTOP | MB_OK | MB_SYSTEMMODAL | MB_SETFOREGROUND);

    // Signal that we want to quit as soon as possible
    m_nCurrentOperation = AUT_QUIT;

} // FatalError()

///////////////////////////////////////////////////////////////////////////////
// InitScript()
//
// Take the loaded script and then make a note of the location
// and details of user functions (line number, parameters)
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::InitScript(char *szFile)
{
    // Check that the block structures are correct
    if ( AUT_FAILED(parser->VerifyBlockStructure()) )
        return AUT_ERR;

    // Scan for user functions
    if ( AUT_FAILED(StoreUserFuncs()) )
        return AUT_ERR;

    // Scan for plugin functions and load required DLLs
//    if ( AUT_FAILED(StorePluginFuncs()) )
//        return AUT_ERR;

    // Check user function calls refer to existing functions (or plugin functions)
    if ( AUT_FAILED(VerifyUserFuncCalls()) )
        return AUT_ERR;

    // Make a note of the script filename (for @ScriptDir, etc)
    char    szFileTemp[_MAX_PATH+1];
    char    *szFilePart;

    GetFullPathName(szFile, _MAX_PATH, szFileTemp, &szFilePart);
    m_sScriptFullPath = szFileTemp;
    m_sScriptName = szFilePart;
    szFilePart[-1] = '\0';
    m_sScriptDir = szFileTemp;

    // Initialise the random number routine (must be done after the script has
    // loaded as the compiled script loader also uses random numbers and must
    // be reseeded now to get random numbers again!
    Util_RandInit();

    return AUT_OK;

} // InitScript()


///////////////////////////////////////////////////////////////////////////////
// ProcessMessages()
//
///////////////////////////////////////////////////////////////////////////////

int    Engine::ProcessMessages()
{
    MSG        msg;

    // Check if there is a message waiting
    while (PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
    {
        // Is it a quit message?
        if (msg.message == WM_QUIT)
        {
            m_bWinQuitProcessed = true;
            m_nCurrentOperation = AUT_QUIT;    // Script to end (if not already)
            break;                            // Exit this while loop
        }

        // Dispatch the message - check for special dialog/GUI related messages first!
#ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
        if (!g_oGUI.IsDialogMessage(&msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#else
            TranslateMessage(&msg);
            DispatchMessage(&msg);
#endif
    }

    // Check if the user has clicked EXIT in the tray or someone tried to WM_CLOSE the main window - tut
    if (g_bTrayExitClicked == true)
    {
        g_bScriptPaused = false;            // Force unpause (clicking the tray pauses the script)    
        g_nExitMethod = AUT_EXITBY_TRAY;
        g_bTrayExitClicked = false;            // To stop re-triggering which would disrupte any OnExit() func
        m_nCurrentOperation = AUT_QUIT;
    }

    // This return value is not used in the Execute() function - just from functions like
    // DirGetSize() that need to know when to quit/pause
    if (m_nCurrentOperation == AUT_QUIT)
        return AUT_QUIT;
    else if (g_bScriptPaused)
        return AUT_PAUSED;
    else
        return AUT_RUN;
}


///////////////////////////////////////////////////////////////////////////////
// Execute()
//
// This is the main function - it reads in a line of script, and then executes
// it :)  It is also called recursively to process winwait, processwait and
// user function calls.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::Execute(int nScriptLine)
{
    MSG            msg;
    VectorToken    LineTokens;                        // Vector (array) of tokens for a line of script
    const char    *szScriptLine;

    // Increase the recursion level of this function and check that we've not gone too far
    if (m_nExecuteRecursionLevel >= AUT_MAXEXECUTERECURSE)
    {
        FatalError(IDS_AUT_E_MAXRECURSE);
        return AUT_ERR;
    }
    else
        ++m_nExecuteRecursionLevel;

    // Is this recursion level 1 (starts as 0 and +1 above)?  If so, we have just started the script so run
    // our OnAutoItStart() function if defined
    if (m_nExecuteRecursionLevel == 1)
    {
        int    nTemp1, nTemp2, nTemp3, nTemp4;

        if (_parser->FindUserFunction("OnAutoItStart", nTemp1, nTemp2, nTemp3, nTemp4) == true)
            SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
    }


    m_bUserFuncReturned = false;                // When this becomes true, a user function (or winwait
                                                // operation has requested to return (or EndFunc encountered)

    // Run our Execute() loop
    while(m_bWinQuitProcessed == false && m_bUserFuncReturned == false)
    {
        processEvents();

        // Get the next line, or quit if none left
        m_nErrorLine = nScriptLine;                // Keep track for errors
        szScriptLine = g_oScriptFile.GetLine(nScriptLine++);
        if ( szScriptLine == NULL )
        {
            m_nCurrentOperation = AUT_QUIT;
            continue;                            // Back to the start of the while loop
        }

        // Do the lexing (convert the line into tokens) - stored in LineTokens
        Lexer(nScriptLine-1, szScriptLine, LineTokens);                // No need to check for errors, already lexed in InitScript()

        // Parse and execute the line
        Parser(LineTokens, nScriptLine);

    } // End While


    // Reset the UserFunction flag before returning (in case Execute() was called recursively)
    m_bUserFuncReturned = false;

    // Is this the final call of Execute() - Level = 1 when finishing completely
    if (m_nExecuteRecursionLevel != 1)
    {
        --m_nExecuteRecursionLevel;
        return AUT_OK;                            // Not completely finishing, just return normally
    }

    //
    // If we are here then we are completely finishing
    //

    // Ask worker threads to close
    g_bKillWorkerThreads = true;

    while (m_InetGetDetails.bInProgress)        // Wait for the thread to finish nicely
        Sleep(AUT_IDLE);


    // Destroy GUI (no longer always a child of the main window so we clean up manually...)
#ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
    g_oGUI.DeleteAll();
#endif

    // Did we recieve a WM_QUIT message above?  If so the message loop and windows are dead
    // so we might as well quit now (any attempt to call an exit function would fail with no windows...)
    // NOTE: WM_QUIT is only EVER posted by the main window's WM_DESTROY code so it is safe to assume
    // that if WM_QUIT then the main window has already run WM_DESTROY
    if (m_bWinQuitProcessed == true)
        return AUT_OK;


    // Run our OnExit function if it exists
    int    nTemp1, nTemp2, nTemp3, nTemp4;

    if (_parser->FindUserFunction(m_sOnExitFunc.c_str(), nTemp1, nTemp2, nTemp3, nTemp4) == true)
    {
        // Set global vars for @ExitCode and @ExitMethod - Note these names CANNOT usually
        // exist because they start with @ :)
        Variant        vTemp;

        vTemp = g_nExitCode;
        g_oVarTable.Assign("@ExitCode", vTemp, true, VARTABLE_FORCEGLOBAL);
        vTemp = g_nExitMethod;
        g_oVarTable.Assign("@ExitMethod", vTemp, true, VARTABLE_FORCEGLOBAL);

        m_nCurrentOperation = AUT_RUN;        // Get back into a run state for the final push :)
        SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
        m_nCurrentOperation = AUT_QUIT;
    }


    // Destroy our main window (Calls WM_DESTROY on our and any child windows)
    DestroyWindow(g_hWnd);

    // Get all remaining window messages until the quit WM_QUIT message is received as a result
    // of the DestroyWindow and WM_DESTROY processing
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return AUT_OK;

} // Execute()


int Engine::processEvents()
{
    // Run the windows message loop and handle quit conditions
    int msg = ProcessMessages();

    // If script is in a quit state then don't execute any more code
    if (msg == AUT_QUIT) {
        return AUT_QUIT;
    }

    // Handle hotkeys first (even if paused - eventually we will and an unpause function to make this useful)
    if (_handleHotKey && _handleHotKey() == true) {
        return msg;
    }

    // If the script is paused, sleep then loop again
    if (g_bScriptPaused == true)
    {
        Sleep(AUT_IDLE);                    // Quick sleep to reduce CPU load
        return msg;
    }

    // If we need to, run an adlib section
    if (_handleAdlib && _handleAdlib() == true) {
        return msg;
    }

    // If we need to, run a GUI event function
    if (_handleGuiEvent && _handleGuiEvent() == true) {
        return msg;
    }
}


///////////////////////////////////////////////////////////////////////////////
// HandleDelayedFunctions()
//
// Handles the processing of delayed commands, Sleep, WinWait, RunWait, etc.
///////////////////////////////////////////////////////////////////////////////

// TODO: delete
//bool Engine::HandleDelayedFunctions(void)
//{
//    // If required, process any winwait style commands
//    return Win_HandleWinWait();
//
//} // HandleDelayedFunctions()


///////////////////////////////////////////////////////////////////////////////
// FunctionExecute()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::FunctionExecute(int nFunction, VectorVariant &vParams, Variant &vResult)
{
    vResult        = 1;                            // Default return value is 1
    SetFuncErrorCode(0);                        // Default extended error code is zero
    SetFuncExtCode(0);                            // Default extended code is zero

    // Lookup the function and execute
    return (this->*m_FuncList[nFunction].lpFunc)(vParams, vResult);    

} // FunctionExecute()


///////////////////////////////////////////////////////////////////////////////
// StoreUserFuncs()
//
// Make a note of the location and details of the user functions
// (name, line number, parameters, end line number)
//
// This function also "sanity checks" the function declaration so that we
// can make assumptions during user function calls
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::StoreUserFuncs(void)
{
    uint            ivPos;                        // Position in the vector
    AString            sFuncName;                    // Temp function name
    VectorToken        LineTokens;                    // Vector (array) of tokens for a line of script
    int                nScriptLine = 1;            // 1 = first line
    const char        *szScriptLine;

    // Check each line of the script for the FUNC keyword
    while ( (szScriptLine = g_oScriptFile.GetLine(nScriptLine++)) != NULL )
    {
        m_nErrorLine = nScriptLine - 1;            // Keep track for errors

        if ( AUT_FAILED( Lexer(nScriptLine-1, szScriptLine, LineTokens) ) )
            return AUT_ERR;                        // Bad line

        ivPos = 0;

        if ( !(LineTokens[ivPos].m_nType == TOK_KEYWORD && LineTokens[ivPos].nValue == K_FUNC) )
            continue;                            // Next line

        ++ivPos;                                // Skip "func" keyword

        // Tokens should be: userfunctionname ( $variable , [ByRef] $variable , ... )

        // Get user function name
        if ( LineTokens[ivPos].m_nType != TOK_USERFUNCTION )
        {
            FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
            return AUT_ERR;
        }

        // Check that this function isn't a duplicate
        sFuncName = LineTokens[ivPos].szValue;    // Get function name
        if (m_oUserFuncList.find(sFuncName.c_str()) != NULL)
        {
            FatalError(IDS_AUT_E_DUPLICATEFUNC);
            return AUT_ERR;
        }

        ++ivPos;                                // Skip function name

        if ( LineTokens[ivPos].m_nType != TOK_LEFTPAREN )
        {
            FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
            return AUT_ERR;
        }

        ++ivPos;                                // Skip (

        // Parse the parameter declarations
        if ( AUT_FAILED(StoreUserFuncs2(LineTokens, ivPos, sFuncName, nScriptLine)) )
            return AUT_ERR;

    } // End While()

    // Finalize the list of user functions which sorts the list for speed searching. 
    // NO USER MORE FUNCTIONS CAN BE ADDED AFTER THIS
    m_oUserFuncList.createindex();

    return AUT_OK;

} // StoreUserFuncs()


///////////////////////////////////////////////////////////////////////////////
// StoreUserFuncs2()
//
// More StoreUserFuncs - split to aid readabilty
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::StoreUserFuncs2(VectorToken &LineTokens, uint &ivPos, const AString &sFuncName, int &nScriptLine)
{
    UserFuncDetails    tFuncDetails;

    // Tokens should be: [ByRef] $variable , ... [ByRef] $variable , ... )

    int    nNumParamsMin = -1;

    int nNumParams = 0;
    int nFuncStart = nScriptLine - 1;                // Make a note of the Func line

    for (;;)
    {
        // Is it )
        if ( LineTokens[ivPos].m_nType == TOK_RIGHTPAREN )
        {
            // Finishing parsing function, next token must be end
            ++ivPos;                            // Skip )

            if (LineTokens[ivPos].m_nType != TOK_END)
            {
                FatalError(IDS_AUT_E_EXTRAONLINE);
                return AUT_ERR;
            }
            else
                break;                            // Exit while loop
        }

        // Is it the ByRef keyword 
        if ( LineTokens[ivPos].m_nType == TOK_KEYWORD && LineTokens[ivPos].nValue == K_BYREF )
        {
            // We don't need to do anything except skip the ByRef keyword, but check that the next 
            // token is a variable
            ++ivPos;                            // Skip ByRef keyword

            if ((LineTokens[ivPos].m_nType != TOK_VARIABLE) || (nNumParamsMin != -1) )
            {
                FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
                return AUT_ERR;
            }
        }

        // Is is a variable?
        if ( LineTokens[ivPos].m_nType == TOK_VARIABLE )
        {
            ++ivPos;                            // Skip variable name

            // Is it the Optional parameter
            if ( LineTokens[ivPos].m_nType == TOK_EQUAL )
            {
                ++ivPos;                        // Skip TOK_EQUAL

                // May be an optional sign (TOK_PLUS/TOK_MINUS next)
                if (LineTokens[ivPos].m_nType == TOK_PLUS || LineTokens[ivPos].m_nType == TOK_MINUS)
                    ++ivPos;                    // Skip sign

                // Then a literal or macro
                if (LineTokens[ivPos].isliteral())
                {
                    ++ivPos;                    // Skip literal
                    if (nNumParamsMin == -1)
                        nNumParamsMin = nNumParams;            // Memorize min number of Param
                }
                else
                {
                    FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
                    return AUT_ERR;
                }
            }
            else
            {
                // Not a default value, so check if any previous were (once a default param
                // is used all following params must also have a default param)
                if (nNumParamsMin != -1) // optional par without default value
                {
                    FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
                    return AUT_ERR;
                }
            }
        
            ++nNumParams;                        // Increase the number of parameters

            // Must be a , or ) next
            if ( LineTokens[ivPos].m_nType != TOK_COMMA && LineTokens[ivPos].m_nType != TOK_RIGHTPAREN )
            {
                FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
                return AUT_ERR;
            }
            else
                continue;                        // Next loop
        }

        // Is it a , ?
        if ( LineTokens[ivPos].m_nType == TOK_COMMA )
        {
            ++ivPos;                            // Skip ,

            // Must be a variable or ByRef keyword next
            if ( LineTokens[ivPos].m_nType != TOK_VARIABLE && 
                !(LineTokens[ivPos].m_nType == TOK_KEYWORD && LineTokens[ivPos].nValue == K_BYREF) )
            {
                FatalError(IDS_AUT_E_BADFUNCSTATEMENT);
                return AUT_ERR;
            }
            else
                continue;                        // Next loop
        }

        // no match
        FatalError(IDS_AUT_E_BADFUNCSTATEMENT, LineTokens[ivPos].m_nCol);
        return AUT_ERR;


    } // End While (getting parameters)



    // Now we have the funcline,  and number of parameters (the function would have
    // already returned if there were errors

    // Search for EndFunc keyword - fatal error if not found
    if ( AUT_FAILED(StoreUserFuncsFindEnd(nScriptLine)) )
        return AUT_ERR;
    
    // Complete user function found, store
    tFuncDetails.sName = sFuncName;
    tFuncDetails.nFuncLineNum = nFuncStart;
    tFuncDetails.nEndFuncLineNum = nScriptLine - 1;        // Line contained EndFunc
    tFuncDetails.nNumParams = nNumParams;
    if (nNumParamsMin == -1)
        nNumParamsMin = nNumParams;        // no optional parameters
    tFuncDetails.nNumParamsMin = nNumParamsMin;
    m_oUserFuncList.add(tFuncDetails);

    return AUT_OK;

} // StoreUserFuncs2()


///////////////////////////////////////////////////////////////////////////////
// StoreUserFuncsFindEnd()
//
// Looks for a valid matching EndFunc, returns the line number of the endfunc (+1)
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::StoreUserFuncsFindEnd(int &nScriptLine)
{
    VectorToken    LineTokens;                        // Vector (array) of tokens for a line of script
    uint        ivPos;
    const char    *szScriptLine;

    bool bEndFuncFound = false;
    while ( bEndFuncFound == false && (szScriptLine = g_oScriptFile.GetLine(nScriptLine)) != NULL )
    {
        ++nScriptLine;
        m_nErrorLine = nScriptLine - 1;            // Keep track for errors

        if ( AUT_FAILED( Lexer(nScriptLine-1, szScriptLine, LineTokens) ) )
            return AUT_ERR;                        // Bad line

        ivPos = 0;

        if (LineTokens[ivPos].m_nType == TOK_KEYWORD && LineTokens[ivPos].nValue == K_FUNC)
        {
            FatalError(IDS_AUT_E_MISSINGENDFUNC);
            return AUT_ERR;
        }

        if (LineTokens[ivPos].m_nType == TOK_KEYWORD && LineTokens[ivPos].nValue == K_ENDFUNC)
            bEndFuncFound = true;            // Break out of endfunc while loop

    } // End While

    return AUT_OK;

} // StoreUserFuncsFindEnd


///////////////////////////////////////////////////////////////////////////////
// VerifyUserFuncCalls()
//
// Checks that each user function call refers to a defined user function
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::VerifyUserFuncCalls(void)
{
    uint            ivPos;                        // Position in the vector
    VectorToken        LineTokens;                    // Vector (array) of tokens for a line of script
    int                nScriptLine = 1;            // 1 = first line
    const char        *szScriptLine;
    int                nLineNum, nNumParams, nNumParamsMin, nEndLineNum;

    // Check each line for user function calls
    while ( (szScriptLine = g_oScriptFile.GetLine(nScriptLine++)) != NULL )
    {
        m_nErrorLine = nScriptLine - 1;            // Keep track for errors
        
        Lexer(nScriptLine-1, szScriptLine, LineTokens);        // No need to test for errors, already done in StoreUserFuncs()

        ivPos = 0;

        while (LineTokens[ivPos].m_nType != TOK_END)
        {
            if (LineTokens[ivPos].m_nType == TOK_USERFUNCTION)
            {
                if (_parser->FindUserFunction(LineTokens[ivPos].szValue, nLineNum, nNumParams, nNumParamsMin, nEndLineNum) == false)
                {
                    FatalError(IDS_AUT_E_UNKNOWNUSERFUNC, LineTokens[ivPos].m_nCol);
                    return AUT_ERR;
                }
            }

            ++ivPos;
        }

    } // End While()

    return AUT_OK;

} // VerifyUserFuncCalls()


///////////////////////////////////////////////////////////////////////////////
// StorePluginFuncs()
//
// Query the scriptfile object for all the plugin dlls specified, load each one
// and make a note of all the function names it supplies.
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT Engine::StorePluginFuncs(void)
{
/*    HINSTANCE hDll = LoadLibrary("example.dll");
    
    if (hDll == NULL)
        return AUT_ERR;

    PluginFuncs *lpEntry = new PluginFuncs;
    
    lpEntry->hDll = hDll;
    lpEntry->sFuncName = "PluginTest";
    lpEntry->lpNext = NULL;

    // Add to the list

*/
    return AUT_OK;

} // StorePluginFuncs()


///////////////////////////////////////////////////////////////////////////////
// HandleAdlib()
//
// Handles the processing of Adlid
///////////////////////////////////////////////////////////////////////////////

bool Engine::HandleAdlib(void)
{
    // Only continue if adlibbing is enabled AND we are not currently adlibing already!
    if (m_bAdlibEnabled == false || m_bAdlibInProgress == true)
        return false;

    // Check the timer - we only run the adlib every so often as it is a strain on the
    // CPU otherwise
    DWORD    dwDiff;
    DWORD    dwCur = timeGetTime();

    if (dwCur < m_tAdlibTimerStarted)
        dwDiff = (UINT_MAX - m_tAdlibTimerStarted) + dwCur; // timer wraps at 2^32
    else
        dwDiff = dwCur - m_tAdlibTimerStarted;

    // Timer elapsed?
    if (dwDiff < m_nAdlibTimeout)
        return false;                            // Not time yet

    // Reset the timer
    m_tAdlibTimerStarted = dwCur;


    // Get the details of the function (we should have previously checked that it
    // exists)
    int        nLineNum, nNumParams, nNumParamsMin, nEndLineNum;

    _parser->FindUserFunction(m_sAdlibFuncName.c_str(), nLineNum, nNumParams, nNumParamsMin, nEndLineNum);
    ++nLineNum;                                    // Skip function declaration

    // Save current operation (may be waiting)
    int nCurrentOperation    = m_nCurrentOperation;

    // Continue execution with the user function (using recursive call of Execute() )
    m_nCurrentOperation = AUT_RUN;                // Change mode to run script (may have been waiting)
    m_bAdlibInProgress    = true;                    // True if we are currently running adlib function

    SaveExecute(nLineNum, true, true);            // Save state and recursively call Execute()

    m_bAdlibInProgress    = false;

    // If the function caused the script to end, we must honour the request rather than restoring
    if (m_nCurrentOperation != AUT_QUIT)
    {
        m_nCurrentOperation    = nCurrentOperation;
        return false;                            // Continue Execute() (to give script a chance to run!)
    }

    return true;                                // Returning true will stop further
                                                // progress in Execute() and restart the loop
} // HandleAdlib()

///////////////////////////////////////////////////////////////////////////////
// HandleGuiEvent()
//
// Handles the processing of GUI events
///////////////////////////////////////////////////////////////////////////////

bool Engine::HandleGuiEvent(void)
{
#ifdef AUT_CONFIG_GUI

    // Only continue if GUI event is enabled AND we are not currently running a GUI function
    if (g_oGUI.m_bGuiEventEnabled == false || m_bGuiEventInProgress == true)
        return false;

    GUIEVENT   Event;
    int        nLineNum, nNumParams, nNumParamsMin, nEndLineNum;

    // Get the messages until there are no more
    while (g_oGUI.GetMsg(Event))
    {
        // Is the event a callback?
        if (Event.sCallback.empty())
            continue;

        // Callback

        // Check that this user function exists
        if (_parser->FindUserFunction(Event.sCallback.c_str(),
                nLineNum, nNumParams, nNumParamsMin, nEndLineNum) == false)
            continue;
        else
        {
            Variant        vTemp;

            // Set global vars for - Note these names CANNOT usually
            // exist because they start with @ :)
            vTemp = Event.nGlobalID;
            g_oVarTable.Assign("@GUI_CTRLID", vTemp, true, VARTABLE_FORCEGLOBAL);

            vTemp = Event.hWnd;
            g_oVarTable.Assign("@GUI_WINHANDLE", vTemp, true, VARTABLE_FORCEGLOBAL);

            vTemp = Event.hCtrl;
            g_oVarTable.Assign("@GUI_CTRLHANDLE", vTemp, true, VARTABLE_FORCEGLOBAL);

            // Save current operation (may be waiting)
            int nCurrentOperation    = m_nCurrentOperation;

            // Continue execution with the user function (using recursive call of Execute() )
            m_nCurrentOperation = AUT_RUN;                // Change mode to run script (may have been waiting)
            m_bGuiEventInProgress    = true;                // True if we are currently running adlib function

            SaveExecute(nLineNum+1, true, true);        // Save state and recursively call Execute()

            m_bGuiEventInProgress    = false;

            // If the function caused the script to end, we must honour the request rather than restoring
            if (m_nCurrentOperation != AUT_QUIT)
                m_nCurrentOperation    = nCurrentOperation;
            else
                return true;                            // Restart the messageloop in order to check the quit condition
        }
    }

#endif
    
    return false;

} // HandleGuiEvent()


///////////////////////////////////////////////////////////////////////////////
// SaveExecute()
//
// Saves the current state of the script and then performs a recursive
// call to Execute() and then restores state. Not all the items saved in state
// are required for every usage but the function is used from many parts of the
// code and needs to be safe for all of them.
// The current scope can optionally be raised/lowered too.
// This function is used by UserFunction calling, Adlib, Hotkey, Call
///////////////////////////////////////////////////////////////////////////////

void Engine::SaveExecute(int nScriptLine, bool bRaiseScope, bool bRestoreErrorCode)
{
    // Saved state vars - Control related
    Variant            vControlSearchValue;                        // The ID, classname or text to search for 

    // Function call related
    int                nNumParams = m_nNumParams;    // Number of parameters passed to a UDF

    // Main vars
    int                nErrorLine        = m_nErrorLine;            // Line number used to generate error messages
    int                nFuncErrorCode    = m_nFuncErrorCode;        // Extended error code
    int                nFuncExtCode    = m_nFuncExtCode;        // Extended code

    // We also need to keep track of how many statements (if, while, etc)
    // we have on the go just in case the user function is naughty (return function in the
    // middle of a loop) and leaves the statement stacks in an incorrect state - we will
    // have to correct this after Execute() returns
    uint    nStackSize        = m_StatementStack.size();


    // Continue execution with the user function (using recursive call of Execute() )

    if (bRaiseScope)
        g_oVarTable.ScopeIncrease();                // Increase scope

    Execute(nScriptLine);

    // Descrease the variable scope - deletes function local variables
    if (bRaiseScope)
        g_oVarTable.ScopeDecrease();

    // Make sure the statement stacks are the same as before the user function was called, 
    // if not we fix them
    while (nStackSize < m_StatementStack.size())
        m_StatementStack.pop();

    m_nNumParams            = nNumParams;
    m_nErrorLine            = nErrorLine;

    // Only restore the @error code in certain situations (adlib/hotkey)
    if (bRestoreErrorCode)
    {
        m_nFuncErrorCode    = nFuncErrorCode;
        m_nFuncExtCode        = nFuncExtCode;
    }

} // SaveExecute()


AUT_RESULT Engine::call(const char* szName, Variant &vResult)
{
    int nTemp1, nTemp2, nTemp3, nTemp4;

    // Check that this user function exists
    if (_parser->FindUserFunction(szName, nTemp1, nTemp2, nTemp3, nTemp4) == false)
    {
        SetFuncErrorCode(1);                // Silent error even though function not valid
        return AUT_OK;                        // As will probably be used this way
    }
    else
    {
        m_vUserRetVal = 1;                    // Default return value is 1
        SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
        vResult = m_vUserRetVal;            // Get return value (0 = timed out)
        return AUT_OK;
    }
}

AUT_RESULT Engine::interruptCall(const char* szName, Variant &vResult)
{
    // Get the details of the function (we should have previously checked that it
    // exists!)
    int        nLineNum, nNumParams, nNumParamsMin, nEndLineNum;
    if (_parser->FindUserFunction(szName, nLineNum, nNumParams, nNumParamsMin, nEndLineNum) == false) {
        SetFuncErrorCode(1);                // Silent error even though function not valid
        return AUT_OK;                      // As will probably be used this way
    }

    // Save current operation (may be waiting)
    int nCurrentOperation    = m_nCurrentOperation;

    // Continue execution with the user function (using recursive call of Execute() )
    m_nCurrentOperation = AUT_RUN;                // Change mode to run script (may have been waiting)

    // Skip function declaration
    m_vUserRetVal = 1;                     // Default return value is 1
    SaveExecute(nLineNum+1, true, true);   // Save state and recursively call Execute()
    vResult = m_vUserRetVal;               // Get return value (0 = timed out)

    // If the function caused the script to end, we must honour the request rather than restoring
    if (m_nCurrentOperation != AUT_QUIT)
        m_nCurrentOperation    = nCurrentOperation;
    return AUT_OK;
}

AUT_RESULT Engine::eval(const char* szName, Variant &vResult)
{
    bool    bConst = false;

     if (g_oVarTable.isDeclared(szName))
     {
         Variant *pvTemp;
         g_oVarTable.GetRef(szName, &pvTemp, bConst);
         vResult = *pvTemp;
         return AUT_OK;
     }
     else
     {
         SetFuncErrorCode(1);            // Silent error even though variable not valid
         vResult = "";
         return AUT_OK;
     }
}

AUT_RESULT Engine::assign(const char* szName, Variant &vValue, int nReqScope,
        bool bCreate, Variant &vResult)
{
    Variant *pvTemp;
    bool    bConst = false;

    // Get a reference to the variable in the requested scope, if it doesn't exist, then create it.
    g_oVarTable.GetRef(szName, &pvTemp, bConst, nReqScope);
    if (pvTemp == NULL)
    {
        if (bCreate)
            g_oVarTable.Assign(szName, vValue, false, nReqScope);
        else
            vResult = 0;                        // Default is 1
    }
    else
        *pvTemp = vValue;

    return AUT_OK;
}

int Engine::isDeclared(const char* szName)
{
    return g_oVarTable.isDeclared(vParams[0].szValue());
}
