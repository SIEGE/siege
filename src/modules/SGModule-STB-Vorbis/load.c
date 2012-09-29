/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "COPYING.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "common.h"

#include <stdlib.h>
#include <string.h>

#define FORMAT_TYPE SG_AUDIO_FORMAT_S16
#define FORMAT_SIZE sizeof(SGshort)

typedef struct LFile
{
    stb_vorbis_info info;
    stb_vorbis* stb;
    void* buf;
} LFile;

SGenum SG_EXPORT sgmAudioFileCreate(void** file, SGStream* stream, SGuint* channels, SGuint* format, SGuint* frequency)
{
    if(!stream || !stream->read || !stream->seek || !stream->tell)
        return SG_INVALID_VALUE;

    *file = malloc(sizeof(LFile));
    if(!*file) return SG_UNKNOWN_ERROR;
    LFile* lfile = *file;

    SGlong pos;
    SGlong size;

    pos = stream->tell(stream->data);
    if(pos < 0)
        goto err;

    stream->seek(stream->data, 0, SG_SEEK_END);
    size = stream->tell(stream->data);
    stream->seek(stream->data, pos, SG_SEEK_SET);
    // "size < pos" is a sanity test
    if(size < 0 || size < pos)
        goto err;
    size -= pos;

    lfile->buf = malloc(size);
    if(stream->read(stream->data, lfile->buf, 1, size) != size)
        goto err;

    int error = 0;
    lfile->stb = stb_vorbis_open_memory(lfile->buf, size, &error, NULL);
    if(!lfile->stb)
        goto err;

    lfile->info = stb_vorbis_get_info(lfile->stb);
    *channels = lfile->info.channels;
    *frequency = lfile->info.sample_rate;
    *format = FORMAT_TYPE;

    return SG_OK;
err:
    free(*file);
    return SG_UNKNOWN_ERROR;
}
SGenum SG_EXPORT sgmAudioFileDestroy(void* file)
{
    LFile* lfile = file;
    stb_vorbis_close(lfile->stb);
    free(lfile->buf);
    free(lfile);
    return SG_OK;
}
SGenum SG_EXPORT sgmAudioFileNumSamples(void* file, SGuint* samples)
{
    LFile* lfile = file;
    *samples = stb_vorbis_stream_length_in_samples(lfile->stb);
    return SG_OK;
}
SGenum SG_EXPORT sgmAudioFileRead(void* file, void* data, SGuint* datalen)
{
    LFile* lfile = file;

#if FORMAT_TYPE == SG_AUDIO_FORMAT_S16
    *datalen = FORMAT_SIZE * stb_vorbis_get_samples_short_interleaved(lfile->stb, lfile->info.channels, data, *datalen / FORMAT_SIZE);
#elif FORMAT_TYPE == SG_AUDIO_FORMAT_F
    *datalen = FORMAT_SIZE * stb_vorbis_get_samples_float_interleaved(lfile->stb, lfile->info.channels, data, *datalen / FORMAT_SIZE);
#else
#error "Unknown format type"
#endif /* FORMAT_TYPE */

    /*SGuint num = *datalen / lfile->size;
    switch(lfile->format)
    {
        case SG_AUDIO_FORMAT_S16:
            *datalen = lfile->size * sf_read_short(lfile->snd, (SGshort*)data, num);
            break;
        case SG_AUDIO_FORMAT_S32:
            *datalen = lfile->size * sf_read_int(lfile->snd, (SGint*)data, num);
            break;
        case SG_AUDIO_FORMAT_F:
            *datalen = lfile->size * sf_read_float(lfile->snd, (SGfloat*)data, num);
            break;
        case SG_AUDIO_FORMAT_D:
            *datalen = lfile->size * sf_read_double(lfile->snd, (SGdouble*)data, num);
            break;
        default:
            sf_close(lfile->snd);
            return SG_UNKNOWN_ERROR;
    }*/
    return SG_OK;
}
