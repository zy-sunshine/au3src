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
// script_win.cpp
//
// Contains window related functions.  Part of script.cpp
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleWin.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <windows.h>
    #include <limits.h>
    #include <commctrl.h>
#endif

#include "Utils/utility.h"
#include "Utils/WinUtil.h"
#include "WinSearchUtil.h"


AU3_FuncInfo ModuleWin::funcInfo[] = {
    {"WINEXISTS", &ModuleWin::F_WinExists, 1, 2},
    {"WINACTIVE", &ModuleWin::F_WinActive, 1, 2},
    {"WINWAIT", &ModuleWin::F_WinWait, 1, 3},
    {"WINWAITACTIVE", &ModuleWin::F_WinWaitActive, 1, 3},
    {"WINWAITCLOSE", &ModuleWin::F_WinWaitClose, 1, 3},
    {"WINWAITNOTACTIVE", &ModuleWin::F_WinWaitNotActive, 1, 3}
    {"WINACTIVATE", &ModuleWin::F_WinActivate, 1, 2},
    {"WINCLOSE", &ModuleWin::F_WinClose, 1, 2},
    {"WINSHOW", &ModuleWin::F_WinShow, 3, 3},
    {"WINSETSTATE", &ModuleWin::F_WinShow, 3, 3},
    {"WINKILL", &ModuleWin::F_WinKill, 1, 2},
    {"WINMINIMIZEALL", &ModuleWin::F_WinMinimizeAll, 0, 0},
    {"WINMINIMIZEALLUNDO", &ModuleWin::F_WinMinimizeAllUndo, 0, 0},
    {"WINSETTITLE", &ModuleWin::F_WinSetTitle, 3, 3},
    {"WINMOVE", &ModuleWin::F_WinMove, 4, 6},
    {"WINGETTEXT", &ModuleWin::F_WinGetText, 1, 2},
    {"WINGETTITLE", &ModuleWin::F_WinGetTitle, 1, 2},
    {"CONTROLCLICK", &ModuleWin::F_ControlClick, 3, 5},
    {"CONTROLFOCUS", &ModuleWin::F_ControlFocus, 3, 3},
    {"CONTROLGETFOCUS", &ModuleWin::F_ControlGetFocus, 1, 2},
    {"WINSETONTOP", &ModuleWin::F_WinSetOnTop, 3, 3},
    {"WINGETPOS", &ModuleWin::F_WinGetPos, 1, 2},
    {"CONTROLGETTEXT", &ModuleWin::F_ControlGetText, 3, 3},
    {"CONTROLSETTEXT", &ModuleWin::F_ControlSetText, 4, 4},
    {"CONTROLGETPOS", &ModuleWin::F_ControlGetPos, 3, 3},
    {"CONTROLCOMMAND", &ModuleWin::F_ControlCommand, 4, 5},
//    {"CONTROLLISTVIEW", &ModuleWin::F_ControlListView, 4, 6},
    {"CONTROLENABLE", &ModuleWin::F_ControlEnable, 3, 3},
    {"CONTROLDISABLE", &ModuleWin::F_ControlDisable, 3, 3},
    {"CONTROLHIDE", &ModuleWin::F_ControlHide, 3, 3},
    {"CONTROLMOVE", &ModuleWin::F_ControlMove, 5, 7},
    {"CONTROLSHOW", &ModuleWin::F_ControlShow, 3, 3},
    {"WINGETCLASSLIST", &ModuleWin::F_WinGetClassList, 1, 2},
//    {"STATUSBARGETTEXT", &ModuleWin::F_StatusbarGetText, 1, 3},
    {"CONTROLSEND", &ModuleWin::F_ControlSend, 4, 5},
    {"WINMENUSELECTITEM", &ModuleWin::F_WinMenuSelectItem, 3, 9},
    {"WINGETCLIENTSIZE", &ModuleWin::F_WinGetClientSize, 1, 2},
    {"WINGETHANDLE", &ModuleWin::F_WinGetHandle, 1, 2},
    {"CONTROLGETHANDLE", &ModuleWin::F_ControlGetHandle, 3, 3},
    {"WINGETCARETPOS", &ModuleWin::F_WinGetCaretPos, 0, 0},
    {"WINGETSTATE", &ModuleWin::F_WinGetState, 1, 2},
    {"WINSETTRANS", &ModuleWin::F_WinSetTrans, 3, 3},
    {"TOOLTIP", &ModuleWin::F_ToolTip, 1, 3},

    {"WINLIST", &ModuleWin::F_WinList, 0, 2},
    {"WINGETPROCESS", &ModuleWin::F_WinGetProcess, 1, 2},

    {"MSGBOX", &ModuleWin::F_MsgBox, 3, 4},
    {"TRAYTIP", &ModuleWin::F_TrayTip, 3, 4},
    {"AUTOITWINSETTITLE", &ModuleWin::F_AutoItWinSetTitle, 1, 1},
    {"AUTOITWINGETTITLE", &ModuleWin::F_AutoItWinGetTitle, 0, 0},
    {"PIXELSEARCH", &ModuleWin::F_PixelSearch, 5, 7},
    {"PIXELCHECKSUM", &ModuleWin::F_PixelChecksum, 4, 5},
    {"PIXELGETCOLOR", &ModuleWin::F_PixelGetColor, 2, 2},
    {"SPLASHIMAGEON", &ModuleWin::F_SplashImageOn, 2, 7},
    {"SPLASHTEXTON", &ModuleWin::F_SplashTextOn, 2, 10},
    {"SPLASHOFF", &ModuleWin::F_SplashOff, 0, 0},
    {"PROGRESSON", &ModuleWin::F_ProgressOn, 2, 6},
    {"PROGRESSOFF", &ModuleWin::F_ProgressOff, 0, 0},
    {"PROGRESSSET", &ModuleWin::F_ProgressSet, 1, 3},
    {"INPUTBOX", &ModuleWin::F_InputBox, 2, 9},
}

ModuleWin::ModuleWin(Engine* engine)
    : engine(engine)
{
    m_hWndTip                    = NULL;            // ToolTip window
}

ModuleWin::~ModuleWin()
{
    // Destroy the ToolTip window if required
    if (m_hWndTip)
        DestroyWindow(m_hWndTip);
}

///////////////////////////////////////////////////////////////////////////////
// WinWait( "title" [,"text"] [,timeout]] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinWait(VectorVariant &vParams, Variant &vResult)
{
    BOOL    bRes = FALSE;
    WinSearchUtil util(engine);

    util.Win_WindowWaitInit(vParams);
    vResult = 1;

    while (true) {
        Sleep(AUT_IDLE);
        if (engine->processEvents() == AUT_QUIT) { break; }
        bRes = util.Win_WinExists();
        if (bRes) { break; }
        if (util.isTimeOut()) {
            vResult = 0;
            return AUT_OK;
        }
    }

    Util_Sleep(engine->nWinWaitDelay());        // Briefly pause before continuing
    return AUT_OK;

} // F_WinWait()


