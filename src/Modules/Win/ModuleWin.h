#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleWin {
public:
    ModuleWin(Engine* engine): engine(engine) {}

    // Window-related functions (script_win.cpp)
    AUT_RESULT    F_WinExists(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinActive(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinWait(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinWaitActive(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinWaitNotActive(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinWaitClose(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinActivate(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinShow(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinClose(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinKill(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinMinimizeAll(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinMinimizeAllUndo(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinSetTitle(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinMove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetTitle(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetText(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlClick(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlFocus(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_ControlGetFocus(VectorVariant &vParams, Variant &vResult);
    void        ControlWithFocus(HWND hWnd, Variant &vResult);
    static BOOL CALLBACK ControlWithFocusProc(HWND hWnd, LPARAM lParam);
    BOOL        ControlWithFocusProcHandler(HWND hWnd, LPARAM lParam);

    AUT_RESULT    F_WinSetOnTop(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetPos(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlGetText(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlSetText(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlGetPos(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlCommand(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlListView(VectorVariant &vParams,  Variant &vResult);
    void        ControlLVSelect(bool bSelect, int nFromIndex, int nToIndex);
    AUT_RESULT    F_ControlTreeView(VectorVariant &vParams,  Variant &vResult);
    AUT_RESULT    F_ControlEnable(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlDisable(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlHide(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlMove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlShow(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetClassList(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StatusbarGetText(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlSend(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinMenuSelectItem(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetClientSize(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetHandle(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ControlGetHandle(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetCaretPos(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinGetState(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_WinSetTrans(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ToolTip(VectorVariant &vParams, Variant &vResult);

    bool        Win_HandleWinWait(void);
    void        Win_WindowSearchInit(VectorVariant &vParams);
    void        Win_WindowWaitInit(VectorVariant &vParams);

    void        Win_WindowSearchDeleteList(void);
    void        Win_WindowSearchAddToList(HWND hWnd);
    bool        Win_WindowSearch(bool bFirstOnly = true);
    static BOOL    CALLBACK Win_WindowSearchProc(HWND hWnd, LPARAM lParam);
    BOOL        Win_WindowSearchProcHandler(HWND hWnd, LPARAM lParam);
    bool        Win_WindowSearchText(void);
    static BOOL    CALLBACK Win_WindowSearchTextProc(HWND hWnd, LPARAM lParam);
    BOOL        Win_WindowSearchTextProcHandler(HWND hWnd, LPARAM lParam);

    AUT_RESULT    F_WinList(VectorVariant &vParams, Variant &vResult);

    bool        Win_WinActive(void);
    bool        Win_WinExists(void);

    bool        ControlSearch(VectorVariant &vParams);
    static BOOL CALLBACK ControlSearchProc(HWND hWnd, LPARAM lParam);
    BOOL        ControlSearchProcHandler(HWND hWnd, LPARAM lParam);

    AUT_RESULT    F_WinGetProcess(VectorVariant &vParams, Variant &vResult);

    // WinMisc.cpp
    AUT_RESULT    F_MsgBox (VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_TrayTip(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_AutoItWinSetTitle(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_AutoItWinGetTitle(VectorVariant &vString, Variant &vResult);

    AUT_RESULT    F_PixelSearch(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_PixelChecksum (VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_PixelGetColor(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_SplashImageOn(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SplashTextOn(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SplashOff(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    Splash(VectorVariant &vParams, uint iNumParams, int nFlag);
    AUT_RESULT    F_ProgressOn(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProgressOff(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProgressSet(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    Progress(VectorVariant &vParams, uint iNumParams, int nFlag);
    AUT_RESULT    F_InputBox(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
