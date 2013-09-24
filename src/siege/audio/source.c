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
#include <siege/audio/source.h>
#include <siege/util/list.h> // plist

#include <stdlib.h>
#include <math.h>

#include <al.h>
#include <alc.h>

static ALCdevice* audioDev;
static ALCcontext* audioCtx;

#define ALSRCD(x)   (*(ALuint*)(x)->handle)
#define ALSRC(x)    ALSRCD((x)->dispatch)

static ALint queryi(ALuint source, ALenum q)
{
    ALint ret;
    alGetSourcei(source, q, &ret);
    return ret;
}
static float queryf(ALuint source, ALenum q)
{
    float ret;
    alGetSourcef(source, q, &ret);
    return ret;
}
static ALint state(ALuint source)
{
    return queryi(source, AL_SOURCE_STATE);
}

static SGuint maxSources(void)
{
    alGetError();
    ALuint threshold = 256;

    ALuint max;
    ALuint* buf = malloc(threshold * sizeof(ALuint));
    for(max = 1; max <= threshold; max++)
    {
        alGenSources(max, buf);
        if(alGetError() != AL_NO_ERROR)
        {
            max--;
            break;
        }
        alDeleteSources(max, buf);
    }
    return max;
}

SGbool SG_CALL _sgAudioSourceInit(void)
{
    audioDev = alcOpenDevice(NULL);
    audioCtx = alcCreateContext(audioDev, NULL);
    alcMakeContextCurrent(audioCtx);

    _sg_srcDisLength = maxSources();
    _sg_srcDisList = malloc(_sg_srcDisLength * sizeof(SGAudioSourceDispatch));

    SGuint i;
    for(i = 0; i < _sg_srcDisLength; i++)
    {
        _sg_srcDisList[i].source = NULL;
        _sg_srcDisList[i].handle = malloc(sizeof(ALuint));
        alGenSources(1, _sg_srcDisList[i].handle);
    }

    _sg_srcDestroy = sgListCreate();

    return SG_TRUE;
}
SGbool SG_CALL _sgAudioSourceDeinit(void)
{
    while(_sg_srcDestroy->head)
        sgAudioSourceDestroy(sgListPopFirst(_sg_srcDestroy));
    sgListDestroy(_sg_srcDestroy);

    SGuint i;
    for(i = 0; i <_sg_srcDisLength; i++)
    {
        alDeleteSources(1, _sg_srcDisList[i].handle);
        free(_sg_srcDisList[i].handle);
    }
    free(_sg_srcDisList);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(audioCtx);
    alcCloseDevice(audioDev);

    return SG_TRUE;
}

SGAudioSourceDispatch* SG_CALL _sgAudioSourceGetFreeDispatch(SGAudioSource* source)
{
    SGlong mini = -1;
    float minf = HUGE_VAL;

    SGlong blanki = -1;
    SGuint processed;
    SGuint queued;

    SGlong i;
    for(i = 0; i <_sg_srcDisLength; i++)
    {
        if(_sg_srcDisList[i].source == NULL)
        {
            _sg_srcDisList[i].source = source;
            return &_sg_srcDisList[i];
        }
        processed = queryi(ALSRCD(&_sg_srcDisList[i]), AL_BUFFERS_PROCESSED);
        queued = queryi(ALSRCD(&_sg_srcDisList[i]), AL_BUFFERS_QUEUED);
        if(processed == queued)
            blanki = i;
        if(_sg_srcDisList[i].source->priority < minf)
        {
            mini = i;
            minf = _sg_srcDisList[i].source->priority;
        }
    }

    // failed to find, so now we revert to used ones
    if((blanki >= 0) || (mini >= 0))
    {
        if(blanki >= 0)
            i = blanki; // try to use a source that's finished playing
        else if(mini >= 0)
            i = mini; // all sources playing, so try to find one with a smaller priority

        _sg_srcDisList[i].source->dispatch = NULL;
        _sg_srcDisList[i].source = source;
        return &_sg_srcDisList[i];
    }

    // nothing found, so give up
    return NULL;
}

SGAudioSource* SG_CALL sgAudioSourceCreate(float priority, float volume, float pitch, SGbool looping)
{
    SGListNode* node;
    SGListNode* next;
    for(node = _sg_srcDestroy->head; node; node = next)
    {
        next = node->next;
        if(!sgAudioSourceIsPlaying(node->item))
        {
            sgAudioSourceDestroy(node->item);
            sgListRemoveNode(_sg_srcDestroy, node);
        }
    }

    SGAudioSource* source = malloc(sizeof(SGAudioSource));
    source->priority = priority;

    source->dispatch = _sgAudioSourceGetFreeDispatch(source);
    // todo: enqueue?
    if(source->dispatch == NULL)
    {
        free(source);
        return NULL;
    }

    sgAudioSourceSetVolume(source, volume);
    sgAudioSourceSetPitch(source, pitch);
    sgAudioSourceSetLooping(source, looping);

    return source;
}
void SG_CALL sgAudioSourceDestroy(SGAudioSource* source)
{
    if(source == NULL)
        return;

    sgAudioSourceUnqueueBuffers(source, sgAudioSourceGetNumQueuedBuffers(source));

    // tell dispatch that the source is available
    if(source->dispatch != NULL)
        source->dispatch->source = NULL;
    free(source);
}
void SG_CALL sgAudioSourceDestroyLazy(SGAudioSource* source)
{
    sgAudioSourceSetLooping(source, SG_FALSE);
    sgListAppend(_sg_srcDestroy, source);
}

