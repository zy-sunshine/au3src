#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleGui: public BaseModule {
public:
    ModuleGui(Engine* engine): engine(engine) {}
    // Gui related functions
//#ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
//    AUT_RESULT    F_GUICreate(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISwitch(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlDelete(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateAvi(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateButton(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateCheckbox (VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateCombo(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateContextMenu(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateDate(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateEdit(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateGroup(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateIcon(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateInput(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateLabel(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateList(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateMenu(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateMenuItem(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreatePic(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateProgress(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateRadio(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateSlider(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateTab(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateTabitem(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateTrayMenu(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateTreeView(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateTreeViewItem(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateListView(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateListViewItem(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateUpdown(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlCreateDummy(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    GUICtrlCreate(int nType, VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlGetState(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetBkColor(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetOnEvent(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetColor(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetCursor(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetData(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetImage(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetFont(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetLimit(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetPos(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetResizing(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetState(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetStyle(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUICtrlSetTip(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIDelete(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIGetMsg(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIRead(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISendToDummy(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISendMsg(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIRecvMsg(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetBkColor(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetCoord(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIGetCursorInfo(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetOnEvent(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetCursor(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetFont(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetHelp(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetIcon(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetState(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetTrayTip(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetTrayBalloon(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUISetTrayIcon(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_GUIStartGroup(VectorVariant &vParams, Variant &vResult);
//#endif

private:
    Engine* engine;
};

