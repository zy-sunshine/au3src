#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleWin.h"
#include "Utils/WinUtil.h"
#include "InputBox.h"

///////////////////////////////////////////////////////////////////////////////
// MsgBox( type, "title", "text" [,timeout] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_MsgBox(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() == 4)
        vResult = Util_MessageBoxEx(NULL, vParams[2].szValue(), vParams[1].szValue(), (UINT)vParams[0].nValue() | MB_SETFOREGROUND, vParams[3].nValue() * 1000);
    else
        vResult = MessageBox(NULL, vParams[2].szValue(), vParams[1].szValue(), (UINT)vParams[0].nValue() | MB_SETFOREGROUND);
    return AUT_OK;

} // F_MsgBox()

///////////////////////////////////////////////////////////////////////////////
// TrayTip("title", "text", timeout, [options])
// Creates a balloon tip near the AutoIt icon with specified text, title and icon on Windows 2000 and later.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_TrayTip(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();

    if (engine->g_oVersion.IsWin2000orLater()) {

        struct MYNOTIFYICONDATA : public _NOTIFYICONDATAA { // Not wide character compliant.
            DWORD dwState;
            DWORD dwStateMask;
            CHAR   szTip[64];            // Padding the size, do not use, may cause problems.
            CHAR  szInfo[256];
            union {
                UINT  uTimeout;
                UINT  uVersion;
            };
            CHAR  szInfoTitle[64];
            DWORD dwInfoFlags;
        } nic;

        nic.cbSize    = sizeof(nic);
        nic.uFlags = 0x00000010;    // NIF_INFO
        nic.hWnd = engine->g_hWnd;
        nic.uID = AUT_NOTIFY_ICON_ID;

        strncpy(nic.szInfoTitle, vParams[0].szValue(), 63); // Emtpy title means no title.
        nic.szInfoTitle[63] = '\0';

        strncpy(nic.szInfo, vParams[1].szValue(), 255);    // Empty string doesn't display a balloon, so that's okay.
        nic.szInfo[255] = '\0';

        nic.uTimeout = vParams[2].nValue() * 1000;

        if (iNumParams > 3)
            nic.dwInfoFlags = vParams[3].nValue();
        else
            nic.dwInfoFlags = 0;

        Shell_NotifyIcon(NIM_MODIFY, &nic);
    }
    return AUT_OK;

} // TrayTip()

///////////////////////////////////////////////////////////////////////////////
// AutoItWinSetTitle()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_AutoItWinSetTitle(VectorVariant &vParams, Variant &vResult)
{
    SetWindowText(engine->g_hWnd, vParams[0].szValue());
    return AUT_OK;

} // AutoItWinSetTitle()


///////////////////////////////////////////////////////////////////////////////
// AutoItWinGetTitle()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_AutoItWinGetTitle(VectorVariant &vParams, Variant &vResult)
{
    char szTemp1[AUT_WINTEXTBUFFER+1];

    GetWindowText(engine->g_hWnd, szTemp1, AUT_WINTEXTBUFFER);
    vResult = szTemp1;
    return AUT_OK;

} // AutoItWinGetTitle()

