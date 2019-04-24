#pragma once
#include "AutoIt.h"
#include "VectorToken.h"

class Engine;
class ParserExp;
class Parser {
public:
    Parser(Engine *engine);
    // Parser functions (script_parser.cpp)
    AUT_RESULT  VerifyBlockStructure(void);
    AUT_RESULT  VerifyBlockStructure2(int nDo, int nWhile, int nFor, int nSelect, int nIf);
    void        Parse(VectorToken &vLineToks, int &nScriptLine);
    void        StartWithVariable(VectorToken &vLineToks, uint &ivPos);
    AUT_RESULT  GetArrayElement(VectorToken &vLineToks, uint &ivPos, Variant **ppvTemp);
    void        StartWithKeyword(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    AUT_RESULT  FunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  GetFunctionCallParams(VectorVariant &vParams, VectorToken &vLineToks, uint &ivPos, int &nNumParams);
    bool        FindUserFunction(const char *szName, int &nLineNum, int &nNumParams,int &nNumParamsMin, int &nEndLineNum);
    AUT_RESULT  UserFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    bool        PluginFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    void        Keyword_IF(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_ELSE(int &nScriptLine);
    void        Keyword_ENDIF(VectorToken &vLineToks, uint &ivPos);
    void        Keyword_WHILE(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Keyword_WEND(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_EXITLOOP(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_CONTINUELOOP(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_DO(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Keyword_UNTIL(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Keyword_FOR(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Keyword_NEXT(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_SELECT(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Keyword_CASE(int &nScriptLine);
    void        Keyword_ENDSELECT(VectorToken &vLineToks, uint &ivPos);
    void        Keyword_DIM(VectorToken &vLineToks, uint &ivPos, int nReqScope);
    void        Keyword_CONST(VectorToken &vLineToks, uint &ivPos, int nReqScope);
    void        Keyword_RETURN(VectorToken &vLineToks, uint &ivPos);
    void        Keyword_EXIT(VectorToken &vLineToks, uint &ivPos);

    AUT_RESULT    StoreUserFuncs(void);                                // Get all user function details
    AUT_RESULT    StoreUserFuncs2(VectorToken &LineTokens, uint &ivPos, const AString &sFuncName, int &nScriptLine);
    AUT_RESULT    StoreUserFuncsFindEnd(int &nScriptLine);            // Finds a matching endfunc during the StoreUserFuncs functions
    AUT_RESULT    VerifyUserFuncCalls(void);                            // Ensures user function calls are defined

    AUT_RESULT    StorePluginFuncs(void);                                // Get all plugin function details

    uint getStatementStackSize();
    void restoreStackmentStackSize(uint size);

private:
    Engine *engine;
    ParserExp* parserExp;

    UserFuncList    m_oUserFuncList;            // Details (line numbers, num params) for user defined functions
    // Statement stacks
    StackStatement    m_StatementStack;            // Stack for tracking If/Func/Select/Loop statements
};
