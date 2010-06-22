module siege.audio.buffer;

private
{
    import siege.util.vector;

    import siege.modules.audio;

    import std.string;
}

class Buffer
{
    private
    {
        void* shandle;
    }

    this()
    {
        if(sgAudioBufferCreate !is null)
            sgAudioBufferCreate(&shandle);
    }
    this(char[] fname, uint numbuffers = 0, uint buffersize = 4096)
    {
        this();

        uint channels;
        uint format;
        uint frequency;
        void* cdata;
        uint datalen;
        if(sgAudioLoadFile !is null)
            sgAudioLoadFile(toStringz(fname), &channels, &format, &frequency, &cdata, &datalen);
        if(sgAudioBufferSetData !is null)
            sgAudioBufferSetData(shandle, channels, format, frequency, cdata, datalen);
        if(sgAudioLoadFreeData !is null)
            sgAudioLoadFreeData(cdata);
    }
    ~this()
    {
        if(sgAudioBufferDestroy !is null)
            sgAudioBufferDestroy(shandle);
    }

    void data()
    {
        /// TODO
        //if(sgAudioBufferSetData !is null)
        //    sgAudioBufferSetData();
    }

    void* handle()
    {
        return shandle;
    }
}
