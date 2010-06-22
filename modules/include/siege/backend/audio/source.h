#ifndef __SIEGE_AUDIO_SOURCE_H__
#define __SIEGE_AUDIO_SOURCE_H__

#include "../../common.h"

#ifdef SG_LEGACY_API
#   define sgAudioSourceCreate sgmAudioSourceCreate
//#   define sgAudioSourceCreateData sgmAudioSourceCreateData
#    define sgAudioSourceDestroy sgmAudioSourceDestroy
#    define sgAudioSourcePlay sgmAudioSourcePlay
#    define sgAudioSourceIsPlaying sgmAudioSourceIsPlaying
#    define sgAudioSourcePause sgmAudioSourcePause
#    define sgAudioSourceIsPaused sgmAudioSourceIsPaused
#    define sgAudioSourceRewind sgmAudioSourceRewind
//#    define sgAudioSourceIsRewinded sgmAudioSourceIsRewinded
#    define sgAudioSourceStop sgmAudioSourceStop
#    define sgAudioSourceIsStopped sgmAudioSourceIsStopped
#    define sgAudioSourceSetSample sgmAudioSourceSetBuffer
//#    define sgAudioSourceGetSample sgmAudioSourceGetBuffer
#    define sgAudioSourceSetPosition sgmAudioSourceSetPosition
#    define sgAudioSourceGetPosition sgmAudioSourceGetPosition
#    define sgAudioSourceSetVelocity sgmAudioSourceSetVelocity
#    define sgAudioSourceGetVelocity sgmAudioSourceGetVelocity
#    define sgAudioSourceSetPitch sgmAudioSourceSetPitch
#    define sgAudioSourceGetPitch sgmAudioSourceGetPitch
#    define sgAudioSourceSetGain sgmAudioSourceSetVolume
#    define sgAudioSourceGetGain sgmAudioSourceGetVolume
#    define sgAudioSourceSetLooping sgmAudioSourceSetLooping
#    define sgAudioSourceGetLooping sgmAudioSourceGetLooping
#endif // SG_LEGACY_API

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgmAudioSourceMaxSources(SGuint* max);

    SGuint SG_EXPORT sgmAudioSourceCreate(void** source);
    //SGuint SG_EXPORT sgmAudioSourceCreateData(void** source, void* sample, float pitch, float gain, SGbool looping);
    SGuint SG_EXPORT sgmAudioSourceDestroy(void* source);
    SGuint SG_EXPORT sgmAudioSourcePlay(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsPlaying(void* source, SGbool* playing);
    SGuint SG_EXPORT sgmAudioSourcePause(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsPaused(void* source, SGbool* paused);
    SGuint SG_EXPORT sgmAudioSourceRewind(void* source);
    //SGuint SG_EXPORT sgmAudioSourceIsRewinded(void* source, SGbool* rewinded);
    SGuint SG_EXPORT sgmAudioSourceStop(void* source);
    SGuint SG_EXPORT sgmAudioSourceIsStopped(void* source, SGbool* stopped);
    SGuint SG_EXPORT SG_DEPRECATED sgmAudioSourceSetBuffer(void* source, void* sample);
    //SGuint SG_EXPORT SG_DEPRECATED sgmAudioSourceGetBuffer(void* source, void** sample);
/// \warning Will most likely change very soon
    SGuint SG_EXPORT sgmAudioSourceGetNumProcessedBuffers(void* source, SGuint* processed);
    SGuint SG_EXPORT sgmAudioSourceGetNumQueuedBuffers(void* source, SGuint* queued);
    SGuint SG_EXPORT sgmAudioSourceSetPosition(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgmAudioSourceGetPosition(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT sgmAudioSourceSetVelocity(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgmAudioSourceGetVelocity(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT sgmAudioSourceSetFalloff(void* source, float falloff);
    SGuint SG_EXPORT sgmAudioSourceGetFalloff(void* source, float* falloff);
    SGuint SG_EXPORT sgmAudioSourceSetPitch(void* source, float pitch);
    SGuint SG_EXPORT sgmAudioSourceGetPitch(void* source, float* pitch);
    SGuint SG_EXPORT sgmAudioSourceSetVolume(void* source, float volume);
    SGuint SG_EXPORT sgmAudioSourceGetVolume(void* source, float* volume);
    SGuint SG_EXPORT sgmAudioSourceSetLooping(void* source, SGbool looping);
    SGuint SG_EXPORT sgmAudioSourceGetLooping(void* source, SGbool* looping);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AUDIO_SOURCE_H__
