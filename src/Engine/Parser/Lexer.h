#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

// Lexer caching
// Assuming an average of 7 tokens per line at 256 bytes per line
// 256 lines of buffer = 64KB.
#define AUT_LEXER_CACHESIZE    256                    // Must be power of 2
#define AUT_LEXER_CACHEMASK    255                    // size - 1
typedef struct
{
    int            nLineNum;                        // Line cached here (or -1)
    VectorToken    vLine;                            // Cached line of tokens
} LexerCache;

class Engine;
class Lexer {
public:
    Lexer(Engine* engine);
    // Lexer functions (script_lexer.cpp)
    AUT_RESULT    doLexer(int nLineNum, const char *szLine, VectorToken &vLineToks);    // Convert a string into tokens
    AUT_RESULT    Lexer_String(const char *szLine, uint &iPos, char *szTemp);
    bool        Lexer_Number(const char *szLine, uint &iPos, Token &rtok, char *szTemp);
    void        Lexer_KeywordOrFunc(const char *szLine, uint &iPos, Token &rtok, char *szTemp);

private:
    Engine *engine;

    // Lexing and parsing vars
#ifdef AUT_CONFIG_LEXERCACHE
    LexerCache         m_LexerCache[AUT_LEXER_CACHESIZE];
#endif
    static char        m_PrecOpRules[OPR_MAXOPR][OPR_MAXOPR];    // Table for precedence rules
    static const char  *m_szKeywords[];            // Valid keywords
    static const char  *m_szMacros[];                // Valid functions
};