///////////////////////////////////////////////////////////////////////////////
// WinWaitActive( "title" [,"text"] [,timeout]] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinWaitActive(VectorVariant &vParams, Variant &vResult)
{
    BOOL    bRes = FALSE;
    WinSearchUtil util(engine);
    util.Win_WindowWaitInit(vParams);

    vResult = 1;                    // Default return value is 1
    while (true) {
        Sleep(AUT_IDLE);
        if (engine->processEvents() == AUT_QUIT) { break; }
        bRes = util.Win_WinActive();
        if (bRes) { break; }
        if (util.isTimeOut()) {
            vResult = 0;
            return AUT_OK;
        }
    }

    Util_Sleep(engine->nWinWaitDelay());        // Briefly pause before continuing
    return AUT_OK;

} // F_WinWaitActive()


///////////////////////////////////////////////////////////////////////////////
// WinWaitNotActive( "title" [,"text"] [,timeout]] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinWaitNotActive(VectorVariant &vParams, Variant &vResult)
{
    BOOL    bRes = FALSE;
    WinSearchUtil util(engine);
    util.Win_WindowWaitInit(vParams);

    vResult = 1;                    // Default return value is 1
    while (true) {
        Sleep(AUT_IDLE);
        if (engine->processEvents() == AUT_QUIT) { break; }
        bRes = !util.Win_WinActive();
        if (bRes) { break; }
        if (util.isTimeOut()) {
            vResult = 0;
            return AUT_OK;
        }
    }

    Util_Sleep(engine->nWinWaitDelay());        // Briefly pause before continuing
    return AUT_OK;

} // F_WinWaitNotActive()


///////////////////////////////////////////////////////////////////////////////
// WinWaitClose( "title" [,"text"] [,timeout]] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinWaitClose(VectorVariant &vParams, Variant &vResult)
{
    BOOL    bRes = FALSE;
    WinSearchUtil util(engine);
    util.Win_WindowWaitInit(vParams);

    vResult = 1;                    // Default return value is 1
    while (true) {
        Sleep(AUT_IDLE);
        if (engine->processEvents() == AUT_QUIT) { break; }
        bRes = !util.Win_WinExists();
        if (bRes) { break; }
        if (util.isTimeOut()) {
            vResult = 0;
            return AUT_OK;
        }
    }

    Util_Sleep(engine->nWinWaitDelay());        // Briefly pause before continuing
    return AUT_OK;

} // F_WinWaitClose()


///////////////////////////////////////////////////////////////////////////////
// WinActive( "title" [,"text"] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinActive(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);
    if (util.Win_WinActive() == false)
        vResult = 0;                    // Default is 1

    return AUT_OK;

} // F_WinActive()


///////////////////////////////////////////////////////////////////////////////
// WinExists( "title" [,"text"] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinExists(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);
    if (util.Win_WinExists() == false)
        vResult = 0;                    // Default is 1

    return AUT_OK;

} // F_WinExists()

///////////////////////////////////////////////////////////////////////////////
// WinActivate( "title" [,"text"] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinActivate(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                            // No window to activate

    engine->g_oSetForeWinEx.Activate(util.m_WindowSearchHWND);
    Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // F_WinActivate()


///////////////////////////////////////////////////////////////////////////////
// WinShow( "title" ,"text", flag )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinShow(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                            // Required window not found

    int nFlag = vParams[2].nValue();

    if (nFlag == SW_ENABLE)
        EnableWindow(util.m_WindowSearchHWND, TRUE);
    else if (nFlag == SW_DISABLE)
        EnableWindow(util.m_WindowSearchHWND, FALSE);
    else
    {
        ShowWindow(util.m_WindowSearchHWND, nFlag);
        Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing
    }

    return AUT_OK;

} // F_WinShow()


