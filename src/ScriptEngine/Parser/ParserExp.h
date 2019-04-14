
class ParserExp {
public:
    // Parsing expression/conditions (script_parse_exp.cpp)
    void        Parser_ExpandEnvString(Variant &vString);
    void        Parser_ExpandVarString(Variant &vString);
    AUT_RESULT    Parser_EvaluateVariable(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT    Parser_EvaluateMacro(const char *szName, Variant &vResult);
    AUT_RESULT    Parser_EvaluateCondition(VectorToken &vLineToks, uint &ivPos, bool &bResult);
    AUT_RESULT    Parser_EvaluateExpression(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT    Parser_OprReduce(StackInt &opStack, StackVariant &valStack);
    AUT_RESULT    Parser_SkipBoolean(VectorToken &vLineToks, unsigned int &ivPos);
};
