#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleKeyboard: public BaseModule {
public:
    static AU3_FuncInfo *funcInfo;
public:
    ModuleKeyboard(Engine* engine);
    ~ModuleKeyboard();

    AUT_RESULT    F_Send(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_HotKeySet(VectorVariant &vParams, Variant &vResult);

private:
    bool HandleHotKey(); // engine loop func

private:
    Engine* engine;

    // HotKey stuff
    HotKeyDetails    *m_HotKeyDetails[AUT_MAXHOTKEYS];    // Array for tracking hotkey details
    int              m_nHotKeyQueuePos;                    // Position in the global hotkey queue
};
