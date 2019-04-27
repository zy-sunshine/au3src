#include "StdAfx.h"                                // Pre-compiled headers
#include "StrUtil.h"
#include <string.h>

StrUtil g_oStrUtil = StrUtil();

int StrUtil::CmpSort(const char* a, const char* b) {
    return strcmp(a, b);
}

int StrUtil::CmpSortReverse(const char* a, const char* b) {
    return strcmp(b, a);
}

static int DistinctChars(const char *a)
{
    int dist = 0;
   
    while (*a != '\0') {
        if (!strchr(a + 1, *a))
            dist++;
        a++;
    }
    return dist;
}

int StrUtil::SortByNumberOfDistinctCharacters(const char* a, const char* b) {
    int res = DistinctChars(a) - DistinctChars(b);
    return (res) ? res : CmpSort(a, b);
}

int StrUtil::SortByLength(const char* a, const char* b) {
    int res = strlen(a) - strlen(b);
    return (res) ? res : CmpSort(a, b);
}

///////////////////////////////////////////////////////////////////////////////
// StrUtil::StripCR()
//
// Strips all \r from some text
//
///////////////////////////////////////////////////////////////////////////////

void StrUtil::StripCR(char *szText)
{
    unsigned int    i = 0, j = 0;

    while (szText[i] != '\0')
    {
        if (szText[i] == '\r')
            ++i;
        else
            szText[j++] = szText[i++];
    }

    szText[j] = '\0';                            // Terminate

} // StrUtil::StripCR


///////////////////////////////////////////////////////////////////////////////
// StrUtil::AddCR()
//
// Adds a preceeding \r to all \n characters.  Call StrUtil::AddCRCount to find
// out how many characters will be added so that you can allocate a correct
// sized buffer for the result
//
///////////////////////////////////////////////////////////////////////////////

void StrUtil::AddCR(const char *szInput, char *szOutput)
{
    unsigned int    i = 0, j = 0;

    while (szInput[i] != '\0')
    {
        if (szInput[i] == '\n')
        {
            szOutput[j++] = '\r';
            szOutput[j++] = szInput[i++];
        }
        else
            szOutput[j++] = szInput[i++];
    }

    szOutput[j] = '\0';                            // Terminate

} // StrUtil::AddCR


///////////////////////////////////////////////////////////////////////////////
// StrUtil::AddCRSize()
//
// Finds out how long the buffer will need to be to store the result of a
// StrUtil::AddCR operation.  Includes the /0 character
//
///////////////////////////////////////////////////////////////////////////////

unsigned int StrUtil::AddCRSize(const char *szText)
{
    unsigned int    i = 0, j = 0;

    while (szText[i] != '\0')
    {
        if (szText[i++] == '\n')
            j++;
    }

    return (i+1) + j;

} // StrUtil::AddCRSize

///////////////////////////////////////////////////////////////////////////////
// StrUtil::AddTextToBuffer()
//
// Adds the specified text to the end of a buffer
///////////////////////////////////////////////////////////////////////////////

void StrUtil::AddTextToBuffer(const char *szText, char *szBuffer, unsigned int iBufSize)
{
    unsigned int nText    = 0;
    unsigned int nBuf    = (unsigned int)strlen(szBuffer);

    while ( (nBuf < iBufSize) && (szText[nText] != '\0') )
        szBuffer[nBuf++] = szText[nText++];

    szBuffer[nBuf] = '\0';                        // terminate the string

} // StrUtil::AddText()

///////////////////////////////////////////////////////////////////////////////
// StrUtil::GetInt()
///////////////////////////////////////////////////////////////////////////////

bool StrUtil::GetInt(const char *szInt, int &pos, int &nValue)
{
    int nSign = 1;
    bool retval = false;

    nValue=0;
    switch (szInt[pos])
    {
    case '-':
        nSign = -1;
    case '+':
        ++pos;
    }
    for (; szInt[pos] != '\0'; ++pos)
    {
        if (isdigit(szInt[pos]))
        {
            nValue *= 10;
            nValue += szInt[pos] - '0';
            retval = true;
        }
        else
            break;
    }
    nValue *= nSign;
    return retval;
}


///////////////////////////////////////////////////////////////////////////////
// StrUtil::DecToHex()
///////////////////////////////////////////////////////////////////////////////

bool StrUtil::DecToHex(const UINT uVal, char *szBuffer, const int iDigits)
{

    char    szHexData[17] = "0123456789ABCDEF";
    int        k;
    UINT    n = uVal;

    for (int i=iDigits-1; i>=0; i--)
    {
        k = n % 16;
        szBuffer[i]= szHexData[k];
        n = n / 16;
    }

    szBuffer[iDigits] = '\0';

    if (n)
        return false;                            // Left overs!
    else
        return true;

} // StrUtil::DecToHex()


///////////////////////////////////////////////////////////////////////////////
// StrUtil::HexToDec()
///////////////////////////////////////////////////////////////////////////////

