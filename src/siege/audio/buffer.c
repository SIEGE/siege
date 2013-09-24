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

#define SG_BUILD_LIBRARY
#include <siege/audio/buffer.h>
#include <siege/modules/audio.h>

#include <stdlib.h>

#include "../internal/stb/stb_vorbis.h"

// TODO: Streaming audio, proper error handling for loading

SGAudioBuffer* SG_CALL sgAudioBufferCreateStream(SGStream* stream, SGbool delstream)
{
    SGAudioBuffer* buffer = malloc(sizeof(SGAudioBuffer));

    buffer->stream = stream;
    buffer->del = delstream;

    if(psgmAudioBufferCreate != NULL)
        psgmAudioBufferCreate(&buffer->handle);

    SGuint channels;
    SGuint format;
    SGuint frequency;
    void* data = NULL;
    SGuint datalen;
    SGuint nsamples;

    void* buf = NULL;
    int error = 0;
    stb_vorbis* stb = NULL;
    stb_vorbis_info info;

    if(!stream || !stream->read || !stream->seek || !stream->tell)
        return NULL;

    SGlong pos;
    SGlong size;

    pos = stream->tell(stream->data);
    if(pos < 0) goto lderr;

    stream->seek(stream->data, 0, SG_SEEK_END);
    size = stream->tell(stream->data);
    stream->seek(stream->data, pos, SG_SEEK_SET);
    if(size < 0) goto lderr;
    size -= pos;

    buf = malloc(size);
    if(stream->read(stream->data, buf, 1, size) != size)
        goto lderr;

    stb = stb_vorbis_open_memory(buf, size, &error, NULL);
    if(!stb) goto lderr;

    info = stb_vorbis_get_info(stb);
    channels = info.channels;
    frequency = info.sample_rate;
    format = SG_AUDIO_FORMAT_S16; // or SG_AUDIO_FORMAT_F

    nsamples = stb_vorbis_stream_length_in_samples(stb);
    datalen = 2 * nsamples * channels;
    data = malloc(datalen);

    datalen = 2 * stb_vorbis_get_samples_short_interleaved(stb, info.channels, data, datalen / 2);

    if(psgmAudioBufferSetData != NULL)
        psgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
    free(data);

lderr:
    if(stb)
        stb_vorbis_close(stb);
    if(buf)
        free(buf);

    return buffer;
}
SGAudioBuffer* SG_CALL sgAudioBufferCreateFile(const char* fname)
{
    return sgAudioBufferCreateStream(sgStreamCreateFile(fname, "r"), SG_TRUE);
}
void SG_CALL sgAudioBufferDestroy(SGAudioBuffer* buffer)
{
    if(buffer == NULL)
        return;

    if(psgmAudioBufferDestroy != NULL)
        psgmAudioBufferDestroy(buffer->handle);
    if(buffer->del)
        sgStreamDestroy(buffer->stream);
    free(buffer);
}

void SG_CALL sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen)
{
    if(buffer == NULL)
        return;
    if(psgmAudioBufferSetData != NULL)
        psgmAudioBufferSetData(buffer->handle, channels, format, frequency, data, datalen);
}