///////////////////////////////////////////////////////////////////////////////
// WinMove()
// Moves a window
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinMove(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nWidth, nHeight;
    RECT    rect;

    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                                    // Required window not found

    GetWindowRect(util.m_WindowSearchHWND, &rect);

    if (iNumParams < 5)
        nWidth = rect.right - rect.left;
    else
        nWidth = vParams[4].nValue();

    if (iNumParams < 6)
        nHeight = rect.bottom - rect.top;
    else
        nHeight = vParams[5].nValue();

    MoveWindow(util.m_WindowSearchHWND, vParams[2].nValue(), vParams[3].nValue(), nWidth, nHeight, TRUE);
    //Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // WinMove()


///////////////////////////////////////////////////////////////////////////////
// WinClose()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinClose(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                            // Required window not found

    PostMessage(util.m_WindowSearchHWND, WM_CLOSE, 0, 0L);
    Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // WinClose()


///////////////////////////////////////////////////////////////////////////////
// WinKill()
// Closes a window - uses more force than WinClose
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinKill(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                            // Required window not found

    Util_WinKill(util.m_WindowSearchHWND);
    Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // WinKill()


///////////////////////////////////////////////////////////////////////////////
// WinSetTitle()
// Changes the text in a window title
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinSetTitle(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                                    // Required window not found

    SetWindowText(util.m_WindowSearchHWND, vParams[2].szValue());

    return AUT_OK;

} // WinSetTitle()


///////////////////////////////////////////////////////////////////////////////
// Win_WinGetTitle()
// Must call Win_WindowSearchInit() first to set title and text to search for
// Gets the Full title of a window
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetTitle(VectorVariant &vParams, Variant &vResult)
{
    char    szBuffer[AUT_WINTEXTBUFFER+1];
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                                    // Required window not found

    GetWindowText(util.m_WindowSearchHWND, szBuffer, AUT_WINTEXTBUFFER);

    vResult = szBuffer;

    return AUT_OK;

} // Win_WinGetTitle()


///////////////////////////////////////////////////////////////////////////////
// Win_WinGetText()
// Must call Win_WindowSearchInit() first to set title and text to search for
// Gets the static text from a window
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetText(VectorVariant &vParams, Variant &vResult)
{
    // $var = WinGetText(<title>, [<text>])
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        return AUT_OK;                                    // Required window not found

    vResult = Util_GetWinText(util.m_WindowSearchHWND, engine->bDetectHiddenText());

    return AUT_OK;

} // Win_WinGetText()

///////////////////////////////////////////////////////////////////////////////
// WinSetOnTop()
// Must call Win_WindowSearchInit() first to set title and text to search for
// Renders a window TOPMOST or NOTOPMOST
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinSetOnTop(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);
    if (util.Win_WindowSearch() == false)
        return AUT_OK;                                    // Required window not found

    if ( vParams[2].nValue() == 1 )                            // 1 = TopMost... else NoTopMost
        SetWindowPos(util.m_WindowSearchHWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
    else
        SetWindowPos(util.m_WindowSearchHWND, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

    return AUT_OK;

} // WinSetOnTop()


///////////////////////////////////////////////////////////////////////////////
// WinGetPos()
//
// $array[4] = WinGetPos("title" [,"text"])
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetPos(VectorVariant &vParams, Variant &vResult)
{
    RECT    rect;
    Variant    *pvTemp;
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required window not found
    }

    GetWindowRect(util.m_WindowSearchHWND, &rect);    // Load the window stats

    // Setup vResult as an Array to hold the 4 values we want to return
    Util_VariantArrayDim(&vResult, 4);

    pvTemp = Util_VariantArrayGetRef(&vResult, 0);    // First element
    *pvTemp = (int)rect.left;                    // X

    pvTemp = Util_VariantArrayGetRef(&vResult, 1);
    *pvTemp = (int)rect.top;                    // Y

    pvTemp = Util_VariantArrayGetRef(&vResult, 2);
    *pvTemp = (int)(rect.right - rect.left);    // Width

    pvTemp = Util_VariantArrayGetRef(&vResult, 3);
    *pvTemp = (int)(rect.bottom - rect.top);    // Height

    return AUT_OK;

} // WinGetPos()


///////////////////////////////////////////////////////////////////////////////
// ControlFocus()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlFocus(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, true);

    if ( SetFocus(util.m_ControlSearchHWND) == NULL)
        vResult = 0;            // Error

    Util_AttachThreadInput(util.m_WindowSearchHWND, false);

    return AUT_OK;

} // ControlFocus()


///////////////////////////////////////////////////////////////////////////////
// ControlClick()
// ControlClick("title,"text", "control", [button], [numclicks])
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlClick(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nClicks;
    UINT    msgdown, msgup;
    WPARAM    wParam;
    RECT    rect;
    LPARAM    lParam;
    WinSearchUtil util(engine);

    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, true);

    SetActiveWindow(util.m_WindowSearchHWND);        // See BM_CLICK documentation, applies to this too

    // Get the dimensions of the control so we can click the centre of it (maybe safer and more natural than 0,0)
    GetWindowRect(util.m_ControlSearchHWND, &rect);
    lParam = MAKELPARAM( (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);

    // Get number of clicks
    if (iNumParams >= 5)
        nClicks = vParams[4].nValue();
    else
        nClicks = 1;

    // Default is left button
    msgdown = WM_LBUTTONDOWN;
    msgup    = WM_LBUTTONUP;
    wParam    = MK_LBUTTON;

    if (iNumParams >= 4)
    {
        if (!stricmp(vParams[3].szValue(), "RIGHT"))
        {
            msgdown = WM_RBUTTONDOWN;
            msgup    = WM_RBUTTONUP;
            wParam    = MK_RBUTTON;
        }
        else if (!stricmp(vParams[3].szValue(), "MIDDLE"))
        {
            msgdown = WM_MBUTTONDOWN;
            msgup    = WM_MBUTTONUP;
            wParam    = MK_MBUTTON;
        }
    }

    for (int i=0; i<nClicks; ++i)
    {
        PostMessage(util.m_ControlSearchHWND, msgdown, wParam, lParam);
        //Sleep(m_nMouseClickDownDelay); - causing failures?
        PostMessage(util.m_ControlSearchHWND, msgup, 0, lParam);
        Util_Sleep(engine->nMouseClickDelay());
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, false);

    return AUT_OK;

} // ControlClick()


///////////////////////////////////////////////////////////////////////////////
// ControlSetText()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlSetText(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    if (SendMessage(util.m_ControlSearchHWND,WM_SETTEXT, 0, (LPARAM)vParams[3].szValue()) != TRUE)
        vResult = 0;            // Error

    return AUT_OK;

} // ControlSetText()



///////////////////////////////////////////////////////////////////////////////
// Win_ControlGetText()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlGetText(VectorVariant &vParams, Variant &vResult)
{
    char    szBuffer[AUT_WINTEXTBUFFER+1];
    WinSearchUtil util(engine);

    vResult = "";                                // In this case set the default to be a blank string

    if (util.ControlSearch(vParams) == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required control not found
    }

    if ( !(SendMessage(util.m_ControlSearchHWND,WM_GETTEXT,(WPARAM)AUT_WINTEXTBUFFER,
                    (LPARAM)szBuffer) > 0) )
        engine->SetFuncErrorCode(1);            // Error
    else
        vResult = szBuffer;

    return AUT_OK;

} // ControlGetText()


///////////////////////////////////////////////////////////////////////////////
// Win_ControlGetPos()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlGetPos(VectorVariant &vParams, Variant &vResult)
{
    Variant    *pvTemp;
    POINT    point;
    RECT    rect;
    WinSearchUtil util(engine);

    if (util.ControlSearch(vParams) == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required control not found
    }

    if ( GetWindowRect(util.m_ControlSearchHWND, &rect) )    // Load the window stats
    {
        point.x = rect.left;
        point.y = rect.top;

        ScreenToClient(util.m_WindowSearchHWND,&point);

        // Setup vResult as an Array to hold the 4 values we want to return
        Util_VariantArrayDim(&vResult, 4);

        pvTemp = Util_VariantArrayGetRef(&vResult, 0);        // First element
        *pvTemp = (int)point.x;                    // X

        pvTemp = Util_VariantArrayGetRef(&vResult, 1);
        *pvTemp = (int)point.y;                    // Y

        pvTemp = Util_VariantArrayGetRef(&vResult, 2);
        *pvTemp = (int)(rect.right - rect.left);        // Width

        pvTemp = Util_VariantArrayGetRef(&vResult, 3);
        *pvTemp = (int)(rect.bottom - rect.top);        // Height

    }
    else
        engine->SetFuncErrorCode(1);            // Error

    return AUT_OK;

} // ControlGetPos()


///////////////////////////////////////////////////////////////////////////////
// ControlMove()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlMove(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nWidth, nHeight;
    RECT    rect;
    WinSearchUtil util(engine);

    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, true);

    if ( GetWindowRect(util.m_ControlSearchHWND, &rect) )    // Load the window stats
    {
        if (iNumParams < 6)
            nWidth = rect.right - rect.left;
        else
            nWidth = vParams[5].nValue();

        if (iNumParams < 7)
            nHeight = rect.bottom - rect.top;
        else
            nHeight = vParams[6].nValue();

        MoveWindow(util.m_ControlSearchHWND, vParams[3].nValue(), vParams[4].nValue(), nWidth, nHeight, true);
    }
    else
    {
        vResult = 0;
        return AUT_OK;
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, false);

    return AUT_OK;

} // ControlMove()


///////////////////////////////////////////////////////////////////////////////
// ControlEnable()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlEnable(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    EnableWindow(util.m_ControlSearchHWND,TRUE);

    return AUT_OK;

} // ControlEnable()


