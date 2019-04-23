#pragma once

#include "Modules/BuiltIn/ModuleBuiltIn.h"

AUT_RESULT F_BitAND(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_BitAND(vParams, vResult); }

AUT_RESULT F_BitOR(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_BitOR(vParams, vResult); }

AUT_RESULT F_BitNOT(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_BitNOT(vParams, vResult); }

AUT_RESULT F_BitXOR(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_BitXOR(vParams, vResult); }

AUT_RESULT F_BitShift(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_BitShift(vParams, vResult); }

AUT_RESULT F_Chr(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Chr(vParams, vResult); }

AUT_RESULT F_Asc(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Asc(vParams, vResult); }

AUT_RESULT F_Dec(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Dec(vParams, vResult); }

AUT_RESULT F_VarType(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_VarType(vParams, vResult); }

AUT_RESULT F_Int(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Int(vParams, vResult); }

AUT_RESULT F_IsArray(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsArray(vParams, vResult); }

AUT_RESULT F_IsString(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsString(vParams, vResult); }

AUT_RESULT F_IsInt(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsInt(vParams, vResult); }

AUT_RESULT F_IsFloat(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsFloat(vParams, vResult); }

AUT_RESULT F_IsNumber(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsNumber(vParams, vResult); }

AUT_RESULT F_Number(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Number(vParams, vResult); }

AUT_RESULT F_String(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_String(vParams, vResult); }

AUT_RESULT F_Random(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Random(vParams, vResult); }

AUT_RESULT F_StringInStr(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringInStr(vParams, vResult); }

AUT_RESULT F_StringLen(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringLen(vParams, vResult); }

AUT_RESULT F_StringLeft(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringLeft(vParams, vResult); }

AUT_RESULT F_StringRight(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringRight(vParams, vResult); }

AUT_RESULT F_StringMid(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringMid(vParams, vResult); }

AUT_RESULT F_StringTrimLeft(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringTrimLeft(vParams, vResult); }

AUT_RESULT F_StringTrimRight(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringTrimRight(vParams, vResult); }

AUT_RESULT F_StringLower(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringLower(vParams, vResult); }

AUT_RESULT F_StringUpper(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringUpper(vParams, vResult); }

AUT_RESULT F_StringReplace(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringReplace(vParams, vResult); }

AUT_RESULT F_StringStripCR(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringStripCR(vParams, vResult); }

AUT_RESULT F_StringAddCR(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringAddCR(vParams, vResult); }

AUT_RESULT F_StringIsAlpha(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsAlpha(vParams, vResult); }

AUT_RESULT F_StringIsAlnum(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsAlnum(vParams, vResult); }

AUT_RESULT F_StringIsDigit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsDigit(vParams, vResult); }

AUT_RESULT F_StringIsXDigit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsXDigit(vParams, vResult); }

AUT_RESULT F_StringIsLower(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsLower(vParams, vResult); }

AUT_RESULT F_StringIsUpper(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsUpper(vParams, vResult); }

AUT_RESULT F_StringIsSpace(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsSpace(vParams, vResult); }

AUT_RESULT F_StringIsASCII(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsASCII(vParams, vResult); }

AUT_RESULT F_StringStripWS(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringStripWS(vParams, vResult); }

AUT_RESULT F_StringIsFloat(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsFloat(vParams, vResult); }

AUT_RESULT F_StringIsInt(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringIsInt(vParams, vResult); }

AUT_RESULT F_StringSplit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringSplit(vParams, vResult); }

AUT_RESULT F_StringFormat(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringFormat(vParams, vResult); }

AUT_RESULT F_StringRegExp(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringRegExp(vParams, vResult); }

AUT_RESULT F_StringRegExpReplace(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_StringRegExpReplace(vParams, vResult); }

AUT_RESULT F_UBound(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_UBound(vParams, vResult); }

AUT_RESULT F_Call(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Call(vParams, vResult); }

AUT_RESULT F_Eval(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Eval(vParams, vResult); }

AUT_RESULT F_Assign(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_Assign(vParams, vResult); }

AUT_RESULT F_IsDeclared(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_IsDeclared(vParams, vResult); }

AUT_RESULT F_ConsoleWrite(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleBuiltIn*)self)->F_ConsoleWrite(vParams, vResult); }

            
#include "Modules/File/ModuleFile.h"

AUT_RESULT F_DirCopy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DirCopy(vParams, vResult); }

AUT_RESULT F_IniRead(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_IniRead(vParams, vResult); }

AUT_RESULT F_IniWrite(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_IniWrite(vParams, vResult); }

AUT_RESULT F_IniDelete(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_IniDelete(vParams, vResult); }

AUT_RESULT F_IniReadSectionNames(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_IniReadSectionNames(vParams, vResult); }

AUT_RESULT F_IniReadSection(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_IniReadSection(vParams, vResult); }

AUT_RESULT F_FileOpen(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileOpen(vParams, vResult); }

AUT_RESULT F_FileClose(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileClose(vParams, vResult); }

AUT_RESULT F_FileReadLine(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileReadLine(vParams, vResult); }

AUT_RESULT F_FileGetTime(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetTime(vParams, vResult); }

AUT_RESULT F_FileGetSize(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetSize(vParams, vResult); }

AUT_RESULT F_FileOpenDialog(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileOpenDialog(vParams, vResult); }

AUT_RESULT F_FileSaveDialog(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileSaveDialog(vParams, vResult); }

AUT_RESULT F_FileWriteLine(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileWriteLine(vParams, vResult); }

AUT_RESULT F_FileWrite(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileWrite(vParams, vResult); }

AUT_RESULT F_FileSelectFolder(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileSelectFolder(vParams, vResult); }

AUT_RESULT F_DriveMapAdd(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveMapAdd(vParams, vResult); }

AUT_RESULT F_DriveMapDel(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveMapDel(vParams, vResult); }

AUT_RESULT F_DriveMapGet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveMapGet(vParams, vResult); }

AUT_RESULT F_DriveSpaceTotal(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveSpaceTotal(vParams, vResult); }

