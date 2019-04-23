#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleSys: public BaseModule {
public:
    ModuleSys(Engine* engine);
    ~ModuleSys();

    // Process related functions (script_process.cpp)
    AUT_RESULT    F_Run(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_RunWait(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_RunAsSet(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProcessClose(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProcessExists(VectorVariant &vParams, Variant &vResult);
    // TODO: open
    //AUT_RESULT    F_ProcessWaitClose(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProcessWait(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_Shutdown(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProcessSetPriority(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_ProcessList(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DllCall(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DllOpen(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DllClose(VectorVariant &vParams, Variant &vResult);

    // form script_misc.cpp
    AUT_RESULT    F_EnvGet(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_EnvSet(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_EnvUpdate(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_Sleep(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_BlockInput(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_AdlibDisable(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_AdlibEnable(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_ClipGet(VectorVariant &vString, Variant &vResult);
    AUT_RESULT    F_ClipPut(VectorVariant &vString, Variant &vResult);

    AUT_RESULT    F_IsAdmin(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_SetError(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SetExtended(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_Break(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_AutoItSetOption(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_TimerInit(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_TimerDiff(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_MemGetStats(VectorVariant &vParams, Variant &vResult);

private:
    int loopCheckProcess();
    AUT_RESULT    Run(int nFunction, VectorVariant &vParams, uint iNumParams, Variant &vResult);
    bool HandleProcessWait(int type, AString &sProcessSearchTitle, int nProcessWaitTimeout,
        int tProcessTimerStarted, Variant &vResult);

    void        ProcessWaitInit(VectorVariant &vParams, uint iNumParams);

private:
    Engine* engine;

    // Process related vars
    AString          m_sProcessSearchTitle;        // Name of process to wait for
    DWORD            m_nProcessWaitTimeout;        // Time (ms) left before timeout (0=no timeout)
    DWORD            m_tProcessTimerStarted;        // Time in millis that timer was started
    HANDLE           m_piRunProcess;                // Used in RunWait command

    bool             m_bRunAsSet;                // Flag if we want to use RunAs user/password in the Run function
    DWORD            m_dwRunAsLogonFlags;        // RunAs logon flags
    wchar_t          *m_wszRunUser;                // User name for RunAs (wide char)
    wchar_t          *m_wszRunDom;                // Domain name for RunAs (wide char)
    wchar_t          *m_wszRunPwd;                // Password for RunAs (wide char)
};
