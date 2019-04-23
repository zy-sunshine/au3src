#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class Lexer {
public:
    // Lexer functions (script_lexer.cpp)
    AUT_RESULT    doLexer(int nLineNum, const char *szLine, VectorToken &vLineToks);    // Convert a string into tokens
    AUT_RESULT    Lexer_String(const char *szLine, uint &iPos, char *szTemp);
    bool        Lexer_Number(const char *szLine, uint &iPos, Token &rtok, char *szTemp);
    void        Lexer_KeywordOrFunc(const char *szLine, uint &iPos, Token &rtok, char *szTemp);
};