///////////////////////////////////////////////////////////////////////////////
// PixelSearch()
// Finds a pixel of certain color within a RECT of pixels
// PixelSearch(<left>,<top>,<right>,<bottom>,<decimal pixel color> [, variation] [, step] )
//
// Variation code from based on cmallet's post on hiddensoft.com forum.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_PixelSearch (VectorVariant &vParams, Variant &vResult)
{
    uint        iNumParams = vParams.size();
    int            q,r;
    int            col;
    BYTE        red, green, blue;
    BYTE        red_low, red_high, green_low, green_high, blue_low, blue_high;
    HDC            hdc;
    RECT        relrect;
    int            nVar;
    int            nStep = 1;
    POINT        ptOrigin;

    relrect.left = vParams[0].nValue();
    relrect.top = vParams[1].nValue();
    relrect.right = vParams[2].nValue();
    relrect.bottom = vParams[3].nValue();

    // Convert coords to screen/active window/client
    WinUtil::instance.ConvertCoords(engine->nCoordPixelMode(), ptOrigin);
    relrect.left += ptOrigin.x;
    relrect.top += ptOrigin.y;
    relrect.right += ptOrigin.x;
    relrect.bottom += ptOrigin.y;


    // Get the search colour and split into components
    col        = vParams[4].nValue();                // Pixel color to find
    if (engine->bColorModeBGR() == false)
        Util_RGBtoBGR(col);                        // Get RGB color into the standard COLORREF BGR format

    red        = GetRValue(col);
    green    = GetGValue(col);
    blue    = GetBValue(col);

    // Variation required?
    if (iNumParams >= 6)
    {
        nVar = vParams[5].nValue();
        if ( nVar < 0 )
            nVar = 0;
        else if ( nVar > 0xff )
            nVar = 0xff;
    }
    else
        nVar = 0;

    // Step required?
    if (iNumParams >= 7 && vParams[6].nValue() > 1)
        nStep = vParams[6].nValue();

    // Config the variation code
    if (nVar == 0)                                // Exact match
    {
        red_low = red_high = red;
        green_low = green_high = green;
        blue_low = blue_high = blue;
    }
    else
    {
        // Prevent wrap around
        red_low = (nVar > red) ? 0 : red - nVar;
        green_low = (nVar > green) ? 0 : green - nVar;
        blue_low = (nVar > blue) ? 0 : blue - nVar;
        red_high = (nVar > 0xFF - red) ? 0xFF : red + nVar;
        green_high = (nVar > 0xFF - green) ? 0xFF : green + nVar;
        blue_high = (nVar > 0xFF - blue) ? 0xFF : blue + nVar;
    }


    hdc = GetDC(NULL);

    for( q=relrect.left; q<=relrect.right; q = q + nStep)
    {
        for( r=relrect.top; r<=relrect.bottom; r = r + nStep)
        {
            col        = GetPixel(hdc, q, r);
            red        = GetRValue(col);
            green    = GetGValue(col);
            blue    = GetBValue(col);

            if (red >= red_low && red <= red_high && green >= green_low && green <= green_high
                    && blue >= blue_low && blue <= blue_high)
            {
                // Match!
                // Setup vResult as an Array to hold the 2 values we want to return
                Variant    *pvTemp;

                Util_VariantArrayDim(&vResult, 2);

                // Convert coords to screen/active window/client
                q -= ptOrigin.x;
                r -= ptOrigin.y;

                pvTemp = Util_VariantArrayGetRef(&vResult, 0);    //First element
                *pvTemp = q;                    // X

                pvTemp = Util_VariantArrayGetRef(&vResult, 1);
                *pvTemp = r;                    // Y

                ReleaseDC(NULL,hdc);

                return AUT_OK;
            }
        }
    }
    ReleaseDC(NULL,hdc);

    engine->SetFuncErrorCode(1);            // Not found
    return AUT_OK;

} // PixelSearch()


