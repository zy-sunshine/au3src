#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleSound: public BaseModule {
public:
    ModuleSound(Engine* engine): engine(engine) {}

    AUT_RESULT    F_SoundPlay(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SoundSetWaveVolume(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
