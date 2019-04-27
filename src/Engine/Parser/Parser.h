#pragma once
#include "AutoIt.h"
#include "VectorToken.h"
#include "Token.h"
#include "StackStatement.h"
#include "UserFuncList.h"
#include "VariableTable.h"

class Engine;
class ParserExp;
class Parser {
    friend class Engine;
    friend class ParserExp;
    friend class Lexer;
public:
    Parser(Engine *engine);
    // Parser functions (script_parser.cpp)
    AUT_RESULT  VerifyBlockStructure(void);
    AUT_RESULT  VerifyBlockStructure2(int nDo, int nWhile, int nFor, int nSelect, int nIf);
    void        Parse(VectorToken &vLineToks, int nScriptLineCurrent, int &nScriptLine);
    void        StartWithVariable(VectorToken &vLineToks, uint &ivPos);
    void        StartWithKeyword(VectorToken &vLineToks, uint &ivPos, int nScriptLineCurrent, int &nScriptLine);
    AUT_RESULT  FunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  GetFunctionCallParams(VectorVariant &vParams, VectorToken &vLineToks, uint &ivPos, int &nNumParams);
    bool        FindUserFunction(const char *szName, int &nLineNum, int &nNumParams,int &nNumParamsMin, int &nEndLineNum);
    AUT_RESULT  UserFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    bool        PluginFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    void        Keyword_IF(VectorToken &vLineToks, uint &ivPos, int nScriptLineCurrent, int &nScriptLine);
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

    void        SaveExecute(int nScriptLine, bool bRaiseScope, bool bRestoreErrorCode);        // Save state and then Execute()
    // Functions
    void        FatalError(int iErr, int nCol = -1);                // Output an error and signal quit (String resource errors)
    void        FatalError(int iErr, const char *szText2);          // Output an error and signal quit (passed text errors)

    void        SetFuncErrorCode(int nCode)
        {m_nFuncErrorCode = nCode;}                    // Set script error info (@error code)
    inline int nFuncErrorCode() { return m_nFuncErrorCode; }

    void        SetFuncExtCode(int nCode)
       {m_nFuncExtCode = nCode;};                        // Set script extended info (@extended code)

    AUT_RESULT  FunctionExecute(int nFunction, VectorVariant &vParams, Variant &vResult);
    AUT_RESULT  call(const char* szName, Variant &vResult);
    AUT_RESULT  interruptCall(const char* szName, Variant &vResult);

private:
    Lexer *lexer;
    Engine *engine;
    ParserExp* parserExp;

    // module register function list
    AU3_FuncInfo       *m_FuncList;                // List of functions and details for each
    int                m_nFuncListSize;            // Number of functions

    UserFuncList    m_oUserFuncList;            // Details (line numbers, num params) for user defined functions
    // Statement stacks
    StackStatement    m_StatementStack;         // Stack for tracking If/Func/Select/Loop statements

    // User functions variables
    bool            m_bUserFuncReturned;        // Becomes true when userfunctions end (return or endfunc)
    Variant         m_vUserRetVal;              // Temp storage for return value of a user function (or winwait result)
    int             m_nFuncErrorCode;           // Extended error code
    int             m_nFuncExtCode;             // Extended code
    int             m_nNumParams;               // Number of parameters when calling a user function

    int             m_nErrorLine;               // Line number used to generate error messages
    int             m_nCurrentOperation;        // The current state of the script (RUN, WAIT, SLEEP, etc)

    VariableTable   m_oVarTable;            // Object for accessing autoit variables
};
