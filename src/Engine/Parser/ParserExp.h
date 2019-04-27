#pragma once
#include "AutoIt.h"
#include "Engine/Type/Variant.h"
#include "VectorToken.h"
#include "StackInt.h"
#include "StackVariant.h"

class Parser;
class Engine;
class ParserExp {
public:
    ParserExp(Parser* parser, Engine* engine)
        :_parser(parser), engine(engine) {}
    // Parsing expression/conditions (script_parse_exp.cpp)
    void        ExpandEnvString(Variant &vString);
    void        ExpandVarString(Variant &vString);
    AUT_RESULT  EvaluateVariable(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  EvaluateMacro(const char *szName, Variant &vResult);
    AUT_RESULT  EvaluateCondition(VectorToken &vLineToks, uint &ivPos, bool &bResult);
    AUT_RESULT  EvaluateExpression(VectorToken &vLineToks, uint &ivPos, Variant &vResult);
    AUT_RESULT  OprReduce(StackInt &opStack, StackVariant &valStack);
    AUT_RESULT  SkipBoolean(VectorToken &vLineToks, unsigned int &ivPos);
    AUT_RESULT  GetArrayElement(VectorToken &vLineToks, uint &ivPos, Variant **ppvTemp);

private:
    Parser *_parser;
    Engine *engine;

    static char        m_PrecOpRules[OPR_MAXOPR][OPR_MAXOPR];    // Table for precedence rules
    static const char  *m_szMacros[];                // Valid functions
};
