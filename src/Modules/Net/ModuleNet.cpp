///////////////////////////////////////////////////////////////////////////////
// HttpSetProxy()
//
// HttpSetProxy( mode, ["proxy:port", "user", "password"] )
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_HttpSetProxy(VectorVariant &vParams, Variant &vResult)
{
    uint iNumParams = vParams.size();

    if (vParams[0].nValue() == 1)
        m_nHttpProxyMode = AUT_PROXY_DIRECT;
    else if (vParams[0].nValue() == 2)
        m_nHttpProxyMode = AUT_PROXY_PROXY;
    else
        m_nHttpProxyMode = AUT_PROXY_REGISTRY;

    if (iNumParams > 1)
        m_sHttpProxy = vParams[1].szValue();
    if (iNumParams > 2)
        m_sHttpProxyUser = vParams[2].szValue();
    if (iNumParams > 3)
        m_sHttpProxyPwd = vParams[3].szValue();

    return AUT_OK;

} // HttpSetProxy()


///////////////////////////////////////////////////////////////////////////////
// FtpSetProxy()
//
// FtpSetProxy( mode, ["proxy:port", "user", "password"] )
//
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_FtpSetProxy(VectorVariant &vParams, Variant &vResult)
{
    uint iNumParams = vParams.size();

    if (vParams[0].nValue() == 1)
        m_nFtpProxyMode = AUT_PROXY_DIRECT;
    else if (vParams[0].nValue() == 2)
        m_nFtpProxyMode = AUT_PROXY_PROXY;
    else
        m_nFtpProxyMode = AUT_PROXY_REGISTRY;

    if (iNumParams > 1)
        m_sFtpProxy = vParams[1].szValue();
    if (iNumParams > 2)
        m_sFtpProxyUser = vParams[2].szValue();
    if (iNumParams > 3)
        m_sFtpProxyPwd = vParams[3].szValue();

    return AUT_OK;

} // FtpSetProxy()


