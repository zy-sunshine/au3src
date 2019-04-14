#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleMouse.h"

///////////////////////////////////////////////////////////////////////////////
// MouseDown("button")
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseDown(VectorVariant &vParams, Variant &vResult)
{
    if (Util_MouseDown(vParams[0].szValue()) == 0)
        vResult = 0;

    return AUT_OK;

} // MouseDown()


///////////////////////////////////////////////////////////////////////////////
// MouseUp("button")
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseUp(VectorVariant &vParams, Variant &vResult)
{
    if (Util_MouseUp(vParams[0].szValue()) == 0)
        vResult = 0;

    return AUT_OK;

} // MouseUp()

///////////////////////////////////////////////////////////////////////////////
// MouseClick()
// Performs a mouse click at the requested coords
// MouseClick( "left|middle|right", [x,y] [#clicks] [speed(0-100)] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseClick(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nSpeed;
    int        nClicks, nX=0, nY=0;

    // Check for x without y
    if (iNumParams == 2)
    {
        FatalError(IDS_AUT_E_FUNCTIONNUMPARAMS);
        return AUT_ERR;
    }

    // Get coords
    if (iNumParams >= 2)
    {
        nX = vParams[1].nValue();
        nY = vParams[2].nValue();
    }

    // Get number of clicks
    if (iNumParams >= 4)
    {
        nClicks = vParams[3].nValue();
        if (nClicks <= 0)
            return AUT_OK;    // 0 or less clicks specified
    }
    else
        nClicks = 1;

    // Get speed
    if (iNumParams >= 5)
        nSpeed = vParams[4].nValue();
    else
        nSpeed = -1;                            // -1 = default speed


    // Do we need to move the mouse?
    if (iNumParams > 1)
        MouseMoveExecute(nX, nY, nSpeed);


    for (int i=0; i<nClicks; ++i)
    {
        // Do the click
        if (Util_MouseDown(vParams[0].szValue()) == 0)
        {
            // not a valid click
            vResult = 0;
            return AUT_OK;
        }
        Util_Sleep(m_nMouseClickDownDelay);
        if (Util_MouseUp(vParams[0].szValue()) == 0) {
            // not a valid click
            vResult = 0;
            return AUT_OK;
        }
        Util_Sleep(m_nMouseClickDelay);
    }

    return AUT_OK;

} // MouseClick()

///////////////////////////////////////////////////////////////////////////////
// MouseMove()
// Moves the mouse
// MouseMove( x, y [,speed(0-100)] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseMove(VectorVariant &vParams, Variant &vResult)
{
    int        nSpeed;

    if (vParams.size() == 3)
        nSpeed = vParams[2].nValue();
    else
        nSpeed = -1;                            // Force default

    MouseMoveExecute(vParams[0].nValue(), vParams[1].nValue(), nSpeed);

    return AUT_OK;

} // MouseMove()

///////////////////////////////////////////////////////////////////////////////
// MouseMoveExecute()
// Function to actually move the mouse
///////////////////////////////////////////////////////////////////////////////

void AutoIt_Script::MouseMoveExecute(int x, int y, int nSpeed)
{
    POINT    ptCur, ptOrigin;
    RECT    rect;
    int        xCur, yCur;
    int        delta;
    const    int    nMinSpeed = 32;


    // Convert coords to screen/active window/client
    ConvertCoords(m_nCoordMouseMode, ptOrigin);
    x += ptOrigin.x;
    y += ptOrigin.y;

    // Get size of desktop
    GetWindowRect(GetDesktopWindow(), &rect);

    // Sanity check coords - removed so that it works on multiple monitors where -ve values are OK
/*    if (x < 0)
        x = 0;
    else if (x > rect.right)
        x = rect.right;

    if (y < 0)
        y = 0;
    else if (y > rect.bottom)
        y = rect.bottom; */

    // Convert our coords to mouse_event coords
    x = ((65535 * x) / (rect.right-1)) + 1;
    y = ((65535 * y) / (rect.bottom-1)) + 1;


    // Are we slowly moving or insta-moving?
    if (nSpeed == 0)
    {
        mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
        Util_Sleep(10);                            // Hopefully fixes "clicks before moving" bug
        return;
    }

    // Sanity check for speed
    if (nSpeed < 0 || nSpeed > 100)
        nSpeed = 10;                            // Default is speed 10


    // So, it's a more gradual speed that is needed :)
    GetCursorPos(&ptCur);
    xCur = ((ptCur.x * 65535) / (rect.right-1)) + 1;
    yCur = ((ptCur.y * 65535) / (rect.bottom-1)) + 1;

    while (xCur != x || yCur != y)
    {
        if (xCur < x)
        {
            delta = (x - xCur) / nSpeed;
            if (delta == 0 || delta < nMinSpeed)
                delta = nMinSpeed;
            if ((xCur + delta) > x)
                xCur = x;
            else
                xCur += delta;
        }
        else
            if (xCur > x)
            {
                delta = (xCur - x) / nSpeed;
                if (delta == 0 || delta < nMinSpeed)
                    delta = nMinSpeed;
                if ((xCur - delta) < x)
                    xCur = x;
                else
                    xCur -= delta;
            }

        if (yCur < y)
        {
            delta = (y - yCur) / nSpeed;
            if (delta == 0 || delta < nMinSpeed)
                delta = nMinSpeed;
            if ((yCur + delta) > y)
                yCur = y;
            else
                yCur += delta;
        }
        else
            if (yCur > y)
            {
                delta = (yCur - y) / nSpeed;
                if (delta == 0 || delta < nMinSpeed)
                    delta = nMinSpeed;
                if ((yCur - delta) < y)
                    yCur = y;
                else
                    yCur -= delta;
            }

        mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, xCur, yCur, 0, 0);

        Util_Sleep(10);                            // 20 ms sleep inbetween moves
    }

} // MouseMoveExecute()

