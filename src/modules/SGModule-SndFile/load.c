/*
 * Copyright (c) 2007 SIEGE Development Team
 * All rights reserved.
 *
 * This file is part of libSIEGE.
 *
 * This software is copyrighted work licensed under the terms of the
 * 2-clause BSD license. Please consult the file "license.txt" for
 * details.
 *
 * If you did not recieve the file with this program, please email
 * Tim Chas <darkuranium@gmail.com>.
 */

#include "main.h"
#include "load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sf_count_t vio_get_filelen(void* data)
{
    SGStream* stream = data;
    if(!stream->seek || !stream->tell) return -1;

    SGlong pos = stream->tell(stream->data);
    if(pos < 0) return -1;

    stream->seek(stream->data, 0, SG_SEEK_END);
    SGlong size = stream->tell(stream->data);
    stream->seek(stream->data, pos, SG_SEEK_SET);
    return size;
}
static sf_count_t vio_seek(sf_count_t offset, int whence, void* data)
{
    SGStream* stream = data;
    if(!stream->seek) return -1;

    SGenum swhence;
    switch(whence)
    {
        case SEEK_SET: swhence = SG_SEEK_SET; break;
        case SEEK_CUR: swhence = SG_SEEK_CUR; break;
        case SEEK_END: swhence = SG_SEEK_END; break;
        default: return -1;
    }

    SGbool ret = stream->seek(stream->data, offset, swhence);
    if(!ret) return -1;

    return stream->tell ? stream->tell(stream->data) : -1;
}
static sf_count_t vio_read(void* ptr, sf_count_t count, void* data)
{
    SGStream* stream = data;
    if(!stream->read) return 0;

    return stream->read(stream->data, ptr, 1, count);
}
static sf_count_t vio_write(const void* ptr, sf_count_t count, void* data)
{
    SGStream* stream = data;
    if(!stream->write) return 0;

    return stream->write(stream->data, ptr, 1, count);
}
static sf_count_t vio_tell(void* data)
{
    SGStream* stream = data;
    if(!stream->tell) return -1;

    return stream->tell(stream->data);
}

SGenum SG_EXPORT sgmAudioFileCreate(void** file, SGStream* stream, SGuint* channels, SGuint* format, SGuint* frequency)
{
    *file = malloc(sizeof(LFile));
    if(!*file) return SG_UNKNOWN_ERROR;
    LFile* lfile = *file;

    SF_VIRTUAL_IO* io = &lfile->io;
    io->get_filelen = vio_get_filelen;
    io->seek = vio_seek;
    io->read = vio_read;
    io->write = vio_write;
    io->tell = vio_tell;

    memset(&lfile->info, 0, sizeof(SF_INFO));
    lfile->snd = sf_open_virtual(&lfile->io, SFM_READ, &lfile->info, stream);
    if(lfile->snd == NULL)
        return SG_UNKNOWN_ERROR;

    switch(lfile->info.format & SF_FORMAT_SUBMASK)
    {
        case SF_FORMAT_FLOAT:
            lfile->format = SG_AUDIO_FORMAT_F;
            lfile->size = 4;
            break;
        case SF_FORMAT_DOUBLE:
            lfile->format = SG_AUDIO_FORMAT_D;
            lfile->size = 8;
            break;
        case SF_FORMAT_PCM_S8:
        case SF_FORMAT_PCM_16:
        case SF_FORMAT_PCM_U8:
            lfile->format = SG_AUDIO_FORMAT_S16;
            lfile->size = 2;
            break;
        case SF_FORMAT_PCM_24:
        case SF_FORMAT_PCM_32:
        default:
            lfile->format = SG_AUDIO_FORMAT_S32;
            lfile->size = 4;
    }

    *format = lfile->format;
    *channels = lfile->info.channels;
    *frequency = lfile->info.samplerate;
    return SG_OK;
}
SGenum SG_EXPORT sgmAudioFileDestroy(void* file)
{
    LFile* lfile = (LFile*)file;

    if(sf_close(lfile->snd) != 0)
        return SG_UNKNOWN_ERROR;
    free(file);
    return SG_OK;
}
SGenum SG_EXPORT sgmAudioFileNumSamples(void* file, SGuint* samples)
{
    LFile* lfile = (LFile*)file;
    *samples = lfile->info.frames;
    return SG_OK;
}
SGenum SG_EXPORT sgmAudioFileRead(void* file, void* data, SGuint* datalen)
{
    LFile* lfile = (LFile*)file;

    SGuint num = *datalen / lfile->size;
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
    }
    return SG_OK;
}
