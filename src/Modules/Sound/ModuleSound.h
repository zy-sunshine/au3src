#include "AutoIt.h"

class ModuleSound {
public:
    AUT_RESULT    F_SoundPlay(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_SoundSetWaveVolume(VectorVariant &vParams, Variant &vResult);
};
