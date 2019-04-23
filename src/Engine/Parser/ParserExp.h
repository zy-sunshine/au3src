#pragma once
#include "AutoIt.h"

class Engine;
class ParserExp {
public:
    ParserExp(Engine *engine)
        :engine(engine) {}
    // Parsing expression/conditions (script_parse_exp.cpp)
    void        ExpandEnvString(Variant &vString);
    void        ExpandVarString(Variant &vString);
    AUT_RESULT  EvaluateVariable(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  EvaluateMacro(const char *szName, Variant &vResult);
    AUT_RESULT  EvaluateCondition(VectorToken &vLineToks, uint &ivPos, bool &bResult);
    AUT_RESULT  EvaluateExpression(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  OprReduce(StackInt &opStack, StackVariant &valStack);
    AUT_RESULT  SkipBoolean(VectorToken &vLineToks, unsigned int &ivPos);

private:
    Engine *engine;
};
