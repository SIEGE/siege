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

#include <stdlib.h>
#include <string.h>

#include <al.h>
#include <alc.h>

#include "../internal/stb/stb_vorbis.h"

// TODO: Streaming audio, proper error handling for loading
#define ALBUF(x) (*(ALuint*)(x)->handle)

// TODO: Move this to an util library; clean it up.
static void* toStereo(SGuint channels, void* data, SGuint* datalen, ALuint* alformat)
{
    void* odata = data;
    if(channels == 2)
    {
        if(*alformat == AL_FORMAT_MONO8)
            *alformat = AL_FORMAT_STEREO8;
        else
            *alformat = AL_FORMAT_STEREO16;
    }
    else if(channels > 2)
    {
        SGuint chan;
        SGuint i;
        long double sum1;
        long double sum2;
        int num1;
        int num2;
        if(*alformat == AL_FORMAT_MONO8)
        {
            odata = malloc(*datalen * sizeof(SGubyte));
            memcpy(odata, data, *datalen * sizeof(SGubyte));

            *alformat = AL_FORMAT_STEREO8;
            SGubyte* bdata = (SGubyte*) odata;

            for(i = 0; i < *datalen; i += channels)
            {
                sum1 = 0;
                num1 = 0;
                sum2 = 0;
                num2 = 0;

                if(channels % 2 != 0)
                {
                    chan = 1;
                    sum1 += bdata[i / channels] * 0.5L; // 1/2 because we put this on both chans
                    num1++;
                    sum2 += bdata[i / channels] * 0.5L;
                    num2++;
                }
                else
                    chan = 0;
                for(; chan < channels; chan++)
                {
                    if(chan % 2 == 0)
                    {
                        sum1 += bdata[i + chan];
                        num1++;
                    }
                    else
                    {
                        sum2 += bdata[i + chan];
                        num2++;
                    }
                }
                bdata[i / channels    ] = (SGubyte)(sum1 / num1);
                bdata[i / channels + 1] = (SGubyte)(sum2 / num2);
            }
        }
        else
        {
            odata = malloc(*datalen * sizeof(SGushort));
            memcpy(odata, data, *datalen * sizeof(SGushort));

            *alformat = AL_FORMAT_STEREO16;
            SGshort* sdata = (SGshort*) odata;

            for(i = 0; i < *datalen / 2; i += channels)
            {
                sum1 = 0;
                num1 = 0;
                sum2 = 0;
                num2 = 0;

                if(channels % 2 != 0)
                {
                    chan = 1;
                    sum1 += sdata[i / channels] * 0.5L; // 1/2 because we put this on both chans
                    num1++;
                    sum2 += sdata[i / channels] * 0.5L;
                    num2++;
                }
                else
                    chan = 0;
                for(; chan < channels; chan++)
                {
                    if(chan % 2 == 0)
                    {
                        sum1 += sdata[i + chan];
                        num1++;
                    }
                    else
                    {
                        sum2 += sdata[i + chan];
                        num2++;
                    }
                }
                sdata[i / channels    ] = (SGushort)(sum1 / num1);
                sdata[i / channels + 1] = (SGushort)(sum2 / num2);
            }
        }
        *datalen = *datalen / channels * 2;
    }
    return odata;
}

SGAudioBuffer* SG_CALL sgAudioBufferCreateStream(SGStream* stream, SGbool delstream)
{
    SGAudioBuffer* buffer = malloc(sizeof(SGAudioBuffer));

    buffer->stream = stream;
    buffer->del = delstream;

    buffer->handle = malloc(sizeof(ALuint));
    alGenBuffers(1, buffer->handle);

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

    sgAudioBufferSetData(buffer, channels, format, frequency, data, datalen);
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

    alDeleteBuffers(1, buffer->handle);
    free(buffer->handle);
    if(buffer->del)
        sgStreamDestroy(buffer->stream);
    free(buffer);
}

void SG_CALL sgAudioBufferSetData(SGAudioBuffer* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, size_t datalen)
{
    //AL_FORMAT_[MONO, STEREO][8, 16]
    ALuint alformat;

    SGuint i;
    SGubyte* bdata = (SGubyte*)data;
    SGshort* scur;
    SGint* icur;
    SGfloat* fcur;
    SGdouble* dcur;
    switch(format)
    {
        case SG_AUDIO_FORMAT_S8:
            alformat = AL_FORMAT_MONO8;
            for(i = 0; i < datalen; i++)
                bdata[i] = bdata[i] + 0x80;
            break;
        case SG_AUDIO_FORMAT_S16:
            alformat = AL_FORMAT_MONO16;
            break;
        case SG_AUDIO_FORMAT_S24:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 3)
            {
                icur = (SGint*)&bdata[i];
                scur = (SGshort*)&bdata[i / 3 * 2];
                *scur = (SGshort)((*icur >> 8) / 256.0L);
            }
            datalen = datalen / 3 * 2;
            break;
        case SG_AUDIO_FORMAT_S32:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 4)
            {
                icur = (SGint*)&bdata[i];
                scur = (SGshort*)&bdata[i / 4 * 2];
                *scur = (SGshort)(*icur / 65536.0L);
            }
            datalen = datalen / 4 * 2;
            break;

        case SG_AUDIO_FORMAT_U8:
            alformat = AL_FORMAT_MONO8;
            break;
        case SG_AUDIO_FORMAT_U16:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 2)
            {
                scur = (SGshort*)&bdata[i];
                *scur = *scur - 0x7FFF;
            }
            break;
        case SG_AUDIO_FORMAT_U24:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 3)
            {
                icur = (SGint*)&bdata[i];
                scur = (SGshort*)&bdata[i / 3 * 2];
                *scur = (SGshort)((*icur >> 8) / 256.0L) - 0x7FFF;
            }
            datalen = datalen / 3 * 2;
            break;
        case SG_AUDIO_FORMAT_U32:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 4)
            {
                icur = (SGint*)&bdata[i];
                scur = (SGshort*)&bdata[i / 4 * 2];
                *scur = (SGshort)(*icur / 65536.0L) - 0x7FFF;
            }
            datalen = datalen / 4 * 2;
            break;

        case SG_AUDIO_FORMAT_F:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 4)
            {
                fcur = (SGfloat*)&bdata[i];
                scur = (SGshort*)&bdata[i / 4 * 2];
                *scur = (SGshort)(*fcur * 0xFFFF);
            }
            datalen = datalen / 4 * 2;
            break;
        case SG_AUDIO_FORMAT_D:
            alformat = AL_FORMAT_MONO16;
            for(i = 0; i < datalen; i += 8)
            {
                dcur = (SGdouble*)&bdata[i];
                scur = (SGshort*)&bdata[i / 8 * 2];
                *scur = (SGshort)(*dcur * 0xFFFF);
            }
            datalen = datalen / 8 * 2;
            break;
        default:
            return; // ERROR
    }
    void* odata = toStereo(channels, data, &datalen, &alformat);
    alBufferData(ALBUF(buffer), alformat, odata, datalen, frequency);
    if(data != odata)
        free(odata);
}
