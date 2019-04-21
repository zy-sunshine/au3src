#include "StdAfx.h"
#include "WinSearchUtil.h"

WinSearchUtil::WinSearchUtil(Engine *engine)
    : engine(engine)
{
    m_WindowSearchHWND          = NULL;        // Last window found set to NULL
    m_bDetectHiddenText         = false;       // Don't detect hidden text by default
    m_bWinSearchChildren        = false;       // Only search top level windows by default

    m_lpWinListFirst            = NULL;            // First entry in window list
    m_lpWinListLast             = NULL;            // First entry in window list
    m_nWinListCount             = 0;            // Number of entries

    // may change by temp usage, so cache to local member var
    m_nWindowSearchMatchMode    = engine->nWindowSearchMatchMode();
}

WinSearchUtil::~WinSearchUtil()
{
    // Clear any WindowSearch() lists
    Win_WindowSearchDeleteList();
}

///////////////////////////////////////////////////////////////////////////////
// Win_WindowSearchInit()
///////////////////////////////////////////////////////////////////////////////

void WinSearchUtil::Win_WindowSearchInit(VectorVariant &vParams)
{
    // Parameters are title, text - only title is mandatory

    m_vWindowSearchTitle    = vParams[0];    // Title

    if (vParams.size() >= 2)
        m_vWindowSearchText    = vParams[1];    // Text
    else
        m_vWindowSearchText    = "";

} // Win_WindowSearchInit()

///////////////////////////////////////////////////////////////////////////////
// Win_WindowWaitInit()
///////////////////////////////////////////////////////////////////////////////

void WinSearchUtil::Win_WindowWaitInit(VectorVariant &vParams)
{
    // Parameters are title, text, timeout - only title is mandatory

    // Setup the search for title/text
    Win_WindowSearchInit(vParams);

    if (vParams.size() == 3)
        m_nWinWaitTimeout    = vParams[2].nValue() * 1000;    // Timeout
    else
        m_nWinWaitTimeout    = 0;


    // Make a note of current system time for comparision in timer
    m_tWinTimerStarted            = timeGetTime();

} // Win_WindowWaitInit()

///////////////////////////////////////////////////////////////////////////////
// Win_WindowSearchDeleteList()
//
// When the window search is run a list of windows matched is created, this
// function clears the list.
//
///////////////////////////////////////////////////////////////////////////////

void WinSearchUtil::Win_WindowSearchDeleteList(void)
{
    WinListNode    *lpTemp = m_lpWinListFirst;
    WinListNode    *lpNext;

    while (lpTemp)
    {
        lpNext = lpTemp->lpNext;
        delete lpTemp;
        lpTemp = lpNext;
    }

    m_lpWinListFirst    = NULL;
    m_lpWinListLast     = NULL;
    m_nWinListCount     = 0;

} // Win_WindowSearchDeleteList()

///////////////////////////////////////////////////////////////////////////////
// Win_WindowSearchAddToList()
//
// Adds a hwnd to the window list
//
///////////////////////////////////////////////////////////////////////////////

void WinSearchUtil::Win_WindowSearchAddToList(HWND hWnd)
{
    WinListNode    *lpTemp = new WinListNode;

    lpTemp->hWnd = hWnd;
    lpTemp->lpNext = NULL;

    if (m_lpWinListLast)
    {
        m_lpWinListLast->lpNext = lpTemp;
        m_lpWinListLast = lpTemp;
    }
    else
        m_lpWinListFirst = m_lpWinListLast = lpTemp;

    ++m_nWinListCount;

} // Win_WindowSearchAddToList()

///////////////////////////////////////////////////////////////////////////////
// Win_WindowSearch()
///////////////////////////////////////////////////////////////////////////////

