#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleBuiltIn.h"

///////////////////////////////////////////////////////////////////////////////
// Call()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Call(VectorVariant &vParams, Variant &vResult)
{
    int nTemp1, nTemp2, nTemp3, nTemp4;

    // Check that this user function exists
    if (engine->parser->FindUserFunction(vParams[0].szValue(), nTemp1, nTemp2, nTemp3, nTemp4) == false)
    {
        engine->SetFuncErrorCode(1);                // Silent error even though function not valid
        return AUT_OK;                        // As will probably be used this way
    }
    else
    {
        m_vUserRetVal = 1;                    // Default return value is 1
        SaveExecute(nTemp1+1, true, false);    // Run the user function (line after the Func declaration)
        vResult = m_vUserRetVal;            // Get return value (0 = timed out)
        return AUT_OK;
    }

} // Call()


///////////////////////////////////////////////////////////////////////////////
// Eval()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Eval(VectorVariant &vParams, Variant &vResult)
{
    bool    bConst = false;

     if (g_oVarTable.isDeclared(vParams[0].szValue()))
     {
         Variant *pvTemp;
         g_oVarTable.GetRef(vParams[0].szValue(), &pvTemp, bConst);
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
    Variant *pvTemp;
    int     nReqScope = VARTABLE_ANY;
    bool    bCreate = true;
    bool    bConst = false;

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
    g_oVarTable.GetRef(vParams[0].szValue(), &pvTemp, bConst, nReqScope);
    if (pvTemp == NULL)
    {
        if (bCreate)
            g_oVarTable.Assign(vParams[0].szValue(), vParams[1], false, nReqScope);
        else
            vResult = 0;                        // Default is 1
    }
    else
        *pvTemp = vParams[1];

    return AUT_OK;

}    // F_Assign()


///////////////////////////////////////////////////////////////////////////////
// IsDeclared
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsDeclared(VectorVariant &vParams, Variant &vResult)
{
     vResult = g_oVarTable.isDeclared(vParams[0].szValue());
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