///////////////////////////////////////////////////////////////////////////////
// MouseGetPos()
// Returns the coords of the mouse pointer
// $array = MouseGetPos()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseGetPos(VectorVariant &vParams, Variant &vResult)
{
    POINT    pt, ptOrigin;

    GetCursorPos(&pt);

    // Convert coords to screen/active window/client
    ConvertCoords(m_nCoordMouseMode, ptOrigin);
    pt.x -= ptOrigin.x;
    pt.y -= ptOrigin.y;

    // Setup vResult as an Array to hold the 2 values we want to return
    Variant    *pvTemp;

    Util_VariantArrayDim(&vResult, 2);

    pvTemp = Util_VariantArrayGetRef(&vResult, 0);    //First element
    *pvTemp = (int)pt.x;                        // X

    pvTemp = Util_VariantArrayGetRef(&vResult, 1);
    *pvTemp = (int)pt.y    ;                        // Y

    return AUT_OK;

} // MouseGetPos()

///////////////////////////////////////////////////////////////////////////////
// MouseGetCursor()
//
// Returns the current mouse cursor 1 - 15
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseGetCursor(VectorVariant &vParams, Variant &vResult)
{
    int            a;
    HCURSOR        ciMyCursor;
    HCURSOR        hcCursor[16];
    HWND        hWnd;
    POINT        pTemp;

    hcCursor[0] = LoadCursor(0,IDC_APPSTARTING);
    hcCursor[1] = LoadCursor(0,IDC_ARROW);
    hcCursor[2] = LoadCursor(0,IDC_CROSS);
    hcCursor[3] = LoadCursor(0,IDC_HELP);
    hcCursor[4] = LoadCursor(0,IDC_IBEAM);
    hcCursor[5] = LoadCursor(0,IDC_ICON);
    hcCursor[6] = LoadCursor(0,IDC_NO);
    hcCursor[7] = LoadCursor(0,IDC_SIZE);
    hcCursor[8] = LoadCursor(0,IDC_SIZEALL);
    hcCursor[9] = LoadCursor(0,IDC_SIZENESW);
    hcCursor[10] = LoadCursor(0,IDC_SIZENS);
    hcCursor[11] = LoadCursor(0,IDC_SIZENWSE);
    hcCursor[12] = LoadCursor(0,IDC_SIZEWE);
    hcCursor[13] = LoadCursor(0,IDC_UPARROW);
    hcCursor[14] = LoadCursor(0,IDC_WAIT);

    GetCursorPos(&pTemp);
    hWnd = WindowFromPoint(pTemp);
    AttachThreadInput(GetCurrentThreadId(),GetWindowThreadProcessId(hWnd, NULL), TRUE);
    ciMyCursor = GetCursor();
    AttachThreadInput(GetCurrentThreadId(),GetWindowThreadProcessId(hWnd, NULL), FALSE);

    for ( a=0;a<=14; ++a )
    {
        if( ciMyCursor && ciMyCursor == hcCursor[a] )
            break;
    }
    if (a <= 14 )
        vResult = ++a;
    else
        vResult = 0;

    return AUT_OK;

} // MouseGetCursor()

///////////////////////////////////////////////////////////////////////////////
// MouseClickDrag()
// Performs a mouse click drag
// MouseClick( "left|middle|right", x1, y1, x2, y2, [speed(0-100)] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseClickDrag(VectorVariant &vParams, Variant &vResult)
{
    int        nSpeed;

    // Get coords
    int nX1 = vParams[1].nValue();
    int nY1 = vParams[2].nValue();
    int nX2 = vParams[3].nValue();
    int nY2 = vParams[4].nValue();

    // Get speed
    if (vParams.size() >= 6)
        nSpeed = vParams[5].nValue();
    else
        nSpeed = -1;                            // -1 = default speed

    // Move the mouse to the start position
    MouseMoveExecute(nX1, nY1, nSpeed);

    // The drag operation fails unless speed is now >=2
    if (nSpeed < 2 && nSpeed != -1)
        nSpeed = 2;

    // Do the drag operation
    if (Util_MouseDown(vParams[0].szValue()) == 0)
    {
        vResult = 0;
        return AUT_OK;
    }
    Util_Sleep(m_nMouseClickDragDelay);
    MouseMoveExecute(nX2, nY2, nSpeed);
    Util_Sleep(m_nMouseClickDragDelay);
    if (Util_MouseUp(vParams[0].szValue()) == 0)
    {
        vResult = 0;
        return AUT_OK;
    }
    Util_Sleep(m_nMouseClickDelay);

    return AUT_OK;

} // MouseClickDrag()

///////////////////////////////////////////////////////////////////////////////
// MouseWheel()
// Performs a Mouse wheel operation
// MouseWheel( "up|down", [#clicks] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_MouseWheel(VectorVariant &vParams, Variant &vResult)
{
    int        nClicks = 1;

    // Get number of clicks
    if (vParams.size() >= 2)
    {
        nClicks = vParams[1].nValue();
        if (nClicks <= 0)
            return AUT_OK;    // 0 or less clicks specified
    }


    for (int i=0; i<nClicks; ++i)
    {
        // Do the click
        if (Util_MouseWheel(vParams[0].szValue())==0)
        {
            vResult = 0;
            return AUT_OK;
        }
        Util_Sleep(m_nMouseClickDelay);
    }

    return AUT_OK;

} // MouseWheel()

