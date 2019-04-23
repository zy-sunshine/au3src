#pragma once

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
// application.h
//
// This is the main application object, where all the windows are created,
// Timer Procs, etc.
//
///////////////////////////////////////////////////////////////////////////////

#include "Engine/Engine.h"
#include "Engine/CmdLine.h"

class ModuleBuiltIn;
class ModuleFile;
class ModuleGui;
class ModuleKeyboard;
class ModuleMath;
class ModuleMouse;
class ModuleNet;
class ModuleReg;
class ModuleSound;
class ModuleSys;
class ModuleWin;

class Application
{
public:
    // Functions
    Application::Application();                    // Constructor
    Application::~Application();                    // Denstructor
    void        CreateTrayIcon(void);
    void        DestroyTrayIcon(void);
    void        Run(void);

    // Variables
    HICON        m_hIcon;
    HICON        m_hIconSmall;
    HICON        m_hIconPause;

private:
    // Variables

    bool        m_bSingleCmdMode;                // TRUE=/c cmdline mode
    AString        m_sSingleLine;                    // Single line for the /c cmdline
    char        m_szScriptFileName[_MAX_PATH+1];// FileName (fullpath) of current script
    char        *m_szScriptFilePart;            // Just the filename (no path)
    bool        m_bShowingPauseIcon;            // State of the flashing paused icon


    // Functions

    // Main window handler messages and processing
    static LRESULT CALLBACK WndProc (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
    LRESULT        WndProcHandler (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

    void        HandleTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
    bool        HandleCommand (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

    void        RegisterClass(void);
    void        WindowCreate(void);
    void        ParseCmdLine(void);

    // Tray icon
    void        SetTrayIconToolTip(void);
    void        NotifyIcon (HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

    void registerModules();
    void unregisterModules();

public:
    Engine      *engine;

    ModuleBuiltIn   *_builtIn;
    ModuleFile      *_file;
    ModuleGui       *_gui;
    ModuleKeyboard  *_keyboard;
    ModuleMath      *_math;
    ModuleMouse     *_mouse;
    ModuleNet       *_net;
    ModuleReg       *_reg;
    ModuleSound     *_sound;
    ModuleSys       *_sys;
    ModuleWin       *_win;

public:
    CmdLine                 g_oCmdLine;             // CmdLine object
};

///////////////////////////////////////////////////////////////////////////////
