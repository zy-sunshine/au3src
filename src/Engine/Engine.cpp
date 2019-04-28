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
#include "Engine/Parser/Parser.h"
#include "Engine/Parser/Lexer.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <limits.h>
#else
//    #include "qmath.h"                            // MinGW doesn't like our asm maths functions
#endif

#include "Utils/SysUtil.h"

#include "Engine/ScriptFile.h"
#include "Utils/OSVersion.h"
#include "Utils/SendKeys.h"
#include "Utils/SetForegroundWinEx.h"

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

    // execute control variables
    m_bWinQuitProcessed            = false;
    m_nExecuteRecursionLevel    = 0;            // Reset our recursion tracker for the Execute() function
 
    // settings
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

    m_bDetectHiddenText         = false;       // Don't detect hidden text by default
    m_bWinSearchChildren        = false;       // Only search top level windows by default
 
    // Initialise DLL handles to NULL
    for (i=0; i<AUT_MAXOPENFILES; ++i)
        m_DLLHandleDetails[i] = NULL;
    
    // Internet download/upload defaults
    m_InetGetDetails.bInProgress    = false;
    m_InetGetDetails.nBytesRead        = -1;

    _handleAdlib = NULL;
    _handleHotkey = NULL;
    _handleGuiEvent = NULL;

    _parser = new Parser(this);

    g_oScriptFile = new ScriptFile(this);
    g_oSetForeWinEx = new SetForegroundWinEx();
    g_oSendKeys = new HS_SendKeys();
    g_oSendKeys->Init();                            // Init sendkeys to defaults
} // Engine()

static int funcNameSort(AU3_FuncInfo *a0,  AU3_FuncInfo *a1)
{
    return strcmp(a0->szName, a1->szName);
}

void Engine::initModules(AU3_FuncInfo * funcList, int size)
{
    _parser->m_FuncList = funcList;
    _parser->m_nFuncListSize = size;

    for (int i=0; i<_parser->m_nFuncListSize; ++i) {
// NOTE: because Lexer search function use binary search, enable these code now
//      but why not sort these function firstly, speed?
//#ifdef _DEBUG
        // test to make sure that the list is in order, but only during development
        if (i>0 && strcmp(_parser->m_FuncList[i-1].szName, _parser->m_FuncList[i].szName) > 0)    // out of sequence
        {
            // display out of order name before aborting.
            AUT_DEBUGMESSAGEBOX(_parser->m_FuncList[i].szName);
            AUT_ASSERT(strcmp(_parser->m_FuncList[i-1].szName, _parser->m_FuncList[i].szName) < 0);
        }
//#endif
    }
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

    // Close any dll handles that script writer has not closed (naughty!)
    for (i=0; i<AUT_MAXOPENFILES; ++i)
    {
        if (m_DLLHandleDetails[i] != NULL)
            FreeLibrary(m_DLLHandleDetails[i]);
    }

    // Free up memory used in our function list
    //for (i=0; i<m_nFuncListSize; ++i) 
    //    delete [] m_FuncList[i].szName;                // Free allocated string

    //delete [] m_FuncList;                            // Delete the entire list

}

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
    if ( AUT_FAILED(_parser->VerifyBlockStructure()) )
        return AUT_ERR;

    // Scan for user functions
    if ( AUT_FAILED(_parser->StoreUserFuncs()) )
        return AUT_ERR;

    // Scan for plugin functions and load required DLLs
