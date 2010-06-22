#include "main.h"
#include "source.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgmAudioSourceMaxSources(SGuint* max)
{
    if(max == NULL)
        return SG_OK; // SG_INVALID_VALUE
    alGetError();
    ALuint threshold = 65536;

    ALuint* buf = malloc(threshold * sizeof(ALuint));
    for(*max = 1; *max <= threshold; (*max)++)
    {
        alGenBuffers(*max, buf);
        if(alGetError() != AL_NO_ERROR)
        {
            (*max)--;
            break;
        }
        alDeleteBuffers(*max, buf);
    }
    free(buf);
    return SG_OK;
}

SGuint SG_EXPORT sgmAudioSourceCreate(void** source)
{
    alGenSources(1, (ALuint*)source);
    return SG_OK;
}
/*SGuint SG_EXPORT sgmAudioSourceCreateData(void** source, void* buffer, float pitch, float gain, SGbool looping)
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
SGuint SG_EXPORT sgmAudioSourceDestroy(void* source)
{
    alDeleteSources(1, (ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourcePlay(void* source)
{
    alSourcePlay(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceIsPlaying(void* source, SGbool* playing)
{
    *playing = state(*(ALuint*)&source) == AL_PLAYING;
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourcePause(void* source)
{
    alSourcePause(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceIsPaused(void* source, SGbool* paused)
{
    *paused = state(*(ALuint*)&source) == AL_PAUSED;
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceRewind(void* source)
{
    alSourceRewind(*(ALuint*)&source);
    return SG_OK;
}
/*SGuint SG_EXPORT sgmAudioSourceIsRewinded(void* source, SGbool* rewinded)
{
    *rewinded = state(source) == AL_REWINDED;
    return SG_OK;
}*/
SGuint SG_EXPORT sgmAudioSourceStop(void* source)
{
    alSourceStop(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceIsStopped(void* source, SGbool* stopped)
{
    *stopped = state(*(ALuint*)&source) == AL_STOPPED;
    return SG_OK;
}
/*SGuint SG_EXPORT sgmAudioSourceSetBuffer(void* source, void* buffer)
{
    alSourcei(*(ALuint*)&source, AL_BUFFER, *(ALuint*)&buffer);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetBuffer(void* source, void** buffer)
{
    return SG_OK;
}*/
SGuint SG_EXPORT sgmAudioSourceQueueBuffers(void* source, void** buffers, SGuint numbuffers)
{
    ALuint* arr = malloc(numbuffers * sizeof(ALuint));
    size_t i;
    for(i = 0; i < numbuffers; i++)
        arr[i] = *(ALuint*)&buffers[i];
    alSourceQueueBuffers(*(ALuint*)&source, numbuffers, arr);
    free(arr);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceUnqueueBuffers(void* source, SGuint numbuffers)
{
    ALuint* arr = malloc(numbuffers * sizeof(ALuint));
    alSourceUnqueueBuffers(*(ALuint*)&source, numbuffers, arr);
    free(arr);
    return SG_OK;
}
SGuint sgAudioSourceGetNumProcessedBuffers(void* source, SGuint* processed)
{
    ALuint p;
    alGetSourcei(*(ALuint*)&source, AL_BUFFERS_PROCESSED, &p);
    *processed = p;
    return SG_OK;
}
SGuint sgAudioSourceGetNumQueuedBuffers(void* source, SGuint* queued)
{
    ALuint q;
    alGetSourcei(*(ALuint*)&source, AL_BUFFERS_QUEUED, &q);
    *queued = q;
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceSetPosition(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)&source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetPosition(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)&source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceSetVelocity(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)&source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetVelocity(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)&source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
/*SGuint SG_EXPORT sgmAudioSourceSetFalloff(void* source, float falloff)
{
    alSourcef(*(ALuint*)&source, AL_GAIN, falloff);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetFalloff(void* source, float* falloff)
{
    alGetSourcef(*(ALuint*)&source, AL_GAIN, falloff);
    return SG_OK;
}*/
SGuint SG_EXPORT sgmAudioSourceSetPitch(void* source, float pitch)
{
    alSourcef(*(ALuint*)&source, AL_PITCH, pitch);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetPitch(void* source, float* pitch)
{
    alGetSourcef(*(ALuint*)&source, AL_PITCH, pitch);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceSetVolume(void* source, float volume)
{
    alSourcef(*(ALuint*)&source, AL_GAIN, volume);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetVolume(void* source, float* volume)
{
    alGetSourcef(*(ALuint*)&source, AL_GAIN, volume);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceSetLooping(void* source, SGbool looping)
{
    alSourcei(*(ALuint*)&source, AL_LOOPING, looping);
    return SG_OK;
}
SGuint SG_EXPORT sgmAudioSourceGetLooping(void* source, SGbool* looping)
{
    ALint allooping;
    alGetSourcei(*(ALuint*)&source, AL_LOOPING, &allooping);
    *looping = allooping;
    return SG_OK;
}
