module siege.audio.sample;

private
{
    import siege.core.core;
    import siege.util.vector;

    import siege.modules.audio;

    import siege.modules.modules;

    import std.string;
}

class Sample
{
    private
    {
        void* shandle;
    }

    this()
    {
        if(sgAudioSampleCreate !is null)
            sgAudioSampleCreate(&shandle);
    }
    this(char[] fname)
    {
        this();

        uint channels;
        uint format;
        uint frequency;
        void* cdata;
        uint datalen;
        if(sgAudioLoadFile !is null)
            sgAudioLoadFile(toStringz(fname), &channels, &format, &frequency, &cdata, &datalen);
        if(sgAudioSampleSetData !is null)
            sgAudioSampleSetData(shandle, channels, format, frequency, cdata, datalen);
        if(sgAudioLoadFreeData !is null)
            sgAudioLoadFreeData(cdata);
    }
    ~this()
    {
        if(sgAudioSampleDestroy !is null)
            sgAudioSampleDestroy(shandle);
    }

    void data()
    {
        /// TODO
        //if(sgAudioSampleSetData !is null)
        //    sgAudioSampleSetData();
    }

    void* handle()
    {
        return shandle;
    }
}
