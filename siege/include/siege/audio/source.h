#ifndef __SIEGE_AUDIO_SOURCE_H__
#define __SIEGE_AUDIO_SOURCE_H__
#include "../common.h"
#include "buffer.h"
#include "../util/plist.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef struct SGSourceDispatch
{
    struct SGSource* source;
    void* handle;
} SGSourceDispatch;

typedef struct SGSource
{
    SGSourceDispatch* dispatch;
    float priority;
} SGSource;

#ifdef SG_BUILD_LIBRARY
SGSourceDispatch* _sg_srcDisList;
SGuint _sg_srcDisLength;
#endif // SG_BUILD_LIBRARY

SGbool SG_EXPORT _sgSourceInit(void);
SGbool SG_EXPORT _sgSourceDeinit(void);

SGSourceDispatch* SG_EXPORT _sgSourceGetFreeDispatch(SGSource* source);

SGSource* SG_EXPORT sgSourceCreate(SGBuffer* buffer, float priority, float volume, float pitch, SGbool looping);
void SG_EXPORT sgSourceDestroy(SGSource* source);
void SG_EXPORT sgSourcePlay(SGSource* source);
SGbool SG_EXPORT sgSourceIsPlaying(SGSource* source);
void SG_EXPORT sgSourcePause(SGSource* source);
SGbool SG_EXPORT sgSourceIsPaused(SGSource* source);
void SG_EXPORT sgSourceRewind(SGSource* source);
//SGbool SG_EXPORT sgSourceIsRewinded(SGSource* source);
void SG_EXPORT sgSourceStop(SGSource* source);
SGbool SG_EXPORT sgSourceIsStopped(SGSource* source);
SGbool SG_EXPORT sgSourceIsActive(SGSource* source);
void SG_EXPORT sgSourceQueueBuffers(SGSource* source, SGBuffer** buffers, SGuint numbuffers);
void SG_EXPORT sgSourceQueueBuffer(SGSource* source, SGBuffer* buffer);

void SG_EXPORT sgSourceSetPosition3f(SGSource* source, float x, float y, float z);
void SG_EXPORT sgSourceSetPosition2f(SGSource* source, float x, float y);
void SG_EXPORT sgSourceGetPosition3f(SGSource* source, float* x, float* y, float* z);
void SG_EXPORT sgSourceGetPosition2f(SGSource* source, float* x, float* y);

void SG_EXPORT sgSourceSetVelocity3f(SGSource* source, float x, float y, float z);
void SG_EXPORT sgSourceSetVelocity2f(SGSource* source, float x, float y);
void SG_EXPORT sgSourceGetVelocity3f(SGSource* source, float* x, float* y, float* z);
void SG_EXPORT sgSourceGetVelocity2f(SGSource* source, float* x, float* y);

//void SG_EXPORT sgSourceSetFalloff(SGSource* source, float falloff);
//float SG_EXPORT sgSourceGetFalloff(SGSource* source);

void SG_EXPORT sgSourceSetPitch(SGSource* source, float pitch);
float SG_EXPORT sgSourceGetPitch(SGSource* source);

void SG_EXPORT sgSourceSetVolume(SGSource* source, float volume);
float SG_EXPORT sgSourceGetVolume(SGSource* source);

void SG_EXPORT sgSourceSetLooping(SGSource* source, SGbool looping);
SGbool SG_EXPORT sgSourceGetLooping(SGSource* source);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SIEGE_AUDIO_SOURCE_H__
