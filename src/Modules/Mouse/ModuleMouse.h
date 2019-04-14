#include "AutoIt.h"

class ModuleMouse {
public:
    AUT_RESULT    F_MouseDown(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseUp(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseClick(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseMove(VectorVariant &vParams, Variant &vResult);
    void        MouseMoveExecute(int x, int y, int nSpeed);
    AUT_RESULT    F_MouseGetPos(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseGetCursor(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseClickDrag(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_MouseWheel(VectorVariant &vParams, Variant &vResult);
};
