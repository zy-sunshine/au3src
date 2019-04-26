///////////////////////////////////////////////////////////////////////////////
//
// AutoIt v3
//
// Copyright (C)1999-2005:
//        - Jonathan Bennett <jon at hiddensoft dot com>
//        - See "AUTHORS.txt" for contributors.
//
// This file is part of AutoIt.
//
// AutoIt source code is copyrighted software distributed under the terms of the
// AutoIt source code license.
//
// You may:
//
// - Customize the design and operation of the AutoIt source code to suit
// the internal needs of your organization except to the extent not
// permitted in this Agreement
//
// You may not:
//
// - Distribute the AutoIt source code and/or compiled versions of AutoIt
// created with the AutoIt source code.
// - Create derivative works based on the AutoIt source code for distribution
// or usage outside your organisation.
// - Modify and/or remove any copyright notices or labels included in the
// AutoIt source code.
//
// AutoIt is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// See the LICENSE.txt file that accompanies the AutoIt source
// code for more details.
//
///////////////////////////////////////////////////////////////////////////////
//
// script_process.cpp
//
// Contains process/main related functions.  Part of script.cpp
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"                                // Pre-compiled headers
#include "Engine/Engine.h"
#include "ModuleSys.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <mmsystem.h>
    #include <limits.h>
    #include <tlhelp32.h>
#endif

#include "Utils/utility.h"
#include "Utils/WinUtil.h"
#include "Utils/OSVersion.h"

//ModuleSys::funcInfo[] = {
//    {"RUN", &Engine::F_Run, 1, 3},
//    {"RUNWAIT", &Engine::F_RunWait, 1, 3},
//    {"RUNASSET", &Engine::F_RunAsSet, 0, 4},
//    {"PROCESSCLOSE", &Engine::F_ProcessClose, 1, 1},
//    {"PROCESSEXISTS", &Engine::F_ProcessExists, 1, 1},
//    {"PROCESSWAITCLOSE", &Engine::F_ProcessWaitClose, 1, 2},
//    {"PROCESSWAIT", &Engine::F_ProcessWait, 1, 2},
//    {"SHUTDOWN", &Engine::F_Shutdown, 1, 1},
//    {"PROCESSSETPRIORITY", &Engine::F_ProcessSetPriority, 2, 2},
//    {"PROCESSLIST", &Engine::F_ProcessList, 0, 1},
////    {"DLLCALL", &Engine::F_DllCall, 3, 255},
////    {"DLLCLOSE", &Engine::F_DllClose, 1, 1},
////    {"DLLOPEN", &Engine::F_DllOpen, 1, 1},
//    {"ENVGET", &Engine::F_EnvGet, 1, 1},
//    {"ENVSET", &Engine::F_EnvSet, 1, 2},
//    {"ENVUPDATE", &Engine::F_EnvUpdate, 0, 0},
//    {"SLEEP", &Engine::F_Sleep, 1, 1},
//    {"BLOCKINPUT", &Engine::F_BlockInput, 1, 1},
//    {"ADLIBDISABLE", &Engine::F_AdlibDisable, 0, 0},
//    {"ADLIBENABLE", &Engine::F_AdlibEnable, 1, 2},
//    {"CLIPGET", &Engine::F_ClipGet, 0, 0},
//    {"CLIPPUT", &Engine::F_ClipPut, 1, 1},
//    {"ISADMIN", &Engine::F_IsAdmin, 0, 0},
//    {"SETERROR", &Engine::F_SetError, 1, 1},
//    {"SETEXTENDED", &Engine::F_SetExtended, 1, 1},
//    {"BREAK", &Engine::F_Break, 1, 1},
//    {"OPT", &Engine::F_AutoItSetOption, 2, 2},
//    {"AUTOITSETOPTION", &Engine::F_AutoItSetOption, 2, 2},
//    {"TIMERINIT", &Engine::F_TimerInit, 0, 0},
//    {"TIMERSTART", &Engine::F_TimerInit, 0, 0},
//    {"TIMERDIFF", &Engine::F_TimerDiff, 1, 1},
//    {"TIMERSTOP", &Engine::F_TimerDiff, 1, 1},
//    {"MEMGETSTATS", &Engine::F_MemGetStats, 0, 0},
//};

