TEMPLATE = app
#CONFIG += warn_on
CONFIG -= qt
CONFIG += debug
DEFINES += _MBCS WIN32 _WINDOWS
DEFINES -= UNICODE

QMAKE_CXXFLAGS_RELEASE += -O2 -MD
QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO += -O2 -MD -Zi
QMAKE_CXXFLAGS_DEBUG += -Zi -MDd

LIBS += \
    wsock32.lib \
    version.lib \
    winmm.lib \
    comctl32.lib \
    mpr.lib \
    kernel32.lib \
    user32.lib \
    gdi32.lib \
    winspool.lib \
    comdlg32.lib \
    advapi32.lib \
    shell32.lib \
    ole32.lib \
    oleaut32.lib \
    uuid.lib \
    odbc32.lib \
    odbccp32.lib

HEADERS = \
    src/AutoIt.h \
    src/Modules/BuiltIn/ModuleBuiltIn.h \
    src/Modules/File/ModuleFile.h \
    src/Modules/Gui/ModuleGui.h \
    src/Modules/Keyboard/ModuleKeyboard.h \
    src/Modules/Math/ModuleMath.h \
    src/Modules/Mouse/ModuleMouse.h \
    src/Modules/Net/ModuleNet.h \
    src/Modules/Reg/ModuleReg.h \
    src/Modules/Sound/ModuleSound.h \
    src/Modules/Sys/ModuleSys.h \
    src/Modules/Win/InputBox.h \
    src/Modules/Win/ModuleWin.h \
    src/Modules/Win/WinSearchUtil.h \
    src/resources/AutoIt_VersionInfo.h \
    src/resources/resource.h \
    src/Engine/Application.h \
    src/Engine/CmdLine.h \
    src/Engine/Type/AString.h \
    src/Engine/Type/Variant.h \
    src/Engine/Type/VectorVariant.h \
    src/Engine/Engine.h \
    src/Engine/Parser/Lexer.h \
    src/Engine/Parser/Parser.h \
    src/Engine/Parser/ParserExp.h \
    src/Engine/Parser/StackInt.h \
    src/Engine/Parser/StackVariant.h \
    src/Engine/Parser/Token.h \
    src/Engine/Parser/VectorToken.h \
    src/Engine/Parser/StackStatement.h \
    src/Engine/Parser/StackVarList.h \
    src/Engine/Parser/UserFuncList.h \
    src/Engine/Parser/VariableList.h \
    src/Engine/Parser/VariableTable.h \
    src/Engine/ScriptFile.h \
    src/StdAfx.h \
    src/Utils/mt19937ar-cok.h \
    src/Utils/OSVersion.h \
    src/Utils/SendKeys.h \
    src/Utils/SetForegroundWinEx.h \
    src/Utils/FileUtil.h \
    src/Utils/StrUtil.h \
    src/Utils/SysUtil.h \
    src/Utils/WinUtil.h

SOURCES = \
    src/AutoIt.cpp \
    src/Modules/BuiltIn/BuiltInArray.cpp \
    src/Modules/BuiltIn/BuiltInMisc.cpp \
    src/Modules/BuiltIn/BuiltInString.cpp \
    src/Modules/BuiltIn/ModuleBuiltIn.cpp \
    src/Modules/File/ModuleFile.cpp \
    src/Modules/Gui/ModuleGui.cpp \
    src/Modules/Keyboard/ModuleKeyboard.cpp \
    src/Modules/Math/ModuleMath.cpp \
    src/Modules/Mouse/ModuleMouse.cpp \
    src/Modules/Net/ModuleNet.cpp \
    src/Modules/Reg/ModuleReg.cpp \
    src/Modules/Sound/ModuleSound.cpp \
    src/Modules/Sys/ModuleSys.cpp \
    src/Modules/Sys/SysMisc.cpp \
    src/Modules/Win/InputBox.cpp \
    src/Modules/Win/ModuleWin.cpp \
    src/Modules/Win/WinMisc.cpp \
    src/Modules/Win/WinSearchUtil.cpp \
    src/Engine/Application.cpp \
    src/Engine/CmdLine.cpp \
    src/Engine/Type/AString.cpp \
    src/Engine/Type/Variant.cpp \
    src/Engine/Type/VectorVariant.cpp \
    src/Engine/Engine.cpp \
    src/Engine/Parser/Lexer.cpp \
    src/Engine/Parser/Parser.cpp \
    src/Engine/Parser/ParserExp.cpp \
    src/Engine/Parser/StackInt.cpp \
    src/Engine/Parser/StackVariant.cpp \
    src/Engine/Parser/Token.cpp \
    src/Engine/Parser/VectorToken.cpp \
    src/Engine/Parser/StackStatement.cpp \
    src/Engine/Parser/StackVarList.cpp \
    src/Engine/Parser/UserFuncList.cpp \
    src/Engine/Parser/VariableList.cpp \
    src/Engine/Parser/VariableTable.cpp \
    src/Engine/ScriptFile.cpp \
    src/Utils/mt19937ar-cok.cpp \
    src/Utils/OSVersion.cpp \
    src/Utils/SendKeys.cpp \
    src/Utils/SetForegroundWinEx.cpp \
    src/Utils/FileUtil.cpp \
    src/Utils/StrUtil.cpp \
    src/Utils/SysUtil.cpp \
    src/Utils/WinUtil.cpp

INCLUDEPATH += src
