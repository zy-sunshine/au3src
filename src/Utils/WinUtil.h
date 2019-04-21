#include "AutoIt.h"

class WinUtil {
public:
    static WinUtil instance;
public:
    void        ConvertCoords(int nCoordMode, POINT &pt);
    const char * FormatWinError(DWORD dwCode = 0xffffffff);            // Gets the string output for a Windows error code
};