// Dynamic function declarations
typedef BOOL (WINAPI *MyCreateProcessWithLogonW)(
    LPCWSTR lpUsername,                 // user's name
    LPCWSTR lpDomain,                   // user's domain
    LPCWSTR lpPassword,                 // user's password
    DWORD dwLogonFlags,                 // logon option
    LPCWSTR lpApplicationName,          // executable module name
    LPWSTR lpCommandLine,               // command-line string
    DWORD dwCreationFlags,              // creation flags
    LPVOID lpEnvironment,               // new environment block
    LPCWSTR lpCurrentDirectory,         // current directory name
    LPSTARTUPINFOW lpStartupInfo,       // startup information
    LPPROCESS_INFORMATION lpProcessInfo // process information
    );

#ifndef LOGON_WITH_PROFILE
    #define LOGON_WITH_PROFILE 1
    #define LOGON_NETCREDENTIALS_ONLY 2
#endif

ModuleSys::ModuleSys(Engine* engine)
    :engine(engine)
{
    // RunAsSet stuff
    m_bRunAsSet                    = false;        // Don't use RunAs by default
    m_wszRunUser = m_wszRunDom = m_wszRunPwd = NULL;    // Strings are empty
}

ModuleSys::~ModuleSys()
{
    // RunAsSet stuff
    delete [] m_wszRunUser;                        // NULL if not used, which is OK
    delete [] m_wszRunDom;
    delete [] m_wszRunPwd;
}

///////////////////////////////////////////////////////////////////////////////
// HandleProcessWait()
//
// Check if a processwait-style operation is in progress, process and returns
// true.  If no processing required returns false
///////////////////////////////////////////////////////////////////////////////

bool ModuleSys::HandleProcessWait(int type, AString &sProcessSearchTitle, int nProcessWaitTimeout,
    int tProcessTimerStarted, Variant &vResult)
{
    while (true) {
        // Idle a little to remove CPU usage
        Sleep(AUT_IDLE);

        engine->processEvents();

        // If required, process the timeout
        if (nProcessWaitTimeout != 0)
        {
            // Get current time in ms
            DWORD    dwDiff;
            DWORD    dwCur = timeGetTime();
            if (dwCur < tProcessTimerStarted)
                dwDiff = (UINT_MAX - tProcessTimerStarted) + dwCur; // timer wraps at 2^32
            else
                dwDiff = dwCur - tProcessTimerStarted;

            // Timer elapsed?
            if (dwDiff >= nProcessWaitTimeout)
            {
                vResult = 0;
                return true;
            }
        }


        // Perform relevant command
        bool bRes = false;
        DWORD    dwPid;
        if (type == AUT_PROCESSWAIT)
        {
            // Process Wait
            if (Util_DoesProcessExist(m_sProcessSearchTitle.c_str(), dwPid, bRes) == false)
            {
                engine->FatalError(IDE_AUT_E_PROCESSNT);
                engine->quit();
            }
        }
        else if (type == AUT_PROCESSWAITCLOSE)
        {
            // Process Wait Close
            if (Util_DoesProcessExist(m_sProcessSearchTitle.c_str(), dwPid, bRes) == false)
            {
                engine->FatalError(IDE_AUT_E_PROCESSNT);
                engine->quit();
            }
            bRes = !bRes;
        } else {
            return false;
        }


        // Wait Command successful?
        if (bRes == true)
        {
            //m_bUserFuncReturned = true;           // Request exit from Execute()
            //m_nCurrentOperation = AUT_RUN;        // Continue script
            // NOTE: why wait here?
            Sleep(engine->nWinWaitDelay());          // Briefly pause before continuing
            vResult = 1;  // TODO: return process pid?
            return true;
        }
    }
    return false;

} // HandleProcessWait()


