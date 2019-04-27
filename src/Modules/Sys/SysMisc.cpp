#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleSys.h"
#include "Engine/Engine.h"
#include "Utils/SendKeys.h"
#include "Utils/OSVersion.h"

///////////////////////////////////////////////////////////////////////////////
// EnvGet()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_EnvGet(VectorVariant &vParams, Variant &vResult)
{
    char    szEnvValue[AUT_MAX_ENVSIZE+1];        // Env variable value

    szEnvValue[0] = '\0';                        // Terminate in case the Get function fails
    GetEnvironmentVariable(vParams[0].szValue(), szEnvValue, AUT_MAX_ENVSIZE);

    vResult = szEnvValue;

    return AUT_OK;

} // EnvGet()


///////////////////////////////////////////////////////////////////////////////
// EnvSet()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_EnvSet(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() >= 2)
        SetEnvironmentVariable(vParams[0].szValue(), vParams[1].szValue());
    else
        SetEnvironmentVariable(vParams[0].szValue(), NULL);

    return AUT_OK;

} // EnvSet()

///////////////////////////////////////////////////////////////////////////////
// EnvUpdate()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_EnvUpdate(VectorVariant &vParams, Variant &vResult)
{
    DWORD_PTR nResult;

    if(SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment",
            SMTO_BLOCK, 15000, &nResult)==0)
        engine->SetFuncErrorCode(1);

    return AUT_OK;

} // EnvUpdate()

///////////////////////////////////////////////////////////////////////////////
// Sleep(ms)
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_Sleep(VectorVariant &vParams, Variant &vResult)
{
    // Handle sleep 0 as a special
    if (vParams[0].nValue() <= 0)
        ::Sleep(0);
    else
    {
        int tWinTimerStarted    = timeGetTime();    // Using the WinWait timer - go fig.
        int nWinWaitTimeout    = vParams[0].nValue();
        while (true) {
            // Idle a little to remove CPU usage
            Sleep(AUT_IDLE);
            engine->processEvents();

            // If required, process the timeout
            if (nWinWaitTimeout != 0)
            {
                // Get current time in ms
                DWORD    dwDiff;
                DWORD    dwCur = timeGetTime();
                if (dwCur < tWinTimerStarted)
                    dwDiff = (UINT_MAX - tWinTimerStarted) + dwCur; // timer wraps at 2^32
                else
                    dwDiff = dwCur - tWinTimerStarted;

                // Timer elapsed?
                if (dwDiff >= nWinWaitTimeout)
                {
                    break;
                }
            }
        }
    }

    return AUT_OK;

} // Sleep()

///////////////////////////////////////////////////////////////////////////////
// BlockInput()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_BlockInput(VectorVariant &vParams, Variant &vResult)
{

typedef void (CALLBACK *BlockInput)(BOOL);

    // Must be running 2000/ win98 for this function to be successful
    // We must dynamically load the function to retain compatibility with Win95

    // Get a handle to the DLL module that contains BlockInput
    HINSTANCE hinstLib = LoadLibrary("user32.dll");

    // If the handle is valid, try to get the function address.
    if (hinstLib != NULL)
    {
        BlockInput lpfnDLLProc = (BlockInput)GetProcAddress(hinstLib, "BlockInput");

        if (lpfnDLLProc != NULL)
        {
            if (vParams[0].nValue() == 0)
                (*lpfnDLLProc)(FALSE);
            else
                (*lpfnDLLProc)(TRUE);
        }

        // Free the DLL module.
        FreeLibrary(hinstLib);
    }

    return AUT_OK;

} // BlockInput()

///////////////////////////////////////////////////////////////////////////////
// AdlibDisable()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_AdlibDisable(VectorVariant &vParams, Variant &vResult)
{
    engine->setAdlibEnabled(false);
    return AUT_OK;

} // AdlibDisable()


