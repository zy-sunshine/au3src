#include "StdAfx.h"                                // Pre-compiled headers
#include "Engine/Engine.h"
#include "ModuleSound.h"
#include "Utils/SysUtil.h"

//AU3_FuncInfo ModuleSound::funcInfo[] = {
//    {"SOUNDPLAY", &ModuleSound::F_SoundPlay, 1, 2},
//    {"SOUNDSETWAVEVOLUME", &ModuleSound::F_SoundSetWaveVolume, 1, 1},
//};

///////////////////////////////////////////////////////////////////////////////
// SoundPlay()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSound::F_SoundPlay(VectorVariant &vParams, Variant &vResult)
{
    if (vParams.size() == 2 && vParams[1].nValue() == 1)
        g_oSysUtil.SoundPlay(vParams[0].szValue(), true);
    else
        g_oSysUtil.SoundPlay(vParams[0].szValue(), false);
    return AUT_OK;

} // SoundPlay()

///////////////////////////////////////////////////////////////////////////////
// SoundSetWaveVolume()
///////////////////////////////////////////////////////////////////////////////

AUT_RESULT ModuleSound::F_SoundSetWaveVolume(VectorVariant &vParams, Variant &vResult)
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