///////////////////////////////////////////////////////////////////////////////
// ProcessWaitInit()
///////////////////////////////////////////////////////////////////////////////

void ModuleSys::ProcessWaitInit(VectorVariant &vParams, uint iNumParams)
{
    // Parameters are processname, timeout - only processname is mandatory

    // Setup the search for title/text
    m_sProcessSearchTitle = vParams[0].szValue();

    if (iNumParams == 2)
        m_nProcessWaitTimeout    = vParams[1].nValue() * 1000;    // Timeout
    else
        m_nProcessWaitTimeout    = 0;


    // Make a note of current system time for comparision in timer
    m_tProcessTimerStarted    = timeGetTime();

} // ProcessWaitInit()


///////////////////////////////////////////////////////////////////////////////
// ProcessExists()
//
// Checks if a process exists
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ProcessExists(VectorVariant &vParams, Variant &vResult)
{
    DWORD    dwPid;
    bool    bResult = false;

    if (Util_DoesProcessExist(vParams[0].szValue(), dwPid, bResult) == false)
    {
        engine->FatalError(IDE_AUT_E_PROCESSNT);
        return AUT_ERR;
    }

    if (bResult)
        vResult = (double)dwPid;
    else
        vResult = 0;

    return AUT_OK;

} // ProcessExists()


///////////////////////////////////////////////////////////////////////////////
// ProcessWait()
//
// Waits for a process
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ProcessWait(VectorVariant &vParams, Variant &vResult)
{
    AString          sProcessSearchTitle;        // Name of process to wait for
    DWORD            nProcessWaitTimeout;        // Time (ms) left before timeout (0=no timeout)
    DWORD            tProcessTimerStarted;        // Time in millis that timer was started
    HANDLE           piRunProcess;                // Used in RunWait command

    // Parameters are processname, timeout - only processname is mandatory

    // Setup the search for title/text
    sProcessSearchTitle = vParams[0].szValue();

    if (vParams.size() == 2)
        nProcessWaitTimeout    = vParams[1].nValue() * 1000;    // Timeout
    else
        nProcessWaitTimeout    = 0;

    // Make a note of current system time for comparision in timer
    tProcessTimerStarted    = timeGetTime();

    vResult = 1;                    // Default return value is 1
    HandleProcessWait(AUT_PROCESSWAIT, sProcessSearchTitle, nProcessWaitTimeout,
            tProcessTimerStarted, vResult);
    return AUT_OK;

} // ProcessWait()


///////////////////////////////////////////////////////////////////////////////
// ProcessWaitClose()
//
// Waits for a process to not exist
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleSys::F_ProcessWaitClose(VectorVariant &vParams, Variant &vResult)
//{
//    ProcessWaitInit(vParams, vParams.size());
//    m_vUserRetVal = 1;                    // Default return value is 1
//    m_nCurrentOperation = AUT_PROCESSWAITCLOSE;
//    Execute();
//    vResult = m_vUserRetVal;            // Get return value (0 = timed out)
//    return AUT_OK;
//
//} // ProcessWaitClose()


///////////////////////////////////////////////////////////////////////////////
// ProcessClose()
//
// Waits for a process to not exist
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ProcessClose(VectorVariant &vParams, Variant &vResult)
{
    DWORD    dwPid;
    bool    bResult = false;

    if (Util_DoesProcessExist(vParams[0].szValue(), dwPid, bResult) == false)
    {
        engine->FatalError(IDE_AUT_E_PROCESSNT);
        return AUT_ERR;
    }

    if (bResult)
    {
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }

    return AUT_OK;

} // ProcessClose()


