#include "main.h"
#include "sample.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgAudioSampleCreate(void** source)
{
    alGenBuffers(1, (ALuint*)source);
    return SG_OK;
}

SGuint SG_EXPORT sgAudioSampleDestroy(void* source)
{
    alDeleteBuffers(1, (ALuint*)&source);
    return SG_OK;
}

void* toStereo(SGuint channels, void* data, SGuint* datalen, ALuint* alformat)
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

SGuint SG_EXPORT sgAudioSampleSetData(void* source, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
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
    alBufferData(*(ALuint*)&source, alformat, data, datalen, frequency);
    return SG_OK;
}
//SGuint SG_EXPORT sgAudioSampleGetData(void* sample, SGuint* channels, SGuint* format, SGuint* frequency, SGPointer* data, SGuint* datalen);
/*SGuint SG_EXPORT sgAudioSampleCreateData(void** source, SGuint channels, SGuint format, SGuint frequency, void* data, SGuint datalen)
{
    SGuint ret = sgAudioSampleCreate(source);
    if(ret != SG_OK)
        return ret;
    return sgAudioSampleData(*info, channels, type, frequency, data, datalen);
}*/
