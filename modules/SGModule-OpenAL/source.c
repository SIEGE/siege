#include "main.h"
#include "source.h"

#include <stdio.h>
#include <stdlib.h>

SGuint SG_EXPORT sgAudioSourceCreate(void** source)
{
    alGenSources(1, (ALuint*)source);
    return SG_OK;
}
/*SGuint SG_EXPORT sgAudioSourceCreateData(void** source, void* sample, float pitch, float gain, SGbool looping)
{
    SGuint ret;
    SGuint fret = SG_OK;
    ret = sgAudioSourceCreate(source);
    if(ret != SG_OK)
        return ret;

    ret = sgAudioSourceSetSample(*source, sample);
    if(ret != SG_OK)
        fret = ret;
    ret = sgAudioSourceSetPitch(*source, pitch);
    if(ret != SG_OK)
        fret = ret;
    ret = sgAudioSourceSetGain(*source, gain);
    if(ret != SG_OK)
        fret = ret;
    ret = sgAudioSourceSetLooping(*source, looping);
    if(ret != SG_OK)
        fret = ret;
    return fret;
}*/
SGuint SG_EXPORT sgAudioSourceDestroy(void* source)
{
    alDeleteSources(1, (ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourcePlay(void* source)
{
    alSourcePlay(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceIsPlaying(void* source, SGbool* playing)
{
    *playing = state(*(ALuint*)&source) == AL_PLAYING;
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourcePause(void* source)
{
    alSourcePause(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceIsPaused(void* source, SGbool* paused)
{
    *paused = state(*(ALuint*)&source) == AL_PAUSED;
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceRewind(void* source)
{
    alSourceRewind(*(ALuint*)&source);
    return SG_OK;
}
/*SGuint SG_EXPORT sgAudioSourceIsRewinded(void* source, SGbool* rewinded)
{
    *rewinded = state(source) == AL_REWINDED;
    return SG_OK;
}*/
SGuint SG_EXPORT sgAudioSourceStop(void* source)
{
    alSourceStop(*(ALuint*)&source);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceIsStopped(void* source, SGbool* stopped)
{
    *stopped = state(*(ALuint*)&source) == AL_STOPPED;
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceSetSample(void* source, void* sample)
{
    alSourcei(*(ALuint*)&source, AL_BUFFER, *(ALuint*)&sample);
    return SG_OK;
}
/*SGuint SG_EXPORT sgAudioSourceGetSample(void* source, void** sample)
{
    //return SG_OK;
}*/
SGuint SG_EXPORT sgAudioSourceSetPosition(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)&source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceGetPosition(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)&source, AL_POSITION, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceSetVelocity(void* source, float x, float y, float z)
{
    alSource3f(*(ALuint*)&source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceGetVelocity(void* source, float* x, float* y, float* z)
{
    alGetSource3f(*(ALuint*)&source, AL_VELOCITY, x, y, z);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceSetPitch(void* source, float pitch)
{
    alSourcef(*(ALuint*)&source, AL_PITCH, pitch);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceGetPitch(void* source, float* pitch)
{
    alGetSourcef(*(ALuint*)&source, AL_PITCH, pitch);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceSetGain(void* source, float gain)
{
    alSourcef(*(ALuint*)&source, AL_GAIN, gain);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceGetGain(void* source, float* gain)
{
    alGetSourcef(*(ALuint*)&source, AL_GAIN, gain);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceSetLooping(void* source, SGbool looping)
{
    alSourcei(*(ALuint*)&source, AL_LOOPING, looping);
    return SG_OK;
}
SGuint SG_EXPORT sgAudioSourceGetLooping(void* source, SGbool* looping)
{
    ALint allooping;
    alGetSourcei(*(ALuint*)&source, AL_LOOPING, &allooping);
    *looping = allooping;
    return SG_OK;
}
