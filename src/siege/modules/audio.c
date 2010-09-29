#define SG_BUILD_LIBRARY
#include <siege/util/link.h>
#include <siege/modules/modules.h>
#include <siege/modules/audio.h>

void SG_EXPORT _sgModuleLoadAudio(SGLibrary* lib)
{
    void* fptr;
    /// Audio
    _SG_BINDS(_sg_modAudio, sgmAudioSourceMaxSources);

    _SG_BINDS(_sg_modAudio, sgmAudioBufferCreate);
    //_SG_BINDS(_sg_modAudio, sgmAudioBufferCreateData);
    _SG_BINDS(_sg_modAudio, sgmAudioBufferSetData);
    //_SG_BINDS(_sg_modAudio, sgmAudioBufferGetData);
    //_SG_BINDS(_sg_modAudio, sgmAudioBufferFreeData);
    _SG_BINDS(_sg_modAudio, sgmAudioBufferDestroy);

    _SG_BINDS(_sg_modAudio, sgmAudioSourceCreate);
    //_SG_BINDS(_sg_modAudio, sgmAudioSourceCreateData);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceDestroy);
    _SG_BINDS(_sg_modAudio, sgmAudioSourcePlay);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceIsPlaying);
    _SG_BINDS(_sg_modAudio, sgmAudioSourcePause);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceIsPaused);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceRewind);
    //_SG_BINDS(_sg_modAudio, sgmAudioSourceIsRewinded);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceStop);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceIsStopped);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetBuffer);
    //_SG_BINDS(_sg_modAudio, sgmAudioSourceGetBuffer);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceQueueBuffers);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceUnqueueBuffers);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetNumProcessedBuffers);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetNumQueuedBuffers);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetPosition);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetPosition);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetVelocity);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetVelocity);
    //_SG_BINDS(_sg_modAudio, sgmAudioSourceSetFalloff);
    //_SG_BINDS(_sg_modAudio, sgmAudioSourceGetFalloff);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetPitch);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetPitch);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetVolume);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetVolume);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceSetLooping);
    _SG_BINDS(_sg_modAudio, sgmAudioSourceGetLooping);

    /// Audio Load
    _SG_BINDS(_sg_modAudio, sgmAudioLoadFile);
    //_SG_BINDS(_sg_modAudio, sgmAudioLoadStream);
    _SG_BINDS(_sg_modAudio, sgmAudioLoadFreeData);

    _SG_BINDS(_sg_modAudio, sgmAudioFileCreate);
    _SG_BINDS(_sg_modAudio, sgmAudioFileDestroy);
    _SG_BINDS(_sg_modAudio, sgmAudioFileNumSamples);
    _SG_BINDS(_sg_modAudio, sgmAudioFileRead);
}

SGModuleAudio* SG_EXPORT sgModuleGetAudio(void)
{
    return &_sg_modAudio;
}

