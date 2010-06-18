module demos.ai.boids;

private
{
    import demos.common;
}

class BoidsDemo: Demo
{
    this()
    {
        name = "AI - Boids";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= BoidsDemo.classinfo;
}
