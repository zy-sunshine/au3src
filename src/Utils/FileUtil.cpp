#include "StdAfx.h"                                // Pre-compiled headers
#include "FileUtil.h"
#include "StrUtil.h"
#include "OSVersion.h"

FileUtil g_oFileUtil = FileUtil();

///////////////////////////////////////////////////////////////////////////////
// FileUtil::StripTrailingDir()
//
// Makes sure a filename does not have a trailing //
//
///////////////////////////////////////////////////////////////////////////////

void FileUtil::StripTrailingDir(char *szPath)
{
    int len = (int)strlen(szPath)-1;

    if (szPath[len] == '\\')
        szPath[len] = '\0';

} // FileUtil::StripTrailingDir


///////////////////////////////////////////////////////////////////////////////
// FileUtil::FileSetTime()
// Sets the time of a file given a FILETIME struct
// 0 = modified, 1=created, 2=accessed
//
// Note, will only set directory times when used under NT based OSes
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::FileSetTime(const char *szFilename, FILETIME *ft, int nWhichTime)
{
    HANDLE    hFile;

    // If this is a directory and we are NOT running NT then just return
    if (FileUtil::IsDir(szFilename) && g_oVersion.IsWin9x() )
        return true;

    if ( (hFile = CreateFile(szFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS, NULL)) == INVALID_HANDLE_VALUE )
        return false;

    if (nWhichTime == 0)
        SetFileTime(hFile, NULL, NULL, ft);    // Modified
    else if (nWhichTime == 1)
        SetFileTime(hFile, ft, NULL, NULL);    // Created
    else
        SetFileTime(hFile, NULL, ft, NULL);    // Accessed

    CloseHandle(hFile);

    return true;

} // FileUtil::FileSetTime()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::DoesFileExist()
// Returns true if file or directory exists
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::DoesFileExist(const char *szFilename)
{
    if ( strchr(szFilename,'*')||strchr(szFilename,'?') )
    {
        WIN32_FIND_DATA    wfd;

        HANDLE hFile = FindFirstFile(szFilename, &wfd);

        if ( hFile == INVALID_HANDLE_VALUE )
            return false;

        FindClose(hFile);
        return true;
    }
    else
    {
        if ( GetFileAttributes(szFilename) != 0xffffffff )
            return true;
        else
            return false;
    }

} // FileUtil::DoesFileExist


///////////////////////////////////////////////////////////////////////////////
// FileUtil::IsDir()
// Returns true if the path is a directory
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::IsDir(const char *szPath)
{
    DWORD dwTemp = GetFileAttributes(szPath);
    if ( dwTemp != 0xffffffff && (dwTemp & FILE_ATTRIBUTE_DIRECTORY) )
        return true;
    else
        return false;

} // FileUtil::IsDir


///////////////////////////////////////////////////////////////////////////////
// FileUtil::GetFullPathName()
// Returns the full pathname and strips any trailing \s.  Assumes output
// is _MAX_PATH in size.  Input and output CAN be the same buffer
///////////////////////////////////////////////////////////////////////////////