///////////////////////////////////////////////////////////////////////////////
// RunAsSet()
//
// Handles the setup the RunAs functionality
//
// $result = RunAsSet( ["user", "domain", "password"] )
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_RunAsSet(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();

    // We must be 2000+ to use this feature
    if (engine->g_oVersion->IsWin2000orLater() == false)
    {
        vResult = 0;                            // Not supported (default 1)
        return AUT_OK;
    }

    // Delete previous strings (may already be NULL, but delete doesn't mind)
    delete [] m_wszRunUser;
    delete [] m_wszRunDom;
    delete [] m_wszRunPwd;
    m_wszRunUser = m_wszRunDom = m_wszRunPwd = NULL;


    // If no params given then disable RunAsSet mode
    if (iNumParams == 0)
    {
        m_bRunAsSet = false;                    // Disable RunAs
        return AUT_OK;
    }

    // 3 or 4 params is the only other valid option
    if (iNumParams != 3 && iNumParams != 4)
    {
        engine->FatalError(IDS_AUT_E_FUNCTIONNUMPARAMS);
        return AUT_ERR;
    }


    // Now, convert to wide character versions to enable easier calling of the
    // CreateProcessAsUser() function which only accepts wide chars
    m_wszRunUser    = Util_ANSItoUNICODE(vParams[0].szValue());
    m_wszRunDom        = Util_ANSItoUNICODE(vParams[1].szValue());
    m_wszRunPwd        = Util_ANSItoUNICODE(vParams[2].szValue());


    // Set logon flags
    m_dwRunAsLogonFlags = LOGON_WITH_PROFILE;    // Default is to load the profile

    if (iNumParams == 4)
    {
        if (vParams[3].nValue() == 0)
            m_dwRunAsLogonFlags = 0;
        else if (vParams[3].nValue() == 2)
            m_dwRunAsLogonFlags = LOGON_NETCREDENTIALS_ONLY;
    }

    m_bRunAsSet = true;                            // Enable RunAs functionality

    return AUT_OK;

} // RunAsSet()



///////////////////////////////////////////////////////////////////////////////
// Run()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_Run(VectorVariant &vParams, Variant &vResult)
{
    return Run(0, vParams, vParams.size(), vResult);

} // Run()


///////////////////////////////////////////////////////////////////////////////
// RunWait()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_RunWait(VectorVariant &vParams, Variant &vResult)
{
    if (AUT_FAILED(Run(1, vParams, vParams.size(), vResult)))
        return AUT_ERR;
    else
    {
        // Run has not indicated an error, BUT if RunErrorsFatal is false this may be an
        // incorrect outcome, so also check if @error == 1 (error executing) before init'ing
        // a RUNWAIT
        if (engine->nFuncErrorCode() == 0)
        {
            vResult = loopCheckProcess();
        }
    }
    return AUT_OK;

} // RunWait()

