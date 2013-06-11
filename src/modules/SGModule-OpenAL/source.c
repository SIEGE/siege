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

static ALint state(ALuint source)
{
    ALint s;
    alGetSourcei(source, AL_SOURCE_STATE, &s);
    return s;
}

SGenum SG_CALL sgmAudioSourceMaxSources(SGuint* max)
{
    if(max == NULL)
        return SG_OK; // SG_INVALID_VALUE
    alGetError();
    ALuint threshold = 256;

    ALuint* buf = malloc(threshold * sizeof(ALuint));
    for(*max = 1; *max <= threshold; (*max)++)
    {
        alGenSources(*max, buf);
        if(alGetError() != AL_NO_ERROR)
        {
            (*max)--;
            break;
        }
        alDeleteSources(*max, buf);
    }
    free(buf);
    return SG_OK;
}

SGenum SG_CALL sgmAudioSourceCreate(void** source)
{
    *source = malloc(sizeof(ALuint));

    alGenSources(1, *source);

    return SG_OK;
}
/*SGenum SG_CALL sgmAudioSourceCreateData(void** source, void* buffer, float pitch, float gain, SGbool looping)
{
    SGuint ret;
    SGuint fret = SG_OK;
    ret = sgmAudioSourceCreate(source);
    if(ret != SG_OK)
        return ret;

    ret = sgmAudioSourceSetBuffer(*source, buffer);
    if(ret != SG_OK)
        fret = ret;
    ret = sgmAudioSourceSetPitch(*source, pitch);
    if(ret != SG_OK)
        fret = ret;
    ret = sgmAudioSourceSetVolume(*source, gain);
    if(ret != SG_OK)
        fret = ret;
    ret = sgmAudioSourceSetLooping(*source, looping);
    if(ret != SG_OK)
        fret = ret;
    return fret;
}*/
SGenum SG_CALL sgmAudioSourceDestroy(void* source)
{
    alDeleteSources(1, (ALuint*)source);
    free(source);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourcePlay(void* source)
{
    alSourcePlay(*(ALuint*)source);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceIsPlaying(void* source, SGbool* playing)
{
    *playing = state(*(ALuint*)source) == AL_PLAYING;
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourcePause(void* source)
{
    alSourcePause(*(ALuint*)source);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceIsPaused(void* source, SGbool* paused)
{
    *paused = state(*(ALuint*)source) == AL_PAUSED;
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceRewind(void* source)
{
    alSourceRewind(*(ALuint*)source);
    return SG_OK;
}
/*SGenum SG_CALL sgmAudioSourceIsRewinded(void* source, SGbool* rewinded)
{
    *rewinded = state(source) == AL_REWINDED;
    return SG_OK;
}*/
SGenum SG_CALL sgmAudioSourceStop(void* source)
{
    alSourceStop(*(ALuint*)source);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceIsStopped(void* source, SGbool* stopped)
{
    *stopped = state(*(ALuint*)source) == AL_STOPPED;
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceSetBuffer(void* source, void* buffer)
{
    alSourcei(*(ALuint*)source, AL_BUFFER, *(ALuint*)buffer);
    return SG_OK;
}
/*SGenum SG_CALL sgmAudioSourceGetBuffer(void* source, void** buffer)
{
    return SG_OK;
}*/
SGenum SG_CALL sgmAudioSourceQueueBuffers(void* source, void** buffers, SGuint numbuffers)
{
    ALuint* arr = malloc(numbuffers * sizeof(ALuint));
    size_t i;
    for(i = 0; i < numbuffers; i++)
        arr[i] = *(ALuint*)buffers[i];
    alSourceQueueBuffers(*(ALuint*)source, numbuffers, arr);
    free(arr);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceUnqueueBuffers(void* source, SGuint numbuffers)
{
    ALuint* arr = malloc(numbuffers * sizeof(ALuint));
    alSourceUnqueueBuffers(*(ALuint*)source, numbuffers, arr);
    free(arr);
    return SG_OK;
}
SGenum sgmAudioSourceGetNumProcessedBuffers(void* source, SGuint* processed)
{
    ALint p;
    alGetSourcei(*(ALuint*)source, AL_BUFFERS_PROCESSED, &p);
    *processed = p;
    return SG_OK;
}
SGenum sgmAudioSourceGetNumQueuedBuffers(void* source, SGuint* queued)
{
    ALint q;
    alGetSourcei(*(ALuint*)source, AL_BUFFERS_QUEUED, &q);
    *queued = q;
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceSetPosition(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetPosition(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceSetVelocity(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetVelocity(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
/*SGenum SG_CALL sgmAudioSourceSetFalloff(void* source, float falloff)
{
    alSourcef(*(ALuint*)&source, AL_GAIN, falloff);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetFalloff(void* source, float* falloff)
{
    alGetSourcef(*(ALuint*)&source, AL_GAIN, falloff);
    return SG_OK;
}*/
SGenum SG_CALL sgmAudioSourceSetPitch(void* source, float pitch)
{
    alSourcef(*(ALuint*)source, AL_PITCH, pitch);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetPitch(void* source, float* pitch)
{
    alGetSourcef(*(ALuint*)source, AL_PITCH, pitch);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceSetVolume(void* source, float volume)
{
    alSourcef(*(ALuint*)source, AL_GAIN, volume);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetVolume(void* source, float* volume)
{
    alGetSourcef(*(ALuint*)source, AL_GAIN, volume);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceSetLooping(void* source, SGbool looping)
{
    alSourcei(*(ALuint*)source, AL_LOOPING, looping);
    return SG_OK;
}
SGenum SG_CALL sgmAudioSourceGetLooping(void* source, SGbool* looping)
{
    ALint allooping;
    alGetSourcei(*(ALuint*)source, AL_LOOPING, &allooping);
    *looping = allooping;
    return SG_OK;
}