//AU3_FuncInfo funcList[] = {
//#ifdef AUT_CONFIG_GUI                            // Is GUI enabled?
//    {"GUICREATE", &Engine::F_GUICreate, 1, 8},
//    {"GUICTRLCREATEAVI", &Engine::F_GUICtrlCreateAvi, 4, 8},
//    {"GUICTRLCREATEBUTTON", &Engine::F_GUICtrlCreateButton, 3, 7},
//    {"GUICTRLCREATECHECKBOX", &Engine::F_GUICtrlCreateCheckbox, 3, 7},
//    {"GUICTRLCREATECOMBO", &Engine::F_GUICtrlCreateCombo, 3, 7},
//    {"GUICTRLCREATECONTEXTMENU", &Engine::F_GUICtrlCreateContextMenu, 0, 1},
//    {"GUICTRLCREATEDATE", &Engine::F_GUICtrlCreateDate, 3, 7},
//    {"GUICTRLCREATEDUMMY", &Engine::F_GUICtrlCreateDummy, 0, 0},
//    {"GUICTRLCREATEEDIT", &Engine::F_GUICtrlCreateEdit, 3, 7},
//    {"GUICTRLCREATEGROUP", &Engine::F_GUICtrlCreateGroup, 3, 7},
//    {"GUICTRLCREATEICON", &Engine::F_GUICtrlCreateIcon, 4, 8},
//    {"GUICTRLCREATEINPUT", &Engine::F_GUICtrlCreateInput, 3, 7},
//    {"GUICTRLCREATELABEL", &Engine::F_GUICtrlCreateLabel, 3, 7},
//    {"GUICTRLCREATELIST", &Engine::F_GUICtrlCreateList, 3, 7},
//    {"GUICTRLCREATELISTVIEW", &Engine::F_GUICtrlCreateListView, 3, 7},
//    {"GUICTRLCREATELISTVIEWITEM", &Engine::F_GUICtrlCreateListViewItem, 2, 2},
//    {"GUICTRLCREATEMENU", &Engine::F_GUICtrlCreateMenu, 1, 3},
//    {"GUICTRLCREATEMENUITEM", &Engine::F_GUICtrlCreateMenuItem, 2, 4},
//    {"GUICTRLCREATEPIC", &Engine::F_GUICtrlCreatePic, 3, 7},
//    {"GUICTRLCREATEPROGRESS", &Engine::F_GUICtrlCreateProgress, 2, 6},
//    {"GUICTRLCREATERADIO", &Engine::F_GUICtrlCreateRadio, 3, 7},
//    {"GUICTRLCREATESLIDER", &Engine::F_GUICtrlCreateSlider, 2, 6},
//    {"GUICTRLCREATETAB", &Engine::F_GUICtrlCreateTab, 2, 6},
//    {"GUICTRLCREATETABITEM", &Engine::F_GUICtrlCreateTabitem, 1, 1},
//    {"GUICTRLCREATETREEVIEW", &Engine::F_GUICtrlCreateTreeView, 2, 6},
//    {"GUICTRLCREATETREEVIEWITEM", &Engine::F_GUICtrlCreateTreeViewItem, 2, 2},
//    {"GUICTRLCREATEUPDOWN", &Engine::F_GUICtrlCreateUpdown, 1, 2},
//    {"GUICTRLDELETE", &Engine::F_GUICtrlDelete, 1, 1},
//    {"GUICTRLGETSTATE", &Engine::F_GUICtrlGetState, 0, 1},
//    {"GUICTRLREAD", &Engine::F_GUIRead, 1, 1},
//    {"GUICTRLRECVMSG", &Engine::F_GUIRecvMsg, 2, 4},
//    {"GUICTRLSENDMSG", &Engine::F_GUISendMsg, 4, 4},
//    {"GUICTRLSENDTODUMMY", &Engine::F_GUISendToDummy, 1, 2},
//    {"GUICTRLSETBKCOLOR", &Engine::F_GUICtrlSetBkColor, 2, 2},
//    {"GUICTRLSETCOLOR", &Engine::F_GUICtrlSetColor, 2, 2},
//    {"GUICTRLSETCURSOR", &Engine::F_GUICtrlSetCursor, 2, 2},
//    {"GUICTRLSETDATA", &Engine::F_GUICtrlSetData, 2, 3},
//    {"GUICTRLSETFONT", &Engine::F_GUICtrlSetFont, 2, 5},
//    {"GUICTRLSETIMAGE", &Engine::F_GUICtrlSetImage, 2, 4},
//    {"GUICTRLSETLIMIT", &Engine::F_GUICtrlSetLimit, 2, 3},
//    {"GUICTRLSETONEVENT", &Engine::F_GUICtrlSetOnEvent, 2, 2},
//    {"GUICTRLSETPOS", &Engine::F_GUICtrlSetPos, 3, 5},
//    {"GUICTRLSETRESIZING", &Engine::F_GUICtrlSetResizing, 2, 2},
//    {"GUICTRLSETSTATE", &Engine::F_GUICtrlSetState, 2, 2},
//    {"GUICTRLSETSTYLE", &Engine::F_GUICtrlSetStyle, 2, 3},
//    {"GUICTRLSETTIP", &Engine::F_GUICtrlSetTip, 2, 2},
//    {"GUIDELETE", &Engine::F_GUIDelete, 0, 1},
//    {"GUIGETCURSORINFO", &Engine::F_GUIGetCursorInfo, 0, 1},
//    {"GUIGETMSG", &Engine::F_GUIGetMsg, 0, 1},
//    {"GUISETBKCOLOR", &Engine::F_GUISetBkColor, 1, 2},
//    {"GUISETCOORD", &Engine::F_GUISetCoord, 2, 5},
//    {"GUISETCURSOR", &Engine::F_GUISetCursor, 0, 3},
//    {"GUISETFONT", &Engine::F_GUISetFont, 1, 5},
//    {"GUISETHELP", &Engine::F_GUISetHelp, 1, 2},
//    {"GUISETICON", &Engine::F_GUISetIcon, 1, 3},
//    {"GUISETONEVENT", &Engine::F_GUISetOnEvent, 2, 3},
//    {"GUISETSTATE", &Engine::F_GUISetState, 0, 2},
//    {"GUISTARTGROUP", &Engine::F_GUIStartGroup, 0, 1},
//    {"GUISWITCH", &Engine::F_GUISwitch, 1, 1},
//#endif
//    {NULL, NULL, 0, 0},
//};
