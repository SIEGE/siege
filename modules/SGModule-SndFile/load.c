#include "main.h"
#include "load.h"
#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgAudioLoadFile(char* fname, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen)
{
    SF_INFO info;
    info.format = 0;
    SNDFILE* file = sf_open(fname, SFM_READ, &info);
    if(file == NULL)
        return SG_UNKNOWN_ERROR;

    int size;
    switch(info.format & SF_FORMAT_SUBMASK)
    {
        case SF_FORMAT_FLOAT:
            *format = SG_AUDIO_FORMAT_F;
            size = 4;
            break;
        case SF_FORMAT_DOUBLE:
            *format = SG_AUDIO_FORMAT_D;
            size = 8;
            break;
        case SF_FORMAT_PCM_S8:
        case SF_FORMAT_PCM_16:
        case SF_FORMAT_PCM_U8:
            *format = SG_AUDIO_FORMAT_S16;
            size = 2;
            break;
        case SF_FORMAT_PCM_24:
        case SF_FORMAT_PCM_32:
        default:
            *format = SG_AUDIO_FORMAT_S32;
            size = 4;
    }

    *channels = info.channels;
    *frequency = info.samplerate;
    *data = malloc(info.frames * info.channels * size);
    *datalen = info.frames * info.channels * size;

    switch(*format)
    {
        case SG_AUDIO_FORMAT_S16:
            sf_read_short(file, (SGshort*)*data, info.frames * info.channels);
            break;
        case SG_AUDIO_FORMAT_S32:
            sf_read_int(file, (SGint*)*data, info.frames * info.channels);
            break;
        case SG_AUDIO_FORMAT_F:
            sf_read_float(file, (SGfloat*)*data, info.frames * info.channels);
            break;
        case SG_AUDIO_FORMAT_D:
            sf_read_double(file, (SGdouble*)*data, info.frames * info.channels);
            break;
        default:
            sf_close(file);
            return SG_UNKNOWN_ERROR;
    }

    if(sf_close(file) != 0)
        return SG_UNKNOWN_ERROR;

    return SG_OK;
}

//SGuint SG_EXPORT sgAudioLoadStream(void* stream, SGuint* channels, SGuint* format, SGuint* frequency, void** data, SGuint* datalen)

SGuint SG_EXPORT sgAudioLoadFreeData(void* data)
{
    free(data);
    return SG_OK;
}
