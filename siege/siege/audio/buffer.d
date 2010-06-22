module siege.audio.buffer;

private
{
    import siege.util.vector;

    import siege.modules.audio;

    import std.string;
}

class Buffer
{
    void* shandle;
    private
    {
        uint length;
    }

    this()
    {
        if(sgmAudioBufferCreate !is null)
            sgmAudioBufferCreate(&shandle);
    }
    this(char[] fname)
    {
        this();

        uint channels;
        uint format;
        uint frequency;
        void* cdata;
        uint datalen;
        if(sgmAudioLoadFile !is null)
            sgmAudioLoadFile(toStringz(fname), &channels, &format, &frequency, &cdata, &datalen);
        if(sgmAudioBufferSetData !is null)
            sgmAudioBufferSetData(shandle, channels, format, frequency, cdata, datalen);
        if(sgmAudioLoadFreeData !is null)
            sgmAudioLoadFreeData(cdata);
    }
    ~this()
    {
        if(sgmAudioBufferDestroy !is null)
            sgmAudioBufferDestroy(shandle);
    }

    void data()
    {
        /// TODO
        //if(sgmAudioBufferSetData !is null)
        //    sgmAudioBufferSetData();
    }

    void* handle()
    {
        return shandle;
    }
}
