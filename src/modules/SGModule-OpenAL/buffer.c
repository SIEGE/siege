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

SGenum SG_EXPORT sgmAudioBufferCreate(void** buffer)
{
    *buffer = malloc(sizeof(ALuint));

    alGenBuffers(1, *buffer);
    return SG_OK;
}

SGenum SG_EXPORT sgmAudioBufferDestroy(void* buffer)
{
    alDeleteBuffers(1, buffer);
    free(buffer);
    return SG_OK;
}

static void* toStereo(SGuint channels, void* data, SGuint* datalen, ALuint* alformat)
{
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
            *alformat = AL_FORMAT_STEREO8;
            SGubyte* bdata = (SGubyte*) data;

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
            *alformat = AL_FORMAT_STEREO16;
            SGshort* sdata = (SGshort*) data;

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
    return data;
}

SGenum SG_EXPORT sgmAudioBufferSetData(void* buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
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
    }
    data = toStereo(channels, data, &datalen, &alformat);
    alBufferData(*(ALuint*)buffer, alformat, data, datalen, frequency);
    return SG_OK;
}
//SGenum SG_EXPORT sgmAudioBufferGetData(void* buffer, SGuint* channels, SGuint* format, SGuint* frequency, SGPointer* data, SGuint* datalen);
/*SGenum SG_EXPORT sgmAudioBufferCreateData(void** buffer, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
{
    SGuint ret = sgmAudioBufferCreate(buffer);
    if(ret != SG_OK)
        return ret;
    return sgmAudioBufferData(*buffer, channels, type, frequency, data, datalen);
}*/