///////////////////////////////////////////////////////////////////////////////
// Win_ControlDisable()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlDisable(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    EnableWindow(util.m_ControlSearchHWND,FALSE);

    return AUT_OK;

} // ControlDisable()


///////////////////////////////////////////////////////////////////////////////
// ControlShow()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlShow(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    ShowWindow(util.m_ControlSearchHWND,SW_SHOWNOACTIVATE);

    return AUT_OK;

} // ControlShow()


///////////////////////////////////////////////////////////////////////////////
// ControlHide()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlHide(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false )
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    ShowWindow(util.m_ControlSearchHWND,SW_HIDE);

    return AUT_OK;

} // ControlHide()


///////////////////////////////////////////////////////////////////////////////
// ControlCommand()
// - ControlCommand(<title>,<text>,<control ref>,<cmd>,<extra>,<extra>)
// - cmds:
// - - ShowDropDown (drops a combo list)
// - - HideDropDown (UNdrops a combo list)
// - - AddString, string (adds a string to the end of a combo list)
// - - DelString, occurrence (deletes a string according to occurence)
// - - TabLeft, (navigates to the next tab to the left of a SysTabControl32)
// - - TabRight, (navigates to the next tab to the right of a SysTabControl32)
// - - CurrentTab, (returns the current tab in focus of a SysTabControl32)
// - - FindString, string (returns occurence ref of the exact string)
// - - GetCurrentSelection, occurrence (sets selection to occurrence ref)
// - - SetCurrentSelection, occurrence (sets selection to occurrence ref)
// - - SelectString, string (sets selection according to string)
// - - IsChecked (returns 1 if Button is checked)
// - - IsVisible (returns 1 if Control is Visible)
// - - IsEnabled (returns 1 if Control is Enabled)
// - - Check (Checks Button)
// - - UnCheck (Unchecks Button)
// - - GetLineCount (Returns # of lines in and Edit)
// - - EditPaste (Pastes text into current cursor pos)
// - - GetCurrentLine (Returns line # of current (caret pos) line in and Edit)
// - - GetCurrentCol (Returns column # of current (caret pos) line in an Edit)
// - - GetLine, # (Returns text line # passed)
//
// Return value depends on the command, @error is used to indicate errors.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlCommand(VectorVariant &vParams,  Variant &vResult)
{
    char    szBuffer[AUT_WINTEXTBUFFER+1];
    const char    *szCmd;
    UINT        vMsg = 0;
    UINT        xMsg = 0;
    UINT        yMsg = 0;
    RECT        rect;
    LPARAM        lParam;
    Variant        vTemp;
    WinSearchUtil util(engine);

    if (util.ControlSearch(vParams) == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required control not found
    }


    // Make sure that any unused parameters are ""
    vTemp = "";
    while (vParams.size() < 5)
        vParams.push_back(vTemp);


    Util_AttachThreadInput(util.m_WindowSearchHWND, true);

    // Easy access to the command parameter
    szCmd = vParams[3].szValue();

    while (1)
    {
        if ( strcmpi(szCmd,"ISVISIBLE")==0 )
        {
            if ( IsWindowVisible(util.m_ControlSearchHWND) )
                vResult = 1;
            else
                vResult = 0;
            break;                            // ISENABLED performed, exit switch
        }
        if ( strcmpi(szCmd,"ISENABLED")==0 )
        {
            if ( IsWindowEnabled(util.m_ControlSearchHWND) )
                vResult = 1;
            else
                vResult = 0;
            break;                            // ISENABLED performed, exit switch
        }
        if ( strcmpi(szCmd,"TABLEFT")==0 )
        {// must be a Tab Control
            PostMessage(util.m_ControlSearchHWND, WM_KEYDOWN, VK_LEFT, (LPARAM)( (MapVirtualKey(VK_LEFT, 0)<<16) | 0x00000001 ) );
            Sleep(0);
            PostMessage(util.m_ControlSearchHWND, WM_KEYUP, VK_LEFT, (LPARAM)( (MapVirtualKey(VK_LEFT, 0)<<16) | 0xC0000001 ) );
            break;                            // TABLEFT performed, exit switch
        }
        if ( strcmpi(szCmd,"TABRIGHT")==0 )
        {// must be a Tab Control
            PostMessage(util.m_ControlSearchHWND,WM_KEYDOWN,VK_RIGHT, (LPARAM)( (MapVirtualKey(VK_LEFT, 0)<<16) | 0x00000001 ) );
            Sleep(0);
            PostMessage(util.m_ControlSearchHWND,WM_KEYUP,VK_RIGHT, (LPARAM)( (MapVirtualKey(VK_LEFT, 0)<<16) | 0xC0000001 ));
            break;                            // TABRIGHT performed, exit switch
        }
        if ( strcmpi(szCmd,"CURRENTTAB")==0 )
        {// must be a Tab Control
            int nTab = (int)SendMessage(util.m_ControlSearchHWND,TCM_GETCURSEL,vParams[4].nValue(),0);
            if ( nTab==-1 )
                engine->SetFuncErrorCode(1);
            else
            {
                nTab++;
                vResult = nTab;
            }
            break;                            // CURRENTTAB performed, exit switch
        }

        if ( strcmpi(szCmd,"SHOWDROPDOWN")==0 )
        {// must be a ComboBox
            if ( !(SendMessage(util.m_ControlSearchHWND, CB_SHOWDROPDOWN, (WPARAM)TRUE, 0)) )
                engine->SetFuncErrorCode(1);
            break;                            // SHOWDROPDOWN performed, exit switch
        }

        if ( strcmpi(szCmd,"HIDEDROPDOWN")==0 )
        {// must be a ComboBox
            if ( !(SendMessage(util.m_ControlSearchHWND, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0)) )
                engine->SetFuncErrorCode(1);
            break;                            // HIDEDROPDOWN performed, exit switch
        }

        if ( strcmpi(szCmd,"ADDSTRING")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"Combo",5)==0 )
                vMsg = CB_ADDSTRING;
            if ( strnicmp(vParams[2].szValue(),"List",4)==0 )
                vMsg = LB_ADDSTRING;
            if ( vMsg )
            {// Must be ComboBox or ListBox
                if ( !(SendMessage(util.m_ControlSearchHWND, vMsg, 0, (LPARAM)vParams[4].szValue())) )
                    engine->SetFuncErrorCode(1);
            }
            break;                            // ADDSTRING performed, exit switch
        }

        if ( strcmpi(szCmd,"DELSTRING")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"Combo",5)==0 )
                vMsg = CB_DELETESTRING;
            if ( strnicmp(vParams[2].szValue(),"List",4)==0 )
                vMsg = LB_DELETESTRING;
            if ( vMsg )
            {// Must be ComboBox or ListBox
                if ( !(SendMessage(util.m_ControlSearchHWND, vMsg, (WPARAM)vParams[4].nValue(), 0)) )
                    engine->SetFuncErrorCode(1);
            }
            break;                            // DELSTRING performed, exit switch
        }

        if ( strcmpi(szCmd,"FINDSTRING")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"Combo",5)==0 )
                vMsg = CB_FINDSTRINGEXACT;
            if ( strnicmp(vParams[2].szValue(),"List",4)==0 )
                vMsg = LB_FINDSTRINGEXACT;
            if ( vMsg )
            {// Must be ComboBox or ListBox
                vResult = (int)SendMessage(util.m_ControlSearchHWND, vMsg, (WPARAM)1, (LPARAM)vParams[4].szValue());
                if ( vResult.nValue() == -1 )
                    engine->SetFuncErrorCode(1);
            }
            else
                engine->SetFuncErrorCode(1);
            break;                            // FINDSTRING performed, exit switch
        }

        if ( strcmpi(szCmd,"SETCURRENTSELECTION")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"Combo",5)==0 )
            {
                vMsg = CB_SETCURSEL;
                xMsg = CBN_SELCHANGE;
                yMsg = CBN_SELENDOK;
            }
            if ( strnicmp(vParams[2].szValue(),"List",4)==0 )
            {
                vMsg = LB_SETCURSEL;
                xMsg = LBN_SELCHANGE;
                yMsg = LBN_DBLCLK;
            }
            if ( vMsg )
            {// Must be ComboBox or ListBox
                if ( SendMessage(util.m_ControlSearchHWND, vMsg, (WPARAM)vParams[4].nValue(), 0) == -1 )
                    engine->SetFuncErrorCode(1);
                else
                {
                    SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                            (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),xMsg),
                            (LPARAM)util.m_ControlSearchHWND);
                    SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                            (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),yMsg),
                            (LPARAM)util.m_ControlSearchHWND);
                }
            }
            break;                            // SETCURRENTSELECTION performed, exit switch
        }

        if ( stricmp(szCmd,"GETCURRENTSELECTION")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"ComboBox",8)==0 )
            {
                vMsg = CB_GETCURSEL;
                xMsg = CB_GETLBTEXTLEN;
                yMsg = CB_GETLBTEXT;
            }
            if ( strnicmp(vParams[2].szValue(),"ListBox",7)==0 )
            {
                vMsg = LB_GETCURSEL;
                xMsg = LB_GETTEXTLEN;
                yMsg = LB_GETTEXT;
            }
            if ( vMsg )
            {// Must be ComboBox or ListBox
                int          nIndex, nLen;
                nIndex = (int)SendMessage(util.m_ControlSearchHWND, vMsg, 0, 0);
                if ( nIndex == -1)
                    engine->SetFuncErrorCode(1);
                else
                {
                    nLen = (int)SendMessage(util.m_ControlSearchHWND,xMsg,(WPARAM)nIndex,0);
                    if ( nLen == -1 )
                        engine->SetFuncErrorCode(1);
                    else
                    {
                        char     *pBuffer = NULL;
                        nLen++;
                        pBuffer=(char*)calloc(256+nLen,1);
                        nLen = (int)SendMessage(util.m_ControlSearchHWND,yMsg,
                                (WPARAM)nIndex,(LPARAM)pBuffer);
                        if ( nLen == -1 )
                                engine->SetFuncErrorCode(1);
                        else
                                vResult = pBuffer;
                        if(pBuffer)
                                free(pBuffer);
                    }
                }
            }
            break;     // GETCURRENTSELECTION performed, exit switch
        }

        if ( strcmpi(szCmd,"SELECTSTRING")==0 )
        {
            if ( strnicmp(vParams[2].szValue(),"ComboBox",8)==0 )
            {
                vMsg = CB_SELECTSTRING;
                xMsg = CBN_SELCHANGE;
                yMsg = CBN_SELENDOK;
            }
            if ( strnicmp(vParams[2].szValue(),"ListBox",7)==0 )
            {
                vMsg = LB_SELECTSTRING;
                xMsg = LBN_SELCHANGE;
                yMsg = LBN_DBLCLK;
            }
            if ( vMsg )
            {// Must be ComboBox or ListBox
                if ( SendMessage(util.m_ControlSearchHWND, vMsg, (WPARAM)1,
                            (LPARAM)vParams[4].szValue()) == -1 )
                    engine->SetFuncErrorCode(1);
                else
                {
                    SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                            (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),xMsg),
                            (LPARAM)util.m_ControlSearchHWND);
                    SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                            (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),yMsg),
                            (LPARAM)util.m_ControlSearchHWND);
                }
            }
            break;                            // SELECTSTRING performed, exit switch
        }

        if ( strcmpi(szCmd,"ISCHECKED")==0  )
        {//Must be a Button
            if ( SendMessage(util.m_ControlSearchHWND,BM_GETCHECK, 0, 0) == BST_CHECKED )
                vResult = 1;                // Is checked (0 is default/not checked)
            else
                vResult = 0;
            break;                            // ISCHECKED performed, exit switch
        }

        if ( strcmpi(szCmd,"CHECK")==0 )
        {//Must be a Button
            // Only send the "check" if the button is not already checked
            if ( SendMessage(util.m_ControlSearchHWND,BM_GETCHECK, 0, 0) == BST_UNCHECKED )
            {
                //SendMessage(util.m_ControlSearchHWND,BM_SETCHECK,(WPARAM)BST_CHECKED, 0);
                //SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                //  (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),BN_CLICKED),
                //  (LPARAM)util.m_ControlSearchHWND);
                SetActiveWindow(util.m_WindowSearchHWND);        // See BM_CLICK docs, applies to this too
                GetWindowRect(util.m_ControlSearchHWND, &rect);    // Code to primary click the centre of the control
                lParam = MAKELPARAM( (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
                PostMessage(util.m_ControlSearchHWND, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
                PostMessage(util.m_ControlSearchHWND, WM_LBUTTONUP, 0, lParam);
            }
            break;                            // CHECK performed, exit switch
        }

        if ( strcmpi(szCmd,"UNCHECK")==0 )
        {//Must be a Button
            // Only send the "uncheck" if the button is not already unchecked
            if ( SendMessage(util.m_ControlSearchHWND,BM_GETCHECK, 0, 0) == BST_CHECKED )
            {
                //SendMessage(util.m_ControlSearchHWND,BM_SETCHECK,(WPARAM)BST_UNCHECKED, 0);
                //SendMessage(GetParent(util.m_ControlSearchHWND),WM_COMMAND,
                //  (WPARAM)MAKELONG(GetDlgCtrlID(util.m_ControlSearchHWND),BN_CLICKED),
                //  (LPARAM)util.m_ControlSearchHWND);
                SetActiveWindow(util.m_WindowSearchHWND);        // See BM_CLICK docs, applies to this too
                GetWindowRect(util.m_ControlSearchHWND, &rect);    // Code to primary click the centre of the control
                lParam = MAKELPARAM( (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2);
                PostMessage(util.m_ControlSearchHWND, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
                PostMessage(util.m_ControlSearchHWND, WM_LBUTTONUP, 0, lParam);
            }
                break;                            // UNCHECK performed, exit switch
        }

        if ( strcmpi(szCmd,"GETSELECTED")==0 )
        {//Must be an Edit
            UINT    nLen,nStart,nEnd;
            char    *pBuffer = NULL;

            SendMessage(util.m_ControlSearchHWND,EM_GETSEL,(WPARAM)&nStart,(LPARAM)&nEnd);
            if (nStart!=nEnd)
            {
                if ( (nLen = (int)SendMessage(util.m_ControlSearchHWND,WM_GETTEXTLENGTH,0 , 0)) )
                {
                    pBuffer=(char*)calloc(256+nLen,1);
                    if ( SendMessage(util.m_ControlSearchHWND,WM_GETTEXT,(WPARAM)(nLen+1),
                                (LPARAM)pBuffer) && nEnd <= AUT_WINTEXTBUFFER )
                    {
                        if (nEnd != nLen )
                            pBuffer[nEnd]='\0';
                        vResult = pBuffer+nStart;
                    }
                    else
                        engine->SetFuncErrorCode(1);
                }
                else
                    engine->SetFuncErrorCode(1);
            }
            else
                engine->SetFuncErrorCode(1);
            if(pBuffer)
                free(pBuffer);
            break;                            // GETSELECTED performed, exit switch
        }

        if ( strcmpi(szCmd,"GETLINECOUNT")==0 )
        {//Must be an Edit
            vResult = (int)SendMessage(util.m_ControlSearchHWND,EM_GETLINECOUNT, 0, 0);
            break;                            // GETLINECOUNT performed, exit switch
        }

        if ( strcmpi(szCmd,"GETCURRENTLINE")==0 )
        {
            vResult = (int)SendMessage(util.m_ControlSearchHWND,EM_LINEFROMCHAR, (WPARAM)-1, 0)+1;
            break;
        }

        if ( strcmpi(szCmd,"GETCURRENTCOL")==0 )
        {
            uint nStart, nEnd, nOriginal;
            int  nLine;

            SendMessage(util.m_ControlSearchHWND,EM_GETSEL,(WPARAM)&nStart,(LPARAM)&nEnd);
            nOriginal = nStart;  //the charcter index

            //Decrement the character index until the row changes
            //Difference between this char index and original is the column.

            nLine = (int)SendMessage(util.m_ControlSearchHWND,EM_LINEFROMCHAR,(WPARAM)nStart,0);
            if (nLine >= 1)
            {
                while (nLine == (int)SendMessage(util.m_ControlSearchHWND,EM_LINEFROMCHAR,(WPARAM)nStart,0))
                {
                    nStart--;
                }
                vResult = (int)nOriginal - (int)nStart;  //no off-by one error :)
            }
            else
                vResult = (int)nStart + 1;  //add 1 because first char index is 0
            break;
        }

        if ( strcmpi(szCmd,"EDITPASTE")==0 )
        {
            SendMessage(util.m_ControlSearchHWND,EM_REPLACESEL, TRUE, (LPARAM)vParams[4].szValue());
            break;
        }
        if ( strcmpi(szCmd,"GETLINE")==0 )
        {
            int nFoo;
            *((LPINT)szBuffer) = sizeof(szBuffer);

            nFoo = (int)SendMessage(util.m_ControlSearchHWND, EM_GETLINE, (WPARAM)vParams[4].nValue()-1, (LPARAM)szBuffer);
            if ( nFoo )
            {
                szBuffer[nFoo]='\0';
                vResult = szBuffer;
            }
            else
                engine->SetFuncErrorCode(1);
            break;                            // GETLINE performed, exit switch
        }

        // If we get to here, no command was matched, or there was an error during a commmand
        engine->SetFuncErrorCode(1);
        break;
    }

    Util_AttachThreadInput(util.m_WindowSearchHWND, false);

    return AUT_OK;

} // ControlCommand()


///////////////////////////////////////////////////////////////////////////////
// ControlSend()
// Needs more info in the LPARAM part of the PostMessage...
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlSend(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = 0;
        return AUT_OK;                                    // Required control not found
    }

    // Send the keys
    if (vParams.size() >= 5 && vParams[4].nValue() != 0)
        engine->oSendKeys().SendRaw(vParams[3].szValue(), util.m_ControlSearchHWND);
    else
        engine->oSendKeys().Send(vParams[3].szValue(), util.m_ControlSearchHWND);

    return AUT_OK;

} // ControlSend()


///////////////////////////////////////////////////////////////////////////////
// WinMenuSelectItem()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinMenuSelectItem(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    char    szBuffer[AUT_WINTEXTBUFFER+1];
    UINT    c,i,nCount;
    UINT    nId = 0;
    BOOL    bFound;
    HMENU    hMenu;
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        vResult = 0;                                // Default is 1
        return AUT_OK;                                // Required window not found
    }

    if ( !(hMenu = GetMenu(util.m_WindowSearchHWND)) )
    {
        vResult = 0;                                // Default is 1
        return AUT_OK;                                // Required menu not found
    }

    for (i=3; i<=iNumParams; i++)
    {
        if ( (nCount=GetMenuItemCount(hMenu))<=0)
        {
            vResult = 0;                            // Default is 1
            return AUT_OK;                            // Required menu items not found
        }
        bFound=FALSE;
        for ( c=0 ;c<=nCount-1; c++ )
        {
            GetMenuString(hMenu,c,szBuffer,AUT_WINTEXTBUFFER,MF_BYPOSITION);
            if ( strncmp(vParams[i-1].szValue(),szBuffer,strlen(vParams[i-1].szValue()))==0 )
            {
                if ( i == iNumParams )
                {
                    nId = GetMenuItemID(hMenu,c);
                    bFound=TRUE;
                    break;
                }
                else
                {
                    if ( !(hMenu = GetSubMenu(hMenu,c)) )
                    {
                        vResult = 0;                // Default is 1
                        return AUT_OK;                // Required submenu not found
                    }
                    else
                    {
                        bFound=TRUE;
                        break;
                    }
                }
            }
        }
        if ( !bFound )
        {
            vResult = 0;                            // Default is 1
            return AUT_OK;                            // ERROR
        }
    }

    if ( nId == (UINT)-1 )
        vResult = 0;                                // Default is 1
    else
    {
        Util_AttachThreadInput(util.m_WindowSearchHWND, true);
        PostMessage(util.m_WindowSearchHWND,WM_COMMAND,(WPARAM)nId,0);
        Util_AttachThreadInput(util.m_WindowSearchHWND, false);
    }

    return AUT_OK;

} // WinMenuSelectItem()


