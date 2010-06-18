module demos.ai.fuzzy;

private
{
    import demos.common;
}

class FuzzyDemo: Demo
{
    this()
    {
        name = "AI - Fuzzy Logic";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= FuzzyDemo.classinfo;
}
