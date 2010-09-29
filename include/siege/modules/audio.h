#ifndef __SIEGE_MODULES_AUDIO_H__
#define __SIEGE_MODULES_AUDIO_H__
#include "../common.h"
#include "../util/link.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
typedef struct SGModuleAudio
{
    /// Audio
    SGuint SG_EXPORT (*sgmAudioSourceMaxSources)(SGuint* max);

    SGuint SG_EXPORT (*sgmAudioBufferCreate)(void** buffer);
    //SGuint SG_EXPORT (*sgmAudioBufferCreateData)(void** buffer, SGuint channels, SGuint type, SGuint frequency, void* data, SGuint datalen);
    SGuint SG_EXPORT (*sgmAudioBufferSetData)(void* buffer, SGuint channels, SGuint type, SGuint frequency, void* data, SGuint datalen);
    //SGuint SG_EXPORT (*sgmAudioBufferGetData)(void* buffer, SGuint* channels, SGuint* type, SGuint* frequency, void** data, SGuint* datalen);
    //SGuint SG_EXPORT (*sgmAudioBufferFreeData)(void* data);
    SGuint SG_EXPORT (*sgmAudioBufferDestroy)(void* buffer);

    SGuint SG_EXPORT (*sgmAudioSourceCreate)(void** source);
    //SGuint SG_EXPORT (*sgmAudioSourceCreateData)(void** source, void* buffer, float pitch, float gain, SGbool looping);
    SGuint SG_EXPORT (*sgmAudioSourceDestroy)(void* source);
    SGuint SG_EXPORT (*sgmAudioSourcePlay)(void* source);
    SGuint SG_EXPORT (*sgmAudioSourceIsPlaying)(void* source, SGbool* playing);
    SGuint SG_EXPORT (*sgmAudioSourcePause)(void* source);
    SGuint SG_EXPORT (*sgmAudioSourceIsPaused)(void* source, SGbool* paused);
    SGuint SG_EXPORT (*sgmAudioSourceRewind)(void* source);
    //SGuint SG_EXPORT (*sgmAudioSourceIsRewinded)(void* source, SGbool* rewinded);
    SGuint SG_EXPORT (*sgmAudioSourceStop)(void* source);
    SGuint SG_EXPORT (*sgmAudioSourceIsStopped)(void* source, SGbool* stopped);
    SGuint SG_EXPORT (*sgmAudioSourceSetBuffer)(void* source, void* buffer);
    //SGuint SG_EXPORT (*sgmAudioSourceGetBuffer)(void* source, void** buffer);

    SGuint SG_EXPORT (*sgmAudioSourceQueueBuffers)(void* source, void** buffers, SGuint numbuffers);
    SGuint SG_EXPORT (*sgmAudioSourceUnqueueBuffers)(void* source, SGuint numbuffers);
/// \warning Will most likely change very soon
    SGuint SG_EXPORT (*sgmAudioSourceGetNumProcessedBuffers)(void* source, SGuint* processed);
    SGuint SG_EXPORT (*sgmAudioSourceGetNumQueuedBuffers)(void* source, SGuint* queued);
    SGuint SG_EXPORT (*sgmAudioSourceSetPosition)(void* source, float x, float y, float z);
    SGuint SG_EXPORT (*sgmAudioSourceGetPosition)(void* source, float* x, float* y, float* z);
    SGuint SG_EXPORT (*sgmAudioSourceSetVelocity)(void* source, float x, float y, float z);
    SGuint SG_EXPORT (*sgmAudioSourceGetVelocity)(void* source, float* x, float* y, float* z);
    //SGuint SG_EXPORT (*sgmAudioSourceSetFalloff)(void* source, float falloff);
    //SGuint SG_EXPORT (*sgmAudioSourceGetFalloff)(void* source, float* falloff);
    SGuint SG_EXPORT (*sgmAudioSourceSetPitch)(void* source, float pitch);
    SGuint SG_EXPORT (*sgmAudioSourceGetPitch)(void* source, float* pitch);
    SGuint SG_EXPORT (*sgmAudioSourceSetVolume)(void* source, float volume);
    SGuint SG_EXPORT (*sgmAudioSourceGetVolume)(void* source, float* volume);
    SGuint SG_EXPORT (*sgmAudioSourceSetLooping)(void* source, SGbool looping);
    SGuint SG_EXPORT (*sgmAudioSourceGetLooping)(void* source, SGbool* looping);

    /// Audio Load
    SGuint SG_EXPORT (*sgmAudioLoadFile)(char* fname, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    //SGuint SG_EXPORT (*sgmAudioLoadStream)(void* stream, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen);
    SGuint SG_EXPORT (*sgmAudioLoadFreeData)(void* data);

    SGuint SG_EXPORT (*sgmAudioFileCreate)(void** file, char* fname, SGuint* channels, SGuint* format, SGuint* frequency);
    SGuint SG_EXPORT (*sgmAudioFileDestroy)(void* file);
    SGuint SG_EXPORT (*sgmAudioFileNumSamples)(void* file, SGuint* samples);
    SGuint SG_EXPORT (*sgmAudioFileRead)(void* file, void* data, SGuint* datalen);
} SGModuleAudio;

#ifdef SG_BUILD_LIBRARY
SGModuleAudio _sg_modAudio;
#endif // SG_BUILD_LIBRARY

void SG_EXPORT _sgModuleLoadAudio(SGLibrary* lib);

SGModuleAudio* SG_EXPORT sgModuleGetAudio(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_MODULES_AUDIO_H__
