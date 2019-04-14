#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleKeyboard {
public:
    ModuleKeyboard(Engine* engine): engine(engine) {}

    AUT_RESULT    F_Send(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_HotKeySet(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
