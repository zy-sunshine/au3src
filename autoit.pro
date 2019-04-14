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

SOURCES = \
    src/astring_datatype.cpp \
    src/globaldata.cpp \
    src/guibox.cpp \
    src/inputbox.cpp \
    src/mt19937ar-cok.cpp \
    src/os_version.cpp \
    src/regexp.cpp \
    src/script.cpp \
    src/script_file.cpp \
    src/script_gui.cpp \
    src/script_math.cpp \
    src/script_misc.cpp \
    src/script_process.cpp \
    src/script_registry.cpp \
    src/script_string.cpp \
    src/script_win.cpp \
    src/scriptfile.cpp \
    src/sendkeys.cpp \
    src/setforegroundwinex.cpp \
    src/shared_memory.cpp \
    src/stack_int_datatype.cpp \
    src/stack_statement_datatype.cpp \
    src/stack_variable_list.cpp \
    src/stack_variant_datatype.cpp \
    src/token_datatype.cpp \
    src/userfunction_list.cpp \
    src/utility.cpp \
    src/variable_list.cpp \
    src/variabletable.cpp \
    src/variant_datatype.cpp \
    src/vector_token_datatype.cpp \
    src/vector_variant_datatype.cpp

# application.cpp
# AutoIt.cpp
# cmdline.cpp
# src/script_parser.cpp
# src/script_parser_exp.cpp
# src/script_lexer.cpp

HEADERS = \
    src/astring_datatype.h \
    src/globaldata.h \
    src/guibox.h \
    src/inputbox.h \
    src/mt19937ar-cok.h \
    src/os_version.h \
    src/regexp.h \
    src/script.h \
    src/scriptfile.h \
    src/sendkeys.h \
    src/setforegroundwinex.h \
    src/shared_memory.h \
    src/stack_int_datatype.h \
    src/stack_statement_datatype.h \
    src/stack_variable_list.h \
    src/stack_variant_datatype.h \
    src/StdAfx.h \
    src/token_datatype.h \
    src/userfunction_list.h \
    src/utility.h \
    src/variable_list.h \
    src/variabletable.h \
    src/variant_datatype.h \
    src/vector_token_datatype.h \
    src/vector_variant_datatype.h

# src/cmdline.h
# src/qmath.h
