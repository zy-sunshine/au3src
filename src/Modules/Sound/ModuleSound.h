#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleSound: public BaseModule {
public:
    static AU3_FuncInfo *funcInfo;
public:
    ModuleSound(Engine* engine): engine(engine) {}

    AUT_RESULT    F_SoundPlay(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SoundSetWaveVolume(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
