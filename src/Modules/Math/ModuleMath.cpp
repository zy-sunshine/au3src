///////////////////////////////////////////////////////////////////////////////
//
// AutoIt v3
//
// Copyright (C)1999-2005:
//        - Jonathan Bennett <jon at hiddensoft dot com>
//        - See "AUTHORS.txt" for contributors.
//
// This file is part of AutoIt.
//
// AutoIt source code is copyrighted software distributed under the terms of the
// AutoIt source code license.
//
// You may:
//
// - Customize the design and operation of the AutoIt source code to suit
// the internal needs of your organization except to the extent not
// permitted in this Agreement
//
// You may not:
//
// - Distribute the AutoIt source code and/or compiled versions of AutoIt
// created with the AutoIt source code.
// - Create derivative works based on the AutoIt source code for distribution
// or usage outside your organisation.
// - Modify and/or remove any copyright notices or labels included in the
// AutoIt source code.
//
// AutoIt is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// See the LICENSE.txt file that accompanies the AutoIt source
// code for more details.
//
///////////////////////////////////////////////////////////////////////////////
//
// script_math.cpp
//
// Contains math/conversion routines.  Part of script.cpp
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleMath.h"

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <math.h>
    #include <limits.h>
#else
//    #include "qmath.h"                            // MinGW doesn't like our asm maths functions
#endif

#include "Utils/utility.h"

///////////////////////////////////////////////////////////////////////////////
// Exp()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Exp(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathExp(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = exp(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Exp()


///////////////////////////////////////////////////////////////////////////////
// Log()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Log(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathLog(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = log(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Log()


///////////////////////////////////////////////////////////////////////////////
// ATan()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_ATan(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathAtan(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = atan(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // ATab()


///////////////////////////////////////////////////////////////////////////////
// ACos()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_ACos(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathAcos(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = acos(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // ACos()


///////////////////////////////////////////////////////////////////////////////
// ASin()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_ASin(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathAsin(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = asin(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // ASin()


///////////////////////////////////////////////////////////////////////////////
// Tan()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Tan(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathTan(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = tan(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Tan()


///////////////////////////////////////////////////////////////////////////////
// Cos()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Cos(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathCos(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = cos(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Cos()


///////////////////////////////////////////////////////////////////////////////
// Sin()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Sin(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathSin(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = sin(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Sin()


///////////////////////////////////////////////////////////////////////////////
// Abs()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Abs(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathFabs(vParams[0].fValue());
//
//#else
//        // Non MS/Ming
//    vResult = fabs(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Abs()


///////////////////////////////////////////////////////////////////////////////
// Mod()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Mod(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathFmod(vParams[0].fValue(), vParams[1].fValue());
//#else
//        // Non MS/Ming
//    vResult = fmod(vParams[0].fValue(), vParams[1].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Mod()


///////////////////////////////////////////////////////////////////////////////
// Sqrt()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Sqrt(VectorVariant &vParams, Variant &vResult)
//{
//#ifdef _MSC_VER
//        // MS Compiler
//    vResult = qmathSqrt(vParams[0].fValue());
//#else
//        // Non MS/Ming
//    vResult = sqrt(vParams[0].fValue());
//#endif
//
//    return AUT_OK;
//
//} // Sqrt()


///////////////////////////////////////////////////////////////////////////////
// Round()
///////////////////////////////////////////////////////////////////////////////

//AUT_RESULT ModuleMath::F_Round(VectorVariant &vParams, Variant &vResult)
//{
//    int        nTemp1;
//    double    fTemp1;
//
//#ifdef _MSC_VER
//        // MS Compiler
//    if (vParams.size() == 1)
//        nTemp1 = 0;
//    else
//        nTemp1 = vParams[1].nValue();
//
//    fTemp1 = qmathPow(10.0, nTemp1);
//    if (vParams[0].fValue() >= 0.0)
//        vResult = qmathFloor(vParams[0].fValue()*fTemp1+0.5)/fTemp1;
//    else
//        vResult = qmathCeil(vParams[0].fValue()*fTemp1-0.5)/fTemp1;
//
//#else
//        // Non MS/Ming
//    if (vParams.size() == 1)
//        nTemp1 = 0;
//    else
//        nTemp1 = vParams[1].nValue();
//
//    fTemp1 = pow(10.0, nTemp1);
//    if (vParams[0].fValue() >= 0.0)
//        vResult = floor(vParams[0].fValue()*fTemp1+0.5)/fTemp1;
//    else
//        vResult = ceil(vParams[0].fValue()*fTemp1-0.5)/fTemp1;
//
//#endif
//
//    return AUT_OK;
//
//} // Round()


///////////////////////////////////////////////////////////////////////////////
// Hex()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleMath::F_Hex(VectorVariant &vParams, Variant &vResult)
{
    char szTemp1[1024+1];

    if (vParams[1].nValue() > 8)
    {
        vResult = "";
        engine->SetFuncErrorCode(1);
        return AUT_OK;
    }
    if (Util_ConvHex(vParams[0].nValue(), szTemp1, vParams[1].nValue()) == false)
        engine->SetFuncErrorCode(1);            // left overs / not enough digits
    vResult = szTemp1;

    return AUT_OK;

} // Hex()

