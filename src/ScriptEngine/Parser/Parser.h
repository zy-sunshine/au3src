class Parser {
public:
    // Parser functions (script_parser.cpp)
    AUT_RESULT    Parser_VerifyBlockStructure(void);
    AUT_RESULT    Parser_VerifyBlockStructure2(int nDo, int nWhile, int nFor, int nSelect, int nIf);
    void        Parser(VectorToken &vLineToks, int &nScriptLine);
    void        Parser_StartWithVariable(VectorToken &vLineToks, uint &ivPos);
    AUT_RESULT    Parser_GetArrayElement(VectorToken &vLineToks, uint &ivPos, Variant **ppvTemp);
    void        Parser_StartWithKeyword(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    AUT_RESULT    Parser_FunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT    Parser_GetFunctionCallParams(VectorVariant &vParams, VectorToken &vLineToks, uint &ivPos, int &nNumParams);
    AUT_RESULT    FunctionExecute(int nFunction, VectorVariant &vParams, Variant &vResult);
    bool        Parser_FindUserFunction(const char *szName, int &nLineNum, int &nNumParams,int &nNumParamsMin, int &nEndLineNum);
    AUT_RESULT    Parser_UserFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    bool        Parser_PluginFunctionCall(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    void        Parser_Keyword_IF(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_ELSE(int &nScriptLine);
    void        Parser_Keyword_ENDIF(VectorToken &vLineToks, uint &ivPos);
    void        Parser_Keyword_WHILE(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_WEND(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_EXITLOOP(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_CONTINUELOOP(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_DO(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_UNTIL(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_FOR(VectorToken &vLineToks,uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_NEXT(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_SELECT(VectorToken &vLineToks, uint &ivPos, int &nScriptLine);
    void        Parser_Keyword_CASE(int &nScriptLine);
    void        Parser_Keyword_ENDSELECT(VectorToken &vLineToks, uint &ivPos);
    void        Parser_Keyword_DIM(VectorToken &vLineToks, uint &ivPos, int nReqScope);
    void        Parser_Keyword_CONST(VectorToken &vLineToks, uint &ivPos, int nReqScope);
    void        Parser_Keyword_RETURN(VectorToken &vLineToks, uint &ivPos);
    void        Parser_Keyword_EXIT(VectorToken &vLineToks, uint &ivPos);
};