///////////////////////////////////////////////////////////////////////////////
// AdlibEnable()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_AdlibEnable(VectorVariant &vParams, Variant &vResult)
{
    int        nTemp1, nTemp2, nTemp3, nTemp4;
    engine->setAdlibEnabled(false);            // Disable by default in case of error

    // Check that this user function exists
    if (engine->FindUserFunction(vParams[0].szValue(), nTemp1, nTemp2, nTemp3, nTemp4) == false)
    {
        engine->FatalError(IDS_AUT_E_UNKNOWNUSERFUNC);
        return AUT_ERR;
    }
    else
    {
        engine->setAdlibFuncName(vParams[0].szValue());
        engine->setAdlibTimerStarted(timeGetTime());

        if (vParams.size() == 2 && vParams[1].nValue() > 0)
            engine->setAdlibTimeout(vParams[1].nValue());
        else
            engine->setAdlibTimeout(AUT_ADLIB_DELAY);

        engine->setAdlibEnabled(true);
    }

    return AUT_OK;

} // AdlibEnable()

///////////////////////////////////////////////////////////////////////////////
// ClipGet()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ClipGet(VectorVariant &vParams, Variant &vResult)
{
    // $var = ClipGet()

    if (IsClipboardFormatAvailable(CF_TEXT))
    {
        OpenClipboard(engine->g_hWnd);
        HGLOBAL hClipMem = GetClipboardData(CF_TEXT);
        if (hClipMem == NULL)
        {
            engine->SetFuncErrorCode(1);                // Default is 0
            return AUT_OK;
        }

        PSTR pClipMem = (char *)GlobalLock(hClipMem);
        if (pClipMem == NULL)
        {
            CloseClipboard();
            engine->SetFuncErrorCode(1);                // Default is 0
            return AUT_OK;
        }

        vResult = pClipMem;                        // Copy the text to result
        GlobalUnlock(hClipMem);
        CloseClipboard();
    }
    else
        engine->SetFuncErrorCode(1);                    // Default is 0

    return AUT_OK;

} // ClipGet()


///////////////////////////////////////////////////////////////////////////////
// ClipPut()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ClipPut(VectorVariant &vParams, Variant &vResult)
{
    // ClipPut(<text>)

    HGLOBAL hClipMem = GlobalAlloc(GMEM_MOVEABLE, strlen(vParams[0].szValue())+1);
    if (hClipMem == NULL)
    {
        vResult = 0;                            // Default is 1
        return AUT_OK;
    }

    PSTR pClipMem = (char *)GlobalLock(hClipMem);
    if (pClipMem == NULL)
    {
        vResult = 0;                            // Default is 1
        return AUT_OK;
    }

    strcpy( pClipMem, vParams[0].szValue() );    // Store the data
    GlobalUnlock(hClipMem);

    OpenClipboard(engine->g_hWnd);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hClipMem);
    CloseClipboard();

    return AUT_OK;

} // ClipPut()

///////////////////////////////////////////////////////////////////////////////
// IsAdmin()
//
// IsAdmin()
// Returns 1 if current user has admin rights (or is running 9x).
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_IsAdmin(VectorVariant &vParams, Variant &vResult)
{
    vResult = 0;                                // Set default

    if (g_oVersion.IsWin9x())
    {
        vResult = 1;
        return AUT_OK;
    }

    // Running NT, check rights

    SC_HANDLE h = OpenSCManager( NULL, NULL, SC_MANAGER_LOCK );
    if ( h )
    {
        SC_LOCK lock = LockServiceDatabase( h ) ;
        if ( lock )
        {
            UnlockServiceDatabase( lock ) ;
            vResult = 1 ;
        }
        else
        {
            DWORD lastErr = GetLastError() ;
            if ( lastErr == ERROR_SERVICE_DATABASE_LOCKED )
                vResult = 1;
        }
        CloseServiceHandle( h ) ;
    }
    return AUT_OK;

} // IsAdmin()

///////////////////////////////////////////////////////////////////////////////
// SetError()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_SetError(VectorVariant &vParams, Variant &vResult)
{
    engine->SetFuncErrorCode(vParams[0].nValue());
    return AUT_OK;

} // SetError()


///////////////////////////////////////////////////////////////////////////////
// SetExtended()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_SetExtended(VectorVariant &vParams, Variant &vResult)
{
    engine->SetFuncExtCode(vParams[0].nValue());
    return AUT_OK;

} // SetError()

///////////////////////////////////////////////////////////////////////////////
// Break()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_Break(VectorVariant &vParams, Variant &vResult)
{
    if (vParams[0].nValue() == 0)
        engine->g_bBreakEnabled = false;
    else
        engine->g_bBreakEnabled = true;
    return AUT_OK;

} // Break()

