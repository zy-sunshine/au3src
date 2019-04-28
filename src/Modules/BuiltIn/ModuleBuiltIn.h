#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleBuiltIn: public BaseModule {
public:
    ModuleBuiltIn(Engine* engine): engine(engine) {}
    virtual ~ModuleBuiltIn() {}
    AUT_RESULT    F_BitAND(VectorVariant &vParams, Variant &vResult); // 2, 255
    AUT_RESULT    F_BitOR(VectorVariant &vParams, Variant &vResult);  // 2, 255
    AUT_RESULT    F_BitNOT(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_BitXOR(VectorVariant &vParams, Variant &vResult); // 2, 255
    AUT_RESULT    F_BitShift(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_Chr(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Asc(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Dec(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_VarType(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Int(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IsArray(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IsString(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IsInt(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IsFloat(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IsNumber(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Number(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_String(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Random(VectorVariant &vParams, Variant &vResult); // 0, 3

    // String related functions (script_string.cpp)
    AUT_RESULT    F_StringInStr(VectorVariant &vParams, Variant &vResult); // 2, 4
    AUT_RESULT    F_StringLen(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringLeft(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_StringRight(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_StringMid(VectorVariant &vParams, Variant &vResult); // 2, 3
    AUT_RESULT    F_StringTrimLeft(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_StringTrimRight(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_StringLower(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringUpper(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringReplace(VectorVariant &vParams, Variant &vResult); // 3, 5
    AUT_RESULT    F_StringStripCR(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringAddCR(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsAlpha(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsAlnum(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsDigit(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsXDigit(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsLower(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsUpper(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsSpace(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsASCII(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringStripWS(VectorVariant &vParams, Variant &vResult); // 2, 2
    AUT_RESULT    F_StringIsFloat(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringIsInt(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_StringSplit(VectorVariant &vParams, Variant &vResult); // 2, 3
    AUT_RESULT    F_StringFormat(VectorVariant &vParams, Variant &vResult); // 1, 33
    // AUT_RESULT    F_StringRegExp(VectorVariant &vParams, Variant &vResult); // 2, 3
    // AUT_RESULT    F_StringRegExpReplace(VectorVariant &vParams, Variant &vResult); // 3, 4

    // BuiltInArray.cpp
    AUT_RESULT    F_UBound(VectorVariant &vParams, Variant &vResult); // 1, 2

    // BuiltInMisc.cpp
    AUT_RESULT    F_Call(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Eval(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_Assign(VectorVariant &vParams, Variant &vResult); // 2, 3
    AUT_RESULT    F_IsDeclared(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_ConsoleWrite(VectorVariant &vParams, Variant &vResult);

private:
    bool        StringIsFloat(Variant &vParams);
    bool        StringIsInt(Variant &vParams);

private:
    Engine* engine;
};
