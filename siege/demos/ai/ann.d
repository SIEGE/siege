module demos.ai.ann;

private
{
    import demos.common;
}

class ANNDemo: Demo
{
    this()
    {
        name = "AI - Artificial Neural Networks";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= ANNDemo.classinfo;
}