void SG_CALL sgAudioSourcePlay(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourcePlay(ALSRC(source));
}
SGbool SG_CALL sgAudioSourceIsPlaying(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    return state(ALSRC(source)) == AL_PLAYING;
}
void SG_CALL sgAudioSourcePause(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourcePause(ALSRC(source));
}
SGbool SG_CALL sgAudioSourceIsPaused(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    return state(ALSRC(source)) == AL_PAUSED;
}
void SG_CALL sgAudioSourceRewind(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourceRewind(ALSRC(source));
}
/*SGbool SG_CALL sgAudioSourceIsRewinded(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool rewinded = SG_FALSE;
    if(psgmAudioSourceIsRewinded != NULL)
        psgmAudioSourceIsRewinded(source->dispatch->handle, &rewinded);
    return rewinded;
}*/
void SG_CALL sgAudioSourceStop(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourceStop(ALSRC(source));
}
SGbool SG_CALL sgAudioSourceIsStopped(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    return state(ALSRC(source)) == AL_STOPPED;
}
SGbool SG_CALL sgAudioSourceIsActive(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGuint processed = sgAudioSourceGetNumProcessedBuffers(source);
    SGuint queued = sgAudioSourceGetNumQueuedBuffers(source);

    return processed != queued;
}

size_t SG_CALL sgAudioSourceGetNumProcessedBuffers(SGAudioSource* source)
{
    if(source == NULL)
        return 0;
    if(source->dispatch == NULL)
        return 0;

    return queryi(ALSRC(source), AL_BUFFERS_PROCESSED);
}
size_t SG_CALL sgAudioSourceGetNumQueuedBuffers(SGAudioSource* source)
{
    if(source == NULL)
        return 0;
    if(source->dispatch == NULL)
        return 0;

    return queryi(ALSRC(source), AL_BUFFERS_QUEUED);
}

void SG_CALL sgAudioSourceQueueBuffers(SGAudioSource* source, SGAudioBuffer** buffers, size_t numbuffers)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    size_t i;
    for(i = 0; i < numbuffers; i++)
        sgAudioSourceQueueBuffer(source, buffers[i]);
}
void SG_CALL sgAudioSourceQueueBuffer(SGAudioSource* source, SGAudioBuffer* buffer)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourceQueueBuffers(ALSRC(source), 1, buffer->handle);
}
void SG_CALL sgAudioSourceUnqueueBuffer(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    ALuint dummy;
    alSourceUnqueueBuffers(ALSRC(source), 1, &dummy);
}
void SG_CALL sgAudioSourceUnqueueBuffers(SGAudioSource* source, size_t numbuffers)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    ALuint* dummies = malloc(numbuffers * sizeof(ALuint));
    alSourceUnqueueBuffers(ALSRC(source), numbuffers, dummies);
    free(dummies);
}

void SG_CALL sgAudioSourceSetPosition3f(SGAudioSource* source, float x, float y, float z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSource3f(ALSRC(source), AL_POSITION, x, y, z);
}
void SG_CALL sgAudioSourceSetPosition2f(SGAudioSource* source, float x, float y)
{
    sgAudioSourceSetPosition3f(source, x, y, 0.0f);
}
void SG_CALL sgAudioSourceGetPosition3f(SGAudioSource* source, float* x, float* y, float* z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    float tmp;
    if(!x) x = &tmp;
    if(!y) y = &tmp;
    if(!z) z = &tmp;

    alGetSource3f(ALSRC(source), AL_POSITION, x, y, z);
}
void SG_CALL sgAudioSourceGetPosition2f(SGAudioSource* source, float* x, float* y)
{
    sgAudioSourceGetPosition3f(source, x, y, NULL);
}

void SG_CALL sgAudioSourceSetVelocity3f(SGAudioSource* source, float x, float y, float z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSource3f(ALSRC(source), AL_VELOCITY, x, y, z);
}
void SG_CALL sgAudioSourceSetVelocity2f(SGAudioSource* source, float x, float y)
{
    sgAudioSourceSetVelocity3f(source, x, y, 0.0f);
}
void SG_CALL sgAudioSourceGetVelocity3f(SGAudioSource* source, float* x, float* y, float* z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    float tmp;
    if(!x) x = &tmp;
    if(!y) y = &tmp;
    if(!z) z = &tmp;

    alGetSource3f(ALSRC(source), AL_VELOCITY, x, y, z);
}
void SG_CALL sgAudioSourceGetVelocity2f(SGAudioSource* source, float* x, float* y)
{
    sgAudioSourceGetVelocity3f(source, x, y, NULL);
}

//void SG_CALL sgAudioSourceSetFalloff(SGAudioSource* source, float falloff);
//float SG_CALL sgAudioSourceGetFalloff(SGAudioSource* source);

void SG_CALL sgAudioSourceSetPitch(SGAudioSource* source, float pitch)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourcef(ALSRC(source), AL_PITCH, pitch);
}
float SG_CALL sgAudioSourceGetPitch(SGAudioSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    return queryf(ALSRC(source), AL_PITCH);
}

void SG_CALL sgAudioSourceSetVolume(SGAudioSource* source, float volume)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourcef(ALSRC(source), AL_GAIN, volume);
}
float SG_CALL sgAudioSourceGetVolume(SGAudioSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    return queryf(ALSRC(source), AL_GAIN);
}

void SG_CALL sgAudioSourceSetLooping(SGAudioSource* source, SGbool looping)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    alSourcei(ALSRC(source), AL_LOOPING, looping);
}
SGbool SG_CALL sgAudioSourceGetLooping(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    return queryi(ALSRC(source), AL_LOOPING) != 0;
}
