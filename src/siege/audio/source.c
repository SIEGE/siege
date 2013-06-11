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
#include <siege/modules/audio.h>
#include <siege/util/list.h> // plist

#include <stdlib.h>
#include <math.h>

SGbool SG_CALL _sgAudioSourceInit(void)
{
    _sg_srcDisLength = 16;
    if(psgmAudioSourceMaxSources != NULL)
        psgmAudioSourceMaxSources(&_sg_srcDisLength);
    _sg_srcDisList = malloc(_sg_srcDisLength * sizeof(SGAudioSourceDispatch));

    SGuint i;
    for(i = 0; i < _sg_srcDisLength; i++)
    {
        _sg_srcDisList[i].source = NULL;
        if(psgmAudioSourceCreate != NULL)
            psgmAudioSourceCreate(&_sg_srcDisList[i].handle);
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
        if(psgmAudioSourceDestroy != NULL)
            psgmAudioSourceDestroy(_sg_srcDisList[i].handle);
    }

    free(_sg_srcDisList);

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
        if((psgmAudioSourceGetNumProcessedBuffers != NULL) && (psgmAudioSourceGetNumQueuedBuffers != NULL))
        {
            psgmAudioSourceGetNumProcessedBuffers(_sg_srcDisList[i].handle, &processed);
            psgmAudioSourceGetNumQueuedBuffers(_sg_srcDisList[i].handle, &queued);
            if(processed == queued)
                blanki = i;
        }
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

    if(psgmAudioSourcePlay != NULL)
        psgmAudioSourcePlay(source->dispatch->handle);
}
SGbool SG_CALL sgAudioSourceIsPlaying(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool playing = SG_FALSE;
    if(psgmAudioSourceIsPlaying != NULL)
        psgmAudioSourceIsPlaying(source->dispatch->handle, &playing);
    return playing;
}
void SG_CALL sgAudioSourcePause(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourcePause != NULL)
        psgmAudioSourcePause(source->dispatch->handle);
}
SGbool SG_CALL sgAudioSourceIsPaused(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool paused = SG_FALSE;
    if(psgmAudioSourceIsPaused != NULL)
        psgmAudioSourceIsPaused(source->dispatch->handle, &paused);
    return paused;
}
void SG_CALL sgAudioSourceRewind(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceRewind != NULL)
        psgmAudioSourceRewind(source->dispatch->handle);
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

    if(psgmAudioSourceStop != NULL)
        psgmAudioSourceStop(source->dispatch->handle);
}
SGbool SG_CALL sgAudioSourceIsStopped(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool stopped = SG_FALSE;
    if(psgmAudioSourceIsStopped != NULL)
        psgmAudioSourceIsStopped(source->dispatch->handle, &stopped);
    return stopped;
}
SGbool SG_CALL sgAudioSourceIsActive(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGuint processed = 0;
    SGuint queued = 0;
    if(psgmAudioSourceGetNumProcessedBuffers != NULL)
        psgmAudioSourceGetNumProcessedBuffers(source->dispatch->handle, &processed);
    if(psgmAudioSourceGetNumQueuedBuffers != NULL)
        psgmAudioSourceGetNumQueuedBuffers(source->dispatch->handle, &queued);

    return processed != queued;
}

size_t SG_CALL sgAudioSourceGetNumProcessedBuffers(SGAudioSource* source)
{
    if(source == NULL)
        return 0;
    if(source->dispatch == NULL)
        return 0;

    SGuint processed = 0;
    if(psgmAudioSourceGetNumProcessedBuffers)
        psgmAudioSourceGetNumProcessedBuffers(source->dispatch->handle, &processed);
    return processed;
}
size_t SG_CALL sgAudioSourceGetNumQueuedBuffers(SGAudioSource* source)
{
    if(source == NULL)
        return 0;
    if(source->dispatch == NULL)
        return 0;

    SGuint queued = 0;
    if(psgmAudioSourceGetNumQueuedBuffers)
        psgmAudioSourceGetNumQueuedBuffers(source->dispatch->handle, &queued);
    return queued;
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

    if(psgmAudioSourceQueueBuffers != NULL)
        psgmAudioSourceQueueBuffers(source->dispatch->handle, &buffer->handle, 1);
}
void SG_CALL sgAudioSourceUnqueueBuffer(SGAudioSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceUnqueueBuffers)
        psgmAudioSourceUnqueueBuffers(source->dispatch->handle, 1);
}
void SG_CALL sgAudioSourceUnqueueBuffers(SGAudioSource* source, size_t numbuffers)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceUnqueueBuffers)
        psgmAudioSourceUnqueueBuffers(source->dispatch->handle, numbuffers);
}

void SG_CALL sgAudioSourceSetPosition3f(SGAudioSource* source, float x, float y, float z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceSetPosition != NULL)
        psgmAudioSourceSetPosition(source->dispatch->handle, x, y, z);
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

    float buf;
    if(x == NULL)
        x = &buf;
    if(y == NULL)
        y = &buf;
    if(z == NULL)
        z = &buf;

    if(psgmAudioSourceGetPosition != NULL)
        psgmAudioSourceGetPosition(source->dispatch->handle, x, y, z);
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

    if(psgmAudioSourceSetVelocity != NULL)
        psgmAudioSourceSetVelocity(source->dispatch->handle, x, y, z);
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

    float buf;
    if(x == NULL)
        x = &buf;
    if(y == NULL)
        y = &buf;
    if(z == NULL)
        z = &buf;

    if(psgmAudioSourceGetVelocity != NULL)
        psgmAudioSourceGetVelocity(source->dispatch->handle, x, y, z);
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

    if(psgmAudioSourceSetPitch != NULL)
        psgmAudioSourceSetPitch(source->dispatch->handle, pitch);
}
float SG_CALL sgAudioSourceGetPitch(SGAudioSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    float pitch = 1.0f;
    if(psgmAudioSourceGetPitch != NULL)
        psgmAudioSourceGetPitch(source->dispatch->handle, &pitch);
    return pitch;
}

void SG_CALL sgAudioSourceSetVolume(SGAudioSource* source, float volume)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceSetVolume != NULL)
        psgmAudioSourceSetVolume(source->dispatch->handle, volume);
}
float SG_CALL sgAudioSourceGetVolume(SGAudioSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    float volume = 1.0f;
    if(psgmAudioSourceGetVolume != NULL)
        psgmAudioSourceGetVolume(source->dispatch->handle, &volume);
    return volume;
}

void SG_CALL sgAudioSourceSetLooping(SGAudioSource* source, SGbool looping)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(psgmAudioSourceSetLooping != NULL)
        psgmAudioSourceSetLooping(source->dispatch->handle, looping);
}
SGbool SG_CALL sgAudioSourceGetLooping(SGAudioSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool looping = SG_FALSE;
    if(psgmAudioSourceGetLooping != NULL)
        psgmAudioSourceGetLooping(source->dispatch->handle, &looping);
    return looping;
}
