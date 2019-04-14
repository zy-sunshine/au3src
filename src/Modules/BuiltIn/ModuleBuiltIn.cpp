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
#include "ModuleBuiltIn.h"

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
// Asc()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Asc(VectorVariant &vParams, Variant &vResult)
{
    vResult = int(uchar(vParams[0].szValue()[0]));
    return AUT_OK;

} // Asc()


///////////////////////////////////////////////////////////////////////////////
// Chr()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Chr(VectorVariant &vParams, Variant &vResult)
{
    char szTemp[2];

    szTemp[0]    =  (char)vParams[0].nValue();
    szTemp[1]    = '\0';
    vResult        = szTemp;                // Return a string variant of this character code

    return AUT_OK;

} // Chr()


///////////////////////////////////////////////////////////////////////////////
// Dec()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Dec(VectorVariant &vParams, Variant &vResult)
{
    int        nTemp1;

    if (Util_ConvDec(vParams[0].szValue(), nTemp1) == false)
        engine->SetFuncErrorCode(1);            // error
    vResult = nTemp1;

    return AUT_OK;

} // Dec()


///////////////////////////////////////////////////////////////////////////////
// VarType()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_VarType(VectorVariant &vParams, Variant &vResult)
{
    vResult = vParams[0].type();

    return AUT_OK;

} // VarType()


///////////////////////////////////////////////////////////////////////////////
// Int()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Int(VectorVariant &vParams, Variant &vResult)
{
    // If the variant is already int32 or int64 then leave alone
    // If the variant is a DOUBLE then convert to an int64
    if (vParams[0].type() == VAR_INT32 || vParams[0].type() == VAR_INT64)
    {
        vResult = vParams[0];
    }
    else if (vParams[0].type() == VAR_DOUBLE || vParams[0].type() == VAR_STRING)
    {
        vResult = vParams[0].n64Value();
    }
    else
    {
        engine->SetFuncErrorCode(1);
        vResult = 0;                            // Invalid
    }

    return AUT_OK;

} // Int()


///////////////////////////////////////////////////////////////////////////////
// IsArray()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsArray(VectorVariant &vParams, Variant &vResult)
{
    vResult = vParams[0].isArray();
    return AUT_OK;

} // IsArray()


///////////////////////////////////////////////////////////////////////////////
// IsString()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsString(VectorVariant &vParams, Variant &vResult)
{
    vResult = vParams[0].isString();
    return AUT_OK;

} // IsString()


///////////////////////////////////////////////////////////////////////////////
// IsInt()
//
// Is the base type numerical AND contains no fractional part
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsInt(VectorVariant &vParams, Variant &vResult)
{
    vResult = 0;

    if (vParams[0].isNumber())
    {
        if (vParams[0].type() == VAR_INT32 || vParams[0].type() == VAR_INT64)
            vResult = 1;
        else
        {                                        // Must be DOUBLE, check for fractions
            __int64 nTemp;

            // Convert to an __int64 and back to a double and compare
            nTemp = (__int64)vParams[0].fValue();
            if ( (double)nTemp == vParams[0].fValue() )
                vResult = 1;
        }
    }

    return AUT_OK;

} // IsInt()


///////////////////////////////////////////////////////////////////////////////
// IsFloat()
//
// Is the base type numerical AND contains a fractional part
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsFloat(VectorVariant &vParams, Variant &vResult)
{
    vResult = 0;

    if (vParams[0].isNumber())
    {
        if (vParams[0].type() == VAR_DOUBLE)
        {                                        // check for fractions
            __int64 nTemp;

            // Convert to an __int64 and back to a double and compare
            nTemp = (__int64)vParams[0].fValue();
            if ( (double)nTemp != vParams[0].fValue() )
                vResult = 1;
        }
    }

    return AUT_OK;

} // IsFloat()


///////////////////////////////////////////////////////////////////////////////
// IsNumber()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_IsNumber(VectorVariant &vParams, Variant &vResult)
{
    vResult = vParams[0].isNumber();
    return AUT_OK;

} // IsNumber()


///////////////////////////////////////////////////////////////////////////////
// Number()
//
// Change to a numerical type - only really valid for strings
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Number(VectorVariant &vParams, Variant &vResult)
{
    if (vParams[0].isNumber())
        vResult = vParams[0];                    // Already numerical
    else
    {
        const char *szTemp = vParams[0].szValue();

        if (strstr(szTemp, "."))                // Contains a decimal point?
            vResult  = atof(szTemp);            // Convert to double
        else
        {
            __int64 n64Temp = _atoi64(szTemp);
            if (n64Temp > INT_MAX || n64Temp < INT_MIN)
                vResult  = n64Temp;                // Store as int64
            else
                vResult  = atoi(szTemp);        // Store as int32
        }
    }

    return AUT_OK;

} // Number()


