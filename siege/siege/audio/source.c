#define SG_BUILD_LIBRARY
#include <siege/audio/source.h>
#include <siege/modules/audio.h>

#include <stdlib.h>
#include <math.h>

SGbool SG_EXPORT _sgSourceInit(void)
{
    _sg_srcDisLength = 16;
    if(_sg_modAudio.sgmAudioSourceMaxSources != NULL)
        _sg_modAudio.sgmAudioSourceMaxSources(&_sg_srcDisLength);
    _sg_srcDisList = malloc(_sg_srcDisLength * sizeof(SGSourceDispatch));

    SGuint i;
    for(i = 0; i < _sg_srcDisLength; i++)
    {
        _sg_srcDisList[i].source = NULL;
        if(_sg_modAudio.sgmAudioSourceCreate != NULL)
            _sg_modAudio.sgmAudioSourceCreate(&_sg_srcDisList[i].handle);
    }

    return SG_TRUE;
}
SGbool SG_EXPORT _sgSourceDeinit(void)
{
    SGuint i;
    for(i = 0; i <_sg_srcDisLength; i++)
    {
        if(_sg_modAudio.sgmAudioSourceDestroy != NULL)
            _sg_modAudio.sgmAudioSourceDestroy(_sg_srcDisList[i].handle);
    }

    free(_sg_srcDisList);

    return SG_TRUE;
}

SGSourceDispatch* SG_EXPORT _sgSourceGetFreeDispatch(SGSource* source)
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
        if((_sg_modAudio.sgmAudioSourceGetNumProcessedBuffers != NULL) && (_sg_modAudio.sgmAudioSourceGetNumQueuedBuffers != NULL))
        {
            _sg_modAudio.sgmAudioSourceGetNumProcessedBuffers(_sg_srcDisList[i].handle, &processed);
            _sg_modAudio.sgmAudioSourceGetNumQueuedBuffers(_sg_srcDisList[i].handle, &queued);
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

SGSource* SG_EXPORT sgSourceCreate(SGBuffer* buffer, float priority, float volume, float pitch, SGbool looping)
{
    SGSource* source = malloc(sizeof(SGSource));
    source->priority = priority;

    source->dispatch = _sgSourceGetFreeDispatch(source);
    // todo: enqueue?
    if(source->dispatch == NULL)
    {
        free(source);
        return NULL;
    }

    //if(_sg_modAudio.sgmAudioSourceSetBuffer != NULL)
    //    _sg_modAudio.sgmAudioSourceSetBuffer(source->dispatch->handle, buffer->handle);
    if(_sg_modAudio.sgmAudioSourceQueueBuffers != NULL)
        _sg_modAudio.sgmAudioSourceQueueBuffers(source->dispatch->handle, &buffer->handle, 1);

    return source;
}
void SG_EXPORT sgSourceDestroy(SGSource* source)
{
    if(source == NULL)
        return;

    // tell dispatch that the source is available
    if(source->dispatch != NULL)
        source->dispatch->source = NULL;
    free(source);
}

void SG_EXPORT sgSourcePlay(SGSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourcePlay != NULL)
        _sg_modAudio.sgmAudioSourcePlay(source->dispatch->handle);
}
SGbool SG_EXPORT sgSourceIsPlaying(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool playing = SG_FALSE;
    if(_sg_modAudio.sgmAudioSourceIsPlaying != NULL)
        _sg_modAudio.sgmAudioSourceIsPlaying(source->dispatch->handle, &playing);
    return playing;
}
void SG_EXPORT sgSourcePause(SGSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourcePause != NULL)
        _sg_modAudio.sgmAudioSourcePause(source->dispatch->handle);
}
SGbool SG_EXPORT sgSourceIsPaused(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool paused = SG_FALSE;
    if(_sg_modAudio.sgmAudioSourceIsPaused != NULL)
        _sg_modAudio.sgmAudioSourceIsPaused(source->dispatch->handle, &paused);
    return paused;
}
void SG_EXPORT sgSourceRewind(SGSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceRewind != NULL)
        _sg_modAudio.sgmAudioSourceRewind(source->dispatch->handle);
}
/*SGbool SG_EXPORT sgSourceIsRewinded(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool rewinded = SG_FALSE;
    if(_sg_modAudio.sgmAudioSourceIsRewinded != NULL)
        _sg_modAudio.sgmAudioSourceIsRewinded(source->dispatch->handle, &rewinded);
    return rewinded;
}*/
void SG_EXPORT sgSourceStop(SGSource* source)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceStop != NULL)
        _sg_modAudio.sgmAudioSourceStop(source->dispatch->handle);
}
SGbool SG_EXPORT sgSourceIsStopped(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool stopped = SG_FALSE;
    if(_sg_modAudio.sgmAudioSourceIsStopped != NULL)
        _sg_modAudio.sgmAudioSourceIsStopped(source->dispatch->handle, &stopped);
    return stopped;
}
SGbool SG_EXPORT sgSourceIsActive(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGuint processed = 0;
    SGuint queued = 0;
    if(_sg_modAudio.sgmAudioSourceGetNumProcessedBuffers != NULL)
        _sg_modAudio.sgmAudioSourceGetNumProcessedBuffers(source->dispatch->handle, &processed);
    if(_sg_modAudio.sgmAudioSourceGetNumQueuedBuffers != NULL)
        _sg_modAudio.sgmAudioSourceGetNumQueuedBuffers(source->dispatch->handle, &queued);

    return processed != queued;
}
void SG_EXPORT sgSourceQueueBuffers(SGSource* source, SGBuffer** buffers, SGuint numbuffers)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    SGuint i;
    for(i = 0; i < numbuffers; i++)
        sgSourceQueueBuffer(source, buffers[i]);
}
void SG_EXPORT sgSourceQueueBuffer(SGSource* source, SGBuffer* buffer)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    //if(_sg_modAudio.sgmAudioSourceSetBuffer != NULL)
    //    _sg_modAudio.sgmAudioSourceSetBuffer(source->dispatch->handle, buffer->handle);
    if(_sg_modAudio.sgmAudioSourceQueueBuffers != NULL)
        _sg_modAudio.sgmAudioSourceQueueBuffers(source->dispatch->handle, &buffer->handle, 1);
}

