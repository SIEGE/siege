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
    checkBindFunc(sgAudioSourceMaxSources)("sgmAudioSourceMaxSources", lib);

    checkBindFunc(sgAudioBufferCreate)("sgmAudioBufferCreate", lib);
    //checkBindFunc(sgAudioBufferCreateData)("sgmAudioBufferCreateData", lib);
    checkBindFunc(sgAudioBufferSetData)("sgmAudioBufferSetData", lib);
    //checkBindFunc(sgAudioBufferGetData)("sgmAudioBufferGetData", lib);
    //checkBindFunc(sgAudioBufferFreeData)("sgmAudioBufferFreeData", lib);
    checkBindFunc(sgAudioBufferDestroy)("sgmAudioBufferDestroy", lib);

    checkBindFunc(sgAudioSourceCreate)("sgmAudioSourceCreate", lib);
    //checkBindFunc(sgAudioSourceCreateData)("sgmAudioSourceCreateData", lib);
    checkBindFunc(sgAudioSourceDestroy)("sgmAudioSourceDestroy", lib);
    checkBindFunc(sgAudioSourcePlay)("sgmAudioSourcePlay", lib);
    checkBindFunc(sgAudioSourceIsPlaying)("sgmAudioSourceIsPlaying", lib);
    checkBindFunc(sgAudioSourcePause)("sgmAudioSourcePause", lib);
    checkBindFunc(sgAudioSourceIsPaused)("sgmAudioSourceIsPaused", lib);
    checkBindFunc(sgAudioSourceRewind)("sgmAudioSourceRewind", lib);
    //checkBindFunc(sgAudioSourceIsRewinded)("sgmAudioSourceIsRewinded", lib);
    checkBindFunc(sgAudioSourceStop)("sgmAudioSourceStop", lib);
    checkBindFunc(sgAudioSourceIsStopped)("sgmAudioSourceIsStopped", lib);
    checkBindFunc(sgAudioSourceSetBuffer)("sgmAudioSourceSetBuffer", lib);
    //checkBindFunc(sgAudioSourceGetBuffer)("sgmAudioSourceGetBuffer", lib);
    checkBindFunc(sgAudioSourceQueueBuffers)("sgmAudioSourceQueueBuffers", lib);
    checkBindFunc(sgAudioSourceUnqueueBuffers)("sgmAudioSourceUnqueueBuffers", lib);
    checkBindFunc(sgAudioSourceGetNumProcessedBuffers)("sgmAudioSourceNumProcessedBuffers", lib);
    checkBindFunc(sgAudioSourceGetNumQueuedBuffers)("sgmAudioSourceNumQueuedBuffers", lib);
    checkBindFunc(sgAudioSourceSetPosition)("sgmAudioSourceSetPosition", lib);
    checkBindFunc(sgAudioSourceGetPosition)("sgmAudioSourceGetPosition", lib);
    checkBindFunc(sgAudioSourceSetVelocity)("sgmAudioSourceSetVelocity", lib);
    checkBindFunc(sgAudioSourceGetVelocity)("sgmAudioSourceGetVelocity", lib);
    //checkBindFunc(sgAudioSourceSetFalloff)("sgmAudioSourceSetFalloff", lib);
    //checkBindFunc(sgAudioSourceGetFalloff)("sgmAudioSourceGetFalloff", lib);
    checkBindFunc(sgAudioSourceSetPitch)("sgmAudioSourceSetPitch", lib);
    checkBindFunc(sgAudioSourceGetPitch)("sgmAudioSourceGetPitch", lib);
    checkBindFunc(sgAudioSourceSetVolume)("sgmAudioSourceSetVolume", lib);
    checkBindFunc(sgAudioSourceGetVolume)("sgmAudioSourceGetVolume", lib);
    checkBindFunc(sgAudioSourceSetLooping)("sgmAudioSourceSetLooping", lib);
    checkBindFunc(sgAudioSourceGetLooping)("sgmAudioSourceGetLooping", lib);

    /// Audio Load
    checkBindFunc(sgAudioLoadFile)("sgmAudioLoadFile", lib);
    //checkBindFunc(sgAudioLoadStream)("sgmAudioLoadStream", lib);
    checkBindFunc(sgAudioLoadFreeData)("sgmAudioLoadFreeData", lib);

    checkBindFunc(sgAudioFileCreate)("sgmAudioFileCreate", lib);
    checkBindFunc(sgAudioFileDestroy)("sgmAudioFileDestroy", lib);
    checkBindFunc(sgmAudioFileNumSamples)("sgmAudioFileNumSamples", lib);
    checkBindFunc(sgAudioFileRead)("sgmAudioFileRead", lib);
}

