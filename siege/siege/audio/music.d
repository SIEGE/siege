module siege.audio.music;

private
{
    import siege.audio.source;
    import siege.audio.buffer;
}

class Music: Source
{
    this(Buffer buffer, float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(buffer, pitch, gain, loop);
    }
    this(float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(pitch, gain, loop);
    }
}
