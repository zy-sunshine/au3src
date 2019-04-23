#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleMath: public BaseModule {
public:
    ModuleMath(Engine* engine): engine(engine) {}

    // Math / Conversion functions (script_math.cpp)
    //AUT_RESULT    F_Sin(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_ASin(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Cos(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_ACos(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Tan(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_ATan(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Log(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Exp(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Abs(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Mod(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Sqrt(VectorVariant &vParams, Variant &vResult);
    //AUT_RESULT    F_Round(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Hex(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
