module capture;

private
{
    import derelict.openal.al;

    import source;
    import buffer;
}

class Capture
{
    ALCdevice* capture;
    int sdata;
    uint frequency;
    uint format;
    uint bufsize;
    void[] data;

    this(char[] device, uint frequency = 44100, uint format = AL_FORMAT_MONO16, uint bufsize = 44100 * 1)
    {
        if(format == AL_FORMAT_MONO16 || format == AL_FORMAT_STEREO16)
            sdata = 2;
        else
            sdata = 1;

        this.frequency = frequency;
        this.format = format;
        this.bufsize = bufsize;

        capture = alcCaptureOpenDevice(null, frequency, format, bufsize);
    }
    ~this()
    {
        alcCaptureCloseDevice(capture);
    }

    void start()
    {
        alcCaptureStart(capture);
    }
    uint poll()
    {
        int samples;
        alcGetIntegerv(capture, ALC_CAPTURE_SAMPLES, 1, &samples);

        if(samples > 0)
        {
            uint dlen = data.length;
            data.length = data.length + samples * sdata;
            alcCaptureSamples(capture, data[dlen..$].ptr, samples);
        }
        return samples;
    }
    void stop()
    {
        alcCaptureStop(capture);
    }
    uint length()
    {
        return data.length;
    }

    Buffer toBuffer()
    {
        Buffer buffer = new Buffer;
        buffer.data(data, format, frequency);
        return buffer;
    }

    Source toSource()
    {
        Source source = new Source;
        source.buffer = toBuffer();
        return source;
    }
}