///////////////////////////////////////////////////////////////////////////////
// WinGetClassList()
// Must call Win_WindowSearchInit() first to set title and text to search for
// Gets the static text from a window
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetClassList(VectorVariant &vParams, Variant &vResult)
{
    // $var = WinGetClassList(<title>, [<text>])
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required window not found
    }

    vResult = Util_GetClassList(util.m_WindowSearchHWND);

    return AUT_OK;

} // WinGetClassList()


///////////////////////////////////////////////////////////////////////////////
// WinGetClientSize()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetClientSize(VectorVariant &vParams, Variant &vResult)
{
    RECT    rect;
    Variant    *pvTemp;
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        engine->SetFuncErrorCode(1);
        return AUT_OK;                                    // Required window not found
    }

    if ( GetClientRect(util.m_WindowSearchHWND, &rect) )    // Load the window stats
    {
        // Setup vResult as an Array to hold the 4 values we want to return
        Util_VariantArrayDim(&vResult, 2);

        pvTemp = Util_VariantArrayGetRef(&vResult, 0);    // First element
        *pvTemp = (int)(rect.right - rect.left);    // Width

        pvTemp = Util_VariantArrayGetRef(&vResult, 1);
        *pvTemp = (int)(rect.bottom - rect.top);    // Height
    }
    else
        engine->SetFuncErrorCode(1);

    return AUT_OK;

} // WinGetClientSize()


