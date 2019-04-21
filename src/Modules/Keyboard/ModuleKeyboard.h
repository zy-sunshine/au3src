#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleKeyboard {
public:
    ModuleKeyboard(Engine* engine);
    ~ModuleKeyboard();

    AUT_RESULT    F_Send(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_HotKeySet(VectorVariant &vParams, Variant &vResult);

    bool HandleHotKey(); // engine loop func

private:
    Engine* engine;

    // HotKey stuff
    HotKeyDetails    *m_HotKeyDetails[AUT_MAXHOTKEYS];    // Array for tracking hotkey details
    int              m_nHotKeyQueuePos;                    // Position in the global hotkey queue
};
