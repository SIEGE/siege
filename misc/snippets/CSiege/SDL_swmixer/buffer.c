#include "buffer.h"
#include <SDL/SDL.h>
#include <stdlib.h>

SWM_Buffer* SWM_CreateBuffer(SWM_BufferSpec* spec, void* data, size_t length)
{
    void* newdata = data;
    if(spec->flags & SWM_COPY)
    {
        newdata = malloc(length);
        memcpy(newdata, data, length);
    }

    SDL_RWops* rw = SDL_RWFromMem(newdata, length);
    SWM_Buffer* buffer = SWM_CreateBufferRW(spec, rw);
    if(spec->flags & SWM_COPY)
        buffer->data = newdata;
    return buffer;
}
SWM_Buffer* SWM_CreateBufferRW(SWM_BufferSpec* spec, SDL_RWops* rw)
{
    SWM_Buffer* buffer = malloc(sizeof(SWM_Buffer));
    buffer->spec = malloc(sizeof(SWM_BufferSpec));
    memcpy(buffer->spec, spec, sizeof(SWM_BufferSpec));
    buffer->refcount = 0;
    buffer->data = NULL;
    buffer->datalen = SDL_RWseek(rw, 0, SEEK_END);

// use native system byte ordering if nothing else is available
    if(!(buffer->spec->flags & SWM_BE) && !(buffer->spec->flags & SWM_LE))
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
        buffer->spec->flags |= SWM_LE;
#else
        buffer->spec->flags |= SWM_BE;
#endif

    return buffer;
}
void SWM_DestroyBuffer(SWM_Buffer* buffer)
{
    if(buffer->spec->flags & (SWM_COPY | SWM_CONV))
        free(buffer->data);
    free(buffer->spec);
    SDL_RWclose(buffer->rw);
    SDL_FreeRW(buffer->rw);
    free(buffer);
}
