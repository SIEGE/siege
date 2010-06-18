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
    checkBindFunc(sgAudioSampleCreate)("sgAudioSampleCreate", lib);
    //checkBindFunc(sgAudioSampleCreateData)("sgAudioSampleCreateData", lib);
    checkBindFunc(sgAudioSampleSetData)("sgAudioSampleSetData", lib);
    //checkBindFunc(sgAudioSampleGetData)("sgAudioSampleGetData", lib);
    //checkBindFunc(sgAudioSampleFreeData)("sgAudioSampleFreeData", lib);
    checkBindFunc(sgAudioSampleDestroy)("sgAudioSampleDestroy", lib);

    checkBindFunc(sgAudioSourceCreate)("sgAudioSourceCreate", lib);
    //checkBindFunc(sgAudioSourceCreateData)("sgAudioSourceCreateData", lib);
    checkBindFunc(sgAudioSourceDestroy)("sgAudioSourceDestroy", lib);
    checkBindFunc(sgAudioSourcePlay)("sgAudioSourcePlay", lib);
    checkBindFunc(sgAudioSourceIsPlaying)("sgAudioSourceIsPlaying", lib);
    checkBindFunc(sgAudioSourcePause)("sgAudioSourcePause", lib);
    checkBindFunc(sgAudioSourceIsPaused)("sgAudioSourceIsPaused", lib);
    checkBindFunc(sgAudioSourceRewind)("sgAudioSourceRewind", lib);
    //checkBindFunc(sgAudioSourceIsRewinded)("sgAudioSourceIsRewinded", lib);
    checkBindFunc(sgAudioSourceStop)("sgAudioSourceStop", lib);
    checkBindFunc(sgAudioSourceIsStopped)("sgAudioSourceIsStopped", lib);
    checkBindFunc(sgAudioSourceSetSample)("sgAudioSourceSetSample", lib);
    //checkBindFunc(sgAudioSourceGetSample)("sgAudioSourceGetSample", lib);
    checkBindFunc(sgAudioSourceSetPosition)("sgAudioSourceSetPosition", lib);
    checkBindFunc(sgAudioSourceGetPosition)("sgAudioSourceGetPosition", lib);
    checkBindFunc(sgAudioSourceSetVelocity)("sgAudioSourceSetVelocity", lib);
    checkBindFunc(sgAudioSourceGetVelocity)("sgAudioSourceGetVelocity", lib);
    checkBindFunc(sgAudioSourceSetPitch)("sgAudioSourceSetPitch", lib);
    checkBindFunc(sgAudioSourceGetPitch)("sgAudioSourceGetPitch", lib);
    checkBindFunc(sgAudioSourceSetGain)("sgAudioSourceSetGain", lib);
    checkBindFunc(sgAudioSourceGetGain)("sgAudioSourceGetGain", lib);
    checkBindFunc(sgAudioSourceSetLooping)("sgAudioSourceSetLooping", lib);
    checkBindFunc(sgAudioSourceGetLooping)("sgAudioSourceGetLooping", lib);

    /// Audio Load
    checkBindFunc(sgAudioLoadFile)("sgAudioLoadFile", lib);
    //checkBindFunc(sgAudioLoadStream)("sgAudioLoadStream", lib);
    checkBindFunc(sgAudioLoadFreeData)("sgAudioLoadFreeData", lib);
}

extern(C)
{
    /// Audio
    uint function(void** sample) sgAudioSampleCreate;
    //uint function(void** sample, uint channels, uint type, uint frequency, void* data, uint datalen) sgAudioSampleCreateData;
    uint function(void* sample, uint channels, uint type, uint frequency, void* data, uint datalen) sgAudioSampleSetData;
    //uint function(void* sample, uint* channels, uint* type, uint* frequency, void** data, uint* datalen) sgAudioSampleGetData;
    //uint function(void* data) sgAudioSampleFreeData;
    uint function(void* sample) sgAudioSampleDestroy;

    uint function(void** source) sgAudioSourceCreate;
    //uint function(void** source, void* sample, float pitch, float gain, bool looping) sgAudioSourceCreateData;
    uint function(void* source) sgAudioSourceDestroy;
    uint function(void* source) sgAudioSourcePlay;
    uint function(void* source, bool* playing) sgAudioSourceIsPlaying;
    uint function(void* source) sgAudioSourcePause;
    uint function(void* source, bool* paused) sgAudioSourceIsPaused;
    uint function(void* source) sgAudioSourceRewind;
    //uint function(void* source, bool* rewinded) sgAudioSourceIsRewinded;
    uint function(void* source) sgAudioSourceStop;
    uint function(void* source, bool* stopped) sgAudioSourceIsStopped;
    uint function(void* source, void* sample) sgAudioSourceSetSample;
    //uint function(void* source, void** sample) sgAudioSourceGetSample;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetPosition;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetPosition;
    uint function(void* source, float x, float y, float z) sgAudioSourceSetVelocity;
    uint function(void* source, float* x, float* y, float* z) sgAudioSourceGetVelocity;
    uint function(void* source, float pitch) sgAudioSourceSetPitch;
    uint function(void* source, float* pitch) sgAudioSourceGetPitch;
    uint function(void* source, float gain) sgAudioSourceSetGain;
    uint function(void* source, float* gain) sgAudioSourceGetGain;
    uint function(void* source, bool looping) sgAudioSourceSetLooping;
    uint function(void* source, bool* looping) sgAudioSourceGetLooping;

    /// Audio Load
    uint function(char* fname, uint* channels, uint* format, uint* frequency, void** data, uint* datalen)  sgAudioLoadFile;
    //uint function(void* stream, uint* channels, uint* format, uint* frequency, void** data, uint* datalen) sgAudioLoadStream;
    uint function(void* data) sgAudioLoadFreeData;
}

