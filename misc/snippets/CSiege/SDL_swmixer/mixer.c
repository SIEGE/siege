#include "mixer.h"
#include "buffer.h"
#include "source.h"
#include "endian.h"
#include <SDL/SDL.h>
#include <stdlib.h>

// todo: pitch, panning, channels, frequency
size_t _SWM_Convert(SWM_Source* source, float* data, size_t len)
{
    if(!source->playing)
        return 0;

    SWM_Buffer* buffer = source->buffer;
    SWM_BufferSpec* spec = buffer->spec;
    size_t clen = buffer->datalen - source->pos;
    if(clen > len)
        clen = len;
    size_t i;

    Uint64 ul; // just a buffer
    SDL_RWseek(buffer->rw, source->pos, SEEK_SET);
    for(i = 0; i * sizeof(float) < clen; i++)
    {
        if(spec->format & SWM_INT8)
        {
            Sint8* c = (Sint8*)&ul;
            Uint8* uc = (Uint8*)&ul;
            SDL_RWread(buffer->rw, c, 1, 1);
            if(spec->format & SWM_UNSIGNED)
                data[i] += *uc / 128.0f - 1.0f;
            else
                data[i] += *c / 128.0f;
        }
        else if(spec->format & SWM_INT16)
        {
            Sint16* c = (Sint16*)&ul;
            Uint16* uc = (Uint16*)&ul;
            if(spec->format & SWM_BE)
                *c = SDL_ReadBE16(buffer->rw);
            else
                *c = SDL_ReadLE16(buffer->rw);
            if(spec->format & SWM_UNSIGNED)
                data[i] += *uc / 32768.0f - 1.0f;
            else
                data[i] += *c / 32768.0f;
        }
        /*else if(spec->format & SWM_INT24)
        {
            Sint32* c = (Sint32*)&ul;
            Sint32* uc = (Uint32*)&ul;
            if(spec->format & SWM_BE)
                *c = SDL_ReadBE16(buffer->rw);
            else
                *c = SDL_ReadLE16(buffer->rw);
            if(spec->format & SWM_UNSIGNED)
                data[i] += *uc / 32768.0f - 1.0f;
            else
                data[i] += *c / 32768.0f;
        }*/
        else if(spec->format & SWM_INT32)
        {
            Sint32* c = (Sint32*)&ul;
            Uint32* uc = (Uint32*)&ul;
            if(spec->format & SWM_BE)
                *c = SDL_ReadBE32(buffer->rw);
            else
                *c = SDL_ReadLE32(buffer->rw);
            if(spec->format & SWM_UNSIGNED)
                data[i] += *uc / 2147483648.0f - 1.0f;
            else
                data[i] += *c / 2147483648.0f;
        }
        else if(spec->format & SWM_FLOAT)
        {
            Sint32* c = (Sint32*)&ul;
            float* fc = (float*)&ul;
            if(spec->format & SWM_BE)
                *c = SDL_ReadBE32(buffer->rw);
            else
                *c = SDL_ReadLE32(buffer->rw);
            data[i] += *fc;
        }
        else if(spec->format & SWM_DOUBLE)
        {
            Uint32* uc = (Uint32*)&ul;
            double* dc = (double*)&ul;
            if(spec->format & SWM_BE)
                *uc = SDL_ReadBE64(buffer->rw);
            else
                *uc = SDL_ReadLE64(buffer->rw);
            data[i] += (float)*dc;
        }

        data[i] *= source->volume;
    }

    source->pos += clen;
    if(source->pos > buffer->datalen)
    {
        if(source->looping)
            source->pos %= buffer->datalen;
        else
        {
            source->pos = buffer->datalen;
            source->playing = 0;
            source->stopped = 1;
        }
    }
    return clen;
}

// todo: global volume, pitch, panning + channels
void SDLCALL _SWM_SDLCallback(void* userdata, Uint8* stream, int len)
{
    float globvol = 0.25f;
    float globpitch = 1.0f;
    float globpan = 0.0f;

    size_t i;

    for(i = 0; i < _SWM_convbuflen; i++)
        _SWM_convbuf[i] = 0.0f;
    for(i = 0; i < _SWM_slistlen; i++)
    {
        SWM_Source* source = _SWM_slist[i];
        size_t conv = _SWM_Convert(source, _SWM_convbuf, _SWM_convbuflen);
        while((conv < _SWM_convbuflen) && (source->looping))
        {
            source->pos = 0;
            conv += _SWM_Convert(source, _SWM_convbuf + conv / sizeof(float), _SWM_convbuflen - conv / sizeof(float));
        }
    }

    Uint16* sstream = (Uint16*)stream;
    for(i = 0; i < _SWM_convbuflen; i++)
    {
        if(_SWM_obtained.channels == 2) // stereo
        {
            if((i % 2) == 0) // left channel
                _SWM_convbuf[i] *= (1.0 - globpan);
            else // right channel
                _SWM_convbuf[i] *= (1.0 + globpan);
        }

        if(_SWM_obtained.format == AUDIO_U8)
            stream[i] = (Uint8)((_SWM_convbuf[i] + 1.0f) * 128.0f * globvol);
        if(_SWM_obtained.format == AUDIO_S8)
            stream[i] = (Sint8)(_SWM_convbuf[i] * 128.0f * globvol);
        if(_SWM_obtained.format == AUDIO_U16LSB)
            sstream[i] = _SWM_ToLE16((Uint16)((_SWM_convbuf[i] + 1.0f) * 32768.0f * globvol));
        if(_SWM_obtained.format == AUDIO_S16LSB)
            sstream[i] = _SWM_ToLE16((Sint16)(_SWM_convbuf[i] * 32768.0f * globvol));
        if(_SWM_obtained.format == AUDIO_U16MSB)
            sstream[i] = _SWM_ToBE16((Uint16)((_SWM_convbuf[i] + 1.0f) * 32768.0f * globvol));
        if(_SWM_obtained.format == AUDIO_S16MSB)
            sstream[i] = _SWM_ToBE16((Uint16)(_SWM_convbuf[i] * 32768.0f * globvol));
    }
}

int SWM_Init()
{
    SDL_AudioSpec desired;
    desired.freq = 44100;
    desired.format = AUDIO_S8;
    desired.channels = 1;
    desired.samples = 1024;
    desired.callback = _SWM_SDLCallback;
    desired.userdata = NULL;
    SDL_OpenAudio(&desired, /*&_SWM_obtained*/NULL);
    _SWM_obtained = desired;
    _SWM_convbuflen = _SWM_obtained.samples * _SWM_obtained.channels;
    _SWM_convbuf = malloc(_SWM_convbuflen * sizeof(float));

    _SWM_slist = NULL;
    _SWM_slistlen = 0;

    SDL_PauseAudio(0);
    return 0;
}

int SWM_Quit()
{
    SDL_CloseAudio();
    free(_SWM_convbuf);
    return 0;
}

