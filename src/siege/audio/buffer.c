/*
    Copyright (c) 2007 SIEGE Development Team
    All rights reserved.

    This file is part of libSIEGE.

    This software is copyrighted work licensed under the terms of the
    2-clause BSD license. Please consult the file "license.txt" for
    details.

    If you did not recieve the file with this program, please email
    Tim Chas <darkuranium@gmail.com>.
*/

#define SG_BUILD_LIBRARY
#include <siege/audio/buffer.h>
#include <siege/modules/audio.h>

#include <stdlib.h>

SGbool SG_EXPORT _sgAudioBufferInit(void)
{
    return SG_TRUE;
}
SGbool SG_EXPORT _sgAudioBufferDeinit(void)
{
    return SG_TRUE;
}

SGAudioBuffer* SG_EXPORT sgAudioBufferCreate(const char* fname)
{
    SGAudioBuffer* buffer = malloc(sizeof(SGAudioBuffer));

    if(_sg_modAudio.sgmAudioBufferCreate != NULL)
        _sg_modAudio.sgmAudioBufferCreate(&buffer->handle);

    SGuint channels = 0;
    SGuint format = 0;
    SGuint frequency = 0;
    void* data = NULL;
    SGuint datalen = 0;
    if(_sg_modAudio.sgmAudioLoadFile != NULL)
        _sg_modAudio.sgmAudioLoadFile(fname, &channels, &format, &frequency, &data, &datalen);
    if(_sg_modAudio.sgmAudioBufferSetData != NULL)
        _sg_modAudio.sgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
    if(_sg_modAudio.sgmAudioLoadFreeData != NULL)
        _sg_modAudio.sgmAudioLoadFreeData(data);

    return buffer;
}
void SG_EXPORT sgAudioBufferDestroy(SGAudioBuffer* buffer)
{
    if(buffer == NULL)
        return;

    if(_sg_modAudio.sgmAudioBufferDestroy != NULL)
        _sg_modAudio.sgmAudioBufferDestroy(buffer->handle);
    free(buffer);
}

void SG_EXPORT sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
{
    if(buffer == NULL)
        return;
    if(_sg_modAudio.sgmAudioBufferSetData != NULL)
        _sg_modAudio.sgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
}
