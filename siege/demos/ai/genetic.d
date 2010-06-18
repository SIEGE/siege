module demos.ai.genetic;

private
{
    import demos.common;
}

class GeneticDemo: Demo
{
    this()
    {
        name = "AI - Genetic Algorithms";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= GeneticDemo.classinfo;
}