//    if ( AUT_FAILED(_parser->StorePluginFuncs()) )
//        return AUT_ERR;

    // Check user function calls refer to existing functions (or plugin functions)
    if ( AUT_FAILED(_parser->VerifyUserFuncCalls()) )
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
    g_oSysUtil.RandInit();

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
            _parser->m_nCurrentOperation = AUT_QUIT;    // Script to end (if not already)
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
        _parser->m_nCurrentOperation = AUT_QUIT;
    }

    // This return value is not used in the Execute() function - just from functions like
    // DirGetSize() that need to know when to quit/pause
    if (_parser->m_nCurrentOperation == AUT_QUIT)
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
            _parser->SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
    }


    _parser->m_bUserFuncReturned = false;       // When this becomes true, a user function (or winwait
                                                // operation has requested to return (or EndFunc encountered)

    // Run our Execute() loop
    while(m_bWinQuitProcessed == false && _parser->m_bUserFuncReturned == false)
    {
        processEvents();

        // Get the next line, or quit if none left
        szScriptLine = g_oScriptFile->GetLine(nScriptLine++);
        if ( szScriptLine == NULL )
        {
            _parser->m_nCurrentOperation = AUT_QUIT;
            continue;                            // Back to the start of the while loop
        }

        // Do the lexing (convert the line into tokens) - stored in LineTokens
        _parser->lexer->doLexer(nScriptLine-1, szScriptLine, LineTokens);  // No need to check for errors, already lexed in InitScript()

        // Parse and execute the line
        _parser->Parse(LineTokens, nScriptLine-1, nScriptLine);

    } // End While


    // Reset the UserFunction flag before returning (in case Execute() was called recursively)
    _parser->m_bUserFuncReturned = false;

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
        _parser->m_oVarTable.Assign("@ExitCode", vTemp, true, VARTABLE_FORCEGLOBAL);
        vTemp = g_nExitMethod;
        _parser->m_oVarTable.Assign("@ExitMethod", vTemp, true, VARTABLE_FORCEGLOBAL);

        _parser->m_nCurrentOperation = AUT_RUN;        // Get back into a run state for the final push :)
        _parser->SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
        _parser->m_nCurrentOperation = AUT_QUIT;
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
    if (_handleHotkey && _handleHotkey() == true) {
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
// HandleAdlib()
//
// Handles the processing of Adlid
///////////////////////////////////////////////////////////////////////////////

// TODO:
//bool Engine::HandleAdlib(void)
//{
//    // Only continue if adlibbing is enabled AND we are not currently adlibing already!
//    if (m_bAdlibEnabled == false || m_bAdlibInProgress == true)
//        return false;
//
//    // Check the timer - we only run the adlib every so often as it is a strain on the
//    // CPU otherwise
//    DWORD    dwDiff;
//    DWORD    dwCur = timeGetTime();
//
//    if (dwCur < m_tAdlibTimerStarted)
//        dwDiff = (UINT_MAX - m_tAdlibTimerStarted) + dwCur; // timer wraps at 2^32
//    else
//        dwDiff = dwCur - m_tAdlibTimerStarted;
//
//    // Timer elapsed?
//    if (dwDiff < m_nAdlibTimeout)
//        return false;                            // Not time yet
//
//    // Reset the timer
//    m_tAdlibTimerStarted = dwCur;
//
//
//    // Get the details of the function (we should have previously checked that it
//    // exists)
//    int        nLineNum, nNumParams, nNumParamsMin, nEndLineNum;
//
//    _parser->FindUserFunction(m_sAdlibFuncName.c_str(), nLineNum, nNumParams, nNumParamsMin, nEndLineNum);
//    ++nLineNum;                                    // Skip function declaration
//
//    // Save current operation (may be waiting)
//    int nCurrentOperation    = _parser->m_nCurrentOperation;
//
//    // Continue execution with the user function (using recursive call of Execute() )
//    _parser->m_nCurrentOperation = AUT_RUN;                // Change mode to run script (may have been waiting)
//    m_bAdlibInProgress    = true;                    // True if we are currently running adlib function
//
//    _parser->SaveExecute(nLineNum, true, true);            // Save state and recursively call Execute()
//
//    m_bAdlibInProgress    = false;
//
//    // If the function caused the script to end, we must honour the request rather than restoring
//    if (_parser->m_nCurrentOperation != AUT_QUIT)
//    {
//        _parser->m_nCurrentOperation    = nCurrentOperation;
//        return false;                            // Continue Execute() (to give script a chance to run!)
//    }
//
//    return true;                                // Returning true will stop further
//                                                // progress in Execute() and restart the loop
//} // HandleAdlib()

///////////////////////////////////////////////////////////////////////////////
// HandleGuiEvent()
//
// Handles the processing of GUI events
///////////////////////////////////////////////////////////////////////////////

// TODO:
//bool Engine::HandleGuiEvent(void)
//{
//#ifdef AUT_CONFIG_GUI
//
//    // Only continue if GUI event is enabled AND we are not currently running a GUI function
//    if (g_oGUI.m_bGuiEventEnabled == false || m_bGuiEventInProgress == true)
//        return false;
//
//    GUIEVENT   Event;
//    int        nLineNum, nNumParams, nNumParamsMin, nEndLineNum;
//
//    // Get the messages until there are no more
//    while (g_oGUI.GetMsg(Event))
//    {
//        // Is the event a callback?
//        if (Event.sCallback.empty())
//            continue;
//
//        // Callback
//
//        // Check that this user function exists
//        if (_parser->FindUserFunction(Event.sCallback.c_str(),
//                nLineNum, nNumParams, nNumParamsMin, nEndLineNum) == false)
//            continue;
//        else
//        {
//            Variant        vTemp;
//
//            // Set global vars for - Note these names CANNOT usually
//            // exist because they start with @ :)
//            vTemp = Event.nGlobalID;
//            _parser->m_oVarTable.Assign("@GUI_CTRLID", vTemp, true, VARTABLE_FORCEGLOBAL);
//
//            vTemp = Event.hWnd;
//            _parser->m_oVarTable.Assign("@GUI_WINHANDLE", vTemp, true, VARTABLE_FORCEGLOBAL);
//
//            vTemp = Event.hCtrl;
//            _parser->m_oVarTable.Assign("@GUI_CTRLHANDLE", vTemp, true, VARTABLE_FORCEGLOBAL);
//
//            // Save current operation (may be waiting)
//            int nCurrentOperation    = _parser->m_nCurrentOperation;
//
//            // Continue execution with the user function (using recursive call of Execute() )
//            _parser->m_nCurrentOperation = AUT_RUN;                // Change mode to run script (may have been waiting)
//            m_bGuiEventInProgress    = true;                // True if we are currently running adlib function
//
//            _parser->SaveExecute(nLineNum+1, true, true);        // Save state and recursively call Execute()
//
//            m_bGuiEventInProgress    = false;
//
//            // If the function caused the script to end, we must honour the request rather than restoring
//            if (_parser->m_nCurrentOperation != AUT_QUIT)
//                _parser->m_nCurrentOperation    = nCurrentOperation;
//            else
//                return true;                            // Restart the messageloop in order to check the quit condition
//        }
//    }
//
//#endif
//    
//    return false;
//
//} // HandleGuiEvent()

int Engine::GetCurLineNumber (void) const
{
return _parser->m_nErrorLine;  // Return current line number for TrayTip debugging
}

void Engine::quit()
{ _parser->m_nCurrentOperation = AUT_QUIT; }


// Assign variable
bool Engine::Assign(const AString &sVarName, const Variant &vVariant,
        bool bConst/* = false*/, int nReqScope/* = VARTABLE_ANY*/)
{
    return _parser->m_oVarTable.Assign(sVarName, vVariant, bConst, nReqScope);
}
// Get pointer to a variable
bool Engine::GetRef(const AString &sVarName, Variant **pvVariant, bool &bConst, int nReqScope/* = VARTABLE_ANY*/)
{
    return _parser->m_oVarTable.GetRef(sVarName, pvVariant, bConst, nReqScope);
}
// Return true if the reference variable exists (and type of variable, global/local etc)
int Engine::isDeclared(const AString &sVarName)
{
    return _parser->m_oVarTable.isDeclared(sVarName);
}
void Engine::SetFuncErrorCode(int nCode)
{
    return _parser->SetFuncErrorCode(nCode);
}
int Engine::nFuncErrorCode()
{
    return _parser->nFuncErrorCode();
}
// Set script extended info (@extended code)
void  Engine::SetFuncExtCode(int nCode)
{
    _parser->SetFuncExtCode(nCode);
}
AUT_RESULT  Engine::call(const char* szName, Variant &vResult)
{
    return _parser->call(szName, vResult);
}
AUT_RESULT  Engine::interruptCall(const char* szName, Variant &vResult)
{
    return _parser->interruptCall(szName, vResult);
}
void Engine::FatalError(int iErr, int nCol/* = -1*/)
{
    _parser->FatalError(iErr, nCol);
}
void Engine::FatalError(int iErr, const char *szText2)
{
    _parser->FatalError(iErr, szText2);
}

bool Engine::FindUserFunction(const char *szName, int &nLineNum, int &nNumParams,
    int &nNumParamsMin, int &nEndLineNum)
{
    return _parser->FindUserFunction(szName, nLineNum, nNumParams, nNumParamsMin, nEndLineNum);
}
// === utility functions ===
///////////////////////////////////////////////////////////////////////////////
// Engine::VariantArrayDim()
//
// Simple helper function for Diming a SINGLE dimension variant with specified
// number of elements
//
///////////////////////////////////////////////////////////////////////////////

void Engine::VariantArrayDim(Variant *pvVariant, unsigned int iElements)
{
    pvVariant->ArraySubscriptClear();            // Reset the subscript
    pvVariant->ArraySubscriptSetNext(iElements);// Number of elements
    pvVariant->ArrayDim();                        // Dimension array

} // Engine::VariantArrayDim()


///////////////////////////////////////////////////////////////////////////////
// Engine::VariantArrayGetRef()
//
// Simple helper function for getting a ref to an element of our simple array
//
///////////////////////////////////////////////////////////////////////////////

Variant * Engine::VariantArrayGetRef(Variant *pvVariant, unsigned int iElement)
{
    pvVariant->ArraySubscriptClear();            // Reset the subscript
    pvVariant->ArraySubscriptSetNext(iElement);    // Set subscript we want to access
    return pvVariant->ArrayGetRef();            // Get reference to the element

} // Engine::VariantArrayGetRef()
