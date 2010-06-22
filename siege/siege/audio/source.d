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

    this(float priority = 0.0)
    {
        if(sgmAudioSourceCreate !is null)
            sgmAudioSourceCreate(&shandle);
    }
    this(Buffer buffer, float priority = 0.0)
    {
        this();
        this.buffer = buffer;
    }
    this(float priority, float pitch, float volume, bool looping)
    {
        this();
        this.pitch = pitch;
        this.volume = volume;
        this.looping = looping;
    }
    this(Buffer buffer, float priority, float pitch, float volume, bool looping)
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
        if(sgmAudioSourceDestroy !is null)
            sgmAudioSourceDestroy(shandle);
    }

    void play(Vector position = Vector())
    {
        if(!position.isNan())
            this.position = position;

        if(sgmAudioSourcePlay !is null)
            sgmAudioSourcePlay(shandle);
    }
    bool playing()
    {
        bool playing;
        if(sgmAudioSourceIsPlaying !is null)
            sgmAudioSourceIsPlaying(shandle, &playing);
        return playing;
    }

    void pause()
    {
        if(sgmAudioSourcePause !is null)
            sgmAudioSourcePause(shandle);
    }
    bool paused()
    {
        bool paused;
        if(sgmAudioSourceIsPaused !is null)
            sgmAudioSourceIsPaused(shandle, &paused);
        return paused;
    }

    void rewind()
    {
        if(sgmAudioSourceRewind !is null)
            sgmAudioSourceRewind(shandle);
    }
    /*
    bool rewinded()
    {
        bool rewinded;
        if(sgmAudioSourceIsRewinded !is null)
            sgmAudioSourceIsRewinded(shandle, &rewinded);
        return rewinded;
    }
    */
    void stop()
    {
        if(sgmAudioSourceStop !is null)
            sgmAudioSourceStop(shandle);
    }
    bool stopped()
    {
        bool stopped;
        if(sgmAudioSourceIsStopped !is null)
            sgmAudioSourceIsStopped(shandle, &stopped);
        return stopped;
    }

    void buffer(Buffer b)
    {
        if(sgmAudioSourceSetBuffer !is null)
            sgmAudioSourceSetBuffer(shandle, b.handle);
    }
    /*Buffer buffer()
    {
        void* handle;
        if(sgmAudioSourceGetBuffer !is null)
            sgmAudioSourceGetBuffer(shandle, &handle);
    }*/

    void position(Vector pos)
    {
        if(sgmAudioSourceSetPosition !is null)
            sgmAudioSourceSetPosition(shandle, pos.x, pos.y, pos.z);
    }
    Vector position()
    {
        Vector pos;
        if(sgmAudioSourceGetPosition !is null)
            sgmAudioSourceGetPosition(shandle, &pos.x, &pos.y, &pos.z);
        return pos;
    }

    void velocity(Vector vel)
    {
        if(sgmAudioSourceSetVelocity !is null)
            sgmAudioSourceSetVelocity(shandle, vel.x, vel.y, vel.z);
    }
    Vector velocity()
    {
        Vector vel;
        if(sgmAudioSourceGetVelocity !is null)
            sgmAudioSourceGetVelocity(shandle, &vel.x, &vel.y, &vel.z);
        return vel;
    }

    /*void falloff(float f)
    {
        if(sgmAudioSourceSetFalloff !is null)
            sgmAudioSourceSetFalloff(shandle, f);
    }
    float falloff()
    {
        float f;
        if(sgmAudioSourceGetFalloff !is null)
            sgmAudioSourceGetFalloff(shandle, &f);
        return f;
    }*/

    void pitch(float p)
    {
        if(sgmAudioSourceSetPitch !is null)
            sgmAudioSourceSetPitch(shandle, p);
    }
    float pitch()
    {
        float p;
        if(sgmAudioSourceGetPitch !is null)
            sgmAudioSourceGetPitch(shandle, &p);
        return p;
    }

    void volume(float g)
    {
        if(sgmAudioSourceSetVolume !is null)
            sgmAudioSourceSetVolume(shandle, g);
    }
    float volume()
    {
        float g;
        if(sgmAudioSourceGetVolume !is null)
            sgmAudioSourceGetVolume(shandle, &g);
        return g;
    }

    void looping(bool l)
    {
        if(sgmAudioSourceSetLooping !is null)
            sgmAudioSourceSetLooping(shandle, l);
    }
    bool looping()
    {
        bool l;
        if(sgmAudioSourceGetLooping !is null)
            sgmAudioSourceGetLooping(shandle, &l);
        return l;
    }

    void* handle()
    {
        return shandle;
    }
}