void FileUtil::GetFullPathName(const char *szIn, char *szOut)
{
    char    *szFilePart;

    ::GetFullPathName(szIn, _MAX_PATH, szOut, &szFilePart);
    StripTrailingDir(szOut);

} // FileUtil::GetFullPathName()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::GetLongFileName()
// Returns the long filename.  Assumes output
// is _MAX_PATH in size
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::GetLongFileName(const char *szIn, char *szOut)
{
    IMalloc*        iMalloc;
    BOOL            ret = FALSE;
    IShellFolder*    iShellFolder;
    WCHAR            buffer[MAX_PATH];
    ULONG            eaten;
    ITEMIDLIST*        itemIDList;
    char            filePath[MAX_PATH];

    if(SHGetMalloc(&iMalloc) != NOERROR)
    {
        strcpy(szOut, szIn);
        return false;
    }

    // convert file path to display name
    if(SHGetDesktopFolder(&iShellFolder) == NOERROR)
    {
        MultiByteToWideChar(CP_ACP, 0, szIn, -1, buffer, MAX_PATH);
        if(iShellFolder->ParseDisplayName(NULL, NULL, buffer, &eaten, &itemIDList, NULL) == S_OK)
        {
            if(    (ret=SHGetPathFromIDList(itemIDList, filePath)) )
                strcpy(szOut, filePath);
            iMalloc->Free(itemIDList);
        }
        iShellFolder->Release();
    }
    iMalloc->Release();

    if (!ret)
    {
        strcpy(szOut, szIn);                    // Error, dupicate input
        return false;
    }
    else
        return true;

} // FileUtil::GetLongFileName()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::IsDifferentVolumes()
// Checks two paths to see if they are on the same volume
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::IsDifferentVolumes(const char *szPath1, const char *szPath2)
{
    char            szP1Drive[_MAX_DRIVE+1];
    char            szP2Drive[_MAX_DRIVE+1];

    char            szP1Dir[_MAX_DIR+1];
    char            szP2Dir[_MAX_DIR+1];

    char            szFile[_MAX_FNAME+1];
    char            szExt[_MAX_EXT+1];

    char            szP1[_MAX_PATH+1];
    char            szP2[_MAX_PATH+1];

    // Get full pathnames
    FileUtil::GetFullPathName(szPath1, szP1);
    FileUtil::GetFullPathName(szPath2, szP2);

    // Split the target into bits
    _splitpath( szP1, szP1Drive, szP1Dir, szFile, szExt );
//    FileUtil::WinPrintf("", "%s - %s - %s - %s", szP1Drive, szP1Dir, szFile, szExt);
    _splitpath( szP2, szP2Drive, szP2Dir, szFile, szExt );
//    FileUtil::WinPrintf("", "%s - %s - %s - %s", szP2Drive, szP2Dir, szFile, szExt);

    if (szP1Drive[0] == '\0' && szP2Drive[0] == '\0' )
    {
        // Both paths are UNC, if both directories are also the same then we assume
        // they are on the same volume (same UNC but different directories may be redirected
        // so I don't think we can assume they are the same volume in that case.
        if ( !stricmp(szP1Dir, szP2Dir) )
            return false;
        else
            return true;
    }
    else
    {
        if ( !stricmp(szP1Drive, szP2Drive) )
            return false;
        else
            return true;
    }

} // FileUtil::IsDifferentVolumes()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::DeleteFile()
// Returns true if a file was deleted.  Note: returns false if file didn't
// exist OR if file did exist and could not be deleted!
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::DeleteFile(const char *szFilename)
{
    WIN32_FIND_DATA    findData;
    bool            bFound = false;                // Not found initially
    char            szDrive[_MAX_PATH+1];
    char            szDir[_MAX_PATH+1];
    char            szFile[_MAX_PATH+1];
    char            szExt[_MAX_PATH+1];
    char            szTempPath[_MAX_PATH+1];

    // Get full path and remove trailing \s
    FileUtil::GetFullPathName(szFilename, szTempPath);

    // If the source is a directory then add *.* to the end
    if (FileUtil::IsDir(szTempPath))
        strcat(szTempPath, "\\*.*");

    // Split the target into bits (used for reconstruction later)
    _splitpath( szTempPath, szDrive, szDir, szFile, szExt );

    // Delete all files matching the criteria
    HANDLE hSearch = FindFirstFile(szTempPath, &findData);
    bool bLoop = true;
    while (hSearch != INVALID_HANDLE_VALUE && bLoop == true)
    {
        // Make sure the returned handle is a file and not a directory before we
        // try and do delete type things on it!
        if ( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
        {
            bFound = true;                            // Found at least one match

            // Returned data is just the filename, we need to add the path stuff back on
            // The find strcut only returns the file NAME, we need to reconstruct the path!
            strcpy(szTempPath, szDrive);
            strcat(szTempPath, szDir);
            strcat(szTempPath, findData.cFileName);

            if ( DeleteFile(szTempPath) != TRUE )
            {
                FindClose(hSearch);
                return false;                        // Error deleting one of the files
            }

        } // End if

        if (FindNextFile(hSearch, &findData) == FALSE)
            bLoop = false;
    }

    FindClose(hSearch);

    return bFound;

} // FileUtil::DeleteFile()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::CopyFile()
// Returns true if all files copied, else returns false
// Also used to move files too
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::CopyFile(const char *szInputSource, const char *szInputDest, bool bOverwrite, bool bMove)
{
    WIN32_FIND_DATA    findData;
    bool            bFound = false;                // Not found initially
    BOOL            bRes;

    char            szSource[_MAX_PATH+1];
    char            szDest[_MAX_PATH+1];
    char            szExpandedDest[MAX_PATH+1];
    char            szTempPath[_MAX_PATH+1];

    char            szDrive[_MAX_PATH+1];
    char            szDir[_MAX_PATH+1];
    char            szFile[_MAX_PATH+1];
    char            szExt[_MAX_PATH+1];

    // Get local version of our source/dest with full path names, strip trailing \s
    FileUtil::GetFullPathName(szInputSource, szSource);
    FileUtil::GetFullPathName(szInputDest, szDest);

    // Check if the files are on different volumes (affects how we do a Move operation)
    bool bDiffVol = FileUtil::IsDifferentVolumes(szSource, szDest);

    // If the source or dest is a directory then add *.* to the end
    if (FileUtil::IsDir(szSource))
        strcat(szSource, "\\*.*");
    if (FileUtil::IsDir(szDest))
        strcat(szDest, "\\*.*");


    // Split source into file and extension (we need this info in the loop below to recontstruct the path)
    _splitpath( szSource, szDrive, szDir, szFile, szExt );

    // Note we now rely on the SOURCE being the contents of szDrive, szDir, szFile, etc.

    // Does the source file exist?
    HANDLE hSearch = FindFirstFile(szSource, &findData);
    bool bLoop = true;
    while (hSearch != INVALID_HANDLE_VALUE && bLoop == true)
    {
        bFound = true;                            // Found at least one match

        // Make sure the returned handle is a file and not a directory before we
        // try and do copy type things on it!
        if ( (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
        {
            // Expand the destination based on this found file
            FileUtil::ExpandFilenameWildcard(findData.cFileName, szDest, szExpandedDest);

            // The find struct only returns the file NAME, we need to reconstruct the path!
            strcpy(szTempPath, szDrive);
            strcat(szTempPath, szDir);
            strcat(szTempPath, findData.cFileName);

            // Does the destination exist? - delete it first if it does (unless we not overwriting)
            if ( FileUtil::DoesFileExist(szExpandedDest) )
            {
                if (bOverwrite == false)
                {
                    FindClose(hSearch);
                    return false;                    // Destination already exists and we not overwriting
                }
                else
                    DeleteFile(szExpandedDest);
            }

            // Move or copy operation?
            if (bMove == true)
            {
                if (bDiffVol == false)
                {
                    bRes = MoveFile(szTempPath, szExpandedDest);
                }
                else
                {
                    // Do a copy then delete (simulated copy)
                    if ( (bRes = ::CopyFile(szTempPath, szExpandedDest, FALSE)) != FALSE )
                        bRes = DeleteFile(szTempPath);
                }
            }
            else
                bRes = ::CopyFile(szTempPath, szExpandedDest, FALSE);

            if (bRes == FALSE)
            {
                FindClose(hSearch);
                return false;                        // Error copying/moving one of the files
            }

        } // End If

        if (FindNextFile(hSearch, &findData) == FALSE)
            bLoop = false;

    } // End while

    FindClose(hSearch);

    return bFound;

} // FileUtil::CopyFile()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::ExpandFilenameWildcard()
///////////////////////////////////////////////////////////////////////////////

void FileUtil::ExpandFilenameWildcard(const char *szSource, const char *szDest, char *szExpandedDest)
{
    // copy one.two.three  *.txt     = one.two   .txt
    // copy one.two.three  *.*.txt   = one.two   .three  .txt
    // copy one.two.three  *.*.*.txt = one.two   .three  ..txt
    // copy one.two           test      = test

    char    szFileTemp[_MAX_PATH+1];
    char    szExtTemp[_MAX_PATH+1];

    char    szSrcFile[_MAX_PATH+1];
    char    szSrcExt[_MAX_PATH+1];

    char    szDestDrive[_MAX_PATH+1];
    char    szDestDir[_MAX_PATH+1];
    char    szDestFile[_MAX_PATH+1];
    char    szDestExt[_MAX_PATH+1];

    // If the destination doesn't include a wildcard, send it back vertabim
    if (strchr(szDest, '*') == NULL)
    {
        strcpy(szExpandedDest, szDest);
        return;
    }

    // Split source and dest into file and extension
    _splitpath( szSource, szDestDrive, szDestDir, szSrcFile, szSrcExt );
    _splitpath( szDest, szDestDrive, szDestDir, szDestFile, szDestExt );

    // Source and Dest ext will either be ".nnnn" or "" or ".*", remove the period
    if (szSrcExt[0] == '.')
        strcpy(szSrcExt, &szSrcExt[1]);
    if (szDestExt[0] == '.')
        strcpy(szDestExt, &szDestExt[1]);

    // Start of the destination with the drive and dir
    strcpy(szExpandedDest, szDestDrive);
    strcat(szExpandedDest, szDestDir);

    // Replace first * in the destext with the srcext, remove any other *
    FileUtil::ExpandFilenameWildcardPart(szSrcExt, szDestExt, szExtTemp);

    // Replace first * in the destfile with the srcfile, remove any other *
    FileUtil::ExpandFilenameWildcardPart(szSrcFile, szDestFile, szFileTemp);

    // Concat the filename and extension if req
    if (szExtTemp[0] != '\0')
    {
        strcat(szFileTemp, ".");
        strcat(szFileTemp, szExtTemp);
    }
    else
    {
        // Dest extension was blank SOURCE MIGHT NOT HAVE BEEN!
        if (szSrcExt[0] != '\0')
        {
            strcat(szFileTemp, ".");
            strcat(szFileTemp, szSrcExt);
        }
    }

    // Now add the drive and directory bit back onto the dest
    strcat(szExpandedDest, szFileTemp);

} // FileUtil::CopyFile


///////////////////////////////////////////////////////////////////////////////
// FileUtil::ExpandFilenameWildcardPart()
///////////////////////////////////////////////////////////////////////////////

void FileUtil::ExpandFilenameWildcardPart(const char *szSource, const char *szDest, char *szExpandedDest)
{
    int        i = 0, j = 0, k = 0;

    // Replace first * in the dest with the src, remove any other *
    // TODO: check char* force convert
    char *lpTemp = strchr((char*)szDest, '*');
    if (lpTemp != NULL)
    {
        // Contains at least one *, copy up to this point
        while(szDest[i] != '*')
            szExpandedDest[j++] = szDest[i++];
        // Skip the * and replace in the dest with the srcext
        while(szSource[k] != '\0')
            szExpandedDest[j++] = szSource[k++];
        // Skip any other *
        i++;
        while(szDest[i] != '\0')
        {
            if (szDest[i] == '*')
                i++;
            else
                szExpandedDest[j++] = szDest[i++];
        }
        szExpandedDest[j] = '\0';
    }
    else
    {
        // No wildcard, straight copy of destext
        strcpy(szExpandedDest, szDest);
    }

} // FileUtil::ExpandFilenameWildcardPart()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::CreateDir()
// Recursive directory creation function
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::CreateDir(const char *szDirName)
{
    bool    bRes;

    DWORD dwTemp = GetFileAttributes(szDirName);
    if (dwTemp == FILE_ATTRIBUTE_DIRECTORY)
        return true;                            // Directory exists, yay!

    if (dwTemp == 0xffffffff)
    {    // error getting attribute - what was the error?
        if (GetLastError() == ERROR_PATH_NOT_FOUND)
        {
            // Create path
            char *szTemp = g_oStrUtil.StrCpyAlloc(szDirName);

            char *psz_Loc = strrchr(szTemp, '\\');    /* find last \ */
            if (psz_Loc == NULL)                // not found
            {
                delete [] szTemp;
                return false;
            }
            else
            {
                *psz_Loc = '\0';                // remove \ and everything after
                bRes = FileUtil::CreateDir(szTemp);
                delete [] szTemp;
                if (bRes)
                {
                    if (CreateDirectory(szDirName, NULL))
                        bRes = true;
                    else
                        bRes = false;
                }

                return bRes;
            }
        }
        else
        {
            if (GetLastError() == ERROR_FILE_NOT_FOUND)
            {
                // Create directory
                if (CreateDirectory(szDirName, NULL))
                    return true;
                else
                    return false;
            }
        }
    }

    return false;                                // Unforeseen error

} // FileUtil::CreateDir()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::CopyDir()
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::CopyDir (const char *szInputSource, const char *szInputDest, bool bOverwrite)
{
    SHFILEOPSTRUCT    FileOp;
    char            szSource[_MAX_PATH+2];
    char            szDest[_MAX_PATH+2];

    // Get the fullpathnames and strip trailing \s
    FileUtil::GetFullPathName(szInputSource, szSource);
    FileUtil::GetFullPathName(szInputDest, szDest);

    // Ensure source is a directory
    if (FileUtil::IsDir(szSource) == false)
        return false;                            // Nope

    // Does the destination dir exist?
    if (FileUtil::IsDir(szDest))
    {
        if (bOverwrite == false)
            return false;
    }
    else
    {
        // We must create the top level directory
        if (!FileUtil::CreateDir(szDest))
            return false;
    }

    // To work under old versions AND new version of shell32.dll the source must be specifed
    // as "dir\*.*" and the destination directory must already exist... Godamn Microsoft and their APIs...
    strcat(szSource, "\\*.*");

    // We must also make source\dest double nulled strings for the SHFileOp API
    szSource[strlen(szSource)+1] = '\0';
    szDest[strlen(szDest)+1] = '\0';

    // Setup the struct
    FileOp.pFrom                    = szSource;
    FileOp.pTo                        = szDest;
    FileOp.hNameMappings            = NULL;
    FileOp.lpszProgressTitle        = NULL;
    FileOp.fAnyOperationsAborted    = FALSE;
    FileOp.hwnd                        = NULL;

    FileOp.wFunc    = FO_COPY;
    FileOp.fFlags    = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI;

    if ( SHFileOperation(&FileOp) )
        return false;

    return true;

} // FileUtil::CopyDir()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::MoveDir()
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::MoveDir (const char *szInputSource, const char *szInputDest, bool bOverwrite)
{
    SHFILEOPSTRUCT    FileOp;
    char            szSource[_MAX_PATH+2];
    char            szDest[_MAX_PATH+2];

    // Get the fullpathnames and strip trailing \s
    FileUtil::GetFullPathName(szInputSource, szSource);
    FileUtil::GetFullPathName(szInputDest, szDest);

    // Ensure source is a directory
    if (FileUtil::IsDir(szSource) == false)
        return false;                            // Nope

    // Does the destination dir exist?
    if (FileUtil::IsDir(szDest))
    {
        if (bOverwrite == false)
            return false;
    }

    // Now, if the source and dest are on different volumes then we must copy rather than move
    // as move in this case only works on some OSes
    if (FileUtil::IsDifferentVolumes(szSource, szDest))
    {
        // Copy and delete (poor man's move)
        if (FileUtil::CopyDir(szSource, szDest, true) == false)
            return false;
        if (FileUtil::RemoveDir(szSource, true) == false)
            return false;
        else
            return true;
    }

    // We must also make source\dest double nulled strings for the SHFileOp API
    szSource[strlen(szSource)+1] = '\0';
    szDest[strlen(szDest)+1] = '\0';

    // Setup the struct
    FileOp.pFrom                    = szSource;
    FileOp.pTo                        = szDest;
    FileOp.hNameMappings            = NULL;
    FileOp.lpszProgressTitle        = NULL;
    FileOp.fAnyOperationsAborted    = FALSE;
    FileOp.hwnd                        = NULL;

    FileOp.wFunc    = FO_MOVE;
    FileOp.fFlags    = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI;

    if ( SHFileOperation(&FileOp) )
        return false;
    else
        return true;

} // FileUtil::MoveDir()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::RemoveDir()
///////////////////////////////////////////////////////////////////////////////

bool FileUtil::RemoveDir (const char *szInputSource, bool bRecurse)
{
    SHFILEOPSTRUCT    FileOp;
    char            szSource[_MAX_PATH+2];

    // Get the fullpathnames and strip trailing \s
    FileUtil::GetFullPathName(szInputSource, szSource);

    // Ensure source is a directory
    if (FileUtil::IsDir(szSource) == false)
        return false;                            // Nope

    // If recursion not on just try a standard delete on the directory (the SHFile function WILL
    // delete a directory even if not empty no matter what flags you give it...)
    if (bRecurse == false)
    {
        if (!RemoveDirectory(szSource))
            return false;
        else
            return true;
    }

    // We must also make double nulled strings for the SHFileOp API
    szSource[strlen(szSource)+1] = '\0';

    // Setup the struct
    FileOp.pFrom                    = szSource;
    FileOp.pTo                        = NULL;
    FileOp.hNameMappings            = NULL;
    FileOp.lpszProgressTitle        = NULL;
    FileOp.fAnyOperationsAborted    = FALSE;
    FileOp.hwnd                        = NULL;

    FileOp.wFunc    = FO_DELETE;
    FileOp.fFlags    = FOF_SILENT | FOF_NOCONFIRMMKDIR | FOF_NOCONFIRMATION | FOF_NOERRORUI;

    if ( SHFileOperation(&FileOp) )
        return false;

    return true;

} // FileUtil::RemoveDir()


///////////////////////////////////////////////////////////////////////////////
// FileUtil::fgets()
//
// Reads is line fo text for files in BINARY mode, cr, crlf and lf are the end
// of line terminators.  BufSize is the size of the buffer INCLUDING the \0
// Data returned is always terminated.
///////////////////////////////////////////////////////////////////////////////

char * FileUtil::fgetsb(char *szBuffer, int nBufSize, FILE *fptr)
{
    int        nMaxPos;
    int        nPos = 0;
    int        ch;

    // If we are already at end of file then return NULL - note feof only returns eof AFTER
    // a read operation has already bounced off the end so make sure we start with a read
    ch = fgetc(fptr);
    if ( ch == EOF )
        return NULL;

    // Work out where the last valid position is and make sure last char in the buffer
    // is terminated
    nMaxPos = nBufSize - 2;

    while (nPos <= nMaxPos)
    {
        if (ch == EOF)
            break;                                // Exit loop on end of file

        if (ch == '\r')                            // is the next char cr?
        {
            // Is the next char lf?
            ch = fgetc(fptr);                    // Get next char
            if (ch == EOF)
                break;                            // Exit loop on end of file
            if (ch != '\n')
                fseek(fptr, -1, SEEK_CUR);        // Oops, not a lf, rewind for next time
            break;
        }
        else if (ch == '\n')                    // is the next char lf?
            break;                                // break, don't store lf
        else
            szBuffer[nPos++] = ch;

        ch = fgetc(fptr);                        // Get next char
    }

    // Terminate
    szBuffer[nPos] = '\0';

    return szBuffer;

} // FileUtil::fgetsb()
