#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleMouse: public BaseModule {
public:
    ModuleMouse(Engine* engine);

    AUT_RESULT    F_MouseDown(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseUp(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseClick(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseMove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseGetPos(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseGetCursor(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseClickDrag(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseWheel(VectorVariant &vParams, Variant &vResult);

private:
    void          MouseMoveExecute(int x, int y, int nSpeed);

private:
    Engine* engine;

};