AUT_RESULT F_DriveSpaceFree(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveSpaceFree(vParams, vResult); }

AUT_RESULT F_FileCreateShortcut(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileCreateShortcut(vParams, vResult); }

AUT_RESULT F_FileGetShortcut(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetShortcut(vParams, vResult); }

AUT_RESULT F_DriveStatus(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveStatus(vParams, vResult); }

AUT_RESULT F_FileExists(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileExists(vParams, vResult); }

AUT_RESULT F_FileFindFirstFile(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileFindFirstFile(vParams, vResult); }

AUT_RESULT F_FileFindNextFile(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileFindNextFile(vParams, vResult); }

AUT_RESULT F_DirCreate(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DirCreate(vParams, vResult); }

AUT_RESULT F_DirRemove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DirRemove(vParams, vResult); }

AUT_RESULT F_CDTray(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_CDTray(vParams, vResult); }

AUT_RESULT F_DriveGetDrive(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveGetDrive(vParams, vResult); }

AUT_RESULT F_FileCopy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileCopy(vParams, vResult); }

AUT_RESULT F_FileDelete(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileDelete(vParams, vResult); }

AUT_RESULT F_FileInstall(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileInstall(vParams, vResult); }

AUT_RESULT F_FileRecycle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileRecycle(vParams, vResult); }

AUT_RESULT F_DriveGetLabel(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveGetLabel(vParams, vResult); }

AUT_RESULT F_DriveGetSerial(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveGetSerial(vParams, vResult); }

AUT_RESULT F_DriveGetFileSystem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveGetFileSystem(vParams, vResult); }

AUT_RESULT F_DriveSetLabel(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveSetLabel(vParams, vResult); }

AUT_RESULT F_DriveGetType(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DriveGetType(vParams, vResult); }

AUT_RESULT F_FileMove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileMove(vParams, vResult); }

AUT_RESULT F_FileGetAttrib(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetAttrib(vParams, vResult); }

AUT_RESULT F_FileGetVersion(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetVersion(vParams, vResult); }

AUT_RESULT F_FileGetLongName(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetLongName(vParams, vResult); }

AUT_RESULT F_FileGetShortName(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileGetShortName(vParams, vResult); }

AUT_RESULT F_FileChangeDir(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileChangeDir(vParams, vResult); }

AUT_RESULT F_FileSetAttrib(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileSetAttrib(vParams, vResult); }

AUT_RESULT F_FileSetTime(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileSetTime(vParams, vResult); }

AUT_RESULT F_DirMove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DirMove(vParams, vResult); }

AUT_RESULT F_FileRead(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileRead(vParams, vResult); }

AUT_RESULT F_FileRecycleEmpty(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_FileRecycleEmpty(vParams, vResult); }

AUT_RESULT F_DirGetSize(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleFile*)self)->F_DirGetSize(vParams, vResult); }

            
#include "Modules/Gui/ModuleGui.h"

AUT_RESULT F_GUICreate(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICreate(vParams, vResult); }

AUT_RESULT F_GUISwitch(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISwitch(vParams, vResult); }

