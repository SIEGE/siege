module siege.audio.source;

private
{
    import siege.util.vector;

    import siege.audio.sample;

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
    this(Sample sample)
    {
        this();
        this.sample = sample;
    }
    this(float pitch, float gain, bool looping)
    {
        this();
        this.pitch = pitch;
        this.gain = gain;
        this.looping = looping;
    }
    this(Sample sample, float pitch, float gain, bool looping)
    {
        this();
        this.sample = sample;
        this.pitch = pitch;
        this.gain = gain;
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

    void sample(Sample s)
    {
        if(sgAudioSourceSetSample !is null)
            sgAudioSourceSetSample(shandle, s.handle);
    }
    /*Sample sample()
    {
        void* handle;
        if(sgAudioSourceGetSample !is null)
            sgAudioSourceGetSample(shandle, &handle);
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

    void gain(float g)
    {
        if(sgAudioSourceSetGain !is null)
            sgAudioSourceSetGain(shandle, g);
    }
    float gain()
    {
        float g;
        if(sgAudioSourceGetGain !is null)
            sgAudioSourceGetGain(shandle, &g);
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
