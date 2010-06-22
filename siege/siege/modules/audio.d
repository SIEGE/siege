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

void loadModuleAudio(SharedLib lib)
{
    /// Audio
    checkBindFunc(sgAudioSourceMaxSources)("sgmAudioSourceMaxSources", lib);

    checkBindFunc(sgAudioBufferCreate)("sgmAudioBufferCreate", "sgAudioSampleCreate", lib);
    //checkBindFunc(sgAudioBufferCreateData)("sgmAudioBufferCreateData", "sgAudioSampleCreateData", lib);
    checkBindFunc(sgAudioBufferSetData)("sgmAudioBufferSetData", "sgAudioSampleSetData", lib);
    //checkBindFunc(sgAudioBufferGetData)("sgmAudioBufferGetData", "sgAudioSampleGetData", lib);
    //checkBindFunc(sgAudioBufferFreeData)("sgmAudioBufferFreeData", "sgAudioSampleFreeData", lib);
    checkBindFunc(sgAudioBufferDestroy)("sgmAudioBufferDestroy", "sgAudioSampleDestroy", lib);

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
    checkBindFunc(sgAudioSourceSetBuffer)("sgmAudioSourceSetBuffer", "sgAudioSourceSetSample", lib);
    //checkBindFunc(sgAudioSourceGetBuffer)("sgmAudioSourceGetBuffer", "sgAudioSourceGetSample", lib);
    checkBindFunc(sgmAudioSourceQueueBuffers)("sgmAudioSourceQueueBuffers", lib);
    checkBindFunc(sgmAudioSourceUnqueueBuffers)("sgmAudioSourceUnqueueBuffers", lib);
    checkBindFunc(sgAudioSourceNumProcessedBuffers)("sgmAudioSourceNumProcessedBuffers", lib);
    checkBindFunc(sgAudioSourceNumQueuedBuffers)("sgmAudioSourceNumQueuedBuffers", lib);
    checkBindFunc(sgAudioSourceSetPosition)("sgmAudioSourceSetPosition", lib);
    checkBindFunc(sgAudioSourceGetPosition)("sgmAudioSourceGetPosition", lib);
    checkBindFunc(sgAudioSourceSetVelocity)("sgmAudioSourceSetVelocity", lib);
    checkBindFunc(sgAudioSourceGetVelocity)("sgmAudioSourceGetVelocity", lib);
    checkBindFunc(sgAudioSourceSetFalloff)("sgmAudioSourceSetFalloff", lib);
    checkBindFunc(sgAudioSourceGetFalloff)("sgmAudioSourceGetFalloff", lib);
    checkBindFunc(sgAudioSourceSetPitch)("sgmAudioSourceSetPitch", lib);
    checkBindFunc(sgAudioSourceGetPitch)("sgmAudioSourceGetPitch", lib);
    checkBindFunc(sgAudioSourceSetVolume)("sgmAudioSourceSetVolume", "sgAudioSourceSetGain", lib);
    checkBindFunc(sgAudioSourceGetVolume)("sgmAudioSourceGetVolume", "sgAudioSourceSetGain", lib);
    checkBindFunc(sgAudioSourceSetLooping)("sgmAudioSourceSetLooping", lib);
    checkBindFunc(sgAudioSourceGetLooping)("sgmAudioSourceGetLooping", lib);

    /// Audio Load
    checkBindFunc(sgAudioLoadFile)("sgmAudioLoadFile", lib);
    //checkBindFunc(sgAudioLoadStream)("sgmAudioLoadStream", lib);
    checkBindFunc(sgAudioLoadFreeData)("sgmAudioLoadFreeData", lib);

    checkBindFunc(sgAudioFileCreate)("sgmAudioFileCreate", lib);
    checkBindFunc(sgAudioFileDestroy)("sgmAudioFileDestroy", lib);
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
    uint function(void* source, void** buffers, uint numbuffers) sgmAudioSourceQueueBuffers;
    uint function(void* source, uint numbuffers) sgmAudioSourceUnqueueBuffers;
/// \warning Will most likely change very soon
    uint function(void* source, uint* processed) sgAudioSourceNumProcessedBuffers;
    uint function(void* source, uint* queued) sgAudioSourceNumQueuedBuffers;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetPosition;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetPosition;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetVelocity;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetVelocity;
    uint function(void* source, float falloff) sgAudioSourceSetFalloff;
    uint function(void* source, float* falloff) sgAudioSourceGetFalloff;
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
    uint function(void* file, void* data, uint datalen) sgAudioFileRead;
}

