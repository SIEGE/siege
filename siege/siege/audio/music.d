module siege.audio.music;

private
{
    import siege.audio.source;
    import siege.audio.sample;
}

class Music: Source
{
    this(Sample sample, float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(sample, pitch, gain, loop);
    }
    this(float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(pitch, gain, loop);
    }
}
