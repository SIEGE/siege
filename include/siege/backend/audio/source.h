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

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmAudioSourceMaxSources(SGuint* max);

    SGuint SG_EXPORT sgmAudioSourceCreate(void** source);
    //SGuint SG_EXPORT sgmAudioSourceCreateData(void** source, void* buffer, float pitch, float gain, SGbool looping);
    SGuint SG_EXPORT sgmAudioSourceDestroy(void* source);
    SGuint SG_EXPORT sgmAudioSourcePlay(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsPlaying(void* source, SGbool* playing);
    SGuint SG_EXPORT sgmAudioSourcePause(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsPaused(void* source, SGbool* paused);
    SGuint SG_EXPORT sgmAudioSourceRewind(void* source);
    //SGuint SG_EXPORT sgmAudioSourceIsRewinded(void* source, SGbool* rewinded);
    SGuint SG_EXPORT sgmAudioSourceStop(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsStopped(void* source, SGbool* stopped);
    SGuint SG_EXPORT SG_HINT_DEPRECATED sgmAudioSourceSetBuffer(void* source, void* buffer);
    //SGuint SG_EXPORT SG_HINT_DEPRECATED sgmAudioSourceGetBuffer(void* source, void** buffer);
    SGuint SG_EXPORT sgmAudioSourceQueueBuffers(void* source, void** buffers, SGuint numbuffers);
    SGuint SG_EXPORT sgmAudioSourceUnqueueBuffers(void* source, SGuint numbuffers);
/// \warning Will most likely change very soon
    SGuint SG_EXPORT sgmAudioSourceGetNumProcessedBuffers(void* source, SGuint* processed);
    SGuint SG_EXPORT sgmAudioSourceGetNumQueuedBuffers(void* source, SGuint* queued);
    SGuint SG_EXPORT sgmAudioSourceSetPosition(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgmAudioSourceGetPosition(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT sgmAudioSourceSetVelocity(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgmAudioSourceGetVelocity(void* source, float* x, float* y, float* z);
    //SGuint SG_EXPORT sgmAudioSourceSetFalloff(void* source, float falloff);
    //SGuint SG_EXPORT sgmAudioSourceGetFalloff(void* source, float* falloff);
    SGuint SG_EXPORT sgmAudioSourceSetPitch(void* source, float pitch);
    SGuint SG_EXPORT sgmAudioSourceGetPitch(void* source, float* pitch);
    SGuint SG_EXPORT sgmAudioSourceSetVolume(void* source, float volume);
    SGuint SG_EXPORT sgmAudioSourceGetVolume(void* source, float* volume);
    SGuint SG_EXPORT sgmAudioSourceSetLooping(void* source, SGbool looping);
    SGuint SG_EXPORT sgmAudioSourceGetLooping(void* source, SGbool* looping);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_BACKEND_AUDIO_SOURCE_H__