AUT_RESULT F_GUICtrlDelete(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlDelete(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateAvi(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateAvi(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateButton(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateButton(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateCombo(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateCombo(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateContextMenu(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateContextMenu(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateDate(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateDate(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateEdit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateEdit(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateGroup(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateGroup(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateIcon(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateIcon(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateInput(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateInput(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateLabel(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateLabel(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateList(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateList(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateMenu(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateMenu(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateMenuItem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateMenuItem(vParams, vResult); }

AUT_RESULT F_GUICtrlCreatePic(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreatePic(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateProgress(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateProgress(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateRadio(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateRadio(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateSlider(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateSlider(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateTab(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateTab(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateTabitem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateTabitem(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateTrayMenu(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateTrayMenu(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateTreeView(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateTreeView(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateTreeViewItem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateTreeViewItem(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateListView(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateListView(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateListViewItem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateListViewItem(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateUpdown(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateUpdown(vParams, vResult); }

AUT_RESULT F_GUICtrlCreateDummy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlCreateDummy(vParams, vResult); }

AUT_RESULT F_GUICtrlGetState(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlGetState(vParams, vResult); }

AUT_RESULT F_GUICtrlSetBkColor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetBkColor(vParams, vResult); }

AUT_RESULT F_GUICtrlSetOnEvent(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetOnEvent(vParams, vResult); }

AUT_RESULT F_GUICtrlSetColor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetColor(vParams, vResult); }

AUT_RESULT F_GUICtrlSetCursor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetCursor(vParams, vResult); }

AUT_RESULT F_GUICtrlSetData(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetData(vParams, vResult); }

AUT_RESULT F_GUICtrlSetImage(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetImage(vParams, vResult); }

AUT_RESULT F_GUICtrlSetFont(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetFont(vParams, vResult); }

AUT_RESULT F_GUICtrlSetLimit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetLimit(vParams, vResult); }

AUT_RESULT F_GUICtrlSetPos(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetPos(vParams, vResult); }

AUT_RESULT F_GUICtrlSetResizing(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetResizing(vParams, vResult); }

AUT_RESULT F_GUICtrlSetState(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetState(vParams, vResult); }

AUT_RESULT F_GUICtrlSetStyle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetStyle(vParams, vResult); }

AUT_RESULT F_GUICtrlSetTip(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUICtrlSetTip(vParams, vResult); }

AUT_RESULT F_GUIDelete(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIDelete(vParams, vResult); }

AUT_RESULT F_GUIGetMsg(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIGetMsg(vParams, vResult); }

AUT_RESULT F_GUIRead(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIRead(vParams, vResult); }

AUT_RESULT F_GUISendToDummy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISendToDummy(vParams, vResult); }

AUT_RESULT F_GUISendMsg(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISendMsg(vParams, vResult); }

AUT_RESULT F_GUIRecvMsg(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIRecvMsg(vParams, vResult); }

AUT_RESULT F_GUISetBkColor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetBkColor(vParams, vResult); }

AUT_RESULT F_GUISetCoord(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetCoord(vParams, vResult); }

AUT_RESULT F_GUIGetCursorInfo(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIGetCursorInfo(vParams, vResult); }

AUT_RESULT F_GUISetOnEvent(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetOnEvent(vParams, vResult); }

AUT_RESULT F_GUISetCursor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetCursor(vParams, vResult); }

AUT_RESULT F_GUISetFont(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetFont(vParams, vResult); }

AUT_RESULT F_GUISetHelp(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetHelp(vParams, vResult); }

AUT_RESULT F_GUISetIcon(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetIcon(vParams, vResult); }

AUT_RESULT F_GUISetState(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetState(vParams, vResult); }

AUT_RESULT F_GUISetTrayTip(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetTrayTip(vParams, vResult); }

AUT_RESULT F_GUISetTrayBalloon(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetTrayBalloon(vParams, vResult); }

AUT_RESULT F_GUISetTrayIcon(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUISetTrayIcon(vParams, vResult); }

AUT_RESULT F_GUIStartGroup(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleGui*)self)->F_GUIStartGroup(vParams, vResult); }

            
#include "Modules/Keyboard/ModuleKeyboard.h"

AUT_RESULT F_Send(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleKeyboard*)self)->F_Send(vParams, vResult); }

AUT_RESULT F_HotKeySet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleKeyboard*)self)->F_HotKeySet(vParams, vResult); }

            
#include "Modules/Math/ModuleMath.h"

AUT_RESULT F_Hex(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMath*)self)->F_Hex(vParams, vResult); }

            
#include "Modules/Mouse/ModuleMouse.h"

AUT_RESULT F_MouseDown(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseDown(vParams, vResult); }

AUT_RESULT F_MouseUp(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseUp(vParams, vResult); }

AUT_RESULT F_MouseClick(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseClick(vParams, vResult); }

AUT_RESULT F_MouseMove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseMove(vParams, vResult); }

AUT_RESULT F_MouseGetPos(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseGetPos(vParams, vResult); }

AUT_RESULT F_MouseGetCursor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseGetCursor(vParams, vResult); }

AUT_RESULT F_MouseClickDrag(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseClickDrag(vParams, vResult); }

AUT_RESULT F_MouseWheel(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleMouse*)self)->F_MouseWheel(vParams, vResult); }

            
#include "Modules/Net/ModuleNet.h"

AUT_RESULT F_HttpSetProxy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleNet*)self)->F_HttpSetProxy(vParams, vResult); }

AUT_RESULT F_FtpSetProxy(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleNet*)self)->F_FtpSetProxy(vParams, vResult); }

            
#include "Modules/Reg/ModuleReg.h"

AUT_RESULT F_RegRead(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleReg*)self)->F_RegRead(vParams, vResult); }

AUT_RESULT F_RegWrite(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleReg*)self)->F_RegWrite(vParams, vResult); }

AUT_RESULT F_RegDelete(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleReg*)self)->F_RegDelete(vParams, vResult); }

AUT_RESULT F_RegEnumKey(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleReg*)self)->F_RegEnumKey(vParams, vResult); }

AUT_RESULT F_RegEnumVal(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleReg*)self)->F_RegEnumVal(vParams, vResult); }

            
#include "Modules/Sound/ModuleSound.h"

AUT_RESULT F_SoundPlay(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSound*)self)->F_SoundPlay(vParams, vResult); }

AUT_RESULT F_SoundSetWaveVolume(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSound*)self)->F_SoundSetWaveVolume(vParams, vResult); }

            
#include "Modules/Sys/ModuleSys.h"

AUT_RESULT F_Run(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_Run(vParams, vResult); }

AUT_RESULT F_RunWait(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_RunWait(vParams, vResult); }

AUT_RESULT F_RunAsSet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_RunAsSet(vParams, vResult); }

AUT_RESULT F_ProcessClose(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ProcessClose(vParams, vResult); }

AUT_RESULT F_ProcessExists(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ProcessExists(vParams, vResult); }

AUT_RESULT F_ProcessWait(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ProcessWait(vParams, vResult); }

AUT_RESULT F_Shutdown(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_Shutdown(vParams, vResult); }

AUT_RESULT F_ProcessSetPriority(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ProcessSetPriority(vParams, vResult); }

AUT_RESULT F_ProcessList(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ProcessList(vParams, vResult); }

AUT_RESULT F_DllCall(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_DllCall(vParams, vResult); }

AUT_RESULT F_DllOpen(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_DllOpen(vParams, vResult); }

AUT_RESULT F_DllClose(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_DllClose(vParams, vResult); }

AUT_RESULT F_EnvGet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_EnvGet(vParams, vResult); }

AUT_RESULT F_EnvSet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_EnvSet(vParams, vResult); }

AUT_RESULT F_EnvUpdate(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_EnvUpdate(vParams, vResult); }

AUT_RESULT F_Sleep(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_Sleep(vParams, vResult); }

AUT_RESULT F_BlockInput(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_BlockInput(vParams, vResult); }

AUT_RESULT F_AdlibDisable(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_AdlibDisable(vParams, vResult); }

AUT_RESULT F_AdlibEnable(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_AdlibEnable(vParams, vResult); }

AUT_RESULT F_ClipGet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ClipGet(vParams, vResult); }

AUT_RESULT F_ClipPut(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_ClipPut(vParams, vResult); }

AUT_RESULT F_IsAdmin(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_IsAdmin(vParams, vResult); }

AUT_RESULT F_SetError(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_SetError(vParams, vResult); }

AUT_RESULT F_SetExtended(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_SetExtended(vParams, vResult); }

AUT_RESULT F_Break(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_Break(vParams, vResult); }

AUT_RESULT F_AutoItSetOption(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_AutoItSetOption(vParams, vResult); }

AUT_RESULT F_TimerInit(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_TimerInit(vParams, vResult); }

AUT_RESULT F_TimerDiff(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_TimerDiff(vParams, vResult); }

AUT_RESULT F_MemGetStats(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleSys*)self)->F_MemGetStats(vParams, vResult); }

            
#include "Modules/Win/ModuleWin.h"

