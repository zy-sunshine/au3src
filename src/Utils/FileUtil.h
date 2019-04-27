#pragma once
#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
#endif

class FileUtil {
public:
    void    StripTrailingDir(char *szPath);
    bool    DoesFileExist(const char *szFilename);
    bool    IsDir(const char *szPath);
    void    GetFullPathName(const char *szIn, char *szOut);
    bool    GetLongFileName(const char *szIn, char *szOut);
    bool    IsDifferentVolumes(const char *szPath1, const char *szPath2);
    bool    DeleteFile(const char *szFilename);
    bool    FileSetTime(const char *szFilename, FILETIME *ft, int nWhichTime);
    bool    CopyFile(const char *szInputSource, const char *szInputDest, bool bOverwrite, bool bMove);
    void    ExpandFilenameWildcard(const char *szSource, const char *szDest, char *szExpandedDest);
    void    ExpandFilenameWildcardPart(const char *szSource, const char *szDest, char *szExpanded);
    bool    CreateDir(const char *szDirName);
    bool    RemoveDir (const char *szInputSource, bool bRecurse);
    bool    CopyDir (const char *szInputSource, const char *szInputDest, bool bOverwrite);
    bool    MoveDir (const char *szInputSource, const char *szInputDest, bool bOverwrite);

    char *  fgetsb(char *szBuffer, int nBufSize, FILE *fptr);
};

extern FileUtil g_oFileUtil;