///////////////////////////////////////////////////////////////////////////////
// AutoItSetOption("option", value)
// Sets various parameters (systray icon, title match modes, mouse modes etc)
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_AutoItSetOption(VectorVariant &vParams, Variant &vResult)
{
    const char *szOption = vParams[0].szValue();
    int            nValue = vParams[1].nValue();

    if ( !stricmp(szOption, "CaretCoordMode") )                // CaretCoordMode
    {
        vResult = (int)engine->nCoordCaretMode();    // Store current value
        engine->setCoordCaretMode(nValue);
    }
    else if ( !stricmp(szOption, "ColorMode") )                // ColorMode
    {
        vResult = (int)engine->bColorModeBGR();

        if (nValue == 0)
        {
            engine->setColorModeBGR(false);

            #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
                engine->g_oGUI.m_bColorModeBGR = false;
            #endif
        }
        else
        {
            engine->setColorModeBGR(true);
            #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
                engine->g_oGUI.m_bColorModeBGR = true;
            #endif
        }
    }
    else if ( !stricmp(szOption, "FtpBinaryMode") )            // GUICoordMode
    {
        vResult = (int)engine->bFtpBinaryMode();    // Store current value

        if (nValue == 0)
            engine->setFtpBinaryMode(false);
        else
            engine->setFtpBinaryMode(true);
    }
    else if ( !stricmp(szOption, "GUICloseOnESC") )            // GUICloseOnESC
    {
        #ifdef AUT_CONFIG_GUI                                // Is GUI enabled?
            vResult = engine->g_oGUI.m_bCloseOnESC;
            if (nValue == 0 )
                engine->g_oGUI.m_bCloseOnESC = false;
            else
                engine->g_oGUI.m_bCloseOnESC = true;
        #endif
    }
    else if ( !stricmp(szOption, "GUICoordMode") )            // GUICoordMode
    {
        #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
            vResult = engine->g_oGUI.m_nGUICoordMode;
            if (nValue >= 0 && nValue <= 2)
                engine->g_oGUI.m_nGUICoordMode = nValue;
            else
                engine->g_oGUI.m_nGUICoordMode = 1;
        #endif
    }
    else if ( !stricmp(szOption, "GUIOnEventMode") )    // GUIOnEventMode
    {
        #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
            vResult = (int)engine->g_oGUI.m_bGuiEventEnabled;
        if (nValue == 0)
            engine->g_oGUI.m_bGuiEventEnabled = false;
        else
            engine->g_oGUI.m_bGuiEventEnabled = true;
        #endif
    }
    else if ( !stricmp(szOption, "GUIResizeMode") )            // GUIResizeMode
    {
        #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
            vResult = engine->g_oGUI.m_nGUIResizeMode;
            if (nValue >= 0 && nValue < 1023)
                engine->g_oGUI.m_nGUIResizeMode = nValue;
            else
                engine->g_oGUI.m_nGUIResizeMode = 0;
        #endif
    }
/*    else if ( !stricmp(szOption, "GuiTaskbarEntry") )        // GuiTaskbarEntry
    {
        #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
            vResult = engine->g_oGUI.m_bGuiTaskbarEntry;
            if (nValue >= 0 && nValue <= 2)
                engine->g_oGUI.m_bGuiTaskbarEntry = (nValue!=0);
            else
                engine->g_oGUI.m_bGuiTaskbarEntry = false;
        #endif
    }
    else if ( !stricmp(szOption, "GuiTrayMode") )            // GuiTrayMode
    {
        #ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
            vResult = engine->g_oGUI.m_nGUITrayMode;
            if (nValue >= 1 && nValue <= 4)
            {
                engine->g_oGUI.m_nGUITrayMode = nValue;
                if (engine->g_oGUI.m_bGUIDisplayed && nValue == 4)    // mode 4 only for start in tray
                    nValue = 1;
            }
            else
                engine->g_oGUI.m_nGUITrayMode = 0;    // default
        #endif
    }
*/    else if ( !stricmp(szOption, "ExpandEnvStrings") )        // ExpandEnvStrings
    {
        vResult = (int)engine->bExpandEnvStrings();    // Store current value

        if (nValue == 0)
            engine->setExpandEnvStrings(false);
        else
            engine->setExpandEnvStrings(true);
    }
    else if ( !stricmp(szOption, "ExpandVarStrings") )        // ExpandEnvStrings
    {
        vResult = (int)engine->bExpandVarStrings();    // Store current value

        if (nValue == 0)
            engine->setExpandVarStrings(false);
        else
            engine->setExpandVarStrings(true);
    }
    else if ( !stricmp(szOption, "MouseClickDelay") )        // MouseClickDelay
    {
        vResult = (int)engine->nMouseClickDelay();    // Store current value

        if (nValue >= 0)
            engine->setMouseClickDelay(nValue);
    }
    else if ( !stricmp(szOption, "MouseClickDownDelay") )    // MouseClickDownDelay
    {
        vResult = (int)engine->nMouseClickDownDelay();    // Store current value

        if (nValue >= 0)
            engine->setMouseClickDownDelay(nValue);
    }
    else if ( !stricmp(szOption, "MouseClickDragDelay") )    // MouseClickDragDelay
    {
        vResult = (int)engine->nMouseClickDragDelay();    // Store current value

        if (nValue >= 0)
            engine->setMouseClickDragDelay(nValue);
    }
    else if ( !stricmp(szOption, "MouseCoordMode") )        // MouseCoordMode
    {
        vResult = (int)engine->nCoordMouseMode();    // Store current value
        engine->setCoordMouseMode(nValue);
    }
    else if ( !stricmp(szOption, "MustDeclareVars") )        // MustDeclareVars
    {
        vResult = (int)engine->bMustDeclareVars();    // Store current value

        if (nValue == 0)
            engine->setMustDeclareVars(false);
        else
            engine->setMustDeclareVars(true);
    }
    else if ( !stricmp(szOption, "OnExitFunc") )            // OnExitFunc
    {
        vResult = engine->sOnExitFunc().c_str();    // Store current value
        engine->setOnExitFunc(vParams[1].szValue());

    }
    else if ( !stricmp(szOption, "PixelCoordMode") )        // PixelCoordMode
    {
        vResult = (int)engine->nCoordPixelMode();    // Store current value
        engine->setCoordPixelMode(nValue);
    }
    else if ( !stricmp(szOption, "RunErrorsFatal") )        // RunErrorsFatal
    {
        vResult = (int)engine->bRunErrorsFatal();    // Store current value

        if (nValue == 0)
            engine->setRunErrorsFatal(false);
        else
            engine->setRunErrorsFatal(true);
    }
    else if ( !stricmp(szOption, "SendAttachMode") )        // SendAttachMode
    {
        vResult = (int)engine->g_oSendKeys->m_bAttachMode;    // Store current value

        if (nValue == 0)
            engine->g_oSendKeys->SetAttachMode(false);
        else
            engine->g_oSendKeys->SetAttachMode(true);
    }
    else if ( !stricmp(szOption, "SendCapslockMode") )        // SendCapslockMode
    {
        vResult = (int)engine->g_oSendKeys->m_bStoreCapslockMode;    // Store current value

        if (nValue == 0)
            engine->g_oSendKeys->SetStoreCapslockMode(false);
        else
            engine->g_oSendKeys->SetStoreCapslockMode(true);
    }
    else if ( !stricmp(szOption, "SendKeyDelay") )            // SendKeyDelay
    {
        vResult = (int)engine->g_oSendKeys->m_nKeyDelay;    // Store current value

        if (nValue >= -1)
            engine->g_oSendKeys->SetKeyDelay( nValue );
    }
    else if ( !stricmp(szOption, "SendKeyDownDelay") )        // SendKeyDownDelay
    {
        vResult = (int)engine->g_oSendKeys->m_nKeyDownDelay;    // Store current value

        if (nValue >= -1)
            engine->g_oSendKeys->SetKeyDownDelay( nValue );
    }
    else if ( !stricmp(szOption, "TrayIconDebug") )            // TrayIconDebug
    {
        vResult = (int)engine->g_bTrayIconDebug;    // Store current value

        if (nValue == 0)
            engine->g_bTrayIconDebug = false;
        else
            engine->g_bTrayIconDebug = true;
    }
//    else if ( !stricmp(szOption, "TrayIconHide") )            // TrayIconHide
//    {
//        vResult = (int)!engine->g_bTrayIcon;    // Store current value
//
//        if (nValue == 0)
//            engine->g_oApplication.CreateTrayIcon();
//        else
//            engine->g_oApplication.DestroyTrayIcon();
//    }
    else if (!stricmp(szOption, "WinSearchChildren"))
    {
        vResult = (int)engine->bWinSearchChildren();    // Store current value

        if (nValue == 0)
            engine->setWinSearchChildren(false);
        else
            engine->setWinSearchChildren(true);
    }
    else if ( !stricmp(szOption, "WinWaitDelay") )            // WinWaitDelay
    {
        vResult = (int)engine->nWinWaitDelay();    // Store current value

        if (nValue >= 0)
            engine->setWinWaitDelay(nValue);
    }
    else if ( !stricmp(szOption, "WinDetectHiddenText") )    // WinDetectHiddenText
    {
        vResult = (int)engine->bDetectHiddenText();    // Store current value

        if ( nValue == 0)
            engine->setDetectHiddenText(false);
        else
            engine->setDetectHiddenText(true);
    }
    else if ( !stricmp(szOption, "WinTextMatchMode") )        // WinTextMatchMode
    {
        vResult = (int)engine->nWindowSearchTextMode();    // Store current value

        if (nValue >= 1 && nValue <= 2)
            engine->setWindowSearchTextMode(nValue);
        else
            engine->setWindowSearchTextMode(1);
    }
    else if ( !stricmp(szOption, "WinTitleMatchMode") )        // WinTitleMatchMode
    {
        vResult = (int)engine->nWindowSearchMatchMode();    // Store current value

        if (nValue >= 1 && nValue <= 4)
            engine->setWindowSearchMatchMode(nValue);
        else
            engine->setWindowSearchMatchMode(1);
    }
    else
    {
        // No matching option if we got here
        engine->FatalError(IDS_AUT_E_BADOPTION);
        return AUT_ERR;
    }

    return AUT_OK;

} // AutoItSetOption()