AUT_RESULT F_WinExists(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinExists(vParams, vResult); }

AUT_RESULT F_WinActive(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinActive(vParams, vResult); }

AUT_RESULT F_WinWait(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinWait(vParams, vResult); }

AUT_RESULT F_WinWaitActive(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinWaitActive(vParams, vResult); }

AUT_RESULT F_WinWaitNotActive(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinWaitNotActive(vParams, vResult); }

AUT_RESULT F_WinWaitClose(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinWaitClose(vParams, vResult); }

AUT_RESULT F_WinActivate(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinActivate(vParams, vResult); }

AUT_RESULT F_WinShow(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinShow(vParams, vResult); }

AUT_RESULT F_WinClose(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinClose(vParams, vResult); }

AUT_RESULT F_WinKill(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinKill(vParams, vResult); }

AUT_RESULT F_WinMinimizeAll(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinMinimizeAll(vParams, vResult); }

AUT_RESULT F_WinMinimizeAllUndo(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinMinimizeAllUndo(vParams, vResult); }

AUT_RESULT F_WinSetTitle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinSetTitle(vParams, vResult); }

AUT_RESULT F_WinMove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinMove(vParams, vResult); }

AUT_RESULT F_WinGetTitle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetTitle(vParams, vResult); }

AUT_RESULT F_WinGetText(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetText(vParams, vResult); }

AUT_RESULT F_ControlClick(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlClick(vParams, vResult); }

AUT_RESULT F_ControlFocus(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlFocus(vParams, vResult); }

AUT_RESULT F_ControlGetFocus(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlGetFocus(vParams, vResult); }

AUT_RESULT F_WinSetOnTop(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinSetOnTop(vParams, vResult); }

AUT_RESULT F_WinGetPos(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetPos(vParams, vResult); }

AUT_RESULT F_ControlGetText(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlGetText(vParams, vResult); }

AUT_RESULT F_ControlSetText(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlSetText(vParams, vResult); }

AUT_RESULT F_ControlGetPos(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlGetPos(vParams, vResult); }

AUT_RESULT F_ControlCommand(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlCommand(vParams, vResult); }

AUT_RESULT F_ControlListView(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlListView(vParams, vResult); }

AUT_RESULT F_ControlTreeView(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlTreeView(vParams, vResult); }

AUT_RESULT F_ControlEnable(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlEnable(vParams, vResult); }

AUT_RESULT F_ControlDisable(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlDisable(vParams, vResult); }

AUT_RESULT F_ControlHide(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlHide(vParams, vResult); }

AUT_RESULT F_ControlMove(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlMove(vParams, vResult); }

AUT_RESULT F_ControlShow(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlShow(vParams, vResult); }

AUT_RESULT F_WinGetClassList(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetClassList(vParams, vResult); }

AUT_RESULT F_StatusbarGetText(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_StatusbarGetText(vParams, vResult); }

AUT_RESULT F_ControlSend(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlSend(vParams, vResult); }

AUT_RESULT F_WinMenuSelectItem(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinMenuSelectItem(vParams, vResult); }

AUT_RESULT F_WinGetClientSize(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetClientSize(vParams, vResult); }

AUT_RESULT F_WinGetHandle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetHandle(vParams, vResult); }

AUT_RESULT F_ControlGetHandle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ControlGetHandle(vParams, vResult); }

AUT_RESULT F_WinGetCaretPos(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetCaretPos(vParams, vResult); }

AUT_RESULT F_WinGetState(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetState(vParams, vResult); }

AUT_RESULT F_WinSetTrans(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinSetTrans(vParams, vResult); }

AUT_RESULT F_ToolTip(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ToolTip(vParams, vResult); }

AUT_RESULT F_WinList(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinList(vParams, vResult); }

AUT_RESULT F_WinGetProcess(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_WinGetProcess(vParams, vResult); }

AUT_RESULT F_TrayTip(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_TrayTip(vParams, vResult); }

AUT_RESULT F_AutoItWinSetTitle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_AutoItWinSetTitle(vParams, vResult); }

AUT_RESULT F_AutoItWinGetTitle(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_AutoItWinGetTitle(vParams, vResult); }

AUT_RESULT F_PixelSearch(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_PixelSearch(vParams, vResult); }

AUT_RESULT F_PixelGetColor(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_PixelGetColor(vParams, vResult); }

AUT_RESULT F_SplashImageOn(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_SplashImageOn(vParams, vResult); }

AUT_RESULT F_SplashTextOn(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_SplashTextOn(vParams, vResult); }

AUT_RESULT F_SplashOff(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_SplashOff(vParams, vResult); }

AUT_RESULT F_ProgressOn(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ProgressOn(vParams, vResult); }

AUT_RESULT F_ProgressOff(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ProgressOff(vParams, vResult); }

AUT_RESULT F_ProgressSet(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_ProgressSet(vParams, vResult); }

