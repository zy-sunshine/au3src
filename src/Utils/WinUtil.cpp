#include "StdAfx.h"                                // Pre-compiled headers
#include "WinUtil.h"
#include "AutoIt.h"

WinUtil g_oWinUtil = WinUtil();

//////////////////////////////////////////////////////////////////////////
// ConvertCoords()
//
// Helps convert coordinates to screen, active window and client relative
//////////////////////////////////////////////////////////////////////////

void WinUtil::ConvertCoords(int nCoordMode, POINT &pt)
{
    HWND    hFore = GetForegroundWindow();
    RECT    rect;

    if (nCoordMode == AUT_COORDMODE_WINDOW)
    {
        GetWindowRect(hFore, &rect);
        pt.x = rect.left;
        pt.y = rect.top;
    }
    else if (nCoordMode == AUT_COORDMODE_CLIENT)
    {
        pt.x = 0;
        pt.y = 0;
        ClientToScreen(hFore, &pt);
    }
    else
    {
        // Screen mode
        pt.x = 0;
        pt.y = 0;
    }

}    // ConvertCoords()

///////////////////////////////////////////////////////////////////////////////
// FormatWinError()
//
// This function retrieves the error text for the given windows error.
///////////////////////////////////////////////////////////////////////////////

const char * WinUtil::FormatWinError(DWORD dwCode)
{
    static char szBuffer[AUT_STRBUFFER+1];

    if (dwCode == 0xffffffff)
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0, szBuffer, AUT_STRBUFFER, NULL);
    else
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwCode, 0, szBuffer, AUT_STRBUFFER, NULL);

    return szBuffer;

} // FormatWinError()