bool WinSearchUtil::Win_WindowSearch(bool bFirstOnly)
{
    // Are we looking for all matching windows or just the first?
    m_bWindowSearchFirstOnly = bFirstOnly;

    // Clear previous search - also set number of found windows (m_nWinListCount) to 0
    Win_WindowSearchDeleteList();

    // If the Title parameter was a HWND type then we don't need to search at all
    if (m_vWindowSearchTitle.isHWND())
    {
        if (IsWindow(m_vWindowSearchTitle.hWnd()) )
        {
            m_WindowSearchHWND = m_vWindowSearchTitle.hWnd();
            Win_WindowSearchAddToList(m_WindowSearchHWND);    // Create a 1 entry list for those functions that use it
            return true;
        }
        else
            return false;
    }

    // If both title and text is blank, then assume active window
    // If we are in mode 4 then do some other checks
    if (m_nWindowSearchMatchMode == 4)
    {
        if (m_vWindowSearchTitle.szValue()[0] == '\0' || !stricmp(m_vWindowSearchTitle.szValue(), "last") )
        {
            if (m_WindowSearchHWND)                    // Make sure that there HAS been a previous match
            {
                Win_WindowSearchAddToList(m_WindowSearchHWND);    // Create a 1 entry list for those functions that use it
                return true;
            }
            else
                return false;
        }
        else if (!stricmp(m_vWindowSearchTitle.szValue(), "active") )
        {
            m_WindowSearchHWND = GetForegroundWindow();
            Win_WindowSearchAddToList(m_WindowSearchHWND);    // Create a 1 entry list for those functions that use it
            return true;
        }
        else if ( !strnicmp(m_vWindowSearchTitle.szValue(), "handle=", 7) )    // handle=
        {
            int        nTemp;

            // Assumes int32 is big enough for HWND (it currently is... 4 bytes)
            // We can always bump up to 64 if required in the future (IA64?)
            Util_ConvDec( &m_vWindowSearchTitle.szValue()[7], nTemp );
            m_WindowSearchHWND = (HWND)nTemp;

            if (IsWindow(m_WindowSearchHWND) )
            {
                Win_WindowSearchAddToList(m_WindowSearchHWND);    // Create a 1 entry list for those functions that use it
                return true;
            }
            else
                return false;
        }
    }
    else if (m_vWindowSearchTitle.szValue()[0] == '\0'  && m_vWindowSearchText.szValue()[0] == '\0' )
    {
        m_WindowSearchHWND = GetForegroundWindow();
        Win_WindowSearchAddToList(m_WindowSearchHWND);    // Create a 1 entry list for those functions that use it
        return true;
    }

    // Do the search
    if (!m_bWinSearchChildren)
        EnumWindows((WNDENUMPROC)Win_WindowSearchProc, this);
    else
        EnumChildWindows(GetDesktopWindow(), (WNDENUMPROC)Win_WindowSearchProc, this);

    if (m_nWinListCount)
    {
        // Set the m_WindowSearchHWND to the FIRST window matched to retain compability with the older code
        // that uses WindowSearch and doesn't know anything about the new WinList struct
        m_WindowSearchHWND = m_lpWinListFirst->hWnd;
        return true;
    }
    else
    {
        m_WindowSearchHWND = NULL;
        return false;
    }
}

BOOL CALLBACK WinSearchUtil::Win_WindowSearchProc(HWND hWnd, LPARAM lParam)
{
    return (WinSearchUtil*)(lParam)->Win_WindowSearchProcHandler(hWnd, lParam);
}