///////////////////////////////////////////////////////////////////////////////
// PixelChecksum()
// Does an Alder32 checksum of a region of pixels
// PixelChecksum(<left>,<top>,<right>,<bottom> [,<step>])
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_PixelChecksum (VectorVariant &vParams, Variant &vResult)
{
    int                q,r;
    COLORREF        col;
    HDC                hdc;
    RECT            relrect;
    unsigned long    adler = 1L;
    unsigned long    s1, s2;
    int                nStep = 1;
    POINT            ptOrigin;

    relrect.left = vParams[0].nValue();
    relrect.top = vParams[1].nValue();
    relrect.right = vParams[2].nValue();
    relrect.bottom = vParams[3].nValue();

    // Step required?
    if (vParams.size() >= 5 && vParams[4].nValue() > 1)
        nStep = vParams[4].nValue();

    // Convert coords to screen/active window/client
    WinUtil::instance.ConvertCoords(engine->nCoordPixelMode(), ptOrigin);
    relrect.left += ptOrigin.x;
    relrect.top += ptOrigin.y;
    relrect.right += ptOrigin.x;
    relrect.bottom += ptOrigin.y;


    hdc = GetDC(NULL);

    for( q=relrect.left; q<=relrect.right; q = q + nStep)
    {
        for( r=relrect.top; r<=relrect.bottom; r = r + nStep)
        {
            col    = GetPixel(hdc, q, r);

            s1 = adler & 0xffff;
            s2 = (adler >> 16) & 0xffff;
            s1 = (s1 + GetRValue(col)) % 65521;
            s2 = (s2 + s1) % 65521;
            adler = (s2 << 16) + s1;

            s1 = adler & 0xffff;
            s2 = (adler >> 16) & 0xffff;
            s1 = (s1 + GetGValue(col)) % 65521;
            s2 = (s2 + s1) % 65521;
            adler = (s2 << 16) + s1;

            s1 = adler & 0xffff;
            s2 = (adler >> 16) & 0xffff;
            s1 = (s1 + GetBValue(col)) % 65521;
            s2 = (s2 + s1) % 65521;
            adler = (s2 << 16) + s1;
        }
    }
    ReleaseDC(NULL,hdc);

    vResult = (double)adler;

    return AUT_OK;

} // PixelChecksum()


///////////////////////////////////////////////////////////////////////////////
// PixelGetColor()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_PixelGetColor(VectorVariant &vParams, Variant &vResult)
{
    HDC        hdc;
    POINT    ptOrigin;

    int relx = vParams[0].nValue();
    int rely = vParams[1].nValue();

    // Convert coords to screen/active window/client
    WinUtil::instance.ConvertCoords(engine->nCoordPixelMode(), ptOrigin);
    relx += ptOrigin.x;
    rely += ptOrigin.y;

    if ( (hdc=GetDC(NULL)) )
    {
        int nCol = (int)GetPixel(hdc,relx,rely);

        // Convert from BGR to RGB?
        if (engine->bColorModeBGR() == false)
            Util_BGRtoRGB(nCol);

        vResult = nCol;

        ReleaseDC(NULL,hdc);
    }
    else
        engine->SetFuncErrorCode(1);

    return AUT_OK;

} // PixelGetColor()

///////////////////////////////////////////////////////////////////////////////
// SplashTextOn()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_SplashTextOn(VectorVariant &vParams, Variant &vResult)
{
    return Splash(vParams, vParams.size(), 1);

} // SplashTextOn()


///////////////////////////////////////////////////////////////////////////////
// SplashImageOn()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_SplashImageOn(VectorVariant &vParams, Variant &vResult)
{
    return Splash(vParams, vParams.size(), 0);

} // SplashImageOn()


///////////////////////////////////////////////////////////////////////////////
// SplashOff()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_SplashOff(VectorVariant &vParams, Variant &vResult)
{
    return Splash(vParams, vParams.size(), 2);

} // SplashOff()


