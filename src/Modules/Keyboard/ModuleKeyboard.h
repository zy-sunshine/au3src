#include "AutoIt.h"

class ModuleKeyboard {
public:
    AUT_RESULT    F_Send(VectorVariant &vParams, Variant &vResult);

    AUT_RESULT    F_HotKeySet(VectorVariant &vParams, Variant &vResult);
};
