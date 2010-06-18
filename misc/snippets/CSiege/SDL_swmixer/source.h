#ifndef __SOURCE_H__
#define __SOURCE_H__
#include <SDL/SDL.h>
#include "common.h"

struct SWM_Source** _SWM_slist;
size_t _SWM_slistlen;
typedef struct SWM_Source
{
    struct SWM_Buffer* buffer;
    Uint32 flags;

    size_t pos;
    Uint8 playing;
    Uint8 paused;
    Uint8 stopped;
    Uint8 looping;
    float volume;
    float pitch;
    float pan;
} SWM_Source;

size_t _SWM_Convert(SWM_Source* source, float* data, size_t datalen);

struct SWM_Source* SWM_CreateSource(struct SWM_Buffer* buffer, Uint32 flags);
void SWM_DestroySource(struct SWM_Source* source);

void SWM_Play(struct SWM_Source* source);
void SWM_PlayBlocking(struct SWM_Source* source);
Uint8 SWM_IsPlaying(struct SWM_Source* source);
void SWM_Pause(struct SWM_Source* source);
Uint8 SWM_IsPaused(struct SWM_Source* source);
void SWM_Stop(struct SWM_Source* source);
Uint8 SWM_IsStopped(struct SWM_Source* source);

void SWM_SetLooping(struct SWM_Source* source, Uint8 looping);
Uint8 SWM_GetLooping(struct SWM_Source* source); // should this be SWM_IsLooping?
void SWM_SetVolume(struct SWM_Source* source, float volume);
float SWM_GetVolume(struct SWM_Source* source);
void SWM_SetPitch(struct SWM_Source* source, float pitch);
float SWM_GetPitch(struct SWM_Source* source);
void SWM_SetPan(struct SWM_Source* source, float pan);
float SWM_GetPan(struct SWM_Source* source);

#endif // __SOURCE_H__