///////////////////////////////////////////////////////////////////////////////
// Splash()
//
// SplashText and SplashImage handler
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::Splash(VectorVariant &vParams, uint iNumParams, int nFlag)
{
    int        W = 500;
    int        H = 400;
    int        L = -1;
    int        T = -1;
    int        lblstyle = WS_CHILD|WS_VISIBLE|SS_CENTER;
    int        style = WS_DISABLED|WS_POPUP|WS_CAPTION;
    int        xstyle = WS_EX_TOPMOST;
    HWND    hWnd;
    RECT    rect;

    if (engine->g_hWndSplash)                // If it exists, kill it...
    {
        if (engine->g_hSplashBitmap)
        {
            DeleteObject(engine->g_hSplashBitmap);
            engine->g_hSplashBitmap = NULL;
        }
        DestroyWindow(engine->g_hWndSplash);
        engine->g_hWndSplash = NULL;        // Reset to a NULL state
    }

    if (nFlag==2)                    // SplashOff()
        return AUT_OK;

    GetWindowRect(GetDesktopWindow(),&rect);    // Get Desktop rect

    if (iNumParams >= 3 && !(vParams[2].nValue()==-1))
        W = vParams[2].nValue();                // Optional width selected
    if (iNumParams >= 4 && !(vParams[3].nValue()==-1))
        H = vParams[3].nValue();                // Optional height selected
    if (iNumParams >= 5 )
        L = vParams[4].nValue();                // Optional left position selected
    if (iNumParams >= 6 )
        T = vParams[5].nValue();                // Optional top position selected
    if (iNumParams >= 7 && vParams[6].nValue() != -1)
    {    ////////////////////////// EXTENDED SPLASH OPTIONS
        if ( nFlag == 1 )                        // SplashText only (not SplashImage)
        {
            if ( vParams[6].nValue() & 8 )
                lblstyle = WS_CHILD|WS_VISIBLE|SS_RIGHT;        // Right justify text
            if ( vParams[6].nValue() & 4 )
            {
                if ( lblstyle & SS_RIGHT )
                    lblstyle = WS_CHILD|WS_VISIBLE|SS_CENTER;    //Chose left and right, so center it
                else
                    lblstyle = WS_CHILD|WS_VISIBLE|SS_LEFT;        // Left justify text
            }
        }
        if ( vParams[6].nValue() & 2 )
            xstyle=0;            // Selected a Not topmost window

        if ( vParams[6].nValue() & 1 )                    // Selected a window
            style = WS_DISABLED|WS_POPUP|WS_BORDER;        // Without a title bar. (border for aethetics)

        if (vParams[6].nValue() & 16)
            style ^= WS_DISABLED;                // Clear the WS_DISABLED flag
    }
    if ( L == -1 )
        L = (rect.right - W)/2;            // Center splash horizontally
    if ( T == -1 )
        T = (rect.bottom - H)/2;        // Center splash vertically

    SetRect (&rect, 0, 0, W, H);
    AdjustWindowRectEx (&rect, style, FALSE, xstyle);

    // CREATE Main Splash Window
    engine->g_hWndSplash = CreateWindowEx(xstyle,AUT_APPCLASS,vParams[0].szValue(),
        style,L,T,rect.right-rect.left,rect.bottom-rect.top,engine->g_hWnd,NULL,NULL,NULL);

    GetClientRect(engine->g_hWndSplash,&rect);    // get the client size

    if ( nFlag==0 )    // SplashImage()
    {
        HANDLE        hFile;
        HBITMAP        hBitmap;
        DWORD        dwFileSize, dwBytesRead;
        LPPICTURE    gpPicture = NULL;
        LPVOID        pvData;
        LPSTREAM    pstm;
        HGLOBAL        hGlobal;

        // CREATE static full size of client area
        hWnd = CreateWindowEx(0,"static",NULL,WS_CHILD|WS_VISIBLE|SS_BITMAP
            ,0,0,rect.right-rect.left,rect.bottom-rect.top,engine->g_hWndSplash,NULL,NULL,NULL);
        // JPG,BMP,WMF,ICO,GIF FILE HERE
        hFile=CreateFile(vParams[1].szValue(),GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);

        if ( hFile == INVALID_HANDLE_VALUE )
        {
            //engine->FatalError(IDS_AUT_E_PICFILENOTFOUND);
            return AUT_OK;                        // File does NOT exist
        }

        dwFileSize = GetFileSize(hFile,NULL);

        hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);                    //
        pvData = GlobalLock(hGlobal);                                        //
        ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);            // Gnarly picture massaging
        GlobalUnlock(hGlobal);                                            //
        CloseHandle(hFile);                                                //
        CreateStreamOnHGlobal(hGlobal,TRUE,&pstm);                        //
        OleLoadPicture(pstm,0,FALSE,IID_IPicture,(LPVOID*)&gpPicture);    //

        // Now we have our IPicture OLE object we don't need the stream stuff anymore
        pstm->Release();
        GlobalFree(hGlobal);

        if (gpPicture == NULL)
            return AUT_OK;                        // Something went wrong trying to get this image

        gpPicture->get_Handle((OLE_HANDLE*)&hBitmap);

        // Get a copy of the actual bitmap date from the OLE object
        hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

        // Now we can release the IPicture OLE object
        gpPicture->Release();

        SendMessage(hWnd,STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hBitmap);    // Set picture
        engine->g_hSplashBitmap = hBitmap;                // Make a note so we can free the memory later
        SetWindowPos(hWnd,HWND_TOP,0,0,rect.right-rect.left,rect.bottom-rect.top,SWP_DRAWFRAME);                            //
    }
    else    // SplashText()
    {
        char    szFont[65];
        int        CyPixels ,nSize = 12, nWeight = 400;
        HFONT    hfFont;
        HDC        h_dc;

        // CREATE static label full size of client area
        hWnd = CreateWindowEx(0,"static",vParams[1].szValue(),lblstyle,
            0,0,rect.right-rect.left,rect.bottom-rect.top,engine->g_hWndSplash,NULL,NULL,NULL);

        h_dc = CreateDC("DISPLAY", NULL, NULL, NULL);                    //
        SelectObject(h_dc,(HFONT)GetStockObject(DEFAULT_GUI_FONT));        // Get Default Font Name
        GetTextFace(h_dc, 64, szFont);                                    //
        CyPixels = GetDeviceCaps(h_dc,LOGPIXELSY);                        // For Some Font Size Math
        DeleteDC(h_dc);

        if ( iNumParams>=8 )
        {
            if ( strlen(vParams[7].szValue()) >= 1 )
            strcpy(szFont,vParams[7].szValue());        // Font Name
        }
        if ( iNumParams>=9 )
        {
            if ( vParams[8].nValue() >= 6 )
                nSize = vParams[8].nValue();            // Font Size
        }
        if ( iNumParams>=10 )
        {
            if ( vParams[9].nValue() >= 0 && vParams[9].nValue() <= 1000 )
            nWeight = vParams[9].nValue();                // Font Weight
        }

        hfFont = CreateFont(0-(nSize*CyPixels)/72,0,0,0,nWeight,0,0,0,DEFAULT_CHARSET,
            OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FF_DONTCARE,szFont);        // Create Font
        SendMessage(hWnd,WM_SETFONT,(WPARAM)hfFont,MAKELPARAM(TRUE,0));                    // Do Font
    }

    ShowWindow(engine->g_hWndSplash,SW_SHOWNOACTIVATE);                // Show the Splash

    return AUT_OK;

} // Splash()