extern(C)
{
    /// Audio
/// \todo USE
    uint function(uint* max) sgAudioSourceMaxSources;

    uint function(void** buffer) sgAudioBufferCreate;
    //uint function(void** buffer, uint channels, uint type, uint frequency, void* data, uint datalen) sgAudioBufferCreateData;
    uint function(void* buffer, uint channels, uint type, uint frequency, void* data, uint datalen) sgAudioBufferSetData;
    //uint function(void* buffer, uint* channels, uint* type, uint* frequency, void** data, uint* datalen) sgAudioBufferGetData;
    //uint function(void* data) sgAudioBufferFreeData;
    uint function(void* buffer) sgAudioBufferDestroy;

    uint function(void** source) sgAudioSourceCreate;
    //uint function(void** source, void* buffer, float pitch, float gain, bool looping) sgAudioSourceCreateData;
    uint function(void* source) sgAudioSourceDestroy;
    uint function(void* source) sgAudioSourcePlay;
    uint function(void* source, bool* playing) sgAudioSourceIsPlaying;
    uint function(void* source) sgAudioSourcePause;
    uint function(void* source, bool* paused) sgAudioSourceIsPaused;
    uint function(void* source) sgAudioSourceRewind;
    //uint function(void* source, bool* rewinded) sgAudioSourceIsRewinded;
    uint function(void* source) sgAudioSourceStop;
    uint function(void* source, bool* stopped) sgAudioSourceIsStopped;
    uint function(void* source, void* buffer) sgAudioSourceSetBuffer;
    //uint function(void* source, void** buffer) sgAudioSourceGetBuffer;
/// \todo USE
    uint function(void* source, void** buffers, uint numbuffers) sgAudioSourceQueueBuffers;
    uint function(void* source, uint numbuffers) sgAudioSourceUnqueueBuffers;
/// \warning Will most likely change very soon
    uint function(void* source, uint* processed) sgAudioSourceGetNumProcessedBuffers;
    uint function(void* source, uint* queued) sgAudioSourceGetNumQueuedBuffers;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetPosition;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetPosition;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetVelocity;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetVelocity;
    //uint function(void* source, float falloff) sgAudioSourceSetFalloff;
    //uint function(void* source, float* falloff) sgAudioSourceGetFalloff;
    uint function(void* source, float pitch) sgAudioSourceSetPitch;
    uint function(void* source, float* pitch) sgAudioSourceGetPitch;
    uint function(void* source, float volume) sgAudioSourceSetVolume;
    uint function(void* source, float* volume) sgAudioSourceGetVolume;
    uint function(void* source, bool looping) sgAudioSourceSetLooping;
    uint function(void* source, bool* looping) sgAudioSourceGetLooping;

    /// Audio Load
    uint function(char* fname, uint* channels, uint* format, uint* frequency, void** data, uint* datalen)  sgAudioLoadFile;
    //uint function(void* stream, uint* channels, uint* format, uint* frequency, void** data, uint* datalen) sgAudioLoadStream;
    uint function(void* data) sgAudioLoadFreeData;
/// \todo USE
    uint function(void** file, char* fname, uint* channels, uint* format, uint* frequency) sgAudioFileCreate;
    uint function(void* file) sgAudioFileDestroy;
    uint function(void* file, uint* samples) sgmAudioFileNumSamples;
    uint function(void* file, void* data, uint* datalen) sgAudioFileRead;
}

