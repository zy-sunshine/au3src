#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleWin;
class WinSearchUtil {
    friend ModuleWin;
public:
    WinSearchUtil(Engine *engine);
    ~WinSearchUtil();

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

    bool        Win_WinActive(void);
    bool        Win_WinExists(void);

    bool        ControlSearch(VectorVariant &vParams);
    static BOOL CALLBACK ControlSearchProc(HWND hWnd, LPARAM lParam);
    BOOL        ControlSearchProcHandler(HWND hWnd, LPARAM lParam);

    void        ControlWithFocus(HWND hWnd, Variant &vResult);
    static BOOL CALLBACK ControlWithFocusProc(HWND hWnd, LPARAM lParam);
    BOOL        ControlWithFocusProcHandler(HWND hWnd, LPARAM lParam);

    bool        isTimeOut();

protected:
    DWORD            m_nWinWaitTimeout;            // Time (ms) left before timeout (0=no timeout)
    DWORD            m_tWinTimerStarted;            // Time in millis that timer was started

    int              m_nControlSearchMethod;        // Temp variable used in the search functions
    Variant          m_vControlSearchValue;        // The ID, classname or text to search for
    uint             m_iControlSearchInstance;    // Variable to keep track of class instance during search
    bool             m_bControlSearchFoundFlag;    // Temp variable used in the search functions
    HWND             m_ControlSearchHWND;        // Contains HWND of a successful control search

    // Window related vars
    Variant            m_vWindowSearchTitle;        // Title/text used for win searches
    Variant            m_vWindowSearchText;        // Title/text used for win searches
//    bool            m_bWinSearchFoundFlag;        // Temp var used in Window searches
    HWND               m_WindowSearchHWND;            // Temp var used in Window searches
    WinListNode        *m_lpWinListFirst;            // First entry in window list
    WinListNode        *m_lpWinListLast;            // First entry in window list
    int                m_nWinListCount;            // Number of entries
    bool            m_bWindowSearchFirstOnly;    // When true will only find the first matching window (otherwise all)

    // cache from engine config
    int                m_nWindowSearchMatchMode;    // Window title substring match mode

private:
    Engine *engine;
};

