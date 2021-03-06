#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleFile: public BaseModule {
public:
    ModuleFile(Engine* engine);
    ~ModuleFile();

public:
    // File related functions (script_file.cpp)
    AUT_RESULT    F_DirCopy(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IniRead(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IniWrite(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IniDelete(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IniReadSectionNames(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_IniReadSection(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileOpen(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileClose(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileReadLine(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetTime(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetSize(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileOpenDialog(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileSaveDialog(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileWriteLine(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileWrite(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileSelectFolder(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveMapAdd(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveMapDel(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveMapGet(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveSpaceTotal(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveSpaceFree(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileCreateShortcut(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetShortcut(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveStatus(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileExists(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileFindFirstFile(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileFindNextFile(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DirCreate(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DirRemove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_CDTray(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveGetDrive(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileCopy(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileDelete(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileInstall(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileRecycle(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveGetLabel(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveGetSerial(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveGetFileSystem(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveSetLabel(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DriveGetType(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileMove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetAttrib(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetVersion(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetLongName(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileGetShortName(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileChangeDir(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileSetAttrib(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileSetTime(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DirMove(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileRead(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FileRecycleEmpty(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_DirGetSize(VectorVariant &vParams, Variant &vResult);

private:
    AUT_RESULT    FileDialog(VectorVariant &vParams, Variant &vResult, uint iNumParams, int nFlag);
    AUT_RESULT    FileWriteLine(VectorVariant &vParams, Variant &vResult, bool bWriteLine);
    static int    CALLBACK BrowseForFolderProc(HWND hWnd,UINT iMsg,LPARAM lParam,LPARAM lpData);
    bool        FileSetAttrib_recurse (const char *szFile, DWORD dwAdd, DWORD dwRemove, bool bRecurse);
    bool        FileSetTime_recurse (const char *szIn, FILETIME *ft, int nWhichTime, bool bRecurse);
    bool        GetDirSize(const char *szInputPath, __int64 &nSize, __int64 &nFiles, __int64 &nDirs, bool bExt, bool bRec);

private:
    Engine* engine;

    // File variables
    int                    m_nNumFileHandles;                        // Number of file handles in use
    FileHandleDetails    *m_FileHandleDetails[AUT_MAXOPENFILES];    // Array contains file handles for File functions
};