///////////////////////////////////////////////////////////////////////////////
// String()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_String(VectorVariant &vParams, Variant &vResult)
{
    vResult =  vParams[0].szValue();

    return AUT_OK;

} // Number()


///////////////////////////////////////////////////////////////////////////////
// BitAND()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_BitAND(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nRes = vParams[0].nValue();

    for (uint i = 1; i < iNumParams; ++i)
        nRes &= vParams[i].nValue();

    vResult = nRes;

    return AUT_OK;

} // BitAND()


///////////////////////////////////////////////////////////////////////////////
// BitOR()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_BitOR(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nRes = vParams[0].nValue();

    for (uint i = 1; i < iNumParams; ++i)
        nRes |= vParams[i].nValue();

    vResult = nRes;

    return AUT_OK;

} // BitOR()


///////////////////////////////////////////////////////////////////////////////
// BitNOT()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_BitNOT(VectorVariant &vParams, Variant &vResult)
{
    vResult = ~vParams[0].nValue();
    return AUT_OK;

} // BitNOT()


///////////////////////////////////////////////////////////////////////////////
// BitXOR()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_BitXOR(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nRes = vParams[0].nValue();

    for (uint i = 1; i < iNumParams; ++i)
        nRes ^= vParams[i].nValue();

    vResult = nRes;

    return AUT_OK;

} // BitXOR()


///////////////////////////////////////////////////////////////////////////////
// BitShift()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_BitShift(VectorVariant &vParams, Variant &vResult)
{
    if (vParams[1].nValue() >= 0)
        vResult = vParams[0].nValue() >> vParams[1].nValue();
    else
        vResult = vParams[0].nValue() << (vParams[1].nValue() * -1);
    return AUT_OK;

} // BitShift()



///////////////////////////////////////////////////////////////////////////////
// Random()
// $var = Random( [Min [, Max [, flag]]] )
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Random(VectorVariant &vParams, Variant &vResult)
{
    double    fTemp1;
    int        nTemp1;
    bool    bInteger = false;                    // Defaults to floats for backwards compatibility
    uint    iNumParams = vParams.size();

    // Integer flag?
    if (iNumParams == 3 && vParams[2].nValue() == 1)
        bInteger = true;

    // Default result is 0
    vResult = 0;

    switch(vParams.size())
    {
        case 0:    // return [0, 1]
            vResult = genrand_real2();
            break;

        case 1: // return [0, n]
            fTemp1 = vParams[0].fValue();
            if (fTemp1 <= 0.0)
                engine->SetFuncErrorCode(1);
            else
                vResult = genrand_real2() * fTemp1;    // return [0,1] * fTemp1
            break;

        case 2:    // return [n, m] for int and [n, m] for float
        case 3:
            if (vParams[0].isArray() || vParams[1].isArray())
                engine->SetFuncErrorCode(1);
            else if (bInteger)
            {
                // Integer (32 bit)
                int nTemp2 = vParams[1].nValue();

                nTemp1 = vParams[0].nValue();
                if (nTemp1 > nTemp2)
                    engine->SetFuncErrorCode(1);    // invalid range
                else
                    vResult = (int)(genrand_int31()%(nTemp2-nTemp1+1) + nTemp1);
            }
            else
            {
                // Float
                double fTemp2 = vParams[1].fValue();

                fTemp1 = vParams[0].fValue();
                if (fTemp1 >= fTemp2)
                    engine->SetFuncErrorCode(1);    // invalid range
                else
                    vResult = genrand_real2()*(fTemp2-fTemp1) + fTemp1;
            }
            break;
    }    // switch vParams.size()

    return AUT_OK;

} // Random()


/*
///////////////////////////////////////////////////////////////////////////////
// Random()
// $var = Random([[min] ,max]])
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleBuiltIn::F_Random(VectorVariant &vParams, Variant &vResult)
{
    double    fTemp1;

    switch(vParams.size())
    {
        case 0:    // return [0, 1)
            vResult = genrand_real2();
            break;

        case 1: // return [0, n]
            switch(vParams[0].type())
            {
                case VAR_DOUBLE:
                    fTemp1 = vParams[0].fValue();
                    if (fTemp1 <= 0.0)
                        engine->SetFuncErrorCode(2);
                    else
                        vResult=genrand_real2()*fTemp1;    // return [0,1)
                    break;
                default:
                    engine->SetFuncErrorCode(1);    // invalid argument type
            }
            break;

        case 2:    // return [n, m] for int and [n, m) for float
            if (vParams[0].isArray() || vParams[1].isArray())
                engine->SetFuncErrorCode(1);
            else
            {
                // Float
                double fTemp2=vParams[1].fValue();

                fTemp1=vParams[0].fValue();
                if (fTemp1>=fTemp2)
                    engine->SetFuncErrorCode(2);    // invalid range
                else
                    vResult = genrand_real2()*(fTemp2-fTemp1) + fTemp1;
            }
            break;
    }
    return AUT_OK;

} // Random()

*/

