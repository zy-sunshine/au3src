#include "StdAfx.h"                                // Pre-compiled headers
#include "ModuleSound.h"

///////////////////////////////////////////////////////////////////////////////
// SoundPlay()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_SoundPlay(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() == 2 && vParams[1].nValue() == 1)
        Util_SoundPlay(vParams[0].szValue(), true);
    else
        Util_SoundPlay(vParams[0].szValue(), false);
    return AUT_OK;

} // SoundPlay()

///////////////////////////////////////////////////////////////////////////////
// SoundSetWaveVolume()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT AutoIt_Script::F_SoundSetWaveVolume(VectorVariant &vParams, Variant &vResult)
{
    int nVol = vParams[0].nValue();
    if((nVol>=0)&&(nVol<101))
    {
        WORD wVolume = (WORD)(0xFFFF*nVol/100);
        waveOutSetVolume(0,MAKELONG(wVolume,wVolume));
    }
    else
        engine->SetFuncErrorCode(1);

    return AUT_OK;

} // SoundSetWaveVolume()
