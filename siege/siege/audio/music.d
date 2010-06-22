module siege.audio.music;

private
{
    import siege.audio.source;
    import siege.audio.buffer;
}

class Music: Source
{
    this(Buffer buffer, float priority = 0.0, float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(buffer, priority, pitch, gain, loop);
    }
    this(float priority = 0.0, float pitch = 1.0, float gain = 0.25, bool loop = true)
    {
        super(priority, pitch, gain, loop);
    }
}
