#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleReg {
public:
    ModuleReg(Engine* engine): engine(engine) {}

    // Registry related functions (script_registry.cpp)
    AUT_RESULT    F_RegRead(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_RegWrite(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_RegDelete(VectorVariant &vParams, Variant &vResult);
    void        RegSplitKey(AString sFull, AString &sCname, AString &sKey, AString &sSubKey);
    bool        RegGetMainKey(AString sKey, HKEY &hKey);
    AUT_RESULT    F_RegEnumKey(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_RegEnumVal(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