BOOL WinSearchUtil::Win_WindowSearchProcHandler(HWND hWnd, LPARAM lParam)
{
    char    szBuffer[1024+1] = "";                // 1024 chars is more than enough for a title

    // Get the window text
    GetWindowText(hWnd, szBuffer, 1024);

    m_WindowSearchHWND = hWnd;                    // Save the handle of the window for use in the WinTextSearch()

    switch (m_nWindowSearchMatchMode)
    {
        case 1:
            if ( !strncmp(m_vWindowSearchTitle.szValue(), szBuffer, strlen(m_vWindowSearchTitle.szValue()) ) )
            {
                if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                    return FALSE;                // No need to search any more
            }
            break;

        case 2:
            if ( strstr(szBuffer, m_vWindowSearchTitle.szValue()) != NULL )
            {
                if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                    return FALSE;                // No need to search any more
            }
            break;

        case 3:
            if ( !strcmp(szBuffer, m_vWindowSearchTitle.szValue()) )
            {
                if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                    return FALSE;                // No need to search any more
            }
            break;

        case 4:
            // valid options are "classname=", "handle=", "", "all", "regexp="
            if ( !strnicmp(m_vWindowSearchTitle.szValue(), "classname=", 10) )    // classname=
            {
                GetClassName(hWnd, szBuffer, 1024);
                if (!strcmp(szBuffer, &m_vWindowSearchTitle.szValue()[10]) )
                {
                    if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                        return FALSE;            // No need to search any more
                }
            }
            else if ( !stricmp(m_vWindowSearchTitle.szValue(), "all") )
            {
                //AUT_MSGBOX("here", "here")
                // We don't care about the title, so try matching the text
                if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                    return FALSE;                // No need to search any more
            }
            else if ( !strncmp(m_vWindowSearchTitle.szValue(), szBuffer, strlen(m_vWindowSearchTitle.szValue())) ) // Try default case 1
            {
                if ( Win_WindowSearchText() == true && m_bWindowSearchFirstOnly == true)
                    return FALSE;                // No need to search any more
            }
            break;

    } // End Switch

    return TRUE;                                // Search more

} // Win_WindowSearchProcHandler()

///////////////////////////////////////////////////////////////////////////////
// Win_WindowSearchText()
///////////////////////////////////////////////////////////////////////////////

bool WinSearchUtil::Win_WindowSearchText(void)
{
    // If the optional text is blank, always return find=yes
    if (m_vWindowSearchText.szValue()[0] == '\0')
    {
        Win_WindowSearchAddToList(m_WindowSearchHWND);
        return true;    // Found!
    }

    // If current search window seems hung then don't attempt to read it (WM_GETTEXT would hang)
    // If we are not using the WM_GETEXT mode then we don't care if it's hung as GetWindowText()
    // will cope
    if ( engine->nWindowSearchTextMode() == 1 && Util_IsWinHung(m_WindowSearchHWND) )
        return false;

    int nLastCount = m_nWinListCount;

    EnumChildWindows(m_WindowSearchHWND, (WNDENUMPROC)Win_WindowSearchTextProc, this);

    if (nLastCount != m_nWinListCount)
        return true;                            // New window matched
    else
        return false;
}

BOOL CALLBACK WinSearchUtil::Win_WindowSearchTextProc(HWND hWnd, LPARAM lParam)
{
    return (WinSearchUtil*)(lParam)->Win_WindowSearchTextProcHandler(hWnd, lParam);
}

BOOL WinSearchUtil::Win_WindowSearchTextProcHandler(HWND hWnd, LPARAM lParam)
{
    char    szBuffer[AUT_WINTEXTBUFFER+1];
    int        nLen;

    // WM_GETTEXT seems to get more info
    szBuffer[0] = '\0';                            // Blank in case of error with WM_GETTEXT

    // Hidden text?
    if ( (IsWindowVisible(hWnd)) || (m_bDetectHiddenText == true) )
    {
        if (engine->nWindowSearchTextMode() == 2)
        {
            nLen = GetWindowText(hWnd, szBuffer, AUT_WINTEXTBUFFER);    // Quicker mode
        }
        else //if (SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0) > 0)
        {
            nLen = (int)SendMessage(hWnd, WM_GETTEXT,(WPARAM)AUT_WINTEXTBUFFER,(LPARAM)szBuffer);
        }

        szBuffer[AUT_WINTEXTBUFFER] = '\0';        // Ensure terminated if large amount of return text

        if ( nLen && strstr(szBuffer, m_vWindowSearchText.szValue()) )
        {
            Win_WindowSearchAddToList(m_WindowSearchHWND);
            return FALSE;                        // No more searching needed in this window
        }

    }    // EndIf Visible

    return TRUE;                                // Carry on searching

} // Win_WindowSearchTextProcHandler()

