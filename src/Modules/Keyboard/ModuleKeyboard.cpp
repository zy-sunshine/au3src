#include "ModuleKeyboard.h"
///////////////////////////////////////////////////////////////////////////////
// Send()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_Send(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() == 2)
    {
        if (vParams[1].nValue() == 0)
            m_oSendKeys.Send(vParams[0].szValue());        // Normal send
        else
            m_oSendKeys.SendRaw(vParams[0].szValue());    // Raw send
    }
    else
        m_oSendKeys.Send(vParams[0].szValue());    // Normal send

    return AUT_OK;

} // Send()

///////////////////////////////////////////////////////////////////////////////
// HotKeySet(key ([mod]key, function)
//
// Sets a hotkey
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_HotKeySet(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nTemp1, nTemp2, nTemp3, nTemp4;
    bool    bShift, bControl, bAlt, bWin;
    UINT    mods = 0;
    UINT    vk;
    int        nFreeHandle;
    LPARAM    lParam;


    // Unless blank, check that the requested user function exists
    if (iNumParams >= 2 && Parser_FindUserFunction(vParams[1].szValue(), nTemp1, nTemp2, nTemp3, nTemp4) == false)
    {
        FatalError(IDS_AUT_E_UNKNOWNUSERFUNC);
        return AUT_ERR;
    }


    // Get the virtual key code and modifiers
    if (m_oSendKeys.GetSingleVKandMods(vParams[0].szValue(), vk, bShift, bControl, bAlt, bWin) == false)
    {
        vResult = 0;                            // Error, default is 1
        return AUT_OK;
    }

    if (bShift)
        mods |= MOD_SHIFT;
    if (bControl)
        mods |= MOD_CONTROL;
    if (bAlt)
        mods |= MOD_ALT;
    if (bWin)
        mods |= MOD_WIN;


    // Create an WM_HOTKEY compatible lParam for the modifiers and the VK
    lParam = (vk << 16) | mods;

    // Is this a duplicate or an unset (Function is blank)
    for (nFreeHandle = 0; nFreeHandle < AUT_MAXHOTKEYS; ++nFreeHandle)
    {
        if (m_HotKeyDetails[nFreeHandle] != NULL)
        {
            if (m_HotKeyDetails[nFreeHandle]->lParam == lParam)
            {
                // Are we reusing or unregistering?
                if (iNumParams == 1)
                {
                    UnregisterHotKey(g_hWnd, (int)m_HotKeyDetails[nFreeHandle]->wParam);    // Unregister
                    delete m_HotKeyDetails[nFreeHandle];    // Delete memory
                    m_HotKeyDetails[nFreeHandle] = NULL;    // Mark as empty
                }
                else
                    m_HotKeyDetails[nFreeHandle]->sFunction = vParams[1].szValue();    // Reuse

                return AUT_OK;
            }
        }
    }

    // If we are here and numParams == 1 (want to unregister) then we failed to find our
    // key to unregister in the code above == error
    if (iNumParams == 1)
    {
        vResult = 0;
        return AUT_OK;
    }

    // Find a free handle
    for (nFreeHandle = 0; nFreeHandle < AUT_MAXHOTKEYS; ++nFreeHandle)
    {
        if (m_HotKeyDetails[nFreeHandle] == NULL)
        {
            m_HotKeyDetails[nFreeHandle] = new HotKeyDetails;    // Create new entry
            m_HotKeyDetails[nFreeHandle]->wParam = 0x0000 + nFreeHandle;
            m_HotKeyDetails[nFreeHandle]->lParam = lParam;
            m_HotKeyDetails[nFreeHandle]->sFunction = vParams[1].szValue();

            if (!RegisterHotKey(g_hWnd, (int)m_HotKeyDetails[nFreeHandle]->wParam, mods, vk))
            {
                // Failed!
                delete m_HotKeyDetails[nFreeHandle];    // Delete memory
                m_HotKeyDetails[nFreeHandle] = NULL;    // Mark as empty
                vResult = 0;                            // Error, default is 1
            }

            return AUT_OK;                        // Return (sucessfull or not)
        }
    }

    vResult = 0;                                // No free handles, error, default is 1

    return AUT_OK;

} // HotKeySet()
