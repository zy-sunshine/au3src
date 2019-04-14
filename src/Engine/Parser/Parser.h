#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"
#include "Engine/Parser/ParserExp.h"

class Parser {
public:
    Parser() { parserExp = new ParserExp(); }
    // Parser functions (script_parser.cpp)
    AUT_RESULT  VerifyBlockStructure(void);
    AUT_RESULT  VerifyBlockStructure2(int nDo, int nWhile, int nFor, int nSelect, int nIf);
    void        Parse(VectorToken &vLineToks, int &nScriptLine);
    void        StartWithVariable(VectorToken &vLineToks, uint &ivPos);
    AUT_RESULT  GetArrayElement(VectorToken &vLineToks, uint &ivPos, Variant **ppvTemp);
    void        StartWithKeyword(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    AUT_RESULT  FunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  GetFunctionCallParams(VectorVariant &vParams, VectorToken &vLineToks, uint &ivPos, int &nNumParams);
    AUT_RESULT  FunctionExecute(int nFunction, VectorVariant &vParams, Variant &vResult);
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

private:
    ParserExp* parserExp;
};
