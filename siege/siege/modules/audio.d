module siege.modules.audio;

private
{
    import derelict.util.loader;

    import siege.modules.modules;
}

enum: uint
{
    SG_AUDIO_FORMAT_S8  = 0x01,
    SG_AUDIO_FORMAT_S16 = 0x02,
    SG_AUDIO_FORMAT_S24 = 0x03,
    SG_AUDIO_FORMAT_S32 = 0x04,

    SG_AUDIO_FORMAT_U8  = 0x05,
    SG_AUDIO_FORMAT_U16 = 0x06,
    SG_AUDIO_FORMAT_U24 = 0x07,
    SG_AUDIO_FORMAT_U32 = 0x08,

    SG_AUDIO_FORMAT_F   = 0x0A,
    SG_AUDIO_FORMAT_D   = 0x0B,
}

uint formatSizeof(uint format)
{
    switch(format)
    {
        case SG_AUDIO_FORMAT_S8:
        case SG_AUDIO_FORMAT_U8:
            return 1;
        case SG_AUDIO_FORMAT_S16:
        case SG_AUDIO_FORMAT_U16:
            return 2;
        case SG_AUDIO_FORMAT_S24:
        case SG_AUDIO_FORMAT_U24:
            return 3;
        case SG_AUDIO_FORMAT_S32:
        case SG_AUDIO_FORMAT_U32:
        case SG_AUDIO_FORMAT_F:
            return 4;
        case SG_AUDIO_FORMAT_D:
            return 8;

        default:
            assert(0, "Unknown audio format");
    }
    assert(0);
}

void loadModuleAudio(SharedLib lib)
{
    /// Audio
    checkBindFunc(sgmAudioSourceMaxSources)("sgmAudioSourceMaxSources", lib);

    checkBindFunc(sgmAudioBufferCreate)("sgmAudioBufferCreate", lib);
    //checkBindFunc(sgmAudioBufferCreateData)("sgmAudioBufferCreateData", lib);
    checkBindFunc(sgmAudioBufferSetData)("sgmAudioBufferSetData", lib);
    //checkBindFunc(sgmAudioBufferGetData)("sgmAudioBufferGetData", lib);
    //checkBindFunc(sgmAudioBufferFreeData)("sgmAudioBufferFreeData", lib);
    checkBindFunc(sgmAudioBufferDestroy)("sgmAudioBufferDestroy", lib);

    checkBindFunc(sgmAudioSourceCreate)("sgmAudioSourceCreate", lib);
    //checkBindFunc(sgmAudioSourceCreateData)("sgmAudioSourceCreateData", lib);
    checkBindFunc(sgmAudioSourceDestroy)("sgmAudioSourceDestroy", lib);
    checkBindFunc(sgmAudioSourcePlay)("sgmAudioSourcePlay", lib);
    checkBindFunc(sgmAudioSourceIsPlaying)("sgmAudioSourceIsPlaying", lib);
    checkBindFunc(sgmAudioSourcePause)("sgmAudioSourcePause", lib);
    checkBindFunc(sgmAudioSourceIsPaused)("sgmAudioSourceIsPaused", lib);
    checkBindFunc(sgmAudioSourceRewind)("sgmAudioSourceRewind", lib);
    //checkBindFunc(sgmAudioSourceIsRewinded)("sgmAudioSourceIsRewinded", lib);
    checkBindFunc(sgmAudioSourceStop)("sgmAudioSourceStop", lib);
    checkBindFunc(sgmAudioSourceIsStopped)("sgmAudioSourceIsStopped", lib);
    checkBindFunc(sgmAudioSourceSetBuffer)("sgmAudioSourceSetBuffer", lib);
    //checkBindFunc(sgmAudioSourceGetBuffer)("sgmAudioSourceGetBuffer", lib);
    checkBindFunc(sgmAudioSourceQueueBuffers)("sgmAudioSourceQueueBuffers", lib);
    checkBindFunc(sgmAudioSourceUnqueueBuffers)("sgmAudioSourceUnqueueBuffers", lib);
    checkBindFunc(sgmAudioSourceGetNumProcessedBuffers)("sgmAudioSourceNumProcessedBuffers", lib);
    checkBindFunc(sgmAudioSourceGetNumQueuedBuffers)("sgmAudioSourceNumQueuedBuffers", lib);
    checkBindFunc(sgmAudioSourceSetPosition)("sgmAudioSourceSetPosition", lib);
    checkBindFunc(sgmAudioSourceGetPosition)("sgmAudioSourceGetPosition", lib);
    checkBindFunc(sgmAudioSourceSetVelocity)("sgmAudioSourceSetVelocity", lib);
    checkBindFunc(sgmAudioSourceGetVelocity)("sgmAudioSourceGetVelocity", lib);
    //checkBindFunc(sgmAudioSourceSetFalloff)("sgmAudioSourceSetFalloff", lib);
    //checkBindFunc(sgmAudioSourceGetFalloff)("sgmAudioSourceGetFalloff", lib);
    checkBindFunc(sgmAudioSourceSetPitch)("sgmAudioSourceSetPitch", lib);
    checkBindFunc(sgmAudioSourceGetPitch)("sgmAudioSourceGetPitch", lib);
    checkBindFunc(sgmAudioSourceSetVolume)("sgmAudioSourceSetVolume", lib);
    checkBindFunc(sgmAudioSourceGetVolume)("sgmAudioSourceGetVolume", lib);
    checkBindFunc(sgmAudioSourceSetLooping)("sgmAudioSourceSetLooping", lib);
    checkBindFunc(sgmAudioSourceGetLooping)("sgmAudioSourceGetLooping", lib);

    /// Audio Load
    checkBindFunc(sgmAudioLoadFile)("sgmAudioLoadFile", lib);
    //checkBindFunc(sgmAudioLoadStream)("sgmAudioLoadStream", lib);
    checkBindFunc(sgmAudioLoadFreeData)("sgmAudioLoadFreeData", lib);

    checkBindFunc(sgmAudioFileCreate)("sgmAudioFileCreate", lib);
    checkBindFunc(sgmAudioFileDestroy)("sgmAudioFileDestroy", lib);
    checkBindFunc(sgmAudioFileNumSamples)("sgmAudioFileNumSamples", lib);
    checkBindFunc(sgmAudioFileRead)("sgmAudioFileRead", lib);
}