///////////////////////////////////////////////////////////////////////////////
// TimerInit()
// Returns a floating point value that is a baseline system time.
// Starts tracking a high performance counter allowing for accurate timers.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_TimerInit(VectorVariant &vParams, Variant &vResult)
{
    __int64 now;

    if (!QueryPerformanceCounter((LARGE_INTEGER *)&now))
        return AUT_OK;

    vResult = (double)now;

    return AUT_OK;

} // TimerInit()

///////////////////////////////////////////////////////////////////////////////
// TimerDiff(Baseline)
// Takes the time difference between now and Baseline and returns the result.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_TimerDiff(VectorVariant &vParams, Variant &vResult)
{
    __int64 freq, now;

    if (!QueryPerformanceFrequency((LARGE_INTEGER *)&freq))
        return AUT_OK;

    if (!QueryPerformanceCounter((LARGE_INTEGER *)&now))
        return AUT_OK;

    vResult = (((double)now - vParams[0].fValue()) / (double)freq) * 1000.0;

    return AUT_OK;

} // TimerDiff()

///////////////////////////////////////////////////////////////////////////////
// MemGetStats()
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_MemGetStats(VectorVariant &vParams, Variant &vResult)
{
    MEMORYSTATUS mem;
    GlobalMemoryStatus(&mem);

    Variant    *pvTemp;

    engine->VariantArrayDim(&vResult, 7);

    // We have to cast all of these because of the overloaded operator= in the Variant class
    pvTemp = engine->VariantArrayGetRef(&vResult, 0);
    *pvTemp = (double)mem.dwMemoryLoad;

    pvTemp = engine->VariantArrayGetRef(&vResult, 1);
    *pvTemp = (double)mem.dwTotalPhys / 1024.0;            // Conv to KB

    pvTemp = engine->VariantArrayGetRef(&vResult, 2);
    *pvTemp = (double)mem.dwAvailPhys / 1024.0;

    pvTemp = engine->VariantArrayGetRef(&vResult, 3);
    *pvTemp = (double)mem.dwTotalPageFile / 1024.0;

    pvTemp = engine->VariantArrayGetRef(&vResult, 4);
    *pvTemp = (double)mem.dwAvailPageFile / 1024.0;

    pvTemp = engine->VariantArrayGetRef(&vResult, 5);
    *pvTemp = (double)mem.dwTotalVirtual / 1024.0;

    pvTemp = engine->VariantArrayGetRef(&vResult, 6);
    *pvTemp = (double)mem.dwAvailVirtual / 1024.0;

    return AUT_OK;

}    // MemGetStats()
