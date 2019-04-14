
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
// script_misc.cpp
//
// Contains routines that don't belong anywhere else.  Part of script.cpp
//
///////////////////////////////////////////////////////////////////////////////


// Includes
#include "StdAfx.h"                                // Pre-compiled headers

#ifndef _MSC_VER                                // Includes for non-MS compilers
    #include <stdio.h>
    #include <windows.h>
    #include <math.h>
    #include <limits.h>
    #include <olectl.h>
    #include <commctrl.h>
    #include <ctype.h>
    #include <wininet.h>
    #include <process.h>
#endif

// MinGW is missing some internet headers from wininet.h so declare them here
#ifndef INTERNET_STATE_CONNECTED
    typedef struct {
        DWORD dwConnectedState;
        DWORD dwFlags;
    } INTERNET_CONNECTED_INFO, * LPINTERNET_CONNECTED_INFO;

    #define INTERNET_STATE_CONNECTED                0x00000001  // connected state (mutually exclusive with disconnected)
    #define INTERNET_STATE_DISCONNECTED             0x00000002  // disconnected from network
    #define INTERNET_STATE_DISCONNECTED_BY_USER     0x00000010  // disconnected by user request
    #define INTERNET_STATE_IDLE                     0x00000100  // no network requests being made (by Wininet)
    #define INTERNET_STATE_BUSY                     0x00000200  // network requests being made (by Wininet)

    #define INTERNET_OPTION_CONNECTED_STATE         50
#endif


#include "AutoIt.h"                                // Autoit values, macros and config options

#include "globaldata.h"
#include "utility.h"
#include "mt19937ar-cok.h"
#include "inputbox.h"
