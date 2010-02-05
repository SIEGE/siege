module siege.physics.constraint;

private
{
    import siege.modules.modules;
    import siege.modules.physics;
}

class Constraint
{
    private
    {
        void* chandle;
    }

    this()
    {
        assert(0, "TODO");
    }

    void* handle()
    {
        return chandle;
    }
}
