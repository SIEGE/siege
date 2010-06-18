#include "source.h"
#include "buffer.h"
#include <SDL/SDL.h>
#include <stdlib.h>

struct SWM_Source* SWM_CreateSource(struct SWM_Buffer* buffer, Uint32 flags)
{
    SWM_Source* source = malloc(sizeof(SWM_Source));
    source->buffer = buffer;
    source->flags = flags;

    source->pos = 0;
    source->playing = 0;
    source->paused = 0;
    source->stopped = 1;
    source->looping = 0;
    source->volume = 1.0f;
    source->pitch = 1.0f;
    source->pan = 0.0f;

    _SWM_slist = realloc(_SWM_slist, (_SWM_slistlen + 1) * sizeof(SWM_Source*));
    _SWM_slist[_SWM_slistlen++] = source;

    return source;
}
void SWM_DestroySource(struct SWM_Source* source)
{
    source->buffer->refcount--;
    if((source->buffer->refcount == 0) && (source->buffer->spec->flags & SWM_AUTOREMOVE))
        SWM_DestroyBuffer(source->buffer);

    ptrdiff_t i;
    for(i = 0; i < _SWM_slistlen; i++)
        if(_SWM_slist[i] == source)
        {
            memmove(_SWM_slist[i], _SWM_slist[i+1], (_SWM_slistlen - i - 1) * sizeof(SWM_Source*));
            _SWM_slist = realloc(_SWM_slist, --_SWM_slistlen * sizeof(SWM_Source*));
            break;
        }

    free(source);
}

void SWM_Play(struct SWM_Source* source)
{
    source->playing = 1;
    source->paused = 0;
    source->stopped = 0;
}
void SWM_PlayBlocking(struct SWM_Source* source)
{
    Uint8 looping = source->looping;

    source->playing = 1;
    source->paused = 0;
    source->stopped = 0;

    source->looping = 0; // can't block and loop...
    while(source->playing)
    {
    }
    source->looping = looping;
}
Uint8 SWM_IsPlaying(struct SWM_Source* source)
{
    return source->playing;
}
void SWM_Pause(struct SWM_Source* source)
{
    source->playing = 0;
    source->paused = 1;
    source->stopped = 0;
}
Uint8 SWM_IsPaused(struct SWM_Source* source)
{
    return source->paused;
}
void SWM_Stop(struct SWM_Source* source)
{
    source->pos = 0;
    source->playing = 0;
    source->paused = 0;
    source->stopped = 1;
}
Uint8 SWM_IsStopped(struct SWM_Source* source)
{
    return source->stopped;
}

void SWM_SetLooping(struct SWM_Source* source, Uint8 looping)
{
    source->looping = looping;
}
Uint8 SWM_GetLooping(struct SWM_Source* source) // should this be SWM_IsLooping?
{
    return source->looping;
}
void SWM_SetVolume(struct SWM_Source* source, float volume)
{
    source->volume = volume;
}
float SWM_GetVolume(struct SWM_Source* source)
{
    return source->volume;
}
void SWM_SetPitch(struct SWM_Source* source, float pitch)
{
    source->pitch = pitch;
}
float SWM_GetPitch(struct SWM_Source* source)
{
    return source->pitch;
}
void SWM_SetPan(struct SWM_Source* source, float pan)
{
    source->pan = pan;
}
float SWM_GetPan(struct SWM_Source* source)
{
    return source->pan;
}