///////////////////////////////////////////////////////////////////////////////
// Win_WinActive()
// Must call Win_WindowSearchInit() first to set title and text to search for
///////////////////////////////////////////////////////////////////////////////

bool WinSearchUtil::Win_WinActive(void)
{
    // If the window doesn't exist it can't be active
    if ( Win_WindowSearch() == false)
        return false;

    if (m_WindowSearchHWND == GetForegroundWindow())
        return true;
    else
        return false;

} // Win_WinActive()

///////////////////////////////////////////////////////////////////////////////
// Win_WinExists()
// Must call Win_WindowSearchInit() first to set title and text to search for
///////////////////////////////////////////////////////////////////////////////

bool WinSearchUtil::Win_WinExists(void)
{
    return Win_WindowSearch();

} // Win_WinExists()

///////////////////////////////////////////////////////////////////////////////
// ControlSearch() - requires a title, text and controlname
///////////////////////////////////////////////////////////////////////////////

bool WinSearchUtil::ControlSearch(VectorVariant &vParams)
{
    // Init the window search and see if it exists
    m_vWindowSearchTitle    = vParams[0];
    m_vWindowSearchText        = vParams[1];

    if (Win_WindowSearch() == false)
        return false;                            // Required window not found


    // Zero control search params
    m_vControlSearchValue        = vParams[2];    // The Control ID/Class or Text to find
    m_iControlSearchInstance    = 0;            // Variable to keep track of class instance
    m_bControlSearchFoundFlag    = false;        // Found nothing yet


    // We have a valid parent window, if the control to search for is a HWND then we can return straight away
    // This used to ignore title/text and use GetParent() but it messed up sometimes.
    if (m_vControlSearchValue.isHWND())
    {
        m_ControlSearchHWND = m_vControlSearchValue.hWnd();
        return true;
    }


    // If the class name is blank, return the main window handle as the control handle...
    if (m_vControlSearchValue.isTrue() == false)    // Blank string is false, and 0 is false
    {
        m_ControlSearchHWND = m_WindowSearchHWND;
        return true;
    }

    // If the class is a number - assume Control ID, otherwise try classnameNN and then text
    if (m_vControlSearchValue.isNumber())
    {
        m_nControlSearchMethod = AUT_CONTROLSEARCH_ID;
        EnumChildWindows(m_WindowSearchHWND, (WNDENUMPROC)ControlSearchProc, this);
    }
    else
    {
        m_nControlSearchMethod = AUT_CONTROLSEARCH_CLASS;
        EnumChildWindows(m_WindowSearchHWND, (WNDENUMPROC)ControlSearchProc, this);

        if (m_bControlSearchFoundFlag == false)
        {
            m_nControlSearchMethod = AUT_CONTROLSEARCH_TEXT;
            EnumChildWindows(m_WindowSearchHWND, (WNDENUMPROC)ControlSearchProc, this);
        }
    }

    return m_bControlSearchFoundFlag;
}

BOOL CALLBACK WinSearchUtil::ControlSearchProc(HWND hWnd, LPARAM lParam)
{
    return (WinSearchUtil*)(lParam)->ControlSearchProcHandler(hWnd, lParam);
}