extern(C)
{
    /// Audio
/// \todo USE
    uint function(uint* max) sgmAudioSourceMaxSources;

    uint function(void** buffer) sgmAudioBufferCreate;
    //uint function(void** buffer, uint channels, uint type, uint frequency, void* data, uint datalen) sgmAudioBufferCreateData;
    uint function(void* buffer, uint channels, uint type, uint frequency, void* data, uint datalen) sgmAudioBufferSetData;
    //uint function(void* buffer, uint* channels, uint* type, uint* frequency, void** data, uint* datalen) sgmAudioBufferGetData;
    //uint function(void* data) sgmAudioBufferFreeData;
    uint function(void* buffer) sgmAudioBufferDestroy;

    uint function(void** source) sgmAudioSourceCreate;
    //uint function(void** source, void* buffer, float pitch, float gain, bool looping) sgmAudioSourceCreateData;
    uint function(void* source) sgmAudioSourceDestroy;
    uint function(void* source) sgmAudioSourcePlay;
    uint function(void* source, bool* playing) sgmAudioSourceIsPlaying;
    uint function(void* source) sgmAudioSourcePause;
    uint function(void* source, bool* paused) sgmAudioSourceIsPaused;
    uint function(void* source) sgmAudioSourceRewind;
    //uint function(void* source, bool* rewinded) sgmAudioSourceIsRewinded;
    uint function(void* source) sgmAudioSourceStop;
    uint function(void* source, bool* stopped) sgmAudioSourceIsStopped;
    uint function(void* source, void* buffer) sgmAudioSourceSetBuffer;
    //uint function(void* source, void** buffer) sgmAudioSourceGetBuffer;
/// \todo USE
    uint function(void* source, void** buffers, uint numbuffers) sgmAudioSourceQueueBuffers;
    uint function(void* source, uint numbuffers) sgmAudioSourceUnqueueBuffers;
/// \warning Will most likely change very soon
    uint function(void* source, uint* processed) sgmAudioSourceGetNumProcessedBuffers;
    uint function(void* source, uint* queued) sgmAudioSourceGetNumQueuedBuffers;
    uint function(void* source, float x, float y, float z) sgmAudioSourceSetPosition;
    uint function(void* source, float* x, float* y, float* z) sgmAudioSourceGetPosition;
    uint function(void* source, float x, float y, float z) sgmAudioSourceSetVelocity;
    uint function(void* source, float* x, float* y, float* z) sgmAudioSourceGetVelocity;
    //uint function(void* source, float falloff) sgmAudioSourceSetFalloff;
    //uint function(void* source, float* falloff) sgmAudioSourceGetFalloff;
    uint function(void* source, float pitch) sgmAudioSourceSetPitch;
    uint function(void* source, float* pitch) sgmAudioSourceGetPitch;
    uint function(void* source, float volume) sgmAudioSourceSetVolume;
    uint function(void* source, float* volume) sgmAudioSourceGetVolume;
    uint function(void* source, bool looping) sgmAudioSourceSetLooping;
    uint function(void* source, bool* looping) sgmAudioSourceGetLooping;

    /// Audio Load
    uint function(char* fname, uint* channels, uint* format, uint* frequency, void** data, uint* datalen)  sgmAudioLoadFile;
    //uint function(void* stream, uint* channels, uint* format, uint* frequency, void** data, uint* datalen) sgmAudioLoadStream;
    uint function(void* data) sgmAudioLoadFreeData;
/// \todo USE
    uint function(void** file, char* fname, uint* channels, uint* format, uint* frequency) sgmAudioFileCreate;
    uint function(void* file) sgmAudioFileDestroy;
    uint function(void* file, uint* samples) sgmAudioFileNumSamples;
    uint function(void* file, void* data, uint* datalen) sgmAudioFileRead;
}

