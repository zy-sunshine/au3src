#pragma once
#include "AutoIt.h"
#include "Engine/Engine.h"

class ModuleNet {
public:
    ModuleNet(Engine* engine): engine(engine) {}

    AUT_RESULT    F_HttpSetProxy(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FtpSetProxy(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_InetGet(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_InetGetSize(VectorVariant &vParams, Variant &vResult);
//    bool        MySplitURL(const char *szUrlFull, DWORD &dwService, int &nPort, char *szHost, char *szUrl, char *szUser, char *szPwd);
//    bool        MyInternetOpen(DWORD dwService, HINTERNET &hInet);
//    static void __cdecl InetGetThreadHandler(void *vp);
//    void        InetGetThread(void);
//    AUT_RESULT    F_Ping(VectorVariant &vParams, Variant &vResult);

private:
    Engine* engine;
};
