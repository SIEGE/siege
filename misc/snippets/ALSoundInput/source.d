module source;

private
{
    import derelict.openal.al;

    import buffer;
}

enum SourceState: int
{
    Playing = AL_PLAYING,
    Paused = AL_PAUSED,
    Stopped = AL_STOPPED,
}

class Source
{
    uint id;

    private
    {
        Buffer _buffer;

        float _pitch;
        float _gain;
        bool _loop;
    }

    this(uint id)
    {
        this.id = id;
    }
    this(float pitch = 1.0, float gain = 1.0, bool loop = false)
    {
        _pitch = pitch;
        _gain = gain;
        _loop = loop;

        alGenSources(1, &id);
    	alSource3f(id, AL_POSITION, 0.0, 0.0, 0.0);
    	alSource3f(id, AL_VELOCITY, 0.0, 0.0, 0.0);
    	alSourcef(id, AL_PITCH, pitch);
    	alSourcef(id, AL_GAIN, gain);
    	alSourcei(id, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

    	//alSourcei(id, AL_BUFFER, buffer);
    }

    ~this()
    {
        alDeleteSources(1, &id);
    }

    void state(int s)
    {
        alSourcei(id, AL_SOURCE_STATE, s);
    }
    int state()
    {
        int s;
        alGetSourcei(id, AL_SOURCE_STATE, &s);
        return s;
    }

    // don't exit while playing...
    void bplay()
    {
        play();
        while(playing)
        {
        }
    }
    void play()
    {
        alSourcePlay(id);
    }
    bool playing()
    {
        return (state == SourceState.Playing) ? true : false;
    }

    void pause()
    {
        alSourcePause(id);
    }
    bool paused()
    {
        return (state == SourceState.Paused) ? true : false;
    }

    void rewind()
    {
        alSourceRewind(id);
    }
    void stop()
    {
        alSourceStop(id);
    }
    bool stopped()
    {
        return (state == SourceState.Stopped) ? true : false;
    }

    void buffer(Buffer buf)
    {
        _buffer = buf;
        alSourcei(id, AL_BUFFER, buf.id);
    }
    Buffer buffer()
    {
        return _buffer;
    }

    void pitch(float p)
    {
        _pitch = p;
    	alSourcef(id, AL_PITCH, p);
    }
    float pitch()
    {
        return _pitch;
    }

    void gain(float g)
    {
        _gain = g;
        alSourcef(id, AL_GAIN, g);
    }
    float gain()
    {
        return _gain;
    }

    void loop(bool l)
    {
        _loop = l;
        alSourcei(id, AL_LOOPING, l ? AL_TRUE : AL_FALSE);
    }
    bool loop()
    {
        return _loop;
    }
}
