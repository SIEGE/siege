module siege.audio.source;

private
{
    import siege.util.vector;

    import siege.audio.buffer;

    import siege.modules.audio;
}

class Source
{
    private
    {
        void* shandle;
    }

    this()
    {
        if(sgAudioSourceCreate !is null)
            sgAudioSourceCreate(&shandle);
    }
    this(Buffer buffer)
    {
        this();
        this.buffer = buffer;
    }
    this(float pitch, float volume, bool looping)
    {
        this();
        this.pitch = pitch;
        this.volume = volume;
        this.looping = looping;
    }
    this(Buffer buffer, float pitch, float volume, bool looping)
    {
        this();
        this.buffer = buffer;
        this.pitch = pitch;
        this.volume = volume;
        this.looping = looping;
    }
    ~this()
    {
        //stop();
        if(sgAudioSourceDestroy !is null)
            sgAudioSourceDestroy(shandle);
    }

    void play(Vector position = Vector())
    {
        if(!position.isNan())
            this.position = position;

        if(sgAudioSourcePlay !is null)
            sgAudioSourcePlay(shandle);
    }
    bool playing()
    {
        bool playing;
        if(sgAudioSourceIsPlaying !is null)
            sgAudioSourceIsPlaying(shandle, &playing);
        return playing;
    }

    void pause()
    {
        if(sgAudioSourcePause !is null)
            sgAudioSourcePause(shandle);
    }
    bool paused()
    {
        bool paused;
        if(sgAudioSourceIsPaused !is null)
            sgAudioSourceIsPaused(shandle, &paused);
        return paused;
    }

    void rewind()
    {
        if(sgAudioSourceRewind !is null)
            sgAudioSourceRewind(shandle);
    }
    /*
    bool rewinded()
    {
        bool rewinded;
        if(sgAudioSourceIsRewinded !is null)
            sgAudioSourceIsRewinded(shandle, &rewinded);
        return rewinded;
    }
    */
    void stop()
    {
        if(sgAudioSourceStop !is null)
            sgAudioSourceStop(shandle);
    }
    bool stopped()
    {
        bool stopped;
        if(sgAudioSourceIsStopped !is null)
            sgAudioSourceIsStopped(shandle, &stopped);
        return stopped;
    }

    void buffer(Buffer b)
    {
        if(sgAudioSourceSetBuffer !is null)
            sgAudioSourceSetBuffer(shandle, b.handle);
    }
    /*Buffer buffer()
    {
        void* handle;
        if(sgAudioSourceGetBuffer !is null)
            sgAudioSourceGetBuffer(shandle, &handle);
    }*/

    void position(Vector pos)
    {
        if(sgAudioSourceSetPosition !is null)
            sgAudioSourceSetPosition(shandle, pos.x, pos.y, pos.z);
    }
    Vector position()
    {
        Vector pos;
        if(sgAudioSourceGetPosition !is null)
            sgAudioSourceGetPosition(shandle, &pos.x, &pos.y, &pos.z);
        return pos;
    }

    void velocity(Vector vel)
    {
        if(sgAudioSourceSetVelocity !is null)
            sgAudioSourceSetVelocity(shandle, vel.x, vel.y, vel.z);
    }
    Vector velocity()
    {
        Vector vel;
        if(sgAudioSourceGetVelocity !is null)
            sgAudioSourceGetVelocity(shandle, &vel.x, &vel.y, &vel.z);
        return vel;
    }

    void falloff(float f)
    {
        if(sgAudioSourceSetFalloff !is null)
            sgAudioSourceSetFalloff(shandle, f);
    }
    float falloff()
    {
        float f;
        if(sgAudioSourceGetFalloff !is null)
            sgAudioSourceGetFalloff(shandle, &f);
        return f;
    }

    void pitch(float p)
    {
        if(sgAudioSourceSetPitch !is null)
            sgAudioSourceSetPitch(shandle, p);
    }
    float pitch()
    {
        float p;
        if(sgAudioSourceGetPitch !is null)
            sgAudioSourceGetPitch(shandle, &p);
        return p;
    }

    void volume(float g)
    {
        if(sgAudioSourceSetVolume !is null)
            sgAudioSourceSetVolume(shandle, g);
    }
    float volume()
    {
        float g;
        if(sgAudioSourceGetVolume !is null)
            sgAudioSourceGetVolume(shandle, &g);
        return g;
    }

    void looping(bool l)
    {
        if(sgAudioSourceSetLooping !is null)
            sgAudioSourceSetLooping(shandle, l);
    }
    bool looping()
    {
        bool l;
        if(sgAudioSourceGetLooping !is null)
            sgAudioSourceGetLooping(shandle, &l);
        return l;
    }

    void* handle()
    {
        return shandle;
    }
}
