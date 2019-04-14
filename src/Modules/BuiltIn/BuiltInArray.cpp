#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleBuiltIn.h"

///////////////////////////////////////////////////////////////////////////////
// UBound()
// Return number of dimensions or the size of dimensions
// $var = UBound($array, $dim_num)
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_UBound(VectorVariant &vParams, Variant &vResult)
{
    // One of the few cases we need to check if it's an array...
    if (vParams[0].isArray() == false)
    {
        vResult=0;
        engine->SetFuncErrorCode(1);
    }
    else if (vParams.size() == 1)
    {
        vResult = vParams[0].ArrayGetBound(1);    // Get size of 1st dimension
    }
    else
    { // vParams.size() == 2
        vResult = vParams[0].ArrayGetBound(vParams[1].nValue());
        if (vResult.nValue() == 0) {
            engine->SetFuncErrorCode(2);
        }
    }
    return AUT_OK;

} // UBound()

