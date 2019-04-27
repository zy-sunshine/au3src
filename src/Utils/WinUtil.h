#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class WinUtil {
public:
    void        ConvertCoords(int nCoordMode, POINT &pt);
    const char * FormatWinError(DWORD dwCode = 0xffffffff);            // Gets the string output for a Windows error code
};

extern WinUtil g_oWinUtil;