void SG_EXPORT sgSourceSetPosition3f(SGSource* source, float x, float y, float z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceSetPosition != NULL)
        _sg_modAudio.sgmAudioSourceSetPosition(source->dispatch->handle, x, y, z);
}
void SG_EXPORT sgSourceSetPosition2f(SGSource* source, float x, float y)
{
    sgSourceSetPosition3f(source, x, y, 0.0f);
}
void SG_EXPORT sgSourceGetPosition3f(SGSource* source, float* x, float* y, float* z)
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

    if(_sg_modAudio.sgmAudioSourceGetPosition != NULL)
        _sg_modAudio.sgmAudioSourceGetPosition(source->dispatch->handle, x, y, z);
}
void SG_EXPORT sgSourceGetPosition2f(SGSource* source, float* x, float* y)
{
    sgSourceGetPosition3f(source, x, y, NULL);
}

void SG_EXPORT sgSourceSetVelocity3f(SGSource* source, float x, float y, float z)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceSetVelocity != NULL)
        _sg_modAudio.sgmAudioSourceSetVelocity(source->dispatch->handle, x, y, z);
}
void SG_EXPORT sgSourceSetVelocity2f(SGSource* source, float x, float y)
{
    sgSourceSetVelocity3f(source, x, y, 0.0f);
}
void SG_EXPORT sgSourceGetVelocity3f(SGSource* source, float* x, float* y, float* z)
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

    if(_sg_modAudio.sgmAudioSourceGetVelocity != NULL)
        _sg_modAudio.sgmAudioSourceGetVelocity(source->dispatch->handle, x, y, z);
}
void SG_EXPORT sgSourceGetVelocity2f(SGSource* source, float* x, float* y)
{
    sgSourceGetVelocity3f(source, x, y, NULL);
}

//void SG_EXPORT sgSourceSetFalloff(SGSource* source, float falloff);
//float SG_EXPORT sgSourceGetFalloff(SGSource* source);

void SG_EXPORT sgSourceSetPitch(SGSource* source, float pitch)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceSetPitch != NULL)
        _sg_modAudio.sgmAudioSourceSetPitch(source->dispatch->handle, pitch);
}
float SG_EXPORT sgSourceGetPitch(SGSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    float pitch = 1.0f;
    if(_sg_modAudio.sgmAudioSourceGetPitch != NULL)
        _sg_modAudio.sgmAudioSourceGetPitch(source->dispatch->handle, &pitch);
    return pitch;
}

void SG_EXPORT sgSourceSetVolume(SGSource* source, float volume)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceSetVolume != NULL)
        _sg_modAudio.sgmAudioSourceSetVolume(source->dispatch->handle, volume);
}
float SG_EXPORT sgSourceGetVolume(SGSource* source)
{
    if(source == NULL)
        return SG_NAN;
    if(source->dispatch == NULL)
        return SG_NAN;

    float volume = 1.0f;
    if(_sg_modAudio.sgmAudioSourceGetVolume != NULL)
        _sg_modAudio.sgmAudioSourceGetVolume(source->dispatch->handle, &volume);
    return volume;
}

void SG_EXPORT sgSourceSetLooping(SGSource* source, SGbool looping)
{
    if(source == NULL)
        return;
    if(source->dispatch == NULL)
        return;

    if(_sg_modAudio.sgmAudioSourceSetLooping != NULL)
        _sg_modAudio.sgmAudioSourceSetLooping(source->dispatch->handle, looping);
}
SGbool SG_EXPORT sgSourceGetLooping(SGSource* source)
{
    if(source == NULL)
        return SG_FALSE;
    if(source->dispatch == NULL)
        return SG_FALSE;

    SGbool looping = SG_FALSE;
    if(_sg_modAudio.sgmAudioSourceGetLooping != NULL)
        _sg_modAudio.sgmAudioSourceGetLooping(source->dispatch->handle, &looping);
    return looping;
}
