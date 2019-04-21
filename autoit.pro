TEMPLATE = lib
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

#SOURCES = \
#    src/astring_datatype.cpp \
#    src/globaldata.cpp \
#    src/guibox.cpp \
#    src/inputbox.cpp \
#    src/mt19937ar-cok.cpp \
#    src/os_version.cpp \
#    src/regexp.cpp \
#    src/script.cpp \
#    src/script_file.cpp \
#    src/script_gui.cpp \
#    src/script_math.cpp \
#    src/script_misc.cpp \
#    src/script_process.cpp \
#    src/script_registry.cpp \
#    src/script_string.cpp \
#    src/script_win.cpp \
#    src/scriptfile.cpp \
#    src/sendkeys.cpp \
#    src/setforegroundwinex.cpp \
#    src/shared_memory.cpp \
#    src/stack_int_datatype.cpp \
#    src/stack_statement_datatype.cpp \
#    src/stack_variable_list.cpp \
#    src/stack_variant_datatype.cpp \
#    src/token_datatype.cpp \
#    src/userfunction_list.cpp \
#    src/utility.cpp \
#    src/variable_list.cpp \
#    src/variabletable.cpp \
#    src/variant_datatype.cpp \
#    src/vector_token_datatype.cpp \
#    src/vector_variant_datatype.cpp

# application.cpp
# AutoIt.cpp
# cmdline.cpp
# src/script_parser.cpp
# src/script_parser_exp.cpp
# src/script_lexer.cpp

#HEADERS = \
#    src/astring_datatype.h \
#    src/globaldata.h \
#    src/guibox.h \
#    src/inputbox.h \
#    src/mt19937ar-cok.h \
#    src/os_version.h \
#    src/regexp.h \
#    src/script.h \
#    src/scriptfile.h \
#    src/sendkeys.h \
#    src/setforegroundwinex.h \
#    src/shared_memory.h \
#    src/stack_int_datatype.h \
#    src/stack_statement_datatype.h \
#    src/stack_variable_list.h \
#    src/stack_variant_datatype.h \
#    src/StdAfx.h \
#    src/token_datatype.h \
#    src/userfunction_list.h \
#    src/utility.h \
#    src/variable_list.h \
#    src/variabletable.h \
#    src/variant_datatype.h \
#    src/vector_token_datatype.h \
#    src/vector_variant_datatype.h

# src/cmdline.h
# src/qmath.h

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
    src/Engine/ScriptFile.h \
    src/Engine/StackStatement.h \
    src/Engine/StackVarList.h \
    src/Engine/UserFuncList.h \
    src/Engine/VariableList.h \
    src/Engine/VariableTable.h \
    src/StdAfx.h \
    src/Utils/mt19937ar-cok.h \
    src/Utils/OSVersion.h \
    src/Utils/SendKeys.h \
    src/Utils/SetForegroundWinEx.h \
    src/Utils/utility.h \
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
    src/Engine/ScriptFile.cpp \
    src/Engine/StackStatement.cpp \
    src/Engine/StackVarList.cpp \
    src/Engine/UserFuncList.cpp \
    src/Engine/VariableList.cpp \
    src/Engine/VariableTable.cpp \
    src/Utils/mt19937ar-cok.cpp \
    src/Utils/OSVersion.cpp \
    src/Utils/SendKeys.cpp \
    src/Utils/SetForegroundWinEx.cpp \
    src/Utils/utility.cpp \
    src/Utils/WinUtil.cpp

INCLUDEPATH += src