///////////////////////////////////////////////////////////////////////////////
// WinGetHandle()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetHandle(VectorVariant &vParams, Variant &vResult)
{
//    char    szTemp[65+1];            // Big enough to hold __int64
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        engine->SetFuncErrorCode(1);
        vResult = "";
        return AUT_OK;                                    // Required window not found
    }

//    sprintf(szTemp, "%p", util.m_WindowSearchHWND);
//    vResult = szTemp;

    vResult = util.m_WindowSearchHWND;

    return AUT_OK;

} // WinGetHandle()


///////////////////////////////////////////////////////////////////////////////
// ControlGetHandle()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlGetHandle(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);
    if (util.ControlSearch(vParams) == false)
    {
        vResult = "";
        return AUT_OK;                                    // Required control not found
    }

    vResult = util.m_ControlSearchHWND;

    return AUT_OK;

} // ControlGetHandle()

///////////////////////////////////////////////////////////////////////////////
// F_ControlGetFocus()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ControlGetFocus(VectorVariant &vParams, Variant &vResult)
{
    // Set default text as "" for error
    vResult = "";
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
        engine->SetFuncErrorCode(1);
    else
        util.ControlWithFocus(util.m_WindowSearchHWND, vResult);

    return AUT_OK;

} // ControlGetFocus()


