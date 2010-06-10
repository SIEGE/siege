module demos.particles;

private
{
    import demos.common;
}

class ParticlesDemo: Demo
{
    this()
    {
        name = "Particles";
        brief = "TODO";
        description = "TODO";
    }
}

static this()
{
    demoinfo ~= ParticlesDemo.classinfo;
}
