#include "StdAfx.h"                                // Pre-compiled headers
#include "Engine/Engine.h"
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
    const char* szName = vParams[0].szValue();
    bool    bConst = false;

     if (engine->isDeclared(szName))
     {
         Variant *pvTemp;
         engine->GetRef(szName, &pvTemp, bConst);
         vResult = *pvTemp;
         return AUT_OK;
     }
     else
     {
         engine->SetFuncErrorCode(1);            // Silent error even though variable not valid
         vResult = "";
         return AUT_OK;
     }
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
    const char* szName = vParams[0].szValue();
    Variant &vValue = vParams[1];
    Variant *pvTemp;
    bool bConst;

    if (vParams.size() == 3)
    {
        if (vParams[2].nValue() & 1)
            nReqScope = VARTABLE_FORCELOCAL;
        if (vParams[2].nValue() & 2)
            nReqScope = VARTABLE_FORCEGLOBAL;
        if (vParams[2].nValue() & 4)
            bCreate = false;
    }

    // Get a reference to the variable in the requested scope, if it doesn't exist, then create it.
    engine->GetRef(szName, &pvTemp, bConst, nReqScope);
    if (pvTemp == NULL)
    {
        if (bCreate) {
            // TODO: bConst === true can not assign
            engine->Assign(szName, vValue, false, nReqScope);
        } else
            vResult = 0;                        // Default is 1
    }
    else
        *pvTemp = vValue;

    return AUT_OK;

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
