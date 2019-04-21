#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleBuiltIn.h"

///////////////////////////////////////////////////////////////////////////////
// Call()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Call(VectorVariant &vParams, Variant &vResult)
{
    return engine->call(vParams[0].szValue(), vResult);
} // Call()


///////////////////////////////////////////////////////////////////////////////
// Eval()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Eval(VectorVariant &vParams, Variant &vResult)
{
    return engine->eval(vParams[0].szValue(), vResult);
} // Eval()


//////////////////////////////////////////////////////////////////////////
// F_Assign("variable", "data")
//
// Assign( "varname", "value" [,flag])
//
// binary flag: 0=any, 1=local, 2=global, 4=no create
//
// Assigns the variable in the first parameter to the data in the second parameter.
// This is a compliment to Eval()
//////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Assign(VectorVariant &vParams, Variant &vResult)
{
    bool    bCreate = true;
    int     nReqScope = VARTABLE_ANY;
    if (vParams.size() == 3)
    {
        if (vParams[2].nValue() & 1)
            nReqScope = VARTABLE_FORCELOCAL;
        if (vParams[2].nValue() & 2)
            nReqScope = VARTABLE_FORCEGLOBAL;
        if (vParams[2].nValue() & 4)
            bCreate = false;
    }

    return engine->assign(vParams[0].szValue(), vParams[1], nReqScope, bCreate, vResult);
}    // F_Assign()


///////////////////////////////////////////////////////////////////////////////
// IsDeclared
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsDeclared(VectorVariant &vParams, Variant &vResult)
{
    vResult = engine->isDeclared(vParams[0].szValue());
    return AUT_OK;
} // IsDeclared()

//////////////////////////////////////////////////////////////////////////
// F_ConsoleWrite("text")
//
// Writes to the console so editors like SciTE can
// read the data
//////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_ConsoleWrite(VectorVariant &vParams, Variant &vResult)
{
    printf("%s", vParams[0].szValue());
    fflush(stdout);

    return AUT_OK;

}    // F_ConsoleWrite()
