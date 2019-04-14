#include "WinUtil.h"
//////////////////////////////////////////////////////////////////////////
// ConvertCoords()
//
// Helps convert coordinates to screen, active window and client relative
//////////////////////////////////////////////////////////////////////////

void AutoIt_Script::ConvertCoords(int nCoordMode, POINT &pt)
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

