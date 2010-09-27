#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <SDL/SDL.h>
#include "common.h"

typedef struct SWM_BufferSpec
{
    SDL_AudioSpec spec;
    Uint32 flags;
    Uint32 freq;
    Uint32 format;
    Uint8 channels;
    Uint8 _res1;
    Uint16 _res2;
    Uint32 samples;
    Uint32 size;
} SWM_BufferSpec;

typedef struct SWM_Buffer
{
    SWM_BufferSpec* spec;
    struct SDL_RWops* rw;
    int refcount;

    void* data; // used if SWM_COPY
    size_t datalen;
} SWM_Buffer;

SWM_Buffer* SWM_CreateBuffer(SWM_BufferSpec* spec, void* data, size_t length);
SWM_Buffer* SWM_CreateBufferRW(SWM_BufferSpec* spec, SDL_RWops* rw);
void SWM_DestroyBuffer(SWM_Buffer* buffer);

#endif // __BUFFER_H__