///////////////////////////////////////////////////////////////////////////////
// ProgressOn()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ProgressOn(VectorVariant &vParams, Variant &vResult)
{
    return Progress(vParams, vParams.size(), 0);

} // ProgressOn()


///////////////////////////////////////////////////////////////////////////////
// ProgressOff()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ProgressOff(VectorVariant &vParams, Variant &vResult)
{
    return Progress(vParams, vParams.size(), 1);

} // ProgressOff()


///////////////////////////////////////////////////////////////////////////////
// ProgressSet()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_ProgressSet(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();

    if (engine->g_hWndProgBar != NULL)
    {
        if ( vParams[0].nValue() >= 0 && vParams[0].nValue() < 101 )
            SendMessage(engine->g_hWndProgBar,PBM_SETPOS,(WPARAM)vParams[0].nValue(),(LPARAM)0);
        if ( iNumParams >= 2 && vParams[1].szValue()[0] != '\0' )
            SendMessage(engine->g_hWndProgLblB,WM_SETTEXT,0,(LPARAM)vParams[1].szValue());
        if (iNumParams > 2)
            SendMessage(engine->g_hWndProgLblA,WM_SETTEXT,0,(LPARAM)vParams[2].szValue());
    }
    return AUT_OK;

} // ProgressSet()


