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

#ifndef __SIEGE_BACKEND_AUDIO_SOURCE_H__
#define __SIEGE_BACKEND_AUDIO_SOURCE_H__

#include "../../common.h"

#ifndef SG_FPTR
#define SG_FPTR(name)	name
#endif // SG_FPTR

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceMaxSources)(SGuint* max);

    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceCreate)(void** source);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioSourceCreateData)(void** source, void* buffer, float pitch, float gain, SGbool looping);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceDestroy)(void* source);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourcePlay)(void* source);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceIsPlaying)(void* source, SGbool* playing);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourcePause)(void* source);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceIsPaused)(void* source, SGbool* paused);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceRewind)(void* source);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioSourceIsRewinded)(void* source, SGbool* rewinded);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceStop)(void* source);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceIsStopped)(void* source, SGbool* stopped);
    SGuint SG_EXPORT SG_HINT_DEPRECATED SG_FPTR(sgmAudioSourceSetBuffer)(void* source, void* buffer);
    //SGuint SG_EXPORT SG_HINT_DEPRECATED (sgmAudioSourceGetBuffer)(void* source, void** buffer);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceQueueBuffers)(void* source, void** buffers, SGuint numbuffers);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceUnqueueBuffers)(void* source, SGuint numbuffers);
/// \warning Will most likely change very soon
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetNumProcessedBuffers)(void* source, SGuint* processed);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetNumQueuedBuffers)(void* source, SGuint* queued);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetPosition)(void* source, float x, float y, float z);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetPosition)(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetVelocity)(void* source, float x, float y, float z);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetVelocity)(void* source, float* x, float* y, float* z);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetFalloff)(void* source, float falloff);
    //SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetFalloff)(void* source, float* falloff);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetPitch)(void* source, float pitch);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetPitch)(void* source, float* pitch);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetVolume)(void* source, float volume);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetVolume)(void* source, float* volume);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceSetLooping)(void* source, SGbool looping);
    SGuint SG_EXPORT SG_FPTR(sgmAudioSourceGetLooping)(void* source, SGbool* looping);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_SOURCE_H__