int ModuleSys::loopCheckProcess()
{
    while (true) {
        DWORD dwexitcode;
        GetExitCodeProcess(m_piRunProcess, &dwexitcode);

        if (dwexitcode != STILL_ACTIVE)
        {
            CloseHandle(m_piRunProcess);    // Close handle
            return (int)dwexitcode;// Set exit code
        }
        else {
            Sleep(AUT_IDLE);                // Quick sleep to reduce CPU load
            if (engine->processEvents() == AUT_QUIT) { break; }
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Run()
//
// Handles the setup of the Run and RunWait commands
// nFunction = 0 = Run
// nFunction = 1 = RunWait
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::Run(int nFunction, VectorVariant &vParams, uint iNumParams, Variant &vResult)
{
    STARTUPINFO                si;
    STARTUPINFOW            wsi;

    PROCESS_INFORMATION        pi;
    char                    szRun[AUT_MAX_LINESIZE+1];
    wchar_t                    *wszRun;
    char                    szDir[AUT_MAX_LINESIZE+1];
    wchar_t                    *wszDir;
    BOOL                    bRes;

    HINSTANCE                    hinstLib = NULL;
    MyCreateProcessWithLogonW    lpfnDLLProc = NULL;


    // init structure for running programs
    si.cb            = sizeof(STARTUPINFO);
    si.lpReserved    = NULL;
    si.lpDesktop    = NULL;
    si.lpTitle        = NULL;
    si.dwFlags        = STARTF_USESHOWWINDOW;
    si.cbReserved2    = 0;
    si.lpReserved2    = NULL;
    si.wShowWindow    = SW_SHOWNORMAL;


    // Must contain at least one parameter
    strcpy(szRun, vParams[0].szValue());

    if (iNumParams >= 2)                        // Has working dir
        strcpy(szDir, vParams[1].szValue());        // Get working directory, if blank get the current working dir
    else
        szDir[0] = '\0';

    if (szDir[0] == '\0')
        GetCurrentDirectory(_MAX_PATH, szDir);

    if (iNumParams == 3)                        // Has show flag
        si.wShowWindow = (WORD)vParams[2].nValue();    // Default is SW_SHOWNORMAL


    // If required, init RunAs (dynamically link to retain compatibility with 95)
    if (m_bRunAsSet)
    {
        // Get a handle to the DLL module that contains CreateProcessWithLogonW
        hinstLib = LoadLibrary("advapi32.dll");
        if (hinstLib != NULL)
        {
            lpfnDLLProc = (MyCreateProcessWithLogonW)GetProcAddress(hinstLib, "CreateProcessWithLogonW");
            if (lpfnDLLProc != NULL)
            {
                // Set up wide char version that we need for CreateProcessWithLogon
                // init structure for running programs (wide char version)
                wsi.cb            = sizeof(STARTUPINFOW);
                wsi.lpReserved    = NULL;
                wsi.lpDesktop    = NULL;
                wsi.lpTitle        = NULL;
                wsi.dwFlags        = STARTF_USESHOWWINDOW;
                wsi.cbReserved2    = 0;
                wsi.lpReserved2    = NULL;
                wsi.wShowWindow = si.wShowWindow;                // Default is same as si

                wszRun = Util_ANSItoUNICODE(szRun);                // Get wide char version of the run string
                wszDir = Util_ANSItoUNICODE(szDir);                // Get wide char version of the dir string
            }
            else
            {
                FreeLibrary(hinstLib);
                engine->FatalError(IDS_AUT_E_RUNASFAILED);
                return AUT_ERR;
            }
        }
        else
        {
            engine->FatalError(IDS_AUT_E_RUNASFAILED);
            return AUT_ERR;
        }
    }


    // RunAs or Normal?
    if (lpfnDLLProc == NULL)
        bRes = CreateProcess(NULL, szRun, NULL, NULL, FALSE, 0, NULL, szDir, &si, &pi);
    else
    {
        bRes = lpfnDLLProc( m_wszRunUser, m_wszRunDom, m_wszRunPwd, m_dwRunAsLogonFlags, 0, wszRun, 0, 0, wszDir, &wsi, &pi );
        delete [] wszRun;                        // Free our wide strings
        delete [] wszDir;
    }


    // Check for success
    if (bRes == FALSE)
    {
        if (hinstLib)
            FreeLibrary(hinstLib);

        if (engine->bRunErrorsFatal() == true)
        {
            engine->FatalError(IDS_AUT_E_RUNPROG, WinUtil::instance.FormatWinError());
            return AUT_ERR;
        }
        else
        {
            engine->SetFuncErrorCode(1);                // Indicate an error (silently)
            vResult = 0;                        // Also set result to 0 (default 1)
            return AUT_OK;                        // Nothing to tidy, so return now
        }
    }


    // Tidy up
    if (hinstLib)
        FreeLibrary(hinstLib);

    CloseHandle(pi.hThread);


    // If this is a RUNWAIT command, track the process
    if (nFunction == 1)                            // RUNWAIT
        m_piRunProcess = pi.hProcess;
    else                                        // RUN
    {
        vResult = (double)pi.dwProcessId;        // Pass the PID back as the result
        CloseHandle(pi.hProcess);
    }

    return AUT_OK;

} // Run()


///////////////////////////////////////////////////////////////////////////////
// Shutdown()
//
// $var = Shutdown(flag)
// flags can be a combination of:
// #define EWX_LOGOFF           0
// #define EWX_SHUTDOWN         0x00000001
// #define EWX_REBOOT           0x00000002
// #define EWX_FORCE            0x00000004
// #define EWX_POWEROFF         0x00000008
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_Shutdown(VectorVariant &vParams, Variant &vResult)
{
    if (Util_Shutdown(vParams[0].nValue()) == FALSE)
        vResult = 0;                            // Shutdown failed

    return AUT_OK;

} // Shutdown()



///////////////////////////////////////////////////////////////////////////////
// ProcessSetPriority()
//
// Sets the process priority.
// Some priority classes aren't supported on Windows 95/98/ME, for those cases,
// @error is set to 2 and the function returns.  Otherwise, @error is 1 on failure and
// 0 on success.  The function returns 1 on success, 0 otherwise, also.
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ProcessSetPriority(VectorVariant &vParams, Variant &vResult)
{
    typedef HANDLE (WINAPI *MyOpenProcess)(DWORD, BOOL, DWORD);
    typedef HANDLE (WINAPI *MySetPriorityClass)(HANDLE, DWORD);
    MyOpenProcess lpfnOpenProcess;
    MySetPriorityClass lpfnSetPriorityClass;
    DWORD dwPid;
    bool bRes;
    HANDLE hProc;
    HMODULE hInst;
    // Assume failure, we'll change for success.
    vResult = 0;
    engine->SetFuncErrorCode(1);

    Util_DoesProcessExist(vParams[0].szValue(), dwPid, bRes);
    if (!bRes)
        return AUT_OK;

    hInst = GetModuleHandle("KERNEL32.DLL");
    if (hInst == NULL)
        return AUT_OK;

    lpfnOpenProcess = (MyOpenProcess)GetProcAddress(hInst, "OpenProcess");
    lpfnSetPriorityClass = (MySetPriorityClass)GetProcAddress(hInst, "SetPriorityClass");
    if (!lpfnOpenProcess || !lpfnSetPriorityClass)
        return AUT_OK;

    hProc = lpfnOpenProcess(PROCESS_SET_INFORMATION, FALSE, dwPid);

    if (!hProc)
        return AUT_OK;

    DWORD dwPriority = 0;
    switch(vParams[1].nValue())
    {
    case 0:
        dwPriority = 0x00000040;                // IDLE_PRIORITY_CLASS
        break;
    case 1:
        if (engine->g_oVersion->IsWin9x() || engine->g_oVersion->IsWinMe())
            engine->SetFuncErrorCode(2);
        else
            dwPriority = 0x00004000;            // BELOW_NORMAL_PRIORITY_CLASS
        break;
    case 2:
        dwPriority = 0x00000020;                // NORMAL_PRIORITY_CLASS
        break;
    case 3:
        if (engine->g_oVersion->IsWin9x() || engine->g_oVersion->IsWinMe())
            engine->SetFuncErrorCode(2);
        else
            dwPriority = 0x00008000;            // ABOVE_NORMAL_PRIORITY_CLASS
        break;
    case 4:
        dwPriority = 0x00000080;                // HIGH_PRIORITY_CLASS;
        break;
    case 5:
        dwPriority = 0x00000100;                // REALTIME_PRIORITY_CLASS
        break;
    }

    if (dwPriority)
    {
        lpfnSetPriorityClass(hProc, dwPriority);
        // Set to success
        vResult = 1;
        engine->SetFuncErrorCode(0);
    }

    CloseHandle(hProc);
    FreeLibrary(hInst);

    return AUT_OK;

}    // ProcessSetPriority()


//////////////////////////////////////////////////////////////////////////
// ProcessList( ["name"] )
//
//////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSys::F_ProcessList(VectorVariant &vParams, Variant &vResult)
{
    // Variables used in both method's.
    int            count = 0;    // Count of all valid processes (May be different depending on method used)
    char        szDrive[_MAX_PATH+1], szDir[_MAX_PATH+1], szFile[_MAX_PATH+1], szExt[_MAX_PATH+1];
    HINSTANCE    hinstLib;
    AString        sNameCmp;

    // Create a small structure to make things easy.
    struct ProcessInfo
    {
        DWORD    dwPid;
        AString sName;
    };
    ProcessInfo piProc[512];

    if (engine->g_oVersion->IsWinNT4())    // Windows NT 4stuff
    {
        typedef BOOL (WINAPI *MyEnumProcesses)(DWORD*, DWORD, DWORD*);
        typedef BOOL (WINAPI *MyEnumProcessModules)(HANDLE, HMODULE*, DWORD, LPDWORD);
        typedef DWORD (WINAPI *MyGetModuleBaseName)(HANDLE, HMODULE, LPTSTR, DWORD);

        MyEnumProcesses            lpfnEnumProcesses;
        MyEnumProcessModules    lpfnEnumProcessModules;
        MyGetModuleBaseName        lpfnGetModuleBaseName;

        DWORD                    idProcessArray[512];        // 512 processes max
        DWORD                    cbNeeded;                    // Bytes returned
        DWORD                    cProcesses;                    // Number of processes
        char                    szProcessName[_MAX_PATH+1];
        HMODULE                    hMod;
        HANDLE                    hProcess;

        // We must dynamically load the function to retain compatibility with Win95
        // Get a handle to the DLL module that contains EnumProcesses
        hinstLib = LoadLibrary("psapi.dll");
        if (!hinstLib)
        {
            engine->SetFuncErrorCode(1);
            return AUT_OK;
        }

        lpfnEnumProcesses        = (MyEnumProcesses)GetProcAddress(hinstLib, "EnumProcesses");
        lpfnEnumProcessModules    = (MyEnumProcessModules)GetProcAddress(hinstLib, "EnumProcessModules");
        lpfnGetModuleBaseName    = (MyGetModuleBaseName)GetProcAddress(hinstLib, "GetModuleBaseNameA");

        if (!lpfnEnumProcesses || !lpfnEnumProcessModules || !lpfnGetModuleBaseName)
        {
            FreeLibrary(hinstLib);                    // Free the DLL module.
            engine->SetFuncErrorCode(1);
            return AUT_OK;
        }

        // Get the list of processes running
        if (!lpfnEnumProcesses(idProcessArray, sizeof(idProcessArray), &cbNeeded))
        {
            FreeLibrary(hinstLib);                    // Free the DLL module.
            engine->SetFuncErrorCode(1);
            return AUT_OK;
        }

        // Get the count of PIDs in the array
        cProcesses = cbNeeded / sizeof(DWORD);

        for(uint i = 0; i < cProcesses; ++i)
        {
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, idProcessArray[i] );
            lpfnEnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded);
            if (lpfnGetModuleBaseName(hProcess, hMod, szProcessName, _MAX_PATH))
            {
                _splitpath( szProcessName, szDrive, szDir, szFile, szExt );    // Split the filename
                strcat(szFile, szExt);

                // Only make a note of matching process names
                if ( vParams.size() == 0 || ( vParams.size() && !stricmp(szFile, vParams[0].szValue()) ) )
                {
                    piProc[count].sName = szFile;
                    piProc[count].dwPid = idProcessArray[i];
                    ++count;
                }
            }
            CloseHandle(hProcess);
        }
        FreeLibrary(hinstLib);                    // Free the DLL module.
    }
    else    // Win 98
    {
        typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
        typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);

        HANDLE            snapshot;
        PROCESSENTRY32    proc;
        CREATESNAPSHOT    lpfnCreateToolhelp32Snapshot = NULL;
        PROCESSWALK        lpfnProcess32First = NULL;
        PROCESSWALK        lpfnProcess32Next  = NULL;

        // We must dynamically load the function to retain compatibility with WinNT
        hinstLib = GetModuleHandle("KERNEL32.DLL");
        if (!hinstLib)
        {
            engine->SetFuncErrorCode(1);
            return AUT_OK;
        }

        lpfnCreateToolhelp32Snapshot = (CREATESNAPSHOT)GetProcAddress(hinstLib, "CreateToolhelp32Snapshot");
        lpfnProcess32First = (PROCESSWALK)GetProcAddress(hinstLib, "Process32First");
        lpfnProcess32Next  = (PROCESSWALK)GetProcAddress(hinstLib, "Process32Next");

        if (!lpfnCreateToolhelp32Snapshot || !lpfnProcess32First || !lpfnProcess32Next)
        {
            FreeLibrary(hinstLib);                    // Free the DLL module.
            engine->SetFuncErrorCode(1);
            return AUT_OK;
        }

        proc.dwSize = sizeof(proc);
        snapshot = lpfnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        lpfnProcess32First(snapshot, &proc);

        do
        {
            _splitpath( proc.szExeFile, szDrive, szDir, szFile, szExt );    // Split the filename
            strcat(szFile, szExt);

            // Only make a note of matching process names
            if ( vParams.size() == 0 || ( vParams.size() && !stricmp(szFile, vParams[0].szValue()) ) )
            {
                piProc[count].sName = szFile;
                piProc[count].dwPid = proc.th32ProcessID;
                ++count;
            }

        } while (lpfnProcess32Next(snapshot, &proc));

        CloseHandle(snapshot);
    }

    // Create and fill the array
    Variant    *pvVariant;

    vResult.ArraySubscriptClear();                        // Reset the subscript
    vResult.ArraySubscriptSetNext(count + 1);            // Number of elements
    vResult.ArraySubscriptSetNext(2);                    // Number of elements ([0]=name. [1]=pid)
    vResult.ArrayDim();                                    // Dimension array

    // Set up the count in [0][0]
    vResult.ArraySubscriptClear();                        // Reset the subscript
    vResult.ArraySubscriptSetNext(0);
    vResult.ArraySubscriptSetNext(0);                    // [0][0]
    pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
    *pvVariant = count;                        // Store the count

    for (int i = 0; i < count; ++i)
    {
        // Process Name
        vResult.ArraySubscriptClear();                        // Reset the subscript
        vResult.ArraySubscriptSetNext(i+1);
        vResult.ArraySubscriptSetNext(0);                    // [i+1][0]
        pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
        *pvVariant = piProc[i].sName.c_str();                // Process name

        // Pid
        vResult.ArraySubscriptClear();                        // Reset the subscript
        vResult.ArraySubscriptSetNext(i+1);
        vResult.ArraySubscriptSetNext(1);                    // [i+1][1]
        pvVariant = vResult.ArrayGetRef();                    // Get reference to the element
        *pvVariant = (int)piProc[i].dwPid;                        // PID
    }



/*
    // Create and fill the array
    Util_VariantArrayDim(&vResult, count+1);
    pvTemp = Util_VariantArrayGetRef(&vResult, 0);
    *pvTemp = count;    // Set the number of processes.

    for (int i = 0; i < count; ++i)
    {
        pvTemp = Util_VariantArrayGetRef(&vResult, i+1);
        *pvTemp = "";

        switch(mode)
        {
        case 0:    // Name only (Default)
        case 2:    // Name|PID (Use pipe as delimiter, designed for StringSplit)
            pvTemp->Concat(piProc[i].vName);
            if (mode != 2)
                break;
            pvTemp->Concat(vDelim);
            // fall through
        case 1:    // PID only
            pvTemp->Concat(piProc[i].vPid);
            break;
        }
    }
*/

    return AUT_OK;

} // ProcessList()
