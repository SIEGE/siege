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

SGuint SG_EXPORT sgmAudioFileCreate(void** file, const char* fname, SGuint* channels, SGuint* format, SGuint* frequency)
{
    LFile** lfile = (LFile**)file;
    *lfile = malloc(sizeof(LFile));
    if(*lfile == NULL)
        return SG_UNKNOWN_ERROR;

    memset(&(*lfile)->info, 0, sizeof(SF_INFO));
    (*lfile)->snd = sf_open(fname, SFM_READ, &(*lfile)->info);
    if((*lfile)->snd == NULL)
        return SG_UNKNOWN_ERROR;

    switch((*lfile)->info.format & SF_FORMAT_SUBMASK)
    {
        case SF_FORMAT_FLOAT:
            (*lfile)->format = SG_AUDIO_FORMAT_F;
            (*lfile)->size = 4;
            break;
        case SF_FORMAT_DOUBLE:
            (*lfile)->format = SG_AUDIO_FORMAT_D;
            (*lfile)->size = 8;
            break;
        case SF_FORMAT_PCM_S8:
        case SF_FORMAT_PCM_16:
        case SF_FORMAT_PCM_U8:
            (*lfile)->format = SG_AUDIO_FORMAT_S16;
            (*lfile)->size = 2;
            break;
        case SF_FORMAT_PCM_24:
        case SF_FORMAT_PCM_32:
        default:
            (*lfile)->format = SG_AUDIO_FORMAT_S32;
            (*lfile)->size = 4;
    }

    *format = (*lfile)->format;
    *channels = (*lfile)->info.channels;
    *frequency = (*lfile)->info.samplerate;
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioFileDestroy(void* file)
{
    LFile* lfile = (LFile*)file;

    if(sf_close(lfile->snd) != 0)
        return SG_UNKNOWN_ERROR;
    free(file);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioFileNumSamples(void* file, SGuint* samples)
{
    LFile* lfile = (LFile*)file;
    *samples = lfile->info.frames;
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioFileRead(void* file, void* data, SGuint* datalen)
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