///////////////////////////////////////////////////////////////////////////////
// Progress()
//
// ProgressBar handler
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT    ModuleWin::Progress(VectorVariant &vParams, uint iNumParams, int nFlag)
{
    int            L = -1;                                        // Splash Left
    int            T = -1;                                        // Splash Top
    int            W, H, CyPixels;                                // Window Width and Height
    int            style = WS_DISABLED|WS_POPUP|WS_CAPTION;    // Default window style
    int            xstyle = WS_EX_TOPMOST;
    AString        sLabelB = "";
    RECT        rect;
    HDC            h_dc;
    HFONT        hfFont;
    char        szFont[65];

    if (engine->g_hWndProgress)            // If it exists, kill it...
    {
        DestroyWindow(engine->g_hWndProgress);
        engine->g_hWndProgress = NULL;    // Reset to a NULL state in case we exit below
    }

    if (nFlag==1)                // ProgressOff()
        return AUT_OK;

    H = 100;    // Progress window size (was 78 +)
    W = 300;                                    //

    if ( iNumParams >= 3 )
        sLabelB = vParams[2].szValue();        // optional sub text
    if ( iNumParams >= 4 )
        L = vParams[3].nValue();            // optional Left position
    if ( iNumParams >= 5 )
        T = vParams[4].nValue();            // optional Top position
    if ( iNumParams >= 6 )
    {
        if ( vParams[5].nValue() & 1 )
            style ^= WS_CAPTION;                // optional No title - remove WS_CAPTION

        if ( vParams[5].nValue() & 2 )            // optional Not on top - remove WS_EX_TOPMOST
            xstyle ^= WS_EX_TOPMOST;

        if ( vParams[5].nValue() & 16 )            // optional moveable - remove WS_DISABLED flag
            style ^= WS_DISABLED;
    }

    SystemParametersInfo(SPI_GETWORKAREA,0,&rect,0);    // Get Desktop rect
    if ( L == -1 )
        L = (rect.right - W)/2;                            // Center Horizontally
    if ( T == -1 )
        T = (rect.bottom - H)/2;                        // Center Vertically

    SetRect (&rect, 0, 0, W, H);
    AdjustWindowRectEx (&rect, style, FALSE, xstyle);

    // CREATE Main Progress Window
    engine->g_hWndProgress = CreateWindowEx(xstyle,AUT_APPCLASS,vParams[0].szValue(),
        style,L,T,rect.right-rect.left,rect.bottom-rect.top,engine->g_hWnd,NULL,NULL,NULL);

    GetClientRect(engine->g_hWndProgress,&rect);                // for some math

    // CREATE Main label
    engine->g_hWndProgLblA = CreateWindowEx(0,"static",vParams[1].szValue(),WS_CHILD|WS_VISIBLE|SS_LEFT,
        (rect.right-rect.left-281),4,1280,24,engine->g_hWndProgress,NULL,NULL,NULL);

    h_dc = CreateDC("DISPLAY", NULL, NULL, NULL);                    //
    SelectObject(h_dc,(HFONT)GetStockObject(DEFAULT_GUI_FONT));        // Get Default Font Name
    GetTextFace(h_dc, 64, szFont);                                    //
    CyPixels = GetDeviceCaps(h_dc,LOGPIXELSY);            // For Some Font Size Math
    DeleteDC(h_dc);

    hfFont = CreateFont(0-(10*CyPixels)/72,0,0,0,600,0,0,0,DEFAULT_CHARSET,                // Create a bigger
        OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,PROOF_QUALITY,FF_DONTCARE,szFont);            // bolder default
    SendMessage(engine->g_hWndProgLblA,WM_SETFONT,(WPARAM)hfFont,MAKELPARAM(TRUE,0));            // GUI font.

    // CREATE Progress control
    engine->g_hWndProgBar = CreateWindowEx(WS_EX_CLIENTEDGE,"msctls_progress32",NULL,WS_CHILD|WS_VISIBLE|PBS_SMOOTH,
        (rect.right-rect.left-260)/2,30,260,20, engine->g_hWndProgress, NULL,NULL,NULL);
    SendMessage(engine->g_hWndProgBar,PBM_SETRANGE,0,MAKELONG(0,100));    //
    SendMessage(engine->g_hWndProgBar,PBM_SETSTEP,1,0);                    // set some characteristics

    // CREATE Sub label
    engine->g_hWndProgLblB = CreateWindowEx(0,"static",sLabelB.c_str(),WS_CHILD|WS_VISIBLE|SS_LEFT,
        (rect.right-rect.left-280),55,1280,50,engine->g_hWndProgress,NULL,NULL,NULL);
    SendMessage(engine->g_hWndProgLblB,WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(TRUE,0));

    ShowWindow(engine->g_hWndProgress,SW_SHOWNOACTIVATE);                // Show the Progress

    return AUT_OK;

} // Progress()

