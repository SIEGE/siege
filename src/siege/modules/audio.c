/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/audio.h>

void SG_CALL _sgModuleLoadAudio(SGLibrary* lib)
{
    void* fptr;
    /// Audio
    _SG_BIND(sgmAudioBufferCreate);
    //_SG_BIND(sgmAudioBufferCreateData);
    _SG_BIND(sgmAudioBufferDestroy);
    _SG_BIND(sgmAudioBufferSetData);
    //_SG_BIND(sgmAudioBufferGetData);
    //_SG_BIND(sgmAudioBufferFreeData);
    _SG_BIND(sgmAudioBufferSetHandle);

	_SG_BIND(sgmAudioSourceMaxSources);

    _SG_BIND(sgmAudioSourceCreate);
    //_SG_BIND(sgmAudioSourceCreateData);
    _SG_BIND(sgmAudioSourceDestroy);
    _SG_BIND(sgmAudioSourcePlay);
    _SG_BIND(sgmAudioSourceIsPlaying);
    _SG_BIND(sgmAudioSourcePause);
    _SG_BIND(sgmAudioSourceIsPaused);
    _SG_BIND(sgmAudioSourceRewind);
    //_SG_BIND(sgmAudioSourceIsRewinded);
    _SG_BIND(sgmAudioSourceStop);
    _SG_BIND(sgmAudioSourceIsStopped);
    _SG_BIND(sgmAudioSourceSetBuffer);
    //_SG_BIND(sgmAudioSourceGetBuffer);
    _SG_BIND(sgmAudioSourceQueueBuffers);
    _SG_BIND(sgmAudioSourceUnqueueBuffers);
    _SG_BIND(sgmAudioSourceGetNumProcessedBuffers);
    _SG_BIND(sgmAudioSourceGetNumQueuedBuffers);
    _SG_BIND(sgmAudioSourceSetPosition);
    _SG_BIND(sgmAudioSourceGetPosition);
    _SG_BIND(sgmAudioSourceSetVelocity);
    _SG_BIND(sgmAudioSourceGetVelocity);
    //_SG_BIND(sgmAudioSourceSetFalloff);
    //_SG_BIND(sgmAudioSourceGetFalloff);
    _SG_BIND(sgmAudioSourceSetPitch);
    _SG_BIND(sgmAudioSourceGetPitch);
    _SG_BIND(sgmAudioSourceSetVolume);
    _SG_BIND(sgmAudioSourceGetVolume);
    _SG_BIND(sgmAudioSourceSetLooping);
    _SG_BIND(sgmAudioSourceGetLooping);

    /// Audio Load
    _SG_BIND(sgmAudioFileCreate);
    _SG_BIND(sgmAudioFileDestroy);
    _SG_BIND(sgmAudioFileNumSamples);
    _SG_BIND(sgmAudioFileRead);

    _SG_BIND(sgmAudioFileGetHandle);
}
