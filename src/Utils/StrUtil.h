#pragma once
#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
#endif

class StrUtil {
public:
    bool    GetInt(const char *szInt, int &pos, int &nValue);
    bool    DecToHex(const UINT uVal, char *szBuffer, const int iDigits);
    bool    HexToDec(const char *szHex, int &nDec);
    
    void    Strncpy(char *szBuffer, const char *szString, int nBufSize);

    wchar_t * ANSItoUNICODE(const char *szANSI, int nMinLen = 0);
    char *    UNICODEtoANSI(const wchar_t *szUNI, int nMinLen = 0);

    void    StripCR(char *szText);
    void    AddCR(const char *szInput, char *szOutput);
    unsigned int AddCRSize(const char *szText);
    
    void    AddTextToBuffer(const char *szText, char *szBuffer, unsigned int iBufSize);

    int     IsSpace(int c);

    char *  StrCpyAlloc(const char *szSource);

    static int CmpSort(const char* a, const char* b);
    static int CmpSortReverse(const char* a, const char* b);
    static int SortByNumberOfDistinctCharacters(const char* a, const char* b);
    static int SortByLength(const char* a, const char* b);
    /* simple bubble sort :) */
    template <typename T>
    static void Sort(T* arr, int len, int (*cmp_func)(const T a, const T b))
    {
        char* temp;
        int i, j;
        for (i=0; i < len-1; i++) {
            for (j=0; j < len-1-i; j++) {
                if (cmp_func(arr[j], arr[j+1]) > 0) {
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
};

extern StrUtil g_oStrUtil;
