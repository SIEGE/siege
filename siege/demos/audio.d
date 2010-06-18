module demos.audio;

private
{
    import demos.common;
}

class AudioDemo: Demo
{
    this()
    {
        name = "Audio";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= AudioDemo.classinfo;
}