bool StrUtil::HexToDec(const char *szHex, int &nDec)
{
    // Really crappy hex conversion
    int i = (int)strlen(szHex) - 1;

    nDec = 0;
    int nMult = 1;
    for (int j = 0; j < 8; ++j)
    {
        if (i < 0)
            break;

        if (szHex[i] >= '0' && szHex[i] <= '9')
            nDec += (szHex[i] - '0') * nMult;
        else if (szHex[i] >= 'A' && szHex[i] <= 'F')
            nDec += (((szHex[i] - 'A'))+10) * nMult;
        else if (szHex[i] >= 'a' && szHex[i] <= 'f')
            nDec += (((szHex[i] - 'a'))+10) * nMult;
        else
        {
            nDec = 0;                    // Set value as 0
            return false;
        }

        --i;
        nMult = nMult * 16;
    }

    if (i != -1)
    {
        nDec = 0;
        return false;
    }
    else
        return true;

} // StrUtil::HexToDec()

///////////////////////////////////////////////////////////////////////////////
// StrUtil::Strncpy()
//
// Copies a given number of characters of a string to a buffer and unlike
// strncpy ensures it is terminated.  The buffer size given should be the
// length of the string PLUS a SINGLE null char - i.e. your entire buffer size.
///////////////////////////////////////////////////////////////////////////////

void StrUtil::Strncpy(char *szBuffer, const char *szString, int nBufSize)
{
    strncpy(szBuffer, szString, nBufSize-1);    // Copy buf-1 characters
    szBuffer[nBufSize-1] = '\0';

} // StrUtil::Strncpy()


///////////////////////////////////////////////////////////////////////////////
// StrUtil::StrCpyAlloc()
//
// Copies a string but allocates (new) the memory first - caller must call
// delete [] on the area when no longer required
//
///////////////////////////////////////////////////////////////////////////////

char * StrUtil::StrCpyAlloc(const char *szSource)
{
    char *szNew = new char [strlen(szSource)+1];
    strcpy(szNew, szSource);

    return szNew;

} // StrUtil::StrCpyAlloc()

///////////////////////////////////////////////////////////////////////////////
// StrUtil::IsSpace
//
// Returns 1 if a char is 0x09 - 0x0D or 0x20.  The C runtime isspace() is unreliable
// on non UK/US characters sets and no windows version exists.
//
///////////////////////////////////////////////////////////////////////////////

int StrUtil::IsSpace(int c)
{
    if ( (c >= 0x09 && c <= 0x0D) || (c == 0x20) )
        return 1;
    else
        return 0;

} // StrUtil::IsSpace()


///////////////////////////////////////////////////////////////////////////////
// StrUtil::ANSItoUNICODE()
//
// Converts an ANSI string into UNICODE - the memory for the UNICODE string is
// automatically allocated - caller must call
// delete [] on the area when no longer required.
//
// nMinLen is the minimum number of wide characters (including /0) to allocate
// for the return buffer.  Default is 0.
//
///////////////////////////////////////////////////////////////////////////////

wchar_t * StrUtil::ANSItoUNICODE(const char *szANSI, int nMinLen)
{
    wchar_t *szUNI;

    // First find out how many wide chars we need
    int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szANSI, -1, NULL, 0);

    if (nLen == 0)
        return NULL;                            // Unable to convert (unlikely)

    // Allocate our buffer (must be at least nMinLen chars)
    if (nMinLen > nLen)
        szUNI = new wchar_t[nMinLen];
    else
        szUNI = new wchar_t[nLen];

    // Do the conversion proper
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szANSI, -1, szUNI, nLen);

    return szUNI;

} // StrUtil::ANSItoUNICODE()


///////////////////////////////////////////////////////////////////////////////
// StrUtil::UNICODEtoANSI()
//
// Converts a UNICODE string into ANSI - the memory for the ANSI string is
// automatically allocated - caller must call
// delete [] on the area when no longer required.
//
// nMinLen is the minimum number of characters (including /0) to allocate
// for the return buffer.  Default is 0.
//
///////////////////////////////////////////////////////////////////////////////

char * StrUtil::UNICODEtoANSI(const wchar_t *szUNI, int nMinLen)
{
    char *szANSI;

    // First find out how many wide chars we need
    int nLen = WideCharToMultiByte(CP_ACP, 0, szUNI, -1, NULL, 0, NULL, NULL);

    if (nLen == 0)
        return NULL;                            // Unable to convert (unlikely)

    // Allocate our buffer (must be at least nMinLen chars)
    if (nMinLen > nLen)
        szANSI = new char[nMinLen];
    else
        szANSI = new char[nLen];

    // Do the conversion proper
    WideCharToMultiByte(CP_ACP, 0, szUNI, -1, szANSI, nLen, NULL, NULL);

    return szANSI;

} // StrUtil::UNICODEtoANSI()
