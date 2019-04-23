#pragma once
#include "AutoIt.h"
#include "Engine/BaseModule.h"
#include "Engine/type/VectorVariant.h"

class Engine;
class ModuleNet: public BaseModule {
public:
    ModuleNet(Engine* engine);

    AUT_RESULT    F_HttpSetProxy(VectorVariant &vParams, Variant &vResult);
    AUT_RESULT    F_FtpSetProxy(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_InetGet(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_InetGetSize(VectorVariant &vParams, Variant &vResult);
//    AUT_RESULT    F_Ping(VectorVariant &vParams, Variant &vResult);

private:
//    bool        MySplitURL(const char *szUrlFull, DWORD &dwService, int &nPort, char *szHost, char *szUrl, char *szUser, char *szPwd);
//    bool        MyInternetOpen(DWORD dwService, HINTERNET &hInet);
//    static void __cdecl InetGetThreadHandler(void *vp);
//    void        InetGetThread(void);

private:
    Engine* engine;

    // Proxy Settings
    int             m_nHttpProxyMode;
    AString         m_sHttpProxy;
    AString         m_sHttpProxyUser;
    AString         m_sHttpProxyPwd;
    int             m_nFtpProxyMode;
    AString         m_sFtpProxy;
    AString         m_sFtpProxyUser;
    AString         m_sFtpProxyPwd;
};
