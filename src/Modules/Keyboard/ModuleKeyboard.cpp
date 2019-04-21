#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleKeyboard.h"

ModuleKeyboard::ModuleKeyboard(Engine* engine)
    : engine(engine) 
{
    // Initialise hotkeys to NULL 
    for (unsigned i=0; i<AUT_MAXHOTKEYS; ++i)
        m_HotKeyDetails[i] = NULL;
    m_nHotKeyQueuePos    = 0;
}

ModuleKeyboard::~ModuleKeyboard()
{
    // Free memory for hotkeys and unregister hotkeys if required
    for (unsigned i=0; i<AUT_MAXHOTKEYS; ++i)
    {
        if (m_HotKeyDetails[i] != NULL)
        {
            UnregisterHotKey(engine->g_hWnd, (int)m_HotKeyDetails[i]->wParam);
            delete m_HotKeyDetails[i];            // Delete memory
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Send()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleKeyboard::F_Send(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() == 2)
    {
        if (vParams[1].nValue() == 0)
            engine->oSendKeys().Send(vParams[0].szValue());        // Normal send
        else
            engine->oSendKeys().SendRaw(vParams[0].szValue());    // Raw send
    }
    else
        engine->oSendKeys().Send(vParams[0].szValue());    // Normal send

    return AUT_OK;

} // Send()

///////////////////////////////////////////////////////////////////////////////
// HotKeySet(key ([mod]key, function)
//
// Sets a hotkey
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleKeyboard::F_HotKeySet(VectorVariant &vParams, Variant &vResult)
{
    uint    iNumParams = vParams.size();
    int        nTemp1, nTemp2, nTemp3, nTemp4;
    bool    bShift, bControl, bAlt, bWin;
    UINT    mods = 0;
    UINT    vk;
    int        nFreeHandle;
    LPARAM    lParam;


    // Unless blank, check that the requested user function exists
    if (iNumParams >= 2 && engine->parser()->FindUserFunction(vParams[1].szValue(), nTemp1, nTemp2, nTemp3, nTemp4) == false)
    {
        engine->FatalError(IDS_AUT_E_UNKNOWNUSERFUNC);
        return AUT_ERR;
    }


    // Get the virtual key code and modifiers
    if (engine->oSendKeys().GetSingleVKandMods(vParams[0].szValue(), vk, bShift, bControl, bAlt, bWin) == false)
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
                    UnregisterHotKey(engine->g_hWnd, (int)m_HotKeyDetails[nFreeHandle]->wParam);    // Unregister
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

            if (!RegisterHotKey(engine->g_hWnd, (int)m_HotKeyDetails[nFreeHandle]->wParam, mods, vk))
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

///////////////////////////////////////////////////////////////////////////////
// HandleHotKey()
//
// Handles the processing of a hotkey and calls a function
///////////////////////////////////////////////////////////////////////////////

bool ModuleKeyboard::HandleHotKey(void)
{
    // See if there is a hotkey request in the queue - only process one per loop!
    if (m_nHotKeyQueuePos == engine->g_HotKeyNext)
        return false;

    // What ID is the hotkey pressed?  Also increment the position and reset if needed
    WPARAM wParam = engine->g_HotKeyQueue[m_nHotKeyQueuePos++];
    if (m_nHotKeyQueuePos >= AUT_HOTKEYQUEUESIZE)
        m_nHotKeyQueuePos = 0;                    // reset

    // Find the corresponding hotkey definition and function
    int        n;

    for (n = 0; n < AUT_MAXHOTKEYS; ++n)
    {
        if (m_HotKeyDetails[n] != NULL && m_HotKeyDetails[n]->wParam == wParam)
            break;
    }
    if (n == AUT_MAXHOTKEYS)
        return false;                            // Not found the ID! Ignore

    Variant vResult;
    engine->interruptCall(m_HotKeyDetails[n]->sFunction.c_str(), vResult);

    return true;                                // Returning true will stop further
                                                // progress in Execute() and start the loop again
} // HandleHotKey()