///////////////////////////////////////////////////////////////////////////////
// WinGetCaretPos()
//
// pos = WinGetCaretPos()
// Gets the caret position of the foreground window
// Trying to get the caret position of a chosen window seems unreliable
// Coordinates are relative to the window its in (This gets funky in MDI's but the correct
// coordinates can be determined by some scripting to fix the offfset)
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetCaretPos(VectorVariant &vParams, Variant &vResult)
{
    POINT point, ptOrigin;
    Variant *pvTemp;
    HWND hWnd = GetForegroundWindow();

    // Doesn't work without attaching
    Util_AttachThreadInput(hWnd, true);

    if (GetCaretPos(&point) == FALSE)
        engine->SetFuncErrorCode(1);
    else
    {
        // point contains the caret pos in CLIENT area coordinates, convert to screen (absolute coords)
        // and then let the current mode decide how they will be returned
        ClientToScreen(hWnd, &point);
        WinUtil::instance.ConvertCoords(engine->nCoordCaretMode(), ptOrigin);
        point.x -= ptOrigin.x;
        point.y -= ptOrigin.y;

        Util_VariantArrayDim(&vResult, 2);

        pvTemp = Util_VariantArrayGetRef(&vResult, 0);        // First element
        *pvTemp = (int)point.x;                    // X

        pvTemp = Util_VariantArrayGetRef(&vResult, 1);
        *pvTemp = (int)point.y;                    // Y
    }

    Util_AttachThreadInput(hWnd, false);

    return AUT_OK;

} // WinGetCaretPos()


///////////////////////////////////////////////////////////////////////////////
// WinGetState()
//
// state = WinGetState("title", "text))
// 0 = not found
// 1 = exists
// 2 = visible
// 4 = enabled
// 8 = active
// 16 = minimized
// 32 = maximized
// 64 =
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetState(VectorVariant &vParams, Variant &vResult)
{
    int        nState = 1;
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        vResult = 0;                            // Default is 1
        engine->SetFuncErrorCode(1);
        return AUT_OK;
    }

    // Is it visible?
    if (IsWindowVisible(util.m_WindowSearchHWND))
        nState |= 2;

    // Is it enabled?
    if (IsWindowEnabled(util.m_WindowSearchHWND))
        nState |= 4;

    // Is it active?
    if (GetForegroundWindow() == util.m_WindowSearchHWND)
        nState |= 8;

    // Is it minimized?
    if (IsIconic(util.m_WindowSearchHWND))
        nState |= 16;

    // Is it maximized?
    if (IsZoomed(util.m_WindowSearchHWND))
        nState |= 32;

    vResult = nState;

    return AUT_OK;

} // WinGetState()



///////////////////////////////////////////////////////////////////////////////
// ToolTip()
//
// ToolTip("text", [x,y])
//
// Creates a tooltip with the specified text at any location on the screen.
// The window isn't created until it's first needed, so no resources are used until then.
// Also, the window is destroyed in ModuleWin's destructor so no resource leaks occur.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ToolTip(VectorVariant &vParams, Variant &vResult)
{
    uint iNumParam = vParams.size();

    // MingW missing some include defines
#ifndef TTF_TRACK
    #define TTF_TRACK 0x0020
    #define TTF_ABSOLUTE 0x0080
    #define TTM_SETMAXTIPWIDTH (WM_USER+24)
    #define TTM_TRACKPOSITION (WM_USER+18)
    #define TTM_TRACKACTIVATE (WM_USER+17)
#endif

    TOOLINFO ti;
    POINT  pt;

    ti.cbSize = sizeof(ti);
    ti.uFlags = TTF_TRACK | TTF_ABSOLUTE;
    ti.hwnd  = NULL;
    ti.hinst = NULL;
    ti.uId  = 0;
    ti.lpszText = (LPSTR)vParams[0].szValue();
    ti.rect.left = ti.rect.top = ti.rect.right = ti.rect.bottom = 0;

    // Set default values for the tip as the current mouse position
    GetCursorPos(&pt);
    pt.x += 16;
    pt.y += 16;

    if (iNumParam >= 2)
        pt.x = vParams[1].nValue();
    if (iNumParam >= 3)
        pt.y = vParams[2].nValue();

    if (!m_hWndTip)
    {
        m_hWndTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, TTS_NOPREFIX | TTS_ALWAYSTIP,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

        RECT dtw;
        GetWindowRect(GetDesktopWindow(), &dtw);

        SendMessage (m_hWndTip , TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO)&ti);
        SendMessage(m_hWndTip, TTM_SETMAXTIPWIDTH, 0, (LPARAM)dtw.right);
    }
    else
        SendMessage(m_hWndTip, TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);

    SendMessage (m_hWndTip , TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(pt.x, pt.y));
    SendMessage (m_hWndTip , TTM_TRACKACTIVATE, true, (LPARAM)&ti);

    return AUT_OK;

} // ToolTip()