AUT_RESULT F_InputBox(void *self, VectorVariant &vParams, Variant &vResult)
{ return ((ModuleWin*)self)->F_InputBox(vParams, vResult); }

            
AU3_FuncInfo funcInfo[] = {

    {NULL, "ModuleSys", "ADLIBDISABLE", &F_AdlibDisable, 1, 1},

    {NULL, "ModuleSys", "ADLIBENABLE", &F_AdlibEnable, 1, 1},

    {NULL, "ModuleBuiltIn", "ASC", &F_Asc, 1, 1},

    {NULL, "ModuleBuiltIn", "ASSIGN", &F_Assign, 1, 1},

    {NULL, "ModuleSys", "AUTOITSETOPTION", &F_AutoItSetOption, 1, 1},

    {NULL, "ModuleWin", "AUTOITWINGETTITLE", &F_AutoItWinGetTitle, 1, 1},

    {NULL, "ModuleWin", "AUTOITWINSETTITLE", &F_AutoItWinSetTitle, 1, 1},

    {NULL, "ModuleBuiltIn", "BITAND", &F_BitAND, 1, 1},

    {NULL, "ModuleBuiltIn", "BITNOT", &F_BitNOT, 1, 1},

    {NULL, "ModuleBuiltIn", "BITOR", &F_BitOR, 1, 1},

    {NULL, "ModuleBuiltIn", "BITSHIFT", &F_BitShift, 1, 1},

    {NULL, "ModuleBuiltIn", "BITXOR", &F_BitXOR, 1, 1},

    {NULL, "ModuleSys", "BLOCKINPUT", &F_BlockInput, 1, 1},

    {NULL, "ModuleSys", "BREAK", &F_Break, 1, 1},

    {NULL, "ModuleFile", "CDTRAY", &F_CDTray, 1, 1},

    {NULL, "ModuleBuiltIn", "CALL", &F_Call, 1, 1},

    {NULL, "ModuleBuiltIn", "CHR", &F_Chr, 1, 1},

    {NULL, "ModuleSys", "CLIPGET", &F_ClipGet, 1, 1},

    {NULL, "ModuleSys", "CLIPPUT", &F_ClipPut, 1, 1},

    {NULL, "ModuleBuiltIn", "CONSOLEWRITE", &F_ConsoleWrite, 1, 1},

    {NULL, "ModuleWin", "CONTROLCLICK", &F_ControlClick, 1, 1},

    {NULL, "ModuleWin", "CONTROLCOMMAND", &F_ControlCommand, 1, 1},

    {NULL, "ModuleWin", "CONTROLDISABLE", &F_ControlDisable, 1, 1},

    {NULL, "ModuleWin", "CONTROLENABLE", &F_ControlEnable, 1, 1},

    {NULL, "ModuleWin", "CONTROLFOCUS", &F_ControlFocus, 1, 1},

    {NULL, "ModuleWin", "CONTROLGETFOCUS", &F_ControlGetFocus, 1, 1},

    {NULL, "ModuleWin", "CONTROLGETHANDLE", &F_ControlGetHandle, 1, 1},

    {NULL, "ModuleWin", "CONTROLGETPOS", &F_ControlGetPos, 1, 1},

    {NULL, "ModuleWin", "CONTROLGETTEXT", &F_ControlGetText, 1, 1},

    {NULL, "ModuleWin", "CONTROLHIDE", &F_ControlHide, 1, 1},

    {NULL, "ModuleWin", "CONTROLLISTVIEW", &F_ControlListView, 1, 1},

    {NULL, "ModuleWin", "CONTROLMOVE", &F_ControlMove, 1, 1},

    {NULL, "ModuleWin", "CONTROLSEND", &F_ControlSend, 1, 1},

    {NULL, "ModuleWin", "CONTROLSETTEXT", &F_ControlSetText, 1, 1},

    {NULL, "ModuleWin", "CONTROLSHOW", &F_ControlShow, 1, 1},

    {NULL, "ModuleWin", "CONTROLTREEVIEW", &F_ControlTreeView, 1, 1},

    {NULL, "ModuleBuiltIn", "DEC", &F_Dec, 1, 1},

    {NULL, "ModuleFile", "DIRCOPY", &F_DirCopy, 1, 1},

    {NULL, "ModuleFile", "DIRCREATE", &F_DirCreate, 1, 1},

    {NULL, "ModuleFile", "DIRGETSIZE", &F_DirGetSize, 1, 1},

    {NULL, "ModuleFile", "DIRMOVE", &F_DirMove, 1, 1},

    {NULL, "ModuleFile", "DIRREMOVE", &F_DirRemove, 1, 1},

    {NULL, "ModuleSys", "DLLCALL", &F_DllCall, 1, 1},

    {NULL, "ModuleSys", "DLLCLOSE", &F_DllClose, 1, 1},

    {NULL, "ModuleSys", "DLLOPEN", &F_DllOpen, 1, 1},

    {NULL, "ModuleFile", "DRIVEGETDRIVE", &F_DriveGetDrive, 1, 1},

    {NULL, "ModuleFile", "DRIVEGETFILESYSTEM", &F_DriveGetFileSystem, 1, 1},

    {NULL, "ModuleFile", "DRIVEGETLABEL", &F_DriveGetLabel, 1, 1},

    {NULL, "ModuleFile", "DRIVEGETSERIAL", &F_DriveGetSerial, 1, 1},

    {NULL, "ModuleFile", "DRIVEGETTYPE", &F_DriveGetType, 1, 1},

    {NULL, "ModuleFile", "DRIVEMAPADD", &F_DriveMapAdd, 1, 1},

    {NULL, "ModuleFile", "DRIVEMAPDEL", &F_DriveMapDel, 1, 1},

    {NULL, "ModuleFile", "DRIVEMAPGET", &F_DriveMapGet, 1, 1},

    {NULL, "ModuleFile", "DRIVESETLABEL", &F_DriveSetLabel, 1, 1},

    {NULL, "ModuleFile", "DRIVESPACEFREE", &F_DriveSpaceFree, 1, 1},

    {NULL, "ModuleFile", "DRIVESPACETOTAL", &F_DriveSpaceTotal, 1, 1},

    {NULL, "ModuleFile", "DRIVESTATUS", &F_DriveStatus, 1, 1},

    {NULL, "ModuleSys", "ENVGET", &F_EnvGet, 1, 1},

    {NULL, "ModuleSys", "ENVSET", &F_EnvSet, 1, 1},

    {NULL, "ModuleSys", "ENVUPDATE", &F_EnvUpdate, 1, 1},

    {NULL, "ModuleBuiltIn", "EVAL", &F_Eval, 1, 1},

    {NULL, "ModuleFile", "FILECHANGEDIR", &F_FileChangeDir, 1, 1},

    {NULL, "ModuleFile", "FILECLOSE", &F_FileClose, 1, 1},

    {NULL, "ModuleFile", "FILECOPY", &F_FileCopy, 1, 1},

    {NULL, "ModuleFile", "FILECREATESHORTCUT", &F_FileCreateShortcut, 1, 1},

    {NULL, "ModuleFile", "FILEDELETE", &F_FileDelete, 1, 1},

    {NULL, "ModuleFile", "FILEEXISTS", &F_FileExists, 1, 1},

    {NULL, "ModuleFile", "FILEFINDFIRSTFILE", &F_FileFindFirstFile, 1, 1},

    {NULL, "ModuleFile", "FILEFINDNEXTFILE", &F_FileFindNextFile, 1, 1},

    {NULL, "ModuleFile", "FILEGETATTRIB", &F_FileGetAttrib, 1, 1},

    {NULL, "ModuleFile", "FILEGETLONGNAME", &F_FileGetLongName, 1, 1},

    {NULL, "ModuleFile", "FILEGETSHORTNAME", &F_FileGetShortName, 1, 1},

    {NULL, "ModuleFile", "FILEGETSHORTCUT", &F_FileGetShortcut, 1, 1},

    {NULL, "ModuleFile", "FILEGETSIZE", &F_FileGetSize, 1, 1},

    {NULL, "ModuleFile", "FILEGETTIME", &F_FileGetTime, 1, 1},

    {NULL, "ModuleFile", "FILEGETVERSION", &F_FileGetVersion, 1, 1},

    {NULL, "ModuleFile", "FILEINSTALL", &F_FileInstall, 1, 1},

    {NULL, "ModuleFile", "FILEMOVE", &F_FileMove, 1, 1},

    {NULL, "ModuleFile", "FILEOPEN", &F_FileOpen, 1, 1},

    {NULL, "ModuleFile", "FILEOPENDIALOG", &F_FileOpenDialog, 1, 1},

    {NULL, "ModuleFile", "FILEREAD", &F_FileRead, 1, 1},

    {NULL, "ModuleFile", "FILEREADLINE", &F_FileReadLine, 1, 1},

    {NULL, "ModuleFile", "FILERECYCLE", &F_FileRecycle, 1, 1},

    {NULL, "ModuleFile", "FILERECYCLEEMPTY", &F_FileRecycleEmpty, 1, 1},

    {NULL, "ModuleFile", "FILESAVEDIALOG", &F_FileSaveDialog, 1, 1},

    {NULL, "ModuleFile", "FILESELECTFOLDER", &F_FileSelectFolder, 1, 1},

    {NULL, "ModuleFile", "FILESETATTRIB", &F_FileSetAttrib, 1, 1},

    {NULL, "ModuleFile", "FILESETTIME", &F_FileSetTime, 1, 1},

    {NULL, "ModuleFile", "FILEWRITE", &F_FileWrite, 1, 1},

    {NULL, "ModuleFile", "FILEWRITELINE", &F_FileWriteLine, 1, 1},

    {NULL, "ModuleNet", "FTPSETPROXY", &F_FtpSetProxy, 1, 1},

    {NULL, "ModuleGui", "GUICREATE", &F_GUICreate, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEAVI", &F_GUICtrlCreateAvi, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEBUTTON", &F_GUICtrlCreateButton, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATECOMBO", &F_GUICtrlCreateCombo, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATECONTEXTMENU", &F_GUICtrlCreateContextMenu, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEDATE", &F_GUICtrlCreateDate, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEDUMMY", &F_GUICtrlCreateDummy, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEEDIT", &F_GUICtrlCreateEdit, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEGROUP", &F_GUICtrlCreateGroup, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEICON", &F_GUICtrlCreateIcon, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEINPUT", &F_GUICtrlCreateInput, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATELABEL", &F_GUICtrlCreateLabel, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATELIST", &F_GUICtrlCreateList, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATELISTVIEW", &F_GUICtrlCreateListView, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATELISTVIEWITEM", &F_GUICtrlCreateListViewItem, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEMENU", &F_GUICtrlCreateMenu, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEMENUITEM", &F_GUICtrlCreateMenuItem, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEPIC", &F_GUICtrlCreatePic, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEPROGRESS", &F_GUICtrlCreateProgress, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATERADIO", &F_GUICtrlCreateRadio, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATESLIDER", &F_GUICtrlCreateSlider, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATETAB", &F_GUICtrlCreateTab, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATETABITEM", &F_GUICtrlCreateTabitem, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATETRAYMENU", &F_GUICtrlCreateTrayMenu, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATETREEVIEW", &F_GUICtrlCreateTreeView, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATETREEVIEWITEM", &F_GUICtrlCreateTreeViewItem, 1, 1},

    {NULL, "ModuleGui", "GUICTRLCREATEUPDOWN", &F_GUICtrlCreateUpdown, 1, 1},

    {NULL, "ModuleGui", "GUICTRLDELETE", &F_GUICtrlDelete, 1, 1},

    {NULL, "ModuleGui", "GUICTRLGETSTATE", &F_GUICtrlGetState, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETBKCOLOR", &F_GUICtrlSetBkColor, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETCOLOR", &F_GUICtrlSetColor, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETCURSOR", &F_GUICtrlSetCursor, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETDATA", &F_GUICtrlSetData, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETFONT", &F_GUICtrlSetFont, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETIMAGE", &F_GUICtrlSetImage, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETLIMIT", &F_GUICtrlSetLimit, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETONEVENT", &F_GUICtrlSetOnEvent, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETPOS", &F_GUICtrlSetPos, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETRESIZING", &F_GUICtrlSetResizing, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETSTATE", &F_GUICtrlSetState, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETSTYLE", &F_GUICtrlSetStyle, 1, 1},

    {NULL, "ModuleGui", "GUICTRLSETTIP", &F_GUICtrlSetTip, 1, 1},

    {NULL, "ModuleGui", "GUIDELETE", &F_GUIDelete, 1, 1},

    {NULL, "ModuleGui", "GUIGETCURSORINFO", &F_GUIGetCursorInfo, 1, 1},

    {NULL, "ModuleGui", "GUIGETMSG", &F_GUIGetMsg, 1, 1},

    {NULL, "ModuleGui", "GUIREAD", &F_GUIRead, 1, 1},

    {NULL, "ModuleGui", "GUIRECVMSG", &F_GUIRecvMsg, 1, 1},

    {NULL, "ModuleGui", "GUISENDMSG", &F_GUISendMsg, 1, 1},

    {NULL, "ModuleGui", "GUISENDTODUMMY", &F_GUISendToDummy, 1, 1},

    {NULL, "ModuleGui", "GUISETBKCOLOR", &F_GUISetBkColor, 1, 1},

    {NULL, "ModuleGui", "GUISETCOORD", &F_GUISetCoord, 1, 1},

    {NULL, "ModuleGui", "GUISETCURSOR", &F_GUISetCursor, 1, 1},

    {NULL, "ModuleGui", "GUISETFONT", &F_GUISetFont, 1, 1},

    {NULL, "ModuleGui", "GUISETHELP", &F_GUISetHelp, 1, 1},

    {NULL, "ModuleGui", "GUISETICON", &F_GUISetIcon, 1, 1},

    {NULL, "ModuleGui", "GUISETONEVENT", &F_GUISetOnEvent, 1, 1},

    {NULL, "ModuleGui", "GUISETSTATE", &F_GUISetState, 1, 1},

    {NULL, "ModuleGui", "GUISETTRAYBALLOON", &F_GUISetTrayBalloon, 1, 1},

    {NULL, "ModuleGui", "GUISETTRAYICON", &F_GUISetTrayIcon, 1, 1},

    {NULL, "ModuleGui", "GUISETTRAYTIP", &F_GUISetTrayTip, 1, 1},

    {NULL, "ModuleGui", "GUISTARTGROUP", &F_GUIStartGroup, 1, 1},

    {NULL, "ModuleGui", "GUISWITCH", &F_GUISwitch, 1, 1},

    {NULL, "ModuleMath", "HEX", &F_Hex, 1, 1},

    {NULL, "ModuleKeyboard", "HOTKEYSET", &F_HotKeySet, 1, 1},

    {NULL, "ModuleNet", "HTTPSETPROXY", &F_HttpSetProxy, 1, 1},

    {NULL, "ModuleFile", "INIDELETE", &F_IniDelete, 1, 1},

    {NULL, "ModuleFile", "INIREAD", &F_IniRead, 1, 1},

    {NULL, "ModuleFile", "INIREADSECTION", &F_IniReadSection, 1, 1},

    {NULL, "ModuleFile", "INIREADSECTIONNAMES", &F_IniReadSectionNames, 1, 1},

    {NULL, "ModuleFile", "INIWRITE", &F_IniWrite, 1, 1},

    {NULL, "ModuleWin", "INPUTBOX", &F_InputBox, 1, 1},

    {NULL, "ModuleBuiltIn", "INT", &F_Int, 1, 1},

    {NULL, "ModuleSys", "ISADMIN", &F_IsAdmin, 1, 1},

    {NULL, "ModuleBuiltIn", "ISARRAY", &F_IsArray, 1, 1},

    {NULL, "ModuleBuiltIn", "ISDECLARED", &F_IsDeclared, 1, 1},

    {NULL, "ModuleBuiltIn", "ISFLOAT", &F_IsFloat, 1, 1},

    {NULL, "ModuleBuiltIn", "ISINT", &F_IsInt, 1, 1},

    {NULL, "ModuleBuiltIn", "ISNUMBER", &F_IsNumber, 1, 1},

    {NULL, "ModuleBuiltIn", "ISSTRING", &F_IsString, 1, 1},

    {NULL, "ModuleSys", "MEMGETSTATS", &F_MemGetStats, 1, 1},

    {NULL, "ModuleMouse", "MOUSECLICK", &F_MouseClick, 1, 1},

    {NULL, "ModuleMouse", "MOUSECLICKDRAG", &F_MouseClickDrag, 1, 1},

    {NULL, "ModuleMouse", "MOUSEDOWN", &F_MouseDown, 1, 1},

    {NULL, "ModuleMouse", "MOUSEGETCURSOR", &F_MouseGetCursor, 1, 1},

    {NULL, "ModuleMouse", "MOUSEGETPOS", &F_MouseGetPos, 1, 1},

    {NULL, "ModuleMouse", "MOUSEMOVE", &F_MouseMove, 1, 1},

    {NULL, "ModuleMouse", "MOUSEUP", &F_MouseUp, 1, 1},

    {NULL, "ModuleMouse", "MOUSEWHEEL", &F_MouseWheel, 1, 1},

    {NULL, "ModuleBuiltIn", "NUMBER", &F_Number, 1, 1},

    {NULL, "ModuleWin", "PIXELGETCOLOR", &F_PixelGetColor, 1, 1},

    {NULL, "ModuleWin", "PIXELSEARCH", &F_PixelSearch, 1, 1},

    {NULL, "ModuleSys", "PROCESSCLOSE", &F_ProcessClose, 1, 1},

    {NULL, "ModuleSys", "PROCESSEXISTS", &F_ProcessExists, 1, 1},

    {NULL, "ModuleSys", "PROCESSLIST", &F_ProcessList, 1, 1},

    {NULL, "ModuleSys", "PROCESSSETPRIORITY", &F_ProcessSetPriority, 1, 1},

    {NULL, "ModuleSys", "PROCESSWAIT", &F_ProcessWait, 1, 1},

    {NULL, "ModuleWin", "PROGRESSOFF", &F_ProgressOff, 1, 1},

    {NULL, "ModuleWin", "PROGRESSON", &F_ProgressOn, 1, 1},

    {NULL, "ModuleWin", "PROGRESSSET", &F_ProgressSet, 1, 1},

    {NULL, "ModuleBuiltIn", "RANDOM", &F_Random, 1, 1},

    {NULL, "ModuleReg", "REGDELETE", &F_RegDelete, 1, 1},

    {NULL, "ModuleReg", "REGENUMKEY", &F_RegEnumKey, 1, 1},

    {NULL, "ModuleReg", "REGENUMVAL", &F_RegEnumVal, 1, 1},

    {NULL, "ModuleReg", "REGREAD", &F_RegRead, 1, 1},

    {NULL, "ModuleReg", "REGWRITE", &F_RegWrite, 1, 1},

    {NULL, "ModuleSys", "RUN", &F_Run, 1, 1},

    {NULL, "ModuleSys", "RUNASSET", &F_RunAsSet, 1, 1},

    {NULL, "ModuleSys", "RUNWAIT", &F_RunWait, 1, 1},

    {NULL, "ModuleKeyboard", "SEND", &F_Send, 1, 1},

    {NULL, "ModuleSys", "SETERROR", &F_SetError, 1, 1},

    {NULL, "ModuleSys", "SETEXTENDED", &F_SetExtended, 1, 1},

    {NULL, "ModuleSys", "SHUTDOWN", &F_Shutdown, 1, 1},

    {NULL, "ModuleSys", "SLEEP", &F_Sleep, 1, 1},

    {NULL, "ModuleSound", "SOUNDPLAY", &F_SoundPlay, 1, 1},

    {NULL, "ModuleSound", "SOUNDSETWAVEVOLUME", &F_SoundSetWaveVolume, 1, 1},

    {NULL, "ModuleWin", "SPLASHIMAGEON", &F_SplashImageOn, 1, 1},

    {NULL, "ModuleWin", "SPLASHOFF", &F_SplashOff, 1, 1},

    {NULL, "ModuleWin", "SPLASHTEXTON", &F_SplashTextOn, 1, 1},

    {NULL, "ModuleWin", "STATUSBARGETTEXT", &F_StatusbarGetText, 1, 1},

    {NULL, "ModuleBuiltIn", "STRING", &F_String, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGADDCR", &F_StringAddCR, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGFORMAT", &F_StringFormat, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGINSTR", &F_StringInStr, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISASCII", &F_StringIsASCII, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISALNUM", &F_StringIsAlnum, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISALPHA", &F_StringIsAlpha, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISDIGIT", &F_StringIsDigit, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISFLOAT", &F_StringIsFloat, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISINT", &F_StringIsInt, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISLOWER", &F_StringIsLower, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISSPACE", &F_StringIsSpace, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISUPPER", &F_StringIsUpper, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGISXDIGIT", &F_StringIsXDigit, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGLEFT", &F_StringLeft, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGLEN", &F_StringLen, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGLOWER", &F_StringLower, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGMID", &F_StringMid, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGREGEXP", &F_StringRegExp, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGREGEXPREPLACE", &F_StringRegExpReplace, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGREPLACE", &F_StringReplace, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGRIGHT", &F_StringRight, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGSPLIT", &F_StringSplit, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGSTRIPCR", &F_StringStripCR, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGSTRIPWS", &F_StringStripWS, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGTRIMLEFT", &F_StringTrimLeft, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGTRIMRIGHT", &F_StringTrimRight, 1, 1},

    {NULL, "ModuleBuiltIn", "STRINGUPPER", &F_StringUpper, 1, 1},

    {NULL, "ModuleSys", "TIMERDIFF", &F_TimerDiff, 1, 1},

    {NULL, "ModuleSys", "TIMERINIT", &F_TimerInit, 1, 1},

    {NULL, "ModuleWin", "TOOLTIP", &F_ToolTip, 1, 1},

    {NULL, "ModuleWin", "TRAYTIP", &F_TrayTip, 1, 1},

    {NULL, "ModuleBuiltIn", "UBOUND", &F_UBound, 1, 1},

    {NULL, "ModuleBuiltIn", "VARTYPE", &F_VarType, 1, 1},

    {NULL, "ModuleWin", "WINACTIVATE", &F_WinActivate, 1, 1},

    {NULL, "ModuleWin", "WINACTIVE", &F_WinActive, 1, 1},

    {NULL, "ModuleWin", "WINCLOSE", &F_WinClose, 1, 1},

    {NULL, "ModuleWin", "WINEXISTS", &F_WinExists, 1, 1},

    {NULL, "ModuleWin", "WINGETCARETPOS", &F_WinGetCaretPos, 1, 1},

    {NULL, "ModuleWin", "WINGETCLASSLIST", &F_WinGetClassList, 1, 1},

    {NULL, "ModuleWin", "WINGETCLIENTSIZE", &F_WinGetClientSize, 1, 1},

    {NULL, "ModuleWin", "WINGETHANDLE", &F_WinGetHandle, 1, 1},

    {NULL, "ModuleWin", "WINGETPOS", &F_WinGetPos, 1, 1},

    {NULL, "ModuleWin", "WINGETPROCESS", &F_WinGetProcess, 1, 1},

    {NULL, "ModuleWin", "WINGETSTATE", &F_WinGetState, 1, 1},

    {NULL, "ModuleWin", "WINGETTEXT", &F_WinGetText, 1, 1},

    {NULL, "ModuleWin", "WINGETTITLE", &F_WinGetTitle, 1, 1},

    {NULL, "ModuleWin", "WINKILL", &F_WinKill, 1, 1},

    {NULL, "ModuleWin", "WINLIST", &F_WinList, 1, 1},

    {NULL, "ModuleWin", "WINMENUSELECTITEM", &F_WinMenuSelectItem, 1, 1},

    {NULL, "ModuleWin", "WINMINIMIZEALL", &F_WinMinimizeAll, 1, 1},

    {NULL, "ModuleWin", "WINMINIMIZEALLUNDO", &F_WinMinimizeAllUndo, 1, 1},

    {NULL, "ModuleWin", "WINMOVE", &F_WinMove, 1, 1},

    {NULL, "ModuleWin", "WINSETONTOP", &F_WinSetOnTop, 1, 1},

    {NULL, "ModuleWin", "WINSETTITLE", &F_WinSetTitle, 1, 1},

    {NULL, "ModuleWin", "WINSETTRANS", &F_WinSetTrans, 1, 1},

    {NULL, "ModuleWin", "WINSHOW", &F_WinShow, 1, 1},

    {NULL, "ModuleWin", "WINWAIT", &F_WinWait, 1, 1},

    {NULL, "ModuleWin", "WINWAITACTIVE", &F_WinWaitActive, 1, 1},

    {NULL, "ModuleWin", "WINWAITCLOSE", &F_WinWaitClose, 1, 1},

    {NULL, "ModuleWin", "WINWAITNOTACTIVE", &F_WinWaitNotActive, 1, 1},

};
        
