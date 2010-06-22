#ifndef __SIEGE_AUDIO_SOURCE_H__
#define __SIEGE_AUDIO_SOURCE_H__

#include "../../common.h"

#ifdef __cplusplus
extern "C"
{
#endif
    SGuint SG_EXPORT sgAudioSourceCreate(void** source);
    //SGuint SG_EXPORT sgAudioSourceCreateData(void** source, void* sample, float pitch, float gain, SGbool looping);
    SGuint SG_EXPORT sgAudioSourceDestroy(void* source);
    SGuint SG_EXPORT sgAudioSourcePlay(void* source);
    SGuint SG_EXPORT sgAudioSourceIsPlaying(void* source, SGbool* playing);
    SGuint SG_EXPORT sgAudioSourcePause(void* source);
    SGuint SG_EXPORT sgAudioSourceIsPaused(void* source, SGbool* paused);
    SGuint SG_EXPORT sgAudioSourceRewind(void* source);
    //SGuint SG_EXPORT sgAudioSourceIsRewinded(void* source, SGbool* rewinded);
    SGuint SG_EXPORT sgAudioSourceStop(void* source);
    SGuint SG_EXPORT sgAudioSourceIsStopped(void* source, SGbool* stopped);
    SGuint SG_EXPORT sgAudioSourceSetSample(void* source, void* sample);
    //SGuint SG_EXPORT sgAudioSourceGetSample(void* source, void** sample);
    SGuint SG_EXPORT sgAudioSourceSetPosition(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgAudioSourceGetPosition(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT sgAudioSourceSetVelocity(void* source, float x, float y, float z);
    SGuint SG_EXPORT sgAudioSourceGetVelocity(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT sgAudioSourceSetPitch(void* source, float pitch);
    SGuint SG_EXPORT sgAudioSourceGetPitch(void* source, float* pitch);
    SGuint SG_EXPORT sgAudioSourceSetGain(void* source, float gain);
    SGuint SG_EXPORT sgAudioSourceGetGain(void* source, float* gain);
    SGuint SG_EXPORT sgAudioSourceSetLooping(void* source, SGbool looping);
    SGuint SG_EXPORT sgAudioSourceGetLooping(void* source, SGbool* looping);
#ifdef __cplusplus
}
#endif

#endif // __SIEGE_AUDIO_SOURCE_H__