///////////////////////////////////////////////////////////////////////////////
// WinMinimizeAll()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinMinimizeAll(VectorVariant &vParams, Variant &vResult)
{
    PostMessage(FindWindow("Shell_TrayWnd", NULL), WM_COMMAND, 419, 0);
    Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // WinMinimizeAll()


///////////////////////////////////////////////////////////////////////////////
// WinMinimizeAllUndo()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinMinimizeAllUndo(VectorVariant &vParams, Variant &vResult)
{
    PostMessage(FindWindow("Shell_TrayWnd", NULL), WM_COMMAND, 416, 0);
    Util_Sleep(engine->nWinWaitDelay());                // Briefly pause before continuing

    return AUT_OK;

} // WinMinimizeAllUndo()


///////////////////////////////////////////////////////////////////////////////
// WinSetTrans
//
// Sets the transparency of a window (Windows 2000/XP or later)
// Takes 3 parameters:
//        vParam[0] - Window Title
//        vParam[1] - Window Text
//        vParam[2] - Integer that controls the transparency
///////////////////////////////////////////////////////////////////////////////
AUT_RESULT ModuleWin::F_WinSetTrans(VectorVariant &vParams, Variant &vResult)
{
#ifndef WS_EX_LAYERED    // Only defined on Windows 2000+
    #define WS_EX_LAYERED 0x00080000
#endif
#ifndef LWA_ALPHA
    #define LWA_ALPHA 0x00000002
#endif

    typedef BOOL (WINAPI *SLWA)(HWND, COLORREF, BYTE, DWORD);    // Prototype for SetLayeredWindowAttributes()

    uint value = vParams[2].nValue() < 0 ? 0 : vParams[2].nValue();        // Valid range is 0 - 255
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);
    if (util.Win_WindowSearch() == false)
        return AUT_OK; // No window

    HMODULE hMod = LoadLibrary("user32.dll");
    if (!hMod)
        return AUT_OK;    // If this happens, we have major OS issues.

    SLWA lpSetLayeredWindowAttributes = (SLWA)GetProcAddress(hMod, "SetLayeredWindowAttributes");
    if (lpSetLayeredWindowAttributes)
    {
        LONG style = GetWindowLong(util.m_WindowSearchHWND, GWL_EXSTYLE);
        if (value >= 255 && (style & WS_EX_LAYERED))
            SetWindowLong(util.m_WindowSearchHWND, GWL_EXSTYLE, style ^ WS_EX_LAYERED);    // Remove
        else
        {
            SetWindowLong(util.m_WindowSearchHWND, GWL_EXSTYLE, style | WS_EX_LAYERED);
            lpSetLayeredWindowAttributes(util.m_WindowSearchHWND, 0, value, LWA_ALPHA);
        }
        vResult = 1;
    }
    else
        engine->SetFuncErrorCode(1);    // This means the OS isn't supported since the function wasn't loaded from the DLL
    FreeLibrary(hMod);

    return AUT_OK;

}    // WinSetTrans()

///////////////////////////////////////////////////////////////////////////////
// WinList()
//
// WinList( ["title" [, "text] )
// Gets a list of all matching windows.
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinList(VectorVariant &vParams, Variant &vResult)
{
    Variant        *pvVariant;
    char        szTitle[AUT_WINTEXTBUFFER+1];
    WinSearchUtil util(engine);

    // Matching defaults
    util.m_vWindowSearchTitle = "all";
    util.m_vWindowSearchText = "";

    if (vParams.size() == 0)
        util.m_nWindowSearchMatchMode = 4;
    else
    {
        if (vParams.size() > 0)
            util.m_vWindowSearchTitle = vParams[0].szValue();
        if (vParams.size() > 1)
            util.m_vWindowSearchText = vParams[1].szValue();
    }

    // Generate the list of matching windows (false = make list rather than stop at first match)

    util.Win_WindowSearch(false);

    // Create a 2d array big enough for all the windows, +1 for the count
    vResult.ArraySubscriptClear();                        // Reset the subscript
    vResult.ArraySubscriptSetNext(util.m_nWinListCount + 1);    // Number of elements
    vResult.ArraySubscriptSetNext(2);                    // Number of elements ([0]=title. [1]=hwnd)
    vResult.ArrayDim();                                    // Dimension array

    // Set up the count in [0][0]
    vResult.ArraySubscriptClear();                        // Reset the subscript
    vResult.ArraySubscriptSetNext(0);
    vResult.ArraySubscriptSetNext(0);                    // [0][0]
    pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
    *pvVariant = util.m_nWinListCount;                        // Store the count


    WinListNode    *lpTemp = util.m_lpWinListFirst;
    for (int i = 1; i <= util.m_nWinListCount; ++i)
    {
        // Get the window text
        GetWindowText(lpTemp->hWnd, szTitle, AUT_WINTEXTBUFFER);
        vResult.ArraySubscriptClear();                        // Reset the subscript
        vResult.ArraySubscriptSetNext(i);
        vResult.ArraySubscriptSetNext(0);                    // [i][0]
        pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
        *pvVariant = szTitle;                                // Store the title

        // Get the window handle
        vResult.ArraySubscriptClear();                        // Reset the subscript
        vResult.ArraySubscriptSetNext(i);
        vResult.ArraySubscriptSetNext(1);                    // [i][1]
        pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
        *pvVariant = lpTemp->hWnd;                            // Store the handle

        lpTemp = lpTemp->lpNext;                            // Next element
    }

    return AUT_OK;
}

///////////////////////////////////////////////////////////////////////////////
// WinGetProcess()
//
// WinGetProcess("title", "text")
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_WinGetProcess(VectorVariant &vParams, Variant &vResult)
{
    WinSearchUtil util(engine);

    util.Win_WindowSearchInit(vParams);

    if (util.Win_WindowSearch() == false)
    {
        vResult = -1;                            // Default is 1
        return AUT_OK;
    }

    DWORD    dwPid;

    GetWindowThreadProcessId(util.m_WindowSearchHWND, &dwPid);
    vResult = (int)dwPid;

    return AUT_OK;

} // WinGetProcess()