BOOL WinSearchUtil::ControlSearchProcHandler(HWND hWnd, LPARAM lParam)
{
    char    szBuffer[1024+1];
    BOOL    bRes = TRUE;                        // Return TRUE to continue enumeration

    // Determine the search method to use, ClassNN, ID or Text
    if (m_nControlSearchMethod == AUT_CONTROLSEARCH_ID)
    {
        if (m_vControlSearchValue.nValue() == GetDlgCtrlID(hWnd))
            bRes = FALSE;
    }
    else if (m_nControlSearchMethod == AUT_CONTROLSEARCH_CLASS)
    {
        GetClassName(hWnd, szBuffer, 256);

        if ( strncmp(m_vControlSearchValue.szValue(), szBuffer, strlen(szBuffer)) == 0 )
        {
            m_iControlSearchInstance++;                //Control name found, increment instance

            sprintf(szBuffer, "%s%u", szBuffer, m_iControlSearchInstance);

            if ( strcmp(szBuffer, m_vControlSearchValue.szValue()) == 0 )    //Do we match control name AND num
                bRes = FALSE;
        }
    }
    else                                        // Use window text
    {
        GetWindowText(hWnd, szBuffer, 1024);

        if ( strcmp(m_vControlSearchValue.szValue(), szBuffer) == 0 )
            bRes = FALSE;
    }

    if (bRes == FALSE)
    {
        m_ControlSearchHWND            = hWnd;    // Save the hwnd of this control
        m_bControlSearchFoundFlag    = true;    // Set the found flag
    }

    return bRes;

} // ControlSearchProcHandler()

///////////////////////////////////////////////////////////////////////////////
// ControlWithFocus()
///////////////////////////////////////////////////////////////////////////////

void WinSearchUtil::ControlWithFocus(HWND hWnd, Variant &vResult)
{
    char    szClass[256];


    Util_AttachThreadInput(hWnd, true);
    m_ControlSearchHWND=GetFocus();                // Get control with focus' hWnd
    Util_AttachThreadInput(hWnd, false);

    if(!m_ControlSearchHWND)
    {
        engine->SetFuncErrorCode(1);
        return;
    }

    GetClassName(m_ControlSearchHWND, szClass, 255);
    m_vControlSearchValue        = szClass;        // Set the class to find

    m_iControlSearchInstance    = 0;            // Variable to keep track of class instance
    m_bControlSearchFoundFlag    = false;        // Found nothing yet

    EnumChildWindows(hWnd, (WNDENUMPROC)ControlWithFocusProc, 0);

    if (m_bControlSearchFoundFlag)
    {
        sprintf(szClass,"%s%d",m_vControlSearchValue.szValue(),m_iControlSearchInstance);
        vResult=szClass;
    }
    else
        engine->SetFuncErrorCode(1);

}

BOOL CALLBACK WinSearchUtil::ControlWithFocusProc(HWND hWnd, LPARAM lParam)
{
    return (WinSearchUtil*)(lParam)->ControlWithFocusProcHandler(hWnd, lParam);
}

BOOL WinSearchUtil::ControlWithFocusProcHandler(HWND hWnd, LPARAM lParam)
{
    char    szBuffer[256];

    GetClassName(hWnd, szBuffer, 255);

    if ( strcmp(m_vControlSearchValue.szValue(), szBuffer) == 0 )
    {
        m_iControlSearchInstance++;                //Control name found, increment instance

        if ( hWnd==m_ControlSearchHWND )    //Do we match control hWnd
        {
            m_bControlSearchFoundFlag    = true;    // Set the found flag
            return FALSE;                        // End the search/enumeration
        }
    }

    return TRUE;                                // Continue the search

} // ControlWithFocusProcHandler()

bool WinSearchUtil::isTimeOut()
{
    // If required, process the timeout
    if (m_nWinWaitTimeout != 0)
    {
        // Get current time in ms
        DWORD    dwDiff;
        DWORD    dwCur = timeGetTime();
        if (dwCur < m_tWinTimerStarted)
            dwDiff = (UINT_MAX - m_tWinTimerStarted) + dwCur; // timer wraps at 2^32
        else
            dwDiff = dwCur - m_tWinTimerStarted;

        // Timer elapsed?
        if (dwDiff >= m_nWinWaitTimeout)
        {
            // timeout
            return true;
        }
    }
    return false;
}