///////////////////////////////////////////////////////////////////////////////
// InputBox()
// InputBox("Title", "Prompt" [, "Default" [, "Password" [, Width, Height [, Left, Top]]]]
// Gets user input text
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleWin::F_InputBox(VectorVariant &vParams, Variant &vResult)
{
    uint        iNumParams = vParams.size();
    int            iRetVal, i, iTmp;
    double        fTmp;
    char        cTmp;
    CInputBox    aDlg(engine);

    switch (iNumParams) {
        case 9: // timeout
             fTmp = vParams[8].nValue();
             if (fTmp <= 0.0)
                 fTmp = -1.0;    // sentinal value for invalid value
             aDlg.m_timeout = fTmp;

        case 8: // with left & top
            aDlg.m_top = vParams[7].nValue();
            aDlg.m_left = vParams[6].nValue();

        case 6: // with width & height
            aDlg.m_height = vParams[5].nValue();
            aDlg.m_width = vParams[4].nValue();

        case 4:    // with password
            cTmp = vParams[3].szValue()[0];
             if (cTmp != '\0' && !Util_IsSpace(cTmp))
                 aDlg.m_password = cTmp;
            if (cTmp != '\0')
                for (i=1; (cTmp = vParams[3].szValue()[i])!= '\0'; ++i) {
                    switch (cTmp) {
                    case 'M': case 'm':
                        // maditory
                        aDlg.m_flags |= aDlg.ibf_notnull;
                        break;
                    case '0': case '1': case '2': case '3':
                    case '4': case '5': case '6': case '7':
                    case '8': case '9': // digits for maximum line length
                         iTmp = vParams[3].szValue()[i] - '0'; // store digit value;
                         while (isdigit(vParams[3].szValue()[i+1]))
                             iTmp = iTmp * 10 + vParams[3].szValue()[++i]-'0';
                         aDlg.m_maxlen=iTmp;
                        break;
                    default:
                        engine->SetFuncErrorCode(3);
                        return AUT_OK;
                    } // switch cTmp
                } // for i

        case 3: // with default
            aDlg.m_strInputText = vParams[2].szValue();

        case 2:    // title and prompt only
            aDlg.m_title = vParams[0].szValue();
            aDlg.m_strPrompt = vParams[1].szValue();
            iRetVal = aDlg.DoModal(engine->g_hInstance, NULL);

            if (iRetVal==IDOK)
                vResult = aDlg.m_strInputText.c_str();
            else if (iRetVal == IDCANCEL) {
                engine->SetFuncErrorCode(1);    // cancel pressed
                vResult = "";
            } else if (iRetVal == IDABORT) { // timeout
                 engine->SetFuncErrorCode(2);
                 vResult = "";
            } else {
                engine->SetFuncErrorCode(3);    // error creating dialog
                vResult = "";
            }
            return AUT_OK;

        default:
             // Check for x without y, width without height
             engine->FatalError(IDS_AUT_E_FUNCTIONNUMPARAMS);
             return AUT_ERR;
    }
} // InputBox()
